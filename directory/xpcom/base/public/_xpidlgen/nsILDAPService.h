/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM nsILDAPService.idl
 */

#ifndef __gen_nsILDAPService_h__
#define __gen_nsILDAPService_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif
class nsILDAPServer; /* forward declaration */

class nsILDAPConnection; /* forward declaration */

class nsILDAPMessageListener; /* forward declaration */


/* starting interface:    nsILDAPService */
#define NS_ILDAPSERVICE_IID_STR "f73cc6c1-2301-484b-94a5-8885bca106d1"

#define NS_ILDAPSERVICE_IID \
  {0xf73cc6c1, 0x2301, 0x484b, \
    { 0x94, 0xa5, 0x88, 0x85, 0xbc, 0xa1, 0x06, 0xd1 }}

/**
 * This interface provides an LDAP connection management service.
 * It's used to cache already established LDAP connections, as well
 * as reaping unused connections after a certain time period. This
 * is done completely asynchronously, using callback functions.
 */
class NS_NO_VTABLE nsILDAPService : public nsISupports {
 public: 

  NS_DEFINE_STATIC_IID_ACCESSOR(NS_ILDAPSERVICE_IID)

  /**
     * Add a (possibly) new LDAP server entry to the service. A
     * server entry holds information about the host, port and
     * other components of the LDAP URL, as well as information
     * used for binding a connection to the LDAP server.
     *
     * An LDAP Server entry (nsILDAPServer) contains the URL,
     * user credentials, and other information related to the actual
     * server itself. It is used for connecting, binding, rebinding,
     * setting timeouts and so forth.
     *
     * @param aServer          an nsILDAPServer object
     *
     * @exception NS_ERROR_FAILURE          the server has already been
     *                                      added to the service
     * @exception NS_ERROR_NULL_POINTER     NULL pointer
     * @exception NS_ERROR_OUT_OF_MEMORY    ran out of memory
     */
  /* void addServer (in nsILDAPServer aServer); */
  NS_IMETHOD AddServer(nsILDAPServer *aServer) = 0;

  /**
     * Mark an LDAP server, in the Service, as a candidate for
     * deletion. If there are still leases ("users") of this server,
     * the operation fails.
     *
     * @param aKey             unique key identifying the server entry
     *
     * @exception NS_ERROR_FAILURE          either the server doesn't
     *                                      exist, or there are still
     *                                      leases oustanding
     */
  /* void deleteServer (in wstring aKey); */
  NS_IMETHOD DeleteServer(const PRUnichar *aKey) = 0;

  /**
     * Get the nsILDAPServer object for the specified server entry
     * in the service.
     *
     * @param aKey             unique key identifying the server entry
     *
     * @exception NS_ERROR_FAILURE          there is no server registered
     *                                      in the service with this key
     * @exception NS_ERROR_NULL_POINTER     NULL pointer
     */
  /* nsILDAPServer getServer (in wstring aKey); */
  NS_IMETHOD GetServer(const PRUnichar *aKey, nsILDAPServer **_retval) = 0;

  /**
     * Request a connection from the service, asynchronously. If there is
     * one "cached" already, we will actually call the callback function
     * before returning from this function. This might be considered a bug,
     * but for now be aware of this (see Bugzilla bug #75989).
     *
     * Calling this method does not increment the leases on this connection,
     * you'll have to use the getConnection() method to actually get the
     * connection itself (presumably from the callback/listener object).
     * The listener needs to implement nsILDAPMessageListener, providing
     * the OnLDAPMessage() method.
     * 
     * @param aKey             unique key identifying the server entry
     * @param aMessageListener the listener object, which we will call
     *                         when the LDAP bind message is available
     *
     * @exception NS_ERROR_FAILURE          there is no server registered
     *                                      in the service with this key,
     *                                      or we were unable to get a
     *                                      connection properly to the server
     * @exception NS_ERROR_NOT_AVAILABLE	couldn't create connection thread
     * @exception NS_ERROR_OUT_OF_MEMORY    ran out of memory
     * @exception NS_ERROR_UNEXPECTED       unknown or unexpected error...
     */
  /* void requestConnection (in wstring aKey, in nsILDAPMessageListener aListener); */
  NS_IMETHOD RequestConnection(const PRUnichar *aKey, nsILDAPMessageListener *aListener) = 0;

  /**
     * This is the nsLDAPConnection object related to this server.
     * This does increase the lease counter on the object, so you have
     * to call the releaseConnection() method to return it. It is
     * important that you do this in matching pairs, and that you do
     * not keep any dangling references to an object around after you
     * have called the releaseConnection() method.
     *
     * @param aKey             unique key identifying the server entry
     *
     * @exception NS_ERROR_FAILURE          there is no server registered
     *                                      in the service with this key
     * @exception NS_ERROR_NULL_POINTER     NULL pointer
     */
  /* nsILDAPConnection getConnection (in wstring aKey); */
  NS_IMETHOD GetConnection(const PRUnichar *aKey, nsILDAPConnection **_retval) = 0;

