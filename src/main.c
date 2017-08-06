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
    printf( "Usage: %s [-d DELIMITER] [-l LINEDELIMITER] [FILE1..FILEn]\n"
            "\n"
            "Usage:\n"
            "   -h, --help              Show this help output.\n"
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
    FILE *input[1024];

    char line[BUFSIZE];
    char *splitsies[BUFSIZE];
    char *delimiter = "\"";
    char *line_delimiter = "\n";

    int option_index = 0;
    int i, j, c;

    static struct option long_options[] = {
        { "delimiter", required_argument, 0, 'd' },
        { "line-delimiter", required_argument, 0, 'l' },
        { "help", no_argument, 0, 'h' },
        { 0, 0, 0, 0 }
    };

    while (1) {
        c = getopt_long(argc, argv, "hl:d:", long_options, &option_index);
        if (c == -1) {
            break;
        }

        switch (c) {
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

            default: /* '?' */
                show_help(argv[0]);
                exit(EXIT_FAILURE);
                break;
        }
    }

    input[0] = stdin;
    input[1] = NULL;

    if (optind <= argc) {
        if (argc > 1023) {
            fprintf(stderr, "%s: too many arguments\n", argv[0]);
            exit(EXIT_FAILURE);
        }
        for (i = optind; i < argc; i++) {
            if (strncmp(argv[i], "-", 1) == 0) {
                input[i] = stdin;
                continue;
            }
            input[i - optind] = open_file(argv[i]);
            if (input[i - optind] == NULL) {
                fprintf(stderr, "%s: Could not open %s: %s\n", argv[0],
                    argv[i], strerror(errno));
                exit(EXIT_FAILURE);
            }
        }
        input[i+1] = NULL;
    }

    for (j = 0; input[j] != NULL; j++) {
        while (fgets(line, BUFSIZE, input[0]) != NULL) {
            matchsplit(line, splitsies, BUFSIZE);
            for (i = 0; splitsies[i]; i++) {
                printf("%s%s", splitsies[i], delimiter);
            }
            printf("%s", line_delimiter);
        }

        if (ferror(input[0])) {
            fprintf(stderr, "%s: error reading input: %s", argv[0], strerror(errno));
            exit(errno);
        }
    }

    return 0;
}
