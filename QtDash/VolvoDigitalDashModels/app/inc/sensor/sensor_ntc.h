#ifndef SENSOR_NTC_H
#define SENSOR_NTC_H

#include <sensor.h>
#include <sensor_source_adc.h>
#include <ntc.h>

/**
 * @brief The NtcSensor class
 */
class NtcSensor : public Sensor {
public:
    static constexpr Units::TemperatureUnits NTC_INTERNAL_UNITS = Units::TemperatureUnits::FAHRENHEIT;

    /**
     * @brief NtcSensor constructor
     * @param parent: parent object
     * @param config: dash config
     * @param source: adc source
     * @param channel: adc channel
     * @param type: type of ntc sensor
     */
    NtcSensor(QObject * parent, Config * config,
              AdcSource * source, int channel,
              SensorConfig::TemperatureSensorType type) :
    Sensor(parent, config, source, channel) {

        // setup temp sensors
        QList<SensorConfig::TempSensorConfig> * tempSensorConfigs =
                mConfig->getTempSensorConfigs();

        for (SensorConfig::TempSensorConfig config : *tempSensorConfigs) {
            // use the sensor source vref
            config.vSupply = source->getVRef();

            // check if its a valid config
            if (config.isValid()) {
                if (config.type == type) {
                    mNtc = new Ntc(config);
                }
            } else {
                qDebug() << "Temperature Sensor Config is not valid: " << QString((int)config.type) << " Check config.ini file";
            }
        }
    }


    QString getUnits() const override {
        return Units::UNITS_F;
    }


public slots:
    /**
     * @brief transform adc votlage into temperature
     * @param data: adc votlage from adc source
     * @param channel: adc channel
     */
    void transform(const QVariant& data, int channel) override {
        if (channel == getChannel()) {
            qreal volts = data.toReal();

            qreal value = mNtc->calculateTemp(volts, NTC_INTERNAL_UNITS);
            qreal vRef = ((AdcSource *)mSource)->getVRef();
            // Check that we're not shorted to ground or VDD (could be disconnected)
            if (!SensorUtils::isValid(volts, vRef)) {
                value = 0;
            }

            emit sensorDataReady(value);
        }
    }

private:
    Ntc * mNtc;
};

#endif // SENSOR_NTC_H
