/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM nsILDAPOperation.idl
 */

#ifndef __gen_nsILDAPOperation_h__
#define __gen_nsILDAPOperation_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

#ifndef __gen_nsILDAPConnection_h__
#include "nsILDAPConnection.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif
class nsILDAPMessage; /* forward declaration */

class nsILDAPMessageListener; /* forward declaration */

typedef PRUint32 PRIntervalTime;


/* starting interface:    nsILDAPOperation */
#define NS_ILDAPOPERATION_IID_STR "fd3d413b-14b0-49c4-8348-a4fc0edba9ff"

#define NS_ILDAPOPERATION_IID \
  {0xfd3d413b, 0x14b0, 0x49c4, \
    { 0x83, 0x48, 0xa4, 0xfc, 0x0e, 0xdb, 0xa9, 0xff }}

class NS_NO_VTABLE nsILDAPOperation : public nsISupports {
 public: 

  NS_DEFINE_STATIC_IID_ACCESSOR(NS_ILDAPOPERATION_IID)

  /**
     * The connection this operation is on. 
     * 
     * @exception NS_ERROR_ILLEGAL_VALUE        a NULL pointer was passed in
     */
  /* readonly attribute nsILDAPConnection connection; */
  NS_IMETHOD GetConnection(nsILDAPConnection * *aConnection) = 0;

  /**
     * Callback for individual result messages related to this operation (set
     * by the init() method).  This is actually an nsISupports proxy object, 
     * as the callback will happen from another thread.
     * 
     * @exception NS_ERROR_ILLEGAL_VALUE        a NULL pointer was passed in
     */
  /* readonly attribute nsILDAPMessageListener messageListener; */
  NS_IMETHOD GetMessageListener(nsILDAPMessageListener * *aMessageListener) = 0;

  /**
     * The message-id associated with this operation.
     *
     * @exception NS_ERROR_ILLEGAL_VALUE        a NULL pointer was passed in
     */
  /* readonly attribute long messageID; */
  NS_IMETHOD GetMessageID(PRInt32 *aMessageID) = 0;

  /**
     * private parameter (anything caller desires)
     */
  /* attribute nsISupports closure; */
  NS_IMETHOD GetClosure(nsISupports * *aClosure) = 0;
  NS_IMETHOD SetClosure(nsISupports * aClosure) = 0;

  /**
     * No time and/or size limit specified
     */
  enum { NO_LIMIT = 0 };

  /**
     * Initializes this operation.  Must be called prior to initiating
     * any actual operations.  Note that by default, the aMessageListener
     * callbacks happen on the LDAP connection thread.  If you need them
     * to happen on the main thread (or any other thread), then you should
     * created an nsISupports proxy object and pass that in.
     *
     * @param aConnection       connection this operation should use
     * @param aMessageListener  interface used to call back the results.
     * @param aClosure          private parameter (anything caller desires)
     *
     * @exception NS_ERROR_ILLEGAL_VALUE        a NULL pointer was passed in
     * @exception NS_ERROR_UNEXPECTED           failed to get connection handle
     */
  /* void init (in nsILDAPConnection aConnection, in nsILDAPMessageListener aMessageListener, in nsISupports aClosure); */
  NS_IMETHOD Init(nsILDAPConnection *aConnection, nsILDAPMessageListener *aMessageListener, nsISupports *aClosure) = 0;

  /**
     * Asynchronously authenticate to the LDAP server.
     * 
     * @param passwd    the password used for binding; NULL for anon-binds
     *
     * @exception NS_ERROR_LDAP_ENCODING_ERROR  problem encoding bind request
     * @exception NS_ERROR_LDAP_SERVER_DOWN     server down (XXX rebinds?)
     * @exception NS_ERROR_LDAP_CONNECT_ERROR   connection failed or lost
     * @exception NS_ERROR_OUT_OF_MEMORY        ran out of memory
     * @exception NS_ERROR_UNEXPECTED           internal error
     */
  /* void simpleBind (in AUTF8String passwd); */
  NS_IMETHOD SimpleBind(const nsACString & passwd) = 0;

