/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM nsISearchService.idl
 */

#ifndef __gen_nsISearchService_h__
#define __gen_nsISearchService_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

#ifndef __gen_nsIRDFDataSource_h__
#include "nsIRDFDataSource.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif
class nsIUnicodeDecoder; /* forward declaration */


/* starting interface:    nsILocalSearchService */
#define NS_ILOCALSEARCHSERVICE_IID_STR "1222e6f0-a5e3-11d2-8b7c-00805f8a7db6"

#define NS_ILOCALSEARCHSERVICE_IID \
  {0x1222e6f0, 0xa5e3, 0x11d2, \
    { 0x8b, 0x7c, 0x00, 0x80, 0x5f, 0x8a, 0x7d, 0xb6 }}

class NS_NO_VTABLE nsILocalSearchService : public nsISupports {
 public: 

  NS_DEFINE_STATIC_IID_ACCESSOR(NS_ILOCALSEARCHSERVICE_IID)

};

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSILOCALSEARCHSERVICE \
  /* no methods! */

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSILOCALSEARCHSERVICE(_to) \
  /* no methods! */

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSILOCALSEARCHSERVICE(_to) \
  /* no methods! */

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsLocalSearchService : public nsILocalSearchService
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSILOCALSEARCHSERVICE

  nsLocalSearchService();
  virtual ~nsLocalSearchService();
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsLocalSearchService, nsILocalSearchService)

nsLocalSearchService::nsLocalSearchService()
{
  /* member initializers and constructor code */
}

nsLocalSearchService::~nsLocalSearchService()
{
  /* destructor code */
}

/* End of implementation class template. */
#endif


/* starting interface:    nsIInternetSearchService */
#define NS_IINTERNETSEARCHSERVICE_IID_STR "6bd1d803-1c67-11d3-9820-ed1b357eb3c4"

#define NS_IINTERNETSEARCHSERVICE_IID \
  {0x6bd1d803, 0x1c67, 0x11d3, \
    { 0x98, 0x20, 0xed, 0x1b, 0x35, 0x7e, 0xb3, 0xc4 }}

class NS_NO_VTABLE nsIInternetSearchService : public nsISupports {
 public: 

  NS_DEFINE_STATIC_IID_ACCESSOR(NS_IINTERNETSEARCHSERVICE_IID)

  enum { kHaveNext = 1U };

  enum { kHavePrev = 2U };

  /* string GetInternetSearchURL (in string searchEngineURI, in wstring searchStr, in short direction, in unsigned short pageNumber, out unsigned short whichButtons); */
  NS_IMETHOD GetInternetSearchURL(const char *searchEngineURI, const PRUnichar *searchStr, PRInt16 direction, PRUint16 pageNumber, PRUint16 *whichButtons, char **_retval) = 0;

  /* void RememberLastSearchText (in wstring escapedSearchStr); */
  NS_IMETHOD RememberLastSearchText(const PRUnichar *escapedSearchStr) = 0;

  /* boolean FindInternetSearchResults (in string url); */
  NS_IMETHOD FindInternetSearchResults(const char *url, PRBool *_retval) = 0;

  /* void Stop (); */
  NS_IMETHOD Stop(void) = 0;

  /* void ClearResults (in boolean flushLastSearchRef); */
  NS_IMETHOD ClearResults(PRBool flushLastSearchRef) = 0;

  /* void ClearResultSearchSites (); */
  NS_IMETHOD ClearResultSearchSites(void) = 0;

  /* nsIRDFDataSource GetCategoryDataSource (); */
  NS_IMETHOD GetCategoryDataSource(nsIRDFDataSource **_retval) = 0;

