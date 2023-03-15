import QtQuick 2.15

Component {
    id: boostDelegate

    Loader {
        source: "qrc:/Gauge.qml"
        asynchronous: true
        onLoaded: {
            item.minValue = gaugeMin
            item.maxValue = gaugeMax
            item.units = gaugeUnits
            item.highAlarm = gaugeHighAlarm
            item.lowAlarm = gaugeMin
            item.initialValueOffset = gaugeMin

            item.minAngle = -226
            item.maxAngle = 45

            item.height = smallGaugeSize
            item.width = smallGaugeSize

            item.imageResource = "qrc:/accCluster/boost_black_no_numbers.png"

            item.needleColor = "orange"

            item.needleWidth = smallGaugeNeedleWidth240
            item.needleLength = smallGaugeSize * 0.55
            item.needleOffset = smallGaugeSize * .25 / 2

            item.needleCenterRadius = 0.15
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