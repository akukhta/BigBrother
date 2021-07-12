cmake_minimum_required(VERSION 3.5)

project(BigBrother VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check https://doc.qt.io/qt/deployment-android.html for more information.
# They need to be set before the find_package( ...) calls below.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

if (UNIX AND NOT APPLE)

    set(PROJECT_SOURCES
            main.cpp
            mainwindow.cpp
            mainwindow.h
            mainwindow.ui
            packettable.h
            packettable.cpp
            analyzer.h
            analyzer.cpp
            networklistener.h
            networklistenerlin.h
            networklistenerlin.cpp
            networklistenerfactory.h
            lindeviceswidges.ui
            lindeviceswidges.h
            lindeviceswidges.cpp
            linuxnetworkdevice.h
            linuxnetworkdevice.cpp
            linuxdevicesmanager.h
            linuxdevicesmanager.cpp
        )
endif(UNIX)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(BigBrother
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(BigBrother SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(BigBrother
            ${PROJECT_SOURCES})
    endif()
endif()

target_link_libraries(BigBrother PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(BigBrother PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(BigBrother)
endif()
