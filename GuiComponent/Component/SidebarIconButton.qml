/*
    SidebarIconButton
    SidebarIconButton.qml
    Author: Trung La
    Date: 2024-12-21
*/

import QtQuick
import QtQuick.Controls
import Qt5Compat.GraphicalEffects
Rectangle {
    id: sideBarIconButton

    width: 80
    height: 80
    color: "white"
    radius: 4

    property string iconSource: ""
    signal clicked()

    Rectangle {
        id: backgroundRect
        anchors.fill: parent
        color: "white"
        anchors.centerIn: parent
        anchors.margins: 5
        radius: 4

        states: [
            State {
                name: "hovered"
                when: sideBarIconButtonMouseArea.containsMouse
                PropertyChanges {
                    target: backgroundRect
                    color: "#D8C4B6"
                }
            },

            State {
                name: "normal"
                when: !sideBarIconButtonMouseArea.containsMouse
                PropertyChanges {
                    target: backgroundRect
                    color: "white"
                }
            }
        ]
    }

    Image {
        id: sideBarIconButtonImage
        width: 32
        height: 32
        anchors.centerIn: parent
        source: iconSource
        fillMode: Image.PreserveAspectFit
        visible: iconSource !== ""

        states: [
            State {
                name: "hovered"
                when: sideBarIconButtonMouseArea.containsMouse
                StateChangeScript {
                    script: {
                        y += 5
                    }
                }
            },
            State {
                name: "normal"
                when: !sideBarIconButtonMouseArea.containsMouse
                StateChangeScript {
                    script: {
                        y -= 5
                    }
                }
            }
        ]
    }

    ColorOverlay {
        id: sideBarIconButtonColorOverlay
        anchors.fill: sideBarIconButtonImage
        source: sideBarIconButtonImage
        color: "#000000"
        visible: sideBarIconButtonImage.visible

        states: [
            State {
                name: "hovered"
                when: sideBarIconButtonMouseArea.containsMouse
                PropertyChanges {
                    target: sideBarIconButtonColorOverlay
                    color: "#FFFFFF"
                }
            },
            State {
                name: "normal"
                when: !sideBarIconButtonMouseArea.containsMouse
                PropertyChanges {
                    target: sideBarIconButtonColorOverlay
                    color: "#000000"
                }
            }
        ]
    }

    MouseArea {
        id: sideBarIconButtonMouseArea
        anchors.fill: parent
        cursorShape: Qt.PointingHandCursor
        hoverEnabled: true
        onClicked: {
            sideBarIconButton.clicked()
        }
    }
}
