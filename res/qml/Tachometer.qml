import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Shapes 1.15
import QtGraphicalEffects 1.12

Item {
	FontLoader { id: gramBold; source: "qrc:/font/gram_bold.ttf" }

	width: 800
	height: 140
	property real value: 14000
	property real valueMax: 14000
	property int n: 100
	property int margin: 3
	property int marginY: 30

	property real activeindex: (value / valueMax) * (n-1)

	Rectangle {
		width: parent.width - 70
		height: parent.height
		anchors.horizontalCenter: parent.horizontalCenter
		color: "transparent"

		Rectangle {
			y: 45
			width: parent.width
			height: 4
			color: "#2d2d3f"
			radius: 3
		}

		Row {
			id: tachometer
			width: parent.width + margin
			height: 38
			spacing: margin
			Repeater {
				model: n
                Rectangle {
                    id: rectangle
                    width: parent.width / n - margin
                    height: parent.height
                    property bool isActive: index < activeindex
                    color: isActive ? "#00ff5a" : "#2d2d3f"
                }
			}
		}

		Repeater {
			id: numbers
			model: 15

			delegate: Rectangle {
				id: rect
				x: index * (parent.width / 14) - width / 2
				y: 44

				width: 8
				height: 12
				color: "white"
				radius: 3

				visible: index % 2 == 0

				property real rpmFocus: Math.abs((index*1000 - value) / valueMax)

				Text {
					id: number
					x: parent.width / 2 - width / 2
					y: 18 - height / 5

					text: index
					font.family: gramBold.name

					visible: index % 2 == 0

					transform: Scale {
						property real scaleFactor: {
							var rpmSize = 2 * (1 - 2.6*rpmFocus)
							if(rpmSize < 1) rpmSize = 1
							return rpmSize
						}
						xScale: scaleFactor
						yScale: scaleFactor
						origin.x: number.width / 2
						origin.y: number.height / 4.5
					}
					font.pixelSize: 36
					color: "white"
					opacity: {
						var c = 1-2*rpmFocus
						if(c <= 0.4) c = 0.4
						return c
					}
				}
			}
		}

		RectangularGlow {
			anchors.fill: dial
			glowRadius: 14
			opacity: 0.5
			color: "black"
			cornerRadius: 4
		}

		Rectangle {
			id: dial
			width: 6
			height:tachometer.height
			x: parent.width * value/valueMax - width/2
			color: "white"
			radius: 3
		}
	}
}
