#include <stdio.h>
#include <string.h>
#include "rift/cli.h"
#include "rift/pattern.h"

int rift_cmd_lang(int argc, char **argv) {
    if (argc < 2 || strcmp(argv[1], "--help") == 0) {
        printf("Usage: rift lang [options] <file>\n\n");
        printf("RIFTLang pattern matching engine.\n\n");
        printf("Options:\n");
        printf("  --pattern <expr>  Apply pattern expression\n");
        printf("  --static          Use R\"\" static mode\n");
        printf("  --dynamic         Use R'' dynamic mode\n");
        printf("  --help            Show this help message\n");
        return 0;
    }

    printf("rift lang: pattern engine ready\n");
    return 0;
}
