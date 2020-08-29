import QtQuick 2.9
import QtQuick.Window 2.3
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import org.cyber.launcher 1.0

ApplicationWindow {
    visible: true
    width: Screen.width
    height: Screen.height
    visibility: Window.FullScreen
    flags: Qt.BypassWindowManagerHint | Qt.FramelessWindowHint | Qt.WindowStaysOnTopHint
    id: root

    property int columns: 6
    property int rows: 0
    property var appPages: []

    color: "transparent"
    background: Rectangle{
        color: "black"
        opacity: 0.7
    }

    ApplicationManager {
        id: applicationManager
    }

//    LauncherModel {
//        id: launcherModel
//        sourceModel: applicationManager
//    }

    TextField {
        id: textField
        height: 50
        width: root.width * 0.2
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.margins: 50

        background: Rectangle {
            opacity: 0.55
            radius: textField.height * 0.2
        }

        onTextChanged: {
            grid.query = text
        }

        Keys.onEscapePressed: Qt.quit()
    }

    LauncherGridView {
        anchors.top: textField.bottom
        anchors.centerIn: parent
        // anchors.horizontalCenter: parent.horizontalCenter
        id: grid
    }

    PageIndicator {
        anchors.top: grid.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        id: pageIndicator
        count: grid.pages
        currentIndex: grid.currentPage
        onCurrentIndexChanged: grid.currentPage = currentIndex
    }
}
