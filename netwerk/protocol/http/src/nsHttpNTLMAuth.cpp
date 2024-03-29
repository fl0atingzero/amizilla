/* ***** BEGIN LICENSE BLOCK *****
 * Version: MPL 1.1/GPL 2.0/LGPL 2.1
 *
 * The contents of this file are subject to the Mozilla Public License Version
 * 1.1 (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 * http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * The Original Code is Mozilla.
 *
 * The Initial Developer of the Original Code is
 * Netscape Communications Corporation.
 * Portions created by the Initial Developer are Copyright (C) 2003
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *   Darin Fisher <darin@meer.net>
 *
 * Alternatively, the contents of this file may be used under the terms of
 * either the GNU General Public License Version 2 or later (the "GPL"), or
 * the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
 * in which case the provisions of the GPL or the LGPL are applicable instead
 * of those above. If you wish to allow use of your version of this file only
 * under the terms of either the GPL or the LGPL, and not to allow others to
 * use your version of this file under the terms of the MPL, indicate your
 * decision by deleting the provisions above and replace them with the notice
 * and other provisions required by the GPL or the LGPL. If you do not delete
 * the provisions above, a recipient may use your version of this file under
 * the terms of any one of the MPL, the GPL or the LGPL.
 *
 * ***** END LICENSE BLOCK ***** */

#include <stdlib.h>
#include "nsHttp.h"
#include "nsHttpNTLMAuth.h"
#include "nsIComponentManager.h"
#include "nsIAuthModule.h"
#include "nsCOMPtr.h"
#include "plbase64.h"

//-----------------------------------------------------------------------------

NS_IMPL_ISUPPORTS1(nsHttpNTLMAuth, nsIHttpAuthenticator)

NS_IMETHODIMP
nsHttpNTLMAuth::ChallengeReceived(nsIHttpChannel *channel,
                                  const char     *challenge,
                                  PRBool          isProxyAuth,
                                  nsISupports   **sessionState,
                                  nsISupports   **continuationState,
                                  PRBool         *identityInvalid)
{
    LOG(("nsHttpNTLMAuth::ChallengeReceived\n"));

    // NOTE: we don't define any session state

    *identityInvalid = PR_FALSE;
    // only request new identity if challenge is exactly "NTLM"
    if (PL_strcasecmp(challenge, "NTLM") == 0) {
        nsCOMPtr<nsIAuthModule> module =
                do_CreateInstance(NS_AUTH_MODULE_CONTRACTID_PREFIX "ntlm");
        // if this fails, then it means that we cannot do NTLM auth.
        if (!module)
            return NS_ERROR_UNEXPECTED;

        // non-null continuation state implies that we failed to authenticate.
        // blow away the old authentication state, and use the new one.
        NS_IF_RELEASE(*continuationState);

        NS_ADDREF(*continuationState = module);

        // prompt user for domain, username, and password...
        *identityInvalid = PR_TRUE;
    }
    return NS_OK;
}

NS_IMETHODIMP
nsHttpNTLMAuth::GenerateCredentials(nsIHttpChannel  *httpChannel,
                                    const char      *challenge,
                                    PRBool           isProxyAuth,
                                    const PRUnichar *domain,
                                    const PRUnichar *user,
                                    const PRUnichar *pass,
                                    nsISupports    **sessionState,
                                    nsISupports    **continuationState,
                                    char           **creds)

{
    LOG(("nsHttpNTLMAuth::GenerateCredentials\n"));

    *creds = nsnull;

    nsresult rv;
    nsCOMPtr<nsIAuthModule> module = do_QueryInterface(*continuationState, &rv);
    NS_ENSURE_SUCCESS(rv, rv);

    void *inBuf, *outBuf;
    PRUint32 inBufLen, outBufLen;

    // initial challenge
    if (PL_strcasecmp(challenge, "NTLM") == 0) {
        // initialize auth module
        rv = module->Init(domain, user, pass);
        if (NS_FAILED(rv))
            return rv;

        inBufLen = 0;
        inBuf = nsnull;
    }
    else {
        // decode challenge; skip past "NTLM " to the start of the base64
        // encoded data.
        int len = strlen(challenge);
        if (len < 6)
            return NS_ERROR_UNEXPECTED; // bogus challenge
        challenge += 5;
        len -= 5;

        // decode into the input secbuffer
        inBufLen = (len * 3)/4;      // sufficient size (see plbase64.h)
        inBuf = nsMemory::Alloc(inBufLen);
        if (!inBuf)
            return NS_ERROR_OUT_OF_MEMORY;

        if (PL_Base64Decode(challenge, len, (char *) inBuf) == nsnull) {
            nsMemory::Free(inBuf);
            return NS_ERROR_UNEXPECTED; // improper base64 encoding
        }
    }

    rv = module->GetNextToken(inBuf, inBufLen, &outBuf, &outBufLen);
    if (NS_SUCCEEDED(rv)) {
        // base64 encode data in output buffer and prepend "NTLM "
        int credsLen = 5 + ((outBufLen + 2)/3)*4;
        *creds = (char *) nsMemory::Alloc(credsLen + 1);
        if (!*creds)
            rv = NS_ERROR_OUT_OF_MEMORY;
        else {
            memcpy(*creds, "NTLM ", 5);
            PL_Base64Encode((char *) outBuf, outBufLen, *creds + 5);
            (*creds)[credsLen] = '\0'; // null terminate
        }
        // OK, we are done with |outBuf|
        nsMemory::Free(outBuf);
    }

    if (inBuf)
        nsMemory::Free(inBuf);

    return rv;
}

NS_IMETHODIMP
nsHttpNTLMAuth::GetAuthFlags(PRUint32 *flags)
{
    *flags = CONNECTION_BASED | IDENTITY_INCLUDES_DOMAIN;
    return NS_OK;
}
