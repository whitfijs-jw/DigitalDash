#ifndef SENSOR_CAN_H
#define SENSOR_CAN_H

#include <sensor.h>
#include <sensor_source_can.h>

/**
 * @brief The Map_Sensor class
 */
class CanSensor : public Sensor {
public:
    /**
     * @brief CAN bus sensor constructor
     * @param parent: parent object
     * @param config: dash config
     * @param source: can sensor source
     * @param channel: can data channel
     */
    CanSensor(QObject * parent, Config * config,
               CanSource * source, int channel) :
    Sensor(parent, config, source, channel) {
    }

    QString getUnits() override {
        return mSource->getUnits(mChannel);
    }

    QString getGuage() {
        CanFrameConfig conf = ((CanSource *)mSource)->getChannelConfig(mChannel);
        return conf.getGauge();
    }

public slots:
    /**
     * @brief Pass values on
     * @param data: data from CAN source
     * @param channel: adc channel
     */
    void transform(QVariant data, int channel) override {
        if (channel == getChannel()) {
            qreal value = data.toReal();
            emit sensorDataReady(value);
        }
    }

private:
};

#endif // SENSOR_CAN_H
