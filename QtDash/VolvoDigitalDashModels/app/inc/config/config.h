#ifndef CONFIG_H
#define CONFIG_H

#include <QObject>
#include <QSettings>
#include <QDebug>

#include <iostream>
#include <memory>

#include <config_keys.h>
#include <can_frame_config.h>
#include <sensor_configs.h>
#include <gauge_configs.h>
#include <screen_configs.h>

#include <units.h>
#include <analog_12v_input.h>


/**
 * @brief Dash config class
 *
 * Configuration is read from a config.ini file.
 * These configurations are used to initialize
 * the sensor, tach, speedo, and dash light inputs
 * from the Dash hardware.
 */
class Config : public QObject {
Q_OBJECT
public:
    /**
     * @struct BacklightControlConfig
     */
    typedef struct BacklightControlConfig {
        qreal minDutyCycle;
        qreal maxDutyCycle;
        qreal lightsOffDutyCycle;
        qreal lightsOnDutyCycle;
        qreal minDimmerRatio;
        qreal maxDimmerRatio;
        bool useDimmer;
        bool activeLow;
    } BacklightControlConfig_t;

    static constexpr char DEFAULT_CONFIG_PATH[] = "/opt/config.ini"; //!< deafult config location
    static constexpr char DEFAULT_GAUGE_CONFIG_PATH[] = "/opt/config_gauges.ini"; //!< default gauge config location
    static constexpr char DEFAULT_ODO_CONFIG_PATH[] = "/opt/config_odo.ini"; //!< default odometer config location
    static constexpr char DEFAULT_CAN_CONFIG_PATH[] = "/opt/config_can.ini"; //!< default CAN frame config location

    /**
     * @brief Constructor
     * @param parent: Parent QObject
     * @param configPath: path to config.ini file (default is /opt/config.ini)
     */
    Config(QObject * parent,
           QString configPath = DEFAULT_CONFIG_PATH,
           QString gaugeConfigPath = DEFAULT_GAUGE_CONFIG_PATH,
           QString odoConfigPath = DEFAULT_ODO_CONFIG_PATH,
           QString canConfigPath = DEFAULT_CAN_CONFIG_PATH);

    bool isCanEnabled() const {
        return mEnableCan;
    }

    /**
     * @brief Load CAN frame configs
     * @return true if successful
     */
    bool loadCanFrameConfigs();

    /**
     * @brief Load odometer configs
     * @return true if successful
     */
    bool loadOdometerConfigs();

    /**
     * @brief Write odometer config
     * @param name config name
     * @param conf Odometer configuration
     * @return true if successful
     */
    bool writeOdometerConfig(QString name, SensorConfig::OdometerConfig conf);

    /**
     * @brief Load gauge configs from the .ini file
     * @return true if successful
     */
    bool loadGaugeConfigs();

    /**
     * @brief Load individual gauge config
     * @param groupName: Gauge group name
     * @return gauge config
     */
    GaugeConfig::GaugeConfig loadGaugeConfig(QString groupName);

    /**
     * @brief Load config from config.ini file
     * @return true on successful completion
     */
    bool loadConfig();

    bool loadScreenConfig();

    /**
     * @brief Print all child keys for the current config subgroup
     * @param setting: Group name to output to log
     */
    void printKeys(QString setting, const QSettings * config) const {
        for (auto key : config->childKeys()) {
            qDebug() << setting << key << ": " << config->value(key, "N/A").toStringList();
        }
    }

    /**
     * @brief Get dash light configuration
     * @return Dash light gpio configuration
     */
    QMap<QString, int> getDashLightConfig() const {
        return mDashLightConfig;
    }

    /**
     * @brief Get Sensor channel configuration
     * @return Sensor channel configuration
     */
    QMap<QString, int> getSensorConfig() const {
        return mSensorChannelConfig;
    }

    /**
     * @brief Get MAP sensor configuration
     * @return MAP sensor configuration
     */
    SensorConfig::MapSensorConfig getMapSensorConfig() const{
        return mMapSensorConfig;
    }

    /**
     * @brief Get temp sensor configurations
     * @return QList of temperature sensor configurations
     */
    QList<SensorConfig::TempSensorConfig> * getTempSensorConfigs(){
        return &mTempSensorConfigs;
    }

    /**
     * @brief Get Tach Input configuration
     * @return tach input configuration
     */
    SensorConfig::TachInputConfig getTachInputConfig() const {
        return mTachConfig;
    }

    /**
     * @brief Check if sensor channel config is valid
     * @return: sensor channel config
     */
    bool isSensorConfigValid() {
        return isMapConfigValid(&mSensorChannelConfig);
    }

    /**
     * @brief Check if the dash light config is valid
     * @return true if config is valid
     */
    bool isDashLightConfigValid() {
        return isMapConfigValid(&mDashLightConfig);
    }

    /**
     * @brief Get resistive sensor config
     * @param name: resistive sensor name
     * @return Sensor Config
     */
    SensorConfig::ResistiveSensorConfig getResistiveSensorConfig(QString name) const {
        SensorConfig::ResistiveSensorConfig empty;
        return mResistiveSensorConfig.value(name, empty);
    }

    /**
     * @brief Get 12V analog input config
     * @param name: 12 analog input name
     * @return input config
     */
    Analog12VInput::Analog12VInputConfig getAnalog12VInputConfig(QString name) const {
        Analog12VInput::Analog12VInputConfig empty;
        return mAnalog12VInputConfig.value(name, empty);
    }

