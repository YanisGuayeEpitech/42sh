set(SRCROOT "${PROJECT_SOURCE_DIR}/tests/io")

set(SRC
    ${SRCROOT}/test_my_fclose.c
    ${SRCROOT}/test_my_feof.c
    ${SRCROOT}/test_my_fflush.c
    ${SRCROOT}/test_my_ffree.c
    ${SRCROOT}/test_my_fget_buffer.c
    ${SRCROOT}/test_my_finit.c
    ${SRCROOT}/test_my_flush_iostream.c
    ${SRCROOT}/test_my_fputc.c
    ${SRCROOT}/test_my_fputint.c
    ${SRCROOT}/test_my_fputintmax_t_base.c
    ${SRCROOT}/test_my_fputs.c
    ${SRCROOT}/test_my_fputs_endl.c
    ${SRCROOT}/test_my_fputuint.c
    ${SRCROOT}/test_my_fputuintmax_t_base.c
    ${SRCROOT}/test_my_fread.c
    ${SRCROOT}/test_my_free_iostream.c
    ${SRCROOT}/test_my_frputc.c
    ${SRCROOT}/test_my_fset_buffer.c
    ${SRCROOT}/test_my_fset_threshold.c
    ${SRCROOT}/test_my_fwrite.c
    ${SRCROOT}/test_my_get_iostream.c
    ${SRCROOT}/test_my_init_iostream.c
    ${SRCROOT}/test_my_is_iostream.c
    ${SRCROOT}/test_my_putchar.c
    ${SRCROOT}/test_my_put_nbr.c
    ${SRCROOT}/test_my_putstr.c
    ${SRCROOT}/test_my_putuint.c
    ${SRCROOT}/test_my_show_word_array.c
    ${SRCROOT}/test_my_showmem.c
    ${SRCROOT}/test_my_showstr.c
)

if ("close" IN_LIST LIBMY_ALLOWED_FUNCTIONS_LIST)
    set(SRC
        ${SRCROOT}/test_my_fclose_allow_close.c
        ${SRC}
    )
endif()

if ("read" IN_LIST LIBMY_ALLOWED_FUNCTIONS_LIST)
    set(SRC
        ${SRCROOT}/test_my_fread_allow_read.c
        ${SRCROOT}/test_my_fread_to_string_allow_read.c
        ${SRC}
    )
endif()

if (LIBMY_ALLOW_MALLOC_FREE)
    set(SRC
        ${SRCROOT}/test_my_fread_to_string.c
        ${SRCROOT}/test_my_getdelim.c
        ${SRC}
    )
endif()

libmy_add_test(test-libmy-io "${SRC}" my-io)
