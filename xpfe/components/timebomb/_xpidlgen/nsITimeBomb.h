/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM nsITimeBomb.idl
 */

#ifndef __gen_nsITimeBomb_h__
#define __gen_nsITimeBomb_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif

/* starting interface:    nsITimeBomb */
#define NS_ITIMEBOMB_IID_STR "93fabc84-e1bf-11d3-ac71-00c04fa0d26b"

#define NS_ITIMEBOMB_IID \
  {0x93fabc84, 0xe1bf, 0x11d3, \
    { 0xac, 0x71, 0x00, 0xc0, 0x4f, 0xa0, 0xd2, 0x6b }}

class NS_NO_VTABLE nsITimeBomb : public nsISupports {
 public: 

  NS_DEFINE_STATIC_IID_ACCESSOR(NS_ITIMEBOMB_IID)

  /* void init (); */
  NS_IMETHOD Init(void) = 0;

  /* void checkWithUI (out boolean expired); */
  NS_IMETHOD CheckWithUI(PRBool *expired) = 0;

  /* void loadUpdateURL (); */
  NS_IMETHOD LoadUpdateURL(void) = 0;

  /* readonly attribute boolean expired; */
  NS_IMETHOD GetExpired(PRBool *aExpired) = 0;

  /* readonly attribute boolean warned; */
  NS_IMETHOD GetWarned(PRBool *aWarned) = 0;

  /* readonly attribute boolean enabled; */
  NS_IMETHOD GetEnabled(PRBool *aEnabled) = 0;

  /* readonly attribute PRTime expirationTime; */
  NS_IMETHOD GetExpirationTime(PRTime *aExpirationTime) = 0;

  /* readonly attribute PRTime warningTime; */
  NS_IMETHOD GetWarningTime(PRTime *aWarningTime) = 0;

  /* readonly attribute PRTime buildTime; */
  NS_IMETHOD GetBuildTime(PRTime *aBuildTime) = 0;

  /* readonly attribute PRTime firstLaunch; */
  NS_IMETHOD GetFirstLaunch(PRTime *aFirstLaunch) = 0;

  /* readonly attribute PRInt64 warningOffset; */
  NS_IMETHOD GetWarningOffset(PRInt64 *aWarningOffset) = 0;

  /* readonly attribute PRInt64 expirationOffset; */
  NS_IMETHOD GetExpirationOffset(PRInt64 *aExpirationOffset) = 0;

