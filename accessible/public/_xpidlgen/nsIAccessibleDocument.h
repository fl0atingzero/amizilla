/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM nsIAccessibleDocument.idl
 */

#ifndef __gen_nsIAccessibleDocument_h__
#define __gen_nsIAccessibleDocument_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

#ifndef __gen_nsIAccessible_h__
#include "nsIAccessible.h"
#endif

#ifndef __gen_domstubs_h__
#include "domstubs.h"
#endif

#ifndef __gen_nsIAccessibleCaret_h__
#include "nsIAccessibleCaret.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif
class nsIDocument; /* forward declaration */

class nsIAccessNode; /* forward declaration */


/* starting interface:    nsIAccessibleDocument */
#define NS_IACCESSIBLEDOCUMENT_IID_STR "8781fc88-355f-4439-881f-6504a0a1ceb6"

#define NS_IACCESSIBLEDOCUMENT_IID \
  {0x8781fc88, 0x355f, 0x4439, \
    { 0x88, 0x1f, 0x65, 0x04, 0xa0, 0xa1, 0xce, 0xb6 }}

class NS_NO_VTABLE nsIAccessibleDocument : public nsISupports {
 public: 

  NS_DEFINE_STATIC_IID_ACCESSOR(NS_IACCESSIBLEDOCUMENT_IID)

  /* readonly attribute AString URL; */
  NS_IMETHOD GetURL(nsAString & aURL) = 0;

  /* readonly attribute AString title; */
  NS_IMETHOD GetTitle(nsAString & aTitle) = 0;

  /* readonly attribute AString mimeType; */
  NS_IMETHOD GetMimeType(nsAString & aMimeType) = 0;

  /* readonly attribute AString docType; */
  NS_IMETHOD GetDocType(nsAString & aDocType) = 0;

  /* readonly attribute boolean isEditable; */
  NS_IMETHOD GetIsEditable(PRBool *aIsEditable) = 0;

  /* AString getNameSpaceURIForID (in short nameSpaceID); */
  NS_IMETHOD GetNameSpaceURIForID(PRInt16 nameSpaceID, nsAString & _retval) = 0;

  /* readonly attribute nsIAccessibleCaret caretAccessible; */
  NS_IMETHOD GetCaretAccessible(nsIAccessibleCaret * *aCaretAccessible) = 0;

  /* [noscript] readonly attribute voidPtr window; */
  NS_IMETHOD GetWindow(void * *aWindow) = 0;

  /* [noscript] nsIAccessNode getCachedAccessNode (in voidPtr aUniqueID); */
  NS_IMETHOD GetCachedAccessNode(void * aUniqueID, nsIAccessNode **_retval) = 0;

  /* [noscript] void InvalidateCacheSubtree (in nsIDOMNode aStartNode); */
  NS_IMETHOD InvalidateCacheSubtree(nsIDOMNode *aStartNode) = 0;

  /* [noscript] nsIAccessible getAccessibleInParentChain (in nsIDOMNode aDOMNode); */
  NS_IMETHOD GetAccessibleInParentChain(nsIDOMNode *aDOMNode, nsIAccessible **_retval) = 0;

  /* [noscript] void cacheAccessNode (in voidPtr aUniqueID, in nsIAccessNode aAccessNode); */
  NS_IMETHOD CacheAccessNode(void * aUniqueID, nsIAccessNode *aAccessNode) = 0;

