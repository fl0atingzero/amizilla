/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM nsILDAPErrors.idl
 */

#ifndef __gen_nsILDAPErrors_h__
#define __gen_nsILDAPErrors_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif

/* starting interface:    nsILDAPErrors */
#define NS_ILDAPERRORS_IID_STR "f9ac10fa-1dd1-11b2-9798-8d5cbda95d74"

#define NS_ILDAPERRORS_IID \
  {0xf9ac10fa, 0x1dd1, 0x11b2, \
    { 0x97, 0x98, 0x8d, 0x5c, 0xbd, 0xa9, 0x5d, 0x74 }}

/**
 * Error codes used in the LDAP XPCOM SDK.
 *
 * Taken from the Mozilla C SDK's ldap.h include file, these should be
 * the same as those specified in the draft-ietf-ldapext-ldap-c-api-04.txt 
 * Internet Draft.  
 *
 * The only good documentation I'm aware of for these error codes is
 * at <http://docs.iplanet.com/docs/manuals/directory.html#SDKC>.
 * Unfortunately, this does not currently seem to be available under any
 * open source license, so I can't include that documentation here as
 * doxygen comments.
 *
 */
class NS_NO_VTABLE nsILDAPErrors : public nsISupports {
 public: 

  NS_DEFINE_STATIC_IID_ACCESSOR(NS_ILDAPERRORS_IID)

  enum { SUCCESS = 0 };

  enum { OPERATIONS_ERROR = 1 };

  enum { PROTOCOL_ERROR = 2 };

  enum { TIMELIMIT_EXCEEDED = 3 };

  enum { SIZELIMIT_EXCEEDED = 4 };

  enum { COMPARE_FALSE = 5 };

  enum { COMPARE_TRUE = 6 };

  enum { STRONG_AUTH_NOT_SUPPORTED = 7 };

  enum { STRONG_AUTH_REQUIRED = 8 };

  /**
     * UMich LDAPv2 extension
     */
  enum { PARTIAL_RESULTS = 9 };

  /**
     * new in LDAPv3
     */
  enum { REFERRAL = 10 };

  /**
     * new in LDAPv3
     */
  enum { ADMINLIMIT_EXCEEDED = 11 };

  /**
     * new in LDAPv3
     */
  enum { UNAVAILABLE_CRITICAL_EXTENSION = 12 };

  /**
     * new in LDAPv3
     */
  enum { CONFIDENTIALITY_REQUIRED = 13 };

  /**
     * new in LDAPv3
     */
  enum { SASL_BIND_IN_PROGRESS = 14 };

  enum { NO_SUCH_ATTRIBUTE = 16 };

  enum { UNDEFINED_TYPE = 17 };

  enum { INAPPROPRIATE_MATCHING = 18 };

  enum { CONSTRAINT_VIOLATION = 19 };

  enum { TYPE_OR_VALUE_EXISTS = 20 };

  enum { INVALID_SYNTAX = 21 };

  enum { NO_SUCH_OBJECT = 32 };

  enum { ALIAS_PROBLEM = 33 };

  enum { INVALID_DN_SYNTAX = 34 };

  /**
     * not used in LDAPv3
     */
  enum { IS_LEAF = 35 };

  enum { ALIAS_DEREF_PROBLEM = 36 };

  enum { INAPPROPRIATE_AUTH = 48 };

  enum { INVALID_CREDENTIALS = 49 };

  enum { INSUFFICIENT_ACCESS = 50 };

  enum { BUSY = 51 };

  enum { UNAVAILABLE = 52 };

  enum { UNWILLING_TO_PERFORM = 53 };

  enum { LOOP_DETECT = 54 };

  /**
     * server side sort extension
     */
  enum { SORT_CONTROL_MISSING = 60 };

  /**
     * VLV extension
     */
  enum { INDEX_RANGE_ERROR = 61 };

  enum { NAMING_VIOLATION = 64 };

  enum { OBJECT_CLASS_VIOLATION = 65 };

  enum { NOT_ALLOWED_ON_NONLEAF = 66 };

  enum { NOT_ALLOWED_ON_RDN = 67 };

  enum { ALREADY_EXISTS = 68 };

  enum { NO_OBJECT_CLASS_MODS = 69 };

