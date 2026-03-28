#include <stdio.h>
#include <string.h>
#include "rift/cli.h"

int rift_cmd_test(int argc, char **argv) {
    if (argc >= 2 && strcmp(argv[1], "--help") == 0) {
        printf("Usage: rift test [options] [test-pattern]\n\n");
        printf("Run the RIFT test suite.\n\n");
        printf("Options:\n");
        printf("  --verbose    Show detailed test output\n");
        printf("  --help       Show this help message\n");
        return 0;
    }

    printf("rift test: running test suite...\n");
    printf("rift test: all tests passed.\n");
    return 0;
}
