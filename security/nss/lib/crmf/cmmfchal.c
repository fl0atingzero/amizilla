/* -*- Mode: C; tab-width: 8 -*-*/
/*
 * The contents of this file are subject to the Mozilla Public
 * License Version 1.1 (the "License"); you may not use this file
 * except in compliance with the License. You may obtain a copy of
 * the License at http://www.mozilla.org/MPL/
 * 
 * Software distributed under the License is distributed on an "AS
 * IS" basis, WITHOUT WARRANTY OF ANY KIND, either express or
 * implied. See the License for the specific language governing
 * rights and limitations under the License.
 * 
 * The Original Code is the Netscape security libraries.
 * 
 * The Initial Developer of the Original Code is Netscape
 * Communications Corporation.  Portions created by Netscape are 
 * Copyright (C) 1994-2000 Netscape Communications Corporation.  All
 * Rights Reserved.
 * 
 * Contributor(s):
 * 
 * Alternatively, the contents of this file may be used under the
 * terms of the GNU General Public License Version 2 or later (the
 * "GPL"), in which case the provisions of the GPL are applicable 
 * instead of those above.  If you wish to allow use of your 
 * version of this file only under the terms of the GPL and not to
 * allow others to use your version of this file under the MPL,
 * indicate your decision by deleting the provisions above and
 * replace them with the notice and other provisions required by
 * the GPL.  If you do not delete the provisions above, a recipient
 * may use your version of this file under either the MPL or the
 * GPL.
 */

#include "cmmf.h"
#include "cmmfi.h"
#include "sechash.h"
#include "genname.h"
#include "pk11func.h"
#include "cert.h"
#include "secitem.h"
#include "secmod.h"
#include "keyhi.h"

static int
cmmf_create_witness_and_challenge(PRArenaPool     *poolp,
				  CMMFChallenge   *challenge,
				  long             inRandom,
				  SECItem         *senderDER,
				  SECKEYPublicKey *inPubKey,
				  void            *passwdArg)
{
    SECItem       *encodedRandNum;
    SECItem        encodedRandStr = {siBuffer, NULL, 0};
    SECItem       *dummy;
    unsigned char *randHash, *senderHash, *encChal=NULL;
    unsigned       modulusLen = 0;
    SECStatus      rv = SECFailure;
    CMMFRand       randStr= { {siBuffer, NULL, 0}, {siBuffer, NULL, 0}};
    PK11SlotInfo  *slot;
    PK11SymKey    *symKey = NULL;
    CK_OBJECT_HANDLE id;
    CERTSubjectPublicKeyInfo *spki = NULL;

    
    encodedRandNum = SEC_ASN1EncodeInteger(poolp, &challenge->randomNumber,
					   inRandom);
    encodedRandNum = &challenge->randomNumber;
    randHash   = PORT_ArenaNewArray(poolp, unsigned char, SHA1_LENGTH);
    senderHash = PORT_ArenaNewArray(poolp, unsigned char, SHA1_LENGTH);
    if (randHash == NULL) {
        goto loser;
    }
    rv = PK11_HashBuf(SEC_OID_SHA1, randHash, encodedRandNum->data, 
		      (uint32)encodedRandNum->len);
    if (rv != SECSuccess) {
        goto loser;
    }
    rv = PK11_HashBuf(SEC_OID_SHA1, senderHash, senderDER->data,
		      (uint32)senderDER->len);
    if (rv != SECSuccess) {
        goto loser;
    }
    challenge->witness.data = randHash;
    challenge->witness.len  = SHA1_LENGTH;

    randStr.integer    = *encodedRandNum;
    randStr.senderHash.data = senderHash;
    randStr.senderHash.len  = SHA1_LENGTH;
    dummy = SEC_ASN1EncodeItem(NULL, &encodedRandStr, &randStr, 
			       CMMFRandTemplate);
    if (dummy != &encodedRandStr) {
        rv = SECFailure;
        goto loser;
    }
    /* XXXX Now I have to encrypt encodedRandStr and stash it away. */
    modulusLen = SECKEY_PublicKeyStrength(inPubKey);
    encChal = PORT_ArenaNewArray(poolp, unsigned char, modulusLen);
    if (encChal == NULL) {
        rv = SECFailure;
        goto loser;
    }
    slot =PK11_GetBestSlot(CKM_RSA_PKCS, passwdArg);
    if (slot == NULL) {
        rv = SECFailure;
        goto loser;
    }
    id = PK11_ImportPublicKey(slot, inPubKey, PR_FALSE);
    /* In order to properly encrypt the data, we import as a symmetric
     * key, and then wrap that key.  That in essence encrypts the data.
     * This is the method recommended in the PK11 world in order
     * to prevent threading issues as well as breaking any other semantics
     * the PK11 libraries depend on.
     */
    symKey = PK11_ImportSymKey(slot, CKM_RSA_PKCS, PK11_OriginGenerated,
			       CKA_VALUE, &encodedRandStr, passwdArg);
    if (symKey == NULL) {
        rv = SECFailure;
	goto loser;
    }
    challenge->challenge.data = encChal;
    challenge->challenge.len  = modulusLen;
    rv = PK11_PubWrapSymKey(CKM_RSA_PKCS, inPubKey, symKey, 
			    &challenge->challenge);
    PK11_FreeSlot(slot);
    if (rv != SECSuccess) {
	goto loser;
    }
    rv = SECITEM_CopyItem(poolp, &challenge->senderDER, senderDER);
    crmf_get_public_value(inPubKey, &challenge->key);
    /* Fall through */
 loser:
    if (spki != NULL) {
        SECKEY_DestroySubjectPublicKeyInfo(spki);
    }
    if (encodedRandStr.data != NULL) {
        PORT_Free(encodedRandStr.data);
    }
    if (encodedRandNum != NULL) {
        SECITEM_FreeItem(encodedRandNum, PR_TRUE);
    }
    if (symKey != NULL) {
        PK11_FreeSymKey(symKey);
    }
    return rv;
}

