import QtQuick 2.15

Item {
	id: _item
	FontLoader { id: heeboBold; source: "qrc:/font/heebo_bold.ttf" }

	width: rectangle.width
	height: rectangle.y + rectangle.height

	Text {
		id: taskText
		text: "Accelerometer"
		font.family: heeboBold.name
		font.pixelSize: 44
		color: "white"

		anchors.left: rectangle.left
		anchors.leftMargin: 20
	}

	Connections {
		target: viewModel
		function onLateralGChanged(value) {
			canvas.latG = value;
			canvas.requestPaint()
		}

		function onLongitudinalGChanged(value) {
			canvas.lonG = value;
			canvas.requestPaint()
		}
	}

	property int leftMargin: 30
	property int topMargin: -4

	Rectangle {
		id: rectangle
		width: 480
		height: 300
		anchors.top: taskText.bottom
		anchors.horizontalCenter: parent.horizontalCenter
		anchors.topMargin: 4
		color: "#121314"
		radius: 20

		Canvas {
			id: canvas
			property real latG: 0.0;
			property real lonG: 0.0;

			width: 260
			height: 260
			anchors.verticalCenter: parent.verticalCenter
			anchors.horizontalCenter: parent.horizontalCenter
			onPaint: function() {
				const ctx = getContext("2d");
				const width = canvas.width;
				const height = canvas.height;
				const x = width / 2;
				const y = height / 2;
				const radius = width / 4 - 2;

				ctx.clearRect(0, 0, width, height);

				ctx.strokeStyle = "#919191";
				ctx.lineWidth = 4;
				ctx.beginPath();
				ctx.moveTo(4, y);
				ctx.lineTo(width - 4, y);
				ctx.stroke();

				ctx.beginPath();
				ctx.moveTo(x, 4);
				ctx.lineTo(x, height - 4);
				ctx.stroke();

				ctx.strokeStyle = "white";
				ctx.font = "22px sans-serif";
				ctx.fillStyle = "white";

				for (let i=1; i<3; i++) {
					ctx.beginPath();
					ctx.arc(x, y, radius * i, 0, 2 * Math.PI);
					ctx.stroke();

					if (i < 4) {
						ctx.fillText(i, x + 5, y - radius * i + 20);
					}
				}

				let gy = x + lonG * radius;
				let gx = y + latG * radius;

				if(gx < 0) gx = 0;
				if(width < gx) gx = width;

				if(gy < 0) gy = height;
				if(height < gy) gy = height;

				ctx.beginPath();
				ctx.arc(gx, gy, 10, 0, 2 * Math.PI);
				ctx.fillStyle = "red";
				ctx.fill();
			}
		}
	}
}
