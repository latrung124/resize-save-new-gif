/*
    Custom text field component
    CustomTextField.qml
    Author: Trung La
    Date: 2024-12-21
*/

import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Basic

TextField {
    id: root

    property int limitedSize: 700
    width: 150
    placeholderText: "Only numbers"
    font.pointSize: 12

    background: Rectangle {
        color: "white"
        border.color: "black"
        radius: 4
    }

    validator: IntValidator {
        bottom: 0 // Set a minimum value if needed
        top: limitedSize // Set a maximum value if needed
    }
}


