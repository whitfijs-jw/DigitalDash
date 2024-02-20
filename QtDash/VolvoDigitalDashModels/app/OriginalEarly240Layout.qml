import QtQuick 2.15

Item {
    Rectangle {
        width: 1280
        height: 480
        color: "transparent"

        Rectangle {
            id: speedoContainer
            width: speedoSize
            height: speedoSize
            anchors.right: tachContainer.left
            anchors.rightMargin: parent.width * 0.035
            anchors.verticalCenter: parent.verticalCenter
            anchors.verticalCenterOffset: 0
            color: "transparent"

            /* Rpm: */
            ListView {
                model: speedoModel
                delegate: speedoDelegateEarly240
            }

        }

        Rectangle {
            id: tachContainer
            width: tachSize
            height: tachSize
            color: "transparent"
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom
            anchors.bottomMargin: tachSize * 0.1

            /* Rpm: */
            ListView {
                model: rpmModel
                delegate: tachoDelegateEarly240Style
            }

        }

        Rectangle {
            id: tempFuelContainer
            width: tempFuelSize
            height: tempFuelSize
            anchors.left: tachContainer.right
            anchors.leftMargin: parent.width * 0.035
            anchors.verticalCenter: parent.verticalCenter
            color: "transparent"

            /* Rpm: */
            ListView {
                model: tempFuelModel
                delegate: tempFuelDelegateEarly240
            }

        }

        Rectangle {
            id: leftBlinker
            width: blinkerSize
            anchors.top: speedoContainer.top
            anchors.topMargin: 10
            anchors.right: parkingBrakeLight.left
            anchors.rightMargin: warningLightHorizontalMargin
            color: "transparent"

            ListView {
                model: leftBlinkerModel
                delegate: leftBlinkerDelegate
            }
        }

        Rectangle {
            id: parkingBrakeLight
            width: warningLightWideWidth
            height: warningLightHeight
            anchors.top: speedoContainer.top
            anchors.topMargin: 10
            anchors.right : highBeamLight.left
            anchors.rightMargin: warningLightHorizontalMargin
            color: "transparent"

            ListView {
                model: parkingBrakeLightModel
                delegate: parkingBrakeLightDelegate
                anchors.fill: parent
            }
        }

        Rectangle {
            id: highBeamLight
            width: warningLightWidth
            height: warningLightHeight
            anchors.top: speedoContainer.top
            anchors.topMargin: 10
            anchors.horizontalCenter: tachContainer.horizontalCenter
            color: "transparent"

            ListView {
                model: highBeamLightModel
                delegate: highBeamLightDelegate
                anchors.fill: parent
            }
        }

        Rectangle {
            id: brakeFailureLight
            width: warningLightWideWidth
            height: warningLightHeight
            anchors.top: speedoContainer.top
            anchors.topMargin: 10
            anchors.left : highBeamLight.right
            anchors.leftMargin: warningLightHorizontalMargin
            color: "transparent"

            ListView {
                model: brakeFailureLightModel
                delegate: brakeFailureLightDelegate
                anchors.fill: parent
            }
        }

        Rectangle {
            id: rightBlinker
            width: blinkerSize
            anchors.top: speedoContainer.top
            anchors.topMargin: 10
            anchors.left : brakeFailureLight.right
            anchors.leftMargin: warningLightHorizontalMargin
            color: "transparent"

            ListView {
                model: rightBlinkerModel
                delegate: rightBlinkerDelegate
            }
        }

        Rectangle {
            id: oilWarningLight
            height: warningLightHeight
            width: warningLightWidth
            anchors.horizontalCenter: tempFuelContainer.horizontalCenter
            anchors.horizontalCenterOffset: -(warningLightWidth + warningLightHorizontalMargin) / 2
            anchors.top: tempFuelContainer.top
            anchors.topMargin: 10
            color: "transparent"

            ListView {
                model: oilWarningLightModel
                delegate: oilWarningLightDelegate
                anchors.fill: parent
            }
        }

        Rectangle {
            id: batteryWarningLight
            height: warningLightHeight
            width: warningLightWidth
            anchors.horizontalCenter: tempFuelContainer.horizontalCenter
            anchors.horizontalCenterOffset: (warningLightWidth + warningLightHorizontalMargin) / 2
            anchors.top: tempFuelContainer.top
            anchors.topMargin: 10
            color: "transparent"

            ListView {
                model: batteryWarningLightModel
                delegate: batteryWarningLightDelegate
                anchors.fill: parent
            }
        }


    }
}
