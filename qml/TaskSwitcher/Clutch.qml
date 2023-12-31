import QtQuick 2.15

Item {
    FontLoader { id: heeboBold; source: "qrc:/font/heebo_bold.ttf" }

    width: rectangle.width
    height: rectangle.y + rectangle.height

    Text {
        id: taskText
        text: "Clutch"
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
            title: "START"
            value: navigation.start
            width: rectangle.width / 3
            height: rectangle.height / 2
            cursor: cursorTask === navigation.START
        }

        Task {
            title: "END"
            value: navigation.end
            width: rectangle.width / 3
            height: rectangle.height / 2
            x: rectangle.width * 1/3
            cursor: cursorTask === navigation.END
        }

        Task {
            title: "FRICTION"
            value: navigation.friction
            width: rectangle.width / 3
            height: rectangle.height / 2
            x: rectangle.width * 2/3
            cursor: cursorTask === navigation.FRICTION
        }

        Task {
            title: "POSITION"
            value: navigation.position
            width: rectangle.width / 2
            height: rectangle.height / 2
            y: rectangle.height / 2
            cursor: cursorTask === navigation.POSITION
        }

        Task {
            title: "AUTO LAUNCH"
            value: navigation.autoLaunch ? "ON" : "OFF"
            width: rectangle.width / 2
            height: rectangle.height / 2
            x: rectangle.width / 2
            y: rectangle.height / 2
            cursor: cursorTask === navigation.AUTOLAUNCH
        }
    }
}
