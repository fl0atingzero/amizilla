/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM nsILDAPConnection.idl
 */

#ifndef __gen_nsILDAPConnection_h__
#define __gen_nsILDAPConnection_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif
class nsILDAPOperation; /* forward declaration */

class nsILDAPMessageListener; /* forward declaration */


/* starting interface:    nsILDAPConnection */
#define NS_ILDAPCONNECTION_IID_STR "337ad2fe-1dd2-11b2-89f8-aae1221ec86c"

#define NS_ILDAPCONNECTION_IID \
  {0x337ad2fe, 0x1dd2, 0x11b2, \
    { 0x89, 0xf8, 0xaa, 0xe1, 0x22, 0x1e, 0xc8, 0x6c }}

class NS_NO_VTABLE nsILDAPConnection : public nsISupports {
 public: 

  NS_DEFINE_STATIC_IID_ACCESSOR(NS_ILDAPCONNECTION_IID)

  /**
     * the string version of lderrno
     */
  /* readonly attribute wstring errorString; */
  NS_IMETHOD GetErrorString(PRUnichar * *aErrorString) = 0;

  /**
     * DN to bind as.  use the init() method to set this.
     *
     * @exception NS_ERROR_OUT_OF_MEMORY
     */
  /* readonly attribute AUTF8String bindName; */
  NS_IMETHOD GetBindName(nsACString & aBindName) = 0;

  /**
     * private parameter (anything caller desires)
     */
  /* attribute nsISupports closure; */
  NS_IMETHOD GetClosure(nsISupports * *aClosure) = 0;
  NS_IMETHOD SetClosure(nsISupports * aClosure) = 0;

  /** 
     * Set up the connection.  Note that init() must be called on a thread
     * that already has an nsIEventQueue.
     *
     * @param aHost             server name for ldap_init()
     * @param aPort             server port number for ldap_init()
     *                          -1 == default port (389)
     * @param aSSL              use SSL on this connection?
     * @param aBindName         DN to bind as
     * @param aMessageListener  Callback for DNS resolution completion
     * @param aClosure          private parameter (anything caller desires)
     *
     * @exception NS_ERROR_ILLEGAL_VALUE        null pointer passed in
     * @exception NS_ERROR_OUT_OF_MEMORY        ran out of memory
     * @exception NS_ERROR_OFFLINE              we are in off-line mode
     * @exception NS_ERROR_FAILURE              
     * @exception NS_ERROR_UNEXPECTED           internal error
     */
  /* void init (in string aHost, in short aPort, in boolean aSSL, in AUTF8String aBindName, in nsILDAPMessageListener aMessageListener, in nsISupports aClosure); */
  NS_IMETHOD Init(const char *aHost, PRInt16 aPort, PRBool aSSL, const nsACString & aBindName, nsILDAPMessageListener *aMessageListener, nsISupports *aClosure) = 0;

  /**
     * Get information about the last error that occured on this connection.
     *
     * @param matched   if the server is returning LDAP_NO_SUCH_OBJECT, 
     *                  LDAP_ALIAS_PROBLEM, LDAP_INVALID_DN_SYNTAX, 
     *                  or LDAP_ALIAS_DEREF_PROBLEM, this will contain
     *                  the portion of DN that matches the entry that is 
     *                  closest to the requested entry
     *
     * @param s         additional error information from the server
     * 
     * @return          the error code, as defined in nsILDAPErrors.idl
     */
  /* long getLdErrno (out AUTF8String matched, out AUTF8String s); */
  NS_IMETHOD GetLdErrno(nsACString & matched, nsACString & s, PRInt32 *_retval) = 0;

};

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSILDAPCONNECTION \
  NS_IMETHOD GetErrorString(PRUnichar * *aErrorString); \
  NS_IMETHOD GetBindName(nsACString & aBindName); \
  NS_IMETHOD GetClosure(nsISupports * *aClosure); \
  NS_IMETHOD SetClosure(nsISupports * aClosure); \
  NS_IMETHOD Init(const char *aHost, PRInt16 aPort, PRBool aSSL, const nsACString & aBindName, nsILDAPMessageListener *aMessageListener, nsISupports *aClosure); \
  NS_IMETHOD GetLdErrno(nsACString & matched, nsACString & s, PRInt32 *_retval); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSILDAPCONNECTION(_to) \
  NS_IMETHOD GetErrorString(PRUnichar * *aErrorString) { return _to GetErrorString(aErrorString); } \
  NS_IMETHOD GetBindName(nsACString & aBindName) { return _to GetBindName(aBindName); } \
  NS_IMETHOD GetClosure(nsISupports * *aClosure) { return _to GetClosure(aClosure); } \
  NS_IMETHOD SetClosure(nsISupports * aClosure) { return _to SetClosure(aClosure); } \
  NS_IMETHOD Init(const char *aHost, PRInt16 aPort, PRBool aSSL, const nsACString & aBindName, nsILDAPMessageListener *aMessageListener, nsISupports *aClosure) { return _to Init(aHost, aPort, aSSL, aBindName, aMessageListener, aClosure); } \
  NS_IMETHOD GetLdErrno(nsACString & matched, nsACString & s, PRInt32 *_retval) { return _to GetLdErrno(matched, s, _retval); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSILDAPCONNECTION(_to) \
  NS_IMETHOD GetErrorString(PRUnichar * *aErrorString) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetErrorString(aErrorString); } \
  NS_IMETHOD GetBindName(nsACString & aBindName) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetBindName(aBindName); } \
  NS_IMETHOD GetClosure(nsISupports * *aClosure) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetClosure(aClosure); } \
  NS_IMETHOD SetClosure(nsISupports * aClosure) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetClosure(aClosure); } \
  NS_IMETHOD Init(const char *aHost, PRInt16 aPort, PRBool aSSL, const nsACString & aBindName, nsILDAPMessageListener *aMessageListener, nsISupports *aClosure) { return !_to ? NS_ERROR_NULL_POINTER : _to->Init(aHost, aPort, aSSL, aBindName, aMessageListener, aClosure); } \
  NS_IMETHOD GetLdErrno(nsACString & matched, nsACString & s, PRInt32 *_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetLdErrno(matched, s, _retval); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsLDAPConnection : public nsILDAPConnection
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSILDAPCONNECTION

  nsLDAPConnection();
  virtual ~nsLDAPConnection();
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsLDAPConnection, nsILDAPConnection)

nsLDAPConnection::nsLDAPConnection()
{
  /* member initializers and constructor code */
}

nsLDAPConnection::~nsLDAPConnection()
{
  /* destructor code */
}

/* readonly attribute wstring errorString; */
NS_IMETHODIMP nsLDAPConnection::GetErrorString(PRUnichar * *aErrorString)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute AUTF8String bindName; */
NS_IMETHODIMP nsLDAPConnection::GetBindName(nsACString & aBindName)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute nsISupports closure; */
NS_IMETHODIMP nsLDAPConnection::GetClosure(nsISupports * *aClosure)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsLDAPConnection::SetClosure(nsISupports * aClosure)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void init (in string aHost, in short aPort, in boolean aSSL, in AUTF8String aBindName, in nsILDAPMessageListener aMessageListener, in nsISupports aClosure); */
NS_IMETHODIMP nsLDAPConnection::Init(const char *aHost, PRInt16 aPort, PRBool aSSL, const nsACString & aBindName, nsILDAPMessageListener *aMessageListener, nsISupports *aClosure)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long getLdErrno (out AUTF8String matched, out AUTF8String s); */
NS_IMETHODIMP nsLDAPConnection::GetLdErrno(nsACString & matched, nsACString & s, PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsILDAPConnection_h__ */
