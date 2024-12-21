import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {
    id: sideBar

    width: 80
    height: 160

    color: "white"
    radius: 4

    ColumnLayout {
        anchors.fill: parent
        spacing: 0

        Repeater {
            model: 2
            delegate: SidebarIconButton {
                iconSource: `Resources/crop-sidebar-icon.png`
            }
        }
    }
}