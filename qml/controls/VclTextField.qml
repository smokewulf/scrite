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

/**
  We this kind of a heavy TextField implementation because, we have to add

  - Transliteration support
  - Special symbols spport
  - Auto completion popups support
  - Cut/Copy/Paste context menu support

  None of these are available in vanilla TextField QML component from QtQuick Controls
  */

import QtQml 2.15
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15

import io.scrite.components 1.0

import "qrc:/qml/globals"
import "qrc:/qml/helpers"

TextField {
    id: textField

    Material.primary: Runtime.colors.primary.key
    Material.accent: Runtime.colors.accent.key
    Material.theme: Material.Light

    signal requestCompletion(string string)
    signal editingComplete()
    signal returnPressed()

    property alias completionAcceptsEnglishStringsOnly: completionModel.acceptEnglishStringsOnly
    property alias completionSortMode: completionModel.sortMode
    property alias completionStrings: completionModel.strings
    property alias completionPrefix: completionModel.completionPrefix
    property alias maxCompletionItems: completionModel.maxVisibleItems
    property int maxVisibleItems: maxCompletionItems
    property int minimumCompletionPrefixLength: 1
    property bool singleClickAutoComplete: true
    property Item tabItem
    property Item backTabItem
    property bool labelAlwaysVisible: false
    property alias label: labelText.text
    property alias labelColor: labelText.color
    property alias labelTextAlign: labelText.horizontalAlignment
    property bool enableTransliteration: false
    property bool includeEmojiSymbols: true
    property bool undoRedoEnabled: false
    property alias showingSymbols: specialSymbolSupport.showingSymbols
    property var includeSuggestion: function(suggestion) {
        return suggestion
    }
    property bool tabItemUponReturn: true

    selectedTextColor: Runtime.colors.accent.c700.text
    selectionColor: Runtime.colors.accent.c700.background
    selectByMouse: true
    font.pointSize: Runtime.idealFontMetrics.font.pointSize

    onEditingFinished: {
        transliterate(true)
        completionModel.allowEnable = false
        editingComplete()
    }

    Component.onDestruction: {
        if(activeFocus) {
            transliterate(true)
            editingComplete()
        }
    }

    onActiveFocusChanged: {
        if(activeFocus && !readOnly)
            selectAll()
        else
            completionViewPopup.close()
    }

    CompletionModel {
        id: completionModel
        property bool allowEnable: true
        property string suggestion: currentCompletion
        property bool hasSuggestion: count > 0
        enabled: allowEnable && textField.activeFocus && textField.length >= textField.minimumCompletionPrefixLength
        sortStrings: false
        completionPrefix: textField.text
        filterKeyStrokes: textField.activeFocus
        onRequestCompletion: autoCompleteOrFocusNext(tabItemUponReturn)
        property bool hasItems: count > 0
        onHasItemsChanged: {
            if(hasItems)
                completionViewPopup.open()
            else
                completionViewPopup.close()
        }
    }

    UndoHandler {
        enabled: undoRedoEnabled && !textField.readOnly && textField.activeFocus
        canUndo: textField.canUndo
        canRedo: textField.canRedo
        onUndoRequest: textField.undo()
        onRedoRequest: textField.redo()
    }

    onTextEdited: {
        transliterate(false)
        completionModel.allowEnable = true
    }

    onFocusChanged: completionModel.allowEnable = true

    property bool userTypedSomeText: false
    Keys.onPressed: {
        if(event.text !== "")
            userTypedSomeText = true
    }

    Keys.onReturnPressed: {
        autoCompleteOrFocusNext(tabItemUponReturn)
        returnPressed()
    }
    Keys.onEnterPressed: {
        autoCompleteOrFocusNext(tabItemUponReturn)
        returnPressed()
    }

    Keys.onTabPressed: autoCompleteOrFocusNext(true)

    ContextMenuEvent.onPopup: (mouse) => {
        if(!textField.activeFocus) {
            textField.forceActiveFocus()
            textField.cursorPosition = textField.positionAt(mouse.x, mouse.y)
        }
        contextMenu.popup()
    }

    function autoCompleteOrFocusNext(doTabItem) {
        if(completionModel.hasSuggestion && completionModel.suggestion !== text) {
            text = includeSuggestion(completionModel.suggestion)
            editingFinished()
        } else if(tabItem && (doTabItem === undefined || doTabItem === true)) {
            editingFinished()
            tabItem.forceActiveFocus()
        } else
            editingFinished()
    }

    KeyNavigation.tab: tabItem
    KeyNavigation.backtab: backTabItem

    function transliterate(includingLastWord) {
        if(includingLastWord === undefined)
            includingLastWord = false
        if(enableTransliteration & userTypedSomeText) {
            var newText = Scrite.app.transliterationEngine.transliteratedParagraph(text, includingLastWord)
            if(text === newText)
                return
            userTypedSomeText = false
            text = newText
        }
    }

    SpecialSymbolsSupport {
        id: specialSymbolSupport
        anchors.top: parent.bottom
        anchors.left: parent.left
        textEditor: textField
        includeEmojis: parent.includeEmojiSymbols
        textEditorHasCursorInterface: true
    }

    VclLabel {
        id: labelText
        text: parent.placeholderText
        font.pointSize: 2*Runtime.idealFontMetrics.font.pointSize/3
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.verticalCenter: parent.top
        anchors.verticalCenterOffset: parent.topPadding/4
        visible: parent.labelAlwaysVisible ? true : parent.text !== ""
    }

    FontMetrics {
        id: fontMetrics
        font: textField.font
    }

    Popup {
        id: completionViewPopup
        x: 0
        y: parent.height
        width: parent.width
        height: visible ? completionView.height + topInset + bottomInset + topPadding + bottomPadding : 100
        focus: false
        closePolicy: textField.length === 0 ? Popup.CloseOnPressOutside : Popup.NoAutoClose
        contentItem: ListView {
            id: completionView
            clip: true
            model: completionModel
            FlickScrollSpeedControl.factor: Runtime.workspaceSettings.flickScrollSpeedFactor
            highlightMoveDuration: 0
            highlightResizeDuration: 0
            keyNavigationEnabled: false
            property real delegateHeight: fontMetrics.lineSpacing + 10
            delegate: VclLabel {
                width: completionView.width - (completionView.contentHeight > completionView.height ? 20 : 1)
                height: completionView.delegateHeight
                text: string
                padding: 5
                font: textField.font
                color: index === completionView.currentIndex ? Runtime.colors.primary.highlight.text : Runtime.colors.primary.c10.text
                MouseArea {
                    id: textMouseArea
                    anchors.fill: parent
                    hoverEnabled: singleClickAutoComplete
                    onContainsMouseChanged: if(singleClickAutoComplete) completionModel.currentRow = index
                    cursorShape: singleClickAutoComplete ? Qt.PointingHandCursor : Qt.ArrowCursor
                    onClicked: {
                        if(singleClickAutoComplete || completionModel.currentRow === index)
                            completionModel.requestCompletion(parent.text)
                        else
                            completionModel.currentRow = index
                    }
                    onDoubleClicked: completionModel.requestCompletion(parent.text)
                }
            }
            highlight: Rectangle {
                color: Runtime.colors.primary.highlight.background
            }
            currentIndex: completionModel.currentRow
            height: Math.min(contentHeight, maxVisibleItems > 0 ? delegateHeight*maxVisibleItems : contentHeight)
            ScrollBar.vertical: VclScrollBar { flickable: completionView }
        }
    }

    VclMenu {
        id: contextMenu
        focus: false
        property bool __persistentSelection: false
        onAboutToShow: {
            __persistentSelection = textField.persistentSelection
            textField.persistentSelection = true
        }
        onAboutToHide: textField.persistentSelection = __persistentSelection

        VclMenuItem {
            text: "Cut\t" + Scrite.app.polishShortcutTextForDisplay("Ctrl+X")
            enabled: textField.selectedText !== ""
            onClicked: textField.cut()
            focusPolicy: Qt.NoFocus
        }

        VclMenuItem {
            text: "Copy\t" + Scrite.app.polishShortcutTextForDisplay("Ctrl+C")
            enabled: textField.selectedText !== ""
            onClicked: textField.copy()
            focusPolicy: Qt.NoFocus
        }

        VclMenuItem {
            text: "Paste\t" + Scrite.app.polishShortcutTextForDisplay("Ctrl+V")
            onClicked: textField.paste()
            focusPolicy: Qt.NoFocus
        }
    }

    Component {
        id: backgroundComponent

        Item {
            implicitWidth: textField.width
            implicitHeight: fontMetrics.lineSpacing

            Rectangle {
                width: parent.width
                height: 1
                color: textField.activeFocus ? Runtime.colors.primary.c700.background : Runtime.colors.primary.c300.background
                anchors.bottom: parent.bottom
            }
        }
    }

    Component.onCompleted: {
        if(!Scrite.app.usingMaterialTheme) {
            background = backgroundComponent.createObject(textField)
            topPadding = topPadding + 4
            bottomPadding = bottomPadding + 4
        }
    }
}
