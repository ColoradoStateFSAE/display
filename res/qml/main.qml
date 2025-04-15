import QtQuick 2.15
import QtQuick.Window 2.15
import QtGraphicalEffects 1.12

import "TaskSwitcher"
import "Error"

Window {
    visible: true
	FontLoader { id: gramBold; source: "qrc:/font/gram_bold.ttf" }

	property int chance: 0
	property bool neutral: false
	property bool estop: false
	property bool etc: false

	Connections {
		target: navigation
		function onChangeTaskSwitcher(enabled) {
			if(blurEnter.running || blurExit.running) return;
			if(taskSwitcherEnter.running || taskSwitcherEnter.running) return;

			if(enabled) {
				blurEnter.running = true;
				taskSwitcherEnter.running = true;
			} else {
				blurExit.running = true;
				taskSwitcherExit.running = true;
			}
		}
	}
	
	Connections {
		target: viewModel
		function onRpmChanged(value) {
			tachometer.value = value;
		}

		function onGearChanged(value) {
			if(chance === 0){
				if(gear.value !== value) {
					if(value > 0) {
						gear.text = value;
					}
					else if(neutral === true){
						gear.text = "N";
					}
					else {
						gear.text = "?"
					}
				}
			}
		}

		function onNeutralChanged(value) {
			if (value === 1) {
				neutral = true;
			}
			else {
				neutral = false;
			}
		}

		function onlateralGChanged(value){
			if (chance === 1){
				gear.text = value;
			}
		}

		function onEstopChanged(value){
			if (value === 1 && etc === false){
				estop.visible = true;
			}
			else {
				estop.visible = false;
			}
		}

		function onEtcChanged(value){
			if (value === 1){
				etc = true;
				etcError.visible = true;
			}
			else {
				etc = false;
				etcError.visible = false;
			}
		}

		function onEcuOffline(state) {ecuOffline.visible = state }
		function onShiftingSystemOffline(state) { shiftingSystemOffline.visible = state }
		function onShiftControllerOffline(state) {steeringOffline.visible = state}
	}

	Rectangle {
		id: dashboard
		anchors.fill: parent
		width: 800
		height: 480
		color: "black"

		Image {
			id: spheres
			source: "qrc:/image/spheres.png"
			anchors.centerIn: parent
			fillMode: Image.PreserveAspectFit
			opacity: 0.7
		}

		Rectangle {
			anchors.fill: parent
			gradient: Gradient {
				GradientStop { position: 0.5; color: "black" }
				GradientStop { position: 1.0; color: "transparent" }
			}
		}

		Rectangle {
			anchors.fill: parent
			color: "transparent"

			Tachometer {
				id: tachometer
				width: parent.width - 50
				y: 20
				anchors.horizontalCenter: parent.horizontalCenter
			}
		}

		PanelLeft {
			id: leftPanel
			anchors.left: parent.left
			anchors.leftMargin: 20
			y: 140

			transform: Rotation { origin.x: leftPanel.x; origin.y: leftPanel.y-200; angle: 24; axis { x: 0; y: 1; z: 0 } }
		}

		PanelRight {
			id: rightPanel
			anchors.right: parent.right
			anchors.rightMargin: 20
			y: 140

			transform: Rotation { origin.x: rightPanel.width; origin.y: rightPanel.y-200; angle: -24; axis { x: 0; y: 1; z: 0 } }
		}

		Text {
			id: gear
			y: 110
			text: "N"
			anchors.horizontalCenter: parent.horizontalCenter
			font.family: gramBold.name
			font.pixelSize: 180
			color: "white"
			renderType: Text.NativeRendering
		}

		ShiftingSystemOffline {
			id: shiftingSystemOffline
			anchors.bottom: parent.bottom
			anchors.horizontalCenter: parent.horizontalCenter
			anchors.bottomMargin: 10
		}

		EcuOffline {
			id: ecuOffline
			anchors.bottom: parent.bottom
			anchors.horizontalCenter: parent.horizontalCenter
			anchors.bottomMargin: 110
		}

		Estop {
			id: estop
			anchors.bottom: parent.bottom
			anchors.horizontalCenter: parent.horizontalCenter
			anchors.bottomMargin: 110
		}

		SteeringOffline {
			id: steeringOffline
			anchors.bottom: parent.bottom
			anchors.horizontalCenter: parent.horizontalCenter
			anchors.bottomMargin: 60
		}
		ETCError {
			id: etcError
			anchors.bottom: parent.bottom
			anchors.horizontalCenter: parent.horizontalCenter
			anchors.bottomMargin: 110
		}
	}

	FastBlur {
		id: blur
		visible: false
		anchors.fill: dashboard
		source: dashboard
		cached: true

		SequentialAnimation on radius {
			id: blurEnter;
			running: false
			onStarted: { blur.visible = true; }
			NumberAnimation { from: 0; to: 80; duration: 200 }
		}
		SequentialAnimation on radius {
			id: blurExit;
			running: false
			NumberAnimation { from: 80; to: 0; duration: 200 }
			onStopped: { blur.visible = false; }
		}
	}
	
	TaskSwitcher {
		id: taskSwitcher
		visible: false
		anchors.fill: parent

		SequentialAnimation on opacity {
			id: taskSwitcherEnter;
			running: false
			onStarted: { taskSwitcher.visible = true; }
			NumberAnimation { from: 0; to: 1; duration: 200 }
		}
		SequentialAnimation on opacity {
			id: taskSwitcherExit;
			running: false
			NumberAnimation { from: 1; to: 0; duration: 200 }
			onStopped: { taskSwitcher.visible = false; }
		}
	}

	Rectangle {
		anchors.fill: parent
		color: "black"
		opacity: 1

		NumberAnimation on opacity { from: 1; to: 0; duration: 700 }
	}
}
