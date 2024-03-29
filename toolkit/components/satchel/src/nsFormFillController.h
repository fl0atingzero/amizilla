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
 * The Original Code is Mozilla Communicator client code.
 *
 * The Initial Developer of the Original Code is 
 * Netscape Communications Corporation.
 * Portions created by the Initial Developer are Copyright (C) 1998
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *   Joe Hewitt <hewitt@netscape.com> (Original Author)
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

#ifndef __nsFormFillController__
#define __nsFormFillController__

#include "nsIFormFillController.h"
#include "nsIAutoCompleteInput.h"
#include "nsIAutoCompleteSearch.h"
#include "nsIAutoCompleteController.h"
#include "nsIAutoCompletePopup.h"
#include "nsIDOMFocusListener.h"
#include "nsIDOMKeyListener.h"
#include "nsIDOMFormListener.h"
#include "nsCOMPtr.h"
#include "nsISupportsArray.h"
#include "nsIDocShell.h"
#include "nsIDOMWindow.h"
#include "nsIDOMHTMLInputElement.h"
#include "nsFormHistory.h"

class nsFormFillController : public nsIFormFillController,
                             public nsIAutoCompleteInput,
                             public nsIAutoCompleteSearch,
                             public nsIDOMFocusListener,
                             public nsIDOMKeyListener,
                             public nsIDOMFormListener
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIFORMFILLCONTROLLER
  NS_DECL_NSIAUTOCOMPLETESEARCH
  NS_DECL_NSIAUTOCOMPLETEINPUT

  // nsIDOMEventListener
  NS_IMETHOD HandleEvent(nsIDOMEvent* aEvent);

  // nsIDOMFocusListener
  NS_IMETHOD Focus(nsIDOMEvent* aEvent);
  NS_IMETHOD Blur(nsIDOMEvent* aEvent);

  // nsIDOMKeyListener
  NS_IMETHOD KeyDown(nsIDOMEvent* aKeyEvent);
  NS_IMETHOD KeyUp(nsIDOMEvent* aKeyEvent);
  NS_IMETHOD KeyPress(nsIDOMEvent* aKeyEvent);

  // nsIDOMFormListener
  NS_IMETHOD Submit(nsIDOMEvent* aEvent);
  NS_IMETHOD Reset(nsIDOMEvent* aEvent);
  NS_IMETHOD Change(nsIDOMEvent* aEvent);
  NS_IMETHOD Select(nsIDOMEvent* aEvent);
  NS_IMETHOD Input(nsIDOMEvent* aEvent);

  nsFormFillController();
  virtual ~nsFormFillController();

protected:
  void AddFocusListener(nsIDOMWindow *aWindow);
  void RemoveFocusListener(nsIDOMWindow *aWindow);
  
  void AddKeyListener(nsIDOMHTMLInputElement *aInput);
  void RemoveKeyListener();
  
  void StartControllingInput(nsIDOMHTMLInputElement *aInput);
  void StopControllingInput();
  
  PRBool RowMatch(nsFormHistory *aHistory, PRUint32 aIndex, const nsAString &aInputName, const nsAString &aInputValue);
  
  inline nsIDocShell *GetDocShellForInput(nsIDOMHTMLInputElement *aInput);
  inline nsIDOMWindow *GetWindowForDocShell(nsIDocShell *aDocShell);
  inline PRInt32 GetIndexOfDocShell(nsIDocShell *aDocShell);

  // members //////////////////////////////////////////

  nsCOMPtr<nsIAutoCompleteController> mController;
  nsCOMPtr<nsIDOMHTMLInputElement> mFocusedInput;
  nsCOMPtr<nsIAutoCompletePopup> mFocusedPopup;

  nsCOMPtr<nsISupportsArray> mDocShells;
  nsCOMPtr<nsISupportsArray> mPopups;
  
  PRUint32 mTimeout;
  PRUint32 mMinResultsForPopup;
  PRUint32 mMaxRows;
  PRPackedBool mDisableAutoComplete; 
  PRPackedBool mCompleteDefaultIndex;
  PRPackedBool mForceComplete;
  PRPackedBool mSuppressOnInput;
};

#endif // __nsFormFillController__
