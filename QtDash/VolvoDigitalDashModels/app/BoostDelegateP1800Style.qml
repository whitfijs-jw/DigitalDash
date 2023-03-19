import QtQuick 2.15

Component {
    id: boostDelegateP1800

    Loader {
        source: "qrc:/Gauge.qml"
        asynchronous: true
        onLoaded: {
            item.minValue = -20
            item.maxValue = 20
            item.units = gaugeUnits
            item.highAlarm = gaugeHighAlarm
            item.lowAlarm = gaugeLowAlarm
            item.initialValueOffset = gaugeMin

            item.minAngle = -145
            item.maxAngle = -35

            item.height = smallGaugeSize
            item.width = smallGaugeSize

            item.imageResource = "qrc:/gauge-faces-p1800/boost-p1800.png"
            item.needleResource = "qrc:/needles/needle-rsport.png"

            item.needleWidth = smallGaugeNeedleWidth240
            item.needleLength = item.width * 0.375
            item.needleOffset = 0

            item.offset = 0

            item.textSize = item.width * 0.1
            item.significantDigits = 2

            item.needleCenterRadius = 0
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
