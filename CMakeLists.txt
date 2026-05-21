cmake_minimum_required(VERSION 3.16)

project(LanChat VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick Network)

qt_standard_project_setup(REQUIRES 6.10)

# Tells the project where to find your header files
include_directories(include)

qt_add_executable(appLanChat
    src/main.cpp
    src/networkmanager.cpp
    include/networkmanager.h
)

qt_add_qml_module(appLanChat
    URI LanChat
    QML_FILES
        ui/Main.qml
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appLanChat PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appLanChat
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appLanChat
    PRIVATE Qt6::Quick Qt6::Network
)

install(TARGETS appLanChat
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
