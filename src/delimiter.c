#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "msplit.h"

char *
delimiter_string(const char *input) {
    char *result = NULL;
    char *s, *t1, *t2;

    if (input) {
        result = strndup(input, BUFSIZE);

        if (result == NULL) {
            return NULL;
        }

        /* replace \n etc. */
        for (s = result; *s != '\0'; s++) {
            if (*s == '\\') {
                switch (*(s + 1)) {
                    case 'n':
                        *s = '\n';
                        t1 = s + 2;
                        break;
                    case 'r':
                        *s = '\r';
                        t1 = s + 2;
                        break;
                    case 't':
                        *s = '\t';
                        t1 = s + 2;
                        break;
                    case '\\':
                        *s = '\\';
                        t1 = s + 2;
                        break;
                }

                /* hella inefficient because we move the entire
                   string each time a replacement has happened. */
                if (t1 > s) {
                    for (t2 = s + 1; *t1 != '\0'; t1++, t2++) {
                        *t2 = *t1;
                    }
                    *t2 = '\0';
                    t1 = s;
                }
            }
        }
    }

    return result;
}
