/*
* ImageContent.qml
* Author: Trung La
* Date: 2024-12-22
*/

import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Dialogs
import App.Enums 1.0

Item {
    id: root

    implicitWidth: 350
    implicitHeight: 350

    property string imageSource: ""
    property QtObject imageModel: null
    property var bottomBarModel: null

    onImageModelChanged: function() {
        image.model = imageModel;
    }

    Rectangle {
        anchors.fill: parent
        color: "#F5EFE7"
        radius: 4
    }

    FileDialog {
        id: importFileDialog
        title: "Please choose an image"
        currentFolder: StandardPaths.standardLocations(StandardPaths.PicturesLocation)[0]
        nameFilters: ["All files (*.png *.jpg *.jpeg *.gif *.bmp)", "*.png", "*.jpg", "*.jpeg", "*.gif", "*.bmp"]
        onAccepted: function() {
            console.log("Accepted: " + importFileDialog.currentFile);
            if (imageModel) {
                imageModel.imageSource = importFileDialog.currentFile;
            }
        }
    }

    FileDialog {
        id: exportFileDialog
        title: "Please choose a folder to export"
        currentFolder: StandardPaths.standardLocations(StandardPaths.PicturesLocation)[0]
        fileMode: FileDialog.SaveFile
        onAccepted: function() {
            console.log("Accepted: " + exportFileDialog.currentFile);
            if (imageModel && imageModel.imageSource === "") {
                return;
            }
            exportController.exportGif(imageModel, exportFileDialog.currentFile);
        }
    }

    ColumnLayout {
        anchors {
            top: parent.top
            left: parent.left
            leftMargin: 2
            right: parent.right
            rightMargin: 2
            bottom: parent.bottom
        }
        spacing: 2

        Rectangle {
            id: imageRect
            Layout.fillWidth: true
            Layout.fillHeight: true
            color: "#F5F5F5"
            radius: 4

            Column {
                anchors.centerIn: parent
                spacing: 8
                visible: !image.source.toString()

                Image {
                    Layout.alignment: Qt.AlignHCenter
                    source: `Resources/add-image.png`
                    width: 48
                    height: 48
                    opacity: 0.5
                }

                Text {
                    text: "Drop image here"
                    color: "#757575"
                    font.pixelSize: 14
                }
            }

            CustomAnimatedImage {
                id: image
                anchors.fill: parent
                source: imageModel ? imageModel.imageSource : ""
                model: root.imageModel
            }

            DropArea {
                id: dropArea
                anchors.fill: parent
                onDropped: function(drop) {
                    if (drop.hasUrls) {
                        imageModel.imageSource = drop.urls[0]
                        root.imageDropped(drop.urls[0])
                    } else if (drop.hasText) {
                        imageModel.imageSource = drop.text
                        root.imageDropped(drop.text)
                    }
                }
            }
        }

        Rectangle {
            Layout.fillWidth: true
            Layout.preferredHeight: 80
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
                    model: bottomBarModel
                    delegate: FeatureButton {
                        opacity: 1
                        iconSource: model.icon
                        iconWidth: 34
                        iconHeight: 34
                        onClicked: function() {
                            if (!model.action) {
                                return;
                            }

                            if (model.action.actionType() === ActionType.FileExplorer) {
                                internal.importFileDialogOpen();
                            } else if (model.action.actionType() === ActionType.Delete) {
                                internal.deleteImage();
                            } else if (model.action.actionType() === ActionType.Refresh) {
                                internal.refreshImage();
                            } else {
                                console.log("Unknown action");
                            }

                            model.action.execute();
                        }
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
                    console.log("Apply button clicked");
                    internal.exportFileDialogOpen();
                }
            }
        }
    }

    QtObject {
        id: internal

        function importFileDialogOpen() {
            importFileDialog.open()
        }

        function exportFileDialogOpen() {
            exportFileDialog.open();
        }

        function refreshImage() {
            imageModel.imageSource = imageModel.imageSource;
        }

        function deleteImage() {
            imageModel.imageSource = "";
        }
    }
}

