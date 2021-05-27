set(SRCROOT ${PROJECT_SOURCE_DIR}/src/line_edit/completion)
set(INCROOT ${PROJECT_SOURCE_DIR}/include)

set(SRC
    ${SRC}
    ${INCROOT}/completion.h
    ${SRCROOT}/get_completion_list.c
    PARENT_SCOPE
)
