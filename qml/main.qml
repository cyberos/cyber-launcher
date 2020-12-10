import QtQuick 2.9
import QtQuick.Window 2.3
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import org.cyber.launcher 1.0
import MeuiKit 1.0 as Meui

ApplicationWindow {
    id: root
    visible: false

//    width: Screen.desktopAvailableWidth - (Screen.desktopAvailableHeight * 0.1)
//    height: Screen.desktopAvailableHeight - (Screen.desktopAvailableHeight * 0.1)
//    x: (Screen.desktopAvailableWidth - root.width) / 2
//    y: (Screen.desktopAvailableHeight - root.height) / 2

//    width: Screen.desktopAvailableWidth
//    height: Screen.desktopAvailableHeight

    width: Screen.width
    height: Screen.height

    flags: Qt.FramelessWindowHint | Qt.WindowStaysOnTopHint | Qt.X11BypassWindowManagerHint

    color: "transparent"
    background: Rectangle{
        color: "black"
        opacity: 0.9
        // radius: root.height * 0.05
    }

    onActiveChanged: {
        if (!active)
            hideLauncher()
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
            color: Meui.Theme.backgroundColor
        }

        onTextChanged: {
            launcherModel.search(text)
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
