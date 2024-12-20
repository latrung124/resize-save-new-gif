qt_add_library(GuiComponent STATIC)

target_link_libraries(GuiComponent PRIVATE
                        Qt6::Quick)

set_source_files_properties(MainWindow.qml
    PROPERTIES
    QT_QML_SINGLETON_TYPE true
)

set(components
    Component/CustomButton.qml
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
        Component/CustomButton.qml
)
