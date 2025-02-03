#ifndef CONFIG_KEYS_H
#define CONFIG_KEYS_H

namespace ConfigKeys {
    // expected groups
    static constexpr char SENSOR_CHANNEL_GROUP[] = "sensor_channels";
    static constexpr char DASH_LIGHT_GROUP[] = "dash_lights";
    static constexpr char MAP_SENSOR_GROUP[] = "map_sensor";
    static constexpr char TEMP_SENSOR_GROUP[] = "temp_sensor";
    static constexpr char TACH_INPUT_GROUP[] = "tach_input";
    static constexpr char RESISTIVE_SENSOR_GROUP[] = "resistive_sensor";
    static constexpr char ANALOG_INPUT_12V_GROUP[] = "12v_analog";
    static constexpr char VSS_INPUT_GROUP[] = "vss_input";
    static constexpr char ODOMETER_GROUP[] = "odometer";
    static constexpr char BACKLIGHT_GROUP[] = "backlight";
    static constexpr char USER_INPUT_GROUP[] = "user_inputs";

    // expected sensor keys
    static constexpr char COOLANT_TEMP_KEY[] = "coolant_temp";
    static constexpr char FUEL_LEVEL_KEY[] = "fuel_level";
    static constexpr char OIL_PRESSURE_KEY[] = "oil_pressure";
    static constexpr char OIL_TEMP_KEY[] = "oil_temp";
    static constexpr char MAP_SENSOR_KEY[] = "map_sensor";
    static constexpr char AMBIENT_TEMP_KEY[] =  "ambient_temp";
    static constexpr char DIMMER_VOLTAGE_KEY[] =  "dimmer_voltage";
    static constexpr char FUSE8_12V_KEY[] = "fuse8_12v";
    static constexpr char REFERENCE_MEASUREMENT[] = "reference";
    static constexpr char V_SUPPLY_KEY[] = "v_supply";
    static constexpr qreal DEFAULT_V_SUPPLY = 5.0;

    // expected dash light keys
    static constexpr char ACTIVE_LOW[] = "active_low";
    static constexpr char OIL_PRESSURE_SW_KEY[] = "oil_pressure_sw";
    static constexpr char OD_LAMP_KEY[] = "od_lamp";
    static constexpr char HIGH_BEAM_KEY[] = "high_beam";
    static constexpr char BRAKE_FAILURE_KEY[] = "brake_failure";
    static constexpr char BULB_FAILURE_KEY[] = "bulb_failure";
    static constexpr char CHARGING_LIGHT_KEY[] = "charging";
    static constexpr char BLINKER_LEFT_KEY[] = "blinker_left";
    static constexpr char BLINKER_RIGHT_KEY[] = "blinker_right";
    static constexpr char OD_LAMP_AUTO[] = "od_lamp_auto";
    static constexpr char CHECK_ENGINE_KEY[] = "check_engine";
    static constexpr char PARKING_BRAKE_KEY[] = "parking_brake";
    static constexpr char CONN_32_PIN3[] = "conn_32_pin3";

    // expected user input keys
    static constexpr char USER_INPUT1[] = "input_1";
    static constexpr char USER_INPUT2[] = "input_2";
    static constexpr char USER_INPUT3[] = "input_3";
    static constexpr char USER_INPUT4[] = "input_4";
    static constexpr char USER_INPUT1_MAP[] = "input_1_map";
    static constexpr char USER_INPUT2_MAP[] = "input_2_map";
    static constexpr char USER_INPUT3_MAP[] = "input_3_map";
    static constexpr char USER_INPUT4_MAP[] = "input_4_map";
    static constexpr Qt::Key USER_INPUT_DEFAULT_KEY = Qt::Key::Key_A;
    static constexpr char USER_INPUT_LONG_PRESS_DURATION[] = "long_press_msec";
    static constexpr int DEFAULT_LONG_PRESS_DURATION_MSEC = 3000;

    //expected map sensor keys
    static constexpr char PRESSURE_AT_0V[] = "p_0v";
    static constexpr char PRESSURE_AT_5V[] = "p_5v";
    static constexpr char PRESSURE_ATM[] = "p_atm";
    static constexpr char PRESSURE_UNITS[] = "units";

    //expected temperature sensor keys
    static constexpr char TEMP_TYPE[] = "type";
    static constexpr char TEMP_R_BALANCE[] = "r_balance";
    static constexpr char T1_TEMP[] = "t1_temp";
    static constexpr char T1_RES[] = "t1_R";
    static constexpr char T2_TEMP[] = "t2_temp";
    static constexpr char T2_RES[] = "t2_R";
    static constexpr char T3_TEMP[] = "t3_temp";
    static constexpr char T3_RES[] = "t3_R";
    static constexpr char TEMP_UNITS[] = "units";

    static constexpr char TEMP_TYPE_COOLANT[] = "coolant";
    static constexpr char TEMP_TYPE_OIL[] = "oil";
    static constexpr char TEMP_TYPE_AMBIENT[] = "ambient";

