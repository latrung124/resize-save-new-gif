/*
    Aspect Ratio Feature
    AspectRatioFeature.qml
    Author: Trung La
    Date: 2024-12-21
    This is a feature that allows the user to change the aspect ratio of the image.
*/

import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Item {
    id: root

    width: 350
    height: 350

    Rectangle {
        id: backgroundRect
        anchors.fill: parent
        color: "#3E5879"
        radius: 4
    }

    Item {
        id: contentItem

        width: parent.width
        height: 350

        ColumnLayout {
            anchors.fill: parent
            spacing: 0

            Item {
                id: titleItem
                Layout.fillWidth: true
                height: 50

                Text {
                    text: "Aspect Ratio"
                    anchors.left: parent.left
                    anchors.leftMargin: 20
                    anchors.verticalCenter: parent.verticalCenter
                    font.pixelSize: 22
                    font.weight: Font.Bold
                    color: "black"
                }
            }

            Item {
                id: aspectRatioItem
                Layout.fillWidth: true
                height: 100

                Text {
                    id: resizeText
                    text: "Resize"
                    anchors.left: parent.left
                    anchors.leftMargin: 20
                    anchors.verticalCenter: parent.verticalCenter
                    font.pixelSize: 18
                    font.weight: Font.Bold
                    color: "black"
                }

                RowLayout {
                    anchors {
                        left: parent.left
                        leftMargin: 20
                        right: parent.right
                        rightMargin: 20
                        top: resizeText.bottom
                        topMargin: 5
                        bottom: parent.bottom
                        bottomMargin: 5
                    }
                    spacing: 10

                    CustomTextField {
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        placeholderText: "Width"
                    }
                    CustomTextField {
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        placeholderText: "Height"
                    }
                }
            }

            Rectangle {
                Layout.fillWidth: true
                height: 1
                color: "#F5EFE7"
            }

            Item {
                id: rotateItem
                Layout.fillWidth: true
                Layout.preferredHeight: 99

                Text {
                    text: "Rotate"
                    anchors.left: parent.left
                    anchors.leftMargin: 20
                    anchors.verticalCenter: parent.verticalCenter
                    font.pixelSize: 18
                    font.weight: Font.Bold
                    color: "black"
                }
            }

            Rectangle {
                Layout.fillWidth: true
                height: 1
                color: "#F5EFE7"
            }

            Item {
                id: flipItem
                Layout.fillWidth: true
                Layout.preferredHeight: 99

                Text {
                    text: "Flip"
                    anchors.left: parent.left
                    anchors.leftMargin: 20
                    anchors.verticalCenter: parent.verticalCenter
                    font.pixelSize: 18
                    font.weight: Font.Bold
                    color: "black"
                }
            }
        }
    }
}