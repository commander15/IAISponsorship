sponsorship_add_library(sponsorship)

set_target_properties(sponsorship
    PROPERTIES
        DISPLAY_NAME Sponsorship
        VERSION      ${Sponsorship_VERSION}
        SOVERSION    ${Sponsorship_VERSION}
        LOCALES      fr
)

target_include_directories(sponsorship
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_link_libraries(sponsorship PUBLIC Qt5::Sql Qt5::Core)

if (BUILD_SHARED_LIBS)
    set(BUILD_TYPE SHARED)
else()
    set(BUILD_TYPE STATIC)
endif()

target_compile_definitions(sponsorship
    PUBLIC  SPONSORSHIP_${BUILD_TYPE} SPONSORSHIP_LIB
    PRIVATE BUILD_SPONSORSHIP_LIB
)

add_subdirectory(kernel)

if (Sponsorship_BUILD_TRANSLATIONS)
    include(translations.cmake)
endif()

sponsorship_install(TARGETS sponsorship EXPORT SponsorshipExport)

