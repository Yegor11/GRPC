cmake_minimum_required(VERSION 3.14)

project(ClientServer VERSION 0.1 LANGUAGES CXX)

include(./common.cmake)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Quick)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Quick)

file(GLOB_RECURSE GEN_SRC ${PROJECT_SOURCE_DIR}/v1/*.cc ${PROJECT_SOURCE_DIR}/v2/*.cc ${PROJECT_SOURCE_DIR}/google/*.cc)

set(PROJECT_SOURCES
        main.cpp
        qml.qrc
        certificate.h
        client.cpp
        client.h

        model.h
        model.cpp
)

set(SERVER_SOURSES
    server.cpp
    server.h
)

message("${GEN_SRC}")

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable( ClientServer
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        ${GEN_SRC}
    )
qt_add_executable( Server1
    MANUAL_FINALIZATION
    ${SERVER_SOURSES}
    ${GEN_SRC}
)
endif()

target_link_libraries(ClientServer
  PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick ${Protobuf_LIBRARIES} ${_GRPC_GRPCPP} ${_REFLECTION} ${_PROTOBUF_LIBPROTOBUF})
target_link_libraries(Server1
  PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick ${Protobuf_LIBRARIES} ${_GRPC_GRPCPP} ${_REFLECTION} ${_PROTOBUF_LIBPROTOBUF})

set_target_properties(ClientServer PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS ClientServer
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_import_qml_plugins(ClientServer)
    qt_finalize_executable(ClientServer)
endif()
