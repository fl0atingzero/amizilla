/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM nsIAccessibleProvider.idl
 */

#ifndef __gen_nsIAccessibleProvider_h__
#define __gen_nsIAccessibleProvider_h__


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

/* starting interface:    nsIAccessibleProvider */
#define NS_IACCESSIBLEPROVIDER_IID_STR "3f0e3eb0-1dd2-11b2-9605-be5b8e76cf4b"

#define NS_IACCESSIBLEPROVIDER_IID \
  {0x3f0e3eb0, 0x1dd2, 0x11b2, \
    { 0x96, 0x05, 0xbe, 0x5b, 0x8e, 0x76, 0xcf, 0x4b }}

class NS_NO_VTABLE nsIAccessibleProvider : public nsISupports {
 public: 

  NS_DEFINE_STATIC_IID_ACCESSOR(NS_IACCESSIBLEPROVIDER_IID)

  /* readonly attribute nsIAccessible accessible; */
  NS_IMETHOD GetAccessible(nsIAccessible * *aAccessible) = 0;

};

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSIACCESSIBLEPROVIDER \
  NS_IMETHOD GetAccessible(nsIAccessible * *aAccessible); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSIACCESSIBLEPROVIDER(_to) \
  NS_IMETHOD GetAccessible(nsIAccessible * *aAccessible) { return _to GetAccessible(aAccessible); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSIACCESSIBLEPROVIDER(_to) \
  NS_IMETHOD GetAccessible(nsIAccessible * *aAccessible) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetAccessible(aAccessible); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsAccessibleProvider : public nsIAccessibleProvider
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIACCESSIBLEPROVIDER

  nsAccessibleProvider();
  virtual ~nsAccessibleProvider();
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsAccessibleProvider, nsIAccessibleProvider)

nsAccessibleProvider::nsAccessibleProvider()
{
  /* member initializers and constructor code */
}

nsAccessibleProvider::~nsAccessibleProvider()
{
  /* destructor code */
}

/* readonly attribute nsIAccessible accessible; */
NS_IMETHODIMP nsAccessibleProvider::GetAccessible(nsIAccessible * *aAccessible)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsIAccessibleProvider_h__ */
