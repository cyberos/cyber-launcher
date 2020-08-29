import QtQuick 2.0
import QtQuick.Controls 2.1
import QtQuick.Controls.Material 2.1

Rectangle {
    property bool hovered: false

    color: hovered ? Qt.rgba(0,0,0,0.1) : "transparent"
    radius: 2
    antialiasing: true

    Image {
        id: icon
        anchors {
            horizontalCenter: parent.horizontalCenter
            top: parent.top
            bottom: label.top
            margins: 2 * 10
        }

        property real size: height

        source: "image://icontheme/" + model.iconName
        sourceSize.width: height
        sourceSize.height: height
        width: height
        height: width
    }

    Label {
        id: label

        anchors {
            horizontalCenter: parent.horizontalCenter
            bottom: parent.bottom
            margins: 10
        }

        text: model.name
        elide: Text.ElideRight
        textFormat: Text.PlainText
        horizontalAlignment: Text.AlignHCenter
        width: parent.width - 2 * 10
        color: "white"
    }
}