  /**
     * Kicks off an asynchronous search request.  The "ext" stands for 
     * "extensions", and is intended to convey that this method will
     * eventually support the extensions described in the
     * draft-ietf-ldapext-ldap-c-api-04.txt Internet Draft.
     *
     * @param aBaseDn           Base DN to search
     * @param aScope            One of SCOPE_{BASE,ONELEVEL,SUBTREE}
     * @param aFilter           Search filter
     * @param aAttrCount        Number of attributes we request (0 for all)
     * @param aAttributes       Array of strings, holding the attributes we need
     * @param aTimeOut          How long to wait
     * @param aSizeLimit        Maximum number of entries to return.
     *
     * @exception NS_ERROR_NOT_INITIALIZED
     * @exception NS_ERROR_LDAP_ENCODING_ERROR
     * @exception NS_ERROR_LDAP_SERVER_DOWN
     * @exception NS_ERROR_OUT_OF_MEMORY
     * @exception NS_ERROR_INVALID_ARG
     * @exception NS_ERROR_LDAP_NOT_SUPPORTED
     * @exception NS_ERROR_LDAP_FILTER_ERROR
     *
     * XXX doesn't currently handle LDAPControl params
     */
  /* void searchExt (in AUTF8String aBaseDn, in PRInt32 aScope, in AUTF8String aFilter, in unsigned long aAttrCount, [array, size_is (aAttrCount)] in string aAttributes, in PRIntervalTime aTimeOut, in PRInt32 aSizeLimit); */
  NS_IMETHOD SearchExt(const nsACString & aBaseDn, PRInt32 aScope, const nsACString & aFilter, PRUint32 aAttrCount, const char **aAttributes, PRIntervalTime aTimeOut, PRInt32 aSizeLimit) = 0;

  /**  
     * Cancels an async operation that is in progress.
     *
     * @exception NS_ERROR_NOT_INITIALIZED      operation not initialized
     * @exception NS_ERROR_LDAP_ENCODING_ERROR  error during BER-encoding
     * @exception NS_ERROR_LDAP_SERVER_DOWN     the LDAP server did not
     *                                          receive the request or the
     *                                          connection was lost
     * @exception NS_ERROR_OUT_OF_MEMORY        out of memory
     * @exception NS_ERROR_INVALID_ARG          invalid argument
     * @exception NS_ERROR_UNEXPECTED           internal error
     */
  /* void abandon (); */
  NS_IMETHOD Abandon(void) = 0;

};

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSILDAPOPERATION \
  NS_IMETHOD GetConnection(nsILDAPConnection * *aConnection); \
  NS_IMETHOD GetMessageListener(nsILDAPMessageListener * *aMessageListener); \
  NS_IMETHOD GetMessageID(PRInt32 *aMessageID); \
  NS_IMETHOD GetClosure(nsISupports * *aClosure); \
  NS_IMETHOD SetClosure(nsISupports * aClosure); \
  NS_IMETHOD Init(nsILDAPConnection *aConnection, nsILDAPMessageListener *aMessageListener, nsISupports *aClosure); \
  NS_IMETHOD SimpleBind(const nsACString & passwd); \
  NS_IMETHOD SearchExt(const nsACString & aBaseDn, PRInt32 aScope, const nsACString & aFilter, PRUint32 aAttrCount, const char **aAttributes, PRIntervalTime aTimeOut, PRInt32 aSizeLimit); \
  NS_IMETHOD Abandon(void); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSILDAPOPERATION(_to) \
  NS_IMETHOD GetConnection(nsILDAPConnection * *aConnection) { return _to GetConnection(aConnection); } \
  NS_IMETHOD GetMessageListener(nsILDAPMessageListener * *aMessageListener) { return _to GetMessageListener(aMessageListener); } \
  NS_IMETHOD GetMessageID(PRInt32 *aMessageID) { return _to GetMessageID(aMessageID); } \
  NS_IMETHOD GetClosure(nsISupports * *aClosure) { return _to GetClosure(aClosure); } \
  NS_IMETHOD SetClosure(nsISupports * aClosure) { return _to SetClosure(aClosure); } \
  NS_IMETHOD Init(nsILDAPConnection *aConnection, nsILDAPMessageListener *aMessageListener, nsISupports *aClosure) { return _to Init(aConnection, aMessageListener, aClosure); } \
  NS_IMETHOD SimpleBind(const nsACString & passwd) { return _to SimpleBind(passwd); } \
  NS_IMETHOD SearchExt(const nsACString & aBaseDn, PRInt32 aScope, const nsACString & aFilter, PRUint32 aAttrCount, const char **aAttributes, PRIntervalTime aTimeOut, PRInt32 aSizeLimit) { return _to SearchExt(aBaseDn, aScope, aFilter, aAttrCount, aAttributes, aTimeOut, aSizeLimit); } \
  NS_IMETHOD Abandon(void) { return _to Abandon(); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSILDAPOPERATION(_to) \
  NS_IMETHOD GetConnection(nsILDAPConnection * *aConnection) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetConnection(aConnection); } \
  NS_IMETHOD GetMessageListener(nsILDAPMessageListener * *aMessageListener) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetMessageListener(aMessageListener); } \
  NS_IMETHOD GetMessageID(PRInt32 *aMessageID) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetMessageID(aMessageID); } \
  NS_IMETHOD GetClosure(nsISupports * *aClosure) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetClosure(aClosure); } \
  NS_IMETHOD SetClosure(nsISupports * aClosure) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetClosure(aClosure); } \
  NS_IMETHOD Init(nsILDAPConnection *aConnection, nsILDAPMessageListener *aMessageListener, nsISupports *aClosure) { return !_to ? NS_ERROR_NULL_POINTER : _to->Init(aConnection, aMessageListener, aClosure); } \
  NS_IMETHOD SimpleBind(const nsACString & passwd) { return !_to ? NS_ERROR_NULL_POINTER : _to->SimpleBind(passwd); } \
  NS_IMETHOD SearchExt(const nsACString & aBaseDn, PRInt32 aScope, const nsACString & aFilter, PRUint32 aAttrCount, const char **aAttributes, PRIntervalTime aTimeOut, PRInt32 aSizeLimit) { return !_to ? NS_ERROR_NULL_POINTER : _to->SearchExt(aBaseDn, aScope, aFilter, aAttrCount, aAttributes, aTimeOut, aSizeLimit); } \
  NS_IMETHOD Abandon(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->Abandon(); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsLDAPOperation : public nsILDAPOperation
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSILDAPOPERATION

  nsLDAPOperation();
  virtual ~nsLDAPOperation();
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsLDAPOperation, nsILDAPOperation)