  /* [noscript] void destroy (); */
  NS_IMETHOD Destroy(void) = 0;

};

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSIACCESSIBLEDOCUMENT \
  NS_IMETHOD GetURL(nsAString & aURL); \
  NS_IMETHOD GetTitle(nsAString & aTitle); \
  NS_IMETHOD GetMimeType(nsAString & aMimeType); \
  NS_IMETHOD GetDocType(nsAString & aDocType); \
  NS_IMETHOD GetIsEditable(PRBool *aIsEditable); \
  NS_IMETHOD GetNameSpaceURIForID(PRInt16 nameSpaceID, nsAString & _retval); \
  NS_IMETHOD GetCaretAccessible(nsIAccessibleCaret * *aCaretAccessible); \
  NS_IMETHOD GetWindow(void * *aWindow); \
  NS_IMETHOD GetCachedAccessNode(void * aUniqueID, nsIAccessNode **_retval); \
  NS_IMETHOD InvalidateCacheSubtree(nsIDOMNode *aStartNode); \
  NS_IMETHOD GetAccessibleInParentChain(nsIDOMNode *aDOMNode, nsIAccessible **_retval); \
  NS_IMETHOD CacheAccessNode(void * aUniqueID, nsIAccessNode *aAccessNode); \
  NS_IMETHOD Destroy(void); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSIACCESSIBLEDOCUMENT(_to) \
  NS_IMETHOD GetURL(nsAString & aURL) { return _to GetURL(aURL); } \
  NS_IMETHOD GetTitle(nsAString & aTitle) { return _to GetTitle(aTitle); } \
  NS_IMETHOD GetMimeType(nsAString & aMimeType) { return _to GetMimeType(aMimeType); } \
  NS_IMETHOD GetDocType(nsAString & aDocType) { return _to GetDocType(aDocType); } \
  NS_IMETHOD GetIsEditable(PRBool *aIsEditable) { return _to GetIsEditable(aIsEditable); } \
  NS_IMETHOD GetNameSpaceURIForID(PRInt16 nameSpaceID, nsAString & _retval) { return _to GetNameSpaceURIForID(nameSpaceID, _retval); } \
  NS_IMETHOD GetCaretAccessible(nsIAccessibleCaret * *aCaretAccessible) { return _to GetCaretAccessible(aCaretAccessible); } \
  NS_IMETHOD GetWindow(void * *aWindow) { return _to GetWindow(aWindow); } \
  NS_IMETHOD GetCachedAccessNode(void * aUniqueID, nsIAccessNode **_retval) { return _to GetCachedAccessNode(aUniqueID, _retval); } \
  NS_IMETHOD InvalidateCacheSubtree(nsIDOMNode *aStartNode) { return _to InvalidateCacheSubtree(aStartNode); } \
  NS_IMETHOD GetAccessibleInParentChain(nsIDOMNode *aDOMNode, nsIAccessible **_retval) { return _to GetAccessibleInParentChain(aDOMNode, _retval); } \
  NS_IMETHOD CacheAccessNode(void * aUniqueID, nsIAccessNode *aAccessNode) { return _to CacheAccessNode(aUniqueID, aAccessNode); } \
  NS_IMETHOD Destroy(void) { return _to Destroy(); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSIACCESSIBLEDOCUMENT(_to) \
  NS_IMETHOD GetURL(nsAString & aURL) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetURL(aURL); } \
  NS_IMETHOD GetTitle(nsAString & aTitle) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetTitle(aTitle); } \
  NS_IMETHOD GetMimeType(nsAString & aMimeType) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetMimeType(aMimeType); } \
  NS_IMETHOD GetDocType(nsAString & aDocType) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetDocType(aDocType); } \
  NS_IMETHOD GetIsEditable(PRBool *aIsEditable) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetIsEditable(aIsEditable); } \
  NS_IMETHOD GetNameSpaceURIForID(PRInt16 nameSpaceID, nsAString & _retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetNameSpaceURIForID(nameSpaceID, _retval); } \
  NS_IMETHOD GetCaretAccessible(nsIAccessibleCaret * *aCaretAccessible) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetCaretAccessible(aCaretAccessible); } \
  NS_IMETHOD GetWindow(void * *aWindow) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetWindow(aWindow); } \
  NS_IMETHOD GetCachedAccessNode(void * aUniqueID, nsIAccessNode **_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetCachedAccessNode(aUniqueID, _retval); } \
  NS_IMETHOD InvalidateCacheSubtree(nsIDOMNode *aStartNode) { return !_to ? NS_ERROR_NULL_POINTER : _to->InvalidateCacheSubtree(aStartNode); } \
  NS_IMETHOD GetAccessibleInParentChain(nsIDOMNode *aDOMNode, nsIAccessible **_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetAccessibleInParentChain(aDOMNode, _retval); } \
  NS_IMETHOD CacheAccessNode(void * aUniqueID, nsIAccessNode *aAccessNode) { return !_to ? NS_ERROR_NULL_POINTER : _to->CacheAccessNode(aUniqueID, aAccessNode); } \
  NS_IMETHOD Destroy(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->Destroy(); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsAccessibleDocument : public nsIAccessibleDocument
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIACCESSIBLEDOCUMENT

  nsAccessibleDocument();
  virtual ~nsAccessibleDocument();
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsAccessibleDocument, nsIAccessibleDocument)

nsAccessibleDocument::nsAccessibleDocument()
{
  /* member initializers and constructor code */
}

nsAccessibleDocument::~nsAccessibleDocument()
{
  /* destructor code */
}

/* readonly attribute AString URL; */
NS_IMETHODIMP nsAccessibleDocument::GetURL(nsAString & aURL)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute AString title; */
NS_IMETHODIMP nsAccessibleDocument::GetTitle(nsAString & aTitle)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute AString mimeType; */
NS_IMETHODIMP nsAccessibleDocument::GetMimeType(nsAString & aMimeType)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute AString docType; */
NS_IMETHODIMP nsAccessibleDocument::GetDocType(nsAString & aDocType)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute boolean isEditable; */
NS_IMETHODIMP nsAccessibleDocument::GetIsEditable(PRBool *aIsEditable)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* AString getNameSpaceURIForID (in short nameSpaceID); */
NS_IMETHODIMP nsAccessibleDocument::GetNameSpaceURIForID(PRInt16 nameSpaceID, nsAString & _retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute nsIAccessibleCaret caretAccessible; */
NS_IMETHODIMP nsAccessibleDocument::GetCaretAccessible(nsIAccessibleCaret * *aCaretAccessible)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* [noscript] readonly attribute voidPtr window; */
NS_IMETHODIMP nsAccessibleDocument::GetWindow(void * *aWindow)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* [noscript] nsIAccessNode getCachedAccessNode (in voidPtr aUniqueID); */
NS_IMETHODIMP nsAccessibleDocument::GetCachedAccessNode(void * aUniqueID, nsIAccessNode **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* [noscript] void InvalidateCacheSubtree (in nsIDOMNode aStartNode); */
NS_IMETHODIMP nsAccessibleDocument::InvalidateCacheSubtree(nsIDOMNode *aStartNode)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* [noscript] nsIAccessible getAccessibleInParentChain (in nsIDOMNode aDOMNode); */
NS_IMETHODIMP nsAccessibleDocument::GetAccessibleInParentChain(nsIDOMNode *aDOMNode, nsIAccessible **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* [noscript] void cacheAccessNode (in voidPtr aUniqueID, in nsIAccessNode aAccessNode); */
NS_IMETHODIMP nsAccessibleDocument::CacheAccessNode(void * aUniqueID, nsIAccessNode *aAccessNode)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* [noscript] void destroy (); */
NS_IMETHODIMP nsAccessibleDocument::Destroy()
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsIAccessibleDocument_h__ */
