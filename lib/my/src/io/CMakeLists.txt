set(INCROOT ${PROJECT_SOURCE_DIR}/include/libmy)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/io)

set(SRC
    ${INCROOT}/io.h
    ${INCROOT}/io/config.h
    ${INCROOT}/io/iostream.h
    ${INCROOT}/io/raw.h
    ${SRCROOT}/my_fclose.c
    ${SRCROOT}/my_feof.c
    ${SRCROOT}/my_fflush.c
    ${SRCROOT}/my_ffree.c
    ${SRCROOT}/my_fget_buffer.c
    ${SRCROOT}/my_finit.c
    ${SRCROOT}/my_flush_iostream.c
    ${SRCROOT}/my_fopen.h
    ${SRCROOT}/my_fopen.c
    ${SRCROOT}/my_fputc.c
    ${SRCROOT}/my_fputint.c
    ${SRCROOT}/my_fputintmax_t_base.c
    ${SRCROOT}/my_fputs.c
    ${SRCROOT}/my_fputs_endl.c
    ${SRCROOT}/my_fputuint.c
    ${SRCROOT}/my_fputuintmax_t_base.c
    ${SRCROOT}/my_fread.c
    ${SRCROOT}/my_free_iostream.c
    ${SRCROOT}/my_frputc.c
    ${SRCROOT}/my_fset_buffer.c
    ${SRCROOT}/my_fset_threshold.c
    ${SRCROOT}/my_fwrite.c
    ${SRCROOT}/my_get_iostream.c
    ${SRCROOT}/my_init_iostream.c
    ${SRCROOT}/my_is_iostream.c
    ${SRCROOT}/my_putchar.c
    ${SRCROOT}/my_put_nbr.c
    ${SRCROOT}/my_putstr.c
    ${SRCROOT}/my_putuint.c
    ${SRCROOT}/my_show_word_array.c
    ${SRCROOT}/my_showmem.c
    ${SRCROOT}/my_showstr.c
)

if ("close" IN_LIST LIBMY_ALLOWED_FUNCTIONS_LIST)
    set(SRC
        ${SRCROOT}/my_fclose_allow_close.c
        ${SRC}
    )
endif()

if ("read" IN_LIST LIBMY_ALLOWED_FUNCTIONS_LIST)
    set(SRC
        ${SRCROOT}/my_fread_allow_read.c
        ${SRCROOT}/my_fread_to_string_allow_read.c
        ${SRC}
    )
endif()

if (LIBMY_ALLOW_MALLOC_FREE)
    set(SRC
        ${SRCROOT}/my_fread_to_string.c
        ${SRCROOT}/my_getdelim.c
        ${SRC}
    )
endif()

# IDE source group
source_group("" FILES ${SRC})

libmy_add_module(my-io SOURCES ${SRC})

# setup dependencies
if (LIBMY_ALLOW_MALLOC_FREE)
    target_link_libraries(my-io PUBLIC my-ascii my-collections)
else()
    target_link_libraries(my-io PUBLIC my-ascii)
endif()

target_include_directories(my-io PUBLIC "${PROJECT_SOURCE_DIR}/include")
