import QtQuick 2.15

Item {

	Connections {
		target: viewModel
		function onBatteryChanged(value) {
			batteryGuage.value = value;
		}
		function onTpsChanged(value) {
			tpsGuage.value = value;
		}

		function onAfrChanged(value) {
			afrGuage.value = value * 14.7;
		}
	}

	width: batteryGuage.width
	height: 300

	Guage {
		id: batteryGuage

		width: 340
		anchors.top: parent.top
		anchors.left: parent.left

		minimum: 11; maximum: 14
		decimals: 1
		error: batteryGuage.value <= 12.2

		units: "V"
		icon: "qrc:/icon/battery.png"
	}

	Guage {
		id: tpsGuage

		width: 320
		anchors.top: batteryGuage.bottom
		anchors.left: leftPanel.left
		anchors.topMargin: 20

		minimum: 0; maximum: 100
		decimals: 0

		label: "TPS"
		units: "%"
		forceOne: false
	}

	Guage {
		id: afrGuage

		width: 300
		anchors.top: tpsGuage.bottom
		anchors.left: parent.left
		anchors.topMargin: 20

		minimum: 8; maximum: 21.4
		decimals: 1

		label: "AFR"

		forceOne: false
	}
}
