/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM nsPIXPIStubHook.idl
 */

#ifndef __gen_nsPIXPIStubHook_h__
#define __gen_nsPIXPIStubHook_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif
class nsIFile; /* forward declaration */


/* starting interface:    nsPIXPIStubHook */
#define NS_PIXPISTUBHOOK_IID_STR "089929f0-4ed9-11d3-abdd-000064657374"

#define NS_PIXPISTUBHOOK_IID \
  {0x089929f0, 0x4ed9, 0x11d3, \
    { 0xab, 0xdd, 0x00, 0x00, 0x64, 0x65, 0x73, 0x74 }}

/**
 * nsPIXPIStubHook
 *
 * Used by the Install Wizard to point at the eventual target dir and
 * override the default assumption that the wizard itself is the program.
 */
class NS_NO_VTABLE nsPIXPIStubHook : public nsISupports {
 public: 

  NS_DEFINE_STATIC_IID_ACCESSOR(NS_PIXPISTUBHOOK_IID)

  /* void StubInitialize (in nsIFile dir, in string logName); */
  NS_IMETHOD StubInitialize(nsIFile *dir, const char *logName) = 0;

};

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSPIXPISTUBHOOK \
  NS_IMETHOD StubInitialize(nsIFile *dir, const char *logName); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSPIXPISTUBHOOK(_to) \
  NS_IMETHOD StubInitialize(nsIFile *dir, const char *logName) { return _to StubInitialize(dir, logName); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSPIXPISTUBHOOK(_to) \
  NS_IMETHOD StubInitialize(nsIFile *dir, const char *logName) { return !_to ? NS_ERROR_NULL_POINTER : _to->StubInitialize(dir, logName); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class _MYCLASS_ : public nsPIXPIStubHook
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSPIXPISTUBHOOK

  _MYCLASS_();
  virtual ~_MYCLASS_();
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(_MYCLASS_, nsPIXPIStubHook)

_MYCLASS_::_MYCLASS_()
{
  /* member initializers and constructor code */
}

_MYCLASS_::~_MYCLASS_()
{
  /* destructor code */
}

/* void StubInitialize (in nsIFile dir, in string logName); */
NS_IMETHODIMP _MYCLASS_::StubInitialize(nsIFile *dir, const char *logName)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsPIXPIStubHook_h__ */
