/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM nsILDAPMessage.idl
 */

#ifndef __gen_nsILDAPMessage_h__
#define __gen_nsILDAPMessage_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif
class nsILDAPBERValue; /* forward declaration */

class nsILDAPOperation; /* forward declaration */


/* starting interface:    nsILDAPMessage */
#define NS_ILDAPMESSAGE_IID_STR "973ff50f-2002-4f0c-b57d-2242156139a2"

#define NS_ILDAPMESSAGE_IID \
  {0x973ff50f, 0x2002, 0x4f0c, \
    { 0xb5, 0x7d, 0x22, 0x42, 0x15, 0x61, 0x39, 0xa2 }}

class NS_NO_VTABLE nsILDAPMessage : public nsISupports {
 public: 

  NS_DEFINE_STATIC_IID_ACCESSOR(NS_ILDAPMESSAGE_IID)

  /**
     * The Distinguished Name of the entry associated with this message.
     * 
     * @exception NS_ERROR_OUT_OF_MEMORY        ran out of memory
     * @exception NS_ERROR_ILLEGAL_VALUE        null pointer passed in
     * @exception NS_ERROR_LDAP_DECODING_ERROR  problem during BER-decoding
     * @exception NS_ERROR_UNEXPECTED           bug or memory corruption
     */
  /* readonly attribute AUTF8String dn; */
  NS_IMETHOD GetDn(nsACString & aDn) = 0;

  /**
     * Get all the attributes in this message.
     *
     * @exception NS_ERROR_OUT_OF_MEMORY
     * @exception NS_ERROR_ILLEGAL_VALUE        null pointer passed in
     * @exception NS_ERROR_UNEXPECTED           bug or memory corruption
     * @exception NS_ERROR_LDAP_DECODING_ERROR  problem during BER decoding
     *
     * @return  array of all attributes in the current message
     */
  /* void getAttributes (out unsigned long count, [array, size_is (count), retval] out string aAttributes); */
  NS_IMETHOD GetAttributes(PRUint32 *count, char ***aAttributes) = 0;

  /**
     * Get an array of all the attribute values in this message.
     *
     * @param attr      The attribute whose values are to be returned
     * @param count     Number of values in the outbound array.
     * @param values    Array of values
     *
     * @exception NS_ERROR_UNEXPECTED           Bug or memory corruption
     * @exception NS_ERROR_LDAP_DECODING_ERROR  Attribute not found or other 
     *                                          decoding error.
     * @exception NS_ERROR_OUT_OF_MEMORY
     */
  /* void getValues (in string attr, out unsigned long count, [array, size_is (count), retval] out wstring values); */
  NS_IMETHOD GetValues(const char *attr, PRUint32 *count, PRUnichar ***values) = 0;

  /**
     * The operation this message originated from
     * 
     * @exception NS_ERROR_NULL_POINTER         NULL pointer to getter
     */
  /* readonly attribute nsILDAPOperation operation; */
  NS_IMETHOD GetOperation(nsILDAPOperation * *aOperation) = 0;

  /**
     * The result code (aka lderrno) for this message.  
     *
     * IDL definitions for these constants live in nsILDAPErrors.idl.
     *
     * @exception NS_ERROR_ILLEGAL_VALUE    null pointer passed in
     */
  /* readonly attribute long errorCode; */
  NS_IMETHOD GetErrorCode(PRInt32 *aErrorCode) = 0;

  /**
     * The result type of this message.  Possible types listed below, the 
     * values chosen are taken from the draft-ietf-ldapext-ldap-c-api-04.txt
     * and are the same ones used in the ldap.h include file from the Mozilla
     * LDAP C SDK.
     *
     * @exception NS_ERROR_ILLEGAL_VALUE    null pointer passed in
     * @exception NS_ERROR_UNEXPECTED       internal error (possible memory
     *                                                      corruption)
     */
  /* readonly attribute long type; */
  NS_IMETHOD GetType(PRInt32 *aType) = 0;

  /**
     * Result of a bind operation
     */
  enum { RES_BIND = 97 };

  /**
     * An entry found in an search operation.
     */
  enum { RES_SEARCH_ENTRY = 100 };

