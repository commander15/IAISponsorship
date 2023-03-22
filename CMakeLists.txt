cmake_minimum_required(VERSION 3.20)

project(Sponsorship
    DESCRIPTION "Sponsorship"
    VERSION     1.0.0
    LANGUAGES   C CXX
)

# Test
option(Sponsorship_BUILD_TEST "Build Sponsorship test" OFF)

# Documentation
option(Sponsorship_BUILD_DOC "Build Sponsorship documentation" OFF)

# Translations
option(Sponsorship_BUILD_TRANSLATIONS "Build Sponsorship translations" OFF)

# Package
set(Sponsorship_COMPONENTS)

include(CMakePackageConfigHelpers)

configure_package_config_file(
    SponsorshipConfig.cmake.in ${CMAKE_BINARY_DIR}/lib/cmake/Sponsorship/SponsorshipConfig.cmake
    INSTALL_DESTINATION lib/cmake/Sponsorship
)

write_basic_package_version_file(
    ${CMAKE_BINARY_DIR}/lib/cmake/Sponsorship/SponsorshipConfigVersion.cmake
    VERSION       ${Sponsorship_VERSION}
    COMPATIBILITY SameMajorVersion
    ARCH_INDEPENDENT
)

# External packages
include(cmake/FindQt5.cmake)
include(cmake/FindCommander.cmake)

# Internal
include(cmake/SponsorshipHelpers.cmake)

# CXX Variables
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# C Variables
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Output locations
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)

add_subdirectory(src)
add_subdirectory(data)

if (Sponsorship_BUILD_TEST)
    add_subdirectory(test)
endif()

if (Sponsorship_BUILD_DOC)
    add_subdirectory(doc)
endif()

add_subdirectory(gen)
add_subdirectory(admin)

# Packaging
sponsorship_export(${Sponsorship_COMPONENTS})