    /**
     * @brief Get vehicle speed sensor config
     * @return
     */
    SensorConfig::VssInputConfig getVssConfig() const {
        return mVssInputConfig;
    }

    /**
     * @brief Get gauge config
     * @param name: gauge name
     * @return Gauge config
     */
    GaugeConfig::GaugeConfig getGaugeConfig(QString name) const {
        GaugeConfig::GaugeConfig empty;
        return mGaugeConfigs.value(name, empty);
    }

    /**
     * @brief Get speedo gauge config
     * @return Speedo gauge config
     */
    GaugeConfig::SpeedoConfig getSpeedoConfig() const {
        return mSpeedoGaugeConfig;
    }

    /**
     * @brief Get tachometer gauge config
     * @return Tachometer gauge config
     */
    GaugeConfig::TachoConfig getTachGaugeConfig() const {
        return mTachGaugeConfig;
    }

    /**
     * @brief Get odometer config
     * @param name odometer/trip counter name
     * @return Odometer config
     */
    SensorConfig::OdometerConfig getOdometerConfig(QString name) const {
        for (auto conf : mOdoConfig) {
            if (conf.name == name) {
                return conf;
            }
        }
        return {Units::DistanceUnits::MILE, 0, 0, ""};
    }

    /**
     * @brief Get the backlight config
     * @return backlight config
     */
    BacklightControlConfig_t getBackLightConfig() const {
        return mBacklightConfig;
    }

    /**
     * @brief Get the list of CAN frame configs
     * @return list of CAN frame configs
     */
    QList<CanFrameConfig> getCanFrameConfigs() const {
        return mCanFrameConfigs;
    }

    /**
     * @brief Get a CAN frame config
     * @param name name of the frame config
     * @return pointer to the config
     */
    CanFrameConfig * getCanFrameConfig(QString name) {
        for (int i = 0; i < mCanFrameConfigs.size(); i++) {
            if (mCanFrameConfigs[i].getName() == name) {
                return &mCanFrameConfigs[i];
            }
        }
        return nullptr;
    }

    /**
     * @brief Get user input configuration
     * @return Map of user input configs
     */
    QMap<int, Qt::Key> geUserInputConfig() const {
        return mUserInputConfig;
    }

    /**
     * @brief Get user input pin configs
     * @return Map of user input pin configs
     */
    QMap<QString, int> getUserInputPinConfig() const {
        return mUserInputPinConfig;
    }

    /**
     * @brief Get the sensor supply voltage specified in the config file
     * @return Sensor supply value specified in the config file or the default value
     * if not set.
     */
    qreal getSensorSupplyVoltage() const {
        return mSensorSupplyVoltage;
    }

    qreal getScreenRotation() const {
        if (mScreenConfig.use) {
            return mScreenConfig.screenRotationAngle;
        } else {
            return 180;
        }
    }

signals:

public slots:

private:
    std::unique_ptr<QSettings> mConfig = nullptr;  //!< QSettings for reading config.ini file
    QMap<QString, int> mSensorChannelConfig; //!< sensor channel configuration
    qreal mSensorSupplyVoltage = ConfigKeys::DEFAULT_V_SUPPLY; //!< Sensor supply voltage
    QMap<QString, int> mDashLightConfig; //!< dash light gpio configuration
    QMap<int, Qt::Key> mUserInputConfig; //!< user input configuration
    QMap<QString, int> mUserInputPinConfig; //!< user input pin configuration
    SensorConfig::MapSensorConfig mMapSensorConfig; //!< MAP sensor configuration
    QList<SensorConfig::TempSensorConfig> mTempSensorConfigs; //!< Temp sensor configurations
    SensorConfig::TachInputConfig mTachConfig; //!< Tach signal input configuration
    QMap<QString, SensorConfig::ResistiveSensorConfig> mResistiveSensorConfig; //!< Resistive sensor configs
    QMap<QString, Analog12VInput::Analog12VInputConfig> mAnalog12VInputConfig; //!< 12V analog configs
    ScreenConfigs::ScreenConfig_t mScreenConfig;

    std::unique_ptr<QSettings> mGaugeConfig = nullptr; //!< Gauge config QSettings
    QMap<QString, GaugeConfig::GaugeConfig> mGaugeConfigs; //!< map of gauge configs
    GaugeConfig::SpeedoConfig mSpeedoGaugeConfig; //!< speedo gauge config
    GaugeConfig::TachoConfig mTachGaugeConfig; //!< tacho gauge config
    SensorConfig::VssInputConfig mVssInputConfig; //!< vehicle speed sensor config

    std::unique_ptr<QSettings> mOdometerConfig = nullptr; //!< odometer configration QSettings
    QList<SensorConfig::OdometerConfig> mOdoConfig; //!< odometer config

    BacklightControlConfig_t mBacklightConfig; //!< backlight configuration

    std::unique_ptr<QSettings> mCanConfig; //!< can config Qsettings
    bool mEnableCan = false; //!< is Can enabled
    QList<CanFrameConfig> mCanFrameConfigs; //!< CAN frame configss

    /**
     * @brief Check that values are valid in a map
     * @param map: map to check
     * @return: true is map config values are valid
     */
    bool isMapConfigValid(QMap<QString, int> *map);

    /**
     * @brief Initialize User Input Keymap -- this is gross
     * @return User Input Key map
     */
    static QMap<QString, Qt::Key> initKeyMap();

    QMap<QString, Qt::Key> mKeyMap = initKeyMap(); //!< Key mappings

};

#endif // CONFIG_H
