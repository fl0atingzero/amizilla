/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM nsISimplePluginInstance.idl
 */

#ifndef __gen_nsISimplePluginInstance_h__
#define __gen_nsISimplePluginInstance_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif

/* starting interface:    nsISimplePluginInstance */
#define NS_ISIMPLEPLUGININSTANCE_IID_STR "fa8728f0-117a-11d4-8fa5-0010a4e73d9a"

#define NS_ISIMPLEPLUGININSTANCE_IID \
  {0xfa8728f0, 0x117a, 0x11d4, \
    { 0x8f, 0xa5, 0x00, 0x10, 0xa4, 0xe7, 0x3d, 0x9a }}

class NS_NO_VTABLE nsISimplePluginInstance : public nsISupports {
 public: 

  NS_DEFINE_STATIC_IID_ACCESSOR(NS_ISIMPLEPLUGININSTANCE_IID)

  /* attribute string text; */
  NS_IMETHOD GetText(char * *aText) = 0;
  NS_IMETHOD SetText(const char * aText) = 0;

};

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSISIMPLEPLUGININSTANCE \
  NS_IMETHOD GetText(char * *aText); \
  NS_IMETHOD SetText(const char * aText); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSISIMPLEPLUGININSTANCE(_to) \
  NS_IMETHOD GetText(char * *aText) { return _to GetText(aText); } \
  NS_IMETHOD SetText(const char * aText) { return _to SetText(aText); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSISIMPLEPLUGININSTANCE(_to) \
  NS_IMETHOD GetText(char * *aText) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetText(aText); } \
  NS_IMETHOD SetText(const char * aText) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetText(aText); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsSimplePluginInstance : public nsISimplePluginInstance
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSISIMPLEPLUGININSTANCE

  nsSimplePluginInstance();
  virtual ~nsSimplePluginInstance();
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsSimplePluginInstance, nsISimplePluginInstance)

nsSimplePluginInstance::nsSimplePluginInstance()
{
  /* member initializers and constructor code */
}

nsSimplePluginInstance::~nsSimplePluginInstance()
{
  /* destructor code */
}

/* attribute string text; */
NS_IMETHODIMP nsSimplePluginInstance::GetText(char * *aText)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsSimplePluginInstance::SetText(const char * aText)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsISimplePluginInstance_h__ */
