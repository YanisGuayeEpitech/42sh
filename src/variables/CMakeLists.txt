set(SRCROOT ${PROJECT_SOURCE_DIR}/src/variables)
set(INCROOT ${PROJECT_SOURCE_DIR}/include)

set(SRC
    ${SRC}
    ${INCROOT}/variables.h
    ${SRCROOT}/check_var_name.c
    PARENT_SCOPE
)
