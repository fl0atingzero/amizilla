/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/* ***** BEGIN LICENSE BLOCK *****
 * Version: NPL 1.1/GPL 2.0/LGPL 2.1
 *
 * The contents of this file are subject to the Netscape Public License
 * Version 1.1 (the "License"); you may not use this file except in
 * compliance with the License. You may obtain a copy of the License at
 * http://www.mozilla.org/NPL/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * The Original Code is mozilla.org code.
 *
 * The Initial Developer of the Original Code is 
 * Netscape Communications Corporation.
 * Portions created by the Initial Developer are Copyright (C) 1998
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *
 *
 * Alternatively, the contents of this file may be used under the terms of
 * either the GNU General Public License Version 2 or later (the "GPL"), or
 * the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
 * in which case the provisions of the GPL or the LGPL are applicable instead
 * of those above. If you wish to allow use of your version of this file only
 * under the terms of either the GPL or the LGPL, and not to allow others to
 * use your version of this file under the terms of the NPL, indicate your
 * decision by deleting the provisions above and replace them with the notice
 * and other provisions required by the GPL or the LGPL. If you do not delete
 * the provisions above, a recipient may use your version of this file under
 * the terms of any one of the NPL, the GPL or the LGPL.
 *
 * ***** END LICENSE BLOCK ***** */

#include "InsertTextTxn.h"
#include "nsIDOMCharacterData.h"
#include "nsISelection.h"
#include "EditAggregateTxn.h"

#ifdef NS_DEBUG
static PRBool gNoisy = PR_FALSE;
#endif

nsIAtom *InsertTextTxn::gInsertTextTxnName;

nsresult InsertTextTxn::ClassInit()
{
  if (!gInsertTextTxnName)
    gInsertTextTxnName = NS_NewAtom("NS_InsertTextTxn");
  return NS_OK;
}

nsresult InsertTextTxn::ClassShutdown()
{
  NS_IF_RELEASE(gInsertTextTxnName);
  return NS_OK;
}

InsertTextTxn::InsertTextTxn()
  : EditTxn()
{
}

InsertTextTxn::~InsertTextTxn()
{
}

NS_IMETHODIMP InsertTextTxn::Init(nsIDOMCharacterData *aElement,
                                  PRUint32             aOffset,
                                  const nsAString     &aStringToInsert,
                                  nsIEditor           *aEditor)
{
#if 0
      nsAutoString text;
      aElement->GetData(text);
      printf("InsertTextTxn: Offset to insert at = %d. Text of the node to insert into:\n", aOffset);
      wprintf(text.get());
      printf("\n");
#endif

  NS_ASSERTION(aElement && aEditor, "bad args");
  if (!aElement || !aEditor) return NS_ERROR_NULL_POINTER;

  mElement = do_QueryInterface(aElement);
  mOffset = aOffset;
  mStringToInsert = aStringToInsert;
  mEditor = aEditor;
  return NS_OK;
}

NS_IMETHODIMP InsertTextTxn::DoTransaction(void)
{
#ifdef NS_DEBUG
  if (gNoisy) { printf("Do Insert Text element = %p\n", mElement.get()); }
#endif

  NS_ASSERTION(mElement && mEditor, "bad state");
  if (!mElement || !mEditor) { return NS_ERROR_NOT_INITIALIZED; }

  nsresult result = mElement->InsertData(mOffset, mStringToInsert);
  if (NS_FAILED(result)) return result;

  // only set selection to insertion point if editor gives permission
  PRBool bAdjustSelection;
  mEditor->ShouldTxnSetSelection(&bAdjustSelection);
  if (bAdjustSelection)
  {
    nsCOMPtr<nsISelection> selection;
    result = mEditor->GetSelection(getter_AddRefs(selection));
    if (NS_FAILED(result)) return result;
    if (!selection) return NS_ERROR_NULL_POINTER;
    result = selection->Collapse(mElement, mOffset+mStringToInsert.Length());
    NS_ASSERTION((NS_SUCCEEDED(result)), "selection could not be collapsed after insert.");
  }
  else
  {
    // do nothing - dom range gravity will adjust selection
  }

  return result;
}

