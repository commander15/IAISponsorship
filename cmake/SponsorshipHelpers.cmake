if (WIN32)
    set(CMAKE_STATIC_LIBRARY_PREFIX "")
    set(CMAKE_SHARED_LIBRARY_PREFIX "")
endif()

option(BUILD_SHARED_LIBS "Enable/disable shared build" ON)

function(sponsorship_add_executable name)
    commander_add_executable(${name} ${ARGN})
endfunction()

function(sponsorship_add_library name)
    commander_add_library(${name} ${ARGN})
endfunction()

macro(sponsorship_sources target)
    set_source_files_properties(${HEADERS2} PROPERTIES PRIVATE TRUE)

    target_files(${target} HEADERS ${HEADERS} ${HEADERS2} SOURCES ${SOURCES})

    unset(HEADERS)
    unset(HEADERS2)
    unset(SOURCES)
endmacro()

macro(sponsorship_install type)
    install(${type} ${ARGN})
endmacro()

macro(sponsorship_export)
    foreach (module "" ${ARGN})
        export(
            EXPORT    Sponsorship${module}Export
            NAMESPACE Sponsorship::
            FILE      ${CMAKE_BINARY_DIR}/lib/cmake/Sponsorship/Sponsorship${module}Targets.cmake
        )

        install(
            EXPORT      Sponsorship${module}Export
            NAMESPACE   Sponsorship::
            DESTINATION lib/cmake/Sponsorship
        )
    endforeach()
endmacro()
