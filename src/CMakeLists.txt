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

add_library(42sh-lib STATIC ${SRC})
add_executable(42sh ${SRCROOT}/main.c)

target_link_libraries(42sh-lib PUBLIC my-ascii my-collections my-hash my-io my-memory my-parsing my-printf)
target_link_libraries(42sh PRIVATE 42sh-lib)

target_include_directories(42sh-lib PUBLIC ${INCROOT} ${LIBMY_INCLUDE_DIR})

add_custom_command(TARGET 42sh
	POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:42sh> ${PROJECT_SOURCE_DIR})