  /**
     * reserved CLDAP
     */
  enum { RESULTS_TOO_LARGE = 70 };

  /**
     * new in LDAPv3
     */
  enum { AFFECTS_MULTIPLE_DSAS = 71 };

  enum { OTHER = 80 };

  enum { SERVER_DOWN = 81 };

  enum { LOCAL_ERROR = 82 };

  enum { ENCODING_ERROR = 83 };

  enum { DECODING_ERROR = 84 };

  enum { TIMEOUT = 85 };

  enum { AUTH_UNKNOWN = 86 };

  enum { FILTER_ERROR = 87 };

  enum { USER_CANCELLED = 88 };

  enum { PARAM_ERROR = 89 };

  enum { NO_MEMORY = 90 };

  enum { CONNECT_ERROR = 91 };

  /**
     * new in LDAPv3
     */
  enum { NOT_SUPPORTED = 92 };

  /**
     * new in LDAPv3
     */
  enum { CONTROL_NOT_FOUND = 93 };

  /**
     * new in LDAPv3
     */
  enum { NO_RESULTS_RETURNED = 94 };

  /**
     * new in LDAPv3
     */
  enum { MORE_RESULTS_TO_RETURN = 95 };

  /**
     * new in LDAPv3
     */
  enum { CLIENT_LOOP = 96 };

  /**
     * new in LDAPv3
     */
  enum { REFERRAL_LIMIT_EXCEEDED = 97 };

};

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSILDAPERRORS \

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSILDAPERRORS(_to) \

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSILDAPERRORS(_to) \

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsLDAPErrors : public nsILDAPErrors
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSILDAPERRORS

  nsLDAPErrors();
  virtual ~nsLDAPErrors();
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsLDAPErrors, nsILDAPErrors)

nsLDAPErrors::nsLDAPErrors()
{
  /* member initializers and constructor code */
}

nsLDAPErrors::~nsLDAPErrors()
{
  /* destructor code */
}

/* End of implementation class template. */
#endif

#define NS_ERROR_LDAP_OPERATIONS_ERROR \
    NS_ERROR_GENERATE_FAILURE(NS_ERROR_MODULE_LDAP, \
                              nsILDAPErrors::OPERATIONS_ERROR)
#define NS_ERROR_LDAP_PROTOCOL_ERROR \
    NS_ERROR_GENERATE_FAILURE(NS_ERROR_MODULE_LDAP, \
                              nsILDAPErrors::PROTOCOL_ERROR)
#define NS_ERROR_LDAP_TIMELIMIT_EXCEEDED \
    NS_ERROR_GENERATE_FAILURE(NS_ERROR_MODULE_LDAP, \
                              nsILDAPErrors::TIMELIMIT_EXCEEDED)
#define NS_ERROR_LDAP_SIZELIMIT_EXCEEDED \
    NS_ERROR_GENERATE_FAILURE(NS_ERROR_MODULE_LDAP, \
                              nsILDAPErrors::SIZELIMIT_EXCEEDED)
#define NS_ERROR_LDAP_COMPARE_FALSE \
    NS_ERROR_GENERATE_FAILURE(NS_ERROR_MODULE_LDAP, \
                              nsILDAPErrors::COMPARE_FALSE)
#define NS_ERROR_LDAP_COMPARE_TRUE \
    NS_ERROR_GENERATE_FAILURE(NS_ERROR_MODULE_LDAP, \
                              nsILDAPErrors::COMPARE_TRUE)
#define NS_ERROR_LDAP_STRONG_AUTH_NOT_SUPPORTED \
    NS_ERROR_GENERATE_FAILURE(NS_ERROR_MODULE_LDAP, \
                              nsILDAPErrors::STRONG_AUTH_NOT_SUPPORTED)
#define NS_ERROR_LDAP_STRONG_AUTH_REQUIRED \
    NS_ERROR_GENERATE_FAILURE(NS_ERROR_MODULE_LDAP, \
                              nsILDAPErrors::STRONG_AUTH_REQUIRED)
#define NS_ERROR_LDAP_PARTIAL_RESULTS \
    NS_ERROR_GENERATE_FAILURE(NS_ERROR_MODULE_LDAP, \
                              nsILDAPErrors::PARTIAL_RESULTS)
