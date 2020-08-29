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

        states: ["mouseIn", "mouseOut"]
        state: "mouseOut"

        transitions: [
            Transition {
                from: "*"
                to: "mouseIn"

                NumberAnimation {
                    target: icon
                    properties: "scale"
                    from: 1
                    to: 1.1
                    duration: 150
                    easing.type: Easing.OutCubic
                }
            },
            Transition {
                from: "*"
                to: "mouseOut"

                NumberAnimation {
                    target: icon
                    properties: "scale"
                    from: 1.1
                    to: 1
                    duration: 150
                    easing.type: Easing.InCubic
                }
            }
        ]

        MouseArea {
            id: iconArea
            anchors.fill: icon
            hoverEnabled: true

            onContainsMouseChanged: {
                icon.state = containsMouse ? "mouseIn" : "mouseOut"
            }
        }
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
