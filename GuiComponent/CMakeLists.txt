qt_add_library(GuiComponent STATIC)

target_link_libraries(GuiComponent PRIVATE
                        Qt6::Quick
                        Qt6::Core5Compat)

set_source_files_properties(MainWindow.qml
    PROPERTIES
    QT_QML_SINGLETON_TYPE true
)

set(components
    Component/CustomButton.qml
    Component/FeatureButton.qml
    Component/SidebarIconButton.qml
    Component/CustomTextField.qml
    Component/RowFeatureButtons.qml
)

foreach(component ${components})
    get_filename_component(component_name ${component} NAME)
    set_source_files_properties(${component} PROPERTIES QT_RESOURCE_ALIAS ${component_name})
endforeach()

qt_add_qml_module(GuiComponent
    URI GuiComponent
    OUTPUT_DIRECTORY GuiComponent
    QML_FILES
        MainWindow.qml
        SideBar.qml
        AspectRatioFeature.qml
        CropFeature.qml
        ImageContent.qml
        Component/CustomButton.qml
        Component/FeatureButton.qml
        Component/SidebarIconButton.qml
        Component/CustomTextField.qml
        Component/RowFeatureButtons.qml
    RESOURCES
        "Resources/crop-sidebar-icon.svg"
        "Resources/crop-sidebar-icon.png"
        "Resources/aspect-ratio.svg"
        "Resources/aspect-ratio.png"
        "Resources/rotate-90-degrees.svg"
        "Resources/rotate-90-degrees.png"
        "Resources/rotate-90-degrees-cw.svg"
        "Resources/rotate-90-degrees-cw.png"
        "Resources/flip-horizontal-left.png"
        "Resources/flip-horizontal-right.png"
        "Resources/refresh.svg"
        "Resources/refresh.png"
        "Resources/delete.svg"
        "Resources/delete.png"
        "Resources/file-explorer.svg"
        "Resources/file-explorer.png"
        "Resources/add-image.svg"
        "Resources/add-image.png"
)
