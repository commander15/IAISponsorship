# Core
set(QT5_MODULES Core Sql)

# Test
if (Sponsorship_BUILD_TESTS)
    list(APPEND QT5_MODULES Test)
endif()

# Apps
list(APPEND QT5_MODULES Widgets Quick)

# Translations
if (Sponsorship_BUILD_TRANSLATIONS)
    list(APPEND QT5_MODULES LinguistTools)
endif()

find_package(Qt5 REQUIRED COMPONENTS ${QT5_MODULES})

# Global variables
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
