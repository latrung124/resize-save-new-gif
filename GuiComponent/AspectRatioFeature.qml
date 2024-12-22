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

    property var aspectRatioFeatureModel: null
    property var rotateFeatureModel: null
    property var flipFeatureModel: null
    signal updateTransformListModel(QtObject aspectRatioFeatureModel)

    onUpdateTransformListModel: function(aspectRatioFeatureModel) {
        console.log("updateTransformListModel")
        rotateFeatureModel = aspectRatioFeatureModel.rotationTransformListModel
        flipFeatureModel = aspectRatioFeatureModel.flipTransformListModel
    }

    Rectangle {
        id: backgroundRect
        anchors.fill: parent
        color: internal.backgroundColor
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
                height: internal.featureRowHeight

                Text {
                    text: "Aspect Ratio"
                    anchors.left: parent.left
                    anchors.leftMargin: internal.featureRowLeftMargin
                    anchors.verticalCenter: parent.verticalCenter
                    font.pixelSize: 22
                    font.weight: Font.Bold
                    font.family: "Helvetica"
                    color: internal.textColor
                }
            }

            Item {
                id: aspectRatioItem
                Layout.fillWidth: true
                height: 100

                Text {
                    id: resizeText
                    text: qsTr("Resize")
                    anchors {
                        left: parent.left
                        leftMargin: internal.featureRowLeftMargin
                        top: parent.top
                        topMargin: internal.featureRowTopMargin
                    }
                    font {
                        pixelSize: 18
                        weight: Font.Bold
                        family: "Helvetica"
                    }
                    color: internal.textColor
                }

                RowLayout {
                    anchors {
                        left: parent.left
                        leftMargin: internal.featureRowLeftMargin
                        right: parent.right
                        rightMargin: 20
                        top: resizeText.bottom
                        topMargin: 15
                        bottom: parent.bottom
                        bottomMargin: 15
                    }
                    spacing: internal.featureRowSpacing

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
                height: internal.borderLineHeight
                color: internal.borderColor
            }

            Item {
                id: rotateItem
                Layout.fillWidth: true
                Layout.preferredHeight: 99

                Text {
                    id: rotateText
                    text: qsTr("Rotate")
                    anchors {
                        left: parent.left
                        leftMargin: internal.featureRowLeftMargin
                        top: parent.top
                        topMargin: internal.featureRowTopMargin
                    }
                    font {
                        pixelSize: 18
                        weight: Font.Bold
                        family: "Helvetica"
                    }
                    color: internal.textColor
                }

                RowFeatureButtons {
                    id: rotateFeatureButtons
                    model: rotateFeatureModel
                    width: internal.featureRowWidth
                    height: internal.featureRowHeight
                    anchors {
                        left: parent.left
                        leftMargin: internal.featureRowLeftMargin
                        top: rotateText.bottom
                        topMargin: internal.featureRowTopMargin
                    }
                }
            }

            Rectangle {
                Layout.fillWidth: true
                height: 1
                color: internal.borderColor
            }

            Item {
                id: flipItem
                Layout.fillWidth: true
                Layout.preferredHeight: 99

                Text {
                    id: flipText
                    text: qsTr("Flip")
                    anchors {
                        left: parent.left
                        leftMargin: 20
                        top: parent.top
                        topMargin: internal.featureRowTopMargin
                    }
                    font {
                        pixelSize: 18
                        weight: Font.Bold
                        family: "Helvetica"
                    }
                    color: internal.textColor
                }

                RowFeatureButtons {
                    id: flipFeatureButtons
                    model: flipFeatureModel
                    width: internal.featureRowWidth
                    height: internal.featureRowHeight
                    anchors {
                        left: parent.left
                        leftMargin: internal.featureRowLeftMargin
                        top: flipText.bottom
                        topMargin: internal.featureRowTopMargin
                    }
                }
            }
        }
    }

    QtObject {
        id: internal

        property color textColor: "black"
        property color backgroundColor: "transparent"
        property color borderColor: "#F5EFE7"

        property int featureRowWidth: 110
        property int featureRowHeight: 50
        property int featureRowSpacing: 10
        property int featureRowTopMargin: 5
        property int featureRowLeftMargin: 20
        property int borderLineHeight: 1
    }
}