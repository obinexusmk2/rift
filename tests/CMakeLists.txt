# RIFT Test Suite

set(TEST_SOURCES
    test_token.c
    test_lexer.c
    test_codec.c
)

foreach(test_src ${TEST_SOURCES})
    get_filename_component(test_name ${test_src} NAME_WE)
    add_executable(${test_name} ${test_src})
    target_link_libraries(${test_name} PRIVATE rift_static)
    target_include_directories(${test_name} PRIVATE ${CMAKE_SOURCE_DIR}/include)
    add_test(NAME ${test_name} COMMAND ${test_name})
endforeach()

# test_cli needs CLI sources (dispatch + commands)
add_executable(test_cli test_cli.c
    ${CMAKE_SOURCE_DIR}/src/cli/dispatch.c
    ${CMAKE_SOURCE_DIR}/src/cli/cmd_bridge.c
    ${CMAKE_SOURCE_DIR}/src/cli/cmd_test.c
    ${CMAKE_SOURCE_DIR}/src/cli/cmd_lang.c
    ${CMAKE_SOURCE_DIR}/src/cli/cmd_man.c
    ${CMAKE_SOURCE_DIR}/src/cli/cmd_doctor.c
    ${CMAKE_SOURCE_DIR}/src/cli/cmd_raf.c
    ${CMAKE_SOURCE_DIR}/src/cli/cmd_compile.c
    ${CMAKE_SOURCE_DIR}/src/cli/cmd_tokenize.c
    ${CMAKE_SOURCE_DIR}/src/cli/cmd_parse.c
    ${CMAKE_SOURCE_DIR}/src/cli/cmd_emit.c
)
target_link_libraries(test_cli PRIVATE rift_static)
target_include_directories(test_cli PRIVATE ${CMAKE_SOURCE_DIR}/include)
add_test(NAME test_cli COMMAND test_cli)
