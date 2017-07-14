#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <errno.h>

#include "delimiter.h"
#include "matchsplit.h"

#ifndef VERSION
#  define VERSION 0
#endif

#define BUFSIZE (32 * 1024)

void
show_help(const char *exc)
{
    printf( "Usage: %s [-d DELIMITER] [-l LINEDELIMITER] [-f FILE]\n"
            "\n"
            "Usage:\n"
            "   -h, --help              Show this help output.\n"
            "   -f, --file FILE         Read lines from FILE ('-' for stdin).\n"
            "   -d, --delimiter D       Use D as the delimiter (default: \").\n" 
            "   -l, --line-delimiter L  Use L as the line delimiter (default: newline).\n"
            "\n"
            "msplit version %d - Cris van Pelt <cris.vanpelt@gmail.com>\n", exc, VERSION);
}

FILE *
open_file(const char *fname) {
    FILE *f = NULL;
    size_t len;

    if (fname) {
        len = strlen(fname);
        if (strncmp("-", fname, len) == 0) {
            f =  stdin;
        } else {
            f = fopen(fname, "r");
        }
    }

    return f;
}

int
main(int argc, char **argv)
{
    FILE *input = stdin;

    char line[BUFSIZE];
    char *splitsies[BUFSIZE];
    char *delimiter = "\"";
    char *line_delimiter = "\n";

    int option_index = 0;
    int i, c;

    static struct option long_options[] = {
        { "file", required_argument, 0, 'f' },
        { "delimiter", required_argument, 0, 'd' },
        { "line-delimiter", required_argument, 0, 'l' },
        { "help", no_argument, 0, 'h' },
        { 0, 0, 0, 0 }
    };

    while (1) {
        c = getopt_long(argc, argv, "hl:d:f:", long_options, &option_index);
        if (c == -1) {
            break;
        }

        switch (c) {
            case 'f':
                input = open_file(optarg);
                if (input == NULL) {
                    fprintf(stderr, "%s: %s: %s\n", argv[0], optarg,
                        strerror(errno));
                    exit(errno);
                }
                break;
            case 'd':
                delimiter = delimiter_string(optarg);
                if (!delimiter) {
                    fprintf(stderr, "%s: %s\n", argv[0], strerror(errno));
                    exit(errno);
                }
                break;
            case 'l':
                line_delimiter = delimiter_string(optarg);
                if (!line_delimiter) {
                    fprintf(stderr, "%s: %s\n", argv[0], strerror(errno));
                    exit(errno);
                }
                break;

            case 'h':
                show_help(argv[0]);
                exit(EXIT_SUCCESS);

            case '?':
                show_help(argv[0]);
                exit(EXIT_FAILURE);
                break;
            default:
                printf("fuck\n");
                break;
        }
    }

    while (fgets(line, BUFSIZE, input) != NULL) {
        matchsplit(line, splitsies, BUFSIZE);
        for (i = 0; splitsies[i]; i++) {
            printf("%s%s", splitsies[i], delimiter);
        }
        printf("%s", line_delimiter);
    }

    if (ferror(input)) {
        fprintf(stderr, "%s: error reading input: %s", argv[0], strerror(errno));
        exit(errno);
    }

    return 0;
}
