/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM nsIBrowserHistory.idl
 */

#ifndef __gen_nsIBrowserHistory_h__
#define __gen_nsIBrowserHistory_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif

/* starting interface:    nsIBrowserHistory */
#define NS_IBROWSERHISTORY_IID_STR "1a9129f7-2490-49d1-ba54-196ddb848ddb"

#define NS_IBROWSERHISTORY_IID \
  {0x1a9129f7, 0x2490, 0x49d1, \
    { 0xba, 0x54, 0x19, 0x6d, 0xdb, 0x84, 0x8d, 0xdb }}

class NS_NO_VTABLE nsIBrowserHistory : public nsISupports {
 public: 

  NS_DEFINE_STATIC_IID_ACCESSOR(NS_IBROWSERHISTORY_IID)

  /**
     * count
     * The number of entries in global history
     */
  /* readonly attribute PRUint32 count; */
  NS_IMETHOD GetCount(PRUint32 *aCount) = 0;

  /**
     * setPageTitle
     * set the page title for the given url. Ignores urls that are not
     * already in the history
     */
  /* void setPageTitle (in string aURL, in wstring aTitle); */
  NS_IMETHOD SetPageTitle(const char *aURL, const PRUnichar *aTitle) = 0;

  /**
     * removePage
     * Remove the specified page from the global history
     */
  /* void removePage (in string aURL); */
  NS_IMETHOD RemovePage(const char *aURL) = 0;

  /**
     * removePagesFromHost
     * Remove all pages from the given host.
     * If aEntireDomain is true, will assume aHost is a domain,
     * and remove all pages from the entire domain.
     */
  /* void removePagesFromHost (in string aHost, in boolean aEntireDomain); */
  NS_IMETHOD RemovePagesFromHost(const char *aHost, PRBool aEntireDomain) = 0;

  /**
     * removeAllPages
     * Remove all pages from global history
     */
  /* void removeAllPages (); */
  NS_IMETHOD RemoveAllPages(void) = 0;

  /**
     * lastPageVisited
     * the most recently visited page
     */
  /* readonly attribute string lastPageVisited; */
  NS_IMETHOD GetLastPageVisited(char * *aLastPageVisited) = 0;

  /**
     * hidePage
     * Hide the specified URL from being enumerated (and thus
     * displayed in the UI)
     *
     * if the page hasn't been visited yet, then it will be added
     * as if it was visited, and then marked as hidden
     */
  /* void hidePage (in string url); */
  NS_IMETHOD HidePage(const char *url) = 0;

  /**
     * markPageAsTyped
     * Designate the url as having been explicitly typed in by
     * the user, so it's okay to be an autocomplete result.
     */
  /* void markPageAsTyped (in string url); */
  NS_IMETHOD MarkPageAsTyped(const char *url) = 0;

};

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSIBROWSERHISTORY \
  NS_IMETHOD GetCount(PRUint32 *aCount); \
  NS_IMETHOD SetPageTitle(const char *aURL, const PRUnichar *aTitle); \
  NS_IMETHOD RemovePage(const char *aURL); \
  NS_IMETHOD RemovePagesFromHost(const char *aHost, PRBool aEntireDomain); \
  NS_IMETHOD RemoveAllPages(void); \
  NS_IMETHOD GetLastPageVisited(char * *aLastPageVisited); \
  NS_IMETHOD HidePage(const char *url); \
  NS_IMETHOD MarkPageAsTyped(const char *url); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSIBROWSERHISTORY(_to) \
  NS_IMETHOD GetCount(PRUint32 *aCount) { return _to GetCount(aCount); } \
  NS_IMETHOD SetPageTitle(const char *aURL, const PRUnichar *aTitle) { return _to SetPageTitle(aURL, aTitle); } \
  NS_IMETHOD RemovePage(const char *aURL) { return _to RemovePage(aURL); } \
  NS_IMETHOD RemovePagesFromHost(const char *aHost, PRBool aEntireDomain) { return _to RemovePagesFromHost(aHost, aEntireDomain); } \
  NS_IMETHOD RemoveAllPages(void) { return _to RemoveAllPages(); } \
  NS_IMETHOD GetLastPageVisited(char * *aLastPageVisited) { return _to GetLastPageVisited(aLastPageVisited); } \
  NS_IMETHOD HidePage(const char *url) { return _to HidePage(url); } \
  NS_IMETHOD MarkPageAsTyped(const char *url) { return _to MarkPageAsTyped(url); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSIBROWSERHISTORY(_to) \
  NS_IMETHOD GetCount(PRUint32 *aCount) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetCount(aCount); } \
  NS_IMETHOD SetPageTitle(const char *aURL, const PRUnichar *aTitle) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetPageTitle(aURL, aTitle); } \
  NS_IMETHOD RemovePage(const char *aURL) { return !_to ? NS_ERROR_NULL_POINTER : _to->RemovePage(aURL); } \
  NS_IMETHOD RemovePagesFromHost(const char *aHost, PRBool aEntireDomain) { return !_to ? NS_ERROR_NULL_POINTER : _to->RemovePagesFromHost(aHost, aEntireDomain); } \
  NS_IMETHOD RemoveAllPages(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->RemoveAllPages(); } \
  NS_IMETHOD GetLastPageVisited(char * *aLastPageVisited) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetLastPageVisited(aLastPageVisited); } \
  NS_IMETHOD HidePage(const char *url) { return !_to ? NS_ERROR_NULL_POINTER : _to->HidePage(url); } \
  NS_IMETHOD MarkPageAsTyped(const char *url) { return !_to ? NS_ERROR_NULL_POINTER : _to->MarkPageAsTyped(url); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsBrowserHistory : public nsIBrowserHistory
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIBROWSERHISTORY

  nsBrowserHistory();
  virtual ~nsBrowserHistory();
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsBrowserHistory, nsIBrowserHistory)

nsBrowserHistory::nsBrowserHistory()
{
  /* member initializers and constructor code */
}

nsBrowserHistory::~nsBrowserHistory()
{
  /* destructor code */
}

/* readonly attribute PRUint32 count; */
NS_IMETHODIMP nsBrowserHistory::GetCount(PRUint32 *aCount)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void setPageTitle (in string aURL, in wstring aTitle); */
NS_IMETHODIMP nsBrowserHistory::SetPageTitle(const char *aURL, const PRUnichar *aTitle)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void removePage (in string aURL); */
NS_IMETHODIMP nsBrowserHistory::RemovePage(const char *aURL)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void removePagesFromHost (in string aHost, in boolean aEntireDomain); */
NS_IMETHODIMP nsBrowserHistory::RemovePagesFromHost(const char *aHost, PRBool aEntireDomain)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void removeAllPages (); */
NS_IMETHODIMP nsBrowserHistory::RemoveAllPages()
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute string lastPageVisited; */
NS_IMETHODIMP nsBrowserHistory::GetLastPageVisited(char * *aLastPageVisited)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void hidePage (in string url); */
NS_IMETHODIMP nsBrowserHistory::HidePage(const char *url)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void markPageAsTyped (in string url); */
NS_IMETHODIMP nsBrowserHistory::MarkPageAsTyped(const char *url)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif

#define NS_GLOBALHISTORY_AUTOCOMPLETE_CONTRACTID \
    "@mozilla.org/autocompleteSession;1?type=history"

#endif /* __gen_nsIBrowserHistory_h__ */
