set(INCROOT ${PROJECT_SOURCE_DIR}/include)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src)

set(SRC
    ${INCROOT}/builtin.h
    ${INCROOT}/context.h
    ${INCROOT}/definition.h
    ${INCROOT}/error.h
    ${INCROOT}/shell.h
    ${SRCROOT}/context.c
    ${SRCROOT}/cwd.c
    ${SRCROOT}/env.c
    ${SRCROOT}/error.c
    ${SRCROOT}/execute.c
    ${SRCROOT}/lint.c
    ${SRCROOT}/print.c
    ${SRCROOT}/reset_path.c
    ${SRCROOT}/start.c
    ${SRCROOT}/status.c
)

add_subdirectory(builtin)
add_subdirectory(command)
add_subdirectory(token)
add_subdirectory(util)

source_group("" FILES ${SRC})

add_library(mysh-lib STATIC ${SRC})
add_executable(mysh ${SRCROOT}/main.c)

target_link_libraries(mysh-lib PUBLIC my-ascii my-collections my-hash my-io my-memory my-parsing my-printf)
target_link_libraries(mysh PRIVATE mysh-lib)

target_include_directories(mysh-lib PUBLIC ${INCROOT} ${LIBMY_INCLUDE_DIR})

add_custom_command(TARGET mysh
	POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:mysh> ${PROJECT_SOURCE_DIR})

