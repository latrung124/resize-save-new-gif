/*
* CustomProgressBar.qml
* Author: Trung La
* Date: 2024-12-29
* Description: Custom progress bar for the application
*/

import QtQuick
import QtQuick.Templates as T
import QtQuick.Controls

T.ProgressBar {
    id: control

    implicitWidth: Math.max(implicitBackgroundWidth + leftInset + rightInset,
                            implicitContentWidth + leftPadding + rightPadding)
    implicitHeight: Math.max(implicitBackgroundHeight + topInset + bottomInset,
                             implicitContentHeight + topPadding + bottomPadding)
    property color progressColor: "#A9BFA8"
    property color backgroundColor: "#5E686D"

    background: Rectangle {
        implicitWidth: internal.implicitWidth
        implicitHeight: internal.height

        radius: internal.radius
        color: backgroundColor
    }

    contentItem: Item {
        implicitHeight: internal.height
        implicitWidth: internal.implicitWidth

        Rectangle {
            visible: !control.indeterminate

            width: control.visualPosition * parent.width
            height: parent.height

            radius: internal.radius
            color: internal.progressColor
        }

        Rectangle {
            id: indeterminateProgress

            visible: control.indeterminate

            y: -internal.progressTopOffset
            height: control.height + internal.progressTopOffset
            width: control.width
            radius: internal.radius

            color: "transparent"
            clip: true

            Rectangle {
                y: internal.progressTopOffset
                height: control.height
                width: internal.progressIndetWidth

                radius: internal.radius
                color: progressColor

                XAnimator on x {
                    from: -internal.progressIndetWidth
                    to: control.width
                    loops: Animation.Infinite
                    running: control.indeterminate && control.visible
                    duration: 3200
                }
            }
        }
    }

    QtObject {
        id: internal

        property int height: 4
        property int radius: height / 2
        property int implicitWidth: 240
        property int progressIndetWidth: width / 3
        property int progressTopOffset: 1
    }
}
