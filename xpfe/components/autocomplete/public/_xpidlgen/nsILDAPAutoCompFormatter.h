/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM nsILDAPAutoCompFormatter.idl
 */

#ifndef __gen_nsILDAPAutoCompFormatter_h__
#define __gen_nsILDAPAutoCompFormatter_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif
class nsIAutoCompleteItem; /* forward declaration */

class nsILDAPMessage; /* forward declaration */


/* starting interface:    nsILDAPAutoCompFormatter */
#define NS_ILDAPAUTOCOMPFORMATTER_IID_STR "cbec617c-22d2-4286-8308-0ef8bf57c0ce"

#define NS_ILDAPAUTOCOMPFORMATTER_IID \
  {0xcbec617c, 0x22d2, 0x4286, \
    { 0x83, 0x08, 0x0e, 0xf8, 0xbf, 0x57, 0xc0, 0xce }}

/**
 * An interface to allow different users of nsILDAPAutoCompleteSession to 
 * format each nsILDAPMessage into an nsIAutoCompleteItem as it sees fit.
 */
class NS_NO_VTABLE nsILDAPAutoCompFormatter : public nsISupports {
 public: 

  NS_DEFINE_STATIC_IID_ACCESSOR(NS_ILDAPAUTOCOMPFORMATTER_IID)

  /**
     * Returns an nsIAutoCompleteItem generated from the data in 
     * the given nsILDAPMessage.
     *
     * @param aMessage  message to be formatted
     * @return          resulting nsIAutoCompleteItem
     */
  /* nsIAutoCompleteItem format (in nsILDAPMessage aMessage); */
  NS_IMETHOD Format(nsILDAPMessage *aMessage, nsIAutoCompleteItem **_retval) = 0;

  /**
     * Gets a list of all the LDAP attributes that should be requested
     * from the LDAP server when a lookup is done.  This avoids
     * wasting server time, bandwidth, and client time processing
     * unused attributes.
     *
     * Note that this is only required to be called by the
     * nsILDAPAutoCompleteSession implementation when the
     * nsILDAPAutoCompleteSession::formatter IDL attribute is set.  .
     * So if for some reason, the LDAP attributes to be returned by
     * searches has to change (eg because the user changed a
     * preference), the nsILDAPAutoCompleteSession::formatter IDL
     * attribute should be re-set to the same object to force a new
     * getAttributes() call.
     * 
     * @param aCount    number of attributes in the array
     * @param aAttrs    list of LDAP attributes to request
     */
  /* void getAttributes (out unsigned long aCount, [array, size_is (aCount), retval] out string aAttrs); */
  NS_IMETHOD GetAttributes(PRUint32 *aCount, char ***aAttrs) = 0;

  /** 
     * This method formats an error condition into an nsIAutoCompleteItem
     * for display to the user.  Specifically, the state that the session
     * was in when the error occured (aState) is formatted into a general
     * error message which is put in the value attribute of the item,
     * and the specific error (aErrorCode) is formatted into another message
     * which is put in an nsISupportsString in the param attribute of the
     * item.
     *
     * @param aState        state of autocomplete session when error occurred
     * @param aErrorCode    specific error encountered
     *
     * @return              newly generated item
     */
  /* nsIAutoCompleteItem formatException (in long aState, in nsresult aErrorCode); */
  NS_IMETHOD FormatException(PRInt32 aState, nsresult aErrorCode, nsIAutoCompleteItem **_retval) = 0;

  /**
     *  Possible states that can be passed in aState to formatException
     */
  enum { STATE_UNBOUND = 0 };

  enum { STATE_INITIALIZING = 1 };

  enum { STATE_BINDING = 2 };

  enum { STATE_BOUND = 3 };

  enum { STATE_SEARCHING = 4 };

};

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSILDAPAUTOCOMPFORMATTER \
  NS_IMETHOD Format(nsILDAPMessage *aMessage, nsIAutoCompleteItem **_retval); \
  NS_IMETHOD GetAttributes(PRUint32 *aCount, char ***aAttrs); \
  NS_IMETHOD FormatException(PRInt32 aState, nsresult aErrorCode, nsIAutoCompleteItem **_retval); \

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSILDAPAUTOCOMPFORMATTER(_to) \
  NS_IMETHOD Format(nsILDAPMessage *aMessage, nsIAutoCompleteItem **_retval) { return _to Format(aMessage, _retval); } \
  NS_IMETHOD GetAttributes(PRUint32 *aCount, char ***aAttrs) { return _to GetAttributes(aCount, aAttrs); } \
  NS_IMETHOD FormatException(PRInt32 aState, nsresult aErrorCode, nsIAutoCompleteItem **_retval) { return _to FormatException(aState, aErrorCode, _retval); } \

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSILDAPAUTOCOMPFORMATTER(_to) \
  NS_IMETHOD Format(nsILDAPMessage *aMessage, nsIAutoCompleteItem **_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->Format(aMessage, _retval); } \
  NS_IMETHOD GetAttributes(PRUint32 *aCount, char ***aAttrs) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetAttributes(aCount, aAttrs); } \
  NS_IMETHOD FormatException(PRInt32 aState, nsresult aErrorCode, nsIAutoCompleteItem **_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->FormatException(aState, aErrorCode, _retval); } \

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsLDAPAutoCompFormatter : public nsILDAPAutoCompFormatter
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSILDAPAUTOCOMPFORMATTER

  nsLDAPAutoCompFormatter();
  virtual ~nsLDAPAutoCompFormatter();
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsLDAPAutoCompFormatter, nsILDAPAutoCompFormatter)

nsLDAPAutoCompFormatter::nsLDAPAutoCompFormatter()
{
  /* member initializers and constructor code */
}

nsLDAPAutoCompFormatter::~nsLDAPAutoCompFormatter()
{
  /* destructor code */
}

/* nsIAutoCompleteItem format (in nsILDAPMessage aMessage); */
NS_IMETHODIMP nsLDAPAutoCompFormatter::Format(nsILDAPMessage *aMessage, nsIAutoCompleteItem **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void getAttributes (out unsigned long aCount, [array, size_is (aCount), retval] out string aAttrs); */
NS_IMETHODIMP nsLDAPAutoCompFormatter::GetAttributes(PRUint32 *aCount, char ***aAttrs)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* nsIAutoCompleteItem formatException (in long aState, in nsresult aErrorCode); */
NS_IMETHODIMP nsLDAPAutoCompFormatter::FormatException(PRInt32 aState, nsresult aErrorCode, nsIAutoCompleteItem **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsILDAPAutoCompFormatter_h__ */
