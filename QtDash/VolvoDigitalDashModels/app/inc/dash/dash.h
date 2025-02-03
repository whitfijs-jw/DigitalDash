#ifndef DASH_H
#define DASH_H

#include <QObject>
#include <QQmlContext>
#include <QMap>
#include <QKeyEvent>

#include <vector>
#include <memory>

#include <tachometer_model.h>
#include <accessory_gauge_model.h>
#include <speedometer_model.h>
#include <temp_and_fuel_gauge_model.h>
#include <indicator_model.h>
#include <warning_light_model.h>
#include <odometer_model.h>

#include <config.h>
#include <event_timers.h>
#include <dash_lights.h>
#include <backlight_control.h>

#include <sensor_source_adc.h>
#include <sensor_source_gps.h>
#include <sensor_source_tach.h>
#include <sensor_source_vss.h>

#include <sensor_configs.h>
#include <sensor_map.h>
#include <sensor_ntc.h>
#include <sensor_voltmeter.h>
#include <sensor_resistive.h>
#include <sensor_speedo.h>
#include <sensor_tach.h>
#include <sensor_odometer.h>

#include <gauge_accessory.h>
#include <gauge_speedo.h>
#include <gauge_tach.h>
#include <gauge_temp_fuel_cluster.h>
#include <gauge_odo.h>

#include <sensor_source_can.h>
#include <sensor_can.h>

/**
 * @brief A class to run the digital dash
 */
class Dash : public QObject {
    Q_OBJECT
public:
    static constexpr char COOLANT_TEMP_MODEL_NAME[] = "coolantTempModel"; //!< coolant temp model name
    static constexpr char FUEL_LEVEL_MODEL_NAME[] = "fuelLevelModel"; //!< fuel level model name
    static constexpr char OIL_PRESSURE_MODEL_NAME[] = "oilPModel"; //!< oil pressure model name
    static constexpr char OIL_TEMPERATURE_MODEL_NAME[] = "oilTModel"; //!< oil temperature model name
    static constexpr char BOOST_GAUGE_MODEL_NAME[] = "boostModel"; //!< boost pressure model name
    static constexpr char VOLT_METER_MODEL_NAME[] = "voltMeterModel"; //!< voltmeter model name
    static constexpr char TACH_MODEL_NAME[] = "rpmModel"; //!< rpm/tacho model name
    static constexpr char SPEEDO_MODEL_NAME[] = "speedoModel"; //!< speedometer model name
    static constexpr char TEMP_FUEL_CLUSTER_MODEL_NAME[] = "tempFuelModel"; //!< 240 combined temp/fuel model name
    static constexpr char ODOMETER_MODEL_NAME[] = "odometerModel";

    /**
     * @brief Constructor
     * @param parent: parent qobject
     * @param context: qml context to link the gauge models to their respective c++ model
     */
    Dash(QObject * parent, QQmlContext * context);

    ~Dash() final = default;
    /**
     * @brief Initialize everything
     */
    void init();

    /**
     * @brief Start dash event timers
     */
    void start() {
        mEventTiming.start();
    }

    /**
     * @brief Stop the dash event timers
     */
    void stop() {
        mEventTiming.stop();
    }

    const Config& getConfig() const {
        return mConfig;
    }

signals:
    void keyPress(QKeyEvent * event);

public slots:
    void odoTripReset(int trip);

private:
    QQmlContext * mContext; //!< QML Context
    EventTimers mEventTiming; //!< Event Timer
    Config mConfig; //!< Dash Config

    DashLights * mDashLights; //!< Dash lights

    AdcSource mAdcSource; //!< ADC source
    GpsSource mGpsSource; //!< GPS speed/position/heading source
    TachSource mTachSource; //!< tach source (pulse counter)
    VssSource mVssSource; //!< vehicle speed sensor source (pulse counter)
    CanSource mCanSource; //!< can data source

