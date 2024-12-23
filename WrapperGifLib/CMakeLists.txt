find_library(GIFLIB
    NAMES libgif gif
    PATHS ${CMAKE_CURRENT_SOURCE_DIR}/giflib-5.2.2/lib
    NO_DEFAULT_PATH
)

find_library(GIFUTIL
    NAMES libutil util
    PATHS ${CMAKE_CURRENT_SOURCE_DIR}/giflib-5.2.2/lib
    NO_DEFAULT_PATH
)

if(NOT GIFLIB)
    message(FATAL_ERROR "libgif library not found")
endif()

add_library(WrapperGifLib STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/IGifConverter.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Implementation/GifConverterImpl.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Implementation/GifConverterImpl.cpp
)

target_link_directories(WrapperGifLib PRIVATE
    ${CMAKE_SOURCE_DIR}/giflib-5.2.2
)

target_include_directories(WrapperGifLib PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/giflib-5.2.2
)

target_link_libraries(WrapperGifLib PRIVATE
    ${GIFLIB}
    ${GIFUTIL}
    Qt6::Core
    Qt6::Gui
)
