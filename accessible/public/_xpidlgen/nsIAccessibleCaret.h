/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM nsIAccessibleCaret.idl
 */

#ifndef __gen_nsIAccessibleCaret_h__
#define __gen_nsIAccessibleCaret_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

#ifndef __gen_nsIAccessible_h__
#include "nsIAccessible.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif

/* starting interface:    nsIAccessibleCaret */
#define NS_IACCESSIBLECARET_IID_STR "9124c666-6133-4be6-b3ed-dd0ec35f1e64"

#define NS_IACCESSIBLECARET_IID \
  {0x9124c666, 0x6133, 0x4be6, \
    { 0xb3, 0xed, 0xdd, 0x0e, 0xc3, 0x5f, 0x1e, 0x64 }}

class NS_NO_VTABLE nsIAccessibleCaret : public nsISupports {
 public: 

  NS_DEFINE_STATIC_IID_ACCESSOR(NS_IACCESSIBLECARET_IID)

  /* void attachNewSelectionListener (in nsIDOMNode aFocusedNode); */
  NS_IMETHOD AttachNewSelectionListener(nsIDOMNode *aFocusedNode) = 0;

  /* void removeSelectionListener (); */
  NS_IMETHOD RemoveSelectionListener(void) = 0;

};

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSIACCESSIBLECARET \
  NS_IMETHOD AttachNewSelectionListener(nsIDOMNode *aFocusedNode); \
  NS_IMETHOD RemoveSelectionListener(void); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSIACCESSIBLECARET(_to) \
  NS_IMETHOD AttachNewSelectionListener(nsIDOMNode *aFocusedNode) { return _to AttachNewSelectionListener(aFocusedNode); } \
  NS_IMETHOD RemoveSelectionListener(void) { return _to RemoveSelectionListener(); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSIACCESSIBLECARET(_to) \
  NS_IMETHOD AttachNewSelectionListener(nsIDOMNode *aFocusedNode) { return !_to ? NS_ERROR_NULL_POINTER : _to->AttachNewSelectionListener(aFocusedNode); } \
  NS_IMETHOD RemoveSelectionListener(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->RemoveSelectionListener(); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsAccessibleCaret : public nsIAccessibleCaret
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIACCESSIBLECARET

  nsAccessibleCaret();
  virtual ~nsAccessibleCaret();
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsAccessibleCaret, nsIAccessibleCaret)

nsAccessibleCaret::nsAccessibleCaret()
{
  /* member initializers and constructor code */
}

nsAccessibleCaret::~nsAccessibleCaret()
{
  /* destructor code */
}

/* void attachNewSelectionListener (in nsIDOMNode aFocusedNode); */
NS_IMETHODIMP nsAccessibleCaret::AttachNewSelectionListener(nsIDOMNode *aFocusedNode)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void removeSelectionListener (); */
NS_IMETHODIMP nsAccessibleCaret::RemoveSelectionListener()
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsIAccessibleCaret_h__ */
