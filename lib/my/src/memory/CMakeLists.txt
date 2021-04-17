set(INCROOT ${PROJECT_SOURCE_DIR}/include/libmy)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/memory)

set(SRC
    ${INCROOT}/memory.h
    ${INCROOT}/memory/cbuffer.h
    ${INCROOT}/memory/config.h
    ${INCROOT}/memory/memory.h
    ${INCROOT}/memory/endian.h
    ${INCROOT}/internal/memory.h
    ${SRCROOT}/my_binary_search.c
    ${SRCROOT}/my_cbuffer_get_parts.c
    ${SRCROOT}/my_cbuffer_init.c
    ${SRCROOT}/my_cbuffer_pop.c
    ${SRCROOT}/my_cbuffer_push.c
    ${SRCROOT}/my_cbuffer_read.c
    ${SRCROOT}/my_cbuffer_rotate.c
    ${SRCROOT}/my_cbuffer_write.c
    ${SRCROOT}/my_memchr.c
    ${SRCROOT}/my_memcpy.c
    ${SRCROOT}/my_memmove.c
    ${SRCROOT}/my_memrev.c
    ${SRCROOT}/my_memset.c
    ${SRCROOT}/my_memswap.c
    ${SRCROOT}/my_msort.c
    ${SRCROOT}/my_swap_ptr.c
)

if (LIBMY_ALLOW_MALLOC_FREE)
    set(SRC
        ${INCROOT}/memory/alloc.h
        ${SRCROOT}/my_calloc.c
        ${SRCROOT}/my_realloc.c
        ${SRCROOT}/my_sfree.c
        ${SRC}
    )
endif()

# IDE source group
source_group("" FILES ${SRC})

libmy_add_module(my-memory SOURCES ${SRC})

target_include_directories(my-memory PUBLIC "${PROJECT_SOURCE_DIR}/include")
