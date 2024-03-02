import QtQuick 2.15
import navigation 1.0

Item {
	FontLoader { id: heeboBold; source: "qrc:/font/heebo_bold.ttf" }

	Connections {
		target: navigation
		function onShiftChanged(a, b, c, d) {
			if(upDelay !== a) upDelay.value = a;
			if(downDelay !== b) downDelay.value = b;
			if(output !== c) output.value = c;
			if(timeout !== d) timeout.value = d;
		}
	}

	width: rectangle.width
	height: rectangle.y + rectangle.height

	property var tasks: []
	visible: tasks.indexOf(cursorTask) !== -1

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
			id: upDelay
			title: "UP DELAY"
			width: rectangle.width / 2
			height: rectangle.height / 2
			cursor: cursorTask === Navigation.UP_DELAY
		}

		Task {
			id: downDelay
			title: "DOWN DELAY"
			width: rectangle.width / 2
			height: rectangle.height / 2
			x: rectangle.width / 2
			cursor: cursorTask === Navigation.DOWN_DELAY
		}

		Task {
			id: output
			title: "OUTPUT"
			width: rectangle.width / 2
			height: rectangle.height / 2
			y: rectangle.height / 2
			cursor: cursorTask === Navigation.OUTPUT
		}

		Task {
			id: timeout
			title: "TIMEOUT"
			width: rectangle.width / 2
			height: rectangle.height / 2
			x: rectangle.width / 2
			y: rectangle.height / 2
			cursor: cursorTask === Navigation.TIMEOUT
		}
	}
}
