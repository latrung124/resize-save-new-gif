cmake_minimum_required(VERSION 3.14)

project(convert-image-application LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Gui Qml Quick Core5Compat)

qt_standard_project_setup(REQUIRES 6.5)

set(CONTROLLER_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/Controller/ModuleController.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Controller/ModuleController.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Controller/FeatureController.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Controller/FeatureController.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Controller/ActionController.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Controller/ActionController.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Controller/ExportController.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Controller/ExportController.cpp
)

set(MODEL_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/Model/BottomBarModel.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Model/BottomBarModel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Model/SideBarModel.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Model/SideBarModel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Model/Action/AbstractAction.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Model/Action/FileExplorerAction.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Model/Action/FileExplorerAction.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Model/Action/RefreshAction.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Model/Action/RefreshAction.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Model/Action/DeleteAction.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Model/Action/DeleteAction.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Model/Action/AbstractActionModel.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Model/Action/AbstractActionModel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Model/Action/FileExplorerActionModel.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Model/Action/FileExplorerActionModel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Model/Action/RefreshActionModel.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Model/Action/RefreshActionModel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Model/Action/DeleteActionModel.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Model/Action/DeleteActionModel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Model/Feature/DetailAspectRatioFeatureModel.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Model/Feature/DetailAspectRatioFeatureModel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Model/Feature/DetailCropFeatureModel.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Model/Feature/DetailCropFeatureModel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Model/Feature/AbstractFeatureModel.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Model/Feature/AbstractFeatureModel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Model/Feature/AspectRatioFeatureModel.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Model/Feature/AspectRatioFeatureModel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Model/Feature/CropFeatureModel.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Model/Feature/CropFeatureModel.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/Model/Transform/AbstractTransformModel.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Model/Transform/AbstractTransformModel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Model/Transform/FlipTransformModel.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Model/Transform/FlipTransformModel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Model/Transform/RotationTransformModel.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Model/Transform/RotationTransformModel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Model/Transform/FlipTransformListModel.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Model/Transform/FlipTransformListModel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Model/Transform/RotationTransformListModel.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Model/Transform/RotationTransformListModel.cpp
)

set(UTILITY_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/Utility/ActionTypeClass.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Utility/FeatureTypeClass.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Utility/TransformTypeClass.h
)

add_executable(convert-image-application
    ${UTILITY_SOURCES}
    ${CONTROLLER_SOURCES}
    ${MODEL_SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/Utility.h
    main.cpp
)

#add include path for giflib and libutil
target_include_directories(convert-image-application PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/Controller
    ${CMAKE_CURRENT_SOURCE_DIR}/Model
    ${CMAKE_CURRENT_SOURCE_DIR}/Model/Action
    ${CMAKE_CURRENT_SOURCE_DIR}/Model/Feature
    ${CMAKE_CURRENT_SOURCE_DIR}/Model/Transform
    ${CMAKE_CURRENT_SOURCE_DIR}/Utility
    ${CMAKE_CURRENT_SOURCE_DIR}/WrapperGifLib
)

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
