import QtQuick 2.15

Item {
	FontLoader { id: heeboBold; source: "qrc:/font/heebo_bold.ttf" }

	width: rectangle.width
	height: rectangle.height

	Rectangle {
		id: rectangle
		width: errorText.width + 34
		height: errorText.height + 10

		color: "#FF3A45"
		radius: 14

		Text {
			id: errorText
			text: "SHIFTING SYSTEM OFFLINE"
			font.family: heeboBold.name
			font.pixelSize: 24
			color: "white"

			anchors.centerIn: parent
		}
	}
}
