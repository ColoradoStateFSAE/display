import QtQuick 2.15

Item {
	property int brendan: 0

	Connections {
		target: viewModel
		function onCoolantChanged(value) {
			coolantGuage.value = value;
		}

		function onClutchChanged(value) {
			if(brendan === 1) {
				clutchGauge.value = value - 10;
			}
			else{
				clutchGuage.value = value;
			}
		}

		function onOilChanged(value) {
			oilGuage.value = value / 6.89476;
		}
	}
	Connections {
		target: navigation
		function onBrendanChanged(value) {
			brendan = value;
		}
	}

	width: coolantGuage.width
	height: 300

	Guage {
		id: coolantGuage

		width: 340
		anchors.top: rightPanel.top
		anchors.right: rightPanel.right

		minimum: 150; maximum: 220
		decimals: 0
		error: 220 <= coolantGuage.value

		units: "°F"
		icon: "qrc:/icon/coolant.png"

		alignRight: true
	}

	Guage {
		id: clutchGuage

		width: 320
		anchors.top: coolantGuage.bottom
		anchors.right: rightPanel.right
		anchors.topMargin: 20

		minimum: 0; maximum: 100
		decimals: 0

		label: "CLUTCH"
		units: "%"
		forceOne: false
		alignRight: true
	}

	Guage {
		id: oilGuage

		width: 300
		anchors.top: clutchGuage.bottom
		anchors.right: rightPanel.right
		anchors.topMargin: 20

		minimum: 0; maximum: 150
		decimals: 0

		label: "OIL"
		units: "PSI"

		forceOne: false
		alignRight: true
	}
}
