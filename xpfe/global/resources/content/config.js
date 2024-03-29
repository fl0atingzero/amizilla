/* -*- Mode: Java; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*-
 * The contents of this file are subject to the Netscape Public
 * License Version 1.1 (the "License"); you may not use this file
 * except in compliance with the License. You may obtain a copy of
 * the License at http://www.mozilla.org/NPL/
 * 
 * Software distributed under the License is distributed on an "AS
 * IS" basis, WITHOUT WARRANTY OF ANY KIND, either express or
 * implied. See the License for the specific language governing
 * rights and limitations under the License.
 * 
 * The Original Code is Mozilla Communicator client code, released
 * March 31, 1998.
 * 
 * The Initial Developer of the Original Code is Netscape
 * Communications Corporation. Portions created by Netscape are
 * Copyright (C) 1998-1999 Netscape Communications Corporation. All
 * Rights Reserved.
 *
 * Contributors:
 *  Chip Clark <chipc@netscape.com>
 *  Seth Spitzer <sspitzer@netscape.com>
 *  Neil Rashbrook <neil@parkwaycc.co.uk>
 */

const nsIPrefLocalizedString = Components.interfaces.nsIPrefLocalizedString;
const nsISupportsString = Components.interfaces.nsISupportsString;
const nsIPromptService = Components.interfaces.nsIPromptService;
const nsIPrefService = Components.interfaces.nsIPrefService;
const nsIPrefBranch = Components.interfaces.nsIPrefBranch;
const nsIClipboardHelper = Components.interfaces.nsIClipboardHelper;
const nsIAtomService = Components.interfaces.nsIAtomService;

const nsSupportsString_CONTRACTID = "@mozilla.org/supports-string;1";
const nsPrompt_CONTRACTID = "@mozilla.org/embedcomp/prompt-service;1";
const nsPrefService_CONTRACTID = "@mozilla.org/preferences-service;1";
const nsClipboardHelper_CONTRACTID = "@mozilla.org/widget/clipboardhelper;1";
const nsAtomService_CONTRACTID = "@mozilla.org/atom-service;1";

const gPromptService = Components.classes[nsPrompt_CONTRACTID].getService(nsIPromptService);
const gPrefService = Components.classes[nsPrefService_CONTRACTID].getService(nsIPrefService);
const gPrefBranch = gPrefService.getBranch(null).QueryInterface(Components.interfaces.nsIPrefBranchInternal);
const gClipboardHelper = Components.classes[nsClipboardHelper_CONTRACTID].getService(nsIClipboardHelper);
const gAtomService = Components.classes[nsAtomService_CONTRACTID].getService(nsIAtomService);

var gLockAtoms = [gAtomService.getAtom("default"), gAtomService.getAtom("user"), gAtomService.getAtom("locked")];
// we get these from a string bundle
var gLockStrs = [];
var gTypeStrs = [];

const PREF_IS_DEFAULT_VALUE = 0;
const PREF_IS_USER_SET = 1;
const PREF_IS_LOCKED = 2;

var gPrefHash = {};
var gPrefArray = [];
var gPrefView = gPrefArray; // share the JS array
var gFastIndex = 0;
var gSortedColumn = "prefCol";
var gSortFunction = null;
var gSortDirection = 1; // 1 is ascending; -1 is descending
var gConfigBundle = null;

