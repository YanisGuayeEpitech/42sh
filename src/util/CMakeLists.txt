set(SRCROOT ${PROJECT_SOURCE_DIR}/src/util)
set(INCROOT ${PROJECT_SOURCE_DIR}/include)

set(SRC
    ${SRC}
    ${INCROOT}/util.h
    ${SRCROOT}/create_file_path.c
    ${SRCROOT}/free_entry.c
    ${SRCROOT}/sclose.c
    PARENT_SCOPE
)
