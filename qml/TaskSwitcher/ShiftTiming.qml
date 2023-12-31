import QtQuick 2.15

Item {
    FontLoader { id: heeboBold; source: "qrc:/font/heebo_bold.ttf" }

    width: rectangle.width
    height: rectangle.y + rectangle.height

    Text {
        id: taskText
        text: "Shift Timing"
        font.family: heeboBold.name
        font.pixelSize: 44
        color: "white"

        anchors.left: rectangle.left
        anchors.leftMargin: 20
    }

    Rectangle {
        id: rectangle
        width: 480
        height: 200
        anchors.top: taskText.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: 4
        color: "#121314"
        radius: 20

        Task {
            title: "UP DELAY"
            value: navigation.upDelay
            width: rectangle.width / 2
            height: rectangle.height / 2
            cursor: cursorTask === navigation.UP_DELAY
        }

        Task {
            title: "DOWN DELAY"
            value: navigation.downDelay
            width: rectangle.width / 2
            height: rectangle.height / 2
            x: rectangle.width / 2
            cursor: cursorTask === navigation.DOWN_DELAY
        }

        Task {
            title: "OUTPUT"
            value: navigation.output
            width: rectangle.width / 2
            height: rectangle.height / 2
            y: rectangle.height / 2
            cursor: cursorTask === navigation.OUTPUT
        }

        Task {
            title: "TIMEOUT"
            value: navigation.timeout
            width: rectangle.width / 2
            height: rectangle.height / 2
            x: rectangle.width / 2
            y: rectangle.height / 2
            cursor: cursorTask === navigation.TIMEOUT
        }
    }
}
