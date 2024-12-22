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
    }
}