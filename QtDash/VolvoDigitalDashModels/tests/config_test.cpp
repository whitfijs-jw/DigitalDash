#include <config_test.h>

void ConfigTest::testLoadSensorChannelConfig() {
    QFETCH(QString, config);
    QFETCH(bool, result);

    Config * testConfig = new Config(this, config);

    if (testConfig != nullptr) {
        QCOMPARE(testConfig->isSensorConfigValid(), result);
    } else {
        QFAIL("Config not loaded.");
    }
}

void ConfigTest::testLoadSensorChannelConfig_data() {
    QTest::addColumn<QString>("config");
    QTest::addColumn<bool>("result");

    QSettings * dummyConfig = new QSettings("emptyConfig.ini", QSettings::IniFormat);

    dummyConfig->beginGroup(Config::SENSOR_CHANNEL_GROUP);
    dummyConfig->setValue(Config::COOLANT_TEMP_KEY, "");
    dummyConfig->setValue(Config::FUEL_LEVEL_KEY, "");
    dummyConfig->setValue(Config::OIL_PRESSURE_KEY, "");
    dummyConfig->setValue(Config::OIL_TEMP_KEY, "");
    dummyConfig->setValue(Config::MAP_SENSOR_KEY, "");
    dummyConfig->setValue(Config::AMBIENT_TEMP_KEY, "");
    dummyConfig->setValue(Config::DIMMER_VOLTAGE_KEY, "");
    dummyConfig->setValue(Config::FUSE8_12V_KEY, "");
    dummyConfig->endGroup();

    QTest::addRow("empty_config") << "emptyConfig.ini" << false;
    delete dummyConfig;

    QSettings * validConfig = new QSettings("validConfig.ini", QSettings::IniFormat);

    validConfig->beginGroup(Config::SENSOR_CHANNEL_GROUP);
    validConfig->setValue(Config::COOLANT_TEMP_KEY, 0);
    validConfig->setValue(Config::FUEL_LEVEL_KEY, 1);
    validConfig->setValue(Config::OIL_PRESSURE_KEY, 2);
    validConfig->setValue(Config::OIL_TEMP_KEY, 3);
    validConfig->setValue(Config::MAP_SENSOR_KEY, 4);
    validConfig->setValue(Config::AMBIENT_TEMP_KEY, 5);
    validConfig->setValue(Config::DIMMER_VOLTAGE_KEY, 6);
    validConfig->setValue(Config::FUSE8_12V_KEY, 7);
    validConfig->endGroup();

    QTest::addRow("valid_config") << "validConfig.ini" << true;
    delete validConfig;

    for (int i = 0; i < 8; i++) {
        QString configName;
        QTextStream(&configName) << "invalidValueConfig" << i << ".ini";
        QSettings * invalidValueConfig = new QSettings(configName, QSettings::IniFormat);

        invalidValueConfig->beginGroup(Config::SENSOR_CHANNEL_GROUP);
        invalidValueConfig->setValue(Config::COOLANT_TEMP_KEY, i == 0 ? -1 : 0);
        invalidValueConfig->setValue(Config::FUEL_LEVEL_KEY,i == 1 ? -1 : 1);
        invalidValueConfig->setValue(Config::OIL_PRESSURE_KEY, i == 2 ? -1 : 2);
        invalidValueConfig->setValue(Config::OIL_TEMP_KEY, i == 3 ? -1 : 3);
        invalidValueConfig->setValue(Config::MAP_SENSOR_KEY, i == 4 ? -1 : 4);
        invalidValueConfig->setValue(Config::AMBIENT_TEMP_KEY, i == 5 ? -1 : 5);
        invalidValueConfig->setValue(Config::DIMMER_VOLTAGE_KEY, i == 6 ? -1 : 6);
        invalidValueConfig->setValue(Config::FUSE8_12V_KEY, i == 7 ? -1 : 7);
        invalidValueConfig->endGroup();

        QTest::addRow(configName.toStdString().c_str()) << configName << false;
        delete invalidValueConfig;
    }
 }


void ConfigTest::testLoadDashLightsConfig() {
    QFETCH(QString, config);
    QFETCH(bool, result);

    Config * testConfig = new Config(this, config);

    QCOMPARE(testConfig->isDashLightConfigValid(), result);
}