  /**
     * An LDAPv3 search reference (a referral to another server)
     */
  enum { RES_SEARCH_REFERENCE = 115 };

  /** 
     * The result of a search operation (i.e. the search is done; no more
     * entries to follow).
     */
  enum { RES_SEARCH_RESULT = 101 };

  /**
     * The result of a modify operation.
     */
  enum { RES_MODIFY = 103 };

  /** 
     * The result of an add operation
     */
  enum { RES_ADD = 105 };

  /**
     * The result of a delete operation
     */
  enum { RES_DELETE = 107 };

  /**
     * The result of an modify DN operation
     */
  enum { RES_MODDN = 109 };

  /**
     * The result of a compare operation
     */
  enum { RES_COMPARE = 111 };

  /** 
     * The result of an LDAPv3 extended operation
     */
  enum { RES_EXTENDED = 120 };

  /**
     * get an LDIF-like string representation of this message
     *
     * @return unicode encoded string representation.
     */
  /* wstring toUnicode (); */
  NS_IMETHOD ToUnicode(PRUnichar **_retval) = 0;

  /**
     * Additional error information optionally sent by the server.
     */
  /* readonly attribute AUTF8String errorMessage; */
  NS_IMETHOD GetErrorMessage(nsACString & aErrorMessage) = 0;

  /**
     * In LDAPv3, when the server returns any of the following errors:
     * NO_SUCH_OBJECT, ALIAS_PROBLEM, INVALID_DN_SYNTAX, ALIAS_DEREF_PROBLEM,
     * it also returns the closest existing DN to the entry requested.
     */
  /* readonly attribute AUTF8String matchedDn; */
  NS_IMETHOD GetMatchedDn(nsACString & aMatchedDn) = 0;

  /**
     * Get an array of all the attribute values in this message (a wrapper
     * around the LDAP C SDK's get_values_len()).
     *
     * @param attr      The attribute whose values are to be returned
     * @param count     Number of values in the outbound array.
     * @param values    Array of nsILDAPBERValue objects
     *
     * @exception NS_ERROR_UNEXPECTED           Bug or memory corruption
     * @exception NS_ERROR_LDAP_DECODING_ERROR  Attribute not found or other 
     *                                          decoding error.
     * @exception NS_ERROR_OUT_OF_MEMORY
     */
  /* void getBinaryValues (in string attr, out unsigned long count, [array, size_is (count), retval] out nsILDAPBERValue values); */
  NS_IMETHOD GetBinaryValues(const char *attr, PRUint32 *count, nsILDAPBERValue ***values) = 0;

};

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSILDAPMESSAGE \
  NS_IMETHOD GetDn(nsACString & aDn); \
  NS_IMETHOD GetAttributes(PRUint32 *count, char ***aAttributes); \
  NS_IMETHOD GetValues(const char *attr, PRUint32 *count, PRUnichar ***values); \
  NS_IMETHOD GetOperation(nsILDAPOperation * *aOperation); \
  NS_IMETHOD GetErrorCode(PRInt32 *aErrorCode); \
  NS_IMETHOD GetType(PRInt32 *aType); \
  NS_IMETHOD ToUnicode(PRUnichar **_retval); \
  NS_IMETHOD GetErrorMessage(nsACString & aErrorMessage); \
  NS_IMETHOD GetMatchedDn(nsACString & aMatchedDn); \
  NS_IMETHOD GetBinaryValues(const char *attr, PRUint32 *count, nsILDAPBERValue ***values); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSILDAPMESSAGE(_to) \
  NS_IMETHOD GetDn(nsACString & aDn) { return _to GetDn(aDn); } \
  NS_IMETHOD GetAttributes(PRUint32 *count, char ***aAttributes) { return _to GetAttributes(count, aAttributes); } \
  NS_IMETHOD GetValues(const char *attr, PRUint32 *count, PRUnichar ***values) { return _to GetValues(attr, count, values); } \
  NS_IMETHOD GetOperation(nsILDAPOperation * *aOperation) { return _to GetOperation(aOperation); } \
  NS_IMETHOD GetErrorCode(PRInt32 *aErrorCode) { return _to GetErrorCode(aErrorCode); } \
  NS_IMETHOD GetType(PRInt32 *aType) { return _to GetType(aType); } \
  NS_IMETHOD ToUnicode(PRUnichar **_retval) { return _to ToUnicode(_retval); } \
  NS_IMETHOD GetErrorMessage(nsACString & aErrorMessage) { return _to GetErrorMessage(aErrorMessage); } \
  NS_IMETHOD GetMatchedDn(nsACString & aMatchedDn) { return _to GetMatchedDn(aMatchedDn); } \
  NS_IMETHOD GetBinaryValues(const char *attr, PRUint32 *count, nsILDAPBERValue ***values) { return _to GetBinaryValues(attr, count, values); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSILDAPMESSAGE(_to) \
  NS_IMETHOD GetDn(nsACString & aDn) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetDn(aDn); } \
  NS_IMETHOD GetAttributes(PRUint32 *count, char ***aAttributes) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetAttributes(count, aAttributes); } \
  NS_IMETHOD GetValues(const char *attr, PRUint32 *count, PRUnichar ***values) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetValues(attr, count, values); } \
  NS_IMETHOD GetOperation(nsILDAPOperation * *aOperation) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetOperation(aOperation); } \
  NS_IMETHOD GetErrorCode(PRInt32 *aErrorCode) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetErrorCode(aErrorCode); } \
  NS_IMETHOD GetType(PRInt32 *aType) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetType(aType); } \
  NS_IMETHOD ToUnicode(PRUnichar **_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->ToUnicode(_retval); } \
  NS_IMETHOD GetErrorMessage(nsACString & aErrorMessage) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetErrorMessage(aErrorMessage); } \
  NS_IMETHOD GetMatchedDn(nsACString & aMatchedDn) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetMatchedDn(aMatchedDn); } \
  NS_IMETHOD GetBinaryValues(const char *attr, PRUint32 *count, nsILDAPBERValue ***values) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetBinaryValues(attr, count, values); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsLDAPMessage : public nsILDAPMessage
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSILDAPMESSAGE

  nsLDAPMessage();
  virtual ~nsLDAPMessage();
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsLDAPMessage, nsILDAPMessage)

