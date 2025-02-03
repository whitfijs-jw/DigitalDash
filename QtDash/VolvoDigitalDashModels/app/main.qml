import QtQuick 2.15
import QtQuick.Window 2.15

Window {
    id: rootWindow
    objectName: "rootWindow"
    visible: true
    width: 1280
    height: 480

    title: qsTr("Lolvo")

    property url initialScreen: "qrc:/Original240Layout.qml"
    property real initialScreenSpeedoMaxMph: 120
    property real initialScreenSpeedoMaxKph: 220

    SideAccessoryScreen {
        id: accessoryScreen
        objectName: "accessoryScreen"
        currentStyle: "240"
    }
    // default blinker size
    property int blinkerSize: rootWindow.height * (50/480)
    property int blinkerTopMargin: rootWindow.height / 48

    property var msg: [
        "You thought this\nwas going to work?",
        "Come back later...",
        "Just crush this\nthing already",
        "Can this thing\neven hit 60?",
        "Have fun with your\nM cam",
        "I bet you could get\n$500 on BaT for this",
        "404 Not Found",
        "I heard you like\nFWD Volvos",
        "How many neutrals\ndoes your trans have?",
        "Is a rear main seal\nsupposed to leak\nthat much?",
        "MOTOBOTO!",
        "Highway speeds\nmight not be\nan option for you",
    ]

    function boundedAngle(angle, min, max) {
        if (angle > max) {
            angle = max;
        } else if (angle < min) {
            angle = min;
        }

        return angle;
    }

    function advance(forward) {
        gaugeItem.advanceScreen(forward);
    }

    Component {
        id: leftBlinkerDelegate

        Loader {
            source: "qrc:/Blinker.qml"
            asynchronous: true
            onLoaded: {
                item.flipped = false
                item.width = blinkerSize
                item.height = 3 * blinkerSize / 4
            }

            Binding {
                target: item
                property: "on"
                value: indicatorOn
            }

            Binding {
                target: item
                property: "width"
                value: blinkerSize
            }

            Binding {
                target: item
                property: "height"
                value: 3 * blinkerSize / 4
            }
        }
    }

    Component {
        id: rightBlinkerDelegate

        Loader {
            source: "qrc:/Blinker.qml"
            asynchronous: true
            onLoaded: {
                item.flipped = true
                item.width = blinkerSize
                item.height = 3 * blinkerSize / 4
            }

            Binding {
                target: item
                property: "on"
                value: indicatorOn
            }

            Binding {
                target: item
                property: "width"
                value: blinkerSize
            }

            Binding {
                target: item
                property: "height"
                value: 3 * blinkerSize / 4
            }
        }
    }

    Item {
        id: loading
        anchors.fill: parent
        rotation: SCREEN_ROTATION_ANGLE
        Rectangle {
            anchors.fill: parent
            color: "black"

            Text {
                id: loadText
                text: qsTr(rootWindow.msg[Math.floor(Math.random() * rootWindow.msg.length)])
                horizontalAlignment: Text.AlignHCenter
                fontSizeMode: Text.Fit
                font.pixelSize: 100
                color: "white"
                onVisibleChanged: {
                    console.count("hidden");
                    var index = Math.floor(Math.random() * rootWindow.msg.length);
                    var txt = qsTr(rootWindow.msg[index]);
                    if (loadText.text === txt) {
                        if (++index > rootWindow.msg.length) {
                            index = 0
                        }

                        loadText.text = qsTr(rootWindow.msg[index]);
                    } else {
                        loadText.text = txt;
                    }
                }
                anchors.centerIn: parent
            }
        }
    }

    Item {
        id: gaugeItem
        anchors.fill: parent
        focus: true
        rotation: SCREEN_ROTATION_ANGLE
        property bool initialLoad: true
        antialiasing: true
        smooth: true
        property int screen: 0

        Loader {
            id: currentGauge
            anchors.fill: parent
            source: rootWindow.initialScreen
            asynchronous: true
            visible: false
            onStatusChanged: {
                if (status == Loader.Ready) {
                    console.log("Loader Ready")
                    if (!gaugeItem.initialLoad) {
                        visible = true;
                        loadText.visible = false;
                    } else {
                        bootTimer.start();
                        gaugeItem.initialLoad = false

                        // setup the speedometer for the initial screen
                        if (speedoModel.units === "mph") {
                            speedoModel.setMaxValue(rootWindow.initialScreenSpeedoMaxMph);
                        } else {
                            speedoModel.setMaxValue(rootWindow.initialScreenSpeedoMaxKph)
                        }
                    }
                } else if (status == Loader.Loading) {
                    currentGauge.visible = false;
                    loadText.visible = true;
                    console.log("Loader Loading")
                }
            }
            Binding {
                target: item
                property: "width"
                value: rootWindow.width
            }
            Binding {
                target: item
                property: "height"
                value: rootWindow.height
            }
        }

        Timer {
            id: bootTimer
            interval: 2000
            running: false
            repeat: false
            onTriggered: {
                currentGauge.visible = true;
                loadText.visible = false;
            }
        }

        function advanceScreen(forward) {
            if (forward) {
                if (++screen > 10) {
                    screen = 0;
                }
            } else {
                if (--screen < 0) {
                    screen = 10;
                }
            }

            switch (screen) {
                case 0:
                    currentGauge.source = "qrc:/BigTachCenter.qml";
                    if (speedoModel.units === "mph") {
                        speedoModel.setMaxValue(120);
                    } else {
                        speedoModel.setMaxValue(220)
                    }

                    rpmModel.setMaxRpm(7000);
                    rpmModel.setRedLine(6000);

                    accessoryScreen.currentStyle = "240";
                    warningLightBar.item.showLights = true;

                    break;
                case 1:
                    currentGauge.source = "qrc:/BigTachLeft.qml";
                    if (speedoModel.units === "mph") {
                        speedoModel.setMaxValue(120);
                    } else {
                        speedoModel.setMaxValue(220)
                    }

                    rpmModel.setMaxRpm(7000);
                    rpmModel.setRedLine(6000);

                    accessoryScreen.currentStyle = "240";
                    warningLightBar.item.showLights = true;
                    break;
                case 2:
                    currentGauge.source = "qrc:/Original240Layout.qml";
                    if (speedoModel.units === "mph") {
                        speedoModel.setMaxValue(120);
                    } else {
                        speedoModel.setMaxValue(220)
                    }

                    rpmModel.setMaxRpm(7000);
                    rpmModel.setRedLine(6000);

                    accessoryScreen.currentStyle = "240";
                    warningLightBar.item.showLights = true;
                    break;
                case 3:
                    currentGauge.source = "qrc:/Original740Layout.qml"
                    if (speedoModel.units === "mph") {
                        speedoModel.setMaxValue(140);
                    } else {
                        speedoModel.setMaxValue(225.308)
                    }

                    rpmModel.setMaxRpm(7000);
                    rpmModel.setRedLine(5500);

                    accessoryScreen.currentStyle = "740";
                    warningLightBar.item.showLights = true;
                    break;
                case 4:
                    currentGauge.source = "qrc:/Original240LayoutClock.qml";
                    if (speedoModel.units === "mph") {
                        speedoModel.setMaxValue(120);
                    } else {
                        speedoModel.setMaxValue(220)
                    }

                    rpmModel.setMaxRpm(7000);
                    rpmModel.setRedLine(6000);

                    accessoryScreen.currentStyle = "240";
                    warningLightBar.item.showLights = true;
                    break;
                case 5:
                    currentGauge.source = "qrc:/Original850R.qml"
                    if (speedoModel.units === "mph") {
                        speedoModel.setMaxValue(140);
                    } else {
                        speedoModel.setMaxValue(225.308)
                    }

                    rpmModel.setMaxRpm(7000);
                    rpmModel.setRedLine(5500);

                    accessoryScreen.currentStyle = "740";
                    warningLightBar.item.showLights = true;
                    break;
                case 6:
                    currentGauge.source = "qrc:/OriginalRSportLayout.qml"
                    if (speedoModel.units === "mph") {
                        speedoModel.setMaxValue(130);
                    } else {
                        speedoModel.setMaxValue(200)
                    }

                    rpmModel.setMaxRpm(8000);
                    rpmModel.setRedLine(6500);

                    accessoryScreen.currentStyle = "rSport";
                    warningLightBar.item.showLights = true;
                    break;
                case 7:
                    currentGauge.source = "qrc:/Original544Layout.qml"
                    if (speedoModel.units === "mph") {
                        speedoModel.setMaxValue(120);
                    } else {
                        speedoModel.setMaxValue(193.121)
                    }
                    accessoryScreen.currentStyle = "240";
                    warningLightBar.item.showLights = true;
                    break;
                case 8:
                    currentGauge.source = "qrc:/OriginalP1800Layout.qml"
                    if (speedoModel.units === "mph") {
                        speedoModel.setMaxValue(120);
                    } else {
                        speedoModel.setMaxValue(200)
                    }

                    rpmModel.setMaxRpm(7000);
                    rpmModel.setRedLine(6000);

                    accessoryScreen.currentStyle = "p1800";
                    warningLightBar.item.showLights = true;
                    break;
                case 9:
                    currentGauge.source = "qrc:/OriginalEarly240Layout.qml"
                    if (speedoModel.units === "mph") {
                        speedoModel.setMaxValue(130);
                    } else {
                        speedoModel.setMaxValue(200)
                    }

                    rpmModel.setMaxRpm(7000);
                    rpmModel.setRedLine(5500);

                    accessoryScreen.currentStyle = "240";
                    warningLightBar.item.showLights = false;
                    break;
                case 10:
                    currentGauge.source = "qrc:/Original140RallyeLayout.qml"
                    if (speedoModel.units === "mph") {
                        speedoModel.setMaxValue(130);
                    } else {
                        speedoModel.setMaxValue(200)
                    }

                    rpmModel.setMaxRpm(8000);
                    rpmModel.setRedLine(6500);

                    accessoryScreen.currentStyle = "140rallye";
                    warningLightBar.item.showLights = true;
                    break;
                default:
                    break;
                }
        }

        Keys.onPressed: {
            if (!event.isAutoRepeat) {
                switch (event.key) {
                case Qt.Key_Left:
                    advanceScreen(false);
                    break;
                case Qt.Key_Right:
                    advanceScreen(true);
                    break;
                }

                event.accepted = true;
            }
        }

        Loader {
            id: warningLightBar
            source: "WarningLightBar.qml"
            asynchronous: true
            anchors.fill: parent
        }
    }
}
