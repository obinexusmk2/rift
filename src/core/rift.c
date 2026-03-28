#include "rift/rift.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

rift_context_t *rift_init(void) {
    rift_context_t *ctx = (rift_context_t *)calloc(1, sizeof(rift_context_t));
    if (!ctx) return NULL;

    ctx->last_error = RIFT_SUCCESS;
    return ctx;
}

void rift_cleanup(rift_context_t *ctx) {
    if (!ctx) return;

    if (ctx->lexer)    rift_lexer_destroy(ctx->lexer);
    if (ctx->parser)   rift_parser_destroy(ctx->parser);
    if (ctx->semantic) rift_semantic_destroy(ctx->semantic);
    if (ctx->codegen)  rift_codegen_destroy(ctx->codegen);
    if (ctx->emitter)  rift_emitter_destroy(ctx->emitter);
    if (ctx->bridge)   rift_bridge_destroy(ctx->bridge);
    if (ctx->pattern)  rift_pattern_destroy(ctx->pattern);

    free(ctx);
}

rift_error_t rift_compile(rift_context_t *ctx,
                           const char *input_path,
                           const char *output_path) {
    if (!ctx || !input_path) return RIFT_ERROR_INVALID_ARGUMENT;

    (void)output_path;

    if (ctx->verbose) {
        printf("rift: compiling %s\n", input_path);
    }

    /* TODO: wire full Z->Y->X internal pipeline */
    ctx->last_error = RIFT_SUCCESS;
    return RIFT_SUCCESS;
}

static const char *error_strings[] = {
    "success",
    "invalid argument",
    "memory allocation failed",
    "file access error",
    "parse failure",
    "semantic analysis failure",
    "code generation failure",
    "emission failure",
    "link failure",
    "unknown error"
};

const char *rift_error_string(rift_error_t err) {
    if (err < 0 || err > RIFT_ERROR_UNKNOWN) return "invalid error code";
    return error_strings[err];
}
