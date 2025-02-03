#include <config.h>

using namespace ConfigKeys;

Config::Config(QObject * parent, QString configPath,
       QString gaugeConfigPath, QString odoConfigPath,
       QString canConfigPath): QObject(parent) {

    mConfig.reset(
        new QSettings(
            configPath,
            QSettings::IniFormat
        )
    );
    loadConfig();

    mGaugeConfig.reset(new QSettings(gaugeConfigPath, QSettings::IniFormat));
    loadGaugeConfigs();

    mOdometerConfig.reset(new QSettings(odoConfigPath, QSettings::IniFormat));
    loadOdometerConfigs();

    mCanConfig.reset(new QSettings(canConfigPath, QSettings::IniFormat));
    loadCanFrameConfigs();
}

bool Config::loadCanFrameConfigs() {
    // parse enable/disable
    mCanConfig->beginGroup(CAN_CONFIG_START);
    printKeys("can", mCanConfig.get());
    mEnableCan = mCanConfig->value(CAN_CONFIG_ENABLE, false).toBool();
    mCanConfig->endGroup();

    // dump keys to log
    mCanConfig->beginGroup(CAN_FRAME);
    printKeys("can", mCanConfig.get());
    mCanConfig->endGroup();

    // parse can frame data configs
    int size = mCanConfig->beginReadArray(CAN_FRAME);
    for (int i = 0; i < size; ++i) {
        mCanConfig->setArrayIndex(i);

        uint32_t frameId = mCanConfig->value(CAN_FRAME_ID, 0).toUInt();
        uint8_t offset = mCanConfig->value(CAN_FRAME_OFFSET, 0).toInt();
        uint8_t size = mCanConfig->value(CAN_FRAME_SIZE, 0).toInt();
        bool sign = mCanConfig->value(CAN_FRAME_SIGNED, false).toBool();
        QString units = mCanConfig->value(CAN_FRAME_UNITS, "").toString();
        QString name = mCanConfig->value(CAN_FRAME_NAME, "").toString();
        QString gauge = mCanConfig->value(CAN_FRAME_GAUGE, "none").toString();

        // create new can frame config
        CanFrameConfig config(frameId, offset, size, sign, units, name, gauge);

        qreal multiply = mCanConfig->value(CAN_FRAME_MULTIPLY, 1).toReal();
        qreal divide = mCanConfig->value(CAN_FRAME_DIVIDE, 1).toReal();
        qreal add = mCanConfig->value(CAN_FRAME_ADD, 0).toReal();

        if (multiply != 1) {
            config.addOperation(CanFrameConfig::OperationType::MULTIPLY, multiply);
        }

        if (divide != 1) {
            config.addOperation(CanFrameConfig::OperationType::DIVIDE, divide);
        }

        if (add != 0) {
            config.addOperation(CanFrameConfig::OperationType::ADD, add);
        }

        mCanFrameConfigs.append(config);
        printKeys("can: ", mCanConfig.get());
    }
    mCanConfig->endArray();

    return true;
}

bool Config::loadOdometerConfigs() {

    mOdometerConfig->beginGroup("start");
    printKeys("odo", mOdometerConfig.get());
    mOdometerConfig->endGroup();

    mOdometerConfig->beginGroup(ODOMETER_GROUP);
    printKeys("odo", mOdometerConfig.get());
    mOdometerConfig->endGroup();

    int size = mOdometerConfig->beginReadArray(ODOMETER_GROUP);
    for (int i = 0; i < size; ++i) {
        SensorConfig::OdometerConfig conf;
        mOdometerConfig->setArrayIndex(i);

        QString odoUnits = mOdometerConfig->value(ODO_UNITS, Units::UNITS_MILE).toString();
        conf.units = Units::getDistanceUnits(odoUnits);
        conf.value = mOdometerConfig->value(ODO_VALUE, 0.0).toReal();
        conf.writeInterval = mOdometerConfig->value(ODO_WRITE_INTERVAL, 2000).toInt();
        conf.name = mOdometerConfig->value(ODO_NAME, "").toString();

        mOdoConfig.push_back(conf);
        printKeys("odo-vals", mOdometerConfig.get());
    }

    mOdometerConfig->endArray();
    return true;
}