#define NS_ERROR_LDAP_REFERRAL \
    NS_ERROR_GENERATE_FAILURE(NS_ERROR_MODULE_LDAP, \
                              nsILDAPErrors::REFERRAL)
#define NS_ERROR_LDAP_ADMINLIMIT_EXCEEDED \
    NS_ERROR_GENERATE_FAILURE(NS_ERROR_MODULE_LDAP, \
                              nsILDAPErrors::ADMINLIMIT_EXCEEDED)
#define NS_ERROR_LDAP_UNAVAILABLE_CRITICAL_EXTENSION \
    NS_ERROR_GENERATE_FAILURE(NS_ERROR_MODULE_LDAP, \
                              nsILDAPErrors::UNAVAILABLE_CRITICAL_EXTENSION)
#define NS_ERROR_LDAP_CONFIDENTIALITY_REQUIRED \
    NS_ERROR_GENERATE_FAILURE(NS_ERROR_MODULE_LDAP, \
                              nsILDAPErrors::CONFIDENTIALITY_REQUIRED)
#define NS_ERROR_LDAP_SASL_BIND_IN_PROGRESS \
    NS_ERROR_GENERATE_FAILURE(NS_ERROR_MODULE_LDAP, \
                              nsILDAPErrors::SASL_BIND_IN_PROGRESS)
#define NS_ERROR_LDAP_NO_SUCH_ATTRIBUTE \
    NS_ERROR_GENERATE_FAILURE(NS_ERROR_MODULE_LDAP, \
                              nsILDAPErrors::NO_SUCH_ATTRIBUTE)
#define NS_ERROR_LDAP_UNDEFINED_TYPE \
    NS_ERROR_GENERATE_FAILURE(NS_ERROR_MODULE_LDAP, \
                              nsILDAPErrors::UNDEFINED_TYPE)
#define NS_ERROR_LDAP_INAPPROPRIATE_MATCHING \
    NS_ERROR_GENERATE_FAILURE(NS_ERROR_MODULE_LDAP, \
                              nsILDAPErrors::INAPPROPRIATE_MATCHING)
#define NS_ERROR_LDAP_CONSTRAINT_VIOLATION \
    NS_ERROR_GENERATE_FAILURE(NS_ERROR_MODULE_LDAP, \
                              nsILDAPErrors::CONSTRAINT_VIOLATION)
#define NS_ERROR_LDAP_TYPE_OR_VALUE_EXISTS \
    NS_ERROR_GENERATE_FAILURE(NS_ERROR_MODULE_LDAP, \
                              nsILDAPErrors::TYPE_OR_VALUE_EXISTS)
#define NS_ERROR_LDAP_INVALID_SYNTAX \
    NS_ERROR_GENERATE_FAILURE(NS_ERROR_MODULE_LDAP, \
                              nsILDAPErrors::INVALID_SYNTAX)
#define NS_ERROR_LDAP_NO_SUCH_OBJECT \
    NS_ERROR_GENERATE_FAILURE(NS_ERROR_MODULE_LDAP, \
                              nsILDAPErrors::NO_SUCH_OBJECT)
#define NS_ERROR_LDAP_ALIAS_PROBLEM \
    NS_ERROR_GENERATE_FAILURE(NS_ERROR_MODULE_LDAP, \
                              nsILDAPErrors::ALIAS_PROBLEM)
#define NS_ERROR_LDAP_INVALID_DN_SYNTAX \
    NS_ERROR_GENERATE_FAILURE(NS_ERROR_MODULE_LDAP, \
                              nsILDAPErrors::INVALID_DN_SYNTAX)
#define NS_ERROR_LDAP_IS_LEAF \
    NS_ERROR_GENERATE_FAILURE(NS_ERROR_MODULE_LDAP, \
                              nsILDAPErrors::IS_LEAF)
#define NS_ERROR_LDAP_ALIAS_DEREF_PROBLEM \
    NS_ERROR_GENERATE_FAILURE(NS_ERROR_MODULE_LDAP, \
                              nsILDAPErrors::ALIAS_DEREF_PROBLEM)
