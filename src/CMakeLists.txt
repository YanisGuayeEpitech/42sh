set(INCROOT ${PROJECT_SOURCE_DIR}/include)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src)

set(SRC
    ${INCROOT}/builtin.h
    ${INCROOT}/context.h
    ${INCROOT}/definition.h
    ${INCROOT}/error.h
    ${INCROOT}/shell.h
    ${SRCROOT}/args.c
    ${SRCROOT}/builtin.c
    ${SRCROOT}/context.c
    ${SRCROOT}/create_file_path.c
    ${SRCROOT}/cwd.c
    ${SRCROOT}/env.c
    ${SRCROOT}/error.c
    ${SRCROOT}/exec.c
    ${SRCROOT}/find_executable.c
    ${SRCROOT}/main.c
    ${SRCROOT}/parsing.c
    ${SRCROOT}/print.c
    ${SRCROOT}/read_line.c
    ${SRCROOT}/reset_path.c
    ${SRCROOT}/start.c
    ${SRCROOT}/status.c
    ${SRCROOT}/util.c
)

add_subdirectory(builtin)

source_group("" FILES ${SRC})

add_executable(mysh ${SRC})
add_custom_command(TARGET mysh
	POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:mysh> ${PROJECT_SOURCE_DIR})

target_link_libraries(mysh PRIVATE my-ascii my-collections my-hash my-io my-memory my-parsing my-printf)
target_include_directories(mysh PRIVATE ${INCROOT} ${LIBMY_INCLUDE_DIR})
