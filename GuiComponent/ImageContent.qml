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

    Rectangle {
        anchors.fill: parent
        color: "#ffffff"
        radius: 4
    }

    ColumnLayout {
        anchors.fill: parent
        spacing: 2

        Rectangle {
            id: imageRect
            Layout.fillWidth: true
            Layout.fillHeight: true
            border.color: "black"
            border.width: 1
            radius: 4
        }

        Rectangle {
            Layout.fillWidth: true
            Layout.preferredHeight: 80
            border.color: "blue"
            border.width: 1
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
            icon: "Resources/refresh.png"
        }
        ListElement {
            icon: "Resources/delete.png"
        }
    }
}

