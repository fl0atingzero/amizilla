/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM nsILDAPAutoCompleteSession.idl
 */

#ifndef __gen_nsILDAPAutoCompleteSession_h__
#define __gen_nsILDAPAutoCompleteSession_h__


#ifndef __gen_nsIAutoCompleteSession_h__
#include "nsIAutoCompleteSession.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif
class nsILDAPURL; /* forward declaration */

class nsILDAPAutoCompFormatter; /* forward declaration */

class nsIAuthPrompt; /* forward declaration */


/* starting interface:    nsILDAPAutoCompleteSession */
#define NS_ILDAPAUTOCOMPLETESESSION_IID_STR "82b6a78e-1dd2-11b2-a3d0-876e20e7b350"

#define NS_ILDAPAUTOCOMPLETESESSION_IID \
  {0x82b6a78e, 0x1dd2, 0x11b2, \
    { 0xa3, 0xd0, 0x87, 0x6e, 0x20, 0xe7, 0xb3, 0x50 }}

/**
 * Extends nsIAutoCompleteSession to have various LDAP-specific parameters.
 * and output format.
 */
class NS_NO_VTABLE nsILDAPAutoCompleteSession : public nsIAutoCompleteSession {
 public: 

  NS_DEFINE_STATIC_IID_ACCESSOR(NS_ILDAPAUTOCOMPLETESESSION_IID)

  /**
     * A template used to construct the RFC 1960 LDAP search filter to use 
     * while autocompleting.  
     *
     * The authoritative documentation for the format in use can be found at 
     * at <http://docs.iplanet.com/docs/manuals/dirsdk/csdk41/html/filter.htm>.
     * The Linux/OpenLDAP man page for ldapfilter.conf(5) does a pretty decent
     * job as well, however.
     *
     * As of this writing, the "@mozilla.org/autocompleteSession;1?type=ldap" 
     * contractid happens to use a default value of 
     * (|(cn=%v1*%v2-*)(mail=%v1*%v2-*)(sn=%v1*%v2-*))
     *
     * @exception NS_ERROR_NULL_POINTER     NULL pointer passed to getter
     * @exception NS_ERROR_OUT_OF_MEMORY    Getter couldn't allocate string
     */
  /* attribute AUTF8String filterTemplate; */
  NS_IMETHOD GetFilterTemplate(nsACString & aFilterTemplate) = 0;
  NS_IMETHOD SetFilterTemplate(const nsACString & aFilterTemplate) = 0;

  /**
     * At most this many nsIAutoCompleteItems will be returned.  This
     * is useful for keeping bandwidth usage over slow-speed
     * connections as well as ensuring that the number of choices
     * offered in the UI is manageble.
     *
     * 1-65535 are interpreted literally
     * 0 means "unlimited"
     * -1 uses the default limit for the LDAP connection in use
     * 
     * @exception NS_ERROR_NULL_POINTER     NULL pointer passed to getter
     * @exception NS_ERROR_ILLEGAL_VALUE    Out-of-range value passed to setter
     */
  /* attribute long maxHits; */
  NS_IMETHOD GetMaxHits(PRInt32 *aMaxHits) = 0;
  NS_IMETHOD SetMaxHits(PRInt32 aMaxHits) = 0;

  /**
     * Strings shorter than this will return |nsIAutoCompleteStatus::ignored|
     * rather than triggering a search.  This allows browsers to be
     * configured to not search on substrings so short that they
     * aren't indexed by the LDAP server (such searches can use
     * significantly more server resources and return a very large
     * number of entries).  cjkMinStringLength is used for CJK
     * languages, and minStringLength for everything else.  As of this
     * writing, the "@mozilla.org/autocompleteSession;1?type=ldap"
     * contractid uses defaults of two and zero, respectively.  This
     * avoids most unindexed searches with at least one widely-deployed
     * webserver, but allows CJK languages, where a single glyph can be an
     * an entire name to still get results.
     * 
     * @exception NS_ERROR_NULL_POINTER  NULL pointer passed to getter
     */
  /* attribute unsigned long minStringLength; */
  NS_IMETHOD GetMinStringLength(PRUint32 *aMinStringLength) = 0;
  NS_IMETHOD SetMinStringLength(PRUint32 aMinStringLength) = 0;

  /* attribute unsigned long cjkMinStringLength; */
  NS_IMETHOD GetCjkMinStringLength(PRUint32 *aCjkMinStringLength) = 0;
  NS_IMETHOD SetCjkMinStringLength(PRUint32 aCjkMinStringLength) = 0;

  /**
     * LDAP server to complete against, in ldap: URL format.  
     * May change to an nsILDAPServer once that infrastructure lands.
     *
     * @exception NS_ERROR_NULL_POINTER     NULL pointer passed to getter    
     */
  /* attribute nsILDAPURL serverURL; */
  NS_IMETHOD GetServerURL(nsILDAPURL * *aServerURL) = 0;
  NS_IMETHOD SetServerURL(nsILDAPURL * aServerURL) = 0;

