/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM nsILDAPServer.idl
 */

#ifndef __gen_nsILDAPServer_h__
#define __gen_nsILDAPServer_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif
class nsILDAPURL; /* forward declaration */


/* starting interface:    nsILDAPServer */
#define NS_ILDAPSERVER_IID_STR "8aa717a4-1dd2-11b2-99c7-f01e2d449ded"

#define NS_ILDAPSERVER_IID \
  {0x8aa717a4, 0x1dd2, 0x11b2, \
    { 0x99, 0xc7, 0xf0, 0x1e, 0x2d, 0x44, 0x9d, 0xed }}

/**
 * this interface provides a way to store, retrieve and manipulate
 * information related to a specific LDAP server. This includes the
 * LDAP URL, as well as certain user specific data (e.g. credentials).
 *
 * The implementation of nsILDAPService relies heavily on this
 * interface, managing all LDAP connections (nsILDAPConnection).
 * The Service manages LDAP connections (connect and disconnect etc.),
 * using the information available from these LDAP Server objects.
 */
class NS_NO_VTABLE nsILDAPServer : public nsISupports {
 public: 

  NS_DEFINE_STATIC_IID_ACCESSOR(NS_ILDAPSERVER_IID)

  /**
     * unique identifier for this server, used (typically) to identify a
     * particular server object in a list of servers. This key can be
     * any "string", but in our case it will most likely be the same
     * identifier as used in a Mozilla preferences files.
     *
     * @exception NS_ERROR_NULL_POINTER     NULL pointer to GET method
     * @exception NS_ERROR_OUT_OF_MEMORY    ran out of memory
     */
  /* attribute wstring key; */
  NS_IMETHOD GetKey(PRUnichar * *aKey) = 0;
  NS_IMETHOD SetKey(const PRUnichar * aKey) = 0;

  /**
     * the password string used to bind to this server. An empty
     * string here implies binding as anonymous.
     *
     * @exception NS_ERROR_NULL_POINTER     NULL pointer to GET method
     * @exception NS_ERROR_OUT_OF_MEMORY    ran out of memory
     */
  /* attribute AUTF8String password; */
  NS_IMETHOD GetPassword(nsACString & aPassword) = 0;
  NS_IMETHOD SetPassword(const nsACString & aPassword) = 0;

  /**
     * the user name to authenticate as. An empty string here would
     * imply binding as anonymous.
     *
     * @exception NS_ERROR_NULL_POINTER     NULL pointer to GET method
     * @exception NS_ERROR_OUT_OF_MEMORY    ran out of memory
     */
  /* attribute AUTF8String username; */
  NS_IMETHOD GetUsername(nsACString & aUsername) = 0;
  NS_IMETHOD SetUsername(const nsACString & aUsername) = 0;

  /**
     * the bind DN (Distinguished Name).
     *
     * @exception NS_ERROR_NULL_POINTER     NULL pointer to GET method
     * @exception NS_ERROR_OUT_OF_MEMORY    ran out of memory
     */
  /* attribute AUTF8String binddn; */
  NS_IMETHOD GetBinddn(nsACString & aBinddn) = 0;
  NS_IMETHOD SetBinddn(const nsACString & aBinddn) = 0;

  /** maximum number of hits we want to accept from an LDAP search
     *  operation.
     *
     * @exception NS_ERROR_NULL_POINTER     NULL pointer to GET method
     */
  /* attribute unsigned long sizelimit; */
  NS_IMETHOD GetSizelimit(PRUint32 *aSizelimit) = 0;
  NS_IMETHOD SetSizelimit(PRUint32 aSizelimit) = 0;

