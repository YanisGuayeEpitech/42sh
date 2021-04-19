set(SRCROOT "${PROJECT_SOURCE_DIR}/tests/memory")

set(SRC
    ${SRCROOT}/test_my_binary_search.c
    ${SRCROOT}/test_my_cbuffer_get_parts.c
    ${SRCROOT}/test_my_cbuffer_init.c
    ${SRCROOT}/test_my_cbuffer_pop.c
    ${SRCROOT}/test_my_cbuffer_push.c
    ${SRCROOT}/test_my_cbuffer_read.c
    ${SRCROOT}/test_my_cbuffer_rotate.c
    ${SRCROOT}/test_my_cbuffer_write.c
    ${SRCROOT}/test_my_endian.c
    ${SRCROOT}/test_my_memchr.c
    ${SRCROOT}/test_my_memcmp.c
    ${SRCROOT}/test_my_memcpy.c
    ${SRCROOT}/test_my_memmove.c
    ${SRCROOT}/test_my_memrev.c
    ${SRCROOT}/test_my_memset.c
    ${SRCROOT}/test_my_memswap.c
    ${SRCROOT}/test_my_msort.c
    ${SRCROOT}/test_my_swap_ptr.c
)

if (LIBMY_ALLOW_MALLOC_FREE)
    set(SRC
        ${SRCROOT}/test_my_calloc.c
        ${SRCROOT}/test_my_memdup.c
        ${SRCROOT}/test_my_realloc.c
        ${SRCROOT}/test_my_sfree.c
        ${SRC}
    )
endif()

libmy_add_test(test-libmy-memory "${SRC}" my-memory)
