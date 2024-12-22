/*
    RowFeatureButtons.qml
    Author: Trung La
    Date: 2024-12-21
*/

import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

RowLayout {
    id: root

    property alias model: repeater.model

    implicitHeight: 50
    implicitWidth: 110
    spacing: 10

    Repeater {
        id: repeater
        delegate: FeatureButton {
            iconSource: model.icon
        }
    }
}