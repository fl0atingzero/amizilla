/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM nsIXPINotifier.idl
 */

#ifndef __gen_nsIXPINotifier_h__
#define __gen_nsIXPINotifier_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif

/* starting interface:    nsIXPIListener */
#define NS_IXPILISTENER_IID_STR "eea90d40-b059-11d2-915e-c12b696c9333"

#define NS_IXPILISTENER_IID \
  {0xeea90d40, 0xb059, 0x11d2, \
    { 0x91, 0x5e, 0xc1, 0x2b, 0x69, 0x6c, 0x93, 0x33 }}

class NS_NO_VTABLE nsIXPIListener : public nsISupports {
 public: 

  NS_DEFINE_STATIC_IID_ACCESSOR(NS_IXPILISTENER_IID)

  /* void onInstallStart (in wstring URL); */
  NS_IMETHOD OnInstallStart(const PRUnichar *URL) = 0;

  /* void onInstallDone (in wstring URL, in long status); */
  NS_IMETHOD OnInstallDone(const PRUnichar *URL, PRInt32 status) = 0;

  /* void onPackageNameSet (in wstring URL, in wstring UIPackageName, in wstring version); */
  NS_IMETHOD OnPackageNameSet(const PRUnichar *URL, const PRUnichar *UIPackageName, const PRUnichar *version) = 0;

  /* void onItemScheduled (in wstring message); */
  NS_IMETHOD OnItemScheduled(const PRUnichar *message) = 0;

  /* void onFinalizeProgress (in wstring message, in long itemNum, in long totNum); */
  NS_IMETHOD OnFinalizeProgress(const PRUnichar *message, PRInt32 itemNum, PRInt32 totNum) = 0;

  /* void onLogComment (in wstring comment); */
  NS_IMETHOD OnLogComment(const PRUnichar *comment) = 0;

};

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSIXPILISTENER \
  NS_IMETHOD OnInstallStart(const PRUnichar *URL); \
  NS_IMETHOD OnInstallDone(const PRUnichar *URL, PRInt32 status); \
  NS_IMETHOD OnPackageNameSet(const PRUnichar *URL, const PRUnichar *UIPackageName, const PRUnichar *version); \
  NS_IMETHOD OnItemScheduled(const PRUnichar *message); \
  NS_IMETHOD OnFinalizeProgress(const PRUnichar *message, PRInt32 itemNum, PRInt32 totNum); \
  NS_IMETHOD OnLogComment(const PRUnichar *comment); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSIXPILISTENER(_to) \
  NS_IMETHOD OnInstallStart(const PRUnichar *URL) { return _to OnInstallStart(URL); } \
  NS_IMETHOD OnInstallDone(const PRUnichar *URL, PRInt32 status) { return _to OnInstallDone(URL, status); } \
  NS_IMETHOD OnPackageNameSet(const PRUnichar *URL, const PRUnichar *UIPackageName, const PRUnichar *version) { return _to OnPackageNameSet(URL, UIPackageName, version); } \
  NS_IMETHOD OnItemScheduled(const PRUnichar *message) { return _to OnItemScheduled(message); } \
  NS_IMETHOD OnFinalizeProgress(const PRUnichar *message, PRInt32 itemNum, PRInt32 totNum) { return _to OnFinalizeProgress(message, itemNum, totNum); } \
  NS_IMETHOD OnLogComment(const PRUnichar *comment) { return _to OnLogComment(comment); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSIXPILISTENER(_to) \
  NS_IMETHOD OnInstallStart(const PRUnichar *URL) { return !_to ? NS_ERROR_NULL_POINTER : _to->OnInstallStart(URL); } \
  NS_IMETHOD OnInstallDone(const PRUnichar *URL, PRInt32 status) { return !_to ? NS_ERROR_NULL_POINTER : _to->OnInstallDone(URL, status); } \
  NS_IMETHOD OnPackageNameSet(const PRUnichar *URL, const PRUnichar *UIPackageName, const PRUnichar *version) { return !_to ? NS_ERROR_NULL_POINTER : _to->OnPackageNameSet(URL, UIPackageName, version); } \
  NS_IMETHOD OnItemScheduled(const PRUnichar *message) { return !_to ? NS_ERROR_NULL_POINTER : _to->OnItemScheduled(message); } \
  NS_IMETHOD OnFinalizeProgress(const PRUnichar *message, PRInt32 itemNum, PRInt32 totNum) { return !_to ? NS_ERROR_NULL_POINTER : _to->OnFinalizeProgress(message, itemNum, totNum); } \
  NS_IMETHOD OnLogComment(const PRUnichar *comment) { return !_to ? NS_ERROR_NULL_POINTER : _to->OnLogComment(comment); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsXPIListener : public nsIXPIListener
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIXPILISTENER

  nsXPIListener();
  virtual ~nsXPIListener();
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsXPIListener, nsIXPIListener)

nsXPIListener::nsXPIListener()
{
  /* member initializers and constructor code */
}

nsXPIListener::~nsXPIListener()
{
  /* destructor code */
}

/* void onInstallStart (in wstring URL); */
NS_IMETHODIMP nsXPIListener::OnInstallStart(const PRUnichar *URL)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void onInstallDone (in wstring URL, in long status); */
NS_IMETHODIMP nsXPIListener::OnInstallDone(const PRUnichar *URL, PRInt32 status)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void onPackageNameSet (in wstring URL, in wstring UIPackageName, in wstring version); */
NS_IMETHODIMP nsXPIListener::OnPackageNameSet(const PRUnichar *URL, const PRUnichar *UIPackageName, const PRUnichar *version)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void onItemScheduled (in wstring message); */
NS_IMETHODIMP nsXPIListener::OnItemScheduled(const PRUnichar *message)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void onFinalizeProgress (in wstring message, in long itemNum, in long totNum); */
NS_IMETHODIMP nsXPIListener::OnFinalizeProgress(const PRUnichar *message, PRInt32 itemNum, PRInt32 totNum)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void onLogComment (in wstring comment); */
NS_IMETHODIMP nsXPIListener::OnLogComment(const PRUnichar *comment)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsIXPINotifier_h__ */
