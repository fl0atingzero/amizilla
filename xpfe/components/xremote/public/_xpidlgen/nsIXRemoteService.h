/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM nsIXRemoteService.idl
 */

#ifndef __gen_nsIXRemoteService_h__
#define __gen_nsIXRemoteService_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif
class nsIDOMWindowInternal; /* forward declaration */

class nsIWidget; /* forward declaration */


/* starting interface:    nsIXRemoteService */
#define NS_IXREMOTESERVICE_IID_STR "510c0946-1dd2-11b2-b210-f5031abff3f0"

#define NS_IXREMOTESERVICE_IID \
  {0x510c0946, 0x1dd2, 0x11b2, \
    { 0xb2, 0x10, 0xf5, 0x03, 0x1a, 0xbf, 0xf3, 0xf0 }}

class NS_NO_VTABLE nsIXRemoteService : public nsISupports {
 public: 

  NS_DEFINE_STATIC_IID_ACCESSOR(NS_IXREMOTESERVICE_IID)

  /* [noscript] void startup (); */
  NS_IMETHOD Startup(void) = 0;

  /* [noscript] void shutdown (); */
  NS_IMETHOD Shutdown(void) = 0;

  /* [noscript] void parseCommand (in nsIWidget aWidget, in string aCommand, out string aResponse); */
  NS_IMETHOD ParseCommand(nsIWidget *aWidget, const char *aCommand, char **aResponse) = 0;

  /* void addBrowserInstance (in nsIDOMWindowInternal aBrowser); */
  NS_IMETHOD AddBrowserInstance(nsIDOMWindowInternal *aBrowser) = 0;

  /* void removeBrowserInstance (in nsIDOMWindowInternal aBrowser); */
  NS_IMETHOD RemoveBrowserInstance(nsIDOMWindowInternal *aBrowser) = 0;

};

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSIXREMOTESERVICE \
  NS_IMETHOD Startup(void); \
  NS_IMETHOD Shutdown(void); \
  NS_IMETHOD ParseCommand(nsIWidget *aWidget, const char *aCommand, char **aResponse); \
  NS_IMETHOD AddBrowserInstance(nsIDOMWindowInternal *aBrowser); \
  NS_IMETHOD RemoveBrowserInstance(nsIDOMWindowInternal *aBrowser); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSIXREMOTESERVICE(_to) \
  NS_IMETHOD Startup(void) { return _to Startup(); } \
  NS_IMETHOD Shutdown(void) { return _to Shutdown(); } \
  NS_IMETHOD ParseCommand(nsIWidget *aWidget, const char *aCommand, char **aResponse) { return _to ParseCommand(aWidget, aCommand, aResponse); } \
  NS_IMETHOD AddBrowserInstance(nsIDOMWindowInternal *aBrowser) { return _to AddBrowserInstance(aBrowser); } \
  NS_IMETHOD RemoveBrowserInstance(nsIDOMWindowInternal *aBrowser) { return _to RemoveBrowserInstance(aBrowser); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSIXREMOTESERVICE(_to) \
  NS_IMETHOD Startup(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->Startup(); } \
  NS_IMETHOD Shutdown(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->Shutdown(); } \
  NS_IMETHOD ParseCommand(nsIWidget *aWidget, const char *aCommand, char **aResponse) { return !_to ? NS_ERROR_NULL_POINTER : _to->ParseCommand(aWidget, aCommand, aResponse); } \
  NS_IMETHOD AddBrowserInstance(nsIDOMWindowInternal *aBrowser) { return !_to ? NS_ERROR_NULL_POINTER : _to->AddBrowserInstance(aBrowser); } \
  NS_IMETHOD RemoveBrowserInstance(nsIDOMWindowInternal *aBrowser) { return !_to ? NS_ERROR_NULL_POINTER : _to->RemoveBrowserInstance(aBrowser); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsXRemoteService : public nsIXRemoteService
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIXREMOTESERVICE

  nsXRemoteService();
  virtual ~nsXRemoteService();
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsXRemoteService, nsIXRemoteService)

nsXRemoteService::nsXRemoteService()
{
  /* member initializers and constructor code */
}

nsXRemoteService::~nsXRemoteService()
{
  /* destructor code */
}

/* [noscript] void startup (); */
NS_IMETHODIMP nsXRemoteService::Startup()
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* [noscript] void shutdown (); */
NS_IMETHODIMP nsXRemoteService::Shutdown()
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* [noscript] void parseCommand (in nsIWidget aWidget, in string aCommand, out string aResponse); */
NS_IMETHODIMP nsXRemoteService::ParseCommand(nsIWidget *aWidget, const char *aCommand, char **aResponse)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void addBrowserInstance (in nsIDOMWindowInternal aBrowser); */
NS_IMETHODIMP nsXRemoteService::AddBrowserInstance(nsIDOMWindowInternal *aBrowser)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void removeBrowserInstance (in nsIDOMWindowInternal aBrowser); */
NS_IMETHODIMP nsXRemoteService::RemoveBrowserInstance(nsIDOMWindowInternal *aBrowser)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif

#define NS_IXREMOTESERVICE_CONTRACTID "@mozilla.org/browser/xremoteservice;1"
#define NS_IXREMOTESERVICE_CLASSNAME  "Mozilla XRemote Service"

#endif /* __gen_nsIXRemoteService_h__ */
