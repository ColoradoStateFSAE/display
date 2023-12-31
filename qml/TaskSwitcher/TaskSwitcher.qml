import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Shapes 1.15
import QtGraphicalEffects 1.12

Item {
    FontLoader { id: heeboBold; source: "qrc:/font/heebo_bold.ttf" }

    property int cursorTask: 0

    Connections {
        target: navigation
        function onChangeCursor(value) { cursorTask = value; }
    }

    Rectangle {
        width: 800
        height: 480
        color: "black"
        opacity: 0.3
    }

    property int topSpacing: 70

    About {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: topSpacing

        visible: cursorTask === navigation.ABOUT
                 ? true : false
    }

    ShiftTiming {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: topSpacing

        visible: cursorTask === navigation.SHIFT ||
                 cursorTask === navigation.UP_DELAY ||
                 cursorTask === navigation.DOWN_DELAY ||
                 cursorTask === navigation.OUTPUT ||
                 cursorTask === navigation.TIMEOUT
                 ? true : false
    }

    Clutch {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: topSpacing

        visible: cursorTask === navigation.CLUTCH ||
                 cursorTask === navigation.POSITION ||
                 cursorTask === navigation.START ||
                 cursorTask === navigation.END ||
                 cursorTask === navigation.FRICTION ||
                 cursorTask === navigation.AUTOLAUNCH
                 ? true : false
    }

    Heading {
        id: exit
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        anchors.leftMargin: 60
        anchors.bottomMargin: 60
        icon: "qrc:/icon/close.png"
        cursor: cursorTask === 0 ? true : false
    }

    Heading {
        id: about
        anchors.left: parent.left
        anchors.bottom: exit.top
        anchors.leftMargin: 60
        anchors.bottomMargin: 10
        headingColor: "#0D8036"
        icon: "qrc:/icon/about.png"
        cursor: cursorTask === 1 ? true : false
    }

    Heading {
        id: shift
        anchors.left: parent.left
        anchors.bottom: about.top
        anchors.leftMargin: 60
        anchors.bottomMargin: 10
        headingColor: "#007aff"
        icon: "qrc:/icon/shift.png"
        cursor: cursorTask === 2 ? true : false
    }

    Heading {
        id: clutch
        anchors.left: parent.left
        anchors.bottom: shift.top
        anchors.leftMargin: 60
        anchors.bottomMargin: 10
        headingColor: "#ff2d55"
        icon: "qrc:/icon/servo.png"
        cursor: cursorTask === 3 ? true : false
    }
}
