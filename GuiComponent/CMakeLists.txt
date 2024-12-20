qt_add_library(GuiComponent STATIC)

target_link_libraries(GuiComponent PRIVATE
                        Qt6::Quick)

set_source_files_properties(MainWindow.qml
    PROPERTIES
    QT_QML_SINGLETON_TYPE true
)

qt_add_qml_module(GuiComponent
    URI GuiComponent
    OUTPUT_DIRECTORY GuiComponent
    QML_FILES
        MainWindow.qml
)