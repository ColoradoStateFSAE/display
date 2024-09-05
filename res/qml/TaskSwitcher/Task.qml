import QtQuick 2.15

Item {
	FontLoader { id: heeboBold; source: "qrc:/font/heebo_bold.ttf" }

	property string value: ""
	property string title: "placeholder"
	property bool cursor: false
	property bool edit: selected && cursor

	Rectangle {
		id: rectangle
		width: parent.width
		height: parent.height
		y: 0
		radius: 20
		color: edit ? "#a3a3a3" : (cursor ? "#00ff5a" : "transparent")

		Text {
			id: description
			text: title
			font.family: heeboBold.name
			font.pixelSize: 22
			color: cursor ? "#121314" : "white"
			anchors.horizontalCenter: parent.horizontalCenter
			anchors.bottom: parent.bottom
			anchors.bottomMargin: 8
		}

		Text {
			id: taskValue
			text: value
			font.family: heeboBold.name
			font.pixelSize: 44
			color: cursor ? "#121314" : "white"

			anchors.horizontalCenter: parent.horizontalCenter
			anchors.bottom: description.top
			anchors.bottomMargin: -10
		}
	}
}
