/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM nsIAccessibilityService.idl
 */

#ifndef __gen_nsIAccessibilityService_h__
#define __gen_nsIAccessibilityService_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

#ifndef __gen_domstubs_h__
#include "domstubs.h"
#endif

#ifndef __gen_nsIAtom_h__
#include "nsIAtom.h"
#endif

#ifndef __gen_domstubs_h__
#include "domstubs.h"
#endif

#ifndef __gen_nsIAccessible_h__
#include "nsIAccessible.h"
#endif

#ifndef __gen_nsIAccessibleCaret_h__
#include "nsIAccessibleCaret.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif
class nsIWeakReference; /* forward declaration */

class nsIAccessibleEventListener; /* forward declaration */

class nsIDocument; /* forward declaration */

class nsIPresShell; /* forward declaration */

class nsIDOMWindow; /* forward declaration */

class nsIAccessNode; /* forward declaration */

class nsObjectFrame; /* forward declaration */


/* starting interface:    nsIAccessibilityService */
#define NS_IACCESSIBILITYSERVICE_IID_STR "68d9720a-0984-42b6-a3f5-8237ed925727"

#define NS_IACCESSIBILITYSERVICE_IID \
  {0x68d9720a, 0x0984, 0x42b6, \
    { 0xa3, 0xf5, 0x82, 0x37, 0xed, 0x92, 0x57, 0x27 }}

class NS_NO_VTABLE nsIAccessibilityService : public nsISupports {
 public: 

  NS_DEFINE_STATIC_IID_ACCESSOR(NS_IACCESSIBILITYSERVICE_IID)

  /* nsIAccessible createOuterDocAccessible (in nsIDOMNode aNode); */
  NS_IMETHOD CreateOuterDocAccessible(nsIDOMNode *aNode, nsIAccessible **_retval) = 0;

  /* nsIAccessible createRootAccessible (in nsIPresShell aShell, in nsIDocument aDocument); */
  NS_IMETHOD CreateRootAccessible(nsIPresShell *aShell, nsIDocument *aDocument, nsIAccessible **_retval) = 0;

  /* nsIAccessibleCaret createCaretAccessible (in nsIDOMNode aNode, in nsIAccessible aRootAccessible); */
  NS_IMETHOD CreateCaretAccessible(nsIDOMNode *aNode, nsIAccessible *aRootAccessible, nsIAccessibleCaret **_retval) = 0;

  /* nsIAccessible createHTML4ButtonAccessible (in nsISupports aFrame); */
  NS_IMETHOD CreateHTML4ButtonAccessible(nsISupports *aFrame, nsIAccessible **_retval) = 0;

  /* nsIAccessible createHTMLAreaAccessible (in nsIWeakReference aPresShell, in nsIDOMNode aDOMNode, in nsIAccessible aAccParent); */
  NS_IMETHOD CreateHTMLAreaAccessible(nsIWeakReference *aPresShell, nsIDOMNode *aDOMNode, nsIAccessible *aAccParent, nsIAccessible **_retval) = 0;

  /* nsIAccessible createHTMLBlockAccessible (in nsISupports aFrame); */
  NS_IMETHOD CreateHTMLBlockAccessible(nsISupports *aFrame, nsIAccessible **_retval) = 0;

  /* nsIAccessible createHTMLButtonAccessible (in nsISupports aFrame); */
  NS_IMETHOD CreateHTMLButtonAccessible(nsISupports *aFrame, nsIAccessible **_retval) = 0;

  /* nsIAccessible createHTMLButtonAccessibleXBL (in nsIDOMNode aNode); */
  NS_IMETHOD CreateHTMLButtonAccessibleXBL(nsIDOMNode *aNode, nsIAccessible **_retval) = 0;

  /* nsIAccessible createHTMLCheckboxAccessible (in nsISupports aFrame); */
  NS_IMETHOD CreateHTMLCheckboxAccessible(nsISupports *aFrame, nsIAccessible **_retval) = 0;

  /* nsIAccessible createHTMLCheckboxAccessibleXBL (in nsIDOMNode aNode); */
  NS_IMETHOD CreateHTMLCheckboxAccessibleXBL(nsIDOMNode *aNode, nsIAccessible **_retval) = 0;

  /* nsIAccessible createHTMLComboboxAccessible (in nsIDOMNode aNode, in nsISupports aPresShell); */
  NS_IMETHOD CreateHTMLComboboxAccessible(nsIDOMNode *aNode, nsISupports *aPresShell, nsIAccessible **_retval) = 0;

  /* nsIAccessible createHTMLGroupboxAccessible (in nsISupports aFrame); */
  NS_IMETHOD CreateHTMLGroupboxAccessible(nsISupports *aFrame, nsIAccessible **_retval) = 0;

  /* nsIAccessible createHTMLHRAccessible (in nsISupports aFrame); */
  NS_IMETHOD CreateHTMLHRAccessible(nsISupports *aFrame, nsIAccessible **_retval) = 0;

  /* nsIAccessible createHTMLImageAccessible (in nsISupports aFrame); */
  NS_IMETHOD CreateHTMLImageAccessible(nsISupports *aFrame, nsIAccessible **_retval) = 0;

  /* nsIAccessible createHTMLLabelAccessible (in nsISupports aFrame); */
  NS_IMETHOD CreateHTMLLabelAccessible(nsISupports *aFrame, nsIAccessible **_retval) = 0;

  /* nsIAccessible createHTMLListboxAccessible (in nsIDOMNode aNode, in nsISupports aPresShell); */
  NS_IMETHOD CreateHTMLListboxAccessible(nsIDOMNode *aNode, nsISupports *aPresShell, nsIAccessible **_retval) = 0;

  /* nsIAccessible createHTMLObjectFrameAccessible (in nsObjectFrame aFrame); */
  NS_IMETHOD CreateHTMLObjectFrameAccessible(nsObjectFrame *aFrame, nsIAccessible **_retval) = 0;

  /* nsIAccessible createHTMLRadioButtonAccessible (in nsISupports aFrame); */
  NS_IMETHOD CreateHTMLRadioButtonAccessible(nsISupports *aFrame, nsIAccessible **_retval) = 0;

  /* nsIAccessible createHTMLRadioButtonAccessibleXBL (in nsIDOMNode aNode); */
  NS_IMETHOD CreateHTMLRadioButtonAccessibleXBL(nsIDOMNode *aNode, nsIAccessible **_retval) = 0;

  /* nsIAccessible createHTMLSelectOptionAccessible (in nsIDOMNode aNode, in nsIAccessible aAccParent, in nsISupports aPresShell); */
  NS_IMETHOD CreateHTMLSelectOptionAccessible(nsIDOMNode *aNode, nsIAccessible *aAccParent, nsISupports *aPresShell, nsIAccessible **_retval) = 0;

  /* nsIAccessible createHTMLTableAccessible (in nsISupports aFrame); */
  NS_IMETHOD CreateHTMLTableAccessible(nsISupports *aFrame, nsIAccessible **_retval) = 0;

  /* nsIAccessible createHTMLTableCellAccessible (in nsISupports aFrame); */
  NS_IMETHOD CreateHTMLTableCellAccessible(nsISupports *aFrame, nsIAccessible **_retval) = 0;

  /* nsIAccessible createHTMLTableCaptionAccessible (in nsIDOMNode aDOMNode); */
  NS_IMETHOD CreateHTMLTableCaptionAccessible(nsIDOMNode *aDOMNode, nsIAccessible **_retval) = 0;

  /* nsIAccessible createHTMLTableHeadAccessible (in nsIDOMNode aDOMNode); */
  NS_IMETHOD CreateHTMLTableHeadAccessible(nsIDOMNode *aDOMNode, nsIAccessible **_retval) = 0;

  /* nsIAccessible createHTMLTextAccessible (in nsISupports aFrame); */
  NS_IMETHOD CreateHTMLTextAccessible(nsISupports *aFrame, nsIAccessible **_retval) = 0;

  /* nsIAccessible createHTMLTextFieldAccessible (in nsISupports aFrame); */
  NS_IMETHOD CreateHTMLTextFieldAccessible(nsISupports *aFrame, nsIAccessible **_retval) = 0;

  /* nsIAccessible createXULButtonAccessible (in nsIDOMNode aNode); */
  NS_IMETHOD CreateXULButtonAccessible(nsIDOMNode *aNode, nsIAccessible **_retval) = 0;

  /* nsIAccessible createXULCheckboxAccessible (in nsIDOMNode aNode); */
  NS_IMETHOD CreateXULCheckboxAccessible(nsIDOMNode *aNode, nsIAccessible **_retval) = 0;

