/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM nsPIXPIProxy.idl
 */

#ifndef __gen_nsPIXPIProxy_h__
#define __gen_nsPIXPIProxy_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif

/* starting interface:    nsPIXPIProxy */
#define NS_PIXPIPROXY_IID_STR "6f9d2890-167d-11d5-8daf-000064657374"

#define NS_PIXPIPROXY_IID \
  {0x6f9d2890, 0x167d, 0x11d5, \
    { 0x8d, 0xaf, 0x00, 0x00, 0x64, 0x65, 0x73, 0x74 }}

/**
 * nsPIXPIProxy
 *
 * Used to handle miscellaneous things that XPInstall needs to perform
 * over on the main UI thread.
 */
class NS_NO_VTABLE nsPIXPIProxy : public nsISupports {
 public: 

  NS_DEFINE_STATIC_IID_ACCESSOR(NS_PIXPIPROXY_IID)

  /* void refreshPlugins (in boolean reloadPages); */
  NS_IMETHOD RefreshPlugins(PRBool reloadPages) = 0;

  /* void notifyRestartNeeded (); */
  NS_IMETHOD NotifyRestartNeeded(void) = 0;

  /* void alert (in wstring title, in wstring text); */
  NS_IMETHOD Alert(const PRUnichar *title, const PRUnichar *text) = 0;

  /* boolean confirm (in wstring title, in wstring text); */
  NS_IMETHOD Confirm(const PRUnichar *title, const PRUnichar *text, PRBool *_retval) = 0;

};

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSPIXPIPROXY \
  NS_IMETHOD RefreshPlugins(PRBool reloadPages); \
  NS_IMETHOD NotifyRestartNeeded(void); \
  NS_IMETHOD Alert(const PRUnichar *title, const PRUnichar *text); \
  NS_IMETHOD Confirm(const PRUnichar *title, const PRUnichar *text, PRBool *_retval); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSPIXPIPROXY(_to) \
  NS_IMETHOD RefreshPlugins(PRBool reloadPages) { return _to RefreshPlugins(reloadPages); } \
  NS_IMETHOD NotifyRestartNeeded(void) { return _to NotifyRestartNeeded(); } \
  NS_IMETHOD Alert(const PRUnichar *title, const PRUnichar *text) { return _to Alert(title, text); } \
  NS_IMETHOD Confirm(const PRUnichar *title, const PRUnichar *text, PRBool *_retval) { return _to Confirm(title, text, _retval); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSPIXPIPROXY(_to) \
  NS_IMETHOD RefreshPlugins(PRBool reloadPages) { return !_to ? NS_ERROR_NULL_POINTER : _to->RefreshPlugins(reloadPages); } \
  NS_IMETHOD NotifyRestartNeeded(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->NotifyRestartNeeded(); } \
  NS_IMETHOD Alert(const PRUnichar *title, const PRUnichar *text) { return !_to ? NS_ERROR_NULL_POINTER : _to->Alert(title, text); } \
  NS_IMETHOD Confirm(const PRUnichar *title, const PRUnichar *text, PRBool *_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->Confirm(title, text, _retval); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class _MYCLASS_ : public nsPIXPIProxy
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSPIXPIPROXY

  _MYCLASS_();
  virtual ~_MYCLASS_();
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(_MYCLASS_, nsPIXPIProxy)

_MYCLASS_::_MYCLASS_()
{
  /* member initializers and constructor code */
}

_MYCLASS_::~_MYCLASS_()
{
  /* destructor code */
}

/* void refreshPlugins (in boolean reloadPages); */
NS_IMETHODIMP _MYCLASS_::RefreshPlugins(PRBool reloadPages)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void notifyRestartNeeded (); */
NS_IMETHODIMP _MYCLASS_::NotifyRestartNeeded()
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void alert (in wstring title, in wstring text); */
NS_IMETHODIMP _MYCLASS_::Alert(const PRUnichar *title, const PRUnichar *text)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* boolean confirm (in wstring title, in wstring text); */
NS_IMETHODIMP _MYCLASS_::Confirm(const PRUnichar *title, const PRUnichar *text, PRBool *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsPIXPIProxy_h__ */