bool Config::writeOdometerConfig(QString name, SensorConfig::OdometerConfig conf) {
    //write to disk
    mOdometerConfig->beginWriteArray(ODOMETER_GROUP);
    for (int i = 0; i < mOdoConfig.size(); i++) {
        mOdometerConfig->setArrayIndex(i);

        if (mOdometerConfig->value(ODO_NAME, "").toString() == name) {
            mOdometerConfig->setValue(ODO_VALUE, conf.value);
            mOdometerConfig->sync();
        }
    }
    mOdometerConfig->endArray();
    return true;
}

bool Config::loadGaugeConfigs() {
    // accessory gauges
    // boost gauge
    GaugeConfig::GaugeConfig boost = loadGaugeConfig(BOOST_GAUGE_GROUP);
    if (boost.displayUnits.compare(Units::UNITS_PSI, Qt::CaseInsensitive) == 0) {
        boost.min = DEFAULT_BOOST_GAUGE_MIN_PSI;
        boost.max = DEFAULT_BOOST_GAUGE_MAX_PSI;
    } else {
        boost.min = DEFAULT_BOOST_GAUGE_MIN_BAR;
        boost.max = DEFAULT_BOOST_GAUGE_MAX_BAR;
    }
    mGaugeConfigs.insert(BOOST_GAUGE_GROUP, boost);

    // coolant temp
    GaugeConfig::GaugeConfig coolantTemp = loadGaugeConfig(COOLANT_TEMP_GAUGE_GROUP);
    if (coolantTemp.displayUnits.compare(Units::UNITS_F, Qt::CaseInsensitive) == 0) {
        coolantTemp.min = DEFAULT_COOLANT_TEMP_GAUGE_MIN_F;
        coolantTemp.max = DEFAULT_COOLANT_TEMP_GAUGE_MAX_F;
    } else {
        coolantTemp.min = DEFAULT_COOLANT_TEMP_GAUGE_MIN_C;
        coolantTemp.max = DEFAULT_COOLANT_TEMP_GAUGE_MAX_C;
    }
    mGaugeConfigs.insert(COOLANT_TEMP_GAUGE_GROUP, coolantTemp);

    // fuel level
    GaugeConfig::GaugeConfig fuelLevel = loadGaugeConfig(FUEL_GAUGE_GROUP);
    fuelLevel.min = 0.0;
    fuelLevel.max = 100.0;
    mGaugeConfigs.insert(FUEL_GAUGE_GROUP, fuelLevel);

    // oil pressure
    GaugeConfig::GaugeConfig oilPressure = loadGaugeConfig(OIL_PRESSURE_GAUGE_GROUP);
    if (oilPressure.displayUnits.compare(Units::UNITS_PSI, Qt::CaseInsensitive) == 0) {
        oilPressure.min = DEFAULT_OIL_PRESSURE_GAUGE_MIN_PSI;
        oilPressure.max = DEFAULT_OIL_PRESSURE_GAUGE_MAX_PSI;
    } else {
        oilPressure.min = DEFAULT_OIL_PRESSURE_GAUGE_MIN_BAR;
        oilPressure.max = DEFAULT_OIL_PRESSURE_GAUGE_MAX_BAR;
    }
    mGaugeConfigs.insert(OIL_PRESSURE_GAUGE_GROUP, oilPressure);

    // oil temperature
    GaugeConfig::GaugeConfig oilTemp = loadGaugeConfig(OIL_TEMPERATURE_GAUGE_GROUP);
    if (oilTemp.displayUnits.compare(Units::UNITS_F, Qt::CaseInsensitive) == 0) {
        oilTemp.min = DEFAULT_OIL_TEMP_GAUGE_MIN_F;
        oilTemp.max = DEFAULT_OIL_TEMP_GAUGE_MAX_F;
    } else {
        oilTemp.min = DEFAULT_OIL_TEMP_GAUGE_MIN_C;
        oilTemp.max = DEFAULT_OIL_TEMP_GAUGE_MAX_C;
    }
    mGaugeConfigs.insert(OIL_TEMPERATURE_GAUGE_GROUP, oilTemp);

    //voltmeter
    GaugeConfig::GaugeConfig voltmeter = loadGaugeConfig(VOLTMETER_GAUGE_GROUP);
    voltmeter.min = DEFAULT_VOLTMETER_GAUGE_MIN;
    voltmeter.max = DEFAULT_VOLTMETER_GAUGE_MAX;
    mGaugeConfigs.insert(VOLTMETER_GAUGE_GROUP, voltmeter);

    // speedo
    mSpeedoGaugeConfig.gaugeConfig = loadGaugeConfig(SPEEDOMETER_GAUGE_GROUP);
    if (mSpeedoGaugeConfig.gaugeConfig.displayUnits.compare(Units::UNITS_MPH, Qt::CaseInsensitive) == 0) {
        mSpeedoGaugeConfig.gaugeConfig.min = 0.0;
        mSpeedoGaugeConfig.gaugeConfig.max =
            mSpeedoGaugeConfig.gaugeConfig.max == 0 ?
                DEFAULT_SPEEDO_GAUGE_MAX_MPH :
                mSpeedoGaugeConfig.gaugeConfig.max;
        mSpeedoGaugeConfig.gaugeConfig.highAlarm = mSpeedoGaugeConfig.gaugeConfig.max;
        mSpeedoGaugeConfig.gaugeConfig.lowAlarm = mSpeedoGaugeConfig.gaugeConfig.min;
    } else {
        mSpeedoGaugeConfig.gaugeConfig.min = 0.0;
        mSpeedoGaugeConfig.gaugeConfig.max =
            mSpeedoGaugeConfig.gaugeConfig.max == 0 ?
                DEFAULT_SPEEDO_GAUGE_MAX_KPH :
                mSpeedoGaugeConfig.gaugeConfig.max;
        mSpeedoGaugeConfig.gaugeConfig.highAlarm = mSpeedoGaugeConfig.gaugeConfig.max;
        mSpeedoGaugeConfig.gaugeConfig.lowAlarm = mSpeedoGaugeConfig.gaugeConfig.min;
    }
    mGaugeConfig->beginGroup(SPEEDOMETER_GAUGE_GROUP);
    mSpeedoGaugeConfig.topSource = mGaugeConfig->value(TOP_VALUE_SOURCE).toString();
    mSpeedoGaugeConfig.topUnits = mGaugeConfig->value(TOP_VALUE_UNITS).toString();

    printKeys("Speedometer: ", mGaugeConfig.get());

    mGaugeConfig->endGroup();

    //tacho
    mGaugeConfig->beginGroup(TACHOMETER_GAUGE_GROUP);
    mTachGaugeConfig.maxRpm = mGaugeConfig->value(MAX_RPM).toInt();
    mTachGaugeConfig.redline = mGaugeConfig->value(REDLINE).toInt();

    printKeys("Tachometer: ", mGaugeConfig.get());

    mGaugeConfig->endGroup();

    return true;
}