var view = {
  get rowCount() { return gPrefView.length; },
  getCellText : function(index, col) {
    if (!(index in gPrefView))
      return "";
    
    var value = gPrefView[index][col];

    switch (col) {
      case "lockCol":           
        return gLockStrs[value];
      case "typeCol":
        return gTypeStrs[value];
      default:
        return value;
    }
  },
  getRowProperties : function(index, prop) {},
  getCellProperties : function(index, col, prop) {
    if (index in gPrefView)
      prop.AppendElement(gLockAtoms[gPrefView[index].lockCol]);
  },
  getColumnProperties : function(col, elt, prop) {},
  treebox : null,
  selection : null,
  isContainer : function(index) { return false; },
  isContainerOpen : function(index) { return false; },
  isContainerEmpty : function(index) { return false; },
  isSorted : function() { return true; },
  canDropOn : function(index) { return false; },
  canDropBeforeAfter : function(index, before) { return false; },
  drop : function(row,orientation) {},
  setTree : function(out) { this.treebox = out; },
  getParentIndex: function(rowIndex) { return -1; },
  hasNextSibling: function(rowIndex, afterIndex) { return false; },
  getLevel: function(index) { return 1; },
  getImageSrc: function(row, colID) { return ""; },
  toggleOpenState : function(index) {},
  cycleHeader: function(colID, elt) {
    var index = this.selection.currentIndex;
    if (colID == gSortedColumn)
      gSortDirection = -gSortDirection;
    if (colID == gSortedColumn && gFastIndex == gPrefArray.length) {
      gPrefArray.reverse();
      if (gPrefView != gPrefArray)
        gPrefView.reverse();
      if (index >= 0)
        index = gPrefView.length - index - 1;
    }
    else {
      var pref = null;
      if (index >= 0) {
        if (gPrefArray != gPrefView)
          index = gPrefView.length - index - 1;
        else
          pref = gPrefArray[index];
      }
      var old = document.getElementById(gSortedColumn);
      old.setAttribute("sortDirection", "");
      gPrefArray.sort(gSortFunction = gSortFunctions[colID]);
      if (gPrefView != gPrefArray) {
        if (colID == gSortedColumn)
          gPrefView.reverse();
        else
          gPrefView.sort(gSortFunction);
      }
      gSortedColumn = colID;
      if (pref)
        index = getIndexOfPref(pref);
    }
    elt.setAttribute("sortDirection", gSortDirection > 0 ? "ascending" : "descending");
    this.treebox.invalidate();
    if (index >= 0) {
      this.selection.select(index);
      this.treebox.ensureRowIsVisible(index);
    }
    gFastIndex = gPrefArray.length;
  },
  selectionChanged : function() {},
  cycleCell: function(row, colID) {},
  isEditable: function(row, colID) {return false; },
  setCellText: function(row, colID, value) {},
  performAction: function(action) {},
  performActionOnRow: function(action, row) {},
  performActionOnCell: function(action, row, colID) {},
  isSeparator: function(index) {return false; }
};

// find the index in gPrefView of a pref object
// or -1 if it does not exist in the filtered view
function getViewIndexOfPref(pref)
{
  var low = -1, high = gPrefView.length;
  var index = (low + high) >> 1;
  while (index > low) {
    var mid = gPrefView[index];
    if (mid == pref)
      return index;
    if (gSortFunction(mid, pref) < 0)
      low = index;
    else
      high = index;
    index = (low + high) >> 1;
  }
  return -1;
}

// find the index in gPrefArray of a pref object
// either one that was looked up in gPrefHash
// or in case it was moved after sorting
function getIndexOfPref(pref)
{
  var low = -1, high = gFastIndex;
  var index = (low + high) >> 1;
  while (index > low) {
    var mid = gPrefArray[index];
    if (mid == pref)
      return index;
    if (gSortFunction(mid, pref) < 0)
      low = index;
    else
      high = index;
    index = (low + high) >> 1;
  }

  for (index = gFastIndex; index < gPrefArray.length; ++index)
    if (gPrefArray[index] == pref)
      break;
  return index;
}

function getNearestIndexOfPref(pref)
{
  var low = -1, high = gFastIndex;
  var index = (low + high) >> 1;
  while (index > low) {
    if (gSortFunction(gPrefArray[index], pref) < 0)
      low = index;
    else
      high = index;
    index = (low + high) >> 1;
  }
  return high;
}

var gPrefListener =
{
  observe: function(subject, topic, prefName)
  {
    if (topic != "nsPref:changed")
      return;

    if (/^capability\./.test(prefName)) // avoid displaying "private" preferences
      return;

    var index = gPrefArray.length;
    if (prefName in gPrefHash) {
      index = getViewIndexOfPref(gPrefHash[prefName]);
      fetchPref(prefName, getIndexOfPref(gPrefHash[prefName]));
      if (index >= 0) {
        // Might need to update the filtered view
        gPrefView[index] = gPrefHash[prefName];
        view.treebox.invalidateRow(index);
      }
      if (gSortedColumn == "lockCol" || gSortedColumn == "valueCol")
        gFastIndex = 1; // TODO: reinsert and invalidate range
    } else {
      fetchPref(prefName, index);
      if (index == gFastIndex) {
        // Keep the array sorted by reinserting the pref object
        var pref = gPrefArray.pop();
        index = getNearestIndexOfPref(pref);
        gPrefArray.splice(index, 0, pref);
        gFastIndex = gPrefArray.length;
      }
      if (gPrefView == gPrefArray)
        view.treebox.rowCountChanged(index, 1);
    }
  }
};

function prefObject(prefName, prefIndex)
{
  this.prefCol = prefName;
}

