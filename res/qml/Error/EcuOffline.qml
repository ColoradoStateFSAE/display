import QtQuick 2.15

Item {
	FontLoader { id: heeboBold; source: "qrc:/font/heebo_bold.ttf" }

	Rectangle {
		color: "black"
		width: 800
		height: 480

		Image {
			id: icon
			source: "qrc:/icon/error.png"
			width: 160
			height: 160
			y: 140
			anchors.horizontalCenter: parent.horizontalCenter
		}

		Text {
			id: errorText
			text: "ECU OFFLINE"
			font.family: heeboBold.name
			font.pixelSize: 28
			color: "#AFAFAF"
			anchors.horizontalCenter: icon.horizontalCenter
			anchors.top: icon.bottom
			anchors.topMargin: 16
		}
	}
}
