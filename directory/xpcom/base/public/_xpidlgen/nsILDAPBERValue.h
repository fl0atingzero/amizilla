/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM nsILDAPBERValue.idl
 */

#ifndef __gen_nsILDAPBERValue_h__
#define __gen_nsILDAPBERValue_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif

/* starting interface:    nsILDAPBERValue */
#define NS_ILDAPBERVALUE_IID_STR "c817c5fe-1dd1-11b2-a10b-ae9885762ea9"

#define NS_ILDAPBERVALUE_IID \
  {0xc817c5fe, 0x1dd1, 0x11b2, \
    { 0xa1, 0x0b, 0xae, 0x98, 0x85, 0x76, 0x2e, 0xa9 }}

/**
 * Representation of a BER value as an interface containing an array of
 * bytes.  Someday this should perhaps be obsoleted by a better, more
 * generalized version of nsIByteBuffer, but that's currently not even
 * scriptable (see bug 125596).  
 */
class NS_NO_VTABLE nsILDAPBERValue : public nsISupports {
 public: 

  NS_DEFINE_STATIC_IID_ACCESSOR(NS_ILDAPBERVALUE_IID)

  /**
     * Set the BER value from an array of bytes (copies).
     *
     * @exception NS_ERROR_OUT_OF_MEMORY    couldn't allocate buffer to copy to
     */
  /* void set (in unsigned long aCount, [array, size_is (aCount)] in octet aValue); */
  NS_IMETHOD Set(PRUint32 aCount, PRUint8 *aValue) = 0;

  /** 
     * Set the BER value from a UTF8 string (copies).
     *
     * @exception NS_ERROR_OUT_OF_MEMORY    couldn't allocate buffer to copy to
     */
  /* void setFromUTF8 (in AUTF8String aValue); */
  NS_IMETHOD SetFromUTF8(const nsACString & aValue) = 0;

  /** 
     * Get the BER value as an array of bytes.  Note that if this value is
     * zero-length, aCount and aRetVal will both be 0.  This means that 
     * (in C++ anyway) the caller MUST test either aCount or aRetval before
     * dereferencing aRetVal.
     *
     * @exception NS_ERROR_OUT_OF_MEMORY    couldn't allocate buffer to copy to
     */
  /* void get (out unsigned long aCount, [array, size_is (aCount), retval] out octet aRetVal); */
  NS_IMETHOD Get(PRUint32 *aCount, PRUint8 **aRetVal) = 0;

};

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSILDAPBERVALUE \
  NS_IMETHOD Set(PRUint32 aCount, PRUint8 *aValue); \
  NS_IMETHOD SetFromUTF8(const nsACString & aValue); \
  NS_IMETHOD Get(PRUint32 *aCount, PRUint8 **aRetVal); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSILDAPBERVALUE(_to) \
  NS_IMETHOD Set(PRUint32 aCount, PRUint8 *aValue) { return _to Set(aCount, aValue); } \
  NS_IMETHOD SetFromUTF8(const nsACString & aValue) { return _to SetFromUTF8(aValue); } \
  NS_IMETHOD Get(PRUint32 *aCount, PRUint8 **aRetVal) { return _to Get(aCount, aRetVal); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSILDAPBERVALUE(_to) \
  NS_IMETHOD Set(PRUint32 aCount, PRUint8 *aValue) { return !_to ? NS_ERROR_NULL_POINTER : _to->Set(aCount, aValue); } \
  NS_IMETHOD SetFromUTF8(const nsACString & aValue) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetFromUTF8(aValue); } \
  NS_IMETHOD Get(PRUint32 *aCount, PRUint8 **aRetVal) { return !_to ? NS_ERROR_NULL_POINTER : _to->Get(aCount, aRetVal); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsLDAPBERValue : public nsILDAPBERValue
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSILDAPBERVALUE

  nsLDAPBERValue();
  virtual ~nsLDAPBERValue();
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsLDAPBERValue, nsILDAPBERValue)

nsLDAPBERValue::nsLDAPBERValue()
{
  /* member initializers and constructor code */
}

nsLDAPBERValue::~nsLDAPBERValue()
{
  /* destructor code */
}

/* void set (in unsigned long aCount, [array, size_is (aCount)] in octet aValue); */
NS_IMETHODIMP nsLDAPBERValue::Set(PRUint32 aCount, PRUint8 *aValue)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void setFromUTF8 (in AUTF8String aValue); */
NS_IMETHODIMP nsLDAPBERValue::SetFromUTF8(const nsACString & aValue)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void get (out unsigned long aCount, [array, size_is (aCount), retval] out octet aRetVal); */
NS_IMETHODIMP nsLDAPBERValue::Get(PRUint32 *aCount, PRUint8 **aRetVal)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsILDAPBERValue_h__ */
