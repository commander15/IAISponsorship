set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(SOURCES adminwindow.cpp studenteditdialog.cpp)

sponsorship_add_executable(admin main.cpp ${SOURCES})

target_link_libraries(admin PRIVATE Qt5::Widgets sponsorship)
