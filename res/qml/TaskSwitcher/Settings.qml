import QtQuick 2.15
import navigation 1.0

Item {
	FontLoader { id: heeboBold; source: "qrc:/font/heebo_bold.ttf" }

    Connections {
		target: navigation
		function onSettingsChanged(a, b) {
			if(brightness !== a) brightness.value = a;
			if(chance !== b) chance.value = b? "ON" : "OFF";
		}
	}

	width: rectangle.width
	height: rectangle.y + rectangle.height

	property var tasks: []
	visible: tasks.indexOf(cursorTask) !== -1

	Text {
		id: taskText
		text: "Settings"
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
			id: brightness;
			title: "LED BRIGHTNESS"
			width: rectangle.width / 2
			height: rectangle.height / 2
			cursor: cursorTask === Navigation.BRIGHTNESS
        }

        Task {
			id: chance
			title: "CHANCE MODE"
			width: rectangle.width / 2
			height: rectangle.height / 2
			x: rectangle.width / 2
			cursor: cursorTask === Navigation.CHANCE
        }
	}
}
