/*
* ImageContent.qml
* Author: Trung La
* Date: 2024-12-22
*/

import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Item {
    id: root

    implicitWidth: 350
    implicitHeight: 350

    property string imageSource: ""

    Rectangle {
        anchors.fill: parent
        color: "#F5EFE7"
        radius: 4
    }

    ColumnLayout {
        anchors {
            top: parent.top
            left: parent.left
            leftMargin: 2
            right: parent.right
            rightMargin: 2
            bottom: parent.bottom
        }
        spacing: 2

        Rectangle {
            id: imageRect
            Layout.fillWidth: true
            Layout.fillHeight: true
            color: "#F5F5F5"
            radius: 4

            Column {
                anchors.centerIn: parent
                spacing: 8
                visible: !image.source.toString()

                Image {
                    anchors.horizontalCenter: parent.horizontalCenter
                    source: `Resources/add-image.png`
                    width: 48
                    height: 48
                    opacity: 0.5
                }

                Text {
                    text: "Drop image here"
                    color: "#757575"
                    font.pixelSize: 14
                }
            }

            Image {
                id: image
                anchors.fill: parent
                source: root.imageSource
                fillMode: Image.PreserveAspectFit
                asynchronous: true
                cache: false

                BusyIndicator {
                    anchors.centerIn: parent
                    running: image.status === Image.Loading
                }
            }

            DropArea {
                id: dropArea
                anchors.fill: parent
                onDropped: function(drop) {
                    if (drop.hasUrls) {
                        root.imageSource = drop.urls[0]
                        root.imageDropped(drop.urls[0])
                    } else if (drop.hasText) {
                        root.imageSource = drop.text
                        root.imageDropped(drop.text)
                    }
                }
            }
        }

        Rectangle {
            Layout.fillWidth: true
            Layout.preferredHeight: 80
            radius: 4

            RowLayout {
                id: rowButtons
                anchors {
                    left: parent.left
                    verticalCenter: parent.verticalCenter
                }
                width: 122
                height: 60
                spacing: 2

                Repeater {
                    model: featureModel
                    delegate: FeatureButton {
                        opacity: 1
                        iconSource: model.icon
                        iconWidth: 34
                        iconHeight: 34
                    }
                }
            }
            CustomButton {
                id: applyButton
                text: "Apply"
                width: 100
                height: 40
                anchors {
                    right: parent.right
                    rightMargin: 4
                    verticalCenter: parent.verticalCenter
                }
                onClicked: function() {
                    console.log("Apply button clicked")
                }
            }
        }
    }

    ListModel {
        id: featureModel
        ListElement {
            icon: "Resources/file-explorer.png"
        }
        ListElement {
            icon: "Resources/refresh.png"
        }
        ListElement {
            icon: "Resources/delete.png"
        }
    }
}

