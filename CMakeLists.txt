cmake_minimum_required(VERSION 3.16)

project(RIFT
    VERSION 5.0.0
    DESCRIPTION "RIFT Is a Flexible Translator"
    LANGUAGES C CXX
)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(cmake/platform.cmake)
include(cmake/options.cmake)

# --- Source file lists ---

set(RIFT_CORE_SOURCES
    src/core/rift.c
    src/core/token.c
    src/core/memory.c
    src/core/platform.c
)

set(RIFT_LANG_SOURCES
    src/lang/lexer.c
    src/lang/parser.c
    src/lang/semantic.c
    src/lang/validator.c
    src/lang/codegen.c
    src/lang/emitter.c
    src/lang/pattern.c
)

set(RIFT_CODEC_SOURCES
    src/codec/codec.c
    src/codec/targets/emit_c.c
    src/codec/targets/emit_hexdump.c
)

set(RIFT_BRIDGE_SOURCES
    src/bridge/bridge.c
    src/bridge/trident.c
    src/bridge/ropen.c
)

set(RIFT_RAF_SOURCES
    src/raf/raf.c
)

set(RIFT_LIB_SOURCES
    ${RIFT_CORE_SOURCES}
    ${RIFT_LANG_SOURCES}
    ${RIFT_CODEC_SOURCES}
    ${RIFT_BRIDGE_SOURCES}
    ${RIFT_RAF_SOURCES}
)

set(RIFT_CLI_SOURCES
    src/cli/main.c
    src/cli/dispatch.c
    src/cli/cmd_bridge.c
    src/cli/cmd_test.c
    src/cli/cmd_lang.c
    src/cli/cmd_man.c
    src/cli/cmd_doctor.c
    src/cli/cmd_raf.c
    src/cli/cmd_compile.c
    src/cli/cmd_tokenize.c
    src/cli/cmd_parse.c
    src/cli/cmd_emit.c
)

# --- Static library: rift.a / rift.lib ---
add_library(rift_static STATIC ${RIFT_LIB_SOURCES})
target_include_directories(rift_static PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)
set_target_properties(rift_static PROPERTIES OUTPUT_NAME rift)

# --- Shared library: rift.dll / rift.so / rift.dylib ---
add_library(rift_shared SHARED ${RIFT_LIB_SOURCES})
target_include_directories(rift_shared PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)
target_compile_definitions(rift_shared PRIVATE RIFT_BUILD_DLL)
set_target_properties(rift_shared PROPERTIES OUTPUT_NAME rift)

# --- CLI executable: rift.exe / rift ---
add_executable(rift_cli ${RIFT_CLI_SOURCES})
target_link_libraries(rift_cli PRIVATE rift_static)
target_include_directories(rift_cli PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
set_target_properties(rift_cli PROPERTIES OUTPUT_NAME rift)

# --- Platform link dependencies ---
if(NOT WIN32)
    find_package(Threads REQUIRED)
    target_link_libraries(rift_static PRIVATE Threads::Threads)
    target_link_libraries(rift_shared PRIVATE Threads::Threads)
endif()

# --- Build output directories ---
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# --- Testing ---
option(RIFT_BUILD_TESTS "Build test suite" ON)
if(RIFT_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

# --- Install ---
install(TARGETS rift_static rift_shared rift_cli
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)
install(DIRECTORY include/rift DESTINATION include)
