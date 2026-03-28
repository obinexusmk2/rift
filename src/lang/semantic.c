#include "rift/semantic.h"
#include <stdlib.h>

struct rift_semantic {
    int initialized;
};

rift_semantic_t *rift_semantic_create(void) {
    rift_semantic_t *sem = (rift_semantic_t *)calloc(1, sizeof(rift_semantic_t));
    if (sem) sem->initialized = 1;
    return sem;
}

void rift_semantic_destroy(rift_semantic_t *sem) {
    free(sem);
}

int rift_semantic_analyze(rift_semantic_t *sem, rift_ast_node_t *ast) {
    if (!sem || !ast) return -1;
    /* TODO: Z->Y->X internal reduction */
    return 0;
}

int rift_semantic_resolve_types(rift_semantic_t *sem) {
    if (!sem) return -1;
    return 0;
}

int rift_semantic_tag_regions(rift_semantic_t *sem) {
    if (!sem) return -1;
    return 0;
}