#define NS_ERROR_LDAP_INAPPROPRIATE_AUTH \
    NS_ERROR_GENERATE_FAILURE(NS_ERROR_MODULE_LDAP, \
                              nsILDAPErrors::INAPPROPRIATE_AUTH)
#define NS_ERROR_LDAP_INVALID_CREDENTIALS \
    NS_ERROR_GENERATE_FAILURE(NS_ERROR_MODULE_LDAP, \
                              nsILDAPErrors::INVALID_CREDENTIALS)
#define NS_ERROR_LDAP_INSUFFICIENT_ACCESS \
    NS_ERROR_GENERATE_FAILURE(NS_ERROR_MODULE_LDAP, \
                              nsILDAPErrors::INSUFFICIENT_ACCESS)
#define NS_ERROR_LDAP_BUSY \
    NS_ERROR_GENERATE_FAILURE(NS_ERROR_MODULE_LDAP, \
                              nsILDAPErrors::BUSY)
#define NS_ERROR_LDAP_UNAVAILABLE \
    NS_ERROR_GENERATE_FAILURE(NS_ERROR_MODULE_LDAP, \
                              nsILDAPErrors::UNAVAILABLE)
#define NS_ERROR_LDAP_UNWILLING_TO_PERFORM \
    NS_ERROR_GENERATE_FAILURE(NS_ERROR_MODULE_LDAP, \
                              nsILDAPErrors::UNWILLING_TO_PERFORM)
#define NS_ERROR_LDAP_LOOP_DETECT \
    NS_ERROR_GENERATE_FAILURE(NS_ERROR_MODULE_LDAP, \
                              nsILDAPErrors::LOOP_DETECT)
#define NS_ERROR_LDAP_SORT_CONTROL_MISSING \
    NS_ERROR_GENERATE_FAILURE(NS_ERROR_MODULE_LDAP, \
                              nsILDAPErrors::SORT_CONTROL_MISSING)
#define NS_ERROR_LDAP_INDEX_RANGE_ERROR \
    NS_ERROR_GENERATE_FAILURE(NS_ERROR_MODULE_LDAP, \
                              nsILDAPErrors::INDEX_RANGE_ERROR)
#define NS_ERROR_LDAP_NAMING_VIOLATION \
    NS_ERROR_GENERATE_FAILURE(NS_ERROR_MODULE_LDAP, \
                              nsILDAPErrors::NAMING_VIOLATION)
#define NS_ERROR_LDAP_OBJECT_CLASS_VIOLATION \
    NS_ERROR_GENERATE_FAILURE(NS_ERROR_MODULE_LDAP, \
                              nsILDAPErrors::OBJECT_CLASS_VIOLATION)
#define NS_ERROR_LDAP_NOT_ALLOWED_ON_NONLEAF \
    NS_ERROR_GENERATE_FAILURE(NS_ERROR_MODULE_LDAP, \
                              nsILDAPErrors::NOT_ALLOWED_ON_NONLEAF)
#define NS_ERROR_LDAP_NOT_ALLOWED_ON_RDN \
    NS_ERROR_GENERATE_FAILURE(NS_ERROR_MODULE_LDAP, \
                              nsILDAPErrors::NOT_ALLOWED_ON_RDN)
#define NS_ERROR_LDAP_ALREADY_EXISTS \
    NS_ERROR_GENERATE_FAILURE(NS_ERROR_MODULE_LDAP, \
                              nsILDAPErrors::ALREADY_EXISTS)
#define NS_ERROR_LDAP_NO_OBJECT_CLASS_MODS \
    NS_ERROR_GENERATE_FAILURE(NS_ERROR_MODULE_LDAP, \
                              nsILDAPErrors::NO_OBJECT_CLASS_MODS)
#define NS_ERROR_LDAP_RESULTS_TOO_LARGE \
    NS_ERROR_GENERATE_FAILURE(NS_ERROR_MODULE_LDAP, \
                              nsILDAPErrors::RESULTS_TOO_LARGE)
#define NS_ERROR_LDAP_AFFECTS_MULTIPLE_DSAS \
    NS_ERROR_GENERATE_FAILURE(NS_ERROR_MODULE_LDAP, \
                              nsILDAPErrors::AFFECTS_MULTIPLE_DSAS)
