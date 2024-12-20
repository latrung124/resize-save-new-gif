// CustomButton.qml
import QtQuick
import QtQuick.Controls

Button {
    id: customButton
    text: "Button 27"

    // Custom properties
    property int animationDuration: 300

    // Main button layout
    implicitWidth: parent.width
    implicitHeight: 60

    background: Rectangle {
        id: buttonBackground
        color: customButton.enabled ? "#000000" : "#666666"  // Darker when disabled
        border.width: 2
        border.color: "#1A1A1A"
        radius: 15
    }

    contentItem: Text {
        text: customButton.text
        font.family: "Segoe UI"
        font.pixelSize: 16
        font.weight: Font.DemiBold
        color: "#FFFFFF"
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        elide: Text.ElideRight
    }

    // Transitions and behaviors
    Behavior on y {
        NumberAnimation {
            duration: customButton.animationDuration
            easing.type: Easing.Bezier
            easing.bezierCurve: [0.23, 1, 0.32, 1, 1]
        }
    }

    // States for different button conditions
    states: [
        State {
            name: "hovered"
            when: customButton.hovered && !customButton.pressed
            PropertyChanges {
                target: customButton
                y: y - 2  // Move up when hovered
            }
        }
    ]

    // Mouse area to handle pointer events
    MouseArea {
        anchors.fill: parent
        cursorShape: Qt.PointingHandCursor
        onPressed: mouse.accepted = false  // Let the Button handle the event
    }
}