void ConfigTest::testLoadDashLightsConfig_data() {
    QTest::addColumn<QString>("config");
    QTest::addColumn<bool>("result");

    QSettings * emptyConfig = new QSettings("emptyConfig.ini", QSettings::IniFormat);

    emptyConfig->beginGroup(Config::DASH_LIGHT_GROUP);
    emptyConfig->setValue(Config::OIL_PRESSURE_SW_KEY, "");
    emptyConfig->setValue(Config::OD_LAMP_KEY, "");
    emptyConfig->setValue(Config::HIGH_BEAM_KEY, "");
    emptyConfig->setValue(Config::BRAKE_FAILURE_KEY, "");
    emptyConfig->setValue(Config::BULB_FAILURE_KEY, "");
    emptyConfig->setValue(Config::CHARGING_LIGHT_KEY, "");
    emptyConfig->setValue(Config::BLINKER_LEFT_KEY, "");
    emptyConfig->setValue(Config::BLINKER_RIGHT_KEY, "");
    emptyConfig->setValue(Config::OD_LAMP_AUTO, "");
    emptyConfig->setValue(Config::CHECK_ENGINE_KEY, "");
    emptyConfig->setValue(Config::CONN_32_PIN3, "");
    emptyConfig->endGroup();

    QTest::addRow("empty_config") << "emptyConfig.ini" << false;
    delete emptyConfig;

    QSettings * validConfig = new QSettings("validConfig.ini", QSettings::IniFormat);

    validConfig->beginGroup(Config::DASH_LIGHT_GROUP);
    validConfig->setValue(Config::OIL_PRESSURE_SW_KEY, 0);
    validConfig->setValue(Config::OD_LAMP_KEY, 1);
    validConfig->setValue(Config::HIGH_BEAM_KEY, 2);
    validConfig->setValue(Config::BRAKE_FAILURE_KEY, 3);
    validConfig->setValue(Config::BULB_FAILURE_KEY, 4);
    validConfig->setValue(Config::CHARGING_LIGHT_KEY, 5);
    validConfig->setValue(Config::BLINKER_LEFT_KEY, 6);
    validConfig->setValue(Config::BLINKER_RIGHT_KEY, 7);
    validConfig->setValue(Config::OD_LAMP_AUTO, 8);
    validConfig->setValue(Config::CHECK_ENGINE_KEY, 9);
    validConfig->setValue(Config::CONN_32_PIN3, 10);
    validConfig->endGroup();

    QTest::addRow("valid_config") << "validConfig.ini" << true;
    delete validConfig;

    for (int i = 0; i < 8; i++) {
        QString configName;
        QTextStream(&configName) << "invalidValueConfig" << i << ".ini";
        QSettings * invalidValueConfig = new QSettings(configName, QSettings::IniFormat);

        invalidValueConfig->beginGroup(Config::DASH_LIGHT_GROUP);

        invalidValueConfig->setValue(Config::OIL_PRESSURE_SW_KEY, i == 0 ? -1 : 0);
        invalidValueConfig->setValue(Config::OD_LAMP_KEY, i == 1 ? -1 : 1);
        invalidValueConfig->setValue(Config::HIGH_BEAM_KEY, i == 2 ? -1 : 2);
        invalidValueConfig->setValue(Config::BRAKE_FAILURE_KEY, i == 3 ? -1 : 3);
        invalidValueConfig->setValue(Config::BULB_FAILURE_KEY, i == 4 ? -1 : 4);
        invalidValueConfig->setValue(Config::CHARGING_LIGHT_KEY, i == 5 ? -1 : 5);
        invalidValueConfig->setValue(Config::BLINKER_LEFT_KEY, i == 6 ? -1 : 6);
        invalidValueConfig->setValue(Config::BLINKER_RIGHT_KEY, i == 7 ? -1 : 7);
        invalidValueConfig->setValue(Config::OD_LAMP_AUTO, i == 8 ? -1 : 8);
        invalidValueConfig->setValue(Config::CHECK_ENGINE_KEY, i == 9 ? -1 : 9);
        invalidValueConfig->setValue(Config::CONN_32_PIN3, i == 10 ? -1 : 10);

        invalidValueConfig->endGroup();

        QTest::addRow(configName.toStdString().c_str()) << configName << false;

        delete invalidValueConfig;
    }
}