  /**
     * the URL for this server.
     *
     * @exception NS_ERROR_NULL_POINTER     NULL pointer to GET method
     */
  /* attribute nsILDAPURL url; */
  NS_IMETHOD GetUrl(nsILDAPURL * *aUrl) = 0;
  NS_IMETHOD SetUrl(nsILDAPURL * aUrl) = 0;

};

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSILDAPSERVER \
  NS_IMETHOD GetKey(PRUnichar * *aKey); \
  NS_IMETHOD SetKey(const PRUnichar * aKey); \
  NS_IMETHOD GetPassword(nsACString & aPassword); \
  NS_IMETHOD SetPassword(const nsACString & aPassword); \
  NS_IMETHOD GetUsername(nsACString & aUsername); \
  NS_IMETHOD SetUsername(const nsACString & aUsername); \
  NS_IMETHOD GetBinddn(nsACString & aBinddn); \
  NS_IMETHOD SetBinddn(const nsACString & aBinddn); \
  NS_IMETHOD GetSizelimit(PRUint32 *aSizelimit); \
  NS_IMETHOD SetSizelimit(PRUint32 aSizelimit); \
  NS_IMETHOD GetUrl(nsILDAPURL * *aUrl); \
  NS_IMETHOD SetUrl(nsILDAPURL * aUrl); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSILDAPSERVER(_to) \
  NS_IMETHOD GetKey(PRUnichar * *aKey) { return _to GetKey(aKey); } \
  NS_IMETHOD SetKey(const PRUnichar * aKey) { return _to SetKey(aKey); } \
  NS_IMETHOD GetPassword(nsACString & aPassword) { return _to GetPassword(aPassword); } \
  NS_IMETHOD SetPassword(const nsACString & aPassword) { return _to SetPassword(aPassword); } \
  NS_IMETHOD GetUsername(nsACString & aUsername) { return _to GetUsername(aUsername); } \
  NS_IMETHOD SetUsername(const nsACString & aUsername) { return _to SetUsername(aUsername); } \
  NS_IMETHOD GetBinddn(nsACString & aBinddn) { return _to GetBinddn(aBinddn); } \
  NS_IMETHOD SetBinddn(const nsACString & aBinddn) { return _to SetBinddn(aBinddn); } \
  NS_IMETHOD GetSizelimit(PRUint32 *aSizelimit) { return _to GetSizelimit(aSizelimit); } \
  NS_IMETHOD SetSizelimit(PRUint32 aSizelimit) { return _to SetSizelimit(aSizelimit); } \
  NS_IMETHOD GetUrl(nsILDAPURL * *aUrl) { return _to GetUrl(aUrl); } \
  NS_IMETHOD SetUrl(nsILDAPURL * aUrl) { return _to SetUrl(aUrl); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSILDAPSERVER(_to) \
  NS_IMETHOD GetKey(PRUnichar * *aKey) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetKey(aKey); } \
  NS_IMETHOD SetKey(const PRUnichar * aKey) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetKey(aKey); } \
  NS_IMETHOD GetPassword(nsACString & aPassword) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetPassword(aPassword); } \
  NS_IMETHOD SetPassword(const nsACString & aPassword) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetPassword(aPassword); } \
  NS_IMETHOD GetUsername(nsACString & aUsername) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetUsername(aUsername); } \
  NS_IMETHOD SetUsername(const nsACString & aUsername) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetUsername(aUsername); } \
  NS_IMETHOD GetBinddn(nsACString & aBinddn) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetBinddn(aBinddn); } \
  NS_IMETHOD SetBinddn(const nsACString & aBinddn) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetBinddn(aBinddn); } \
  NS_IMETHOD GetSizelimit(PRUint32 *aSizelimit) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetSizelimit(aSizelimit); } \
  NS_IMETHOD SetSizelimit(PRUint32 aSizelimit) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetSizelimit(aSizelimit); } \
  NS_IMETHOD GetUrl(nsILDAPURL * *aUrl) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetUrl(aUrl); } \
  NS_IMETHOD SetUrl(nsILDAPURL * aUrl) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetUrl(aUrl); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsLDAPServer : public nsILDAPServer
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSILDAPSERVER

  nsLDAPServer();
  virtual ~nsLDAPServer();
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsLDAPServer, nsILDAPServer)

nsLDAPServer::nsLDAPServer()
{
  /* member initializers and constructor code */
}

nsLDAPServer::~nsLDAPServer()
{
  /* destructor code */
}

/* attribute wstring key; */
NS_IMETHODIMP nsLDAPServer::GetKey(PRUnichar * *aKey)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsLDAPServer::SetKey(const PRUnichar * aKey)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute AUTF8String password; */
NS_IMETHODIMP nsLDAPServer::GetPassword(nsACString & aPassword)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsLDAPServer::SetPassword(const nsACString & aPassword)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute AUTF8String username; */
NS_IMETHODIMP nsLDAPServer::GetUsername(nsACString & aUsername)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsLDAPServer::SetUsername(const nsACString & aUsername)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute AUTF8String binddn; */
NS_IMETHODIMP nsLDAPServer::GetBinddn(nsACString & aBinddn)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsLDAPServer::SetBinddn(const nsACString & aBinddn)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute unsigned long sizelimit; */
NS_IMETHODIMP nsLDAPServer::GetSizelimit(PRUint32 *aSizelimit)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsLDAPServer::SetSizelimit(PRUint32 aSizelimit)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute nsILDAPURL url; */
NS_IMETHODIMP nsLDAPServer::GetUrl(nsILDAPURL * *aUrl)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsLDAPServer::SetUrl(nsILDAPURL * aUrl)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsILDAPServer_h__ */