  /* void AddSearchEngine (in string engineURL, in string iconURL, in wstring suggestedTitle, in wstring suggestedCategory); */
  NS_IMETHOD AddSearchEngine(const char *engineURL, const char *iconURL, const PRUnichar *suggestedTitle, const PRUnichar *suggestedCategory) = 0;

};

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSIINTERNETSEARCHSERVICE \
  NS_IMETHOD GetInternetSearchURL(const char *searchEngineURI, const PRUnichar *searchStr, PRInt16 direction, PRUint16 pageNumber, PRUint16 *whichButtons, char **_retval); \
  NS_IMETHOD RememberLastSearchText(const PRUnichar *escapedSearchStr); \
  NS_IMETHOD FindInternetSearchResults(const char *url, PRBool *_retval); \
  NS_IMETHOD Stop(void); \
  NS_IMETHOD ClearResults(PRBool flushLastSearchRef); \
  NS_IMETHOD ClearResultSearchSites(void); \
  NS_IMETHOD GetCategoryDataSource(nsIRDFDataSource **_retval); \
  NS_IMETHOD AddSearchEngine(const char *engineURL, const char *iconURL, const PRUnichar *suggestedTitle, const PRUnichar *suggestedCategory); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSIINTERNETSEARCHSERVICE(_to) \
  NS_IMETHOD GetInternetSearchURL(const char *searchEngineURI, const PRUnichar *searchStr, PRInt16 direction, PRUint16 pageNumber, PRUint16 *whichButtons, char **_retval) { return _to GetInternetSearchURL(searchEngineURI, searchStr, direction, pageNumber, whichButtons, _retval); } \
  NS_IMETHOD RememberLastSearchText(const PRUnichar *escapedSearchStr) { return _to RememberLastSearchText(escapedSearchStr); } \
  NS_IMETHOD FindInternetSearchResults(const char *url, PRBool *_retval) { return _to FindInternetSearchResults(url, _retval); } \
  NS_IMETHOD Stop(void) { return _to Stop(); } \
  NS_IMETHOD ClearResults(PRBool flushLastSearchRef) { return _to ClearResults(flushLastSearchRef); } \
  NS_IMETHOD ClearResultSearchSites(void) { return _to ClearResultSearchSites(); } \
  NS_IMETHOD GetCategoryDataSource(nsIRDFDataSource **_retval) { return _to GetCategoryDataSource(_retval); } \
  NS_IMETHOD AddSearchEngine(const char *engineURL, const char *iconURL, const PRUnichar *suggestedTitle, const PRUnichar *suggestedCategory) { return _to AddSearchEngine(engineURL, iconURL, suggestedTitle, suggestedCategory); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSIINTERNETSEARCHSERVICE(_to) \
  NS_IMETHOD GetInternetSearchURL(const char *searchEngineURI, const PRUnichar *searchStr, PRInt16 direction, PRUint16 pageNumber, PRUint16 *whichButtons, char **_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetInternetSearchURL(searchEngineURI, searchStr, direction, pageNumber, whichButtons, _retval); } \
  NS_IMETHOD RememberLastSearchText(const PRUnichar *escapedSearchStr) { return !_to ? NS_ERROR_NULL_POINTER : _to->RememberLastSearchText(escapedSearchStr); } \
  NS_IMETHOD FindInternetSearchResults(const char *url, PRBool *_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->FindInternetSearchResults(url, _retval); } \
  NS_IMETHOD Stop(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->Stop(); } \
  NS_IMETHOD ClearResults(PRBool flushLastSearchRef) { return !_to ? NS_ERROR_NULL_POINTER : _to->ClearResults(flushLastSearchRef); } \
  NS_IMETHOD ClearResultSearchSites(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->ClearResultSearchSites(); } \
  NS_IMETHOD GetCategoryDataSource(nsIRDFDataSource **_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetCategoryDataSource(_retval); } \
  NS_IMETHOD AddSearchEngine(const char *engineURL, const char *iconURL, const PRUnichar *suggestedTitle, const PRUnichar *suggestedCategory) { return !_to ? NS_ERROR_NULL_POINTER : _to->AddSearchEngine(engineURL, iconURL, suggestedTitle, suggestedCategory); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsInternetSearchService : public nsIInternetSearchService
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIINTERNETSEARCHSERVICE

  nsInternetSearchService();
  virtual ~nsInternetSearchService();
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsInternetSearchService, nsIInternetSearchService)

nsInternetSearchService::nsInternetSearchService()
{
  /* member initializers and constructor code */
}

nsInternetSearchService::~nsInternetSearchService()
{
  /* destructor code */
}

/* string GetInternetSearchURL (in string searchEngineURI, in wstring searchStr, in short direction, in unsigned short pageNumber, out unsigned short whichButtons); */
NS_IMETHODIMP nsInternetSearchService::GetInternetSearchURL(const char *searchEngineURI, const PRUnichar *searchStr, PRInt16 direction, PRUint16 pageNumber, PRUint16 *whichButtons, char **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void RememberLastSearchText (in wstring escapedSearchStr); */
NS_IMETHODIMP nsInternetSearchService::RememberLastSearchText(const PRUnichar *escapedSearchStr)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* boolean FindInternetSearchResults (in string url); */
NS_IMETHODIMP nsInternetSearchService::FindInternetSearchResults(const char *url, PRBool *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void Stop (); */
NS_IMETHODIMP nsInternetSearchService::Stop()
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void ClearResults (in boolean flushLastSearchRef); */
NS_IMETHODIMP nsInternetSearchService::ClearResults(PRBool flushLastSearchRef)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void ClearResultSearchSites (); */
NS_IMETHODIMP nsInternetSearchService::ClearResultSearchSites()
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* nsIRDFDataSource GetCategoryDataSource (); */
NS_IMETHODIMP nsInternetSearchService::GetCategoryDataSource(nsIRDFDataSource **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void AddSearchEngine (in string engineURL, in string iconURL, in wstring suggestedTitle, in wstring suggestedCategory); */
NS_IMETHODIMP nsInternetSearchService::AddSearchEngine(const char *engineURL, const char *iconURL, const PRUnichar *suggestedTitle, const PRUnichar *suggestedCategory)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


/* starting interface:    nsIInternetSearchContext */
#define NS_IINTERNETSEARCHCONTEXT_IID_STR "ac0c0781-ab71-11d3-a652-b09b68feee44"

#define NS_IINTERNETSEARCHCONTEXT_IID \
  {0xac0c0781, 0xab71, 0x11d3, \
    { 0xa6, 0x52, 0xb0, 0x9b, 0x68, 0xfe, 0xee, 0x44 }}

class NS_NO_VTABLE nsIInternetSearchContext : public nsISupports {
 public: 

  NS_DEFINE_STATIC_IID_ACCESSOR(NS_IINTERNETSEARCHCONTEXT_IID)

  enum { WEB_SEARCH_CONTEXT = 1U };

  enum { ENGINE_DOWNLOAD_CONTEXT = 2U };

  enum { ICON_DOWNLOAD_CONTEXT = 3U };

  enum { ENGINE_UPDATE_CONTEXT = 4U };

  enum { ICON_UPDATE_CONTEXT = 5U };

  /* readonly attribute unsigned long ContextType; */
  NS_IMETHOD GetContextType(PRUint32 *aContextType) = 0;

  /* nsIUnicodeDecoder GetUnicodeDecoder (); */
  NS_IMETHOD GetUnicodeDecoder(nsIUnicodeDecoder **_retval) = 0;

  /* nsIRDFResource GetParent (); */
  NS_IMETHOD GetParent(nsIRDFResource **_retval) = 0;

  /* nsIRDFResource GetEngine (); */
  NS_IMETHOD GetEngine(nsIRDFResource **_retval) = 0;

  /* void GetHintConst ([shared] out wstring buffer); */
  NS_IMETHOD GetHintConst(const PRUnichar **buffer) = 0;

  /* void AppendBytes (in string buffer, in long numBytes); */
  NS_IMETHOD AppendBytes(const char *buffer, PRInt32 numBytes) = 0;

  /* void AppendUnicodeBytes (in wstring buffer, in long numUniBytes); */
  NS_IMETHOD AppendUnicodeBytes(const PRUnichar *buffer, PRInt32 numUniBytes) = 0;

  /* long GetBufferLength (); */
  NS_IMETHOD GetBufferLength(PRInt32 *_retval) = 0;

  /* void GetBufferConst ([shared] out wstring buffer); */
  NS_IMETHOD GetBufferConst(const PRUnichar **buffer) = 0;

  /* void Truncate (); */
  NS_IMETHOD Truncate(void) = 0;

};

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSIINTERNETSEARCHCONTEXT \
  NS_IMETHOD GetContextType(PRUint32 *aContextType); \
  NS_IMETHOD GetUnicodeDecoder(nsIUnicodeDecoder **_retval); \
  NS_IMETHOD GetParent(nsIRDFResource **_retval); \
  NS_IMETHOD GetEngine(nsIRDFResource **_retval); \
  NS_IMETHOD GetHintConst(const PRUnichar **buffer); \
  NS_IMETHOD AppendBytes(const char *buffer, PRInt32 numBytes); \
  NS_IMETHOD AppendUnicodeBytes(const PRUnichar *buffer, PRInt32 numUniBytes); \
  NS_IMETHOD GetBufferLength(PRInt32 *_retval); \
  NS_IMETHOD GetBufferConst(const PRUnichar **buffer); \
  NS_IMETHOD Truncate(void); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSIINTERNETSEARCHCONTEXT(_to) \
  NS_IMETHOD GetContextType(PRUint32 *aContextType) { return _to GetContextType(aContextType); } \
  NS_IMETHOD GetUnicodeDecoder(nsIUnicodeDecoder **_retval) { return _to GetUnicodeDecoder(_retval); } \
  NS_IMETHOD GetParent(nsIRDFResource **_retval) { return _to GetParent(_retval); } \
  NS_IMETHOD GetEngine(nsIRDFResource **_retval) { return _to GetEngine(_retval); } \
  NS_IMETHOD GetHintConst(const PRUnichar **buffer) { return _to GetHintConst(buffer); } \
  NS_IMETHOD AppendBytes(const char *buffer, PRInt32 numBytes) { return _to AppendBytes(buffer, numBytes); } \
  NS_IMETHOD AppendUnicodeBytes(const PRUnichar *buffer, PRInt32 numUniBytes) { return _to AppendUnicodeBytes(buffer, numUniBytes); } \
  NS_IMETHOD GetBufferLength(PRInt32 *_retval) { return _to GetBufferLength(_retval); } \
  NS_IMETHOD GetBufferConst(const PRUnichar **buffer) { return _to GetBufferConst(buffer); } \
  NS_IMETHOD Truncate(void) { return _to Truncate(); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSIINTERNETSEARCHCONTEXT(_to) \
  NS_IMETHOD GetContextType(PRUint32 *aContextType) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetContextType(aContextType); } \
  NS_IMETHOD GetUnicodeDecoder(nsIUnicodeDecoder **_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetUnicodeDecoder(_retval); } \
  NS_IMETHOD GetParent(nsIRDFResource **_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetParent(_retval); } \
  NS_IMETHOD GetEngine(nsIRDFResource **_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetEngine(_retval); } \
  NS_IMETHOD GetHintConst(const PRUnichar **buffer) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetHintConst(buffer); } \
  NS_IMETHOD AppendBytes(const char *buffer, PRInt32 numBytes) { return !_to ? NS_ERROR_NULL_POINTER : _to->AppendBytes(buffer, numBytes); } \
  NS_IMETHOD AppendUnicodeBytes(const PRUnichar *buffer, PRInt32 numUniBytes) { return !_to ? NS_ERROR_NULL_POINTER : _to->AppendUnicodeBytes(buffer, numUniBytes); } \
  NS_IMETHOD GetBufferLength(PRInt32 *_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetBufferLength(_retval); } \
  NS_IMETHOD GetBufferConst(const PRUnichar **buffer) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetBufferConst(buffer); } \
  NS_IMETHOD Truncate(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->Truncate(); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsInternetSearchContext : public nsIInternetSearchContext
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIINTERNETSEARCHCONTEXT

  nsInternetSearchContext();
  virtual ~nsInternetSearchContext();
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsInternetSearchContext, nsIInternetSearchContext)

nsInternetSearchContext::nsInternetSearchContext()
{
  /* member initializers and constructor code */
}

nsInternetSearchContext::~nsInternetSearchContext()
{
  /* destructor code */
}

/* readonly attribute unsigned long ContextType; */
NS_IMETHODIMP nsInternetSearchContext::GetContextType(PRUint32 *aContextType)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* nsIUnicodeDecoder GetUnicodeDecoder (); */
NS_IMETHODIMP nsInternetSearchContext::GetUnicodeDecoder(nsIUnicodeDecoder **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* nsIRDFResource GetParent (); */
NS_IMETHODIMP nsInternetSearchContext::GetParent(nsIRDFResource **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* nsIRDFResource GetEngine (); */
NS_IMETHODIMP nsInternetSearchContext::GetEngine(nsIRDFResource **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void GetHintConst ([shared] out wstring buffer); */
NS_IMETHODIMP nsInternetSearchContext::GetHintConst(const PRUnichar **buffer)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void AppendBytes (in string buffer, in long numBytes); */
NS_IMETHODIMP nsInternetSearchContext::AppendBytes(const char *buffer, PRInt32 numBytes)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void AppendUnicodeBytes (in wstring buffer, in long numUniBytes); */
NS_IMETHODIMP nsInternetSearchContext::AppendUnicodeBytes(const PRUnichar *buffer, PRInt32 numUniBytes)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long GetBufferLength (); */
NS_IMETHODIMP nsInternetSearchContext::GetBufferLength(PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void GetBufferConst ([shared] out wstring buffer); */
NS_IMETHODIMP nsInternetSearchContext::GetBufferConst(const PRUnichar **buffer)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void Truncate (); */
NS_IMETHODIMP nsInternetSearchContext::Truncate()
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif

#define NS_IINTERNETSEARCHDATASOURCECALLBACK_IID \
{ 0x88774583, 0x1edd, 0x11d3, { 0x98, 0x20, 0xbf, 0x1b, 0xe7, 0x7e, 0x61, 0xc4 } }
#define NS_IINTERNETSEARCHDATAOURCE_IID \
{ 0x6bd1d803, 0x1c67, 0x11d3, { 0x98, 0x20, 0xed, 0x1b, 0x35, 0x7e, 0xb3, 0xc4 } }
#define NS_ILOCALSEARCHDATASOURCE_IID \
{ 0x1222e6f0, 0xa5e3, 0x11d2, { 0x8b, 0x7c, 0x00, 0x80, 0x5f, 0x8a, 0x7d, 0xb6 } }
#define NS_LOCALSEARCH_SERVICE_CONTRACTID \
    "@mozilla.org/browser/localsearch-service;1"
#define NS_LOCALSEARCH_DATASOURCE_CONTRACTID \
    "@mozilla.org/rdf/datasource;1?name=localsearch"
#define NS_INTERNETSEARCH_SERVICE_CONTRACTID \
    "@mozilla.org/browser/internetsearch-service;1"
#define NS_INTERNETSEARCH_DATASOURCE_CONTRACTID \
    "@mozilla.org/rdf/datasource;1?name=internetsearch"

#endif /* __gen_nsISearchService_h__ */
