/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM nsILDAPMessageListener.idl
 */

#ifndef __gen_nsILDAPMessageListener_h__
#define __gen_nsILDAPMessageListener_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif
class nsILDAPMessage; /* forward declaration */

class nsILDAPConnection; /* forward declaration */


/* starting interface:    nsILDAPMessageListener */
#define NS_ILDAPMESSAGELISTENER_IID_STR "dc721d4b-3ff2-4387-a80c-5e29545f774a"

#define NS_ILDAPMESSAGELISTENER_IID \
  {0xdc721d4b, 0x3ff2, 0x4387, \
    { 0xa8, 0x0c, 0x5e, 0x29, 0x54, 0x5f, 0x77, 0x4a }}

/** 
 * A callback interface to be implemented by any objects that want to 
 * receive results from an nsILDAPOperation (ie nsILDAPMessages) as they
 * come in.
 */
class NS_NO_VTABLE nsILDAPMessageListener : public nsISupports {
 public: 

  NS_DEFINE_STATIC_IID_ACCESSOR(NS_ILDAPMESSAGELISTENER_IID)

  /**
     * Messages received are passed back via this function.
     *
     * @arg aMessage  The message that was returned, NULL if none was.
     *
     * XXX semantics of NULL?
     */
  /* void onLDAPMessage (in nsILDAPMessage aMessage); */
  NS_IMETHOD OnLDAPMessage(nsILDAPMessage *aMessage) = 0;

  /**
     * Notify the listener that the Init has completed, passing
     * in the results from the connection initialization. The
     * Reason for this is to allow us to do asynchronous DNS
     * lookups, preresolving hostnames.
     *
     * @arg aConn     The LDAP connection in question
     * @arg aStatus   The result from the LDAP connection init
     */
  /* void onLDAPInit (in nsILDAPConnection aConn, in nsresult aStatus); */
  NS_IMETHOD OnLDAPInit(nsILDAPConnection *aConn, nsresult aStatus) = 0;

};

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSILDAPMESSAGELISTENER \
  NS_IMETHOD OnLDAPMessage(nsILDAPMessage *aMessage); \
  NS_IMETHOD OnLDAPInit(nsILDAPConnection *aConn, nsresult aStatus); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSILDAPMESSAGELISTENER(_to) \
  NS_IMETHOD OnLDAPMessage(nsILDAPMessage *aMessage) { return _to OnLDAPMessage(aMessage); } \
  NS_IMETHOD OnLDAPInit(nsILDAPConnection *aConn, nsresult aStatus) { return _to OnLDAPInit(aConn, aStatus); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSILDAPMESSAGELISTENER(_to) \
  NS_IMETHOD OnLDAPMessage(nsILDAPMessage *aMessage) { return !_to ? NS_ERROR_NULL_POINTER : _to->OnLDAPMessage(aMessage); } \
  NS_IMETHOD OnLDAPInit(nsILDAPConnection *aConn, nsresult aStatus) { return !_to ? NS_ERROR_NULL_POINTER : _to->OnLDAPInit(aConn, aStatus); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsLDAPMessageListener : public nsILDAPMessageListener
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSILDAPMESSAGELISTENER

  nsLDAPMessageListener();
  virtual ~nsLDAPMessageListener();
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsLDAPMessageListener, nsILDAPMessageListener)

nsLDAPMessageListener::nsLDAPMessageListener()
{
  /* member initializers and constructor code */
}

nsLDAPMessageListener::~nsLDAPMessageListener()
{
  /* destructor code */
}

/* void onLDAPMessage (in nsILDAPMessage aMessage); */
NS_IMETHODIMP nsLDAPMessageListener::OnLDAPMessage(nsILDAPMessage *aMessage)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void onLDAPInit (in nsILDAPConnection aConn, in nsresult aStatus); */
NS_IMETHODIMP nsLDAPMessageListener::OnLDAPInit(nsILDAPConnection *aConn, nsresult aStatus)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsILDAPMessageListener_h__ */