nsLDAPMessage::nsLDAPMessage()
{
  /* member initializers and constructor code */
}

nsLDAPMessage::~nsLDAPMessage()
{
  /* destructor code */
}

/* readonly attribute AUTF8String dn; */
NS_IMETHODIMP nsLDAPMessage::GetDn(nsACString & aDn)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void getAttributes (out unsigned long count, [array, size_is (count), retval] out string aAttributes); */
NS_IMETHODIMP nsLDAPMessage::GetAttributes(PRUint32 *count, char ***aAttributes)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void getValues (in string attr, out unsigned long count, [array, size_is (count), retval] out wstring values); */
NS_IMETHODIMP nsLDAPMessage::GetValues(const char *attr, PRUint32 *count, PRUnichar ***values)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute nsILDAPOperation operation; */
NS_IMETHODIMP nsLDAPMessage::GetOperation(nsILDAPOperation * *aOperation)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute long errorCode; */
NS_IMETHODIMP nsLDAPMessage::GetErrorCode(PRInt32 *aErrorCode)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute long type; */
NS_IMETHODIMP nsLDAPMessage::GetType(PRInt32 *aType)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* wstring toUnicode (); */
NS_IMETHODIMP nsLDAPMessage::ToUnicode(PRUnichar **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute AUTF8String errorMessage; */
NS_IMETHODIMP nsLDAPMessage::GetErrorMessage(nsACString & aErrorMessage)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute AUTF8String matchedDn; */
NS_IMETHODIMP nsLDAPMessage::GetMatchedDn(nsACString & aMatchedDn)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void getBinaryValues (in string attr, out unsigned long count, [array, size_is (count), retval] out nsILDAPBERValue values); */
NS_IMETHODIMP nsLDAPMessage::GetBinaryValues(const char *attr, PRUint32 *count, nsILDAPBERValue ***values)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsILDAPMessage_h__ */