prefObject.prototype =
{
  lockCol: PREF_IS_DEFAULT_VALUE,
  typeCol: nsIPrefBranch.PREF_STRING,
  valueCol: ""
};

function fetchPref(prefName, prefIndex)
{
  var pref = new prefObject(prefName);

  gPrefHash[prefName] = pref;
  gPrefArray[prefIndex] = pref;

  if (gPrefBranch.prefIsLocked(prefName))
    pref.lockCol = PREF_IS_LOCKED;
  else if (gPrefBranch.prefHasUserValue(prefName))
    pref.lockCol = PREF_IS_USER_SET;

  try {
    switch (gPrefBranch.getPrefType(prefName)) {
      case gPrefBranch.PREF_BOOL:
        pref.typeCol = gPrefBranch.PREF_BOOL;
        // convert to a string
        pref.valueCol = gPrefBranch.getBoolPref(prefName).toString();
        break;
      case gPrefBranch.PREF_INT:
        pref.typeCol = gPrefBranch.PREF_INT;
        // convert to a string
        pref.valueCol = gPrefBranch.getIntPref(prefName).toString();
        break;
      default:
      case gPrefBranch.PREF_STRING:
        pref.valueCol = gPrefBranch.getComplexValue(prefName, nsISupportsString).data;
        // Try in case it's a localized string (will throw an exception if not)
        if (pref.lockCol == PREF_IS_DEFAULT_VALUE &&
            /^chrome:\/\/.+\/locale\/.+\.properties/.test(pref.valueCol))
          pref.valueCol = gPrefBranch.getComplexValue(prefName, nsIPrefLocalizedString).data;
        break;
    }
  } catch (e) {
    // Also catch obscure cases in which you can't tell in advance
    // that the pref exists but has no user or default value...
  }
}

function onConfigLoad()
{
  // Load strings
  gConfigBundle = document.getElementById("configBundle");
  document.title = gConfigBundle.getString("title");

  gLockStrs[PREF_IS_DEFAULT_VALUE] = gConfigBundle.getString("default");
  gLockStrs[PREF_IS_USER_SET] = gConfigBundle.getString("user");
  gLockStrs[PREF_IS_LOCKED] = gConfigBundle.getString("locked");

  gTypeStrs[nsIPrefBranch.PREF_STRING] = gConfigBundle.getString("string");
  gTypeStrs[nsIPrefBranch.PREF_INT] = gConfigBundle.getString("int");
  gTypeStrs[nsIPrefBranch.PREF_BOOL] = gConfigBundle.getString("bool");

  var prefCount = { value: 0 };
  var prefArray = gPrefBranch.getChildList("", prefCount);

  for (var i = 0; i < prefCount.value; ++i) 
  {
    var prefName = prefArray[i];
    if (/^capability\./.test(prefName)) // avoid displaying "private" preferences
      continue;

    fetchPref(prefName, gPrefArray.length);
  }

  var descending = document.getElementsByAttribute("sortDirection", "descending");
  if (descending.length) {
    gSortedColumn = descending[0].id;
    gSortDirection = -1;
  }
  else {
    var ascending = document.getElementsByAttribute("sortDirection", "ascending");
    if (ascending.length)
      gSortedColumn = ascending[0].id;
    else
      document.getElementById(gSortedColumn).setAttribute("sortDirection", "ascending");
  }
  gSortFunction = gSortFunctions[gSortedColumn];
  gPrefArray.sort(gSortFunction);
  gFastIndex = gPrefArray.length;
  
  gPrefBranch.addObserver("", gPrefListener, false);

  document.getElementById("configTree").view = view;
  
  document.getElementById("textbox").focus();
}

function onConfigUnload()
{
  gPrefBranch.removeObserver("", gPrefListener);
  document.getElementById("configTree").view = null;
}

function FilterPrefs()
{
  var substring = document.getElementById("textbox").value.toLowerCase();
  var prefCol = view.selection.currentIndex < 0 ? null : gPrefView[view.selection.currentIndex].prefCol;
  var array = gPrefView;
  gPrefView = gPrefArray;
  if (substring) {
    gPrefView = [];
    for (var i = 0; i < gPrefArray.length; ++i)
      if (gPrefArray[i].prefCol.toLowerCase().indexOf(substring) >= 0)
        gPrefView.push(gPrefArray[i]);
    if (gFastIndex < gPrefArray.length)
      gPrefView.sort(gSortFunction);
  }
  view.treebox.invalidate();
  view.treebox.rowCountChanged(array.length, gPrefView.length - array.length);
  gotoPref(prefCol);
  document.getElementById("button").disabled = !substring;
}

