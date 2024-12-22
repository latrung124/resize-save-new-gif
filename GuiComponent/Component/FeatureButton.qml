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
        onClicked: root.clicked()
    }

    states: [
        State {
            name: "hovered"
            when: mouseArea.containsMouse
            PropertyChanges {
                target: colorOverlay
                color: "white"
            }

            PropertyChanges {
                target: backgroundRect
                color: "#D8C4B6"
            }

            StateChangeScript {
                script: {
                    y -= 4;
                }
            }
        },
        State {
            name: "normal"
            when: !mouseArea.containsMouse
            PropertyChanges {
                target: colorOverlay
                color: "black"
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
