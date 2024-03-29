#include <stdio.h>
#include "nsIURLParser.h"
#include "nsCOMPtr.h"
#include "nsIServiceManager.h"
#include "nsNetCID.h"

static void
print_field(const char *label, char *str, PRInt32 len)
{
    char c = str[len];
    str[len] = '\0';
    printf("[%s=%s]\n", label, str);
    str[len] = c;
}

#define PRINT_FIELD(x) \
        print_field(# x, x, x ## Len)

#define PRINT_SUBFIELD(base, x) \
    PR_BEGIN_MACRO \
        if (x ## Len != -1) \
            print_field(# x, base + x ## Pos, x ## Len); \
    PR_END_MACRO

static void
parse_authority(nsIURLParser *urlParser, char *auth, PRInt32 authLen)
{
    PRINT_FIELD(auth);

    PRUint32 usernamePos, passwordPos;
    PRInt32 usernameLen, passwordLen;
    PRUint32 hostnamePos;
    PRInt32 hostnameLen, port;

    urlParser->ParseAuthority(auth, authLen,
                              &usernamePos, &usernameLen,
                              &passwordPos, &passwordLen,
                              &hostnamePos, &hostnameLen,
                              &port);

    PRINT_SUBFIELD(auth, username);
    PRINT_SUBFIELD(auth, password);
    PRINT_SUBFIELD(auth, hostname);
    if (port != -1)
        printf("[port=%d]\n", port);
}

static void
parse_file_path(nsIURLParser *urlParser, char *filepath, PRInt32 filepathLen)
{
    PRINT_FIELD(filepath);

    PRUint32 dirPos, basePos, extPos;
    PRInt32 dirLen, baseLen, extLen;

    urlParser->ParseFilePath(filepath, filepathLen,
                             &dirPos, &dirLen,
                             &basePos, &baseLen,
                             &extPos, &extLen);

    PRINT_SUBFIELD(filepath, dir);
    PRINT_SUBFIELD(filepath, base);
    PRINT_SUBFIELD(filepath, ext);
}

static void
parse_path(nsIURLParser *urlParser, char *path, PRInt32 pathLen)
{
    PRINT_FIELD(path);

    PRUint32 filePos, paramPos, queryPos, refPos;
    PRInt32 fileLen, paramLen, queryLen, refLen;

    urlParser->ParsePath(path, pathLen,
                         &filePos, &fileLen,
                         &paramPos, &paramLen,
                         &queryPos, &queryLen,
                         &refPos, &refLen);

    if (fileLen != -1)
        parse_file_path(urlParser, path + filePos, fileLen);
    PRINT_SUBFIELD(path, param);
    PRINT_SUBFIELD(path, query);
    PRINT_SUBFIELD(path, ref);
}

int
main(int argc, char **argv)
{
    if (argc < 2) {
        printf("usage: TestURLParser [-std|-noauth|-auth] <url>\n");
        return -1;
    }
    nsCOMPtr<nsIURLParser> urlParser;
    if (strcmp(argv[1], "-noauth") == 0) {
        urlParser = do_GetService(NS_NOAUTHURLPARSER_CONTRACTID);
        argv[1] = argv[2];
    }
    else if (strcmp(argv[1], "-auth") == 0) {
        urlParser = do_GetService(NS_AUTHURLPARSER_CONTRACTID);
        argv[1] = argv[2];
    }
    else {
        urlParser = do_GetService(NS_STDURLPARSER_CONTRACTID);
        if (strcmp(argv[1], "-std") == 0)
            argv[1] = argv[2];
        else
            printf("assuming -std\n");
    }
    if (urlParser) {
        printf("have urlParser @%p\n", urlParser.get());

        char *spec = argv[1];
        PRUint32 schemePos, authPos, pathPos;
        PRInt32 schemeLen, authLen, pathLen;

        urlParser->ParseURL(spec, -1,
                            &schemePos, &schemeLen,
                            &authPos, &authLen,
                            &pathPos, &pathLen);

        if (schemeLen != -1)
            PRINT_SUBFIELD(spec, scheme);
        if (authLen != -1)
            parse_authority(urlParser, spec + authPos, authLen);
        if (pathLen != -1)
            parse_path(urlParser, spec + pathPos, pathLen);
    }
    else
        printf("no urlParser\n");
    return 0;
}