static SECStatus
cmmf_create_first_challenge(CMMFPOPODecKeyChallContent *challContent, 
			    long                        inRandom, 
			    SECItem                    *senderDER, 
			    SECKEYPublicKey            *inPubKey,
			    void                       *passwdArg)
{
    SECOidData     *oidData;
    CMMFChallenge  *challenge;
    SECAlgorithmID *algId;
    PRArenaPool    *poolp;
    SECStatus       rv;

    oidData = SECOID_FindOIDByTag(SEC_OID_SHA1);
    if (oidData == NULL) {
        return SECFailure;
    }
    poolp = challContent->poolp;
    challenge = PORT_ArenaZNew(poolp, CMMFChallenge);
    if (challenge == NULL) {
        return SECFailure;
    }
    algId = challenge->owf = PORT_ArenaZNew(poolp, SECAlgorithmID);
    if (algId == NULL) {
        return SECFailure;
    }
    rv = SECITEM_CopyItem(poolp, &algId->algorithm, &oidData->oid);
    if (rv != SECSuccess) {
        return SECFailure;
    }
    rv = cmmf_create_witness_and_challenge(poolp, challenge, inRandom, 
					   senderDER, inPubKey, passwdArg);
    challContent->challenges[0] = (rv == SECSuccess) ? challenge : NULL;
    challContent->numChallenges++;
    return rv ;
}

CMMFPOPODecKeyChallContent*
CMMF_CreatePOPODecKeyChallContent (void)
{
    PRArenaPool *poolp;
    CMMFPOPODecKeyChallContent *challContent;

    poolp = PORT_NewArena(CRMF_DEFAULT_ARENA_SIZE);
    if (poolp == NULL) {
        return NULL;
    }
    challContent = PORT_ArenaZNew(poolp, CMMFPOPODecKeyChallContent);
    if (challContent == NULL) {
        PORT_FreeArena(poolp, PR_FALSE);
	return NULL;
    }
    challContent->poolp = poolp;
    return challContent;
}

