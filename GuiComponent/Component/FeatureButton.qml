/*
* FeatureButton.qml
* Author: trung.la
* Date: 2024-12-21
*/

import QtQuick
import QtQuick.Controls
import Qt5Compat.GraphicalEffects

Item {
    id: root

    width: 50
    height: 50

    property string iconSource: ""
    property alias iconWidth: iconImage.width
    property alias iconHeight: iconImage.height

    opacity: 0.8
    signal clicked()

    Rectangle {
        id: backgroundRect
        anchors.fill: parent
        color: "transparent"
        anchors.centerIn: parent
        anchors.margins: 5
        radius: 4
    }

    Image {
        id: iconImage
        width: 20
        height: 20
        source: iconSource
        fillMode: Image.PreserveAspectFit
        anchors.centerIn: parent
        smooth: true
        antialiasing: true
    }

    ColorOverlay {
        id: colorOverlay
        anchors.fill: iconImage
        source: iconImage
        color: "black"
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        hoverEnabled: true
        onClicked: function() {
            root.clicked()
        }
    }

    states: [
        State {
            name: "hovered"
            when: !mouseArea.pressed && mouseArea.containsMouse
            PropertyChanges {
                target: colorOverlay
                color: "white"
            }

            PropertyChanges {
                target: backgroundRect
                color: "#2A3335"
            }

            StateChangeScript {
                script: {
                    y = 0;
                    y -= 4;
                }
            }
        },
        State {
            name: "pressed"
            when: mouseArea.pressed && mouseArea.containsMouse
            PropertyChanges {
                target: colorOverlay
                color: "white"
            }

            PropertyChanges {
                target: backgroundRect
                color: "#51595c"
            }
        },
        State {
            name: "normal"
            when: !mouseArea.containsMouse && !mouseArea.pressed
            PropertyChanges {
                target: colorOverlay
                color: "#000000"
            }

            PropertyChanges {
                target: backgroundRect
                color: "transparent"
            }

            StateChangeScript {
                script: {
                    y = 0;
                }
            }
        }
    ]
}
