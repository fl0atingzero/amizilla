/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM nsIAccessible.idl
 */

#ifndef __gen_nsIAccessible_h__
#define __gen_nsIAccessible_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

#ifndef __gen_nsIDOMNode_h__
#include "nsIDOMNode.h"
#endif

#ifndef __gen_domstubs_h__
#include "domstubs.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif

/* starting interface:    nsIAccessible */
#define NS_IACCESSIBLE_IID_STR "b26fbe47-9a5f-42a1-822b-082461ae4d6d"

#define NS_IACCESSIBLE_IID \
  {0xb26fbe47, 0x9a5f, 0x42a1, \
    { 0x82, 0x2b, 0x08, 0x24, 0x61, 0xae, 0x4d, 0x6d }}

class nsIAccessible : public nsISupports {
 public: 

  NS_DEFINE_STATIC_IID_ACCESSOR(NS_IACCESSIBLE_IID)

  /* readonly attribute nsIAccessible accParent; */
  NS_IMETHOD GetAccParent(nsIAccessible * *aAccParent) = 0;

  /* readonly attribute nsIAccessible accNextSibling; */
  NS_IMETHOD GetAccNextSibling(nsIAccessible * *aAccNextSibling) = 0;

  /* readonly attribute nsIAccessible accPreviousSibling; */
  NS_IMETHOD GetAccPreviousSibling(nsIAccessible * *aAccPreviousSibling) = 0;

  /* readonly attribute nsIAccessible accFirstChild; */
  NS_IMETHOD GetAccFirstChild(nsIAccessible * *aAccFirstChild) = 0;

  /* readonly attribute nsIAccessible accLastChild; */
  NS_IMETHOD GetAccLastChild(nsIAccessible * *aAccLastChild) = 0;

  /* readonly attribute long accChildCount; */
  NS_IMETHOD GetAccChildCount(PRInt32 *aAccChildCount) = 0;

  /* attribute AString accName; */
  NS_IMETHOD GetAccName(nsAString & aAccName) = 0;
  NS_IMETHOD SetAccName(const nsAString & aAccName) = 0;

  /* readonly attribute AString accValue; */
  NS_IMETHOD GetAccValue(nsAString & aAccValue) = 0;

  /* readonly attribute AString accDescription; */
  NS_IMETHOD GetAccDescription(nsAString & aAccDescription) = 0;

  /* readonly attribute AString accKeyboardShortcut; */
  NS_IMETHOD GetAccKeyboardShortcut(nsAString & aAccKeyboardShortcut) = 0;

  /* readonly attribute AString accKeybinding; */
  NS_IMETHOD GetAccKeybinding(nsAString & aAccKeybinding) = 0;

  /* readonly attribute unsigned long accRole; */
  NS_IMETHOD GetAccRole(PRUint32 *aAccRole) = 0;

  /* readonly attribute unsigned long accState; */
  NS_IMETHOD GetAccState(PRUint32 *aAccState) = 0;

  /* readonly attribute unsigned long accExtState; */
  NS_IMETHOD GetAccExtState(PRUint32 *aAccExtState) = 0;

  /* readonly attribute AString accHelp; */
  NS_IMETHOD GetAccHelp(nsAString & aAccHelp) = 0;

  /* readonly attribute nsIAccessible accFocused; */
  NS_IMETHOD GetAccFocused(nsIAccessible * *aAccFocused) = 0;

  /* nsIAccessible accGetAt (in long x, in long y); */
  NS_IMETHOD AccGetAt(PRInt32 x, PRInt32 y, nsIAccessible **_retval) = 0;

  /* nsIAccessible getChildAt (in long aChildIndex); */
  NS_IMETHOD GetChildAt(PRInt32 aChildIndex, nsIAccessible **_retval) = 0;

  /* nsIAccessible accNavigateRight (); */
  NS_IMETHOD AccNavigateRight(nsIAccessible **_retval) = 0;

  /* nsIAccessible accNavigateLeft (); */
  NS_IMETHOD AccNavigateLeft(nsIAccessible **_retval) = 0;

  /* nsIAccessible accNavigateUp (); */
  NS_IMETHOD AccNavigateUp(nsIAccessible **_retval) = 0;

  /* nsIAccessible accNavigateDown (); */
  NS_IMETHOD AccNavigateDown(nsIAccessible **_retval) = 0;

  /* void accGetBounds (out long x, out long y, out long width, out long height); */
  NS_IMETHOD AccGetBounds(PRInt32 *x, PRInt32 *y, PRInt32 *width, PRInt32 *height) = 0;

  /* void accAddSelection (); */
  NS_IMETHOD AccAddSelection(void) = 0;

  /* void accRemoveSelection (); */
  NS_IMETHOD AccRemoveSelection(void) = 0;

  /* void accExtendSelection (); */
  NS_IMETHOD AccExtendSelection(void) = 0;

  /* void accTakeSelection (); */
  NS_IMETHOD AccTakeSelection(void) = 0;

  /* void accTakeFocus (); */
  NS_IMETHOD AccTakeFocus(void) = 0;

  /* readonly attribute PRUint8 accNumActions; */
  NS_IMETHOD GetAccNumActions(PRUint8 *aAccNumActions) = 0;

  /* AString getAccActionName (in PRUint8 index); */
  NS_IMETHOD GetAccActionName(PRUint8 index, nsAString & _retval) = 0;

