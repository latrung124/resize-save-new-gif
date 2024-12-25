/*
    CustomAnimatedImage.qml
*/

import QtQuick
import QtQuick.Controls

Item {
    id: root

    property string source: ""
    signal rotateRight()
    signal rotateLeft()
    signal flipHorizontalRight()
    signal flipHorizontalLeft()

    onRotateRight: function() {
        console.log("CustomAnimatedImage: Rotate right signal received");
        if (gifRect.visible) {
            animatedImage.rotation = (animatedImage.rotation + 90) % 360;
        }

        if (image.visible) {
            image.rotation = (image.rotation + 90) % 360;
        }
    }

    onRotateLeft: function() {
        console.log("CustomAnimatedImage: Rotate left signal received");
        if (gifRect.visible) {
            animatedImage.rotation = (animatedImage.rotation - 90) % 360;
        }

        if (image.visible) {
            image.rotation = (image.rotation - 90) % 360;
        }
    }

    onFlipHorizontalRight: function() {
        console.log("CustomAnimatedImage: Flip horizontal right signal received");
        if (gifRect.visible) {
            animatedImageScale.xScale = 1;
        }

        if (image.visible) {
            imageScale.xScale = 1;
        }
    }

    onFlipHorizontalLeft: function() {
        console.log("CustomAnimatedImage: Flip horizontal left signal received");
        if (gifRect.visible) {
            animatedImageScale.xScale = -1;
        }

        if (image.visible) {
            imageScale.xScale = -1;
        }
    }

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
            transform: Scale {
                id: animatedImageScale
                xScale: 1
                origin.x: animatedImage.width / 2
            }

            BusyIndicator {
                anchors.centerIn: parent
                running: animatedImage.status === AnimatedImage.Loading
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

