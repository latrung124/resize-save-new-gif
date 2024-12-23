/*
    RowFeatureButtons.qml
    Author: Trung La
    Date: 2024-12-21
*/

import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import App.Enums 1.0

RowLayout {
    id: root

    property alias model: repeater.model

    signal transformTrigger(string name)

    implicitHeight: 50
    implicitWidth: 110
    spacing: 10

    Repeater {
        id: repeater
        delegate: FeatureButton {
            iconSource: model.icon
            onClicked: function() {
                console.log("Transform feature button clicked! " + model.name + " type: " + model.transformType);
                transformTrigger(model.name);
            }
        }
    }
}