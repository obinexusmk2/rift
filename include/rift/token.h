#ifndef RIFT_TOKEN_H
#define RIFT_TOKEN_H

#include <stddef.h>
#include <stdint.h>
#include "rift/platform.h"
#include "rift/memory.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Token types */
typedef enum rift_token_type {
    RIFT_TOKEN_EOF = 0,
    RIFT_TOKEN_KEYWORD,
    RIFT_TOKEN_IDENTIFIER,
    RIFT_TOKEN_LITERAL_INT,
    RIFT_TOKEN_LITERAL_FLOAT,
    RIFT_TOKEN_LITERAL_STRING,
    RIFT_TOKEN_LITERAL_CHAR,
    RIFT_TOKEN_OPERATOR,
    RIFT_TOKEN_DELIMITER,
    RIFT_TOKEN_COMMENT,
    RIFT_TOKEN_WHITESPACE,
    RIFT_TOKEN_PATTERN_STATIC,   /* R"" - compile-time static string */
    RIFT_TOKEN_PATTERN_DYNAMIC,  /* R'' - runtime dynamic character */
    RIFT_TOKEN_HEXDUMP,          /* Hexdump canonical form */
    RIFT_TOKEN_UNKNOWN
} rift_token_type_t;

/* Token value union */
typedef union rift_token_value {
    int64_t  i64;
    uint64_t u64;
    double   f64;
    char    *str;
} rift_token_value_t;

/*
 * Token Triplet: the fundamental RIFT unit
 *   - type:   semantic classification
 *   - value:  the token's data
 *   - memory: memory governance for this token
 */
typedef struct rift_token {
    rift_token_type_t    type;
    rift_token_value_t   value;
    rift_memory_span_t   memory;
    uint8_t              validation_bits;
    uint32_t             line;
    uint32_t             column;
} rift_token_t;

RIFT_API rift_token_t  rift_token_create(rift_token_type_t type, const char *value);
RIFT_API void          rift_token_destroy(rift_token_t *token);
RIFT_API int           rift_token_validate(const rift_token_t *token);
RIFT_API const char   *rift_token_type_name(rift_token_type_t type);

#ifdef __cplusplus
}
#endif

#endif /* RIFT_TOKEN_H */
