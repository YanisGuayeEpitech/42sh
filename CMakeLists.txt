cmake_minimum_required(VERSION 3.0.0)

project(Minishell2 C)

# Specify the C standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

# Unit testing
if (BUILD_TEST_SUITE)
    set(LIBMY_BUILD_TEST_SUITE True)
    enable_testing()
endif()

if (CMAKE_COMPILER_IS_GNUCC)
    # Compile Options
    add_compile_options(
       "-Wall" "-Wextra" "-Wshadow"
       "$<$<CONFIG:RELEASE>:-O3>"
       "$<$<CONFIG:DEBUG>:-O0;-g3;-ggdb>"
    )

    # Enable test coverage
    if (LIBMY_USE_GCOV)
        add_link_options("-lgcov" "--coverage")
        add_compile_options("--coverage" "-fprofile-arcs" "-ftest-coverage")
    endif()
endif()

# LibMy dependency
set(BUILD_SHARED_LIBS FALSE)
set(LIBMY_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/lib/my/include")
set(LIBMY_MODULES
    ascii
    collections
    hash
    io
    memory
    parsing
    printf
)
set(LIBMY_ALLOWED_FUNCTIONS
    malloc_free
    open
    read
    write
    close
)
add_subdirectory(lib/my)

add_subdirectory(src)