  /* void accDoAction (in PRUint8 index); */
  NS_IMETHOD AccDoAction(PRUint8 index) = 0;

  /* nsIDOMNode accGetDOMNode (); */
  NS_IMETHOD AccGetDOMNode(nsIDOMNode **_retval) = 0;

  /* [noscript] void setAccParent (in nsIAccessible aAccParent); */
  NS_IMETHOD SetAccParent(nsIAccessible *aAccParent) = 0;

  /* [noscript] void setAccFirstChild (in nsIAccessible aAccFirstChild); */
  NS_IMETHOD SetAccFirstChild(nsIAccessible *aAccFirstChild) = 0;

  /* [noscript] void setAccNextSibling (in nsIAccessible aAccNextSibling); */
  NS_IMETHOD SetAccNextSibling(nsIAccessible *aAccNextSibling) = 0;

  /* [noscript] void invalidateChildren (); */
  NS_IMETHOD InvalidateChildren(void) = 0;

  /* [noscript] void fireToolkitEvent (in unsigned long aEvent, in nsIAccessible aTarget, in voidPtr aData); */
  NS_IMETHOD FireToolkitEvent(PRUint32 aEvent, nsIAccessible *aTarget, void * aData) = 0;

  /* [noscript] void getNativeInterface (out voidPtr aOutAccessible); */
  NS_IMETHOD GetNativeInterface(void * *aOutAccessible) = 0;

  enum { STATE_UNAVAILABLE = 1U };

  enum { STATE_SELECTED = 2U };

  enum { STATE_FOCUSED = 4U };

  enum { STATE_PRESSED = 8U };

  enum { STATE_CHECKED = 16U };

  enum { STATE_MIXED = 32U };

  enum { STATE_READONLY = 64U };

  enum { STATE_HOTTRACKED = 128U };

  enum { STATE_DEFAULT = 256U };

  enum { STATE_EXPANDED = 512U };

  enum { STATE_COLLAPSED = 1024U };

  enum { STATE_BUSY = 2048U };

  enum { STATE_FLOATING = 4096U };

  enum { STATE_MARQUEED = 8192U };

  enum { STATE_ANIMATED = 16384U };

  enum { STATE_INVISIBLE = 32768U };

  enum { STATE_OFFSCREEN = 65536U };

  enum { STATE_SIZEABLE = 131072U };

  enum { STATE_MOVEABLE = 262144U };

  enum { STATE_SELFVOICING = 524288U };

  enum { STATE_FOCUSABLE = 1048576U };

  enum { STATE_SELECTABLE = 2097152U };

  enum { STATE_LINKED = 4194304U };

  enum { STATE_TRAVERSED = 8388608U };

  enum { STATE_MULTISELECTABLE = 16777216U };

  enum { STATE_EXTSELECTABLE = 33554432U };

  enum { STATE_ALERT_LOW = 67108864U };

  enum { STATE_ALERT_MEDIUM = 134217728U };

  enum { STATE_ALERT_HIGH = 268435456U };

  enum { STATE_PROTECTED = 536870912U };

  enum { STATE_HASPOPUP = 1073741824U };

  enum { STATE_INVALID = 2097152U };

  enum { STATE_ACTIVE = 4194304U };

  enum { STATE_EXPANDABLE = 8388608U };

  enum { STATE_MODAL = 16777216U };

  enum { STATE_MULTI_LINE = 33554432U };

  enum { STATE_SENSITIVE = 67108864U };

  enum { STATE_RESIZABLE = 134217728U };

  enum { STATE_SHOWING = 268435456U };

  enum { STATE_SINGLE_LINE = 536870912U };

  enum { STATE_TRANSIENT = 1073741824U };