GaugeConfig::GaugeConfig Config::loadGaugeConfig(QString groupName) {
    mGaugeConfig->beginGroup(groupName);

    GaugeConfig::GaugeConfig conf;

    conf.min = mGaugeConfig->value(MIN_VALUE, "").toReal();
    conf.max = mGaugeConfig->value(MAX_VALUE, "").toReal();
    conf.highAlarm = mGaugeConfig->value(HIGH_ALARM, "").toReal();
    conf.lowAlarm = mGaugeConfig->value(LOW_ALARM, "").toReal();
    conf.displayUnits = mGaugeConfig->value(GAUGE_UNITS, "").toString();

    conf.altDisplayUnits.use = mGaugeConfig->value(ENABLE_ALT_UNITS, false).toBool();
    conf.altDisplayUnits.displayUnits = mGaugeConfig->value(GAUGE_ALT_UNITS, "").toString();
    conf.altDisplayUnits.aboveCutoff = mGaugeConfig->value(ALT_UNITS_ABOVE_THRS, false).toBool();
    conf.altDisplayUnits.cutoff = mGaugeConfig->value(ALT_UNITS_THRESHOLD, 0.0).toReal();

    printKeys(groupName, mGaugeConfig.get());

    mGaugeConfig->endGroup();

    return conf;
}

