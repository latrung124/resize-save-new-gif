add_library(WrapperGifLib STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/IGifConverter.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Implementation/GifConverterImpl.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Implementation/GifConverterImpl.cpp
)

target_include_directories(WrapperGifLib PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/giflib-5.2.2
)

target_link_libraries(WrapperGifLib PRIVATE
    libgif
    libutil
    Qt6::Core
    Qt6::Gui
)