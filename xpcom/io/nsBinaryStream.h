/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
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
 * Copyright (C) 1998-2001 Netscape Communications Corporation. All
 * Rights Reserved.
 *
 */

#ifndef nsBinaryStream_h___
#define nsBinaryStream_h___

#include "nsCOMPtr.h"
#include "nsAString.h"
#include "nsIObjectInputStream.h"
#include "nsIObjectOutputStream.h"
#include "nsIStreamBufferAccess.h"

#define NS_BINARYOUTPUTSTREAM_CID        \
{ /* 86c37b9a-74e7-4672-844e-6e7dd83ba484 */         \
     0x86c37b9a,                                     \
     0x74e7,                                         \
     0x4672,                                         \
    {0x84, 0x4e, 0x6e, 0x7d, 0xd8, 0x3b, 0xa4, 0x84} \
}

#define NS_BINARYOUTPUTSTREAM_CONTRACTID "@mozilla.org/binaryoutputstream;1"
#define NS_BINARYOUTPUTSTREAM_CLASSNAME "Binary Output Stream"

// Derive from nsIObjectOutputStream so this class can be used as a superclass
// by nsObjectOutputStream.
class nsBinaryOutputStream : public nsIObjectOutputStream
{
public:
    nsBinaryOutputStream() {};
    // virtual dtor since subclasses call our Release()
    virtual ~nsBinaryOutputStream() {};

protected:
    // nsISupports methods
    NS_DECL_ISUPPORTS

    // nsIOutputStream methods
    NS_DECL_NSIOUTPUTSTREAM

    // nsIBinaryOutputStream methods
    NS_DECL_NSIBINARYOUTPUTSTREAM

    // nsIObjectOutputStream methods
    NS_DECL_NSIOBJECTOUTPUTSTREAM

    // Call Write(), ensuring that all proffered data is written
    nsresult WriteFully(const char *aBuf, PRUint32 aCount);

    nsCOMPtr<nsIOutputStream>       mOutputStream;
    nsCOMPtr<nsIStreamBufferAccess> mBufferAccess;
};

#define NS_BINARYINPUTSTREAM_CID        \
{ /* c521a612-2aad-46db-b6ab-3b821fb150b1 */         \
     0xc521a612,                                     \
     0x2aad,                                         \
     0x46db,                                         \
    {0xb6, 0xab, 0x3b, 0x82, 0x1f, 0xb1, 0x50, 0xb1} \
}

#define NS_BINARYINPUTSTREAM_CONTRACTID "@mozilla.org/binaryinputstream;1"
#define NS_BINARYINPUTSTREAM_CLASSNAME "Binary Input Stream"

// Derive from nsIObjectInputStream so this class can be used as a superclass
// by nsObjectInputStream.
class nsBinaryInputStream : public nsIObjectInputStream
{
public:
    nsBinaryInputStream() {};
    // virtual dtor since subclasses call our Release()
    virtual ~nsBinaryInputStream() {};

protected:
    // nsISupports methods
    NS_DECL_ISUPPORTS

    // nsIInputStream methods
    NS_DECL_NSIINPUTSTREAM

    // nsIBinaryInputStream methods
    NS_DECL_NSIBINARYINPUTSTREAM

    // nsIObjectInputStream methods
    NS_DECL_NSIOBJECTINPUTSTREAM

    nsCOMPtr<nsIInputStream>        mInputStream;
    nsCOMPtr<nsIStreamBufferAccess> mBufferAccess;
};

#endif // nsBinaryStream_h___