#define NS_ERROR_LDAP_OTHER \
    NS_ERROR_GENERATE_FAILURE(NS_ERROR_MODULE_LDAP, \
                              nsILDAPErrors::OTHER)
#define NS_ERROR_LDAP_SERVER_DOWN \
    NS_ERROR_GENERATE_FAILURE(NS_ERROR_MODULE_LDAP, \
                              nsILDAPErrors::SERVER_DOWN)
#define NS_ERROR_LDAP_LOCAL_ERROR \
    NS_ERROR_GENERATE_FAILURE(NS_ERROR_MODULE_LDAP, \
                              nsILDAPErrors::LOCAL_ERROR)
#define NS_ERROR_LDAP_ENCODING_ERROR \
    NS_ERROR_GENERATE_FAILURE(NS_ERROR_MODULE_LDAP, \
                              nsILDAPErrors::ENCODING_ERROR)
#define NS_ERROR_LDAP_DECODING_ERROR \
    NS_ERROR_GENERATE_FAILURE(NS_ERROR_MODULE_LDAP, \
                              nsILDAPErrors::DECODING_ERROR)
#define NS_ERROR_LDAP_TIMEOUT \
    NS_ERROR_GENERATE_FAILURE(NS_ERROR_MODULE_LDAP, \
                              nsILDAPErrors::TIMEOUT)
#define NS_ERROR_LDAP_AUTH_UNKNOWN \
    NS_ERROR_GENERATE_FAILURE(NS_ERROR_MODULE_LDAP, \
                              nsILDAPErrors::AUTH_UNKNOWN)
#define NS_ERROR_LDAP_FILTER_ERROR \
    NS_ERROR_GENERATE_FAILURE(NS_ERROR_MODULE_LDAP, \
                              nsILDAPErrors::FILTER_ERROR)
#define NS_ERROR_LDAP_USER_CANCELLED \
    NS_ERROR_GENERATE_FAILURE(NS_ERROR_MODULE_LDAP, \
                              nsILDAPErrors::USER_CANCELLED)
#define NS_ERROR_LDAP_PARAM_ERROR \
    NS_ERROR_GENERATE_FAILURE(NS_ERROR_MODULE_LDAP, \
                              nsILDAPErrors::PARAM_ERROR)
#define NS_ERROR_LDAP_NO_MEMORY \
    NS_ERROR_GENERATE_FAILURE(NS_ERROR_MODULE_LDAP, \
                              nsILDAPErrors::NO_MEMORY)
#define NS_ERROR_LDAP_CONNECT_ERROR \
    NS_ERROR_GENERATE_FAILURE(NS_ERROR_MODULE_LDAP, \
                              nsILDAPErrors::CONNECT_ERROR)
#define NS_ERROR_LDAP_NOT_SUPPORTED \
    NS_ERROR_GENERATE_FAILURE(NS_ERROR_MODULE_LDAP, \
                              nsILDAPErrors::NOT_SUPPORTED)
#define NS_ERROR_LDAP_CONTROL_NOT_FOUND \
    NS_ERROR_GENERATE_FAILURE(NS_ERROR_MODULE_LDAP, \
                              nsILDAPErrors::CONTROL_NOT_FOUND)
#define NS_ERROR_LDAP_NO_RESULTS_RETURNED \
    NS_ERROR_GENERATE_FAILURE(NS_ERROR_MODULE_LDAP, \
                              nsILDAPErrors::NO_RESULTS_RETURNED)
#define NS_ERROR_LDAP_MORE_RESULTS_TO_RETURN \
    NS_ERROR_GENERATE_FAILURE(NS_ERROR_MODULE_LDAP, \
                              nsILDAPErrors::MORE_RESULTS_TO_RETURN)
#define NS_ERROR_LDAP_CLIENT_LOOP \
    NS_ERROR_GENERATE_FAILURE(NS_ERROR_MODULE_LDAP, \
                              nsILDAPErrors::CLIENT_LOOP)
#define NS_ERROR_LDAP_REFERRAL_LIMIT_EXCEEDED \
    NS_ERROR_GENERATE_FAILURE(NS_ERROR_MODULE_LDAP, \
                              nsILDAPErrors::REFERRAL_LIMIT_EXCEEDED)

#endif /* __gen_nsILDAPErrors_h__ */
