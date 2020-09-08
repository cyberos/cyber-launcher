import QtQuick 2.9
import QtQuick.Window 2.3
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import org.cyber.launcher 1.0

ApplicationWindow {
    visible: false
    width: Screen.width
    height: Screen.height
    flags: Qt.BypassWindowManagerHint | Qt.FramelessWindowHint | Qt.WindowStaysOnTopHint
    id: root

    color: "transparent"
    background: Rectangle{
        color: "black"
        opacity: 0.8
    }

    MouseArea {
        anchors.fill: parent

        onClicked: {
            hideLauncher()
        }
    }

    LauncherModel {
        id: launcherModel
    }

    Connections {
        target: launcherModel

        function onApplicationLaunched() {
            hideLauncher()
        }
    }

    TextField {
        id: textField
        height: minimumHeight < calcHeight ? calcHeight : minimumHeight
        width: root.width * 0.2
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.margins: root.height * 0.05
        placeholderText: qsTr("Search")
        focus: Qt.StrongFocus

        property var calcHeight: root.height * 0.03
        property var minimumHeight: 35

        background: Rectangle {
            opacity: 0.8
            radius: textField.height * 0.2
        }

        onTextChanged: {
            // grid.query = text
        }

        Keys.onEscapePressed: hideLauncher()
    }

    LauncherGridView {
        anchors.top: textField.bottom
        anchors.centerIn: parent
        // anchors.horizontalCenter: parent.horizontalCenter
        id: grid
    }

    PageIndicator {
        id: pageIndicator
        anchors.top: grid.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        count: grid.pages
        currentIndex: grid.currentPage
        onCurrentIndexChanged: grid.currentPage = currentIndex
        topPadding: root.height * 0.03
        interactive: true

        delegate: Rectangle {
            width: 10
            height: width
            radius: width / 2
            color: index === pageIndicator.currentIndex ? "white" : Qt.darker("white")
        }
    }

    function showLauncher() {
        root.visible = true;
        root.visibility = Window.FullScreen
    }

    function hideLauncher() {
        textField.text = ""
        root.visible = false;
    }

    function toggle() {
        if (root.visible)
            hideLauncher()
        else
            showLauncher()
    }
}