  /**
     * Release the lease on a (cached) LDAP connection, making it a
     * potential candidate for disconnection. Note that this will not
     * delete the actual LDAP server entry in the service, it's still
     * registered and can be used in future calls to requestConnection().
     *
     * This API might be deprecated in the future, once we figure out how
     * to use weak references to support our special needs for reference
     * counting. For the time being, it is vital that you call this function
     * when you're done with a Connection, and that you do not keep any
     * copies of the Connection object lingering around.
     *
     * @param aKey             unique key identifying the server entry
     *
     * @exception NS_ERROR_FAILURE          there is no server registered
     *                                      in the service with this key
     * @exception NS_ERROR_OUT_OF_MEMORY    ran out of memory
     */
  /* void releaseConnection (in wstring aKey); */
  NS_IMETHOD ReleaseConnection(const PRUnichar *aKey) = 0;

  /**
     * If we detect that a connection is broken (server disconnected us,
     * or any other problem with the link), we need to try to reestablish
     * the connection. This is very similar to requestConnection(),
     * except you use this when detecting an error with a connection
     * that is being cached.
     *
     * @param aKey             unique key identifying the server entry
     * @param aMessageListener the listener object, which we will call
     *                         when the LDAP bind message is available
     *
     * @exception NS_ERROR_FAILURE          there is no server registered
     *                                      in the service with this key,
     *                                      or we were unable to get a
     *                                      connection properly to the server
     * @exception NS_ERROR_NOT_AVAILABLE	couldn't create connection thread
     * @exception NS_ERROR_OUT_OF_MEMORY    ran out of memory
     * @exception NS_ERROR_UNEXPECTED       unknown or unexpected error...
     */
  /* void reconnectConnection (in wstring aKey, in nsILDAPMessageListener aListener); */
  NS_IMETHOD ReconnectConnection(const PRUnichar *aKey, nsILDAPMessageListener *aListener) = 0;

