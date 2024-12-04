cmake_minimum_required(VERSION 3.14)

project(convert-image-console LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Gui)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Gui)

add_executable(convert-image-console
  main.cpp
  qgiflibhandler.h
  qgiflibhandler.cpp
  gifhandler.h
  gifhandler.cpp
)

#add include path for giflib and libutil
target_include_directories(convert-image-console PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/giflib-5.2.2
)

target_link_directories(convert-image-console PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(convert-image-console
    libgif
    libutil
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Gui)

include(GNUInstallDirs)
install(TARGETS convert-image-console
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
