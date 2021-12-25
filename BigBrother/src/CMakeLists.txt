cmake_minimum_required(VERSION 3.5)

project(BigBrother VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
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
            Net/AbstractPacket.h
            Common/main.cpp
            GUI/mainwindow.cpp
            GUI/mainwindow.h
            GUI/mainwindow.ui
            Common/packettable.h
            Common/packettable.cpp
            Common/analyzer.h
            Common/analyzer.cpp
            Net/networklistener.h
            Linux/networklistenerlin.h
            Linux/networklistenerlin.cpp
            Net/networklistenerfactory.h
            GUI/lindeviceswidges.ui
            GUI/lindeviceswidges.h
            GUI/lindeviceswidges.cpp
            Net/networkdevice.h
            Net/networkdevice.cpp
            Linux/linuxdevicesmanager.h
            Linux/linuxdevicesmanager.cpp
            Net/networkdevicefactory.cpp
            Net/EthernetHeader.h
            Net/EthernetIIHeader.h
            Net/ProtocolHeader.h
            Net/IPv4Header.h
            Net/TransportHeader.h
            Net/TCPHeader.h
            Net/UDPHeader.h
            Net/IPv6Header.h
            Common/packethandler.h
            Common/packethandler.cpp
            Common/utiles.h
            printerchooserwidget.h
            printerchooserwidget.cpp
            printerchooserwidget.ui
            GUI/terminal.h
            GUI/terminal.cpp
            GUI/terminal.ui
            GUI/viewsettingsdialog.h
            GUI/viewsettingsdialog.cpp
            GUI/viewsettingsdialog.ui
            GUI/packetviewer.ui
            GUI/packetviewer.h
            GUI/packetviewer.cpp
            GUI/memoryusagedialog.ui
            GUI/memoryusagedialog.h
            GUI/memoryusagedialog.cpp
            Common/outputmanager.h
            Common/outputmanager.cpp
            Common/littleendianparser.h
            Common/StringUtiles.h
            Common/ViewSettings.h
            Common/settings.cpp
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

target_link_libraries(BigBrother PRIVATE Qt${QT_VERSION_MAJOR}::Widgets pthread boost_unit_test_framework)

set_target_properties(BigBrother PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(BigBrother)
endif()