  enum { STATE_VERTICAL = 2147483648U };

#ifdef MOZ_ACCESSIBILITY_ATK
/*******************************************************************************
The following nsIAccessible roles are traslated to ATK_ROLE_UNKNOWN
  ROLE_TITLEBAR, ROLE_SOUND, ROLE_CURSOR, ROLE_CARET, ROLE_BORDER,
  ROLE_GROUPING, ROLE_EQUATION, ROLE_COLUMN, ROLE_ROW, ROLE_LINK,
  ROLE_WHITESPACE, ROLE_CLOCK,
  ROLE_IPADDRESS
  ROLE_GRIP
    The object represents a special mouse pointer, which allows a user to
    manipulate user interface elements such as windows.
  ROLE_HELPBALLOON
    The object displays a Help topic in the form of a ToolTip or Help balloon.
  ROLE_PROPERTYPAGE
    The object represents a property sheet.
  ROLE_INDICATOR
    The object represents an indicator, such as a pointer graphic pointing to
    the currrent item.
  ROLE_HOTKEYFIELD
    The object represents a hot-key field that allow the user to enter a
    sequence of keystroke.
The following ATK roles have no corresponding nsIAccessible roles. Perhaps
there are not these types of widget/control in Mozilla, so don't need these
ATK roles? Or need add some of them?
  ATK_ROLE_ARROW
    An arrow in one of the four cardinal directions.
  ATK_ROLE_INTERNAL_FRAME
    A frame-like object that is clipped by a desktop pane.
  ATK_ROLE_ACCEL_LABEL, ATK_ROLE_CANVAS, ATK_ROLE_CHECK_MENU_ITEM,
  ATK_ROLE_COLOR_CHOOSER, ATK_ROLE_DATE_EDITOR, ATK_ROLE_DESKTOP_ICON,
  ATK_ROLE_DESKTOP_FRAME, ATK_ROLE_DIRECTORY_PANE, ATK_ROLE_FILE_CHOOSER,
  ATK_ROLE_FILLER, ATK_ROLE_FONT_CHOOSER, ATK_ROLE_GLASS_PANE,
  ATK_ROLE_HTML_CONTAINER, ATK_ROLE_ICON, ATK_ROLE_LAYERED_PANE,
  ATK_ROLE_POPUP_MENU, ATK_ROLE_OPTION_PANE, ATK_ROLE_PASSWORD_TEXT,
  ATK_ROLE_RADIO_MENU_ITEM, ATK_ROLE_ROOT_PANE, ATK_ROLE_SCROLL_PANE,
  ATK_ROLE_SPLIT_PANE, ATK_ROLE_TEAR_OFF_MENU_ITEM, ATK_ROLE_TERMINAL,
  ATK_ROLE_TOGGLE_BUTTON, ATK_ROLE_TREE_TABLE, ATK_ROLE_VIEWPORT, ATK_ROLE_LABEL
Important:
  Following value should keep synchronization with the definitions in atk.h
*******************************************************************************/
  enum { ROLE_TITLEBAR = 66U };    // ATK_ROLE_UNKNOWN
  enum { ROLE_MENUBAR = 33U };     // ATK_ROLE_MENU_BAR
  enum { ROLE_SCROLLBAR = 47U };   // ATK_ROLE_SCROLL_BAR
  enum { ROLE_GRIP = 66U };        // ATK_ROLE_UNKNOWN
  enum { ROLE_SOUND = 66U };       // ATK_ROLE_UNKNOWN
  enum { ROLE_CURSOR = 66U };      // ATK_ROLE_UNKNOWN
  enum { ROLE_CARET = 66U };       // ATK_ROLE_UNKNOWN
  enum { ROLE_ALERT = 2U };        // ATK_ROLE_ALERT
  enum { ROLE_WINDOW = 68U };      // ATK_ROLE_WINDOW
  // An object used for drawing custom user interface elements
  enum { ROLE_CLIENT = 18U };      // ATK_ROLE_DRAWING_AREA
  enum { ROLE_MENUPOPUP = 32U };   // ATK_ROLE_MENU
  enum { ROLE_MENUITEM = 34U };    // ATK_ROLE_MENU_ITEM
  enum { ROLE_TOOLTIP = 63U };     // ATK_ROLE_TOOL_TIP
  // The object represents a main window for a application
  enum { ROLE_APPLICATION = 73U }; // ATK_ROLE_APPLICATION
  // The object represents a document window, only for MDI windows
  enum { ROLE_DOCUMENT = 68U };    // ATK_ROLE_WINDOW
  enum { ROLE_PANE = 38U };        // ATK_ROLE_PANEL
  enum { ROLE_CHART = 26U };       // ATK_ROLE_IMAGE
  enum { ROLE_DIALOG = 16U };      // ATK_ROLE_DIALOG
  enum { ROLE_BORDER = 66U };      // ATK_ROLE_UNKNOWN
  enum { ROLE_GROUPING = 66U };    // ATK_ROLE_UNKNOWN
  enum { ROLE_SEPARATOR = 49U };   // ATK_ROLE_SEPARATOR
  enum { ROLE_TOOLBAR = 62U };     // ATK_ROLE_TOOL_BAR
  enum { ROLE_STATUSBAR = 53U };   // ATK_ROLE_STATUSBAR
  enum { ROLE_TABLE = 54U };       // ATK_ROLE_TABLE
  // Or ATK_ROLE_TABLE_COLUMN_HEADER?
  enum { ROLE_COLUMNHEADER = 10U };// ATK_ROLE_COLUMN_HEADER
  // Or ATK_ROLE_TABLE_ROW_HEADER ?
  enum { ROLE_ROWHEADER = 46U };   // ATK_ROLE_ROW_HEADER
  enum { ROLE_COLUMN = 66U };      // ATK_ROLE_UNKNOWN
  enum { ROLE_ROW = 66U };         // ATK_ROLE_UNKNOWN
  enum { ROLE_CELL = 55U };        // ATK_ROLE_TABLE_CELL
  enum { ROLE_LINK = 66U };        // ATK_ROLE_UNKNOWN
  enum { ROLE_HELPBALLOON = 66U }; // ATK_ROLE_UNKNOWN
  // The object represents a cartoon-like graphic object
  enum { ROLE_CHARACTER = 26U };   // ATK_ROLE_IMAGE
  enum { ROLE_LIST = 30U };        // ATK_ROLE_LIST
  enum { ROLE_LISTITEM = 31U };    // ATK_ROLE_LIST_ITEM
  // The object represents an outline or tree structure
  enum { ROLE_OUTLINE = 64U };     // ATK_ROLE_TREE
  // The object represents an item in an outline or tree structure
  enum { ROLE_OUTLINEITEM = 31U }; // ATK_ROLE_LIST_ITEM
  enum { ROLE_PAGETAB = 36U };     // ATK_ROLE_PAGE_TAB
  enum { ROLE_PROPERTYPAGE = 66U };// ATK_ROLE_UNKNOWN
  enum { ROLE_INDICATOR = 66U };   // ATK_ROLE_UNKNOWN
  enum { ROLE_GRAPHIC = 26U };     // ATK_ROLE_IMAGE
  // Read-only text, can't be modified or selected
  enum { ROLE_STATICTEXT = 60U };  // ATK_ROLE_TEXT
  enum { ROLE_TEXT = 60U };        // ATK_ROLE_TEXT
  enum { ROLE_PUSHBUTTON = 42U };  // ATK_ROLE_PUSH_BUTTON
  enum { ROLE_CHECKBUTTON = 7U };  // ATK_ROLE_CHECK_BOX
  enum { ROLE_RADIOBUTTON = 43U }; // ATK_ROLE_RADIO_BUTTON
  enum { ROLE_COMBOBOX = 11U };    // ATK_ROLE_COMBO_BOX
  // Just represents the calender control
  enum { ROLE_DROPLIST = 5U };     // ATK_ROLE_CALENDAR
  enum { ROLE_PROGRESSBAR = 41U }; // ATK_ROLE_PROGRESS_BAR
  enum { ROLE_DIAL = 15U };        // ATK_ROLE_DIAL
  enum { ROLE_HOTKEYFIELD = 66U }; // ATK_ROLE_UNKNOWN
  enum { ROLE_SLIDER = 50U };      // ATK_ROLE_SLIDER
  enum { ROLE_SPINBUTTON = 52U };  // ATK_ROLE_SPIN_BUTTON
  enum { ROLE_DIAGRAM = 26U };     // ATK_ROLE_IMAGE
  enum { ROLE_ANIMATION = 3U };    // ATK_ROLE_ANIMATION
  enum { ROLE_EQUATION = 66U };    // ATK_ROLE_UNKNOWN
  enum { ROLE_BUTTONDROPDOWN = 42U }; // ATK_ROLE_PUSH_BUTTON
  enum { ROLE_BUTTONMENU = 42U };  // ATK_ROLE_PUSH_BUTTON
  // Represents a button that drops down a grid
  enum { ROLE_BUTTONDROPDOWNGRID = 66U }; // ATK_ROLE_UNKNOWN
  enum { ROLE_WHITESPACE = 66U };  // ATK_ROLE_UNKNOWN
  enum { ROLE_PAGETABLIST = 37U }; // ATK_ROLE_PAGE_TAB_LIST
  enum { ROLE_CLOCK = 66U };       // ATK_ROLE_UNKNOWN
  // Represents a button on the toolbar that has a drop-down list icon
  // directly adjacent to the button
  enum { ROLE_SPLITBUTTON = 42U }; // ATK_ROLE_PUSH_BUTTON
  enum { ROLE_IPADDRESS = 66U };   // ATK_ROLE_UNKNOWN
  enum { ROLE_NOTHING = 0U };      // ATK_ROLE_INVALID
#else
// MSAA Roles - only one per nsIAccessible or IAccessible
  enum { ROLE_TITLEBAR = 1U };
  enum { ROLE_MENUBAR = 2U };
  enum { ROLE_SCROLLBAR = 3U };
  enum { ROLE_GRIP = 4U };
  enum { ROLE_SOUND = 5U };
  enum { ROLE_CURSOR = 6U };
  enum { ROLE_CARET = 7U };
  enum { ROLE_ALERT = 8U };
  enum { ROLE_WINDOW = 9U };
  enum { ROLE_CLIENT = 10U };
  enum { ROLE_MENUPOPUP = 11U };
  enum { ROLE_MENUITEM = 12U };
  enum { ROLE_TOOLTIP = 13U };
  enum { ROLE_APPLICATION = 14U };
  enum { ROLE_DOCUMENT = 15U };
  enum { ROLE_PANE = 16U };
  enum { ROLE_CHART = 17U };
  enum { ROLE_DIALOG = 18U };
  enum { ROLE_BORDER = 19U };
  enum { ROLE_GROUPING = 20U };
  enum { ROLE_SEPARATOR = 21U };
  enum { ROLE_TOOLBAR = 22U };
  enum { ROLE_STATUSBAR = 23U };
  enum { ROLE_TABLE = 24U };
  enum { ROLE_COLUMNHEADER = 25U };
  enum { ROLE_ROWHEADER = 26U };
  enum { ROLE_COLUMN = 27U };
  enum { ROLE_ROW = 28U };
  enum { ROLE_CELL = 29U };
  enum { ROLE_LINK = 30U };
  enum { ROLE_HELPBALLOON = 31U };
  enum { ROLE_CHARACTER = 32U };
  enum { ROLE_LIST = 33U };
  enum { ROLE_LISTITEM = 34U };
  enum { ROLE_OUTLINE = 35U };
  enum { ROLE_OUTLINEITEM = 36U };
  enum { ROLE_PAGETAB = 37U };
  enum { ROLE_PROPERTYPAGE = 38U };
  enum { ROLE_INDICATOR = 39U };
  enum { ROLE_GRAPHIC = 40U };
  enum { ROLE_STATICTEXT = 41U };
  enum { ROLE_TEXT = 42U };
  enum { ROLE_PUSHBUTTON = 43U };
  enum { ROLE_CHECKBUTTON = 44U };
  enum { ROLE_RADIOBUTTON = 45U };
  enum { ROLE_COMBOBOX = 46U };
  enum { ROLE_DROPLIST = 47U };
  enum { ROLE_PROGRESSBAR = 48U };
  enum { ROLE_DIAL = 49U };
  enum { ROLE_HOTKEYFIELD = 50U };
  enum { ROLE_SLIDER = 51U };
  enum { ROLE_SPINBUTTON = 52U };
  enum { ROLE_DIAGRAM = 53U };
  enum { ROLE_ANIMATION = 54U };
  enum { ROLE_EQUATION = 55U };
  enum { ROLE_BUTTONDROPDOWN = 56U };
  enum { ROLE_BUTTONMENU = 57U };
  enum { ROLE_BUTTONDROPDOWNGRID = 58U };
  enum { ROLE_WHITESPACE = 59U };
  enum { ROLE_PAGETABLIST = 60U };
  enum { ROLE_CLOCK = 61U };
  enum { ROLE_SPLITBUTTON = 62U };
  enum { ROLE_IPADDRESS = 63U };
  enum { ROLE_NOTHING = 4294967295U };
#endif
};

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSIACCESSIBLE \
  NS_IMETHOD GetAccParent(nsIAccessible * *aAccParent); \
  NS_IMETHOD GetAccNextSibling(nsIAccessible * *aAccNextSibling); \
  NS_IMETHOD GetAccPreviousSibling(nsIAccessible * *aAccPreviousSibling); \
  NS_IMETHOD GetAccFirstChild(nsIAccessible * *aAccFirstChild); \
  NS_IMETHOD GetAccLastChild(nsIAccessible * *aAccLastChild); \
  NS_IMETHOD GetAccChildCount(PRInt32 *aAccChildCount); \
  NS_IMETHOD GetAccName(nsAString & aAccName); \
  NS_IMETHOD SetAccName(const nsAString & aAccName); \
  NS_IMETHOD GetAccValue(nsAString & aAccValue); \
  NS_IMETHOD GetAccDescription(nsAString & aAccDescription); \
  NS_IMETHOD GetAccKeyboardShortcut(nsAString & aAccKeyboardShortcut); \
  NS_IMETHOD GetAccKeybinding(nsAString & aAccKeybinding); \
  NS_IMETHOD GetAccRole(PRUint32 *aAccRole); \
  NS_IMETHOD GetAccState(PRUint32 *aAccState); \
  NS_IMETHOD GetAccExtState(PRUint32 *aAccExtState); \
  NS_IMETHOD GetAccHelp(nsAString & aAccHelp); \
  NS_IMETHOD GetAccFocused(nsIAccessible * *aAccFocused); \
  NS_IMETHOD AccGetAt(PRInt32 x, PRInt32 y, nsIAccessible **_retval); \
  NS_IMETHOD GetChildAt(PRInt32 aChildIndex, nsIAccessible **_retval); \
  NS_IMETHOD AccNavigateRight(nsIAccessible **_retval); \
  NS_IMETHOD AccNavigateLeft(nsIAccessible **_retval); \
  NS_IMETHOD AccNavigateUp(nsIAccessible **_retval); \
  NS_IMETHOD AccNavigateDown(nsIAccessible **_retval); \
  NS_IMETHOD AccGetBounds(PRInt32 *x, PRInt32 *y, PRInt32 *width, PRInt32 *height); \
  NS_IMETHOD AccAddSelection(void); \
  NS_IMETHOD AccRemoveSelection(void); \
  NS_IMETHOD AccExtendSelection(void); \
  NS_IMETHOD AccTakeSelection(void); \
  NS_IMETHOD AccTakeFocus(void); \
  NS_IMETHOD GetAccNumActions(PRUint8 *aAccNumActions); \
  NS_IMETHOD GetAccActionName(PRUint8 index, nsAString & _retval); \
  NS_IMETHOD AccDoAction(PRUint8 index); \
  NS_IMETHOD AccGetDOMNode(nsIDOMNode **_retval); \
  NS_IMETHOD SetAccParent(nsIAccessible *aAccParent); \
  NS_IMETHOD SetAccFirstChild(nsIAccessible *aAccFirstChild); \
  NS_IMETHOD SetAccNextSibling(nsIAccessible *aAccNextSibling); \
  NS_IMETHOD InvalidateChildren(void); \
  NS_IMETHOD FireToolkitEvent(PRUint32 aEvent, nsIAccessible *aTarget, void * aData); \
  NS_IMETHOD GetNativeInterface(void * *aOutAccessible); \

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSIACCESSIBLE(_to) \
  NS_IMETHOD GetAccParent(nsIAccessible * *aAccParent) { return _to GetAccParent(aAccParent); } \
  NS_IMETHOD GetAccNextSibling(nsIAccessible * *aAccNextSibling) { return _to GetAccNextSibling(aAccNextSibling); } \
  NS_IMETHOD GetAccPreviousSibling(nsIAccessible * *aAccPreviousSibling) { return _to GetAccPreviousSibling(aAccPreviousSibling); } \
  NS_IMETHOD GetAccFirstChild(nsIAccessible * *aAccFirstChild) { return _to GetAccFirstChild(aAccFirstChild); } \
  NS_IMETHOD GetAccLastChild(nsIAccessible * *aAccLastChild) { return _to GetAccLastChild(aAccLastChild); } \
  NS_IMETHOD GetAccChildCount(PRInt32 *aAccChildCount) { return _to GetAccChildCount(aAccChildCount); } \
  NS_IMETHOD GetAccName(nsAString & aAccName) { return _to GetAccName(aAccName); } \
  NS_IMETHOD SetAccName(const nsAString & aAccName) { return _to SetAccName(aAccName); } \
  NS_IMETHOD GetAccValue(nsAString & aAccValue) { return _to GetAccValue(aAccValue); } \
  NS_IMETHOD GetAccDescription(nsAString & aAccDescription) { return _to GetAccDescription(aAccDescription); } \
  NS_IMETHOD GetAccKeyboardShortcut(nsAString & aAccKeyboardShortcut) { return _to GetAccKeyboardShortcut(aAccKeyboardShortcut); } \
  NS_IMETHOD GetAccKeybinding(nsAString & aAccKeybinding) { return _to GetAccKeybinding(aAccKeybinding); } \
  NS_IMETHOD GetAccRole(PRUint32 *aAccRole) { return _to GetAccRole(aAccRole); } \
  NS_IMETHOD GetAccState(PRUint32 *aAccState) { return _to GetAccState(aAccState); } \
  NS_IMETHOD GetAccExtState(PRUint32 *aAccExtState) { return _to GetAccExtState(aAccExtState); } \
  NS_IMETHOD GetAccHelp(nsAString & aAccHelp) { return _to GetAccHelp(aAccHelp); } \
  NS_IMETHOD GetAccFocused(nsIAccessible * *aAccFocused) { return _to GetAccFocused(aAccFocused); } \
  NS_IMETHOD AccGetAt(PRInt32 x, PRInt32 y, nsIAccessible **_retval) { return _to AccGetAt(x, y, _retval); } \
  NS_IMETHOD GetChildAt(PRInt32 aChildIndex, nsIAccessible **_retval) { return _to GetChildAt(aChildIndex, _retval); } \
  NS_IMETHOD AccNavigateRight(nsIAccessible **_retval) { return _to AccNavigateRight(_retval); } \
  NS_IMETHOD AccNavigateLeft(nsIAccessible **_retval) { return _to AccNavigateLeft(_retval); } \
  NS_IMETHOD AccNavigateUp(nsIAccessible **_retval) { return _to AccNavigateUp(_retval); } \
  NS_IMETHOD AccNavigateDown(nsIAccessible **_retval) { return _to AccNavigateDown(_retval); } \
  NS_IMETHOD AccGetBounds(PRInt32 *x, PRInt32 *y, PRInt32 *width, PRInt32 *height) { return _to AccGetBounds(x, y, width, height); } \
  NS_IMETHOD AccAddSelection(void) { return _to AccAddSelection(); } \
  NS_IMETHOD AccRemoveSelection(void) { return _to AccRemoveSelection(); } \
  NS_IMETHOD AccExtendSelection(void) { return _to AccExtendSelection(); } \
  NS_IMETHOD AccTakeSelection(void) { return _to AccTakeSelection(); } \
  NS_IMETHOD AccTakeFocus(void) { return _to AccTakeFocus(); } \
  NS_IMETHOD GetAccNumActions(PRUint8 *aAccNumActions) { return _to GetAccNumActions(aAccNumActions); } \
  NS_IMETHOD GetAccActionName(PRUint8 index, nsAString & _retval) { return _to GetAccActionName(index, _retval); } \
  NS_IMETHOD AccDoAction(PRUint8 index) { return _to AccDoAction(index); } \
  NS_IMETHOD AccGetDOMNode(nsIDOMNode **_retval) { return _to AccGetDOMNode(_retval); } \
  NS_IMETHOD SetAccParent(nsIAccessible *aAccParent) { return _to SetAccParent(aAccParent); } \
  NS_IMETHOD SetAccFirstChild(nsIAccessible *aAccFirstChild) { return _to SetAccFirstChild(aAccFirstChild); } \
  NS_IMETHOD SetAccNextSibling(nsIAccessible *aAccNextSibling) { return _to SetAccNextSibling(aAccNextSibling); } \
  NS_IMETHOD InvalidateChildren(void) { return _to InvalidateChildren(); } \
  NS_IMETHOD FireToolkitEvent(PRUint32 aEvent, nsIAccessible *aTarget, void * aData) { return _to FireToolkitEvent(aEvent, aTarget, aData); } \
  NS_IMETHOD GetNativeInterface(void * *aOutAccessible) { return _to GetNativeInterface(aOutAccessible); } \

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSIACCESSIBLE(_to) \
  NS_IMETHOD GetAccParent(nsIAccessible * *aAccParent) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetAccParent(aAccParent); } \
  NS_IMETHOD GetAccNextSibling(nsIAccessible * *aAccNextSibling) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetAccNextSibling(aAccNextSibling); } \
  NS_IMETHOD GetAccPreviousSibling(nsIAccessible * *aAccPreviousSibling) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetAccPreviousSibling(aAccPreviousSibling); } \
  NS_IMETHOD GetAccFirstChild(nsIAccessible * *aAccFirstChild) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetAccFirstChild(aAccFirstChild); } \
  NS_IMETHOD GetAccLastChild(nsIAccessible * *aAccLastChild) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetAccLastChild(aAccLastChild); } \
  NS_IMETHOD GetAccChildCount(PRInt32 *aAccChildCount) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetAccChildCount(aAccChildCount); } \
  NS_IMETHOD GetAccName(nsAString & aAccName) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetAccName(aAccName); } \
  NS_IMETHOD SetAccName(const nsAString & aAccName) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetAccName(aAccName); } \
  NS_IMETHOD GetAccValue(nsAString & aAccValue) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetAccValue(aAccValue); } \
  NS_IMETHOD GetAccDescription(nsAString & aAccDescription) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetAccDescription(aAccDescription); } \
  NS_IMETHOD GetAccKeyboardShortcut(nsAString & aAccKeyboardShortcut) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetAccKeyboardShortcut(aAccKeyboardShortcut); } \
  NS_IMETHOD GetAccKeybinding(nsAString & aAccKeybinding) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetAccKeybinding(aAccKeybinding); } \
  NS_IMETHOD GetAccRole(PRUint32 *aAccRole) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetAccRole(aAccRole); } \
  NS_IMETHOD GetAccState(PRUint32 *aAccState) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetAccState(aAccState); } \
  NS_IMETHOD GetAccExtState(PRUint32 *aAccExtState) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetAccExtState(aAccExtState); } \
  NS_IMETHOD GetAccHelp(nsAString & aAccHelp) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetAccHelp(aAccHelp); } \
  NS_IMETHOD GetAccFocused(nsIAccessible * *aAccFocused) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetAccFocused(aAccFocused); } \
  NS_IMETHOD AccGetAt(PRInt32 x, PRInt32 y, nsIAccessible **_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->AccGetAt(x, y, _retval); } \
  NS_IMETHOD GetChildAt(PRInt32 aChildIndex, nsIAccessible **_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetChildAt(aChildIndex, _retval); } \
  NS_IMETHOD AccNavigateRight(nsIAccessible **_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->AccNavigateRight(_retval); } \
  NS_IMETHOD AccNavigateLeft(nsIAccessible **_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->AccNavigateLeft(_retval); } \
  NS_IMETHOD AccNavigateUp(nsIAccessible **_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->AccNavigateUp(_retval); } \
  NS_IMETHOD AccNavigateDown(nsIAccessible **_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->AccNavigateDown(_retval); } \
  NS_IMETHOD AccGetBounds(PRInt32 *x, PRInt32 *y, PRInt32 *width, PRInt32 *height) { return !_to ? NS_ERROR_NULL_POINTER : _to->AccGetBounds(x, y, width, height); } \
  NS_IMETHOD AccAddSelection(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->AccAddSelection(); } \
  NS_IMETHOD AccRemoveSelection(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->AccRemoveSelection(); } \
  NS_IMETHOD AccExtendSelection(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->AccExtendSelection(); } \
  NS_IMETHOD AccTakeSelection(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->AccTakeSelection(); } \
  NS_IMETHOD AccTakeFocus(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->AccTakeFocus(); } \
  NS_IMETHOD GetAccNumActions(PRUint8 *aAccNumActions) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetAccNumActions(aAccNumActions); } \
  NS_IMETHOD GetAccActionName(PRUint8 index, nsAString & _retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetAccActionName(index, _retval); } \
  NS_IMETHOD AccDoAction(PRUint8 index) { return !_to ? NS_ERROR_NULL_POINTER : _to->AccDoAction(index); } \
  NS_IMETHOD AccGetDOMNode(nsIDOMNode **_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->AccGetDOMNode(_retval); } \
  NS_IMETHOD SetAccParent(nsIAccessible *aAccParent) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetAccParent(aAccParent); } \
  NS_IMETHOD SetAccFirstChild(nsIAccessible *aAccFirstChild) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetAccFirstChild(aAccFirstChild); } \
  NS_IMETHOD SetAccNextSibling(nsIAccessible *aAccNextSibling) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetAccNextSibling(aAccNextSibling); } \
  NS_IMETHOD InvalidateChildren(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->InvalidateChildren(); } \
  NS_IMETHOD FireToolkitEvent(PRUint32 aEvent, nsIAccessible *aTarget, void * aData) { return !_to ? NS_ERROR_NULL_POINTER : _to->FireToolkitEvent(aEvent, aTarget, aData); } \
  NS_IMETHOD GetNativeInterface(void * *aOutAccessible) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetNativeInterface(aOutAccessible); } \

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsAccessible : public nsIAccessible
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIACCESSIBLE

  nsAccessible();
  virtual ~nsAccessible();
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsAccessible, nsIAccessible)

