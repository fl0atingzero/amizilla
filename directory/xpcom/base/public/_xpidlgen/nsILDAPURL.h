/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM nsILDAPURL.idl
 */

#ifndef __gen_nsILDAPURL_h__
#define __gen_nsILDAPURL_h__


#ifndef __gen_nsIURI_h__
#include "nsIURI.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif

/* starting interface:    nsILDAPURL */
#define NS_ILDAPURL_IID_STR "7310562d-1567-43c7-a123-633c1ba3663e"

#define NS_ILDAPURL_IID \
  {0x7310562d, 0x1567, 0x43c7, \
    { 0xa1, 0x23, 0x63, 0x3c, 0x1b, 0xa3, 0x66, 0x3e }}

/**
 * Strings in methods inherited from nsIURI, which are using XPIDL
 * |string| types, are expected to be UTF8 encoded. All such strings
 * in this interface, except attribute types (e.g. "cn"), should in fact
 * be UTF8. It's important to remember that attributes can not be UTF8,
 * they can only be of a limited subset of ASCII (see RFC 2251).
 */
class NS_NO_VTABLE nsILDAPURL : public nsIURI {
 public: 

  NS_DEFINE_STATIC_IID_ACCESSOR(NS_ILDAPURL_IID)

  /**
     * The distinguished name of the URL (ie the base DN for the search).
     * This string is expected to be a valid UTF8 string.
     *
     * for the getter:
     *
     * @exception NS_ERROR_NULL_POINTER     NULL pointer to GET method
     * @exception NS_ERROR_OUT_OF_MEMORY	Ran out of memory
     */
  /* attribute AUTF8String dn; */
  NS_IMETHOD GetDn(nsACString & aDn) = 0;
  NS_IMETHOD SetDn(const nsACString & aDn) = 0;

  /**
     * Return all LDAP attributes currently set. The empty array indicates
     * that all attributes are requested.
     *
     * @exception NS_ERROR_NULL_POINTER     NULL pointer to GET method
     * @exception NS_ERROR_OUT_OF_MEMORY	Ran out of memory
     */
  /* void getAttributes (out unsigned long aCount, [array, size_is (aCount), retval] out string aAttrs); */
  NS_IMETHOD GetAttributes(PRUint32 *aCount, char ***aAttrs) = 0;

  /**
     * Set the array of attributes, dropping whatever was there before.
     *
     * @param aAttrs                        An array of LDAP attributes
     * @exception NS_ERROR_OUT_OF_MEMORY	Ran out of memory
     */
  /* void setAttributes (in unsigned long aCount, [array, size_is (aCount)] in string aAttrs); */
  NS_IMETHOD SetAttributes(PRUint32 aCount, const char **aAttrs) = 0;

  /**
     * Add one attribute to the array of attributes to request. If the
     * attribute is already in our array, this becomes a noop.
     *
     * @param aAttribute          An LDAP attribute (e.g. "cn")
     */
  /* void addAttribute (in string aAttribute); */
  NS_IMETHOD AddAttribute(const char *aAttribute) = 0;

  /**
     * Remove one attribute from the array of attributes to request. If
     * the attribute didn't exist in the array, this becomes a noop.
     *
     * @param aAttribute                    An LDAP attribute (e.g. "cn")
     * @exception NS_ERROR_OUT_OF_MEMORY	Ran out of memory
     */
  /* void removeAttribute (in string aAttribute); */
  NS_IMETHOD RemoveAttribute(const char *aAttribute) = 0;

  /**
     * Test if an attribute is in our list of attributes already
     *
     * @param aAttribute                    An LDAP attribute (e.g. "cn")
     * @return boolean                      Truth value
     * @exception NS_ERROR_NULL_POINTER     NULL pointer to GET method
     */
  /* boolean hasAttribute (in string aAttribute); */
  NS_IMETHOD HasAttribute(const char *aAttribute, PRBool *_retval) = 0;

