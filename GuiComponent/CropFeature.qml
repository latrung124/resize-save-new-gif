/*
    Crop Feature
    CropFeature.qml
    Author: Trung La
    Date: 2024-12-22
    This is a feature that allows the user to crop the image.
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
        color: internal.backgroundColor
        radius: 4
    }

    Item {
        id: contentItem

        width: parent.width
        height: 350

        ColumnLayout {
            id: contentLayout
            anchors.fill: parent
            spacing: 0

            Item {
                id: titleItem
                Layout.fillWidth: true
                height: internal.featureRowHeight
                Layout.alignment: Qt.AlignTop

                Text {
                    text: "Crop"
                    anchors.left: parent.left
                    anchors.leftMargin: internal.featureRowLeftMargin
                    anchors.verticalCenter: parent.verticalCenter
                    font.pixelSize: 22
                    font.weight: Font.Bold
                    font.family: "Helvetica"
                    color: internal.textColor
                }
            }
        }
    }

    QtObject {
        id: internal

        property color backgroundColor: "transparent"
        property int featureRowWidth: 110
        property int featureRowHeight: 50
        property int featureRowSpacing: 10
        property int featureRowTopMargin: 5
        property int featureRowLeftMargin: 20
        property int borderLineHeight: 1
    }
}