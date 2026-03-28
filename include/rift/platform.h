#ifndef RIFT_PLATFORM_H
#define RIFT_PLATFORM_H

#ifdef __cplusplus
extern "C" {
#endif

/* Platform detection */
#if defined(_WIN32) || defined(_WIN64)
    #define RIFT_PLATFORM_WINDOWS 1
#elif defined(__APPLE__)
    #define RIFT_PLATFORM_MACOS 1
#elif defined(__linux__)
    #define RIFT_PLATFORM_LINUX 1
#else
    #define RIFT_PLATFORM_UNKNOWN 1
#endif

/* RIFT_API: DLL export/import for Windows, visibility for Unix */
#if defined(RIFT_PLATFORM_WINDOWS)
    #if defined(RIFT_BUILD_DLL)
        #define RIFT_API __declspec(dllexport)
    #elif defined(RIFT_USE_DLL)
        #define RIFT_API __declspec(dllimport)
    #else
        #define RIFT_API
    #endif
    #define RIFT_CALL __cdecl
#else
    #if defined(RIFT_BUILD_DLL)
        #define RIFT_API __attribute__((visibility("default")))
    #else
        #define RIFT_API
    #endif
    #define RIFT_CALL
#endif

/* Thread abstraction */
#if defined(RIFT_PLATFORM_WINDOWS)
    #ifndef WIN32_LEAN_AND_MEAN
        #define WIN32_LEAN_AND_MEAN
    #endif
    #include <windows.h>
    typedef CRITICAL_SECTION rift_mutex_t;
    typedef HANDLE rift_thread_t;
#else
    #include <pthread.h>
    typedef pthread_mutex_t rift_mutex_t;
    typedef pthread_t rift_thread_t;
#endif

/* Regex abstraction */
#if defined(RIFT_PLATFORM_WINDOWS)
    /* Minimal regex stub for Windows (no POSIX regex) */
    #define RIFT_REGEX_STUB 1
    typedef struct {
        const char *pattern;
        int compiled;
    } rift_regex_t;
#else
    #include <regex.h>
    typedef regex_t rift_regex_t;
#endif

/* Platform functions */
RIFT_API int  rift_mutex_init(rift_mutex_t *mutex);
RIFT_API int  rift_mutex_lock(rift_mutex_t *mutex);
RIFT_API int  rift_mutex_unlock(rift_mutex_t *mutex);
RIFT_API int  rift_mutex_destroy(rift_mutex_t *mutex);

RIFT_API int  rift_regex_compile(rift_regex_t *rx, const char *pattern);
RIFT_API int  rift_regex_match(const rift_regex_t *rx, const char *text);
RIFT_API void rift_regex_free(rift_regex_t *rx);

RIFT_API double rift_time_ms(void);

#ifdef __cplusplus
}
#endif

#endif /* RIFT_PLATFORM_H */
