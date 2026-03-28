#include "rift/token.h"
#include <stdlib.h>
#include <string.h>

rift_token_t rift_token_create(rift_token_type_t type, const char *value) {
    rift_token_t token;
    memset(&token, 0, sizeof(token));
    token.type = type;

    if (value) {
        size_t len = strlen(value) + 1;
        token.memory = rift_memory_alloc(len, RIFT_MEMORY_ALIGN_DEFAULT);
        if (token.memory.ptr) {
            memcpy(token.memory.ptr, value, len);
            token.value.str = (char *)token.memory.ptr;
        }
    }

    token.validation_bits = 0x07; /* type | value | memory all valid */
    return token;
}

void rift_token_destroy(rift_token_t *token) {
    if (!token) return;
    rift_memory_free(&token->memory);
    memset(token, 0, sizeof(*token));
}

int rift_token_validate(const rift_token_t *token) {
    if (!token) return 0;
    if (token->type == RIFT_TOKEN_UNKNOWN) return 0;
    if ((token->validation_bits & 0x07) != 0x07) return 0;
    return rift_memory_validate(&token->memory);
}

static const char *token_type_names[] = {
    "EOF", "KEYWORD", "IDENTIFIER",
    "LITERAL_INT", "LITERAL_FLOAT", "LITERAL_STRING", "LITERAL_CHAR",
    "OPERATOR", "DELIMITER", "COMMENT", "WHITESPACE",
    "PATTERN_STATIC", "PATTERN_DYNAMIC", "HEXDUMP", "UNKNOWN"
};

const char *rift_token_type_name(rift_token_type_t type) {
    if (type < 0 || type > RIFT_TOKEN_UNKNOWN) return "INVALID";
    return token_type_names[type];
}
