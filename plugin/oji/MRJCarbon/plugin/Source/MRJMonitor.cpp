/* ----- BEGIN LICENSE BLOCK -----
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
 * The Original Code is the MRJ Carbon OJI Plugin.
 *
 * The Initial Developer of the Original Code is
 * Netscape Communications Corp.
 * Portions created by the Initial Developer are Copyright (C) 2001
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):  Patrick C. Beard <beard@netscape.com>
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
 * ----- END LICENSE BLOCK ----- */

/*
	MRJMonitor.cpp
	
	Provides a C++ interface to Java monitors.
	
	by Patrick C. Beard.
 */

#include "MRJMonitor.h"
#include "MRJSession.h"

MRJMonitor::MRJMonitor(MRJSession* session, jobject monitor)
	:	mSession(session), mMonitor(NULL), mWaitMethod(NULL), mNotifyMethod(NULL), mNotifyAllMethod(NULL)
{
	JNIEnv* env = mSession->getCurrentEnv();
	jclass javaLangObject = env->FindClass("java/lang/Object");
	if (javaLangObject != NULL) {
		// look up method IDs.
		mWaitMethod = env->GetMethodID(javaLangObject, "wait", "()V");
		mTimedWaitMethod = env->GetMethodID(javaLangObject, "wait", "(J)V");
		mNotifyMethod = env->GetMethodID(javaLangObject, "notify", "()V");
		mNotifyAllMethod = env->GetMethodID(javaLangObject, "notifyAll", "()V");
		
		Boolean allocateMonitor = (monitor == NULL);
		if (allocateMonitor)
			monitor = env->AllocObject(javaLangObject);
		
		if (monitor != NULL)
			mMonitor = env->NewGlobalRef(monitor);

		if (allocateMonitor)
			env->DeleteLocalRef(monitor);

		env->DeleteLocalRef(javaLangObject);
	}
}

MRJMonitor::~MRJMonitor()
{
	if (mMonitor != NULL) {
		JNIEnv* env = mSession->getCurrentEnv();
		env->DeleteGlobalRef(mMonitor);
		mMonitor = NULL;
	}
}

void MRJMonitor::enter()
{
	JNIEnv* env = mSession->getCurrentEnv();
	env->MonitorEnter(mMonitor);
}

void MRJMonitor::exit()
{
	JNIEnv* env = mSession->getCurrentEnv();
	env->MonitorExit(mMonitor);
}

void MRJMonitor::wait()
{
	if (mMonitor != NULL && mWaitMethod != NULL) {
		JNIEnv* env = mSession->getCurrentEnv();
		env->MonitorEnter(mMonitor);
		env->CallVoidMethod(mMonitor, mWaitMethod);
		env->MonitorExit(mMonitor);
	}
}

void MRJMonitor::wait(long long millis)
{
	if (mMonitor != NULL && mWaitMethod != NULL) {
		JNIEnv* env = mSession->getCurrentEnv();
		env->MonitorEnter(mMonitor);
		env->CallVoidMethod(mMonitor, mTimedWaitMethod, jlong(millis));
		env->MonitorExit(mMonitor);
	}
}

void MRJMonitor::notify()
{
	if (mMonitor != NULL && mNotifyMethod != NULL) {
		JNIEnv* env = mSession->getCurrentEnv();
		env->MonitorEnter(mMonitor);
		env->CallVoidMethod(mMonitor, mNotifyMethod);
		env->MonitorExit(mMonitor);
	}
}

void MRJMonitor::notifyAll()
{
	if (mMonitor != NULL && mNotifyAllMethod != NULL) {
		JNIEnv* env = mSession->getCurrentEnv();
		env->MonitorEnter(mMonitor);
		env->CallVoidMethod(mMonitor, mNotifyAllMethod);
		env->MonitorExit(mMonitor);
	}
}

jobject MRJMonitor::getObject()
{
	return mMonitor;
}
