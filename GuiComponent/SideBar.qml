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
    property var sideBarModel: null // SideBarModel

    signal featureSelected(QtObject featureModel)

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
                    featureSelected(model);
                }
            }
        }
    }
}
