if (NOT EXISTS ${Sponsorship_SOURCE_DIR}/translations)
    file(MAKE_DIRECTORY ${Sponsorship_SOURCE_DIR}/translations)
endif()

get_target_property(TS_FILES sponsorship LOCALES)

list(TRANSFORM TS_FILES PREPEND ${Sponsorship_SOURCE_DIR}/translations/sponsorship_)
list(TRANSFORM TS_FILES APPEND  .ts)

qt5_create_translation(QM_FILES ${CMAKE_CURRENT_SOURCE_DIR} ${TS_FILES})

target_sources(sponsorship PRIVATE ${QM_FILES})

install(FILES ${QM_FILES} DESTINATION translations)
