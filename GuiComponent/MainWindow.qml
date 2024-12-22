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

    objectName: "mainWindow"
    visible: true
    width: 1366
    height: 780

    title: qsTr("Convert Image Tool")
    color: "white"

    Component.onCompleted: function() {
        x = (screen.width - width) / 2;
        y = (screen.height - height) / 2;
    }

    Rectangle {
        id: backgroundRect
        anchors.fill: parent
        color: "#F5EFE7"
    }

    Rectangle {
        id: titleBar
        anchors {
            top: parent.top
            left: parent.left
            right: parent.right
        }
        height: 100
        color: "white"

        Text {
            id: titleText
            anchors {
                left: parent.left
                leftMargin: 20
                verticalCenter: parent.verticalCenter
            }
            text: "Image Tool"
            font.pixelSize: 24
            font.weight: Font.Bold
            font.family: "Helvetica"
            color: "#333333"
        }
    }

    Rectangle {
        id: sideBarRect
        anchors {
            top: titleBar.bottom
            topMargin: 2
            left: parent.left
            bottom: parent.bottom
        }
        width: 80
        color: "white"
        radius: 4

        SideBar {
            id: sideBar
            objectName: "sideBar"
            anchors {
                top: parent.top
                left: parent.left
            }
            onFeatureSelected: function(source) {
                featureLoader.source = source
            }
        }
    }

    Rectangle {
        id: sideButtonContentRect
        anchors {
            top: titleBar.bottom
            topMargin: 2
            left: sideBarRect.right
            right: parent.right
            bottom: parent.bottom
            leftMargin: 2
        }
        color: "white"
        radius: 4

        Item {
            id: sideButtonFeatureIt
            anchors {
                top: parent.top
                bottom: parent.bottom
                left: parent.left
            }
            width: 350

            Loader {
                id: featureLoader
                anchors.fill: parent
                source: ""
            }
        }

        ImageContent {
            id: imageContent
            anchors {
                top: parent.top
                bottom: parent.bottom
                left: sideButtonFeatureIt.right
                right: parent.right
                leftMargin: 2
                rightMargin: 2
            }
        }
    }
}
