import QtQuick 2.15
import navigation 1.0

Item {
	FontLoader { id: heeboBold; source: "qrc:/font/heebo_bold.ttf" }

	Connections {
		target: navigation
		function onClutchChanged(a, b, c, d, e) {
			if(start.value !== a) start.value = a;
			if(end.value !== b) end.value = b;
			if(friction.value !== c) friction.value = c;
			if(position.value !== d) position.value = d;
			if(autoLaunch.value !== e) autoLaunch.value = e ? "ON" : "OFF";
		}
	}

	width: rectangle.width
	height: rectangle.y + rectangle.height

	property var tasks: []
	visible: tasks.indexOf(cursorTask) !== -1

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
			id: start;
			title: "START"
			width: rectangle.width / 3
			height: rectangle.height / 2
			cursor: cursorTask === Navigation.START
		}

		Task {
			id: end;
			title: "END"
			width: rectangle.width / 3
			height: rectangle.height / 2
			x: rectangle.width * 1/3
			cursor: cursorTask === Navigation.END
		}

		Task {
			id: friction
			title: "FRICTION"
			width: rectangle.width / 3
			height: rectangle.height / 2
			x: rectangle.width * 2/3
			cursor: cursorTask === Navigation.FRICTION
		}

		Task {
			id: position
			title: "POSITION"
			width: rectangle.width / 2
			height: rectangle.height / 2
			y: rectangle.height / 2
			cursor: cursorTask === Navigation.POSITION
		}

		Task {
			id: autoLaunch
			title: "AUTO LAUNCH"
			width: rectangle.width / 2
			height: rectangle.height / 2
			x: rectangle.width / 2
			y: rectangle.height / 2
			cursor: cursorTask === Navigation.AUTO_LAUNCH
		}
	}
}
