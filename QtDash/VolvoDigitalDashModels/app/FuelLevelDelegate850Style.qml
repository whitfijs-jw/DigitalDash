import QtQuick 2.15

Component {
    id: fuelLevelDelegate850


    Loader {
        source: "qrc:/Gauge.qml"
        asynchronous: true
        onLoaded: {
            item.minValue = gaugeMin
            item.maxValue = gaugeMax
            item.units = gaugeUnits
            item.highAlarm = gaugeMax
            item.lowAlarm = gaugeLowAlarm

            item.minAngle = -225
            item.maxAngle = -135

            item.height = smallGaugeSize
            item.width = smallGaugeSize

            item.imageResource = "qrc:/gauge-faces-850/850_fuel_level.png"
            item.needleResource = "qrc:/needles/needle-740-940.png"

            item.needleColor = "red"

            item.needleWidth = smallGaugeSize * 0.05
            item.needleLength = smallGaugeSize * 0.50
            item.needleOffset = smallGaugeSize * .25 / 2

            item.significantDigits = 0

            item.needleCenterRadius = 0.25
        }

        Binding {
            target: item
            property: "value"
            value: currentValue
        }

        Binding {
            target: item
            property: "width"
            value: smallGaugeSize
        }

        Binding {
            target: item
            property: "height"
            value: smallGaugeSize
        }
    }
}
