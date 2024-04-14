import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    id: gauge

    property bool clockwise: true
    property real maxValue: 100
    property real minValue: 0
    property real value: 0
    property real internalValue: clockwise ? value : (maxValue - (value - minValue))
    property real angle: (internalValue <= initialValueOffset) ?
                           (initialValueOffset - minValue) / (maxValue - minValue) * (maxAngle - minAngle) + minAngle :
                           (internalValue - minValue) / (maxValue - minValue) * (maxAngle - minAngle) + minAngle;
    property string units: "F"
    property int lowAlarm: 0
    property int highAlarm: 0
    property int offset: 0
    property int offsetX: 0
    property int initialValueOffset: 0

    property int minAngle: -235
    property int maxAngle: 45

    property real needleWidth: parent.height * 0.03
    property real needleLength: parent.width * 0.6
    property real needleTipRadius: needleWidth
    property real needleOffset: parent.height * .20

    property real needleCenterRadius: 0.15

    property string imageResource
    property string needleResource: ":/../VolvoDigitalDashModels/app/needle-240.png"

    property color needleColor: "orange"

    property real textOffset:  parent.height / 2.0
    property real textSize: parent.height / 8
    property bool textEnabled: true
    property int significantDigits: 1

    property string topUnits: "F"
    property real topValue: 0
    property real topTextSize: parent.height / 16.0
    property real topTextOffset: parent.height / 4.0
    property bool topValueEnabled: false

    property real dir: RotationAnimation.Numerical

    width: smallGaugeSize
    height: smallGaugeSize

    function boundedAngle(angle, min, max) {
        if (angle > max) {
            angle = max;
        } else if (angle < min) {
            angle = min;
        }

        return angle;
    }

    Rectangle {
        anchors.fill: parent
        color: "transparent"

        Image {
            source: gauge.imageResource
            cache: true
            rotation: 0
            anchors.fill: parent
            mipmap: true
            z: -1
        }

        NeedleCenter {
            id: needleCenter
            size: needleCenterRadius * parent.width
            x: parent.width / 2 + offsetX
            y: parent.height / 2 + offset
            antialiasing: true
            smooth: true

            transform: [
                Rotation {
                    angle: gauge.angle > gauge.maxAngle ?
                               gauge.maxAngle : (gauge.angle < minAngle) ?
                                   gauge.minAngle : gauge.angle
                    origin.x: 0
                    origin.y: 0

                    Behavior on angle {
                        RotationAnimation {
                            duration: 150
                            direction: gauge.dir
                        }
                    }
                }
            ]
        }

        Image {
            id: needle

            x: parent.width / 2 + offsetX
            y: parent.height / 2 + offset
            width: gauge.needleLength
            height: gauge.needleWidth

            antialiasing: true
            smooth: true
            source: needleResource

            transform: [
                Translate {
                    y: -needle.height / 2
                    x: -needleOffset
                },

                Rotation {
                    angle: gauge.angle > gauge.maxAngle ?
                               gauge.maxAngle : (gauge.angle < minAngle) ?
                                   gauge.minAngle : gauge.angle
                    origin.x: 0
                    origin.y: 0

                    Behavior on angle {
                        RotationAnimation {
                            duration: 150
                            direction: gauge.dir
                        }
                    }
                }
            ]
        }

        Text {

            id: valueText

            visible: textEnabled

            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            anchors.horizontalCenterOffset: 0

            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            anchors.verticalCenterOffset: gauge.textOffset

            fontSizeMode: Text.Fit
            font.pixelSize: gauge.textSize

            text: Number(gauge.value).toFixed(significantDigits).toLocaleString(Qt.locale("en_US")) + " " + units
            color: ( (gauge.value < gauge.lowAlarm)  || (gauge.value > gauge.highAlarm))
                   ? "#ff7011" : "white"
        }

        Text {

            id: topValueText

            visible: topValueEnabled

            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            anchors.horizontalCenterOffset: 0

            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            anchors.verticalCenterOffset: gauge.topTextOffset

            fontSizeMode: Text.Fit
            font.pixelSize: gauge.topTextSize

            text: Number(gauge.topValue).toFixed(1).toLocaleString(Qt.locale("en_US")) + " " + gauge.topUnits
            color: "white"
        }
    }

}

/*##^##
Designer {
    D{i:0;formeditorZoom:3;height:140;width:140}D{i:2}D{i:3}D{i:5}D{i:12}D{i:1}
}
##^##*/
