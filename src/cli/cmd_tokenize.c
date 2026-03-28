#include <stdio.h>
#include <string.h>
#include "rift/cli.h"
#include "rift/lexer.h"

int rift_cmd_tokenize(int argc, char **argv) {
    if (argc < 2 || strcmp(argv[1], "--help") == 0) {
        printf("Usage: rift tokenize [options] <input-file>\n\n");
        printf("Tokenize a RIFT source file and output the token stream.\n\n");
        printf("Options:\n");
        printf("  --format <f>  Output format (text, json, csv)\n");
        printf("  --help        Show this help message\n");
        return 0;
    }

    printf("rift tokenize: tokenizer ready for '%s'\n", argv[1]);
    return 0;
}