  /* nsIAccessible createXULColorPickerAccessible (in nsIDOMNode aNode); */
  NS_IMETHOD CreateXULColorPickerAccessible(nsIDOMNode *aNode, nsIAccessible **_retval) = 0;

  /* nsIAccessible createXULColorPickerTileAccessible (in nsIDOMNode aNode); */
  NS_IMETHOD CreateXULColorPickerTileAccessible(nsIDOMNode *aNode, nsIAccessible **_retval) = 0;

  /* nsIAccessible createXULComboboxAccessible (in nsIDOMNode aNode); */
  NS_IMETHOD CreateXULComboboxAccessible(nsIDOMNode *aNode, nsIAccessible **_retval) = 0;

  /* nsIAccessible createXULDropmarkerAccessible (in nsIDOMNode aNode); */
  NS_IMETHOD CreateXULDropmarkerAccessible(nsIDOMNode *aNode, nsIAccessible **_retval) = 0;

  /* nsIAccessible createXULGroupboxAccessible (in nsIDOMNode aNode); */
  NS_IMETHOD CreateXULGroupboxAccessible(nsIDOMNode *aNode, nsIAccessible **_retval) = 0;

  /* nsIAccessible createXULImageAccessible (in nsIDOMNode aNode); */
  NS_IMETHOD CreateXULImageAccessible(nsIDOMNode *aNode, nsIAccessible **_retval) = 0;

  /* nsIAccessible createXULListboxAccessible (in nsIDOMNode aNode); */
  NS_IMETHOD CreateXULListboxAccessible(nsIDOMNode *aNode, nsIAccessible **_retval) = 0;

  /* nsIAccessible createXULListitemAccessible (in nsIDOMNode aNode); */
  NS_IMETHOD CreateXULListitemAccessible(nsIDOMNode *aNode, nsIAccessible **_retval) = 0;

  /* nsIAccessible createXULMenubarAccessible (in nsIDOMNode aNode); */
  NS_IMETHOD CreateXULMenubarAccessible(nsIDOMNode *aNode, nsIAccessible **_retval) = 0;

  /* nsIAccessible createXULMenuitemAccessible (in nsIDOMNode aNode); */
  NS_IMETHOD CreateXULMenuitemAccessible(nsIDOMNode *aNode, nsIAccessible **_retval) = 0;

  /* nsIAccessible createXULMenupopupAccessible (in nsIDOMNode aNode); */
  NS_IMETHOD CreateXULMenupopupAccessible(nsIDOMNode *aNode, nsIAccessible **_retval) = 0;

  /* nsIAccessible createXULMenuSeparatorAccessible (in nsIDOMNode aNode); */
  NS_IMETHOD CreateXULMenuSeparatorAccessible(nsIDOMNode *aNode, nsIAccessible **_retval) = 0;

  /* nsIAccessible createXULProgressMeterAccessible (in nsIDOMNode aNode); */
  NS_IMETHOD CreateXULProgressMeterAccessible(nsIDOMNode *aNode, nsIAccessible **_retval) = 0;

  /* nsIAccessible createXULStatusBarAccessible (in nsIDOMNode aNode); */
  NS_IMETHOD CreateXULStatusBarAccessible(nsIDOMNode *aNode, nsIAccessible **_retval) = 0;

  /* nsIAccessible createXULRadioButtonAccessible (in nsIDOMNode aNode); */
  NS_IMETHOD CreateXULRadioButtonAccessible(nsIDOMNode *aNode, nsIAccessible **_retval) = 0;

  /* nsIAccessible createXULRadioGroupAccessible (in nsIDOMNode aNode); */
  NS_IMETHOD CreateXULRadioGroupAccessible(nsIDOMNode *aNode, nsIAccessible **_retval) = 0;

  /* nsIAccessible createXULSelectOptionAccessible (in nsIDOMNode aNode); */
  NS_IMETHOD CreateXULSelectOptionAccessible(nsIDOMNode *aNode, nsIAccessible **_retval) = 0;

  /* nsIAccessible createXULSelectListAccessible (in nsIDOMNode aNode); */
  NS_IMETHOD CreateXULSelectListAccessible(nsIDOMNode *aNode, nsIAccessible **_retval) = 0;

  /* nsIAccessible createXULTabAccessible (in nsIDOMNode aNode); */
  NS_IMETHOD CreateXULTabAccessible(nsIDOMNode *aNode, nsIAccessible **_retval) = 0;

  /* nsIAccessible createXULTabBoxAccessible (in nsIDOMNode aNode); */
  NS_IMETHOD CreateXULTabBoxAccessible(nsIDOMNode *aNode, nsIAccessible **_retval) = 0;

  /* nsIAccessible createXULTabPanelsAccessible (in nsIDOMNode aNode); */
  NS_IMETHOD CreateXULTabPanelsAccessible(nsIDOMNode *aNode, nsIAccessible **_retval) = 0;

  /* nsIAccessible createXULTabsAccessible (in nsIDOMNode aNode); */
  NS_IMETHOD CreateXULTabsAccessible(nsIDOMNode *aNode, nsIAccessible **_retval) = 0;

  /* nsIAccessible createXULTextAccessible (in nsIDOMNode aNode); */
  NS_IMETHOD CreateXULTextAccessible(nsIDOMNode *aNode, nsIAccessible **_retval) = 0;

  /* nsIAccessible createXULTextBoxAccessible (in nsIDOMNode aNode); */
  NS_IMETHOD CreateXULTextBoxAccessible(nsIDOMNode *aNode, nsIAccessible **_retval) = 0;

  /* nsIAccessible createXULTreeAccessible (in nsIDOMNode aNode); */
  NS_IMETHOD CreateXULTreeAccessible(nsIDOMNode *aNode, nsIAccessible **_retval) = 0;

  /* nsIAccessible createXULTreeColumnsAccessible (in nsIDOMNode aNode); */
  NS_IMETHOD CreateXULTreeColumnsAccessible(nsIDOMNode *aNode, nsIAccessible **_retval) = 0;

  /* nsIAccessible createXULTreeColumnitemAccessible (in nsIDOMNode aNode); */
  NS_IMETHOD CreateXULTreeColumnitemAccessible(nsIDOMNode *aNode, nsIAccessible **_retval) = 0;

  /* nsIAccessible createXULToolbarAccessible (in nsIDOMNode aNode); */
  NS_IMETHOD CreateXULToolbarAccessible(nsIDOMNode *aNode, nsIAccessible **_retval) = 0;

  /* nsIAccessible createXULToolbarSeparatorAccessible (in nsIDOMNode aNode); */
  NS_IMETHOD CreateXULToolbarSeparatorAccessible(nsIDOMNode *aNode, nsIAccessible **_retval) = 0;

  /* nsIAccessible createXULTooltipAccessible (in nsIDOMNode aNode); */
  NS_IMETHOD CreateXULTooltipAccessible(nsIDOMNode *aNode, nsIAccessible **_retval) = 0;

  /* nsIAccessible getAccessibleFor (in nsIDOMNode aNode); */
  NS_IMETHOD GetAccessibleFor(nsIDOMNode *aNode, nsIAccessible **_retval) = 0;

  /* nsIAccessible getAccessibleInWindow (in nsIDOMNode aNode, in nsIDOMWindow aDOMWin); */
  NS_IMETHOD GetAccessibleInWindow(nsIDOMNode *aNode, nsIDOMWindow *aDOMWin, nsIAccessible **_retval) = 0;

  /* nsIAccessible getAccessibleInWeakShell (in nsIDOMNode aNode, in nsIWeakReference aPresShell); */
  NS_IMETHOD GetAccessibleInWeakShell(nsIDOMNode *aNode, nsIWeakReference *aPresShell, nsIAccessible **_retval) = 0;

  /* nsIAccessible getAccessibleInShell (in nsIDOMNode aNode, in nsIPresShell aPresShell); */
  NS_IMETHOD GetAccessibleInShell(nsIDOMNode *aNode, nsIPresShell *aPresShell, nsIAccessible **_retval) = 0;

  /* [noscript] nsIAccessNode getCachedAccessNode (in nsIDOMNode aNode, in nsIWeakReference aShell); */
  NS_IMETHOD GetCachedAccessNode(nsIDOMNode *aNode, nsIWeakReference *aShell, nsIAccessNode **_retval) = 0;