  /** 
     * Callback used to format an individual LDAP message into an
     * nsIAutoCompleteItem.  
     */
  /* attribute nsILDAPAutoCompFormatter formatter; */
  NS_IMETHOD GetFormatter(nsILDAPAutoCompFormatter * *aFormatter) = 0;
  NS_IMETHOD SetFormatter(nsILDAPAutoCompFormatter * aFormatter) = 0;

  /**
     * "Login as..." this ID.  Currently, this must be specified as a DN.
     * In the future, we may support userid and/or email address as well.
     * If unset, bind anonymously.
     */
  /* attribute AUTF8String login; */
  NS_IMETHOD GetLogin(nsACString & aLogin) = 0;
  NS_IMETHOD SetLogin(const nsACString & aLogin) = 0;

  /**
     * If set, use this object to get a password for logging in to the server.
     */
  /* attribute nsIAuthPrompt authPrompter; */
  NS_IMETHOD GetAuthPrompter(nsIAuthPrompt * *aAuthPrompter) = 0;
  NS_IMETHOD SetAuthPrompter(nsIAuthPrompt * aAuthPrompter) = 0;

};

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSILDAPAUTOCOMPLETESESSION \
  NS_IMETHOD GetFilterTemplate(nsACString & aFilterTemplate); \
  NS_IMETHOD SetFilterTemplate(const nsACString & aFilterTemplate); \
  NS_IMETHOD GetMaxHits(PRInt32 *aMaxHits); \
  NS_IMETHOD SetMaxHits(PRInt32 aMaxHits); \
  NS_IMETHOD GetMinStringLength(PRUint32 *aMinStringLength); \
  NS_IMETHOD SetMinStringLength(PRUint32 aMinStringLength); \
  NS_IMETHOD GetCjkMinStringLength(PRUint32 *aCjkMinStringLength); \
  NS_IMETHOD SetCjkMinStringLength(PRUint32 aCjkMinStringLength); \
  NS_IMETHOD GetServerURL(nsILDAPURL * *aServerURL); \
  NS_IMETHOD SetServerURL(nsILDAPURL * aServerURL); \
  NS_IMETHOD GetFormatter(nsILDAPAutoCompFormatter * *aFormatter); \
  NS_IMETHOD SetFormatter(nsILDAPAutoCompFormatter * aFormatter); \
  NS_IMETHOD GetLogin(nsACString & aLogin); \
  NS_IMETHOD SetLogin(const nsACString & aLogin); \
  NS_IMETHOD GetAuthPrompter(nsIAuthPrompt * *aAuthPrompter); \
  NS_IMETHOD SetAuthPrompter(nsIAuthPrompt * aAuthPrompter); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSILDAPAUTOCOMPLETESESSION(_to) \
  NS_IMETHOD GetFilterTemplate(nsACString & aFilterTemplate) { return _to GetFilterTemplate(aFilterTemplate); } \
  NS_IMETHOD SetFilterTemplate(const nsACString & aFilterTemplate) { return _to SetFilterTemplate(aFilterTemplate); } \
  NS_IMETHOD GetMaxHits(PRInt32 *aMaxHits) { return _to GetMaxHits(aMaxHits); } \
  NS_IMETHOD SetMaxHits(PRInt32 aMaxHits) { return _to SetMaxHits(aMaxHits); } \
  NS_IMETHOD GetMinStringLength(PRUint32 *aMinStringLength) { return _to GetMinStringLength(aMinStringLength); } \
  NS_IMETHOD SetMinStringLength(PRUint32 aMinStringLength) { return _to SetMinStringLength(aMinStringLength); } \
  NS_IMETHOD GetCjkMinStringLength(PRUint32 *aCjkMinStringLength) { return _to GetCjkMinStringLength(aCjkMinStringLength); } \
  NS_IMETHOD SetCjkMinStringLength(PRUint32 aCjkMinStringLength) { return _to SetCjkMinStringLength(aCjkMinStringLength); } \
  NS_IMETHOD GetServerURL(nsILDAPURL * *aServerURL) { return _to GetServerURL(aServerURL); } \
  NS_IMETHOD SetServerURL(nsILDAPURL * aServerURL) { return _to SetServerURL(aServerURL); } \
  NS_IMETHOD GetFormatter(nsILDAPAutoCompFormatter * *aFormatter) { return _to GetFormatter(aFormatter); } \
  NS_IMETHOD SetFormatter(nsILDAPAutoCompFormatter * aFormatter) { return _to SetFormatter(aFormatter); } \
  NS_IMETHOD GetLogin(nsACString & aLogin) { return _to GetLogin(aLogin); } \
  NS_IMETHOD SetLogin(const nsACString & aLogin) { return _to SetLogin(aLogin); } \
  NS_IMETHOD GetAuthPrompter(nsIAuthPrompt * *aAuthPrompter) { return _to GetAuthPrompter(aAuthPrompter); } \
  NS_IMETHOD SetAuthPrompter(nsIAuthPrompt * aAuthPrompter) { return _to SetAuthPrompter(aAuthPrompter); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSILDAPAUTOCOMPLETESESSION(_to) \
  NS_IMETHOD GetFilterTemplate(nsACString & aFilterTemplate) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetFilterTemplate(aFilterTemplate); } \
  NS_IMETHOD SetFilterTemplate(const nsACString & aFilterTemplate) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetFilterTemplate(aFilterTemplate); } \
  NS_IMETHOD GetMaxHits(PRInt32 *aMaxHits) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetMaxHits(aMaxHits); } \
  NS_IMETHOD SetMaxHits(PRInt32 aMaxHits) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetMaxHits(aMaxHits); } \
  NS_IMETHOD GetMinStringLength(PRUint32 *aMinStringLength) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetMinStringLength(aMinStringLength); } \
  NS_IMETHOD SetMinStringLength(PRUint32 aMinStringLength) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetMinStringLength(aMinStringLength); } \
  NS_IMETHOD GetCjkMinStringLength(PRUint32 *aCjkMinStringLength) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetCjkMinStringLength(aCjkMinStringLength); } \
  NS_IMETHOD SetCjkMinStringLength(PRUint32 aCjkMinStringLength) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetCjkMinStringLength(aCjkMinStringLength); } \
  NS_IMETHOD GetServerURL(nsILDAPURL * *aServerURL) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetServerURL(aServerURL); } \
  NS_IMETHOD SetServerURL(nsILDAPURL * aServerURL) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetServerURL(aServerURL); } \
  NS_IMETHOD GetFormatter(nsILDAPAutoCompFormatter * *aFormatter) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetFormatter(aFormatter); } \
  NS_IMETHOD SetFormatter(nsILDAPAutoCompFormatter * aFormatter) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetFormatter(aFormatter); } \
  NS_IMETHOD GetLogin(nsACString & aLogin) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetLogin(aLogin); } \
  NS_IMETHOD SetLogin(const nsACString & aLogin) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetLogin(aLogin); } \
  NS_IMETHOD GetAuthPrompter(nsIAuthPrompt * *aAuthPrompter) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetAuthPrompter(aAuthPrompter); } \
  NS_IMETHOD SetAuthPrompter(nsIAuthPrompt * aAuthPrompter) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetAuthPrompter(aAuthPrompter); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsLDAPAutoCompleteSession : public nsILDAPAutoCompleteSession
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSILDAPAUTOCOMPLETESESSION

  nsLDAPAutoCompleteSession();
  virtual ~nsLDAPAutoCompleteSession();
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsLDAPAutoCompleteSession, nsILDAPAutoCompleteSession)