  /**
     * The scope of the search.  defaults to SCOPE_BASE. 
     *
     * @exception NS_ERROR_NULL_POINTER     NULL pointer to GET method
     * @exception NS_ERROR_MALFORMED_URI	Illegal base to SET method
     */
  /* attribute long scope; */
  NS_IMETHOD GetScope(PRInt32 *aScope) = 0;
  NS_IMETHOD SetScope(PRInt32 aScope) = 0;

  /**
     * Search just the base object
     */
  enum { SCOPE_BASE = 0 };

  /** 
     * Search only the children of the base object
     */
  enum { SCOPE_ONELEVEL = 1 };

  /**
     * Search the entire subtree under and including the base object
     */
  enum { SCOPE_SUBTREE = 2 };

  /**
     * The search filter. "(objectClass=*)" is the default.
     */
  /* attribute AUTF8String filter; */
  NS_IMETHOD GetFilter(nsACString & aFilter) = 0;
  NS_IMETHOD SetFilter(const nsACString & aFilter) = 0;

  /**
     * Any options defined for this URL (check options using a bitwise and)
     * 
     * @exception NS_ERROR_NULL_POINTER     NULL pointer to GET method
     * @exception NS_ERROR_OUT_OF_MEMORY    Ran out of memory
     */
  /* attribute unsigned long options; */
  NS_IMETHOD GetOptions(PRUint32 *aOptions) = 0;
  NS_IMETHOD SetOptions(PRUint32 aOptions) = 0;

  /**
     * If this is set/true, this is an ldaps: URL, not an ldap: URL
     */
  enum { OPT_SECURE = 1U };

};

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSILDAPURL \
  NS_IMETHOD GetDn(nsACString & aDn); \
  NS_IMETHOD SetDn(const nsACString & aDn); \
  NS_IMETHOD GetAttributes(PRUint32 *aCount, char ***aAttrs); \
  NS_IMETHOD SetAttributes(PRUint32 aCount, const char **aAttrs); \
  NS_IMETHOD AddAttribute(const char *aAttribute); \
  NS_IMETHOD RemoveAttribute(const char *aAttribute); \
  NS_IMETHOD HasAttribute(const char *aAttribute, PRBool *_retval); \
  NS_IMETHOD GetScope(PRInt32 *aScope); \
  NS_IMETHOD SetScope(PRInt32 aScope); \
  NS_IMETHOD GetFilter(nsACString & aFilter); \
  NS_IMETHOD SetFilter(const nsACString & aFilter); \
  NS_IMETHOD GetOptions(PRUint32 *aOptions); \
  NS_IMETHOD SetOptions(PRUint32 aOptions); \

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSILDAPURL(_to) \
  NS_IMETHOD GetDn(nsACString & aDn) { return _to GetDn(aDn); } \
  NS_IMETHOD SetDn(const nsACString & aDn) { return _to SetDn(aDn); } \
  NS_IMETHOD GetAttributes(PRUint32 *aCount, char ***aAttrs) { return _to GetAttributes(aCount, aAttrs); } \
  NS_IMETHOD SetAttributes(PRUint32 aCount, const char **aAttrs) { return _to SetAttributes(aCount, aAttrs); } \
  NS_IMETHOD AddAttribute(const char *aAttribute) { return _to AddAttribute(aAttribute); } \
  NS_IMETHOD RemoveAttribute(const char *aAttribute) { return _to RemoveAttribute(aAttribute); } \
  NS_IMETHOD HasAttribute(const char *aAttribute, PRBool *_retval) { return _to HasAttribute(aAttribute, _retval); } \
  NS_IMETHOD GetScope(PRInt32 *aScope) { return _to GetScope(aScope); } \
  NS_IMETHOD SetScope(PRInt32 aScope) { return _to SetScope(aScope); } \
  NS_IMETHOD GetFilter(nsACString & aFilter) { return _to GetFilter(aFilter); } \
  NS_IMETHOD SetFilter(const nsACString & aFilter) { return _to SetFilter(aFilter); } \
  NS_IMETHOD GetOptions(PRUint32 *aOptions) { return _to GetOptions(aOptions); } \
  NS_IMETHOD SetOptions(PRUint32 aOptions) { return _to SetOptions(aOptions); } \

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSILDAPURL(_to) \
  NS_IMETHOD GetDn(nsACString & aDn) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetDn(aDn); } \
  NS_IMETHOD SetDn(const nsACString & aDn) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetDn(aDn); } \
  NS_IMETHOD GetAttributes(PRUint32 *aCount, char ***aAttrs) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetAttributes(aCount, aAttrs); } \
  NS_IMETHOD SetAttributes(PRUint32 aCount, const char **aAttrs) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetAttributes(aCount, aAttrs); } \
  NS_IMETHOD AddAttribute(const char *aAttribute) { return !_to ? NS_ERROR_NULL_POINTER : _to->AddAttribute(aAttribute); } \
  NS_IMETHOD RemoveAttribute(const char *aAttribute) { return !_to ? NS_ERROR_NULL_POINTER : _to->RemoveAttribute(aAttribute); } \
  NS_IMETHOD HasAttribute(const char *aAttribute, PRBool *_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->HasAttribute(aAttribute, _retval); } \
  NS_IMETHOD GetScope(PRInt32 *aScope) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetScope(aScope); } \
  NS_IMETHOD SetScope(PRInt32 aScope) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetScope(aScope); } \
  NS_IMETHOD GetFilter(nsACString & aFilter) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetFilter(aFilter); } \
  NS_IMETHOD SetFilter(const nsACString & aFilter) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetFilter(aFilter); } \
  NS_IMETHOD GetOptions(PRUint32 *aOptions) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetOptions(aOptions); } \
  NS_IMETHOD SetOptions(PRUint32 aOptions) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetOptions(aOptions); } \

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsLDAPURL : public nsILDAPURL
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSILDAPURL

  nsLDAPURL();
  virtual ~nsLDAPURL();
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsLDAPURL, nsILDAPURL)

