/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM nsIAccessNode.idl
 */

#ifndef __gen_nsIAccessNode_h__
#define __gen_nsIAccessNode_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

#ifndef __gen_nsIAccessibleDocument_h__
#include "nsIAccessibleDocument.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif

/* starting interface:    nsIAccessNode */
#define NS_IACCESSNODE_IID_STR "46820f9b-3088-4046-ab0f-56fdacdc7a82"

#define NS_IACCESSNODE_IID \
  {0x46820f9b, 0x3088, 0x4046, \
    { 0xab, 0x0f, 0x56, 0xfd, 0xac, 0xdc, 0x7a, 0x82 }}

class NS_NO_VTABLE nsIAccessNode : public nsISupports {
 public: 

  NS_DEFINE_STATIC_IID_ACCESSOR(NS_IACCESSNODE_IID)

  /* [noscript] void init (); */
  NS_IMETHOD Init(void) = 0;

  /* [noscript] void shutdown (); */
  NS_IMETHOD Shutdown(void) = 0;

  /* [noscript] readonly attribute voidPtr ownerWindow; */
  NS_IMETHOD GetOwnerWindow(void * *aOwnerWindow) = 0;

  /* [noscript] readonly attribute voidPtr uniqueID; */
  NS_IMETHOD GetUniqueID(void * *aUniqueID) = 0;

};

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSIACCESSNODE \
  NS_IMETHOD Init(void); \
  NS_IMETHOD Shutdown(void); \
  NS_IMETHOD GetOwnerWindow(void * *aOwnerWindow); \
  NS_IMETHOD GetUniqueID(void * *aUniqueID); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSIACCESSNODE(_to) \
  NS_IMETHOD Init(void) { return _to Init(); } \
  NS_IMETHOD Shutdown(void) { return _to Shutdown(); } \
  NS_IMETHOD GetOwnerWindow(void * *aOwnerWindow) { return _to GetOwnerWindow(aOwnerWindow); } \
  NS_IMETHOD GetUniqueID(void * *aUniqueID) { return _to GetUniqueID(aUniqueID); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSIACCESSNODE(_to) \
  NS_IMETHOD Init(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->Init(); } \
  NS_IMETHOD Shutdown(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->Shutdown(); } \
  NS_IMETHOD GetOwnerWindow(void * *aOwnerWindow) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetOwnerWindow(aOwnerWindow); } \
  NS_IMETHOD GetUniqueID(void * *aUniqueID) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetUniqueID(aUniqueID); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsAccessNode : public nsIAccessNode
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIACCESSNODE

  nsAccessNode();
  virtual ~nsAccessNode();
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsAccessNode, nsIAccessNode)

nsAccessNode::nsAccessNode()
{
  /* member initializers and constructor code */
}

nsAccessNode::~nsAccessNode()
{
  /* destructor code */
}

/* [noscript] void init (); */
NS_IMETHODIMP nsAccessNode::Init()
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* [noscript] void shutdown (); */
NS_IMETHODIMP nsAccessNode::Shutdown()
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* [noscript] readonly attribute voidPtr ownerWindow; */
NS_IMETHODIMP nsAccessNode::GetOwnerWindow(void * *aOwnerWindow)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* [noscript] readonly attribute voidPtr uniqueID; */
NS_IMETHODIMP nsAccessNode::GetUniqueID(void * *aUniqueID)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsIAccessNode_h__ */
