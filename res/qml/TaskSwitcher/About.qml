import QtQuick 2.15

Item {
	FontLoader { id: heeboBold; source: "qrc:/font/heebo_bold.ttf" }

	width: rectangle.width
	height: rectangle.y + rectangle.height

	Text {
		id: taskText
		text: "About"
		font.family: heeboBold.name
		font.pixelSize: 44
		color: "white"

		anchors.left: rectangle.left
		anchors.leftMargin: 20
	}

	property int leftMargin: 30
	property int topMargin: -4

	property string formattedText: "<font color=\"#FFFFFF\">%1</font>&nbsp;&nbsp;<font color=\"#b3b3b3\">%2</font>"

	Rectangle {
		id: rectangle
		width: 480
		height: 200
		anchors.top: taskText.bottom
		anchors.horizontalCenter: parent.horizontalCenter
		anchors.topMargin: 4
		color: "#121314"
		radius: 20

		Text {
			id: pi
			text: DEVICE
			font.family: heeboBold.name
			font.pixelSize: 24
			color: "white"

			anchors.left: rectangle.left
			anchors.top: rectangle.top
			anchors.leftMargin: leftMargin
			anchors.topMargin: 30
		}

		Text {
			id: processor
			text: formattedText.arg("Processor").arg(PROCESSOR)
			font.family: heeboBold.name
			font.pixelSize: 24

			anchors.left: rectangle.left
			anchors.top: pi.bottom
			anchors.leftMargin: leftMargin
			anchors.topMargin: topMargin
		}

		Text {
			id: memory
			text: formattedText.arg("Memory").arg(MEMORY)
			font.family: heeboBold.name
			font.pixelSize: 24

			anchors.left: rectangle.left
			anchors.top: processor.bottom
			anchors.leftMargin: leftMargin
			anchors.topMargin: topMargin
		}

		Text {
			id: display
			text: formattedText.arg("Display").arg(DISPLAY)
			font.family: heeboBold.name
			font.pixelSize: 24

			anchors.left: rectangle.left
			anchors.top: memory.bottom
			anchors.leftMargin: leftMargin
			anchors.topMargin: topMargin
		}
	}
}