nsLDAPURL::nsLDAPURL()
{
  /* member initializers and constructor code */
}

nsLDAPURL::~nsLDAPURL()
{
  /* destructor code */
}

/* attribute AUTF8String dn; */
NS_IMETHODIMP nsLDAPURL::GetDn(nsACString & aDn)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsLDAPURL::SetDn(const nsACString & aDn)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void getAttributes (out unsigned long aCount, [array, size_is (aCount), retval] out string aAttrs); */
NS_IMETHODIMP nsLDAPURL::GetAttributes(PRUint32 *aCount, char ***aAttrs)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void setAttributes (in unsigned long aCount, [array, size_is (aCount)] in string aAttrs); */
NS_IMETHODIMP nsLDAPURL::SetAttributes(PRUint32 aCount, const char **aAttrs)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void addAttribute (in string aAttribute); */
NS_IMETHODIMP nsLDAPURL::AddAttribute(const char *aAttribute)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void removeAttribute (in string aAttribute); */
NS_IMETHODIMP nsLDAPURL::RemoveAttribute(const char *aAttribute)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* boolean hasAttribute (in string aAttribute); */
NS_IMETHODIMP nsLDAPURL::HasAttribute(const char *aAttribute, PRBool *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute long scope; */
NS_IMETHODIMP nsLDAPURL::GetScope(PRInt32 *aScope)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsLDAPURL::SetScope(PRInt32 aScope)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute AUTF8String filter; */
NS_IMETHODIMP nsLDAPURL::GetFilter(nsACString & aFilter)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsLDAPURL::SetFilter(const nsACString & aFilter)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute unsigned long options; */
NS_IMETHODIMP nsLDAPURL::GetOptions(PRUint32 *aOptions)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsLDAPURL::SetOptions(PRUint32 aOptions)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsILDAPURL_h__ */
