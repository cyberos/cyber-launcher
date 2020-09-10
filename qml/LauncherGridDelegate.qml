import QtQuick 2.9
import QtQuick.Controls 2.1
import QtQuick.Controls.Material 2.1

Rectangle {
    color: "transparent"
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
                    to: 1.2
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
                    from: 1.2
                    to: 1
                    duration: 100
                    easing.type: Easing.InCubic
                }
            }
        ]

        MouseArea {
            id: iconArea
            anchors.fill: icon
            hoverEnabled: true

            onEntered: {
                icon.state = "mouseIn"
            }

            onExited: {
                icon.state = "mouseOut"
            }
        }
    }

    MouseArea {
        anchors.fill: parent

        onClicked: {
            launcherModel.launch(model.appId)
        }
    }

    TextMetrics {
        id: fontMetrics
        font.family: label.font.family
        text: label.text
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
        wrapMode: "WordWrap"
        horizontalAlignment: Text.AlignHCenter
        width: parent.width - 2 * 10
        height: fontMetrics.height
        color: "white"
    }
}