  /**
     * Generates and returns an LDAP search filter by substituting
     * aValue, aAttr, aPrefix, and aSuffix into aPattern.
     *
     * The only good documentation I'm aware of for this function is
     * at <http://docs.iplanet.com/docs/manuals/dirsdk/csdk41/html/filter.htm>
     * and 
     * <http://docs.iplanet.com/docs/manuals/dirsdk/csdk41/html/function.htm#17835>
     * Unfortunately, this does not currently seem to be available
     * under any open source license, so I can't include that
     * documentation here in the doxygen comments.
     *
     * @param aMaxSize   maximum size (in char) of string to be 
     *                   created and returned (including final \0)
     * @param aPattern   pattern to be used for the filter
     * @param aPrefix    prefix to prepend to the filter
     * @param aSuffix    suffix to be appended to the filer
     * @param aAttr      replacement for %a in the pattern
     * @param aValue     replacement for %v in the pattern
     *  
     * @exception NS_ERROR_INVALID_ARG      invalid parameter passed in
     * @exception NS_ERROR_OUT_OF_MEMORY    allocation failed
     * @exception NS_ERROR_NOT_AVAILABLE    filter longer than maxsiz chars
     * @exception NS_ERROR_UNEXPECTED       ldap_create_filter returned
     *                                      unexpected error code
     */
  /* AUTF8String createFilter (in unsigned long aMaxSize, in AUTF8String aPattern, in AUTF8String aPrefix, in AUTF8String aSuffix, in AUTF8String aAttr, in AUTF8String aValue); */
  NS_IMETHOD CreateFilter(PRUint32 aMaxSize, const nsACString & aPattern, const nsACString & aPrefix, const nsACString & aSuffix, const nsACString & aAttr, const nsACString & aValue, nsACString & _retval) = 0;

};

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSILDAPSERVICE \
  NS_IMETHOD AddServer(nsILDAPServer *aServer); \
  NS_IMETHOD DeleteServer(const PRUnichar *aKey); \
  NS_IMETHOD GetServer(const PRUnichar *aKey, nsILDAPServer **_retval); \
  NS_IMETHOD RequestConnection(const PRUnichar *aKey, nsILDAPMessageListener *aListener); \
  NS_IMETHOD GetConnection(const PRUnichar *aKey, nsILDAPConnection **_retval); \
  NS_IMETHOD ReleaseConnection(const PRUnichar *aKey); \
  NS_IMETHOD ReconnectConnection(const PRUnichar *aKey, nsILDAPMessageListener *aListener); \
  NS_IMETHOD CreateFilter(PRUint32 aMaxSize, const nsACString & aPattern, const nsACString & aPrefix, const nsACString & aSuffix, const nsACString & aAttr, const nsACString & aValue, nsACString & _retval); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSILDAPSERVICE(_to) \
  NS_IMETHOD AddServer(nsILDAPServer *aServer) { return _to AddServer(aServer); } \
  NS_IMETHOD DeleteServer(const PRUnichar *aKey) { return _to DeleteServer(aKey); } \
  NS_IMETHOD GetServer(const PRUnichar *aKey, nsILDAPServer **_retval) { return _to GetServer(aKey, _retval); } \
  NS_IMETHOD RequestConnection(const PRUnichar *aKey, nsILDAPMessageListener *aListener) { return _to RequestConnection(aKey, aListener); } \
  NS_IMETHOD GetConnection(const PRUnichar *aKey, nsILDAPConnection **_retval) { return _to GetConnection(aKey, _retval); } \
  NS_IMETHOD ReleaseConnection(const PRUnichar *aKey) { return _to ReleaseConnection(aKey); } \
  NS_IMETHOD ReconnectConnection(const PRUnichar *aKey, nsILDAPMessageListener *aListener) { return _to ReconnectConnection(aKey, aListener); } \
  NS_IMETHOD CreateFilter(PRUint32 aMaxSize, const nsACString & aPattern, const nsACString & aPrefix, const nsACString & aSuffix, const nsACString & aAttr, const nsACString & aValue, nsACString & _retval) { return _to CreateFilter(aMaxSize, aPattern, aPrefix, aSuffix, aAttr, aValue, _retval); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSILDAPSERVICE(_to) \
  NS_IMETHOD AddServer(nsILDAPServer *aServer) { return !_to ? NS_ERROR_NULL_POINTER : _to->AddServer(aServer); } \
  NS_IMETHOD DeleteServer(const PRUnichar *aKey) { return !_to ? NS_ERROR_NULL_POINTER : _to->DeleteServer(aKey); } \
  NS_IMETHOD GetServer(const PRUnichar *aKey, nsILDAPServer **_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetServer(aKey, _retval); } \
  NS_IMETHOD RequestConnection(const PRUnichar *aKey, nsILDAPMessageListener *aListener) { return !_to ? NS_ERROR_NULL_POINTER : _to->RequestConnection(aKey, aListener); } \
  NS_IMETHOD GetConnection(const PRUnichar *aKey, nsILDAPConnection **_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetConnection(aKey, _retval); } \
  NS_IMETHOD ReleaseConnection(const PRUnichar *aKey) { return !_to ? NS_ERROR_NULL_POINTER : _to->ReleaseConnection(aKey); } \
  NS_IMETHOD ReconnectConnection(const PRUnichar *aKey, nsILDAPMessageListener *aListener) { return !_to ? NS_ERROR_NULL_POINTER : _to->ReconnectConnection(aKey, aListener); } \
  NS_IMETHOD CreateFilter(PRUint32 aMaxSize, const nsACString & aPattern, const nsACString & aPrefix, const nsACString & aSuffix, const nsACString & aAttr, const nsACString & aValue, nsACString & _retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->CreateFilter(aMaxSize, aPattern, aPrefix, aSuffix, aAttr, aValue, _retval); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsLDAPService : public nsILDAPService
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSILDAPSERVICE

  nsLDAPService();
  virtual ~nsLDAPService();
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsLDAPService, nsILDAPService)

nsLDAPService::nsLDAPService()
{
  /* member initializers and constructor code */
}

nsLDAPService::~nsLDAPService()
{
  /* destructor code */
}

/* void addServer (in nsILDAPServer aServer); */
NS_IMETHODIMP nsLDAPService::AddServer(nsILDAPServer *aServer)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void deleteServer (in wstring aKey); */
NS_IMETHODIMP nsLDAPService::DeleteServer(const PRUnichar *aKey)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* nsILDAPServer getServer (in wstring aKey); */
NS_IMETHODIMP nsLDAPService::GetServer(const PRUnichar *aKey, nsILDAPServer **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void requestConnection (in wstring aKey, in nsILDAPMessageListener aListener); */
NS_IMETHODIMP nsLDAPService::RequestConnection(const PRUnichar *aKey, nsILDAPMessageListener *aListener)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* nsILDAPConnection getConnection (in wstring aKey); */
NS_IMETHODIMP nsLDAPService::GetConnection(const PRUnichar *aKey, nsILDAPConnection **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void releaseConnection (in wstring aKey); */
NS_IMETHODIMP nsLDAPService::ReleaseConnection(const PRUnichar *aKey)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void reconnectConnection (in wstring aKey, in nsILDAPMessageListener aListener); */
NS_IMETHODIMP nsLDAPService::ReconnectConnection(const PRUnichar *aKey, nsILDAPMessageListener *aListener)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* AUTF8String createFilter (in unsigned long aMaxSize, in AUTF8String aPattern, in AUTF8String aPrefix, in AUTF8String aSuffix, in AUTF8String aAttr, in AUTF8String aValue); */
NS_IMETHODIMP nsLDAPService::CreateFilter(PRUint32 aMaxSize, const nsACString & aPattern, const nsACString & aPrefix, const nsACString & aSuffix, const nsACString & aAttr, const nsACString & aValue, nsACString & _retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsILDAPService_h__ */