  /* readonly attribute string timebombURL; */
  NS_IMETHOD GetTimebombURL(char * *aTimebombURL) = 0;

};

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSITIMEBOMB \
  NS_IMETHOD Init(void); \
  NS_IMETHOD CheckWithUI(PRBool *expired); \
  NS_IMETHOD LoadUpdateURL(void); \
  NS_IMETHOD GetExpired(PRBool *aExpired); \
  NS_IMETHOD GetWarned(PRBool *aWarned); \
  NS_IMETHOD GetEnabled(PRBool *aEnabled); \
  NS_IMETHOD GetExpirationTime(PRTime *aExpirationTime); \
  NS_IMETHOD GetWarningTime(PRTime *aWarningTime); \
  NS_IMETHOD GetBuildTime(PRTime *aBuildTime); \
  NS_IMETHOD GetFirstLaunch(PRTime *aFirstLaunch); \
  NS_IMETHOD GetWarningOffset(PRInt64 *aWarningOffset); \
  NS_IMETHOD GetExpirationOffset(PRInt64 *aExpirationOffset); \
  NS_IMETHOD GetTimebombURL(char * *aTimebombURL); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSITIMEBOMB(_to) \
  NS_IMETHOD Init(void) { return _to Init(); } \
  NS_IMETHOD CheckWithUI(PRBool *expired) { return _to CheckWithUI(expired); } \
  NS_IMETHOD LoadUpdateURL(void) { return _to LoadUpdateURL(); } \
  NS_IMETHOD GetExpired(PRBool *aExpired) { return _to GetExpired(aExpired); } \
  NS_IMETHOD GetWarned(PRBool *aWarned) { return _to GetWarned(aWarned); } \
  NS_IMETHOD GetEnabled(PRBool *aEnabled) { return _to GetEnabled(aEnabled); } \
  NS_IMETHOD GetExpirationTime(PRTime *aExpirationTime) { return _to GetExpirationTime(aExpirationTime); } \
  NS_IMETHOD GetWarningTime(PRTime *aWarningTime) { return _to GetWarningTime(aWarningTime); } \
  NS_IMETHOD GetBuildTime(PRTime *aBuildTime) { return _to GetBuildTime(aBuildTime); } \
  NS_IMETHOD GetFirstLaunch(PRTime *aFirstLaunch) { return _to GetFirstLaunch(aFirstLaunch); } \
  NS_IMETHOD GetWarningOffset(PRInt64 *aWarningOffset) { return _to GetWarningOffset(aWarningOffset); } \
  NS_IMETHOD GetExpirationOffset(PRInt64 *aExpirationOffset) { return _to GetExpirationOffset(aExpirationOffset); } \
  NS_IMETHOD GetTimebombURL(char * *aTimebombURL) { return _to GetTimebombURL(aTimebombURL); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSITIMEBOMB(_to) \
  NS_IMETHOD Init(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->Init(); } \
  NS_IMETHOD CheckWithUI(PRBool *expired) { return !_to ? NS_ERROR_NULL_POINTER : _to->CheckWithUI(expired); } \
  NS_IMETHOD LoadUpdateURL(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->LoadUpdateURL(); } \
  NS_IMETHOD GetExpired(PRBool *aExpired) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetExpired(aExpired); } \
  NS_IMETHOD GetWarned(PRBool *aWarned) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetWarned(aWarned); } \
  NS_IMETHOD GetEnabled(PRBool *aEnabled) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetEnabled(aEnabled); } \
  NS_IMETHOD GetExpirationTime(PRTime *aExpirationTime) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetExpirationTime(aExpirationTime); } \
  NS_IMETHOD GetWarningTime(PRTime *aWarningTime) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetWarningTime(aWarningTime); } \
  NS_IMETHOD GetBuildTime(PRTime *aBuildTime) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetBuildTime(aBuildTime); } \
  NS_IMETHOD GetFirstLaunch(PRTime *aFirstLaunch) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetFirstLaunch(aFirstLaunch); } \
  NS_IMETHOD GetWarningOffset(PRInt64 *aWarningOffset) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetWarningOffset(aWarningOffset); } \
  NS_IMETHOD GetExpirationOffset(PRInt64 *aExpirationOffset) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetExpirationOffset(aExpirationOffset); } \
  NS_IMETHOD GetTimebombURL(char * *aTimebombURL) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetTimebombURL(aTimebombURL); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsTimeBomb : public nsITimeBomb
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSITIMEBOMB

  nsTimeBomb();
  virtual ~nsTimeBomb();
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsTimeBomb, nsITimeBomb)

nsTimeBomb::nsTimeBomb()
{
  /* member initializers and constructor code */
}

nsTimeBomb::~nsTimeBomb()
{
  /* destructor code */
}

/* void init (); */
NS_IMETHODIMP nsTimeBomb::Init()
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void checkWithUI (out boolean expired); */
NS_IMETHODIMP nsTimeBomb::CheckWithUI(PRBool *expired)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void loadUpdateURL (); */
NS_IMETHODIMP nsTimeBomb::LoadUpdateURL()
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute boolean expired; */
NS_IMETHODIMP nsTimeBomb::GetExpired(PRBool *aExpired)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute boolean warned; */
NS_IMETHODIMP nsTimeBomb::GetWarned(PRBool *aWarned)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute boolean enabled; */
NS_IMETHODIMP nsTimeBomb::GetEnabled(PRBool *aEnabled)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute PRTime expirationTime; */
NS_IMETHODIMP nsTimeBomb::GetExpirationTime(PRTime *aExpirationTime)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute PRTime warningTime; */
NS_IMETHODIMP nsTimeBomb::GetWarningTime(PRTime *aWarningTime)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute PRTime buildTime; */
NS_IMETHODIMP nsTimeBomb::GetBuildTime(PRTime *aBuildTime)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute PRTime firstLaunch; */
NS_IMETHODIMP nsTimeBomb::GetFirstLaunch(PRTime *aFirstLaunch)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute PRInt64 warningOffset; */
NS_IMETHODIMP nsTimeBomb::GetWarningOffset(PRInt64 *aWarningOffset)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute PRInt64 expirationOffset; */
NS_IMETHODIMP nsTimeBomb::GetExpirationOffset(PRInt64 *aExpirationOffset)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute string timebombURL; */
NS_IMETHODIMP nsTimeBomb::GetTimebombURL(char * *aTimebombURL)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif

#define NS_TIMEBOMB_CONTRACTID "@mozilla.org/timebomb;1"

#endif /* __gen_nsITimeBomb_h__ */
