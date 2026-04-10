#include "rift/platform.h"
#include <string.h>
#if !defined(RIFT_PLATFORM_WINDOWS)
#  include <time.h>
#endif

/* Mutex implementation */

int rift_mutex_init(rift_mutex_t *mutex) {
    if (!mutex) return -1;
#if defined(RIFT_PLATFORM_WINDOWS)
    InitializeCriticalSection(mutex);
    return 0;
#else
    return pthread_mutex_init(mutex, NULL);
#endif
}

int rift_mutex_lock(rift_mutex_t *mutex) {
    if (!mutex) return -1;
#if defined(RIFT_PLATFORM_WINDOWS)
    EnterCriticalSection(mutex);
    return 0;
#else
    return pthread_mutex_lock(mutex);
#endif
}

int rift_mutex_unlock(rift_mutex_t *mutex) {
    if (!mutex) return -1;
#if defined(RIFT_PLATFORM_WINDOWS)
    LeaveCriticalSection(mutex);
    return 0;
#else
    return pthread_mutex_unlock(mutex);
#endif
}

int rift_mutex_destroy(rift_mutex_t *mutex) {
    if (!mutex) return -1;
#if defined(RIFT_PLATFORM_WINDOWS)
    DeleteCriticalSection(mutex);
    return 0;
#else
    return pthread_mutex_destroy(mutex);
#endif
}

/* Regex implementation */

int rift_regex_compile(rift_regex_t *rx, const char *pattern) {
    if (!rx || !pattern) return -1;
#if defined(RIFT_REGEX_STUB)
    rx->pattern = pattern;
    rx->compiled = 1;
    return 0;
#else
    return regcomp(rx, pattern, REG_EXTENDED | REG_NOSUB);
#endif
}

int rift_regex_match(const rift_regex_t *rx, const char *text) {
    if (!rx || !text) return -1;
#if defined(RIFT_REGEX_STUB)
    if (!rx->compiled) return -1;
    /* Stub: simple substring match */
    return strstr(text, rx->pattern) != NULL ? 0 : 1;
#else
    return regexec(rx, text, 0, NULL, 0);
#endif
}

void rift_regex_free(rift_regex_t *rx) {
    if (!rx) return;
#if defined(RIFT_REGEX_STUB)
    rx->pattern = NULL;
    rx->compiled = 0;
#else
    regfree(rx);
#endif
}

/* Timing */

double rift_time_ms(void) {
#if defined(RIFT_PLATFORM_WINDOWS)
    LARGE_INTEGER freq, counter;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&counter);
    return (double)counter.QuadPart / (double)freq.QuadPart * 1000.0;
#else
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (double)ts.tv_sec * 1000.0 + (double)ts.tv_nsec / 1000000.0;
#endif
}
