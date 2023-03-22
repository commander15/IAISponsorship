set(SOURCES helper.cpp)

sponsorship_add_executable(gen WIN32 ${SOURCES} main.cpp qml.qrc)

target_link_libraries(gen PRIVATE Qt5::Quick sponsorship)