nsLDAPAutoCompleteSession::nsLDAPAutoCompleteSession()
{
  /* member initializers and constructor code */
}

nsLDAPAutoCompleteSession::~nsLDAPAutoCompleteSession()
{
  /* destructor code */
}

/* attribute AUTF8String filterTemplate; */
NS_IMETHODIMP nsLDAPAutoCompleteSession::GetFilterTemplate(nsACString & aFilterTemplate)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsLDAPAutoCompleteSession::SetFilterTemplate(const nsACString & aFilterTemplate)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute long maxHits; */
NS_IMETHODIMP nsLDAPAutoCompleteSession::GetMaxHits(PRInt32 *aMaxHits)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsLDAPAutoCompleteSession::SetMaxHits(PRInt32 aMaxHits)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute unsigned long minStringLength; */
NS_IMETHODIMP nsLDAPAutoCompleteSession::GetMinStringLength(PRUint32 *aMinStringLength)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsLDAPAutoCompleteSession::SetMinStringLength(PRUint32 aMinStringLength)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute unsigned long cjkMinStringLength; */
NS_IMETHODIMP nsLDAPAutoCompleteSession::GetCjkMinStringLength(PRUint32 *aCjkMinStringLength)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsLDAPAutoCompleteSession::SetCjkMinStringLength(PRUint32 aCjkMinStringLength)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute nsILDAPURL serverURL; */
NS_IMETHODIMP nsLDAPAutoCompleteSession::GetServerURL(nsILDAPURL * *aServerURL)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsLDAPAutoCompleteSession::SetServerURL(nsILDAPURL * aServerURL)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute nsILDAPAutoCompFormatter formatter; */
NS_IMETHODIMP nsLDAPAutoCompleteSession::GetFormatter(nsILDAPAutoCompFormatter * *aFormatter)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsLDAPAutoCompleteSession::SetFormatter(nsILDAPAutoCompFormatter * aFormatter)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute AUTF8String login; */
NS_IMETHODIMP nsLDAPAutoCompleteSession::GetLogin(nsACString & aLogin)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsLDAPAutoCompleteSession::SetLogin(const nsACString & aLogin)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute nsIAuthPrompt authPrompter; */
NS_IMETHODIMP nsLDAPAutoCompleteSession::GetAuthPrompter(nsIAuthPrompt * *aAuthPrompter)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsLDAPAutoCompleteSession::SetAuthPrompter(nsIAuthPrompt * aAuthPrompter)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsILDAPAutoCompleteSession_h__ */
