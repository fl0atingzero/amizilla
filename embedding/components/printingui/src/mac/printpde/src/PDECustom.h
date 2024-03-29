/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/* ***** BEGIN LICENSE BLOCK *****
 * Version: MPL 1.1/GPL 2.0/LGPL 2.1
 *
 * The contents of this file are subject to the Mozilla Public License Version
 * 1.1 (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 * http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * The Original Code is mozilla.org code.
 *
 * The Initial Developer of the Original Code is
 * Netscape Communications Corporation.
 * Portions created by the Initial Developer are Copyright (C) 2002
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *   Conrad Carlen <ccarlen@netscape.com>
 *
 * Alternatively, the contents of this file may be used under the terms of
 * either the GNU General Public License Version 2 or later (the "GPL"), or
 * the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
 * in which case the provisions of the GPL or the LGPL are applicable instead
 * of those above. If you wish to allow use of your version of this file only
 * under the terms of either the GPL or the LGPL, and not to allow others to
 * use your version of this file under the terms of the MPL, indicate your
 * decision by deleting the provisions above and replace them with the notice
 * and other provisions required by the GPL or the LGPL. If you do not delete
 * the provisions above, a recipient may use your version of this file under
 * the terms of any one of the MPL, the GPL or the LGPL.
 *
 * ***** END LICENSE BLOCK ***** */

#ifndef __PDECUSTOM__
#define __PDECUSTOM__

#ifndef nsPDECommon_h___
#include "nsPDECommon.h"
#endif

/*
--------------------------------------------------------------------------------
**  kMyBundleIdentifier
**  
**  The identifier that's also used as the CFBundleIdentifier entry in the
**  property list. This ID should always be a unique string in Java-style
**  package format (substitute your vendor domain for "com.appvendor").
**  
--------------------------------------------------------------------------------
*/

#define  kMyBundleIdentifier \
            CFSTR("org.mozilla.pde." kMozPDESignature)

/*
--------------------------------------------------------------------------------
**  kMyPaneKindID
**  
**  For application-hosted PDEs, this unique Java-style package name is used
**  to identify your custom pane. Here we simply use the bundle identifier.
**  
**  For printer module-hosted PDEs, a unique Java-style package name is
**  recommended too, unless you are overriding a standard (Apple-supplied)
**  pane -- then you should use the appropriate kind ID constant from
**  PMPrintingDialogExtensions.h.
**
--------------------------------------------------------------------------------
*/

#define  kMyPaneKindID  kMyBundleIdentifier


/*
--------------------------------------------------------------------------------
**  kMyNibFile
**  
**  The name of your nib file (without the ".nib" extension).
**  
--------------------------------------------------------------------------------
*/

#define  kMyNibFile  CFSTR("PrintPDE")

/*
--------------------------------------------------------------------------------
**  kMyNibWindow
**  
**  The name of the Carbon window created from the nib interface.
**  
--------------------------------------------------------------------------------
*/

#define  kMyNibWindow  CFSTR("PrintPDE")


/*
--------------------------------------------------------------------------------
**  kMyAppPrintSettingsKey
**  
**  In order to use the print settings ticket, your application-hosted PDE
**  needs to define a ticket data storage and retrieval key by concatenating
**  this standard prefix with its unique 4-byte signature.
**  
--------------------------------------------------------------------------------
*/

#define  kMyAppPrintSettingsKey \
            CFSTR("com.apple.print.PrintSettingsTicket." kMozPDESignature)

/*
--------------------------------------------------------------------------------
**  kMyAppPageFormatKey
**  
**  In order to use the page format ticket, your application-hosted PDE
**  needs to define a ticket data storage and retrieval key by concatenating
**  this standard prefix with its unique 4-byte signature.
**
--------------------------------------------------------------------------------
*/

#define  kMyAppPageFormatKey \
            CFSTR("com.apple.print.PageFormatTicket." kMozPDESignature)


/*
--------------------------------------------------------------------------------
    If you provide user assistance using Help Viewer, define these two
    constants. Otherwise, comment them out.
--------------------------------------------------------------------------------
*/

//#define  kMyHelpFolder  CFSTR("Help")
//#define  kMyHelpFile    CFSTR("help.html")


/*
--------------------------------------------------------------------------------
    vertical and horizontal extent in pixels needed to display your
    custom interface
--------------------------------------------------------------------------------
*/

enum {
    kMyMaxV = 216,
    kMyMaxH = 478
};

/*
--------------------------------------------------------------------------------
    Indexes of radio buttons in our radio group control
--------------------------------------------------------------------------------
*/

enum {
    kFramesAsLaidOutIndex = 1,
    kFramesSelectedIndex,
    kFramesEachSeparatelyIndex,
};

/*
--------------------------------------------------------------------------------
    data types for a context that represents the state of the controls
    in an instance of your custom interface
--------------------------------------------------------------------------------
*/

typedef struct {
    ControlRef frameRadioGroup;
    ControlRef printSelCheck;
    ControlRef shrinkToFitCheck;
    ControlRef printBGColorsCheck;
    ControlRef printBGImagesCheck;
} MyControls;

typedef nsPrintExtensions MySettings;

typedef struct {
    MyControls controls;
    MySettings settings;
} MyCustomContextBlock;

typedef MyCustomContextBlock *MyCustomContext;


/*
--------------------------------------------------------------------------------
    functions you need to implement in your custom code
--------------------------------------------------------------------------------
*/

/*
    Sometime after calling MyGetCustomTitle (TRUE) to get the localized title
    of your custom pane, we call MyGetCustomTitle (FALSE) to release the copy.
*/

extern CFStringRef  MyGetCustomTitle (Boolean stillNeeded);

extern MyCustomContext  MyCreateCustomContext();
extern void             MyReleaseCustomContext (MyCustomContext);

extern OSStatus  MyEmbedCustomControls  (MyCustomContext, WindowRef, ControlRef);
extern OSStatus  MyGetSummaryText       (MyCustomContext, CFMutableArrayRef, CFMutableArrayRef);
extern OSStatus  MySyncPaneFromTicket   (MyCustomContext, PMPrintSession);
extern OSStatus  MySyncTicketFromPane   (MyCustomContext, PMPrintSession);


#endif