    //expected keys for tach input
    static constexpr char TACH_PULSES_PER_ROTATION[] = "pulse_per_rot";
    static constexpr char TACH_MAX_RPM[] = "max_rpm";
    static constexpr char TACH_AVG_NUM_SAMPLES[] = "avg_num_samples";

    //expected keys for vss input
    static constexpr char VSS_PULSES_PER_ROTATION[] = "pulse_per_rot";
    static constexpr char VSS_TIRE_DIAMETER[] = "tire_diameter";
    static constexpr char VSS_TIRE_DIAMETER_UNITS[] = "diameter_units";
    static constexpr char VSS_PULSES_PER_DISTANCE[] = "pulse_per_unit_distance";
    static constexpr char VSS_DISTANCE_UNITS[] = "distance_units";
    static constexpr char VSS_MAX_SPEED[] = "max_speed";
    static constexpr char VSS_USE_GPS[] = "use_gps";

    //expected keys for resistive sensors
    static constexpr char RES_SENSOR_TYPE[] = "type";
    static constexpr char RES_SENSOR_FIT_TYPE[] = "fit";
    static constexpr char RES_SENSOR_R_VALUES[] = "r";
    static constexpr char RES_SENSOR_Y_VALUES[] = "y";
    static constexpr char RES_SENSOR_UNITS[] = "units";
    static constexpr char RES_SENSOR_R_BALANCE[] = "r_balance";
    static constexpr char RES_SENSOR_LAG[] = "lag";
    static constexpr char RES_SENSOR_LAG_DECAY[] = "lag_decay";

    static constexpr char RES_SENSOR_TYPE_FUEL_LEVEL[] = "fuel_level";
    static constexpr char RES_SENSOR_TYPE_OIL_PRESSURE[] = "oil_pressure";

    static constexpr char RES_SENSOR_FIT_TYPE_POLYNOMIAL[] = "polynomial";
    static constexpr char RES_SENSOR_FIT_TYPE_INTERPOLATION[] = "interp";

    //expected keys for 12V analog signals
    static constexpr char ANALOG_INPUT_12V_NAME[] = "name";
    static constexpr char ANALOG_INPUT_12V_OPTO_R1[] = "opto_r1";
    static constexpr char ANALOG_INPUT_12V_OPTO_R2[] = "opto_r2";
    static constexpr char ANALOG_INPUT_12V_INPUT_R1[] = "input_r1";
    static constexpr char ANALOG_INPUT_12V_INPUT_R2[] = "input_r2";
    static constexpr char ANALOG_INPUT_12V_OPTO_GAIN_K3[] = "k3";
    static constexpr char ANALOG_INPUT_12V_OFFSET[] = "offset";
    static constexpr char ANALOG_INPUT_12V_X_VALUES[] = "x";
    static constexpr char ANALOG_INPUT_12V_Y_VALUES[] = "y";

    static constexpr char ANALOG_INPUT_12V_VOLTMETER[] = "voltmeter";
    static constexpr char ANALOG_INPUT_12V_RHEOSTAT[] = "rheostat";

    //expected odometer keys
    static constexpr char ODO_NAME[] = "name";
    static constexpr char ODO_UNITS[] = "units";
    static constexpr char ODO_VALUE[] = "value";
    static constexpr char ODO_WRITE_INTERVAL[] = "interval";

    static constexpr char ODO_NAME_ODOMETER[] = "odometer";
    static constexpr char ODO_NAME_TRIPA[] = "tripA";
    static constexpr char ODO_NAME_TRIPB[] = "tripB";

    static constexpr char BACKLIGHT_MAX_DUTY_CYCLE[] = "max_duty_cycle";
    static constexpr char BACKLIGHT_MIN_DUTY_CYCLE[] = "min_duty_cycle";
    static constexpr char BACKLIGHT_LIGHTS_OFF_DUTY_CYCLE[] = "lights_off_duty_cycle";
    static constexpr char BACKLIGHT_LIGHTS_ON_DUTY_CYCLE[] = "lights_on_duty_cycle";
    static constexpr char BACKLIGHT_MIN_DIMMER_RATIO[] = "min_dimmer_ratio";
    static constexpr char BACKLIGHT_MAX_DIMMER_RATIO[] = "max_dimmer_ratio";
    static constexpr char BACKLIGHT_USE_DIMMER[] = "use_dimmer";
    static constexpr char BACKLIGHT_ACTIVE_LOW[] = "active_low";

    //gauge config groups
    // boost gauge configs
    static constexpr char BOOST_GAUGE_GROUP[] = "boost";
    static constexpr qreal DEFAULT_BOOST_GAUGE_MIN_PSI = -20;
    static constexpr qreal DEFAULT_BOOST_GAUGE_MAX_PSI = 30;

    static constexpr qreal DEFAULT_BOOST_GAUGE_MIN_BAR = -1.0;
    static constexpr qreal DEFAULT_BOOST_GAUGE_MAX_BAR = 1.5;
    //coolant temp gauge configs
    static constexpr char COOLANT_TEMP_GAUGE_GROUP[] = "coolant_temp";
    static constexpr qreal DEFAULT_COOLANT_TEMP_GAUGE_MIN_F = 120.0;
    static constexpr qreal DEFAULT_COOLANT_TEMP_GAUGE_MAX_F = 250.0;