nsLDAPOperation::nsLDAPOperation()
{
  /* member initializers and constructor code */
}

nsLDAPOperation::~nsLDAPOperation()
{
  /* destructor code */
}

/* readonly attribute nsILDAPConnection connection; */
NS_IMETHODIMP nsLDAPOperation::GetConnection(nsILDAPConnection * *aConnection)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute nsILDAPMessageListener messageListener; */
NS_IMETHODIMP nsLDAPOperation::GetMessageListener(nsILDAPMessageListener * *aMessageListener)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute long messageID; */
NS_IMETHODIMP nsLDAPOperation::GetMessageID(PRInt32 *aMessageID)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute nsISupports closure; */
NS_IMETHODIMP nsLDAPOperation::GetClosure(nsISupports * *aClosure)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsLDAPOperation::SetClosure(nsISupports * aClosure)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void init (in nsILDAPConnection aConnection, in nsILDAPMessageListener aMessageListener, in nsISupports aClosure); */
NS_IMETHODIMP nsLDAPOperation::Init(nsILDAPConnection *aConnection, nsILDAPMessageListener *aMessageListener, nsISupports *aClosure)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void simpleBind (in AUTF8String passwd); */
NS_IMETHODIMP nsLDAPOperation::SimpleBind(const nsACString & passwd)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void searchExt (in AUTF8String aBaseDn, in PRInt32 aScope, in AUTF8String aFilter, in unsigned long aAttrCount, [array, size_is (aAttrCount)] in string aAttributes, in PRIntervalTime aTimeOut, in PRInt32 aSizeLimit); */
NS_IMETHODIMP nsLDAPOperation::SearchExt(const nsACString & aBaseDn, PRInt32 aScope, const nsACString & aFilter, PRUint32 aAttrCount, const char **aAttributes, PRIntervalTime aTimeOut, PRInt32 aSizeLimit)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void abandon (); */
NS_IMETHODIMP nsLDAPOperation::Abandon()
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsILDAPOperation_h__ */