function ClearFilter(button)
{
  var textbox = document.getElementById("textbox");
  textbox.value = "";
  textbox.focus();
  FilterPrefs();
}

function prefColSortFunction(x, y)
{
  if (x.prefCol > y.prefCol)
    return gSortDirection;
  if (x.prefCol < y.prefCol) 
    return -gSortDirection;
  return 0;
}

function lockColSortFunction(x, y)
{
  if (x.lockCol != y.lockCol)
    return gSortDirection * (y.lockCol - x.lockCol);
  return prefColSortFunction(x, y);
}

function typeColSortFunction(x, y)
{
  if (x.typeCol != y.typeCol) 
    return gSortDirection * (y.typeCol - x.typeCol);
  return prefColSortFunction(x, y);
}

function valueColSortFunction(x, y)
{
  if (x.valueCol > y.valueCol)
    return gSortDirection;
  if (x.valueCol < y.valueCol) 
    return -gSortDirection;
  return prefColSortFunction(x, y);
}

const gSortFunctions =
{
  prefCol: prefColSortFunction, 
  lockCol: lockColSortFunction, 
  typeCol: typeColSortFunction, 
  valueCol: valueColSortFunction
};

function updateContextMenu(popup) {
  if (view.selection.currentIndex < 0)
    return false;
  var pref = gPrefView[view.selection.currentIndex];
  var reset = popup.lastChild;
  reset.setAttribute("disabled", pref.lockCol != PREF_IS_USER_SET);
  var modify = reset.previousSibling;
  modify.setAttribute("disabled", pref.lockCol == PREF_IS_LOCKED);
  return true;
}

function copyName()
{
  gClipboardHelper.copyString(gPrefView[view.selection.currentIndex].prefCol);
}

function copyValue()
{
  gClipboardHelper.copyString(gPrefView[view.selection.currentIndex].valueCol);
}

function ModifySelected()
{
  ModifyPref(gPrefView[view.selection.currentIndex]);
}

function ResetSelected()
{
  var entry = gPrefView[view.selection.currentIndex];
  gPrefBranch.clearUserPref(entry.prefCol);
}

function NewPref(type)
{
  var result = { value: "" };
  var dummy = { value: 0 };
  // XXX get these from a string bundle
  if (gPromptService.prompt(window,
                            gConfigBundle.getFormattedString("new_title", [gTypeStrs[type]]),
                            gConfigBundle.getString("new_prompt"),
                            result,
                            null,
                            dummy)) {
    var pref;
    if (result.value in gPrefHash)
      pref = gPrefHash[result.value];
    else
      pref = { prefCol: result.value, lockCol: PREF_IS_DEFAULT_VALUE, typeCol: type, valueCol: "" };
    if (ModifyPref(pref))
      setTimeout(gotoPref, 0, result.value);
  }
}

function gotoPref(pref) {
  // make sure the pref exists and is displayed in the current view
  var index = pref in gPrefHash ? getViewIndexOfPref(gPrefHash[pref]) : -1;
  if (index >= 0) {
    view.selection.select(index);
    view.treebox.ensureRowIsVisible(index);
  } else {
    view.selection.clearSelection();
    view.selection.currentIndex = -1;
  }
}

function ModifyPref(entry)
{
  if (entry.lockCol == PREF_IS_LOCKED)
    return false;
  var result = { value: entry.valueCol };
  var dummy = { value: 0 };
  // XXX get this from a string bundle
  if (!gPromptService.prompt(window,
                             gConfigBundle.getFormattedString("modify_title", [gTypeStrs[entry.typeCol]]),
                             entry.prefCol,
                             result,
                             null,
                             dummy))
    return false;
  switch (entry.typeCol) {
    case nsIPrefBranch.PREF_BOOL:
      gPrefBranch.setBoolPref(entry.prefCol, eval(result.value));
      break;
    case nsIPrefBranch.PREF_INT:
      gPrefBranch.setIntPref(entry.prefCol, eval(result.value));
      break;
    default:
    case nsIPrefBranch.PREF_STRING:
      var supportsString = Components.classes[nsSupportsString_CONTRACTID].createInstance(nsISupportsString);
      supportsString.data = result.value;
      gPrefBranch.setComplexValue(entry.prefCol, nsISupportsString, supportsString);
      break;
  }
  return true;
}
