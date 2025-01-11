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

pragma Singleton

import QtQuick 2.15

import io.scrite.components 1.0

QtObject {
    id: root

    function init() { }

    property AutoUpdate autoUpdate: Scrite.app.autoUpdate

    Notification.active: autoUpdate.updateAvailable
    Notification.title: "Update Available"
    Notification.text: {
        if(autoUpdate.updateAvailable)
            return "Scrite " + autoUpdate.updateInfo.versionString + " is now available for download. <font size=\"-1\"><i>[<strong>What's new?</strong> " + autoUpdate.updateInfo.changeLog + "]</i></font>"
        return ""
    }
    Notification.buttons: ["Download", "Ignore"]
    Notification.onButtonClicked: (index) => {
        if(autoUpdate.updateAvailable) {
            if(index === 0)
                Qt.openUrlExternally(autoUpdate.updateDownloadUrl)
        }
    }
}
