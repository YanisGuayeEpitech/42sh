find_package(Doxygen REQUIRED)

# set the input and output documentation paths
set(DOXYGEN_INPUT_DIR ${PROJECT_SOURCE_DIR})
set(DOXYGEN_OUTPUT_DIR ${PROJECT_SOURCE_DIR}/doc)


# configure the source Doxyfile by copying it and replacing all @variables@
set(DOXYGEN_CONFIGURED_INPUT ${DOXYGEN_OUTPUT_DIR}/Doxyfile)
configure_file(${DOXYGEN_INPUT_DIR}/doc/Doxyfile.in ${DOXYGEN_CONFIGURED_INPUT} @ONLY)

# target setup
add_custom_target(doc ALL
    COMMAND ${CMAKE_COMMAND} -E echo_append "Building API Documentation..."
    COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_CONFIGURED_INPUT}
    COMMAND ${CMAKE_COMMAND} -E echo "Done."
    WORKING_DIRECTORY ${DOXYGEN_INPUT_DIR}
)

# Prevent this target from being built by default
set_target_properties(doc PROPERTIES EXCLUDE_FROM_ALL TRUE)