void ConfigTest::testLoadMapConfig() {
    QFETCH(QString, config);
    QFETCH(bool, result);
    QFETCH(qreal, pressure_0V);
    QFETCH(qreal, pressure_5V);
    QFETCH(QString, units);

    Config * testConfig = new Config(this, config);

    // check if the settings are valid
    QCOMPARE(testConfig->getMapSensorConfig().isValid(), result);

    // now check the rest if the results should be good
    if (result) {
        QCOMPARE(testConfig->getMapSensorConfig().p0V, pressure_0V);
        QCOMPARE(testConfig->getMapSensorConfig().p5V, pressure_5V);

        auto configUnits = testConfig->getMapSensorConfig().units;
        QString compare;
        if (configUnits == Units::PressureUnits::KPA) {
            compare = Units::UNITS_KPA;
        } else if (configUnits == Units::PressureUnits::BAR) {
            compare = Units::UNITS_BAR;
        } else if (configUnits == Units::PressureUnits::PSI) {
            compare = Units::UNITS_PSI;
        }

        QCOMPARE(compare.toLower(), units.toLower());
    }

    delete testConfig;
}

void ConfigTest::testLoadMapConfig_data() {
    QTest::addColumn<QString>("config");
    QTest::addColumn<bool>("result");
    QTest::addColumn<qreal>("pressure_0V");
    QTest::addColumn<qreal>("pressure_5V");
    QTest::addColumn<QString>("units");

    // try an empty config
    QSettings * emptyConfig = new QSettings("emptyConfig.ini", QSettings::IniFormat);

    emptyConfig->beginGroup(Config::MAP_SENSOR_GROUP);
    emptyConfig->setValue(Config::PRESSURE_AT_0V, "");
    emptyConfig->setValue(Config::PRESSURE_AT_5V, "");
    emptyConfig->setValue(Config::PRESSURE_UNITS, "");
    emptyConfig->endGroup();

    QTest::addRow("empty_config") << "emptyConfig.ini" << false << 0.0 << 0.0 << "kpa";
    delete emptyConfig;

    // try a known valid config
    QSettings * validConfig = new QSettings("validConfig.ini", QSettings::IniFormat);
    qreal p0v = 3.6;
    qreal p5v = 315.0;
    QString units = "kpa";

    validConfig->beginGroup(Config::MAP_SENSOR_GROUP);
    validConfig->setValue(Config::PRESSURE_AT_0V, p0v);
    validConfig->setValue(Config::PRESSURE_AT_5V, p5v);
    validConfig->setValue(Config::PRESSURE_UNITS, units);
    validConfig->endGroup();

    QTest::addRow("valid_config") << "validConfig.ini" << true << p0v << p5v << units;
    delete validConfig;

    // try a known valid config w/ different values
    QSettings * validConfig1 = new QSettings("validConfig1.ini", QSettings::IniFormat);
    p0v = 10.0;
    p5v = 105.0;
    units = "kPa"; // try different case

    validConfig1->beginGroup(Config::MAP_SENSOR_GROUP);
    validConfig1->setValue(Config::PRESSURE_AT_0V, p0v);
    validConfig1->setValue(Config::PRESSURE_AT_5V, p5v);
    validConfig1->setValue(Config::PRESSURE_UNITS, units);
    validConfig1->endGroup();

    QTest::addRow("valid_config1") << "validConfig1.ini" << true << p0v << p5v << units;
    delete validConfig1;

    // lets mess it all up
    QSettings * invalidConfig = new QSettings("invalidConfig.ini", QSettings::IniFormat);
    p0v = -10.0; // slip a negative in here
    p5v = 105.0;
    units = "kpa"; // try different case

    invalidConfig->beginGroup(Config::MAP_SENSOR_GROUP);
    invalidConfig->setValue(Config::PRESSURE_AT_0V, p0v);
    invalidConfig->setValue(Config::PRESSURE_AT_5V, p5v);
    invalidConfig->setValue(Config::PRESSURE_UNITS, units);
    invalidConfig->endGroup();

    QTest::addRow("invalid_config") << "invalidConfig.ini" << false << p0v << p5v << units;
    delete invalidConfig;
}

void ConfigTest::testLoadTempSensorConfig() {
    QFETCH(QString, config);
    QFETCH(bool, result);
    QFETCH(qreal, r_balance);
    QFETCH(qreal, t1_temp);
    QFETCH(qreal, t1_R);
    QFETCH(qreal, t2_temp);
    QFETCH(qreal, t2_R);
    QFETCH(qreal, t3_temp);
    QFETCH(qreal, t3_R);
    QFETCH(QString, units);

    Config * testConfig = new Config(this, config);

    // check if the settings are valid
    SensorConfig::TempSensorConfig conf = testConfig->getTempSensorConfigs()->at(0);
    QCOMPARE(conf.isValid(), result);

    if(result) {
        QCOMPARE(conf.rBalance, r_balance);
        QCOMPARE(conf.t1, t1_temp);
        QCOMPARE(conf.r1, t1_R);
        QCOMPARE(conf.t2, t2_temp);
        QCOMPARE(conf.r2, t2_R);
        QCOMPARE(conf.t3, t3_temp);
        QCOMPARE(conf.r3, t3_R);


        auto configUnits = conf.units;
        QString compare;
        if (configUnits == Units::TemperatureUnits::CELSIUS) {
            compare = Units::UNITS_C;
        } else if (configUnits == Units::TemperatureUnits::FAHRENHEIT) {
            compare = Units::UNITS_F;
        } else if (configUnits == Units::TemperatureUnits::KELVIN) {
            compare = Units::UNITS_K;
        }
        QCOMPARE(compare.toLower(), units.toLower());
    }

    delete(testConfig);
}

