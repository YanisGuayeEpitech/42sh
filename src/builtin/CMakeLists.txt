set(SRCROOT ${PROJECT_SOURCE_DIR}/src/builtin)

set(SRC
    ${SRC}
    ${SRCROOT}/bindkey.c
    ${SRCROOT}/builtins.c
    ${SRCROOT}/cd.c
    ${SRCROOT}/dirs.c
    ${SRCROOT}/env.c
    ${SRCROOT}/exit.c
    ${SRCROOT}/get_builtin.c
    ${SRCROOT}/repeat.c
    ${SRCROOT}/set.c
    ${SRCROOT}/setenv.c
    ${SRCROOT}/unsetenv.c
    PARENT_SCOPE
)
