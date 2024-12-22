/*
* CustomButton.qml
* Author: Trung La
* Date: 2024-12-22
*/
import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Basic

Item {
    id: root
    property int animationDuration: 300

    property alias text: buttonText.text

    implicitWidth: parent.width
    implicitHeight: 60

    signal clicked()

    Rectangle {
        id: buttonBackground
        anchors.fill: parent
        color: "#000000"
        border.width: 2
        border.color: "#1A1A1A"
        radius: 15
        states: [
            State {
                name: "hovered"
                when: mouseArea.containsMouse
                PropertyChanges { target: buttonBackground; opacity: 0.8 }
            },
            State {
                name: "normal"
                when: !mouseArea.containMouse
                PropertyChanges { target: buttonBackground; opacity: 1 }
            }
        ]
    }

    Text {
        id: buttonText
        text: root.text
        font.family: "Helvetica"
        font.pixelSize: 16
        font.weight: Font.DemiBold
        color: "#FFFFFF"
        anchors.centerIn: parent
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        elide: Text.ElideRight
    }

    Behavior on y {
        NumberAnimation {
            duration: root.animationDuration
            easing.type: Easing.Bezier
            easing.bezierCurve: [0.23, 1, 0.32, 1, 1]
        }
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        cursorShape: Qt.PointingHandCursor
        hoverEnabled: true
        onClicked: function() {
            root.clicked()
        }
    }
}
