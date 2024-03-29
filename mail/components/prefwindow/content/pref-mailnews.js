function Startup()
{
  var startupFunc;
  try {
    startupFunc = document.getElementById("mailnewsEnableMapi").getAttribute('startupFunc');
  }
  catch (ex) {
    startupFunc = null;
  }
  if (startupFunc)
    eval(startupFunc);

  StartPageCheck();

  // now do some Notification panel startup work: 

  PlaySoundCheck();

  // if we don't have the alert service, hide the pref UI for using alerts to notify on new mail
  // see bug #158711
  var newMailNotificationAlertUI = document.getElementById("newMailNotificationAlert");
  newMailNotificationAlertUI.hidden = !("@mozilla.org/alerts-service;1" in Components.classes);
}

function setColorWell(menu) 
{
  // Find the colorWell and colorPicker in the hierarchy.
  var colorWell = menu.firstChild.nextSibling;
  var colorPicker = menu.firstChild.nextSibling.nextSibling.firstChild;

  // Extract color from colorPicker and assign to colorWell.
  var color = colorPicker.getAttribute('color');
  colorWell.style.backgroundColor = color;
}

function StartPageCheck()
{
  var checked = document.getElementById("mailnewsStartPageEnabled").checked;
  document.getElementById("mailnewsStartPageUrl").disabled = !checked;
}

function setHomePageToDefaultPage(folderFieldId)
{
  var homePageField = document.getElementById(folderFieldId);
  var prefService = Components.classes["@mozilla.org/preferences-service;1"]
                              .getService(Components.interfaces.nsIPrefService);
  var prefs = prefService.getDefaultBranch(null);
  var url = prefs.getComplexValue("mailnews.start_page.url",
                                  Components.interfaces.nsIPrefLocalizedString).data;
  homePageField.value = url;
}

function PlaySoundCheck()
{
  var playSound = document.getElementById("newMailNotification").checked;
  var playSoundType = document.getElementById("newMailNotificationType");
  playSoundType.disabled = !playSound;

  var disableCustomUI = !(playSound && playSoundType.value == 1);
  var mailnewsSoundFileUrl = document.getElementById("mailnewsSoundFileUrl");

  mailnewsSoundFileUrl.disabled = disableCustomUI
  document.getElementById("preview").disabled = disableCustomUI || (mailnewsSoundFileUrl.value == "");
  document.getElementById("browse").disabled = disableCustomUI;
}

function onCustomWavInput()
{
  document.getElementById("preview").disabled = (document.getElementById("mailnewsSoundFileUrl").value == "");
}

const nsIFilePicker = Components.interfaces.nsIFilePicker;

function Browse()
{
  var fp = Components.classes["@mozilla.org/filepicker;1"]
                       .createInstance(nsIFilePicker);

  // XXX todo, persist the last sound directory and pass it in
  // XXX todo filter by .wav
  fp.init(window, document.getElementById("browse").getAttribute("filepickertitle"), nsIFilePicker.modeOpen);
  fp.appendFilters(nsIFilePicker.filterAll);

  var ret = fp.show();
  if (ret == nsIFilePicker.returnOK) {
    var mailnewsSoundFileUrl = document.getElementById("mailnewsSoundFileUrl");

    // convert the nsILocalFile into a nsIFile url 
    mailnewsSoundFileUrl.value = fp.fileURL.spec;
  }

  onCustomWavInput();
}

var gSound = null;

function PreviewSound()
{
  var soundURL = document.getElementById("mailnewsSoundFileUrl").value;

  if (!gSound)
    gSound = Components.classes["@mozilla.org/sound;1"].createInstance(Components.interfaces.nsISound);

  if (soundURL.indexOf("file://") == -1) {
    // XXX todo see if we can create a nsIURL from the native file path
    // otherwise, play a system sound
    gSound.playSystemSound(soundURL);
  }
  else {
    var ioService = Components.classes["@mozilla.org/network/io-service;1"].getService(Components.interfaces.nsIIOService);
    var url = ioService.newURI(soundURL, null, null);
    gSound.play(url)
  }
}