NS_IMETHODIMP InsertTextTxn::UndoTransaction(void)
{
#ifdef NS_DEBUG
  if (gNoisy) { printf("Undo Insert Text element = %p\n", mElement.get()); }
#endif

  NS_ASSERTION(mElement && mEditor, "bad state");
  if (!mElement || !mEditor) { return NS_ERROR_NOT_INITIALIZED; }

  PRUint32 length = mStringToInsert.Length();
  return mElement->DeleteData(mOffset, length);
}

NS_IMETHODIMP InsertTextTxn::Merge(nsITransaction *aTransaction, PRBool *aDidMerge)
{
  // set out param default value
  if (aDidMerge)
    *aDidMerge = PR_FALSE;
  nsresult result = NS_OK;
  if (aDidMerge && aTransaction)
  {
    // if aTransaction is a InsertTextTxn, and if the selection hasn't changed, 
    // then absorb it
    InsertTextTxn *otherInsTxn = nsnull;
    aTransaction->QueryInterface(InsertTextTxn::GetCID(), (void **)&otherInsTxn);
    if (otherInsTxn)
    {
      if (IsSequentialInsert(otherInsTxn))
      {
        nsAutoString otherData;
        otherInsTxn->GetData(otherData);
        mStringToInsert += otherData;
        *aDidMerge = PR_TRUE;
#ifdef NS_DEBUG
        if (gNoisy) { printf("InsertTextTxn assimilated %p\n", aTransaction); }
#endif
      }
      NS_RELEASE(otherInsTxn);
    }
    else
    { // the next InsertTextTxn might be inside an aggregate that we have special knowledge of
      EditAggregateTxn *otherTxn = nsnull;
      aTransaction->QueryInterface(EditAggregateTxn::GetCID(), (void **)&otherTxn);
      if (otherTxn)
      {
        nsCOMPtr<nsIAtom> txnName;
        otherTxn->GetName(getter_AddRefs(txnName));
        if (txnName && txnName.get()==gInsertTextTxnName)
        { // yep, it's one of ours.  By definition, it must contain only
          // another aggregate with a single child,
          // or a single InsertTextTxn
          EditTxn * childTxn;
          otherTxn->GetTxnAt(0, (&childTxn));
          if (childTxn)
          {
            InsertTextTxn * otherInsertTxn = nsnull;
            result = childTxn->QueryInterface(InsertTextTxn::GetCID(), (void**)&otherInsertTxn);
            if (NS_SUCCEEDED(result))
            {
              if (otherInsertTxn)
              {
                if (IsSequentialInsert(otherInsertTxn))
	              {
	                nsAutoString otherData;
	                otherInsertTxn->GetData(otherData);
	                mStringToInsert += otherData;
	                *aDidMerge = PR_TRUE;
#ifdef NS_DEBUG
	                if (gNoisy) { printf("InsertTextTxn assimilated %p\n", aTransaction); }
#endif
	              }
	              NS_RELEASE(otherInsertTxn);
	            }
            }
            
            NS_RELEASE(childTxn);
          }
        }
        NS_RELEASE(otherTxn);
      }
    }
  }
  return result;
}

NS_IMETHODIMP InsertTextTxn::GetTxnDescription(nsAString& aString)
{
  aString.Assign(NS_LITERAL_STRING("InsertTextTxn: "));
  aString += mStringToInsert;
  return NS_OK;
}

/* ============= nsISupports implementation ====================== */

NS_IMETHODIMP
InsertTextTxn::QueryInterface(REFNSIID aIID, void** aInstancePtr)
{
  if (!aInstancePtr) {
    return NS_ERROR_NULL_POINTER;
  }
  if (aIID.Equals(InsertTextTxn::GetCID())) {
    *aInstancePtr = (void*)(InsertTextTxn*)this;
    NS_ADDREF_THIS();
    return NS_OK;
  }
  return (EditTxn::QueryInterface(aIID, aInstancePtr));
}

/* ============ protected methods ================== */

NS_IMETHODIMP InsertTextTxn::GetData(nsString& aResult)
{
  aResult = mStringToInsert;
  return NS_OK;
}

PRBool InsertTextTxn::IsSequentialInsert(InsertTextTxn *aOtherTxn)
{
  NS_ASSERTION(aOtherTxn, "null param");
  if (aOtherTxn && aOtherTxn->mElement == mElement)
  {
    // here, we need to compare offsets.
    PRInt32 length = mStringToInsert.Length();
    if (aOtherTxn->mOffset == (mOffset + length))
      return PR_TRUE;
  }
  return PR_FALSE;
}
