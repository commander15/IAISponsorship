if (NOT EXISTS ${CMAKE_BINARY_DIR}/data/database.db)
    file(COPY database.db DESTINATION ${CMAKE_BINARY_DIR}/data)
endif()

install(FILES database.db DESTINATION data)
