set(SRCROOT ${PROJECT_SOURCE_DIR}/src/builtin)

set(SRC
    ${SRC}
    ${SRCROOT}/cd.c
    ${SRCROOT}/dirs.c
    ${SRCROOT}/env.c
    ${SRCROOT}/exit.c
    ${SRCROOT}/get_builtin.c
    ${SRCROOT}/setenv.c
    ${SRCROOT}/unsetenv.c
    PARENT_SCOPE
)
