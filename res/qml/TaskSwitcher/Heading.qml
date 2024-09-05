import QtQuick 2.15

Item {
	property string headingColor: "#3d4043"
	property string icon
	property int taskId
	property bool cursor: cursorTask === taskId ? true : false

	width: heading.width
	height: heading.height

	Rectangle {
		id: heading
		width: 70
		height: heading.width
		color: headingColor
		radius: height / 2

		Image {
			id: centeredImage
			source: icon
			anchors.fill: parent
			anchors.margins: 16
			width: heading.height
			height: heading.height
		}

		transform: Scale {
			id: scaleTransform
			origin.x: heading.width / 2
			origin.y: heading.height / 2
		}
	}

	PropertyAnimation {
		target: scaleTransform
		properties: "xScale, yScale"
		to: 1
		duration: 30
		easing.type: Easing.InOutQuad
		running: cursor
	}

	PropertyAnimation {
		target: scaleTransform
		properties: "xScale, yScale"
		to: 0.6
		duration: 30
		easing.type: Easing.InOutQuad
		running: !cursor
	}
}
