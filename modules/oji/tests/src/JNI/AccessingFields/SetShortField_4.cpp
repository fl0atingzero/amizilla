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
#include "AccessingFields.h"

JNI_OJIAPITest(JNIEnv_SetShortField_4)
{
  GET_JNI_FOR_TEST

  IMPLEMENT_GetFieldID_METHOD("Test1","name_short", "S");

  env->SetShortField(obj, NULL, 1);
  printf("value = %d\n", env->GetShortField(obj, fieldID));
  if(env->GetShortField(obj, fieldID) == 0){
    return TestResult::PASS("SetShortField(fieldID == NULL) do not set field - correct");
  }else{
    return TestResult::FAIL("SetShortField(fieldID == NULL) set field - incorrect");
  }

}
