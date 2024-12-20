/*
* MainWindow.qml
* Author: trung.la
* Date: 2024-12-20
*/

pragma Singleton

import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ApplicationWindow {
    id: root

    visible: true
    width: 780
    height: 480

    title: qsTr("Convert Image Tool")

    RowLayout {
        id: rowLayout
        
        anchors.fill: parent
        spacing: 10

        Rectangle {
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.margins: 10
            border.color: "black"
            border.width: 1
            radius: 4

            CustomButton {
                id: importImageButton
                text: qsTr("Import Image")
                width: 100
                height: 30
                anchors.centerIn: parent
            }
        }

        Rectangle {
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.margins: 10
            border.color: "blue"
            border.width: 1
            radius: 4
        }
    }
}
