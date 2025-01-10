/*
    CustomAnimatedImage.qml
*/

import QtQuick
import QtQuick.Controls

Item {
    id: root

    property string source: ""
    property QtObject model: null

    width: 350
    height: 350

    onSourceChanged: function() {
        if (root.source === "") {
            return;
        }

        internal.handleImageExtension(root.source);
    }

    Image {
        id: image

        visible: image.source !== ""
        width: parent.width
        height: parent.height
        anchors.centerIn: parent
        source: internal.imageSource
        fillMode: Image.PreserveAspectFit
        asynchronous: true
        cache: false
        rotation: model ? model.rotationAngle : 0
        transform: Scale {
            id: imageScale
            xScale: 1
            origin.x: image.width / 2
        }

        onStatusChanged: function(status) {
            if (status === Image.Ready) {
                console.log("Image loaded");
            }
        }

        BusyIndicator {
            anchors.centerIn: parent
            running: image.status === Image.Loading
        }
    }

    Rectangle {
        id: gifRect

        visible: animatedImage.source !== ""
        width: animatedImage.width
        height: animatedImage.height
        anchors.centerIn: parent
        color: "transparent"

        AnimatedImage {
            id: animatedImage

            source: internal.animatedImageSource
            asynchronous: true
            cache: false
            rotation: model ? model.rotationAngle : 0
            transform: Scale {
                id: animatedImageScale
                xScale: model ? model.flipType : 1
                origin.x: animatedImage.width / 2
            }

            BusyIndicator {
                anchors.centerIn: parent
                running: animatedImage.status === AnimatedImage.Loading
            }

            onStatusChanged: function(status) {
                if (status === AnimatedImage.Ready) {
                    widthBinding.target = animatedImage;
                    heightBinding.target = animatedImage;
                }
            }

            Binding {
                id: widthBinding
                target: null
                property: "width"
                value: model ? model.width : 0
            }

            Binding {
                id: heightBinding
                target: null
                property: "height"
                value: model ? model.height : 0
            }
        }

        Item {
            id: frameIndicator

            property int frames: animatedImage.frameCount

            visible: internal.animatedImageSource !== ""
            width: 50
            height: 50
            x: gifRect.width - width
            y: 0

            Text {
                visible: parent.visible
                font.pixelSize: 14
                text: animatedImage.currentFrame + "/" + frameIndicator.frames
                color: "white"
                anchors.centerIn: parent
            }
        }
    }

    QtObject {
        id: internal

        property string imageSource: ""
        property string animatedImageSource: ""

        function handleImageExtension(sourceFile) {
            console.log("handleImageExtension: sourceFile: ", sourceFile);
            var extension = sourceFile.split(".").pop();
            if (extension === "png" || extension === "jpg" || extension === "jpeg" || extension === "bmp") {
                internal.imageSource = sourceFile;
                internal.animatedImageSource = "";
            } else if (extension === "gif") {
                internal.animatedImageSource = source;
                internal.imageSource = "";
            } else {
                console.log("Unsupported image extension: ", extension);
            }
        }
    }
}