    Map_Sensor mMapSensor; //!< map sensor
    NtcSensor mCoolantTempSensor; //!< coolant temp sensor
    NtcSensor mAmbientTempSensor; //!< ambient temp sensor
    NtcSensor mOilTempSensor; //!< oil temp sensor
    VoltmeterSensor mVoltmeterSensor; //!< voltmeter sensor
    VoltmeterSensor mDimmerVoltageSensor; //!< rheostat dimmer voltage
    ResistiveSensor mOilPressureSensor; //!< oil pressure sensor
    ResistiveSensor mFuelLevelSensor; //!< fuel level sensor
    SpeedometerSensor<GpsSource> mGpsSpeedoSensor; //!< speedometer w/ gps input
    SpeedometerSensor<VssSource> mSpeedoSensor; //!< speedometer w/ vss input
    TachSensor mTachSensor; //!< tachometer sensor
    OdometerSensor mOdoSensor; //!< odometer
    OdometerSensor mTripAOdoSensor; //!< trip a counter
    OdometerSensor mTripBOdoSensor; //!< trip b counter

    AccessoryGaugeModel mBoostModel; //!< boost pressure QML model
    AccessoryGaugeModel mOilTemperatureModel; //!< oil temperature QML model
    AccessoryGaugeModel mCoolantTempModel; //!< coolant temperature QML model
    AccessoryGaugeModel mOilPressureModel; //!< oil pressure QML model
    AccessoryGaugeModel mFuelLevelModel; //!< fuel level QML model
    AccessoryGaugeModel mVoltMeterModel; //!< voltmeter QML model
    TempAndFuelGaugeModel mTempFuelModel; //!< 240 combined temp/fuel QML model
    OdometerModel mOdometerModel; //!< odometer QML model

    SpeedometerModel mSpeedoModel; //!< speedometer QML model
    TachometerModel mTachoModel; //!< Tachometer QML model

    std::unique_ptr<AccessoryGauge> mBoostGauge;
    std::unique_ptr<AccessoryGauge> mCoolantTempGauge; //!< coolant temp gauge
    std::unique_ptr<AccessoryGauge> mOilTempGauge; //!< oil temp gauge
    std::unique_ptr<AccessoryGauge> mVoltmeterGauge; //!< voltmeter gauge
    std::unique_ptr<AccessoryGauge> mOilPressureGauge; //!< oil pressure gauge
    std::unique_ptr<AccessoryGauge> mFuelLevelGauge; //!< fuel level gauge
    std::unique_ptr<TempFuelClusterGauge> mTempFuelClusterGauge; //!< 240 combined temp/fuel gauge

    std::unique_ptr<SpeedometerGauge> mSpeedoGauge; //!< speedometer gauge
    std::unique_ptr<TachometerGauge> mTachoGauge; //!< tachometer gauge
    std::unique_ptr<OdometerGauge> mOdoGauge; //!< odometer gauge

    std::unique_ptr<BackLightControl> mBacklightControl;

    std::vector<std::unique_ptr<CanSensor>> mCanSensors;

    /**
     * @brief Initialize sensor sources
     */
    void initSensorSources();

    /**
     * @brief Initialize the CAN sensors
     */
    void initCanSensors();

    /**
     * @brief Get can sensor
     * @param gaugeName Gauge name
     * @return pointer to the CAN sensor or nullptr
     */
    const CanSensor * getCanSensor(QString gaugeName);

    /**
     * @brief Initialize sensors and connect the sensor sources
     * to the appropriate sensors
     */
    void initSensors();

    /**
     * @brief Initialize the accessory gauges (coolant, fuel level, oil pressure/temp, etc)
     */
    void initAccessoryGauges();

    /**
     * @brief Initialize the speedometer
     */
    void initSpeedo();

    /**
     * @brief Initialize the tachometer
     */
    void initTacho();

    /**
     * @brief Initialize the odometer
     */
    void initOdometer();

    /**
     * @brief Initialize the dash lights and indicators
     */
    void initDashLights();

    /**
     * @brief Initialize the backlight control
     */
    void initBackLightControl();
};

#endif // DASH_H