bool Config::loadConfig() {
    QStringList keys = mConfig->allKeys();

    // Load sensor configuration
    mConfig->beginGroup(SENSOR_CHANNEL_GROUP);

    for (auto key : mConfig->childKeys()) {
        if (key == V_SUPPLY_KEY) {
            mSensorSupplyVoltage = mConfig->value(key, DEFAULT_V_SUPPLY).toReal();
        } else {
            mSensorChannelConfig.insert(key, mConfig->value(key, -1).toInt());
        }
    }

    printKeys("Sensor Channels ", mConfig.get());

    mConfig->endGroup();

    // Load dash light configuration
    mConfig->beginGroup(DASH_LIGHT_GROUP);

    for (auto key : mConfig->childKeys()) {
        mDashLightConfig.insert(key, mConfig->value(key, -1).toInt());
    }

    printKeys("Dash Light Config ", mConfig.get());

    mConfig->endGroup();

    // user input group
    mConfig->beginGroup(USER_INPUT_GROUP);

    for (QString key : mConfig->childKeys()) {
        if (QString::compare(key, USER_INPUT1_MAP) == 0) {
            mUserInputConfig.insert(0, mKeyMap.value(mConfig->value(key, "Key_Left").toString(), USER_INPUT_DEFAULT_KEY));
        } else if (QString::compare(key, USER_INPUT2_MAP) == 0) {
            mUserInputConfig.insert(1, mKeyMap.value(mConfig->value(key, "Key_A").toString(), USER_INPUT_DEFAULT_KEY));
        } else if (QString::compare(key, USER_INPUT3_MAP) == 0) {
            mUserInputConfig.insert(2, mKeyMap.value(mConfig->value(key, "Key_B").toString(), USER_INPUT_DEFAULT_KEY));
        } else if (QString::compare(key, USER_INPUT4_MAP) == 0) {
            mUserInputConfig.insert(3, mKeyMap.value(mConfig->value(key, "Key_Right").toString(), USER_INPUT_DEFAULT_KEY));
        } else if (QString::compare(key, USER_INPUT_LONG_PRESS_DURATION) == 0) {
            mUserInputPinConfig.insert(key, mConfig->value(key, DEFAULT_LONG_PRESS_DURATION_MSEC).toInt());
        } else {
            mUserInputPinConfig.insert(key, mConfig->value(key).toInt());
        }
    }

    printKeys("User Inputs: ", mConfig.get());
    mConfig->endGroup();

    //load map sensor config
    mConfig->beginGroup(MAP_SENSOR_GROUP);

    for (auto key : mConfig->childKeys()) {
        if (key == PRESSURE_AT_0V) {
            mMapSensorConfig.p0V = mConfig->value(key, -1).toReal();
        } else if (key == PRESSURE_AT_5V) {
            mMapSensorConfig.p5V = mConfig->value(key, -1).toReal();
        } else if (key == PRESSURE_ATM) {
            mMapSensorConfig.pAtm = mConfig->value(key, -1).toReal();
        } else if (key == PRESSURE_UNITS) {
            // default to kPa
            QString units = mConfig->value(key, Units::UNITS_KPA).toString();
            mMapSensorConfig.units = Units::getPressureUnits(units);
        }
    }

    printKeys("Map Sensor ", mConfig.get());

    mConfig->endGroup();

    // Temperature sensor config
    int size = mConfig->beginReadArray(TEMP_SENSOR_GROUP);
    for (int i = 0; i < size; ++i) {
        SensorConfig::TempSensorConfig conf;
        mConfig->setArrayIndex(i);

        conf.rBalance = mConfig->value(TEMP_R_BALANCE, 1000).toReal();
        conf.t1 = mConfig->value(T1_TEMP, -1).toReal();
        conf.t2 = mConfig->value(T2_TEMP, -1).toReal();
        conf.t3 = mConfig->value(T3_TEMP, -1).toReal();
        conf.r1 = mConfig->value(T1_RES, -1).toReal();
        conf.r2 = mConfig->value(T2_RES, -1).toReal();
        conf.r3 = mConfig->value(T3_RES, -1).toReal();

        QString units = mConfig->value(TEMP_UNITS, Units::UNITS_K).toString();
        conf.units = Units::getTempUnits(units);

        QString type = mConfig->value(TEMP_TYPE, TEMP_TYPE_COOLANT).toString();
        if (type.compare(TEMP_TYPE_COOLANT, Qt::CaseInsensitive) == 0) {
            conf.type = SensorConfig::TemperatureSensorType::COOLANT;
        } else if (type.compare(TEMP_TYPE_OIL, Qt::CaseInsensitive) == 0) {
            conf.type = SensorConfig::TemperatureSensorType::OIL;
        } else if (type.compare(TEMP_TYPE_AMBIENT, Qt::CaseInsensitive) == 0) {
            conf.type = SensorConfig::TemperatureSensorType::AMBIENT;
        } else {
            qDebug() << "Unrecognized temperature sensor type, assuming coolant.  Fix config.ini file if not correct";
            conf.type = SensorConfig::TemperatureSensorType::COOLANT;
        }

        mTempSensorConfigs.append(conf);

        printKeys("Temp Sensor ", mConfig.get());
    }
    mConfig->endArray();

    //tach input config
    mConfig->beginGroup(TACH_INPUT_GROUP);

    mTachConfig.pulsesPerRot = mConfig->value(TACH_PULSES_PER_ROTATION, 2).toInt(); // default to 4 cylinder
    mTachConfig.maxRpm = mConfig->value(TACH_MAX_RPM, 9000).toInt(); // default rpm is 9000 (a bit aspirational)
    mTachConfig.avgNumSamples = mConfig->value(TACH_AVG_NUM_SAMPLES, 4).toInt(); // default is to average over last 4 tach pulse spacing

    printKeys("Tach Input ", mConfig.get());

    mConfig->endGroup();

    size = 0;
    size = mConfig->beginReadArray(RESISTIVE_SENSOR_GROUP);
    for (int i = 0; i < size; ++i) {
        mConfig->setArrayIndex(i);
        SensorConfig::ResistiveSensorConfig rSensorConf;
        // sensor type/name
        rSensorConf.type = mConfig->value(RES_SENSOR_TYPE, "").toString();

        // sensor fit type
        QList fit = mConfig->value(RES_SENSOR_FIT_TYPE, "").toList();
        if (fit.at(0).toString() == RES_SENSOR_FIT_TYPE_POLYNOMIAL && fit.length() == 2) {
            rSensorConf.fitType = SensorConfig::ResistiveSensorType::POLYNOMIAL;
            rSensorConf.order = fit.at(1).toInt();
        } else {
            rSensorConf.fitType = SensorConfig::ResistiveSensorType::INTERPOLATION;
            rSensorConf.order = -1;
        }

        // balance/pullup/high side whatever resistor
        rSensorConf.rBalance = mConfig->value(RES_SENSOR_R_BALANCE, "1000.0").toReal();

        // resistance values
        QList r = mConfig->value(RES_SENSOR_R_VALUES, "").toList();
        for (QVariant val : r) {
            rSensorConf.x.push_back(val.toReal());
        }

        // y values (fuel level, pressure, etc)
        QList y = mConfig->value(RES_SENSOR_Y_VALUES, "").toList();
        for (QVariant val : y) {
            rSensorConf.y.push_back(val.toReal());
        }

        // y value units
        rSensorConf.units = mConfig->value(RES_SENSOR_UNITS, "").toString();

        // lag coefficient
        rSensorConf.lag = mConfig->value(RES_SENSOR_LAG, 1.0).toReal();
        rSensorConf.lagDecay = mConfig->value(RES_SENSOR_LAG_DECAY, 0.0).toReal();

        if (rSensorConf.lag == 1.0) {
            rSensorConf.lagStart = rSensorConf.lag;
        } else {
            rSensorConf.lagStart = 1.0 - rSensorConf.lag;
        }

        mResistiveSensorConfig.insert(rSensorConf.type, rSensorConf);
        printKeys("Resistive Sensor: ", mConfig.get());


    }
    mConfig->endArray();

    size = 0;
    size = mConfig->beginReadArray(ANALOG_INPUT_12V_GROUP);
    for (int i = 0; i < size; ++i) {
        mConfig->setArrayIndex(i);

        Analog12VInput::Analog12VInputConfig conf;

        conf.type = mConfig->value(ANALOG_INPUT_12V_NAME, "").toString();
        conf.optoR1 = mConfig->value(ANALOG_INPUT_12V_OPTO_R1, 1).toReal();
        conf.optoR2 = mConfig->value(ANALOG_INPUT_12V_OPTO_R2, 1).toReal();
        conf.inputR1 = mConfig->value(ANALOG_INPUT_12V_INPUT_R1, 1).toReal();
        conf.inputR2 = mConfig->value(ANALOG_INPUT_12V_INPUT_R2, 1).toReal();
        conf.gainK3 = mConfig->value(ANALOG_INPUT_12V_OPTO_GAIN_K3, 1).toReal();
        conf.offset = mConfig->value(ANALOG_INPUT_12V_OFFSET, 0).toReal();

        // resistance values
        QList r = mConfig->value(ANALOG_INPUT_12V_X_VALUES, "").toList();
        for (QVariant val : r) {
            conf.x.push_back(val.toReal());
        }

        // y values (fuel level, pressure, etc)
        QList y = mConfig->value(ANALOG_INPUT_12V_Y_VALUES, "").toList();
        for (QVariant val : y) {
            conf.y.push_back(val.toReal());
        }
        if (conf.x.length() > 0) {
            conf.order = 1;
        } else {
            conf.order = 0;
        }

        mAnalog12VInputConfig.insert(conf.type, conf);
        printKeys("Analog 12V input: ", mConfig.get());
    }
    mConfig->endArray();


    // VSS Input Configuration
    mConfig->beginGroup(VSS_INPUT_GROUP);

    mVssInputConfig.pulsePerRot = mConfig->value(VSS_PULSES_PER_ROTATION, 12).toInt();
    mVssInputConfig.tireDiameter = mConfig->value(VSS_TIRE_DIAMETER, 24.9).toReal();
    QString diameterUnits =  mConfig->value(VSS_TIRE_DIAMETER_UNITS, "inch").toString().toLower();
    mVssInputConfig.tireDiameterUnits = Units::getDistanceUnits(diameterUnits);
    mVssInputConfig.pulsePerUnitDistance = mConfig->value(VSS_PULSES_PER_DISTANCE, 0).toInt();
    QString distanceUnits = mConfig->value(VSS_DISTANCE_UNITS, "mile").toString().toLower();
    mVssInputConfig.distanceUnits = Units::getDistanceUnits(distanceUnits);
    mVssInputConfig.maxSpeed = mConfig->value(VSS_MAX_SPEED, 160).toInt();
    mVssInputConfig.useGps = mConfig->value(VSS_USE_GPS, false).toBool();

    printKeys("VSS Input: ", mConfig.get());

    mConfig->endGroup();

    mConfig->beginGroup(BACKLIGHT_GROUP);
    mBacklightConfig.minDutyCycle = mConfig->value(BACKLIGHT_MIN_DUTY_CYCLE, 0.2).toReal();
    mBacklightConfig.maxDutyCycle = mConfig->value(BACKLIGHT_MAX_DUTY_CYCLE, 1.0).toReal();
    mBacklightConfig.lightsOffDutyCycle = mConfig->value(BACKLIGHT_LIGHTS_OFF_DUTY_CYCLE, 1.0).toReal();
    mBacklightConfig.lightsOnDutyCycle = mConfig->value(BACKLIGHT_LIGHTS_ON_DUTY_CYCLE, 0.6).toReal();
    mBacklightConfig.minDimmerRatio = mConfig->value(BACKLIGHT_MIN_DIMMER_RATIO, 0.82).toReal();
    mBacklightConfig.maxDimmerRatio = mConfig->value(BACKLIGHT_MAX_DIMMER_RATIO, 0.93).toReal();
    mBacklightConfig.useDimmer = mConfig->value(BACKLIGHT_USE_DIMMER, true).toBool();
    mBacklightConfig.activeLow = mConfig->value(BACKLIGHT_ACTIVE_LOW, false).toBool();

    printKeys("Backlight Config: ", mConfig.get());

    mConfig->endGroup();

    loadScreenConfig();

    return keys.size() > 0;
}

