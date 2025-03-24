cmake_minimum_required(VERSION 3.16)

project(AstraSpecs VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Qt6 and required components (add Core and Network)
find_package(Qt6 6.5 REQUIRED COMPONENTS Core Quick SerialPort Network)

# Find pkg-config for PostgreSQL (pqxx)
find_package(PkgConfig REQUIRED)
pkg_check_modules(PQXX REQUIRED libpqxx)

# Standard Qt project setup
qt_standard_project_setup(REQUIRES 6.5)

# Define the executable
qt_add_executable(appAstraSpecs
    main.cpp
)

# Define the QML module
qt_add_qml_module(appAstraSpecs
    URI AstraSpecs
    VERSION 1.0
    QML_FILES
        Main.qml
    SOURCES
        network/tcpserver.h network/tcpserver.cpp

        QML_FILES components/TopBar/TopBar.qml
        QML_FILES components/BottomBar/BottomBar.qml
        QML_FILES components/body/body.qml
)

# Set target properties
set_target_properties(appAstraSpecs PROPERTIES
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

# Link libraries to your application
target_include_directories(appAstraSpecs
    PRIVATE ${PQXX_INCLUDE_DIRS}  # Add pqxx include directories
)

target_link_libraries(appAstraSpecs
    PRIVATE Qt6::Core           # Link Core module for basic Qt functionality
            Qt6::Quick          # Link Quick module for QML
            Qt6::SerialPort     # Link SerialPort module
            Qt6::Network        # Link Network module (for QTcpServer)
            pqxx               # Link pqxx library for PostgreSQL support
            ${PQXX_LIBRARIES}   # Add pqxx libraries from pkg-config
)

# Installation settings
include(GNUInstallDirs)
install(TARGETS appAstraSpecs
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