    static constexpr qreal DEFAULT_COOLANT_TEMP_GAUGE_MIN_C = 50.0;
    static constexpr qreal DEFAULT_COOLANT_TEMP_GAUGE_MAX_C = 120.0;

    static constexpr char FUEL_GAUGE_GROUP[] = "fuel_level";
    // oil presssure gauge configs
    static constexpr char OIL_PRESSURE_GAUGE_GROUP[] = "oil_pressure";
    static constexpr qreal DEFAULT_OIL_PRESSURE_GAUGE_MIN_PSI = 0.0;
    static constexpr qreal DEFAULT_OIL_PRESSURE_GAUGE_MAX_PSI = 80.0;

    static constexpr qreal DEFAULT_OIL_PRESSURE_GAUGE_MIN_BAR = 0.0;
    static constexpr qreal DEFAULT_OIL_PRESSURE_GAUGE_MAX_BAR = 5.0;
    //oil temperature gauge configs
    static constexpr char OIL_TEMPERATURE_GAUGE_GROUP[] = "oil_temperature";
    static constexpr qreal DEFAULT_OIL_TEMP_GAUGE_MIN_F = 120.0;
    static constexpr qreal DEFAULT_OIL_TEMP_GAUGE_MAX_F = 300.0;

    static constexpr qreal DEFAULT_OIL_TEMP_GAUGE_MIN_C = 50.0;
    static constexpr qreal DEFAULT_OIL_TEMP_GAUGE_MAX_C = 150.0;
    // voltmeter
    static constexpr char VOLTMETER_GAUGE_GROUP[] = "voltmeter";
    static constexpr qreal DEFAULT_VOLTMETER_GAUGE_MIN = 10.0;
    static constexpr qreal DEFAULT_VOLTMETER_GAUGE_MAX = 16.0;
    //speedometer gauge configs
    static constexpr char SPEEDOMETER_GAUGE_GROUP[] = "speedo";
    static constexpr qreal DEFAULT_SPEEDO_GAUGE_MIN_MPH = 0.0;
    static constexpr qreal DEFAULT_SPEEDO_GAUGE_MAX_MPH = 120.0;

    static constexpr qreal DEFAULT_SPEEDO_GAUGE_MIN_KPH = 0.0;
    static constexpr qreal DEFAULT_SPEEDO_GAUGE_MAX_KPH = 220.0;

    static constexpr char TACHOMETER_GAUGE_GROUP[] = "tacho";
    static constexpr qreal DEFAULT_TACH_GAUGE_MAX = 7000.0;
    static constexpr qreal DEFAULT_TACH_GAUGE_REDLINE = 6000.0;


    // gauge config keys
    static constexpr char MIN_VALUE[] = "min";
    static constexpr char MAX_VALUE[] = "max";
    static constexpr char HIGH_ALARM[] = "high_alarm";
    static constexpr char LOW_ALARM[] = "low_alarm";
    static constexpr char GAUGE_UNITS[] = "units";
    static constexpr char TOP_VALUE_SOURCE[] = "top_value_source";
    static constexpr char TOP_VALUE_UNITS[] = "top_value_units";
    static constexpr char MAX_RPM[] = "max_rpm";
    static constexpr char REDLINE[] = "redline";
    static constexpr char ENABLE_ALT_UNITS[] = "alt_units_enable";
    static constexpr char GAUGE_ALT_UNITS[] = "alt_units";
    static constexpr char ALT_UNITS_THRESHOLD[] = "alt_units_thres";
    static constexpr char ALT_UNITS_ABOVE_THRS[] = "alt_units_above";

    //can config keys
    static constexpr char CAN_CONFIG_START[] = "start";
    static constexpr char CAN_CONFIG_ENABLE[] = "use";
    static constexpr char CAN_FRAME[] = "can_frame";
    static constexpr char CAN_FRAME_ID[] = "frame_id";
    static constexpr char CAN_FRAME_OFFSET[] = "offset";
    static constexpr char CAN_FRAME_SIZE[] = "data_size";
    static constexpr char CAN_FRAME_SIGNED[] = "signed";
    static constexpr char CAN_FRAME_NAME[] = "name";
    static constexpr char CAN_FRAME_UNITS[] = "units";
    static constexpr char CAN_FRAME_MULTIPLY[] = "multiply";
    static constexpr char CAN_FRAME_DIVIDE[] = "divide";
    static constexpr char CAN_FRAME_ADD[] = "add";
    static constexpr char CAN_FRAME_GAUGE[] = "gauge";

    //screen properties keys
    static constexpr char SCREEN_PROP_GROUP[] = "screen_prop";
    static constexpr char SCREEN_PROP_USE[] = "use";
    static constexpr char SCREEN_PROP_ORIENTATION[] = "orientation_angle";

}

#endif // CONFIG_KEYS_H
