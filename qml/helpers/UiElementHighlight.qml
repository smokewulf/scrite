/****************************************************************************
**
** Copyright (C) VCreate Logic Pvt. Ltd. Bengaluru
** Author: Prashanth N Udupa (prashanth@scrite.io)
**
** This code is distributed under GPL v3. Complete text of the license
** can be found here: https://www.gnu.org/licenses/gpl-3.0.txt
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/

import QtQml 2.15
import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15

import io.scrite.components 1.0

import "qrc:/qml/globals"
import "qrc:/qml/helpers"
import "qrc:/qml/controls"

/**
  This item is used for highlighting UI elements to educate users about where
  certain options are present.
  */

Item {
    id: uiElementHighlight

    property Item uiElement
    property string description
    property int descriptionPosition: Item.Right
    property bool uiElementBoxVisible: false
    property bool highlightAnimationEnabled: true

    signal done()
    signal scaleAnimationDone()

    ItemPositionMapper {
        id: uiElementPosition
        from: uiElement
        to: uiElementHighlight
    }

    Item {
        id: uiElementOverlay
        x: uiElementPosition.mappedPosition.x
        y: uiElementPosition.mappedPosition.y
        width: uiElement.width * uiElement.scale
        height: uiElement.height * uiElement.scale

        Rectangle {
            anchors.fill: parent
            anchors.margins: -2.5
            color: Qt.rgba(0,0,0,0)
            border.width: 2
            border.color: Runtime.colors.accent.highlight.background
            visible: uiElementBoxVisible
        }

        BoxShadow {
            anchors.fill: descTip
        }

        Rectangle {
            id: descTip
            color: Runtime.colors.accent.highlight.background
            width: descLabel.width
            height: descLabel.height
            border.width: 1
            border.color: Runtime.colors.accent.borderColor

            VclLabel {
                id: descLabel
                text: description
                font.bold: true
                font.pointSize: Runtime.idealFontMetrics.font.pointSize+2
                color: Runtime.colors.accent.highlight.text
                leftPadding: (descriptionPosition === Item.Right ? descIcon.width : (descriptionPosition === Item.Bottom || descriptionPosition === Item.Top ? 20 : 0)) + 5
                rightPadding: (descriptionPosition === Item.Left ? descIcon.width : (descriptionPosition === Item.Bottom || descriptionPosition === Item.Top ? 20 : 0)) + 5
                topPadding: descriptionPosition === Item.Bottom || descriptionPosition === Item.Top ? descIcon.height : 10
                bottomPadding: descriptionPosition === Item.Top || descriptionPosition === Item.Bottom ? descIcon.height : 10

                Image {
                    id: descIcon
                    width: Runtime.idealFontMetrics.height
                    height: width
                    smooth: true
                    source: {
                        switch(descriptionPosition) {
                        case Item.Right:
                            return "qrc:/icons/navigation/arrow_left_inverted.png"
                        case Item.Right:
                            return "qrc:/icons/navigation/arrow_right_inverted.png"
                        case Item.Top:
                        case Item.TopLeft:
                        case Item.TopRight:
                            return "qrc:/icons/navigation/arrow_down_inverted.png"
                        case Item.Bottom:
                        case Item.BottomLeft:
                        case Item.BottomRight:
                            return "qrc:/icons/navigation/arrow_up_inverted.png"
                        }
                    }
                }
            }

            Component.onCompleted: {
                switch(descriptionPosition) {
                case Item.Right:
                    descTip.anchors.verticalCenter = uiElementOverlay.verticalCenter
                    descTip.anchors.left = uiElementOverlay.right
                    descIcon.anchors.verticalCenter = descLabel.verticalCenter
                    descIcon.anchors.left = descLabel.left
                    break
                case Item.Left:
                    descTip.anchors.verticalCenter = uiElementOverlay.verticalCenter
                    descTip.anchors.right = uiElementOverlay.left
                    descIcon.anchors.verticalCenter = descLabel.verticalCenter
                    descIcon.anchors.right = descLabel.right
                    break
                case Item.Top:
                case Item.TopLeft:
                case Item.TopRight:
                    if(descriptionPosition === Item.Top) {
                        descTip.anchors.horizontalCenter = uiElementOverlay.horizontalCenter
                        descIcon.anchors.horizontalCenter = descLabel.horizontalCenter
                    } else if(descriptionPosition === Item.TopRight) {
                        descTip.anchors.left = uiElementOverlay.left
                        descTip.anchors.leftMargin = descLabel.leftPadding
                        descIcon.anchors.left = descLabel.left
                        descIcon.anchors.leftMargin = descLabel.leftPadding
                    } else {
                        descTip.anchors.right = uiElementOverlay.right
                        descTip.anchors.rightMargin = descLabel.rightPadding
                        descIcon.anchors.right = descLabel.right
                        descIcon.anchors.right = descLabel.rightPadding
                    }
                    descTip.anchors.bottom = uiElementOverlay.top
                    descIcon.anchors.bottom = descLabel.bottom
                    break
                case Item.Bottom:
                case Item.BottomLeft:
                case Item.BottomRight:
                    if(descriptionPosition === Item.Top) {
                        descTip.anchors.horizontalCenter = uiElementOverlay.horizontalCenter
                        descIcon.anchors.horizontalCenter = descLabel.horizontalCenter
                    } else if(descriptionPosition === Item.BottomRight) {
                        descTip.anchors.left = uiElementOverlay.left
                        descTip.anchors.leftMargin = descLabel.leftPadding
                        descIcon.anchors.left = descLabel.left
                        descIcon.anchors.leftMargin = descLabel.leftPadding
                    } else {
                        descTip.anchors.right = uiElementOverlay.right
                        descTip.anchors.rightMargin = descLabel.rightPadding
                        descIcon.anchors.right = descLabel.right
                        descIcon.anchors.right = descLabel.rightPadding
                    }
                    descTip.anchors.top = uiElementOverlay.bottom
                    descIcon.anchors.top = descLabel.top
                    break
                }
            }
        }
    }

    SequentialAnimation {
        running: true

        NumberAnimation {
            target: uiElement
            property: "scale"
            from: 1; to: highlightAnimationEnabled ? 2 : 1
            duration: 500
        }

        PauseAnimation {
            duration: 250
        }

        NumberAnimation {
            target: uiElement
            property: "scale"
            from: highlightAnimationEnabled ? 2 : 1; to: 1
            duration: 500
        }

        ScriptAction {
            script: scaleAnimationDone()
        }
    }

    MouseArea {
        anchors.fill: parent
        onClicked: done()
    }

    Timer {
        running: true
        repeat: false
        interval: 4000
        onTriggered: done()
    }
}
