/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM nsIAccessibleEventReceiver.idl
 */

#ifndef __gen_nsIAccessibleEventReceiver_h__
#define __gen_nsIAccessibleEventReceiver_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif

/* starting interface:    nsIAccessibleEventReceiver */
#define NS_IACCESSIBLEEVENTRECEIVER_IID_STR "ab331e47-4faa-4a12-9480-9b480dd78b39"

#define NS_IACCESSIBLEEVENTRECEIVER_IID \
  {0xab331e47, 0x4faa, 0x4a12, \
    { 0x94, 0x80, 0x9b, 0x48, 0x0d, 0xd7, 0x8b, 0x39 }}

class NS_NO_VTABLE nsIAccessibleEventReceiver : public nsISupports {
 public: 

  NS_DEFINE_STATIC_IID_ACCESSOR(NS_IACCESSIBLEEVENTRECEIVER_IID)

  /* void addEventListeners (); */
  NS_IMETHOD AddEventListeners(void) = 0;

  /* void removeEventListeners (); */
  NS_IMETHOD RemoveEventListeners(void) = 0;

  enum { EVENT_CREATE = 32768U };

  enum { EVENT_DESTROY = 32769U };

  enum { EVENT_SHOW = 32770U };

  enum { EVENT_HIDE = 32771U };

  enum { EVENT_REORDER = 32772U };

  enum { EVENT_FOCUS = 32773U };

  enum { EVENT_STATE_CHANGE = 32778U };

  enum { EVENT_LOCATION_CHANGE = 32779U };

  enum { EVENT_NAME_CHANGE = 32780U };

  enum { EVENT_DESCRIPTIONCHANGE = 32781U };

  enum { EVENT_VALUE_CHANGE = 32782U };

  enum { EVENT_PARENTCHANGE = 32783U };

  enum { EVENT_HELPCHANGE = 32784U };

  enum { EVENT_DEFACTIONCHANGE = 32785U };

  enum { EVENT_ACCELERATORCHANGE = 32786U };

  enum { EVENT_SELECTION = 32774U };

  enum { EVENT_SELECTION_ADD = 32775U };

  enum { EVENT_SELECTION_REMOVE = 32776U };

  enum { EVENT_SELECTION_WITHIN = 32777U };

  enum { EVENT_ALERT = 2U };

  enum { EVENT_FOREGROUND = 3U };

  enum { EVENT_MENUSTART = 4U };

  enum { EVENT_MENUEND = 5U };

  enum { EVENT_MENUPOPUPSTART = 6U };

  enum { EVENT_MENUPOPUPEND = 7U };

  enum { EVENT_CAPTURESTART = 8U };

  enum { EVENT_CAPTUREEND = 9U };

  enum { EVENT_MOVESIZESTART = 10U };

  enum { EVENT_MOVESIZEEND = 11U };

  enum { EVENT_CONTEXTHELPSTART = 12U };

  enum { EVENT_CONTEXTHELPEND = 13U };

  enum { EVENT_DRAGDROPSTART = 14U };

  enum { EVENT_DRAGDROPEND = 15U };

  enum { EVENT_DIALOGSTART = 16U };

  enum { EVENT_DIALOGEND = 17U };

  enum { EVENT_SCROLLINGSTART = 18U };

  enum { EVENT_SCROLLINGEND = 19U };

  enum { EVENT_MINIMIZESTART = 22U };

  enum { EVENT_MINIMIZEEND = 23U };

  enum { EVENT_ATK_PROPERTY_CHANGE = 256U };

  enum { EVENT_ATK_SELECTION_CHANGE = 257U };

  enum { EVENT_ATK_TEXT_CHANGE = 258U };

  enum { EVENT_ATK_TEXT_SELECTION_CHANGE = 259U };

  enum { EVENT_ATK_TEXT_CARET_MOVE = 260U };

  enum { EVENT_ATK_VISIBLE_DATA_CHANGE = 261U };

  enum { EVENT_ATK_TABLE_MODEL_CHANGE = 272U };

  enum { EVENT_ATK_TABLE_ROW_INSERT = 273U };

  enum { EVENT_ATK_TABLE_ROW_DELETE = 274U };

  enum { EVENT_ATK_TABLE_ROW_REORDER = 275U };

  enum { EVENT_ATK_TABLE_COLUMN_INSERT = 276U };

  enum { EVENT_ATK_TABLE_COLUMN_DELETE = 277U };

  enum { EVENT_ATK_TABLE_COLUMN_REORDER = 278U };

  enum { EVENT_ATK_LINK_SELECTED = 279U };

};

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSIACCESSIBLEEVENTRECEIVER \
  NS_IMETHOD AddEventListeners(void); \
  NS_IMETHOD RemoveEventListeners(void); \

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSIACCESSIBLEEVENTRECEIVER(_to) \
  NS_IMETHOD AddEventListeners(void) { return _to AddEventListeners(); } \
  NS_IMETHOD RemoveEventListeners(void) { return _to RemoveEventListeners(); } \

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSIACCESSIBLEEVENTRECEIVER(_to) \
  NS_IMETHOD AddEventListeners(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->AddEventListeners(); } \
  NS_IMETHOD RemoveEventListeners(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->RemoveEventListeners(); } \

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsAccessibleEventReceiver : public nsIAccessibleEventReceiver
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIACCESSIBLEEVENTRECEIVER

  nsAccessibleEventReceiver();
  virtual ~nsAccessibleEventReceiver();
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsAccessibleEventReceiver, nsIAccessibleEventReceiver)

nsAccessibleEventReceiver::nsAccessibleEventReceiver()
{
  /* member initializers and constructor code */
}

nsAccessibleEventReceiver::~nsAccessibleEventReceiver()
{
  /* destructor code */
}

/* void addEventListeners (); */
NS_IMETHODIMP nsAccessibleEventReceiver::AddEventListeners()
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void removeEventListeners (); */
NS_IMETHODIMP nsAccessibleEventReceiver::RemoveEventListeners()
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsIAccessibleEventReceiver_h__ */
