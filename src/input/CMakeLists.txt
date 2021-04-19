set(SRCROOT ${PROJECT_SOURCE_DIR}/src/input)
set(INCROOT ${PROJECT_SOURCE_DIR}/include)

set(SRC
    ${SRC}
    ${INCROOT}/input.h
    ${SRCROOT}/token_stream_drop.c
    ${SRCROOT}/token_stream_init.c
    ${SRCROOT}/token_stream_parse.c
    ${SRCROOT}/token_stream_push.c
    PARENT_SCOPE
)
