configure_file(Doxyfile.in Doxyfile)

find_package(Doxygen REQUIRED)

find_program(qhelpgenerator qhelpgenerator REQUIRED)

add_custom_target(sponsorship_doc ALL
    Doxygen::doxygen  Doxyfile
    SOURCES           Doxyfile.in
)

add_dependencies(sponsorship_doc sponsorship)

install(DIRECTORY ${CMAKE_BINARY_DIR}/doc/Sponsorship DESTINATION doc)
