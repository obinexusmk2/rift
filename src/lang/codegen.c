#include "rift/codegen.h"
#include <stdlib.h>

struct rift_codegen {
    int initialized;
};

rift_codegen_t *rift_codegen_create(void) {
    rift_codegen_t *cg = (rift_codegen_t *)calloc(1, sizeof(rift_codegen_t));
    if (cg) cg->initialized = 1;
    return cg;
}

void rift_codegen_destroy(rift_codegen_t *cg) {
    free(cg);
}

int rift_codegen_generate(rift_codegen_t *cg, const rift_ast_node_t *ast) {
    if (!cg || !ast) return -1;
    /* TODO: IR/bytecode generation */
    return 0;
}