  /* [noscript] nsIAccessible getCachedAccessible (in nsIDOMNode aNode, in nsIWeakReference aShell); */
  NS_IMETHOD GetCachedAccessible(nsIDOMNode *aNode, nsIWeakReference *aShell, nsIAccessible **_retval) = 0;

};

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSIACCESSIBILITYSERVICE \
  NS_IMETHOD CreateOuterDocAccessible(nsIDOMNode *aNode, nsIAccessible **_retval); \
  NS_IMETHOD CreateRootAccessible(nsIPresShell *aShell, nsIDocument *aDocument, nsIAccessible **_retval); \
  NS_IMETHOD CreateCaretAccessible(nsIDOMNode *aNode, nsIAccessible *aRootAccessible, nsIAccessibleCaret **_retval); \
  NS_IMETHOD CreateHTML4ButtonAccessible(nsISupports *aFrame, nsIAccessible **_retval); \
  NS_IMETHOD CreateHTMLAreaAccessible(nsIWeakReference *aPresShell, nsIDOMNode *aDOMNode, nsIAccessible *aAccParent, nsIAccessible **_retval); \
  NS_IMETHOD CreateHTMLBlockAccessible(nsISupports *aFrame, nsIAccessible **_retval); \
  NS_IMETHOD CreateHTMLButtonAccessible(nsISupports *aFrame, nsIAccessible **_retval); \
  NS_IMETHOD CreateHTMLButtonAccessibleXBL(nsIDOMNode *aNode, nsIAccessible **_retval); \
  NS_IMETHOD CreateHTMLCheckboxAccessible(nsISupports *aFrame, nsIAccessible **_retval); \
  NS_IMETHOD CreateHTMLCheckboxAccessibleXBL(nsIDOMNode *aNode, nsIAccessible **_retval); \
  NS_IMETHOD CreateHTMLComboboxAccessible(nsIDOMNode *aNode, nsISupports *aPresShell, nsIAccessible **_retval); \
  NS_IMETHOD CreateHTMLGroupboxAccessible(nsISupports *aFrame, nsIAccessible **_retval); \
  NS_IMETHOD CreateHTMLHRAccessible(nsISupports *aFrame, nsIAccessible **_retval); \
  NS_IMETHOD CreateHTMLImageAccessible(nsISupports *aFrame, nsIAccessible **_retval); \
  NS_IMETHOD CreateHTMLLabelAccessible(nsISupports *aFrame, nsIAccessible **_retval); \
  NS_IMETHOD CreateHTMLListboxAccessible(nsIDOMNode *aNode, nsISupports *aPresShell, nsIAccessible **_retval); \
  NS_IMETHOD CreateHTMLObjectFrameAccessible(nsObjectFrame *aFrame, nsIAccessible **_retval); \
  NS_IMETHOD CreateHTMLRadioButtonAccessible(nsISupports *aFrame, nsIAccessible **_retval); \
  NS_IMETHOD CreateHTMLRadioButtonAccessibleXBL(nsIDOMNode *aNode, nsIAccessible **_retval); \
  NS_IMETHOD CreateHTMLSelectOptionAccessible(nsIDOMNode *aNode, nsIAccessible *aAccParent, nsISupports *aPresShell, nsIAccessible **_retval); \
  NS_IMETHOD CreateHTMLTableAccessible(nsISupports *aFrame, nsIAccessible **_retval); \
  NS_IMETHOD CreateHTMLTableCellAccessible(nsISupports *aFrame, nsIAccessible **_retval); \
  NS_IMETHOD CreateHTMLTableCaptionAccessible(nsIDOMNode *aDOMNode, nsIAccessible **_retval); \
  NS_IMETHOD CreateHTMLTableHeadAccessible(nsIDOMNode *aDOMNode, nsIAccessible **_retval); \
  NS_IMETHOD CreateHTMLTextAccessible(nsISupports *aFrame, nsIAccessible **_retval); \
  NS_IMETHOD CreateHTMLTextFieldAccessible(nsISupports *aFrame, nsIAccessible **_retval); \
  NS_IMETHOD CreateXULButtonAccessible(nsIDOMNode *aNode, nsIAccessible **_retval); \
  NS_IMETHOD CreateXULCheckboxAccessible(nsIDOMNode *aNode, nsIAccessible **_retval); \
  NS_IMETHOD CreateXULColorPickerAccessible(nsIDOMNode *aNode, nsIAccessible **_retval); \
  NS_IMETHOD CreateXULColorPickerTileAccessible(nsIDOMNode *aNode, nsIAccessible **_retval); \
  NS_IMETHOD CreateXULComboboxAccessible(nsIDOMNode *aNode, nsIAccessible **_retval); \
  NS_IMETHOD CreateXULDropmarkerAccessible(nsIDOMNode *aNode, nsIAccessible **_retval); \
  NS_IMETHOD CreateXULGroupboxAccessible(nsIDOMNode *aNode, nsIAccessible **_retval); \
  NS_IMETHOD CreateXULImageAccessible(nsIDOMNode *aNode, nsIAccessible **_retval); \
  NS_IMETHOD CreateXULListboxAccessible(nsIDOMNode *aNode, nsIAccessible **_retval); \
  NS_IMETHOD CreateXULListitemAccessible(nsIDOMNode *aNode, nsIAccessible **_retval); \
  NS_IMETHOD CreateXULMenubarAccessible(nsIDOMNode *aNode, nsIAccessible **_retval); \
  NS_IMETHOD CreateXULMenuitemAccessible(nsIDOMNode *aNode, nsIAccessible **_retval); \
  NS_IMETHOD CreateXULMenupopupAccessible(nsIDOMNode *aNode, nsIAccessible **_retval); \
  NS_IMETHOD CreateXULMenuSeparatorAccessible(nsIDOMNode *aNode, nsIAccessible **_retval); \
  NS_IMETHOD CreateXULProgressMeterAccessible(nsIDOMNode *aNode, nsIAccessible **_retval); \
  NS_IMETHOD CreateXULStatusBarAccessible(nsIDOMNode *aNode, nsIAccessible **_retval); \
  NS_IMETHOD CreateXULRadioButtonAccessible(nsIDOMNode *aNode, nsIAccessible **_retval); \
  NS_IMETHOD CreateXULRadioGroupAccessible(nsIDOMNode *aNode, nsIAccessible **_retval); \
  NS_IMETHOD CreateXULSelectOptionAccessible(nsIDOMNode *aNode, nsIAccessible **_retval); \
  NS_IMETHOD CreateXULSelectListAccessible(nsIDOMNode *aNode, nsIAccessible **_retval); \
  NS_IMETHOD CreateXULTabAccessible(nsIDOMNode *aNode, nsIAccessible **_retval); \
  NS_IMETHOD CreateXULTabBoxAccessible(nsIDOMNode *aNode, nsIAccessible **_retval); \
  NS_IMETHOD CreateXULTabPanelsAccessible(nsIDOMNode *aNode, nsIAccessible **_retval); \
  NS_IMETHOD CreateXULTabsAccessible(nsIDOMNode *aNode, nsIAccessible **_retval); \
  NS_IMETHOD CreateXULTextAccessible(nsIDOMNode *aNode, nsIAccessible **_retval); \
  NS_IMETHOD CreateXULTextBoxAccessible(nsIDOMNode *aNode, nsIAccessible **_retval); \
  NS_IMETHOD CreateXULTreeAccessible(nsIDOMNode *aNode, nsIAccessible **_retval); \
  NS_IMETHOD CreateXULTreeColumnsAccessible(nsIDOMNode *aNode, nsIAccessible **_retval); \
  NS_IMETHOD CreateXULTreeColumnitemAccessible(nsIDOMNode *aNode, nsIAccessible **_retval); \
  NS_IMETHOD CreateXULToolbarAccessible(nsIDOMNode *aNode, nsIAccessible **_retval); \
  NS_IMETHOD CreateXULToolbarSeparatorAccessible(nsIDOMNode *aNode, nsIAccessible **_retval); \
  NS_IMETHOD CreateXULTooltipAccessible(nsIDOMNode *aNode, nsIAccessible **_retval); \
  NS_IMETHOD GetAccessibleFor(nsIDOMNode *aNode, nsIAccessible **_retval); \
  NS_IMETHOD GetAccessibleInWindow(nsIDOMNode *aNode, nsIDOMWindow *aDOMWin, nsIAccessible **_retval); \
  NS_IMETHOD GetAccessibleInWeakShell(nsIDOMNode *aNode, nsIWeakReference *aPresShell, nsIAccessible **_retval); \
  NS_IMETHOD GetAccessibleInShell(nsIDOMNode *aNode, nsIPresShell *aPresShell, nsIAccessible **_retval); \
  NS_IMETHOD GetCachedAccessNode(nsIDOMNode *aNode, nsIWeakReference *aShell, nsIAccessNode **_retval); \
  NS_IMETHOD GetCachedAccessible(nsIDOMNode *aNode, nsIWeakReference *aShell, nsIAccessible **_retval); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSIACCESSIBILITYSERVICE(_to) \
  NS_IMETHOD CreateOuterDocAccessible(nsIDOMNode *aNode, nsIAccessible **_retval) { return _to CreateOuterDocAccessible(aNode, _retval); } \
  NS_IMETHOD CreateRootAccessible(nsIPresShell *aShell, nsIDocument *aDocument, nsIAccessible **_retval) { return _to CreateRootAccessible(aShell, aDocument, _retval); } \
  NS_IMETHOD CreateCaretAccessible(nsIDOMNode *aNode, nsIAccessible *aRootAccessible, nsIAccessibleCaret **_retval) { return _to CreateCaretAccessible(aNode, aRootAccessible, _retval); } \
  NS_IMETHOD CreateHTML4ButtonAccessible(nsISupports *aFrame, nsIAccessible **_retval) { return _to CreateHTML4ButtonAccessible(aFrame, _retval); } \
  NS_IMETHOD CreateHTMLAreaAccessible(nsIWeakReference *aPresShell, nsIDOMNode *aDOMNode, nsIAccessible *aAccParent, nsIAccessible **_retval) { return _to CreateHTMLAreaAccessible(aPresShell, aDOMNode, aAccParent, _retval); } \
  NS_IMETHOD CreateHTMLBlockAccessible(nsISupports *aFrame, nsIAccessible **_retval) { return _to CreateHTMLBlockAccessible(aFrame, _retval); } \
  NS_IMETHOD CreateHTMLButtonAccessible(nsISupports *aFrame, nsIAccessible **_retval) { return _to CreateHTMLButtonAccessible(aFrame, _retval); } \
  NS_IMETHOD CreateHTMLButtonAccessibleXBL(nsIDOMNode *aNode, nsIAccessible **_retval) { return _to CreateHTMLButtonAccessibleXBL(aNode, _retval); } \
  NS_IMETHOD CreateHTMLCheckboxAccessible(nsISupports *aFrame, nsIAccessible **_retval) { return _to CreateHTMLCheckboxAccessible(aFrame, _retval); } \
  NS_IMETHOD CreateHTMLCheckboxAccessibleXBL(nsIDOMNode *aNode, nsIAccessible **_retval) { return _to CreateHTMLCheckboxAccessibleXBL(aNode, _retval); } \
  NS_IMETHOD CreateHTMLComboboxAccessible(nsIDOMNode *aNode, nsISupports *aPresShell, nsIAccessible **_retval) { return _to CreateHTMLComboboxAccessible(aNode, aPresShell, _retval); } \
  NS_IMETHOD CreateHTMLGroupboxAccessible(nsISupports *aFrame, nsIAccessible **_retval) { return _to CreateHTMLGroupboxAccessible(aFrame, _retval); } \
  NS_IMETHOD CreateHTMLHRAccessible(nsISupports *aFrame, nsIAccessible **_retval) { return _to CreateHTMLHRAccessible(aFrame, _retval); } \
  NS_IMETHOD CreateHTMLImageAccessible(nsISupports *aFrame, nsIAccessible **_retval) { return _to CreateHTMLImageAccessible(aFrame, _retval); } \
  NS_IMETHOD CreateHTMLLabelAccessible(nsISupports *aFrame, nsIAccessible **_retval) { return _to CreateHTMLLabelAccessible(aFrame, _retval); } \
  NS_IMETHOD CreateHTMLListboxAccessible(nsIDOMNode *aNode, nsISupports *aPresShell, nsIAccessible **_retval) { return _to CreateHTMLListboxAccessible(aNode, aPresShell, _retval); } \
  NS_IMETHOD CreateHTMLObjectFrameAccessible(nsObjectFrame *aFrame, nsIAccessible **_retval) { return _to CreateHTMLObjectFrameAccessible(aFrame, _retval); } \
  NS_IMETHOD CreateHTMLRadioButtonAccessible(nsISupports *aFrame, nsIAccessible **_retval) { return _to CreateHTMLRadioButtonAccessible(aFrame, _retval); } \
  NS_IMETHOD CreateHTMLRadioButtonAccessibleXBL(nsIDOMNode *aNode, nsIAccessible **_retval) { return _to CreateHTMLRadioButtonAccessibleXBL(aNode, _retval); } \
  NS_IMETHOD CreateHTMLSelectOptionAccessible(nsIDOMNode *aNode, nsIAccessible *aAccParent, nsISupports *aPresShell, nsIAccessible **_retval) { return _to CreateHTMLSelectOptionAccessible(aNode, aAccParent, aPresShell, _retval); } \
  NS_IMETHOD CreateHTMLTableAccessible(nsISupports *aFrame, nsIAccessible **_retval) { return _to CreateHTMLTableAccessible(aFrame, _retval); } \
  NS_IMETHOD CreateHTMLTableCellAccessible(nsISupports *aFrame, nsIAccessible **_retval) { return _to CreateHTMLTableCellAccessible(aFrame, _retval); } \
  NS_IMETHOD CreateHTMLTableCaptionAccessible(nsIDOMNode *aDOMNode, nsIAccessible **_retval) { return _to CreateHTMLTableCaptionAccessible(aDOMNode, _retval); } \
  NS_IMETHOD CreateHTMLTableHeadAccessible(nsIDOMNode *aDOMNode, nsIAccessible **_retval) { return _to CreateHTMLTableHeadAccessible(aDOMNode, _retval); } \
  NS_IMETHOD CreateHTMLTextAccessible(nsISupports *aFrame, nsIAccessible **_retval) { return _to CreateHTMLTextAccessible(aFrame, _retval); } \
  NS_IMETHOD CreateHTMLTextFieldAccessible(nsISupports *aFrame, nsIAccessible **_retval) { return _to CreateHTMLTextFieldAccessible(aFrame, _retval); } \
  NS_IMETHOD CreateXULButtonAccessible(nsIDOMNode *aNode, nsIAccessible **_retval) { return _to CreateXULButtonAccessible(aNode, _retval); } \
  NS_IMETHOD CreateXULCheckboxAccessible(nsIDOMNode *aNode, nsIAccessible **_retval) { return _to CreateXULCheckboxAccessible(aNode, _retval); } \
  NS_IMETHOD CreateXULColorPickerAccessible(nsIDOMNode *aNode, nsIAccessible **_retval) { return _to CreateXULColorPickerAccessible(aNode, _retval); } \
  NS_IMETHOD CreateXULColorPickerTileAccessible(nsIDOMNode *aNode, nsIAccessible **_retval) { return _to CreateXULColorPickerTileAccessible(aNode, _retval); } \
  NS_IMETHOD CreateXULComboboxAccessible(nsIDOMNode *aNode, nsIAccessible **_retval) { return _to CreateXULComboboxAccessible(aNode, _retval); } \
  NS_IMETHOD CreateXULDropmarkerAccessible(nsIDOMNode *aNode, nsIAccessible **_retval) { return _to CreateXULDropmarkerAccessible(aNode, _retval); } \
  NS_IMETHOD CreateXULGroupboxAccessible(nsIDOMNode *aNode, nsIAccessible **_retval) { return _to CreateXULGroupboxAccessible(aNode, _retval); } \
  NS_IMETHOD CreateXULImageAccessible(nsIDOMNode *aNode, nsIAccessible **_retval) { return _to CreateXULImageAccessible(aNode, _retval); } \
  NS_IMETHOD CreateXULListboxAccessible(nsIDOMNode *aNode, nsIAccessible **_retval) { return _to CreateXULListboxAccessible(aNode, _retval); } \
  NS_IMETHOD CreateXULListitemAccessible(nsIDOMNode *aNode, nsIAccessible **_retval) { return _to CreateXULListitemAccessible(aNode, _retval); } \
  NS_IMETHOD CreateXULMenubarAccessible(nsIDOMNode *aNode, nsIAccessible **_retval) { return _to CreateXULMenubarAccessible(aNode, _retval); } \
  NS_IMETHOD CreateXULMenuitemAccessible(nsIDOMNode *aNode, nsIAccessible **_retval) { return _to CreateXULMenuitemAccessible(aNode, _retval); } \
  NS_IMETHOD CreateXULMenupopupAccessible(nsIDOMNode *aNode, nsIAccessible **_retval) { return _to CreateXULMenupopupAccessible(aNode, _retval); } \
  NS_IMETHOD CreateXULMenuSeparatorAccessible(nsIDOMNode *aNode, nsIAccessible **_retval) { return _to CreateXULMenuSeparatorAccessible(aNode, _retval); } \
  NS_IMETHOD CreateXULProgressMeterAccessible(nsIDOMNode *aNode, nsIAccessible **_retval) { return _to CreateXULProgressMeterAccessible(aNode, _retval); } \
  NS_IMETHOD CreateXULStatusBarAccessible(nsIDOMNode *aNode, nsIAccessible **_retval) { return _to CreateXULStatusBarAccessible(aNode, _retval); } \
  NS_IMETHOD CreateXULRadioButtonAccessible(nsIDOMNode *aNode, nsIAccessible **_retval) { return _to CreateXULRadioButtonAccessible(aNode, _retval); } \
  NS_IMETHOD CreateXULRadioGroupAccessible(nsIDOMNode *aNode, nsIAccessible **_retval) { return _to CreateXULRadioGroupAccessible(aNode, _retval); } \
  NS_IMETHOD CreateXULSelectOptionAccessible(nsIDOMNode *aNode, nsIAccessible **_retval) { return _to CreateXULSelectOptionAccessible(aNode, _retval); } \
  NS_IMETHOD CreateXULSelectListAccessible(nsIDOMNode *aNode, nsIAccessible **_retval) { return _to CreateXULSelectListAccessible(aNode, _retval); } \
  NS_IMETHOD CreateXULTabAccessible(nsIDOMNode *aNode, nsIAccessible **_retval) { return _to CreateXULTabAccessible(aNode, _retval); } \
  NS_IMETHOD CreateXULTabBoxAccessible(nsIDOMNode *aNode, nsIAccessible **_retval) { return _to CreateXULTabBoxAccessible(aNode, _retval); } \
  NS_IMETHOD CreateXULTabPanelsAccessible(nsIDOMNode *aNode, nsIAccessible **_retval) { return _to CreateXULTabPanelsAccessible(aNode, _retval); } \
  NS_IMETHOD CreateXULTabsAccessible(nsIDOMNode *aNode, nsIAccessible **_retval) { return _to CreateXULTabsAccessible(aNode, _retval); } \
  NS_IMETHOD CreateXULTextAccessible(nsIDOMNode *aNode, nsIAccessible **_retval) { return _to CreateXULTextAccessible(aNode, _retval); } \
  NS_IMETHOD CreateXULTextBoxAccessible(nsIDOMNode *aNode, nsIAccessible **_retval) { return _to CreateXULTextBoxAccessible(aNode, _retval); } \
  NS_IMETHOD CreateXULTreeAccessible(nsIDOMNode *aNode, nsIAccessible **_retval) { return _to CreateXULTreeAccessible(aNode, _retval); } \
  NS_IMETHOD CreateXULTreeColumnsAccessible(nsIDOMNode *aNode, nsIAccessible **_retval) { return _to CreateXULTreeColumnsAccessible(aNode, _retval); } \
  NS_IMETHOD CreateXULTreeColumnitemAccessible(nsIDOMNode *aNode, nsIAccessible **_retval) { return _to CreateXULTreeColumnitemAccessible(aNode, _retval); } \
  NS_IMETHOD CreateXULToolbarAccessible(nsIDOMNode *aNode, nsIAccessible **_retval) { return _to CreateXULToolbarAccessible(aNode, _retval); } \
  NS_IMETHOD CreateXULToolbarSeparatorAccessible(nsIDOMNode *aNode, nsIAccessible **_retval) { return _to CreateXULToolbarSeparatorAccessible(aNode, _retval); } \
  NS_IMETHOD CreateXULTooltipAccessible(nsIDOMNode *aNode, nsIAccessible **_retval) { return _to CreateXULTooltipAccessible(aNode, _retval); } \
  NS_IMETHOD GetAccessibleFor(nsIDOMNode *aNode, nsIAccessible **_retval) { return _to GetAccessibleFor(aNode, _retval); } \
  NS_IMETHOD GetAccessibleInWindow(nsIDOMNode *aNode, nsIDOMWindow *aDOMWin, nsIAccessible **_retval) { return _to GetAccessibleInWindow(aNode, aDOMWin, _retval); } \
  NS_IMETHOD GetAccessibleInWeakShell(nsIDOMNode *aNode, nsIWeakReference *aPresShell, nsIAccessible **_retval) { return _to GetAccessibleInWeakShell(aNode, aPresShell, _retval); } \
  NS_IMETHOD GetAccessibleInShell(nsIDOMNode *aNode, nsIPresShell *aPresShell, nsIAccessible **_retval) { return _to GetAccessibleInShell(aNode, aPresShell, _retval); } \
  NS_IMETHOD GetCachedAccessNode(nsIDOMNode *aNode, nsIWeakReference *aShell, nsIAccessNode **_retval) { return _to GetCachedAccessNode(aNode, aShell, _retval); } \
  NS_IMETHOD GetCachedAccessible(nsIDOMNode *aNode, nsIWeakReference *aShell, nsIAccessible **_retval) { return _to GetCachedAccessible(aNode, aShell, _retval); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSIACCESSIBILITYSERVICE(_to) \
  NS_IMETHOD CreateOuterDocAccessible(nsIDOMNode *aNode, nsIAccessible **_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->CreateOuterDocAccessible(aNode, _retval); } \
  NS_IMETHOD CreateRootAccessible(nsIPresShell *aShell, nsIDocument *aDocument, nsIAccessible **_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->CreateRootAccessible(aShell, aDocument, _retval); } \
  NS_IMETHOD CreateCaretAccessible(nsIDOMNode *aNode, nsIAccessible *aRootAccessible, nsIAccessibleCaret **_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->CreateCaretAccessible(aNode, aRootAccessible, _retval); } \
  NS_IMETHOD CreateHTML4ButtonAccessible(nsISupports *aFrame, nsIAccessible **_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->CreateHTML4ButtonAccessible(aFrame, _retval); } \
  NS_IMETHOD CreateHTMLAreaAccessible(nsIWeakReference *aPresShell, nsIDOMNode *aDOMNode, nsIAccessible *aAccParent, nsIAccessible **_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->CreateHTMLAreaAccessible(aPresShell, aDOMNode, aAccParent, _retval); } \
  NS_IMETHOD CreateHTMLBlockAccessible(nsISupports *aFrame, nsIAccessible **_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->CreateHTMLBlockAccessible(aFrame, _retval); } \
  NS_IMETHOD CreateHTMLButtonAccessible(nsISupports *aFrame, nsIAccessible **_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->CreateHTMLButtonAccessible(aFrame, _retval); } \
  NS_IMETHOD CreateHTMLButtonAccessibleXBL(nsIDOMNode *aNode, nsIAccessible **_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->CreateHTMLButtonAccessibleXBL(aNode, _retval); } \
  NS_IMETHOD CreateHTMLCheckboxAccessible(nsISupports *aFrame, nsIAccessible **_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->CreateHTMLCheckboxAccessible(aFrame, _retval); } \
  NS_IMETHOD CreateHTMLCheckboxAccessibleXBL(nsIDOMNode *aNode, nsIAccessible **_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->CreateHTMLCheckboxAccessibleXBL(aNode, _retval); } \
  NS_IMETHOD CreateHTMLComboboxAccessible(nsIDOMNode *aNode, nsISupports *aPresShell, nsIAccessible **_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->CreateHTMLComboboxAccessible(aNode, aPresShell, _retval); } \
  NS_IMETHOD CreateHTMLGroupboxAccessible(nsISupports *aFrame, nsIAccessible **_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->CreateHTMLGroupboxAccessible(aFrame, _retval); } \
  NS_IMETHOD CreateHTMLHRAccessible(nsISupports *aFrame, nsIAccessible **_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->CreateHTMLHRAccessible(aFrame, _retval); } \
  NS_IMETHOD CreateHTMLImageAccessible(nsISupports *aFrame, nsIAccessible **_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->CreateHTMLImageAccessible(aFrame, _retval); } \
  NS_IMETHOD CreateHTMLLabelAccessible(nsISupports *aFrame, nsIAccessible **_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->CreateHTMLLabelAccessible(aFrame, _retval); } \
  NS_IMETHOD CreateHTMLListboxAccessible(nsIDOMNode *aNode, nsISupports *aPresShell, nsIAccessible **_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->CreateHTMLListboxAccessible(aNode, aPresShell, _retval); } \
  NS_IMETHOD CreateHTMLObjectFrameAccessible(nsObjectFrame *aFrame, nsIAccessible **_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->CreateHTMLObjectFrameAccessible(aFrame, _retval); } \
  NS_IMETHOD CreateHTMLRadioButtonAccessible(nsISupports *aFrame, nsIAccessible **_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->CreateHTMLRadioButtonAccessible(aFrame, _retval); } \
  NS_IMETHOD CreateHTMLRadioButtonAccessibleXBL(nsIDOMNode *aNode, nsIAccessible **_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->CreateHTMLRadioButtonAccessibleXBL(aNode, _retval); } \
  NS_IMETHOD CreateHTMLSelectOptionAccessible(nsIDOMNode *aNode, nsIAccessible *aAccParent, nsISupports *aPresShell, nsIAccessible **_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->CreateHTMLSelectOptionAccessible(aNode, aAccParent, aPresShell, _retval); } \
  NS_IMETHOD CreateHTMLTableAccessible(nsISupports *aFrame, nsIAccessible **_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->CreateHTMLTableAccessible(aFrame, _retval); } \
  NS_IMETHOD CreateHTMLTableCellAccessible(nsISupports *aFrame, nsIAccessible **_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->CreateHTMLTableCellAccessible(aFrame, _retval); } \
  NS_IMETHOD CreateHTMLTableCaptionAccessible(nsIDOMNode *aDOMNode, nsIAccessible **_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->CreateHTMLTableCaptionAccessible(aDOMNode, _retval); } \
  NS_IMETHOD CreateHTMLTableHeadAccessible(nsIDOMNode *aDOMNode, nsIAccessible **_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->CreateHTMLTableHeadAccessible(aDOMNode, _retval); } \
  NS_IMETHOD CreateHTMLTextAccessible(nsISupports *aFrame, nsIAccessible **_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->CreateHTMLTextAccessible(aFrame, _retval); } \
  NS_IMETHOD CreateHTMLTextFieldAccessible(nsISupports *aFrame, nsIAccessible **_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->CreateHTMLTextFieldAccessible(aFrame, _retval); } \
  NS_IMETHOD CreateXULButtonAccessible(nsIDOMNode *aNode, nsIAccessible **_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->CreateXULButtonAccessible(aNode, _retval); } \
  NS_IMETHOD CreateXULCheckboxAccessible(nsIDOMNode *aNode, nsIAccessible **_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->CreateXULCheckboxAccessible(aNode, _retval); } \
  NS_IMETHOD CreateXULColorPickerAccessible(nsIDOMNode *aNode, nsIAccessible **_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->CreateXULColorPickerAccessible(aNode, _retval); } \
  NS_IMETHOD CreateXULColorPickerTileAccessible(nsIDOMNode *aNode, nsIAccessible **_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->CreateXULColorPickerTileAccessible(aNode, _retval); } \
  NS_IMETHOD CreateXULComboboxAccessible(nsIDOMNode *aNode, nsIAccessible **_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->CreateXULComboboxAccessible(aNode, _retval); } \
  NS_IMETHOD CreateXULDropmarkerAccessible(nsIDOMNode *aNode, nsIAccessible **_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->CreateXULDropmarkerAccessible(aNode, _retval); } \
  NS_IMETHOD CreateXULGroupboxAccessible(nsIDOMNode *aNode, nsIAccessible **_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->CreateXULGroupboxAccessible(aNode, _retval); } \
  NS_IMETHOD CreateXULImageAccessible(nsIDOMNode *aNode, nsIAccessible **_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->CreateXULImageAccessible(aNode, _retval); } \
  NS_IMETHOD CreateXULListboxAccessible(nsIDOMNode *aNode, nsIAccessible **_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->CreateXULListboxAccessible(aNode, _retval); } \
  NS_IMETHOD CreateXULListitemAccessible(nsIDOMNode *aNode, nsIAccessible **_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->CreateXULListitemAccessible(aNode, _retval); } \
  NS_IMETHOD CreateXULMenubarAccessible(nsIDOMNode *aNode, nsIAccessible **_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->CreateXULMenubarAccessible(aNode, _retval); } \
  NS_IMETHOD CreateXULMenuitemAccessible(nsIDOMNode *aNode, nsIAccessible **_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->CreateXULMenuitemAccessible(aNode, _retval); } \
  NS_IMETHOD CreateXULMenupopupAccessible(nsIDOMNode *aNode, nsIAccessible **_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->CreateXULMenupopupAccessible(aNode, _retval); } \
  NS_IMETHOD CreateXULMenuSeparatorAccessible(nsIDOMNode *aNode, nsIAccessible **_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->CreateXULMenuSeparatorAccessible(aNode, _retval); } \
  NS_IMETHOD CreateXULProgressMeterAccessible(nsIDOMNode *aNode, nsIAccessible **_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->CreateXULProgressMeterAccessible(aNode, _retval); } \
  NS_IMETHOD CreateXULStatusBarAccessible(nsIDOMNode *aNode, nsIAccessible **_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->CreateXULStatusBarAccessible(aNode, _retval); } \
  NS_IMETHOD CreateXULRadioButtonAccessible(nsIDOMNode *aNode, nsIAccessible **_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->CreateXULRadioButtonAccessible(aNode, _retval); } \
  NS_IMETHOD CreateXULRadioGroupAccessible(nsIDOMNode *aNode, nsIAccessible **_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->CreateXULRadioGroupAccessible(aNode, _retval); } \
  NS_IMETHOD CreateXULSelectOptionAccessible(nsIDOMNode *aNode, nsIAccessible **_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->CreateXULSelectOptionAccessible(aNode, _retval); } \
  NS_IMETHOD CreateXULSelectListAccessible(nsIDOMNode *aNode, nsIAccessible **_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->CreateXULSelectListAccessible(aNode, _retval); } \
  NS_IMETHOD CreateXULTabAccessible(nsIDOMNode *aNode, nsIAccessible **_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->CreateXULTabAccessible(aNode, _retval); } \
  NS_IMETHOD CreateXULTabBoxAccessible(nsIDOMNode *aNode, nsIAccessible **_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->CreateXULTabBoxAccessible(aNode, _retval); } \
  NS_IMETHOD CreateXULTabPanelsAccessible(nsIDOMNode *aNode, nsIAccessible **_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->CreateXULTabPanelsAccessible(aNode, _retval); } \
  NS_IMETHOD CreateXULTabsAccessible(nsIDOMNode *aNode, nsIAccessible **_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->CreateXULTabsAccessible(aNode, _retval); } \
  NS_IMETHOD CreateXULTextAccessible(nsIDOMNode *aNode, nsIAccessible **_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->CreateXULTextAccessible(aNode, _retval); } \
  NS_IMETHOD CreateXULTextBoxAccessible(nsIDOMNode *aNode, nsIAccessible **_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->CreateXULTextBoxAccessible(aNode, _retval); } \
  NS_IMETHOD CreateXULTreeAccessible(nsIDOMNode *aNode, nsIAccessible **_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->CreateXULTreeAccessible(aNode, _retval); } \
  NS_IMETHOD CreateXULTreeColumnsAccessible(nsIDOMNode *aNode, nsIAccessible **_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->CreateXULTreeColumnsAccessible(aNode, _retval); } \
  NS_IMETHOD CreateXULTreeColumnitemAccessible(nsIDOMNode *aNode, nsIAccessible **_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->CreateXULTreeColumnitemAccessible(aNode, _retval); } \
  NS_IMETHOD CreateXULToolbarAccessible(nsIDOMNode *aNode, nsIAccessible **_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->CreateXULToolbarAccessible(aNode, _retval); } \
  NS_IMETHOD CreateXULToolbarSeparatorAccessible(nsIDOMNode *aNode, nsIAccessible **_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->CreateXULToolbarSeparatorAccessible(aNode, _retval); } \
  NS_IMETHOD CreateXULTooltipAccessible(nsIDOMNode *aNode, nsIAccessible **_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->CreateXULTooltipAccessible(aNode, _retval); } \
  NS_IMETHOD GetAccessibleFor(nsIDOMNode *aNode, nsIAccessible **_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetAccessibleFor(aNode, _retval); } \
  NS_IMETHOD GetAccessibleInWindow(nsIDOMNode *aNode, nsIDOMWindow *aDOMWin, nsIAccessible **_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetAccessibleInWindow(aNode, aDOMWin, _retval); } \
  NS_IMETHOD GetAccessibleInWeakShell(nsIDOMNode *aNode, nsIWeakReference *aPresShell, nsIAccessible **_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetAccessibleInWeakShell(aNode, aPresShell, _retval); } \
  NS_IMETHOD GetAccessibleInShell(nsIDOMNode *aNode, nsIPresShell *aPresShell, nsIAccessible **_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetAccessibleInShell(aNode, aPresShell, _retval); } \
  NS_IMETHOD GetCachedAccessNode(nsIDOMNode *aNode, nsIWeakReference *aShell, nsIAccessNode **_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetCachedAccessNode(aNode, aShell, _retval); } \
  NS_IMETHOD GetCachedAccessible(nsIDOMNode *aNode, nsIWeakReference *aShell, nsIAccessible **_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetCachedAccessible(aNode, aShell, _retval); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsAccessibilityService : public nsIAccessibilityService
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIACCESSIBILITYSERVICE

  nsAccessibilityService();
  virtual ~nsAccessibilityService();
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsAccessibilityService, nsIAccessibilityService)

nsAccessibilityService::nsAccessibilityService()
{
  /* member initializers and constructor code */
}

nsAccessibilityService::~nsAccessibilityService()
{
  /* destructor code */
}

/* nsIAccessible createOuterDocAccessible (in nsIDOMNode aNode); */
NS_IMETHODIMP nsAccessibilityService::CreateOuterDocAccessible(nsIDOMNode *aNode, nsIAccessible **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* nsIAccessible createRootAccessible (in nsIPresShell aShell, in nsIDocument aDocument); */
NS_IMETHODIMP nsAccessibilityService::CreateRootAccessible(nsIPresShell *aShell, nsIDocument *aDocument, nsIAccessible **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* nsIAccessibleCaret createCaretAccessible (in nsIDOMNode aNode, in nsIAccessible aRootAccessible); */
NS_IMETHODIMP nsAccessibilityService::CreateCaretAccessible(nsIDOMNode *aNode, nsIAccessible *aRootAccessible, nsIAccessibleCaret **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* nsIAccessible createHTML4ButtonAccessible (in nsISupports aFrame); */
NS_IMETHODIMP nsAccessibilityService::CreateHTML4ButtonAccessible(nsISupports *aFrame, nsIAccessible **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* nsIAccessible createHTMLAreaAccessible (in nsIWeakReference aPresShell, in nsIDOMNode aDOMNode, in nsIAccessible aAccParent); */
NS_IMETHODIMP nsAccessibilityService::CreateHTMLAreaAccessible(nsIWeakReference *aPresShell, nsIDOMNode *aDOMNode, nsIAccessible *aAccParent, nsIAccessible **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* nsIAccessible createHTMLBlockAccessible (in nsISupports aFrame); */
NS_IMETHODIMP nsAccessibilityService::CreateHTMLBlockAccessible(nsISupports *aFrame, nsIAccessible **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* nsIAccessible createHTMLButtonAccessible (in nsISupports aFrame); */
NS_IMETHODIMP nsAccessibilityService::CreateHTMLButtonAccessible(nsISupports *aFrame, nsIAccessible **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* nsIAccessible createHTMLButtonAccessibleXBL (in nsIDOMNode aNode); */
NS_IMETHODIMP nsAccessibilityService::CreateHTMLButtonAccessibleXBL(nsIDOMNode *aNode, nsIAccessible **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* nsIAccessible createHTMLCheckboxAccessible (in nsISupports aFrame); */
NS_IMETHODIMP nsAccessibilityService::CreateHTMLCheckboxAccessible(nsISupports *aFrame, nsIAccessible **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* nsIAccessible createHTMLCheckboxAccessibleXBL (in nsIDOMNode aNode); */
NS_IMETHODIMP nsAccessibilityService::CreateHTMLCheckboxAccessibleXBL(nsIDOMNode *aNode, nsIAccessible **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* nsIAccessible createHTMLComboboxAccessible (in nsIDOMNode aNode, in nsISupports aPresShell); */
NS_IMETHODIMP nsAccessibilityService::CreateHTMLComboboxAccessible(nsIDOMNode *aNode, nsISupports *aPresShell, nsIAccessible **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* nsIAccessible createHTMLGroupboxAccessible (in nsISupports aFrame); */
NS_IMETHODIMP nsAccessibilityService::CreateHTMLGroupboxAccessible(nsISupports *aFrame, nsIAccessible **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* nsIAccessible createHTMLHRAccessible (in nsISupports aFrame); */
NS_IMETHODIMP nsAccessibilityService::CreateHTMLHRAccessible(nsISupports *aFrame, nsIAccessible **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* nsIAccessible createHTMLImageAccessible (in nsISupports aFrame); */
NS_IMETHODIMP nsAccessibilityService::CreateHTMLImageAccessible(nsISupports *aFrame, nsIAccessible **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* nsIAccessible createHTMLLabelAccessible (in nsISupports aFrame); */
NS_IMETHODIMP nsAccessibilityService::CreateHTMLLabelAccessible(nsISupports *aFrame, nsIAccessible **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* nsIAccessible createHTMLListboxAccessible (in nsIDOMNode aNode, in nsISupports aPresShell); */
NS_IMETHODIMP nsAccessibilityService::CreateHTMLListboxAccessible(nsIDOMNode *aNode, nsISupports *aPresShell, nsIAccessible **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* nsIAccessible createHTMLObjectFrameAccessible (in nsObjectFrame aFrame); */
NS_IMETHODIMP nsAccessibilityService::CreateHTMLObjectFrameAccessible(nsObjectFrame *aFrame, nsIAccessible **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* nsIAccessible createHTMLRadioButtonAccessible (in nsISupports aFrame); */
NS_IMETHODIMP nsAccessibilityService::CreateHTMLRadioButtonAccessible(nsISupports *aFrame, nsIAccessible **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* nsIAccessible createHTMLRadioButtonAccessibleXBL (in nsIDOMNode aNode); */
NS_IMETHODIMP nsAccessibilityService::CreateHTMLRadioButtonAccessibleXBL(nsIDOMNode *aNode, nsIAccessible **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* nsIAccessible createHTMLSelectOptionAccessible (in nsIDOMNode aNode, in nsIAccessible aAccParent, in nsISupports aPresShell); */
NS_IMETHODIMP nsAccessibilityService::CreateHTMLSelectOptionAccessible(nsIDOMNode *aNode, nsIAccessible *aAccParent, nsISupports *aPresShell, nsIAccessible **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* nsIAccessible createHTMLTableAccessible (in nsISupports aFrame); */
NS_IMETHODIMP nsAccessibilityService::CreateHTMLTableAccessible(nsISupports *aFrame, nsIAccessible **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* nsIAccessible createHTMLTableCellAccessible (in nsISupports aFrame); */
NS_IMETHODIMP nsAccessibilityService::CreateHTMLTableCellAccessible(nsISupports *aFrame, nsIAccessible **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* nsIAccessible createHTMLTableCaptionAccessible (in nsIDOMNode aDOMNode); */
NS_IMETHODIMP nsAccessibilityService::CreateHTMLTableCaptionAccessible(nsIDOMNode *aDOMNode, nsIAccessible **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* nsIAccessible createHTMLTableHeadAccessible (in nsIDOMNode aDOMNode); */
NS_IMETHODIMP nsAccessibilityService::CreateHTMLTableHeadAccessible(nsIDOMNode *aDOMNode, nsIAccessible **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* nsIAccessible createHTMLTextAccessible (in nsISupports aFrame); */
NS_IMETHODIMP nsAccessibilityService::CreateHTMLTextAccessible(nsISupports *aFrame, nsIAccessible **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* nsIAccessible createHTMLTextFieldAccessible (in nsISupports aFrame); */
NS_IMETHODIMP nsAccessibilityService::CreateHTMLTextFieldAccessible(nsISupports *aFrame, nsIAccessible **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* nsIAccessible createXULButtonAccessible (in nsIDOMNode aNode); */
NS_IMETHODIMP nsAccessibilityService::CreateXULButtonAccessible(nsIDOMNode *aNode, nsIAccessible **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* nsIAccessible createXULCheckboxAccessible (in nsIDOMNode aNode); */
NS_IMETHODIMP nsAccessibilityService::CreateXULCheckboxAccessible(nsIDOMNode *aNode, nsIAccessible **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* nsIAccessible createXULColorPickerAccessible (in nsIDOMNode aNode); */
NS_IMETHODIMP nsAccessibilityService::CreateXULColorPickerAccessible(nsIDOMNode *aNode, nsIAccessible **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* nsIAccessible createXULColorPickerTileAccessible (in nsIDOMNode aNode); */
NS_IMETHODIMP nsAccessibilityService::CreateXULColorPickerTileAccessible(nsIDOMNode *aNode, nsIAccessible **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* nsIAccessible createXULComboboxAccessible (in nsIDOMNode aNode); */
NS_IMETHODIMP nsAccessibilityService::CreateXULComboboxAccessible(nsIDOMNode *aNode, nsIAccessible **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* nsIAccessible createXULDropmarkerAccessible (in nsIDOMNode aNode); */
NS_IMETHODIMP nsAccessibilityService::CreateXULDropmarkerAccessible(nsIDOMNode *aNode, nsIAccessible **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* nsIAccessible createXULGroupboxAccessible (in nsIDOMNode aNode); */
NS_IMETHODIMP nsAccessibilityService::CreateXULGroupboxAccessible(nsIDOMNode *aNode, nsIAccessible **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* nsIAccessible createXULImageAccessible (in nsIDOMNode aNode); */
NS_IMETHODIMP nsAccessibilityService::CreateXULImageAccessible(nsIDOMNode *aNode, nsIAccessible **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* nsIAccessible createXULListboxAccessible (in nsIDOMNode aNode); */
NS_IMETHODIMP nsAccessibilityService::CreateXULListboxAccessible(nsIDOMNode *aNode, nsIAccessible **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* nsIAccessible createXULListitemAccessible (in nsIDOMNode aNode); */
NS_IMETHODIMP nsAccessibilityService::CreateXULListitemAccessible(nsIDOMNode *aNode, nsIAccessible **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* nsIAccessible createXULMenubarAccessible (in nsIDOMNode aNode); */
NS_IMETHODIMP nsAccessibilityService::CreateXULMenubarAccessible(nsIDOMNode *aNode, nsIAccessible **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* nsIAccessible createXULMenuitemAccessible (in nsIDOMNode aNode); */
NS_IMETHODIMP nsAccessibilityService::CreateXULMenuitemAccessible(nsIDOMNode *aNode, nsIAccessible **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* nsIAccessible createXULMenupopupAccessible (in nsIDOMNode aNode); */
NS_IMETHODIMP nsAccessibilityService::CreateXULMenupopupAccessible(nsIDOMNode *aNode, nsIAccessible **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* nsIAccessible createXULMenuSeparatorAccessible (in nsIDOMNode aNode); */
NS_IMETHODIMP nsAccessibilityService::CreateXULMenuSeparatorAccessible(nsIDOMNode *aNode, nsIAccessible **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* nsIAccessible createXULProgressMeterAccessible (in nsIDOMNode aNode); */
NS_IMETHODIMP nsAccessibilityService::CreateXULProgressMeterAccessible(nsIDOMNode *aNode, nsIAccessible **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* nsIAccessible createXULStatusBarAccessible (in nsIDOMNode aNode); */
NS_IMETHODIMP nsAccessibilityService::CreateXULStatusBarAccessible(nsIDOMNode *aNode, nsIAccessible **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* nsIAccessible createXULRadioButtonAccessible (in nsIDOMNode aNode); */
NS_IMETHODIMP nsAccessibilityService::CreateXULRadioButtonAccessible(nsIDOMNode *aNode, nsIAccessible **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* nsIAccessible createXULRadioGroupAccessible (in nsIDOMNode aNode); */
NS_IMETHODIMP nsAccessibilityService::CreateXULRadioGroupAccessible(nsIDOMNode *aNode, nsIAccessible **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* nsIAccessible createXULSelectOptionAccessible (in nsIDOMNode aNode); */
NS_IMETHODIMP nsAccessibilityService::CreateXULSelectOptionAccessible(nsIDOMNode *aNode, nsIAccessible **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* nsIAccessible createXULSelectListAccessible (in nsIDOMNode aNode); */
NS_IMETHODIMP nsAccessibilityService::CreateXULSelectListAccessible(nsIDOMNode *aNode, nsIAccessible **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* nsIAccessible createXULTabAccessible (in nsIDOMNode aNode); */
NS_IMETHODIMP nsAccessibilityService::CreateXULTabAccessible(nsIDOMNode *aNode, nsIAccessible **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* nsIAccessible createXULTabBoxAccessible (in nsIDOMNode aNode); */
NS_IMETHODIMP nsAccessibilityService::CreateXULTabBoxAccessible(nsIDOMNode *aNode, nsIAccessible **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* nsIAccessible createXULTabPanelsAccessible (in nsIDOMNode aNode); */
NS_IMETHODIMP nsAccessibilityService::CreateXULTabPanelsAccessible(nsIDOMNode *aNode, nsIAccessible **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* nsIAccessible createXULTabsAccessible (in nsIDOMNode aNode); */
NS_IMETHODIMP nsAccessibilityService::CreateXULTabsAccessible(nsIDOMNode *aNode, nsIAccessible **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* nsIAccessible createXULTextAccessible (in nsIDOMNode aNode); */
NS_IMETHODIMP nsAccessibilityService::CreateXULTextAccessible(nsIDOMNode *aNode, nsIAccessible **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* nsIAccessible createXULTextBoxAccessible (in nsIDOMNode aNode); */
NS_IMETHODIMP nsAccessibilityService::CreateXULTextBoxAccessible(nsIDOMNode *aNode, nsIAccessible **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* nsIAccessible createXULTreeAccessible (in nsIDOMNode aNode); */
NS_IMETHODIMP nsAccessibilityService::CreateXULTreeAccessible(nsIDOMNode *aNode, nsIAccessible **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* nsIAccessible createXULTreeColumnsAccessible (in nsIDOMNode aNode); */
NS_IMETHODIMP nsAccessibilityService::CreateXULTreeColumnsAccessible(nsIDOMNode *aNode, nsIAccessible **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* nsIAccessible createXULTreeColumnitemAccessible (in nsIDOMNode aNode); */
NS_IMETHODIMP nsAccessibilityService::CreateXULTreeColumnitemAccessible(nsIDOMNode *aNode, nsIAccessible **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* nsIAccessible createXULToolbarAccessible (in nsIDOMNode aNode); */
NS_IMETHODIMP nsAccessibilityService::CreateXULToolbarAccessible(nsIDOMNode *aNode, nsIAccessible **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* nsIAccessible createXULToolbarSeparatorAccessible (in nsIDOMNode aNode); */
NS_IMETHODIMP nsAccessibilityService::CreateXULToolbarSeparatorAccessible(nsIDOMNode *aNode, nsIAccessible **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* nsIAccessible createXULTooltipAccessible (in nsIDOMNode aNode); */
NS_IMETHODIMP nsAccessibilityService::CreateXULTooltipAccessible(nsIDOMNode *aNode, nsIAccessible **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* nsIAccessible getAccessibleFor (in nsIDOMNode aNode); */
NS_IMETHODIMP nsAccessibilityService::GetAccessibleFor(nsIDOMNode *aNode, nsIAccessible **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* nsIAccessible getAccessibleInWindow (in nsIDOMNode aNode, in nsIDOMWindow aDOMWin); */
NS_IMETHODIMP nsAccessibilityService::GetAccessibleInWindow(nsIDOMNode *aNode, nsIDOMWindow *aDOMWin, nsIAccessible **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* nsIAccessible getAccessibleInWeakShell (in nsIDOMNode aNode, in nsIWeakReference aPresShell); */
NS_IMETHODIMP nsAccessibilityService::GetAccessibleInWeakShell(nsIDOMNode *aNode, nsIWeakReference *aPresShell, nsIAccessible **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* nsIAccessible getAccessibleInShell (in nsIDOMNode aNode, in nsIPresShell aPresShell); */
NS_IMETHODIMP nsAccessibilityService::GetAccessibleInShell(nsIDOMNode *aNode, nsIPresShell *aPresShell, nsIAccessible **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* [noscript] nsIAccessNode getCachedAccessNode (in nsIDOMNode aNode, in nsIWeakReference aShell); */
NS_IMETHODIMP nsAccessibilityService::GetCachedAccessNode(nsIDOMNode *aNode, nsIWeakReference *aShell, nsIAccessNode **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* [noscript] nsIAccessible getCachedAccessible (in nsIDOMNode aNode, in nsIWeakReference aShell); */
NS_IMETHODIMP nsAccessibilityService::GetCachedAccessible(nsIDOMNode *aNode, nsIWeakReference *aShell, nsIAccessible **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif

// for component registration
// {DE401C37-9A7F-4278-A6F8-3DE2833989EF}
#define NS_ACCESSIBILITY_SERVICE_CID \
{ 0xde401c37, 0x9a7f, 0x4278, { 0xa6, 0xf8, 0x3d, 0xe2, 0x83, 0x39, 0x89, 0xef } }
extern nsresult
NS_NewAccessibilityService(nsIAccessibilityService** aResult);

#endif /* __gen_nsIAccessibilityService_h__ */
