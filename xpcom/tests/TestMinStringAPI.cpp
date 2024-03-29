/* vim:set ts=2 sw=2 et cindent: */
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
 * The Original Code is Mozilla.
 *
 * The Initial Developer of the Original Code is IBM Corporation.
 * Portions created by IBM Corporation are Copyright (C) 2003
 * IBM Corporation.  All Rights Reserved.
 *
 * Contributor(s):
 *   Darin Fisher <darin@meer.net>
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

#include <stdio.h>
#include "nsStringAPI.h"
#include "nsCRT.h"

static const char kAsciiData[] = "hello world";

static const PRUnichar kUnicodeData[] =
  {'h','e','l','l','o',' ','w','o','r','l','d','\0'};

static PRBool test_basic_1()
  {
    nsCStringContainer s;
    NS_CStringContainerInit(s);

    const char *ptr;
    PRUint32 len;
    char *clone;

    NS_CStringGetData(s, &ptr);
    if (ptr == nsnull || *ptr != '\0')
      {
        NS_ERROR("unexpected result");
        return PR_FALSE;
      }

    NS_CStringSetData(s, kAsciiData, PR_UINT32_MAX);
    len = NS_CStringGetData(s, &ptr);
    if (ptr == nsnull || strcmp(ptr, kAsciiData) != 0)
      {
        NS_ERROR("unexpected result");
        return PR_FALSE;
      }
    if (len != sizeof(kAsciiData)-1)
      {
        NS_ERROR("unexpected result");
        return PR_FALSE;
      }

    clone = NS_CStringCloneData(s);
    if (ptr == nsnull || strcmp(ptr, kAsciiData) != 0)
      {
        NS_ERROR("unexpected result");
        return PR_FALSE;
      }
    nsMemory::Free(clone);

    nsCStringContainer temp;
    NS_CStringContainerInit(temp);
    NS_CStringCopy(temp, s);

    len = NS_CStringGetData(temp, &ptr);
    if (ptr == nsnull || strcmp(ptr, kAsciiData) != 0)
      {
        NS_ERROR("unexpected result");
        return PR_FALSE;
      }
    if (len != sizeof(kAsciiData)-1)
      {
        NS_ERROR("unexpected result");
        return PR_FALSE;
      }

    NS_CStringContainerFinish(temp);

    NS_CStringContainerFinish(s);
    return PR_TRUE;
  }

static PRBool test_basic_2()
  {
    nsStringContainer s;
    NS_StringContainerInit(s);

    const PRUnichar *ptr;
    PRUint32 len;
    PRUnichar *clone;

    NS_StringGetData(s, &ptr);
    if (ptr == nsnull || *ptr != '\0')
      {
        NS_ERROR("unexpected result");
        return PR_FALSE;
      }

    NS_StringSetData(s, kUnicodeData, PR_UINT32_MAX);
    len = NS_StringGetData(s, &ptr);
    if (ptr == nsnull || nsCRT::strcmp(ptr, kUnicodeData) != 0)
      {
        NS_ERROR("unexpected result");
        return PR_FALSE;
      }
    if (len != sizeof(kUnicodeData)/2 - 1)
      {
        NS_ERROR("unexpected result");
        return PR_FALSE;
      }

    clone = NS_StringCloneData(s);
    if (ptr == nsnull || nsCRT::strcmp(ptr, kUnicodeData) != 0)
      {
        NS_ERROR("unexpected result");
        return PR_FALSE;
      }
    nsMemory::Free(clone);

    nsStringContainer temp;
    NS_StringContainerInit(temp);
    NS_StringCopy(temp, s);

    len = NS_StringGetData(temp, &ptr);
    if (ptr == nsnull || nsCRT::strcmp(ptr, kUnicodeData) != 0)
      {
        NS_ERROR("unexpected result");
        return PR_FALSE;
      }
    if (len != sizeof(kUnicodeData)/2 - 1)
      {
        NS_ERROR("unexpected result");
        return PR_FALSE;
      }

    NS_StringContainerFinish(temp);

    NS_StringContainerFinish(s);

    return PR_TRUE;
  }

static PRBool test_convert()
  {
    nsStringContainer s;
    NS_StringContainerInit(s);
    NS_StringSetData(s, kUnicodeData, sizeof(kUnicodeData)/2 - 1);

    nsCStringContainer temp;
    NS_CStringContainerInit(temp);

    const char *data;

    NS_UTF16ToCString(s, NS_CSTRING_ENCODING_ASCII, temp);
    NS_CStringGetData(temp, &data);
    if (strcmp(data, kAsciiData) != 0)
      return PR_FALSE;

    NS_UTF16ToCString(s, NS_CSTRING_ENCODING_UTF8, temp);
    NS_CStringGetData(temp, &data);
    if (strcmp(data, kAsciiData) != 0)
      return PR_FALSE;

    NS_CStringContainerFinish(temp);

    NS_StringContainerFinish(s);
    return PR_TRUE;
  }

static PRBool test_append()
  {
    nsCStringContainer s;
    NS_CStringContainerInit(s);

    NS_CStringSetData(s, "foo");
    NS_CStringAppendData(s, "bar");

    NS_CStringContainerFinish(s);
    return PR_TRUE;
  }

//----

typedef PRBool (*TestFunc)();

static const struct Test
  {
    const char* name;
    TestFunc    func;
  }
tests[] =
  {
    { "test_basic_1", test_basic_1 },
    { "test_basic_2", test_basic_2 },
    { "test_convert", test_convert },
    { "test_append", test_append },
    { nsnull, nsnull }
  };

//----

int main(int argc, char **argv)
  {
    int count = 1;
    if (argc > 1)
      count = atoi(argv[1]);

    while (count--)
      {
        for (const Test* t = tests; t->name != nsnull; ++t)
          {
            printf("%25s : %s\n", t->name, t->func() ? "SUCCESS" : "FAILURE");
          }
      }
    
    return 0;
  }