void ConfigTest::testLoadTempSensorConfig_data() {
    QTest::addColumn<QString>("config");
    QTest::addColumn<bool>("result");
    QTest::addColumn<QString>("type");
    QTest::addColumn<qreal>("r_balance");
    QTest::addColumn<qreal>("t1_temp");
    QTest::addColumn<qreal>("t1_R");
    QTest::addColumn<qreal>("t2_temp");
    QTest::addColumn<qreal>("t2_R");
    QTest::addColumn<qreal>("t3_temp");
    QTest::addColumn<qreal>("t3_R");
    QTest::addColumn<QString>("units");

    // try an empty config
    QSettings * emptyConfig = new QSettings("emptyConfig.ini", QSettings::IniFormat);

    emptyConfig->beginWriteArray(Config::TEMP_SENSOR_GROUP);
    emptyConfig->setArrayIndex(0);
    emptyConfig->setValue(Config::TEMP_TYPE, "");
    emptyConfig->setValue(Config::TEMP_R_BALANCE, "");
    emptyConfig->setValue(Config::T1_TEMP, "");
    emptyConfig->setValue(Config::T1_RES, "");
    emptyConfig->setValue(Config::T2_TEMP, "");
    emptyConfig->setValue(Config::T2_RES, "");
    emptyConfig->setValue(Config::T3_TEMP, "");
    emptyConfig->setValue(Config::T3_RES, "");
    emptyConfig->setValue(Config::TEMP_UNITS, "");
    emptyConfig->endArray();

    QTest::addRow("empty_config")
            << "emptyConfig.ini"
            << false
            << Config::TEMP_TYPE_COOLANT
            << 1000.0
            << -1.0
            << -1.0
            << -1.0
            << -1.0
            << -1.0
            << -1.0
            << "K";
    delete emptyConfig;

    // try an valid config
    QSettings * validConfig = new QSettings("validConfig.ini", QSettings::IniFormat);

    validConfig->beginWriteArray(Config::TEMP_SENSOR_GROUP);
    validConfig->setArrayIndex(0);
    validConfig->setValue(Config::TEMP_TYPE, "coolant");
    validConfig->setValue(Config::TEMP_R_BALANCE, "470");
    validConfig->setValue(Config::T1_TEMP, "60");
    validConfig->setValue(Config::T1_RES, "217");
    validConfig->setValue(Config::T2_TEMP, "90");
    validConfig->setValue(Config::T2_RES, "87");
    validConfig->setValue(Config::T3_TEMP, "100");
    validConfig->setValue(Config::T3_RES, "67");
    validConfig->setValue(Config::TEMP_UNITS, "C");
    validConfig->endArray();

    QTest::addRow("validConfig")
            << "validConfig.ini"
            << true
            << Config::TEMP_TYPE_COOLANT
            << 470.0
            << 60.0
            << 217.0
            << 90.0
            << 87.0
            << 100.0
            << 67.0
            << "C";
    delete validConfig;
}

void ConfigTest::test_getPressureUnits() {}
void ConfigTest::test_getPressureUnits_data() {}

void ConfigTest::test_getTemperatureUnits() {}
void ConfigTest::test_getTemperatureUnits_data() {}

void ConfigTest::test_getDistanceUnits() {}
void ConfigTest::test_getDistanceUnits_data() {}

void ConfigTest::test_getSpeedUnits() {}
void ConfigTest::test_getSpeedUnits_data() {}

void ConfigTest::test_loadCanFrameConfig() {}
void ConfigTest::test_loadCanFrameConfig_data() {}

void ConfigTest::test_loadOdometerConfig() {}
void ConfigTest::test_loadOdometerConfig_data() {}

void ConfigTest::test_writeOdometerConfig() {}
void ConfigTest::test_writeOdometerConfig_data() {}

void ConfigTest::test_loadGaugeConfig() {}
void ConfigTest::test_loadGaugeConfig_data() {}
