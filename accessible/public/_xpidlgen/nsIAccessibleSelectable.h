/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM nsIAccessibleSelectable.idl
 */

#ifndef __gen_nsIAccessibleSelectable_h__
#define __gen_nsIAccessibleSelectable_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

#ifndef __gen_nsIAccessible_h__
#include "nsIAccessible.h"
#endif

#ifndef __gen_nsISupportsArray_h__
#include "nsISupportsArray.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif

/* starting interface:    nsIAccessibleSelectable */
#define NS_IACCESSIBLESELECTABLE_IID_STR "34d268d6-1dd2-11b2-9d63-83a5e0ada290"

#define NS_IACCESSIBLESELECTABLE_IID \
  {0x34d268d6, 0x1dd2, 0x11b2, \
    { 0x9d, 0x63, 0x83, 0xa5, 0xe0, 0xad, 0xa2, 0x90 }}

class nsIAccessibleSelectable : public nsISupports {
 public: 

  NS_DEFINE_STATIC_IID_ACCESSOR(NS_IACCESSIBLESELECTABLE_IID)

	enum { eSelection_Add = 0U, eSelection_Remove = 1U, eSelection_GetState = 2U };
  /* nsISupportsArray GetSelectedChildren (); */
  NS_IMETHOD GetSelectedChildren(nsISupportsArray **_retval) = 0;

  /**
      * Returns the number of accessible children currently selected.
      */
  /* readonly attribute long selectionCount; */
  NS_IMETHOD GetSelectionCount(PRInt32 *aSelectionCount) = 0;

  /**
      * Adds the specified accessible child of the object to the
      * object's selection.
      */
  /* void addSelection (in long index); */
  NS_IMETHOD AddSelection(PRInt32 index) = 0;

  /**
      * Removes the specified child of the object from the object's selection.
      */
  /* void removeSelection (in long index); */
  NS_IMETHOD RemoveSelection(PRInt32 index) = 0;

  /**
      * Clears the selection in the object so that no children in the object
      * are selected.
      */
  /* void clearSelection (); */
  NS_IMETHOD ClearSelection(void) = 0;

  /**
      * Returns a reference to the accessible object representing the specified
      * selected child of the object.
      */
  /* nsIAccessible refSelection (in long index); */
  NS_IMETHOD RefSelection(PRInt32 index, nsIAccessible **_retval) = 0;

  /**
      * Determines if the current child of this object is selected
      */
  /* boolean isChildSelected (in long index); */
  NS_IMETHOD IsChildSelected(PRInt32 index, PRBool *_retval) = 0;

  /**
      * If the object does not accept multiple selection, return false.
      */
  /* boolean selectAllSelection (); */
  NS_IMETHOD SelectAllSelection(PRBool *_retval) = 0;

};

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSIACCESSIBLESELECTABLE \
  NS_IMETHOD GetSelectedChildren(nsISupportsArray **_retval); \
  NS_IMETHOD GetSelectionCount(PRInt32 *aSelectionCount); \
  NS_IMETHOD AddSelection(PRInt32 index); \
  NS_IMETHOD RemoveSelection(PRInt32 index); \
  NS_IMETHOD ClearSelection(void); \
  NS_IMETHOD RefSelection(PRInt32 index, nsIAccessible **_retval); \
  NS_IMETHOD IsChildSelected(PRInt32 index, PRBool *_retval); \
  NS_IMETHOD SelectAllSelection(PRBool *_retval); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSIACCESSIBLESELECTABLE(_to) \
  NS_IMETHOD GetSelectedChildren(nsISupportsArray **_retval) { return _to GetSelectedChildren(_retval); } \
  NS_IMETHOD GetSelectionCount(PRInt32 *aSelectionCount) { return _to GetSelectionCount(aSelectionCount); } \
  NS_IMETHOD AddSelection(PRInt32 index) { return _to AddSelection(index); } \
  NS_IMETHOD RemoveSelection(PRInt32 index) { return _to RemoveSelection(index); } \
  NS_IMETHOD ClearSelection(void) { return _to ClearSelection(); } \
  NS_IMETHOD RefSelection(PRInt32 index, nsIAccessible **_retval) { return _to RefSelection(index, _retval); } \
  NS_IMETHOD IsChildSelected(PRInt32 index, PRBool *_retval) { return _to IsChildSelected(index, _retval); } \
  NS_IMETHOD SelectAllSelection(PRBool *_retval) { return _to SelectAllSelection(_retval); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSIACCESSIBLESELECTABLE(_to) \
  NS_IMETHOD GetSelectedChildren(nsISupportsArray **_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetSelectedChildren(_retval); } \
  NS_IMETHOD GetSelectionCount(PRInt32 *aSelectionCount) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetSelectionCount(aSelectionCount); } \
  NS_IMETHOD AddSelection(PRInt32 index) { return !_to ? NS_ERROR_NULL_POINTER : _to->AddSelection(index); } \
  NS_IMETHOD RemoveSelection(PRInt32 index) { return !_to ? NS_ERROR_NULL_POINTER : _to->RemoveSelection(index); } \
  NS_IMETHOD ClearSelection(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->ClearSelection(); } \
  NS_IMETHOD RefSelection(PRInt32 index, nsIAccessible **_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->RefSelection(index, _retval); } \
  NS_IMETHOD IsChildSelected(PRInt32 index, PRBool *_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->IsChildSelected(index, _retval); } \
  NS_IMETHOD SelectAllSelection(PRBool *_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->SelectAllSelection(_retval); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsAccessibleSelectable : public nsIAccessibleSelectable
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIACCESSIBLESELECTABLE

  nsAccessibleSelectable();
  virtual ~nsAccessibleSelectable();
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsAccessibleSelectable, nsIAccessibleSelectable)

nsAccessibleSelectable::nsAccessibleSelectable()
{
  /* member initializers and constructor code */
}

nsAccessibleSelectable::~nsAccessibleSelectable()
{
  /* destructor code */
}

/* nsISupportsArray GetSelectedChildren (); */
NS_IMETHODIMP nsAccessibleSelectable::GetSelectedChildren(nsISupportsArray **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute long selectionCount; */
NS_IMETHODIMP nsAccessibleSelectable::GetSelectionCount(PRInt32 *aSelectionCount)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void addSelection (in long index); */
NS_IMETHODIMP nsAccessibleSelectable::AddSelection(PRInt32 index)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void removeSelection (in long index); */
NS_IMETHODIMP nsAccessibleSelectable::RemoveSelection(PRInt32 index)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void clearSelection (); */
NS_IMETHODIMP nsAccessibleSelectable::ClearSelection()
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* nsIAccessible refSelection (in long index); */
NS_IMETHODIMP nsAccessibleSelectable::RefSelection(PRInt32 index, nsIAccessible **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* boolean isChildSelected (in long index); */
NS_IMETHODIMP nsAccessibleSelectable::IsChildSelected(PRInt32 index, PRBool *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* boolean selectAllSelection (); */
NS_IMETHODIMP nsAccessibleSelectable::SelectAllSelection(PRBool *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsIAccessibleSelectable_h__ */
