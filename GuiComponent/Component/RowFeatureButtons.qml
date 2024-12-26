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

    signal featureTrigger(int index)

    onFeatureTrigger: function(index) {
        model.onTransformTrigger(index);
    }

    implicitHeight: 50
    implicitWidth: 110
    spacing: 10

    Repeater {
        id: repeater
        delegate: FeatureButton {
            iconSource: model.icon
            onClicked: function() {
                root.featureTrigger(index);
            }
        }
    }
}
