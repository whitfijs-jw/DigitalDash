import QtQuick 2.15
import QtQuick.Controls 2.15

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

    property string overlayImageSource: "qrc:/mainCluster/later-240-temp-fuel-overlay.png"
    property string gaugeImageResource: "qrc:/mainCluster/later-240-temp-fuel.png"

    property real needleLength: 0.4
    property real needleWidth: 0.02
    property real needleOffset: 0
    property string needleResource: "qrc:/needles/needle-240.png"

    property real offsetX: 0

    property real textXOffset: 0
    property real textOffset : 1 / 4.5
    property real textSize: 1 / 16.0

    property bool enableFuelText: false

    Image {
        z: 0;
        id: overlay
        source: overlayImageSource
        anchors.fill: parent
    }

    Image {
        z: 1;
        id: warningLight
        source: "qrc:mainCluster/temp_coolant_gas_can.png"
        anchors.fill: parent
        visible: fuelLevel < lowAlarm ? true : false
    }

    Gauge {
        id: coolant
        z: -1

        anchors.fill: parent

        value: tempCoolant.coolantTemp

        lowAlarm: 0
        highAlarm: tempCoolant.highAlarm

        maxValue: tempCoolant.maxCoolantTemp
        minValue: tempCoolant.minCoolantTemp

        minAngle: -205
        maxAngle: -155

        offsetX: tempCoolant.offsetX

        units: tempCoolant.units
        needleResource: tempCoolant.needleResource
        needleLength: tempCoolant.needleLength
        needleWidth: tempCoolant.needleWidth
        needleOffset: 0

        imageResource: gaugeImageResource

        textOffset: tempCoolant.textOffset
        textXOffset: -tempCoolant.textXOffset
        textSize: tempCoolant.textSize

    }

    Gauge {
        id: fuel
        z: -1
        anchors.fill: parent

        clockwise: false

        value: tempCoolant.fuelLevel
        units: "%"

        minValue: tempCoolant.minFuel
        maxValue: tempCoolant.maxFuel

        highAlarm: tempCoolant.maxFuel
        lowAlarm: tempCoolant.lowAlarm

        offsetX: -tempCoolant.offsetX

        minAngle: -27
        maxAngle: 25

        needleResource: tempCoolant.needleResource
        needleLength: tempCoolant.needleLength
        needleWidth: tempCoolant.needleWidth
        needleOffset: 0

        imageResource: ""

        textEnabled: tempCoolant.enableFuelText
        textOffset: tempCoolant.textOffset
        textXOffset: tempCoolant.textXOffset
        textSize: tempCoolant.textSize
    }
}

