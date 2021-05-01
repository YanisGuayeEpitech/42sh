set(SRCROOT ${PROJECT_SOURCE_DIR}/src/command)
set(INCROOT ${PROJECT_SOURCE_DIR}/include)

set(SRC
    ${SRC}
    ${INCROOT}/command.h
    ${SRCROOT}/command_drop.c
    ${SRCROOT}/command_execute_builtin.c
    ${SRCROOT}/command_execute_external.c
    ${SRCROOT}/command_execute.c
    ${SRCROOT}/command_init.c
    ${SRCROOT}/command_parse.c
    ${SRCROOT}/command_resolve.c
    ${SRCROOT}/command_resolve.c
    ${SRCROOT}/external_pipe.c
    PARENT_SCOPE
)
