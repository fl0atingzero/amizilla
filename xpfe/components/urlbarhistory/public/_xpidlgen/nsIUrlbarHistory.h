/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM nsIUrlbarHistory.idl
 */

#ifndef __gen_nsIUrlbarHistory_h__
#define __gen_nsIUrlbarHistory_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

#ifndef __gen_nsIFactory_h__
#include "nsIFactory.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif
#define NS_URLBARHISTORY_CID \
{0x74254499, 0x171a, 0x11d4, {0x98, 0x70, 0x0, 0xc0, 0x4f, 0xa0, 0x2f, 0x40}}
#define NS_URLBARHISTORY_CONTRACTID "@mozilla.org/browser/urlbarhistory;1"
#define NS_URLBARAUTOCOMPLETE_CONTRACTID "@mozilla.org/autocompleteSession;1?type=urlbar"
#define UBHISTORY_MAX_ENTRIES = 15;

/* starting interface:    nsIUrlbarHistory */
#define NS_IURLBARHISTORY_IID_STR "74254499-171a-11d4-9870-00c04fa02f40"

#define NS_IURLBARHISTORY_IID \
  {0x74254499, 0x171a, 0x11d4, \
    { 0x98, 0x70, 0x00, 0xc0, 0x4f, 0xa0, 0x2f, 0x40 }}

class NS_NO_VTABLE nsIUrlbarHistory : public nsISupports {
 public: 

  NS_DEFINE_STATIC_IID_ACCESSOR(NS_IURLBARHISTORY_IID)

  /**
   * Get the size of the History list
   */
  /* readonly attribute long count; */
  NS_IMETHOD GetCount(PRInt32 *aCount) = 0;

  /**
   * print the History contents
   */
  /* void printHistory (); */
  NS_IMETHOD PrintHistory(void) = 0;

  /**
   * clear the History contents
   */
  /* void clearHistory (); */
  NS_IMETHOD ClearHistory(void) = 0;

};

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSIURLBARHISTORY \
  NS_IMETHOD GetCount(PRInt32 *aCount); \
  NS_IMETHOD PrintHistory(void); \
  NS_IMETHOD ClearHistory(void); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSIURLBARHISTORY(_to) \
  NS_IMETHOD GetCount(PRInt32 *aCount) { return _to GetCount(aCount); } \
  NS_IMETHOD PrintHistory(void) { return _to PrintHistory(); } \
  NS_IMETHOD ClearHistory(void) { return _to ClearHistory(); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSIURLBARHISTORY(_to) \
  NS_IMETHOD GetCount(PRInt32 *aCount) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetCount(aCount); } \
  NS_IMETHOD PrintHistory(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->PrintHistory(); } \
  NS_IMETHOD ClearHistory(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->ClearHistory(); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsUrlbarHistory : public nsIUrlbarHistory
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIURLBARHISTORY

  nsUrlbarHistory();
  virtual ~nsUrlbarHistory();
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsUrlbarHistory, nsIUrlbarHistory)

nsUrlbarHistory::nsUrlbarHistory()
{
  /* member initializers and constructor code */
}

nsUrlbarHistory::~nsUrlbarHistory()
{
  /* destructor code */
}

/* readonly attribute long count; */
NS_IMETHODIMP nsUrlbarHistory::GetCount(PRInt32 *aCount)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void printHistory (); */
NS_IMETHODIMP nsUrlbarHistory::PrintHistory()
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void clearHistory (); */
NS_IMETHODIMP nsUrlbarHistory::ClearHistory()
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsIUrlbarHistory_h__ */
