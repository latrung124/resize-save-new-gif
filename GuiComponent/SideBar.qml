import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {
    id: root

    width: 80
    height: 160
    color: "white"
    radius: 4

    property int selectedIndex: -1

    signal featureSelected(string source)

    ColumnLayout {
        anchors.fill: parent
        spacing: 0

        Repeater {
            model: sideBarModel
            delegate: SidebarIconButton {
                id: sideBarIconButton

                isSelected: root.selectedIndex === index
                iconSource: model.icon
                onClicked: function() {
                    root.selectedIndex = index;
                    featureSelected(model.source);
                }
            }
        }
    }

    ListModel {
        id: sideBarModel
        ListElement {
            icon: `Resources/aspect-ratio.png`
            source: `AspectRatioFeature.qml`
        }
        ListElement {
            icon: `Resources/crop-sidebar-icon.png`
            source: `CropFeature.qml`
        }
    }
}