import QtQuick 2.15

Component {
    id: coolantS60RDelegate

    Loader {
        source: "qrc:/Gauge.qml"
        asynchronous: true
        onLoaded: {
            item.minValue = gaugeMin
            item.maxValue = gaugeMax
            item.units = gaugeUnits
            item.highAlarm = gaugeHighAlarm
            item.lowAlarm = gaugeLowAlarm

            item.minAngle = -130
            item.maxAngle = -50

            item.height = smallGaugeSize
            item.width = smallGaugeSize

            item.imageResource = "qrc:/gauge-faces-s60r/s60r_coolant_temp.png"
            item.needleResource = "qrc:/needles/needle_s60r.png"

            item.needleCenterImageSize = speedoSize / 5
            item.needleCenterUseImage = true
            item.needleCenterImageResource = "qrc:/needles/needle_center_s60r.png"

            item.needleWidth = smallGaugeSize * 0.05
            item.needleLength = smallGaugeSize * 0.7
            item.needleOffset = smallGaugeSize * 0.175
            item.offset = smallGaugeSize / 4

            item.significantDigits = 0
            item.textSize = speedoSize / 20
            item.textOffset = smallGaugeSize * 0.6

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
