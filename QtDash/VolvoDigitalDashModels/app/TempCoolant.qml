import QtQuick 2.15
import QtQuick.Extras 1.4
import QtQuick.Controls.Styles 1.4

Item
{
    id: tempCoolant
    property int maxCoolantTemp
    property int minCoolantTemp
    property int highAlarm

    property int maxFuel: 100
    property int minFuel: 0
    property int lowAlarm

    property real coolantTemp
    property real fuelLevel

    property string units

    Image {
        z: 0;
        source: "qrc:mainCluster/temp_coolant_overlay_small.png"
        anchors.fill: parent
        asynchronous: true
    }

    Image {
        z: -2;
        source: "qrc:mainCluster/temp_coolant.png"
        anchors.fill: parent
        asynchronous: true
    }

    Image {
        z: 1;
        source: "qrc:mainCluster/temp_coolant_gas_can.png"
        anchors.fill: parent
        visible: fuelLevel < lowAlarm ? true : false
        asynchronous: true
    }

    CircularGauge
    {
        id: gaugeCoolant

        value: tempCoolant.coolantTemp

        anchors.fill: parent
        z: -1

        maximumValue: tempCoolant.maxCoolantTemp
        minimumValue: tempCoolant.minCoolantTemp

        Rectangle
        {
            id: indexTextBox
            width: parent.width/2
            height: parent.height/1.2

            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter

            color: "transparent"
        }

        style: CircularGaugeStyle {
            maximumValueAngle: -65
            minimumValueAngle: -115

            tickmark: null
//            tickmarkStepSize: 10
            tickmarkLabel: null
            minorTickmark: null

            background: Rectangle {
                anchors.fill: parent
                color: "transparent"

                Text {
                    z: 3
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter

                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.verticalCenterOffset: outerRadius *  0.35

                    fontSizeMode: Text.Fit
                    font.pixelSize: outerRadius * 0.15

                    text: Number(tempCoolant.coolantTemp).toFixed(1).toLocaleString(Qt.locale("en_US")) + " " + units
                    color: tempCoolant.coolantTemp > tempCoolant.highAlarm ? "#ff7011" : "white"

                }
            }

            needle: Rectangle {
                y: - outerRadius * 0.3
                radius: outerRadius * 0.025
                implicitWidth: outerRadius * 1.05
                implicitHeight: outerRadius * 0.03
                antialiasing: true
                rotation: 90
                gradient: Gradient {
                        GradientStop { position: 0.25; color: "orange"}
                        GradientStop { position: 0.5; color: "white" }
                        GradientStop { position: 0.75; color: "orange" }
                }
            }

        }

        CircularGauge
        {
            id: gaugeFuel

            value: tempCoolant.fuelLevel

            anchors.fill: parent
            z: -1

            maximumValue: tempCoolant.maxFuel
            minimumValue: tempCoolant.minFuel

            style: CircularGaugeStyle {
                maximumValueAngle: 65
                minimumValueAngle: 115

                tickmark: null
                tickmarkLabel: null
                minorTickmark: null

                needle: Rectangle {
                    y: - outerRadius * 0.3
                    radius: outerRadius * 0.025
                    implicitWidth: outerRadius * 1.05
                    implicitHeight: outerRadius * 0.03
                    antialiasing: true
                    rotation: 90
                    gradient: Gradient {
                            GradientStop { position: 0.25; color: "orange"}
                            GradientStop { position: 0.5; color: "white" }
                            GradientStop { position: 0.75; color: "orange" }
                    }
                }
            }
        }


    }
}
