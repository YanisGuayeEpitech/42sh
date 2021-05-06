set(SRCROOT "${PROJECT_SOURCE_DIR}/tests")

set(SRC
    ${SRCROOT}/test_args.c
    ${SRCROOT}/test_context.c
    ${SRCROOT}/test_create_file_path.c
    ${SRCROOT}/test_env.c
    ${SRCROOT}/test_error.c
    ${SRCROOT}/test_parsing.c
    ${SRCROOT}/test_reset_path.c
    ${SRCROOT}/test_util.c
)

add_executable(test-42sh ${SRC})

source_group("" FILES ${SRC})
set_target_properties(test-42sh PROPERTIES FOLDER "tests")

if (CMAKE_COMPILER_IS_GNUCC)
    target_compile_options(test-42sh PRIVATE -Wall -Wextra)
endif()

target_link_libraries(test-42sh PRIVATE 42sh-lib ${CRITERION_LIBRARIES})

# Link to gcov if build type is set to 'static'
if (CMAKE_COMPILER_IS_GNUCC AND USE_GCOV)
    target_link_libraries(test-42sh PRIVATE gcov)
endif()

add_test(test-42sh test-42sh)
