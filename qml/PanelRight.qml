import QtQuick 2.15

Item {
    Connections {
        target: viewModel
        function onCoolantChanged(value) { coolantGuage.value = value; }
        function onAfrChanged(value) { afrGuage.value = value; }
        function onAdvanceChanged(value) { advanceGuage.value = value; }
    }

    width: coolantGuage.width
    height: 300

    Guage {
        objectName: "coolant"
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
        objectName: "afr"
        id: afrGuage

        width: 320
        anchors.top: coolantGuage.bottom
        anchors.right: parent.right
        anchors.topMargin: 20

        minimum: 8; maximum: 21.4
        decimals: 1

        label: "AFR"

        forceOne: false
        alignRight: true
    }

    Guage {
        objectName: "adv"
        id: advanceGuage

        width: 300
        anchors.top: afrGuage.bottom
        anchors.right: rightPanel.right
        anchors.topMargin: 20

        minimum: -50; maximum: 50
        decimals: 0

        label: "ADVANCE"
        units: "°"

        forceOne: false
        alignRight: true
    }
}
