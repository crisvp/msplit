#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <assert.h>

#include <delimiter.h>
#include <matchsplit.h>

//size_t matchsplit(char *s, char **argv, size_t max) {

void
test_matchsplit(const char *description, char *s, char **argv, size_t max,
    size_t expected_result, char **expected_elements)
{
    size_t actual_result;
    int i;

    printf("Running test: %s\n", description);

    printf("Splitting string: %s\n", s);
    actual_result = matchsplit(s, argv, max);

    printf("Actual result: %lu, expected result: %lu\n", actual_result,
        expected_result);
    assert(actual_result == expected_result);

    for (i = 0; i < actual_result; i++) {
        printf("Comparing result %d (%s == %s)\n", i, expected_elements[i], argv[i]);
        assert(strcmp(expected_elements[i], argv[i]) == 0);
    }

}

char **
string_array(int argc, ...)
{
    char **result;
    va_list valist;
    int i;

    assert(argc < 100);

    result = malloc(argc * sizeof(char *));
    assert(result != NULL);

    va_start(valist, argc);
    for (i = 0; i < argc; i++) {
        result[i] = strdup(va_arg(valist, char *));
    }
    va_end(valist);

    return result;
}

int
main()
{
    char *results[100];
    char **r;
    printf("Running tests.\n");

    r = string_array(1, "abc");
    test_matchsplit("Single word", strdup("abc"), results, 8, 1, r);

    r = string_array(2, "abc", "def");
    test_matchsplit("Double word", strdup("abc def"), results, 8, 2, r);

    r = string_array(1, "abc");
    test_matchsplit("Single word, double quotes", strdup("\"abc\""), results, 8, 1, r);

    r = string_array(2, "abc", "def");
    test_matchsplit("Double word, double quotes", strdup("\"abc\" \"def\""), results, 8, 2, r);

    r = string_array(2, "abc", "def");
    test_matchsplit("Double word, single quotes", strdup("'abc' 'def'"), results, 8, 2, r);

    r = string_array(1, "\"abc\" \"def\"");
    test_matchsplit("Double word, nested quotes", strdup("'\"abc\" \"def\"'"), results, 8, 1, r);

    r = string_array(3, "abc", "def", "");
    test_matchsplit("Double word, improperly nested quotes", strdup("\"abc\" \"def\"'"), results, 8, 3, r);

    r = string_array(3, "abc", "def", " efg");
    test_matchsplit("Double word, improperly nested quotes #2", strdup("\"abc\" \"def\"' efg"), results, 8, 3, r);

    test_matchsplit("NULL pointer", NULL, results, 8, 0, r);

    printf("\n\nAll tests passed.\n");

    return 0;
}
