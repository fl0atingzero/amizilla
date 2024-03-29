/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 * The contents of this file are subject to the Mozilla Public
 * License Version 1.1 (the "License"); you may not use this file
 * except in compliance with the License. You may obtain a copy of
 * the License at http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS
 * IS" basis, WITHOUT WARRANTY OF ANY KIND, either express or
 * implied. See the License for the specific language governing
 * rights and limitations under the License.
 *
 * The Original Code is mozilla.org code.
 *
 * The Initial Developer of the Original Code is Sun Microsystems,
 * Inc. Portions created by Sun are
 * Copyright (C) 1999 Sun Microsystems, Inc. All
 * Rights Reserved.
 *
 * Contributor(s): 
 */
#include "JNIEnvTests.h"
#include "CallingStaticMethods.h"

JNI_OJIAPITest(JNIEnv_GetStaticMethodID_22)
{
  GET_JNI_FOR_TEST
  jclass clazz_exp = env->FindClass("Ljava/security/PrivilegedActionException;");
  IMPLEMENT_GetStaticMethodID_METHOD("Test1", "Get_int_field_super_private_static", "()I");
  if(clazz == NULL){
      printf("Class is NULL!!!");
  }
  jint value = env->CallStaticIntMethod(clazz, MethodID, NULL);

  jthrowable excep  = env->ExceptionOccurred();
  if(MethodID!=NULL){
     if((excep != NULL) && (env->IsInstanceOf(excep, clazz_exp))){
       return TestResult::PASS("GetStaticMethodID for private method from non-abstract class, inherited from superclass return correct value");
     }else{
       if(SecENV){
         return TestResult::FAIL("GetStaticMethodID for private method from non-abstract class, inherited from superclass return incorrect value");
       }else{
         return TestResult::PASS("GetStaticMethodID for private method from non-abstract class, inherited from superclass return correct value");
       }
     }
  }else{
    return TestResult::FAIL("GetStaticMethodID for private method from non-abstract class, inherited from superclass return incorrect value");
  }
}
