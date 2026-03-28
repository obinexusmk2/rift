#include "rift/emitter.h"
#include <stdlib.h>
#include <string.h>

struct rift_emitter {
    rift_emit_target_t target;
};

rift_emitter_t *rift_emitter_create(rift_emit_target_t target) {
    rift_emitter_t *emitter = (rift_emitter_t *)calloc(1, sizeof(rift_emitter_t));
    if (emitter) emitter->target = target;
    return emitter;
}

void rift_emitter_destroy(rift_emitter_t *emitter) {
    free(emitter);
}

int rift_emitter_emit(rift_emitter_t *emitter, const void *ir, const char *output_path) {
    if (!emitter || !ir) return -1;
    (void)output_path;
    /* TODO: emit to target format */
    return 0;
}
