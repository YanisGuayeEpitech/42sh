set(SRCROOT ${PROJECT_SOURCE_DIR}/src/line_edit/keybinds)
set(INCROOT ${PROJECT_SOURCE_DIR}/include)

set(SRC
    ${SRC}
    ${INCROOT}/line_edit.h
    ${SRCROOT}/keybind_delete.c
    ${SRCROOT}/keybind_empty.c
    ${SRCROOT}/keybind_eof.c
    ${SRCROOT}/keybind_move_cursor.c
    ${SRCROOT}/keybind_show.c
    ${SRCROOT}/keybinds.c
    PARENT_SCOPE
)
