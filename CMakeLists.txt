cmake_minimum_required(VERSION 3.14)

project(convert-image-application LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Gui Qml Quick)

qt_standard_project_setup(REQUIRES 6.5)

set(CONTROLLER_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/ModuleController/ModuleController.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ModuleController/ModuleController.cpp
)

add_executable(convert-image-application
    ${CONTROLLER_SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/Utility.h
    main.cpp
)

#add include path for giflib and libutil
target_link_directories(convert-image-application PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

add_subdirectory(GuiComponent)
add_subdirectory(WrapperGifLib)

target_link_libraries(convert-image-application
    GuiComponentplugin
    Qt6::Core
    Qt6::Gui
    Qt6::Qml
    WrapperGifLib
)

include(GNUInstallDirs)
install(TARGETS convert-image-application
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
