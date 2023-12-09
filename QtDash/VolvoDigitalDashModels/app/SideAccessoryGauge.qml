import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    property string initialGauge: "boost";

    function getModel(name) {
        switch (name) {
        case "boost":
            return boostModel;
        case "oil temp":
            return oilTModel;
        case "oil pressure":
            return oilPModel;
        case "voltmeter":
            return voltMeterModel
        case "coolant temp":
            return coolantTempModel;
        case "fuel level":
            return fuelLevelModel;
        default:
            return boostModel
        }
    }

    function getDelegateByName(name) {
        for (var i = 0; i < getNumOptions(currentStyle);i++ ) {
            if (name === currentModel.get(i).name) {
                return getDelegate(currentStyle, i);
            }
        }
        initialGauge = "boost";
        return getDelegate(currentStyle, 0);
    }

    function getDelegate(style, index) {
        switch (style) {
        case "240":
            return delegates240[index];
        case "740":
            return delegates740[index];
        case "p1800":
            return delegatesP1800[index];
        case "rSport":
            return delegatesRSport[index];
        case "s60r":
            return delegatesS60r[index];
        default:
            return delegates240[index];
        }
    }

    function getNumOptions(style) {
        switch (style) {
        case "240":
            return delegates240.length;
        case "740":
            return delegates740.length;
        case "p1800":
            return delegatesP1800.length;
        case "rSport":
            return delegatesRSport.length;
        case "s60r":
            return delegatesS60r.length;
        default:
            return delegates240.length;
        }
    }

    Rectangle {
        id: gaugeContainer
        anchors.fill: parent
        color: "transparent"
        z:0

        ListView {
            id: gaugeTop
            model: getModel(initialGauge)
            delegate: getDelegateByName(initialGauge)
            z:0
        }

        Image {
            anchors.horizontalCenter: gaugeContainer.horizontalCenter
            anchors.verticalCenter: gaugeContainer.verticalCenter
            source: "qrc:/gauge-faces-p1800/center-cover-medium-p1800.png"
            visible: {currentStyle === "p1800"}
        }

        MouseArea {
            anchors.fill: parent
            onPressAndHold: {
                selectionMenu.visible = true;
            }
            Component {
                id: listOptionDelegate
                Rectangle {
                    id: button
                    width: parent.width
                    height: parent.width / getNumOptions(currentStyle)
                    color: "white"
                    Text {
                        id: nameText
                        text: name
                        anchors.centerIn: parent
                    }
                    MouseArea {
                        anchors.fill: parent
                        onPressed: {
                            initialGauge = name;
                            selectionMenu.visible = false;
                        }
                    }
                }

            }
            ListView {
                id: selectionMenu
                anchors.fill: parent
                model: currentModel
                delegate: listOptionDelegate
                z: 100
                visible: false
            }
        }
    }
}
