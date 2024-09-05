import QtQuick 2.15

Item {
	FontLoader { id: gramBold; source: "qrc:/font/gram_bold.ttf" }

	width: 340
	height: iconImage.y + iconImage.height

	property real value: 12
	property real minimum: 10
	property real maximum: 12
	property real decimals: 1
	property string icon: ""
	property string label: ""
	property string units: ""
	property bool forceOne: true
	property bool error: false

	property int n: 12
	property real margin: 6
	property bool alignRight: false

	Row {
		id: guage
		width: parent.width + margin
		height: 16
		spacing: margin

		Repeater {
			model: n
			Rectangle {
				id: rectangle
				width: parent.width / n - margin
				height: parent.height

				property color colorActive: "#00ff5a"
				property color colorError: "#FF3A45"
				property color colorInactive: "#2d2d3f"

				function normalize(value, min, max) {
					return (value - min) / (max - min)
				}

				color: {
					var active = Math.round(n * normalize(value, minimum, maximum)) - 1
					if(active < 0 && forceOne) active = 0

					if(index <= active) {
						if(error) return colorError
						return colorActive
					} else {
						return colorInactive
					}
				}
			}
		}
	}

	Image {
		id: iconImage
		source: icon
		width: label != "" ? labelText.width : height
		height: 44

		anchors.left: parent.left
		anchors.top: guage.bottom
		anchors.topMargin: 6

		LayoutMirroring.enabled: alignRight

		Text {
			id: labelText

			anchors.verticalCenter: iconImage.verticalCenter
			anchors.left: iconImage.left

			text: label
			font.family: gramBold.name
			font.pixelSize: 46
			font.letterSpacing: 4
			color: "white"
		}
	}

	Item {
		anchors.verticalCenter: iconImage.verticalCenter
		anchors.left: iconImage.right


		width: valueText.width + unitsText.anchors.leftMargin + unitsText.width
		height: valueText.height

		anchors.leftMargin: 18

		LayoutMirroring.enabled: alignRight
		LayoutMirroring.childrenInherit: false

		Text {
			id: valueText
			text: {
				var multiplier = Math.pow(10, decimals);
				return (Math.round(value * multiplier) / multiplier).toFixed(decimals);
			}
			font.family: gramBold.name
			font.pixelSize: 60
			font.letterSpacing: 4
			color: "white"
		}

		Text {
			id: unitsText
			text: units
			font.family: gramBold.name
			font.pixelSize: 42
			color: "white"

			anchors.left: valueText.right
			anchors.top: valueText.top

			anchors.leftMargin: 6
			anchors.topMargin: 4
		}
	}
}
