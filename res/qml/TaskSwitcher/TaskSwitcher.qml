import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Shapes 1.15
import QtGraphicalEffects 1.12
import navigation 1.0

Item {
	FontLoader { id: heeboBold; source: "qrc:/font/heebo_bold.ttf" }

	property int cursorTask: 0
	property bool selected: false;

	Connections {
		target: navigation
		function onCursorChanged(value, editing) {
			if(blurEnter.running || blurExit.running) return;
			if(taskSwitcherEnter.running || taskSwitcherEnter.running) return;
			
			cursorTask = value;
			selected = editing;
		}
	}

	Rectangle {
		width: 800
		height: 480
		color: "black"
		opacity: 0.3
	}

	property int topSpacing: 70

	About {
		anchors.horizontalCenter: parent.horizontalCenter
		anchors.top: parent.top
		anchors.topMargin: topSpacing

		visible: cursorTask === Navigation.ABOUT
				 ? true : false
	}

	ShiftTiming {
		anchors.horizontalCenter: parent.horizontalCenter
		anchors.top: parent.top
		anchors.topMargin: topSpacing

		tasks: [
			Navigation.SHIFT,
			Navigation.UP_DELAY,
			Navigation.DOWN_DELAY,
			Navigation.OUTPUT,
			Navigation.TIMEOUT
		]
	}

	Clutch {
		anchors.horizontalCenter: parent.horizontalCenter
		anchors.top: parent.top
		anchors.topMargin: topSpacing

		tasks: [
			Navigation.CLUTCH,
			Navigation.POSITION,
			Navigation.START,
			Navigation.END,
			Navigation.FRICTION,
			Navigation.AUTO_LAUNCH
		]
	}

	Heading {
		id: exit
		anchors.left: parent.left
		anchors.bottom: parent.bottom
		anchors.leftMargin: 60
		anchors.bottomMargin: 60
		icon: "qrc:/icon/close.png"
		taskId: Navigation.EXIT
	}

	Heading {
		id: about
		anchors.left: parent.left
		anchors.bottom: exit.top
		anchors.leftMargin: 60
		anchors.bottomMargin: 10
		headingColor: "#0D8036"
		icon: "qrc:/icon/about.png"
		taskId: Navigation.ABOUT
	}

	Heading {
		id: shift
		anchors.left: parent.left
		anchors.bottom: about.top
		anchors.leftMargin: 60
		anchors.bottomMargin: 10
		headingColor: "#007aff"
		icon: "qrc:/icon/shift.png"
		taskId: Navigation.SHIFT
	}

	Heading {
		id: clutch
		anchors.left: parent.left
		anchors.bottom: shift.top
		anchors.leftMargin: 60
		anchors.bottomMargin: 10
		headingColor: "#ff2d55"
		icon: "qrc:/icon/servo.png"
		taskId: Navigation.CLUTCH
	}
}