bool Config::loadScreenConfig() {
    mConfig->beginGroup(SCREEN_PROP_GROUP);
    mScreenConfig.use = mConfig->value(SCREEN_PROP_USE, false).toBool();
    mScreenConfig.screenRotationAngle = mConfig->value(SCREEN_PROP_ORIENTATION, 180).toReal();

    printKeys("Screen Properties: ", mConfig.get());

    mConfig->endGroup();

    return true;
}

bool Config::isMapConfigValid(QMap<QString, int> *map) {
    QSet<int> values;
    for (int val : map->values()) {
        // check that the value is valid
        if (val < 0) {
            return false;
        }

        // check that the value doesn't already exist
        if (values.contains(val)) {
            return false;
        }

        values.insert(val);
    }
    return true;
}

QMap<QString, Qt::Key> Config::initKeyMap() {
    QMap<QString, Qt::Key> map;

    map.insert("Key_Left", Qt::Key::Key_Left);
    map.insert("Key_Right", Qt::Key::Key_Right);
    map.insert("Key_Up", Qt::Key::Key_Up);
    map.insert("Key_Down", Qt::Key::Key_Down);
    map.insert("Key_A", Qt::Key::Key_A);
    map.insert("Key_B", Qt::Key::Key_B);
    map.insert("Key_C", Qt::Key::Key_C);
    map.insert("Key_D", Qt::Key::Key_D);
    map.insert("Key_1", Qt::Key::Key_1);
    map.insert("Key_2", Qt::Key::Key_2);
    map.insert("Key_3", Qt::Key::Key_3);
    map.insert("Key_4", Qt::Key::Key_4);

    return map;
}