nsAccessible::nsAccessible()
{
  /* member initializers and constructor code */
}

nsAccessible::~nsAccessible()
{
  /* destructor code */
}

/* readonly attribute nsIAccessible accParent; */
NS_IMETHODIMP nsAccessible::GetAccParent(nsIAccessible * *aAccParent)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute nsIAccessible accNextSibling; */
NS_IMETHODIMP nsAccessible::GetAccNextSibling(nsIAccessible * *aAccNextSibling)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute nsIAccessible accPreviousSibling; */
NS_IMETHODIMP nsAccessible::GetAccPreviousSibling(nsIAccessible * *aAccPreviousSibling)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute nsIAccessible accFirstChild; */
NS_IMETHODIMP nsAccessible::GetAccFirstChild(nsIAccessible * *aAccFirstChild)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute nsIAccessible accLastChild; */
NS_IMETHODIMP nsAccessible::GetAccLastChild(nsIAccessible * *aAccLastChild)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute long accChildCount; */
NS_IMETHODIMP nsAccessible::GetAccChildCount(PRInt32 *aAccChildCount)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute AString accName; */
NS_IMETHODIMP nsAccessible::GetAccName(nsAString & aAccName)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsAccessible::SetAccName(const nsAString & aAccName)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute AString accValue; */
NS_IMETHODIMP nsAccessible::GetAccValue(nsAString & aAccValue)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute AString accDescription; */
NS_IMETHODIMP nsAccessible::GetAccDescription(nsAString & aAccDescription)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute AString accKeyboardShortcut; */
NS_IMETHODIMP nsAccessible::GetAccKeyboardShortcut(nsAString & aAccKeyboardShortcut)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute AString accKeybinding; */
NS_IMETHODIMP nsAccessible::GetAccKeybinding(nsAString & aAccKeybinding)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute unsigned long accRole; */
NS_IMETHODIMP nsAccessible::GetAccRole(PRUint32 *aAccRole)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute unsigned long accState; */
NS_IMETHODIMP nsAccessible::GetAccState(PRUint32 *aAccState)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute unsigned long accExtState; */
NS_IMETHODIMP nsAccessible::GetAccExtState(PRUint32 *aAccExtState)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute AString accHelp; */
NS_IMETHODIMP nsAccessible::GetAccHelp(nsAString & aAccHelp)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute nsIAccessible accFocused; */
NS_IMETHODIMP nsAccessible::GetAccFocused(nsIAccessible * *aAccFocused)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* nsIAccessible accGetAt (in long x, in long y); */
NS_IMETHODIMP nsAccessible::AccGetAt(PRInt32 x, PRInt32 y, nsIAccessible **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* nsIAccessible getChildAt (in long aChildIndex); */
NS_IMETHODIMP nsAccessible::GetChildAt(PRInt32 aChildIndex, nsIAccessible **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* nsIAccessible accNavigateRight (); */
NS_IMETHODIMP nsAccessible::AccNavigateRight(nsIAccessible **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* nsIAccessible accNavigateLeft (); */
NS_IMETHODIMP nsAccessible::AccNavigateLeft(nsIAccessible **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* nsIAccessible accNavigateUp (); */
NS_IMETHODIMP nsAccessible::AccNavigateUp(nsIAccessible **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* nsIAccessible accNavigateDown (); */
NS_IMETHODIMP nsAccessible::AccNavigateDown(nsIAccessible **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void accGetBounds (out long x, out long y, out long width, out long height); */
NS_IMETHODIMP nsAccessible::AccGetBounds(PRInt32 *x, PRInt32 *y, PRInt32 *width, PRInt32 *height)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void accAddSelection (); */
NS_IMETHODIMP nsAccessible::AccAddSelection()
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void accRemoveSelection (); */
NS_IMETHODIMP nsAccessible::AccRemoveSelection()
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void accExtendSelection (); */
NS_IMETHODIMP nsAccessible::AccExtendSelection()
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void accTakeSelection (); */
NS_IMETHODIMP nsAccessible::AccTakeSelection()
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void accTakeFocus (); */
NS_IMETHODIMP nsAccessible::AccTakeFocus()
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute PRUint8 accNumActions; */
NS_IMETHODIMP nsAccessible::GetAccNumActions(PRUint8 *aAccNumActions)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* AString getAccActionName (in PRUint8 index); */
NS_IMETHODIMP nsAccessible::GetAccActionName(PRUint8 index, nsAString & _retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void accDoAction (in PRUint8 index); */
NS_IMETHODIMP nsAccessible::AccDoAction(PRUint8 index)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* nsIDOMNode accGetDOMNode (); */
NS_IMETHODIMP nsAccessible::AccGetDOMNode(nsIDOMNode **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* [noscript] void setAccParent (in nsIAccessible aAccParent); */
NS_IMETHODIMP nsAccessible::SetAccParent(nsIAccessible *aAccParent)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* [noscript] void setAccFirstChild (in nsIAccessible aAccFirstChild); */
NS_IMETHODIMP nsAccessible::SetAccFirstChild(nsIAccessible *aAccFirstChild)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* [noscript] void setAccNextSibling (in nsIAccessible aAccNextSibling); */
NS_IMETHODIMP nsAccessible::SetAccNextSibling(nsIAccessible *aAccNextSibling)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* [noscript] void invalidateChildren (); */
NS_IMETHODIMP nsAccessible::InvalidateChildren()
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* [noscript] void fireToolkitEvent (in unsigned long aEvent, in nsIAccessible aTarget, in voidPtr aData); */
NS_IMETHODIMP nsAccessible::FireToolkitEvent(PRUint32 aEvent, nsIAccessible *aTarget, void * aData)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* [noscript] void getNativeInterface (out voidPtr aOutAccessible); */
NS_IMETHODIMP nsAccessible::GetNativeInterface(void * *aOutAccessible)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsIAccessible_h__ */