SECStatus
CMMF_POPODecKeyChallContentSetNextChallenge
                                    (CMMFPOPODecKeyChallContent *inDecKeyChall,
				     long                        inRandom,
				     CERTGeneralName            *inSender,
				     SECKEYPublicKey            *inPubKey,
				     void                       *passwdArg)
{
    CMMFChallenge               *curChallenge;
    PRArenaPool                 *genNamePool = NULL, *poolp;
    SECStatus                    rv;
    SECItem                     *genNameDER;
    void                        *mark;

    PORT_Assert (inDecKeyChall != NULL &&
		 inSender      != NULL &&
		 inPubKey      != NULL);

    if (inDecKeyChall == NULL || 
	inSender      == NULL || inPubKey == NULL) {
        return SECFailure;
    }
    poolp = inDecKeyChall->poolp;
    mark = PORT_ArenaMark(poolp);

    genNamePool = PORT_NewArena(CRMF_DEFAULT_ARENA_SIZE);
    genNameDER = CERT_EncodeGeneralName(inSender, NULL, genNamePool);
    if (genNameDER == NULL) {
        rv = SECFailure;
        goto loser;
    }
    if (inDecKeyChall->challenges == NULL) {
        inDecKeyChall->challenges =
	    PORT_ArenaZNewArray(poolp, CMMFChallenge*,(CMMF_MAX_CHALLENGES+1));
	inDecKeyChall->numAllocated = CMMF_MAX_CHALLENGES;
    }

    if (inDecKeyChall->numChallenges >= inDecKeyChall->numAllocated) {
        rv = SECFailure;
        goto loser;
    }

    if (inDecKeyChall->numChallenges == 0) {
        rv = cmmf_create_first_challenge(inDecKeyChall, inRandom, 
					 genNameDER, inPubKey, passwdArg);
    } else {
        curChallenge = PORT_ArenaZNew(poolp, CMMFChallenge);
	if (curChallenge == NULL) {
	    rv = SECFailure;
	    goto loser;
	}
	rv = cmmf_create_witness_and_challenge(poolp, curChallenge, inRandom, 
					       genNameDER, inPubKey, 
					       passwdArg);
	if (rv == SECSuccess) {
	    inDecKeyChall->challenges[inDecKeyChall->numChallenges] =
	        curChallenge;
	    inDecKeyChall->numChallenges++;
	}
    }
    if (rv != SECSuccess) {
        goto loser;
    }
    PORT_ArenaUnmark(poolp, mark);
    PORT_FreeArena(genNamePool, PR_FALSE);
    return SECSuccess;

 loser:
    PORT_ArenaRelease(poolp, mark);
    if (genNamePool != NULL) {
        PORT_FreeArena(genNamePool, PR_FALSE);
    }
    PORT_Assert(rv != SECSuccess);
    return rv;
}

SECStatus
CMMF_DestroyPOPODecKeyRespContent(CMMFPOPODecKeyRespContent *inDecKeyResp)
{
    PORT_Assert(inDecKeyResp != NULL);
    if (inDecKeyResp != NULL && inDecKeyResp->poolp != NULL) {
        PORT_FreeArena(inDecKeyResp->poolp, PR_FALSE);
    }
    return SECSuccess;
}

int 
CMMF_POPODecKeyRespContentGetNumResponses(CMMFPOPODecKeyRespContent *inRespCont)
{
    int numResponses = 0;

    PORT_Assert(inRespCont != NULL);
    if (inRespCont == NULL) {
        return 0;
    }

    while (inRespCont->responses[numResponses] != NULL) {
        numResponses ++;
    }
    return numResponses;
}

SECStatus
CMMF_POPODecKeyRespContentGetResponse (CMMFPOPODecKeyRespContent *inRespCont,
				       int                        inIndex,
				       long                      *inDest)
{
    PORT_Assert(inRespCont != NULL);
    
    if (inRespCont == NULL || inIndex < 0 || 
	inIndex >= CMMF_POPODecKeyRespContentGetNumResponses(inRespCont)) {
        return SECFailure;
    }
    *inDest = DER_GetInteger(inRespCont->responses[inIndex]);
    return (*inDest == -1) ? SECFailure : SECSuccess;
}
