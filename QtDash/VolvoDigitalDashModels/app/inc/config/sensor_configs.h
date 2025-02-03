#ifndef SENSOR_CONFIGS_H
#define SENSOR_CONFIGS_H

#include <units.h>

namespace SensorConfig {
    static constexpr qreal INVALID_TEMP = -459.67; // value if temp could not be read

    /*
    * @brief The ResistiveSensorType enum
    */
    using ResistiveSensorType = enum class ResistiveSensorType_t {
        INTERPOLATION = 0, //!< interpolate calibration data
        POLYNOMIAL, //!< fit polynomial to calibration data
    };

    /**
     * @brief TemperatureSensorType enum
     */
    enum class TemperatureSensorType {
        COOLANT = 0, //!< Coolant temp sensor
        OIL, //!< Oil temp sensor
        AMBIENT, //!< Outside/Ambient temp sensor
    };

    /**
     * @struct Resistive Sensor config
     */
    using ResistiveSensorConfig = struct resistiveSensorConfig {
        QString type; //!< sensor type
        ResistiveSensorType fitType; //!< @ref ResistiveSensorType
        QList<qreal> x; //!< calibration x data
        QList<qreal> y; //!< calibration y data
        QList<qreal> coeff; //!< coefficients for polynomial fit only
        int order; //!< polynomial order -- polynomial only
        qreal rBalance; //!< balance resistor value in ohms
        QString units; //!< calibration data units
        qreal lag; //!< filtering value (0-1)
        qreal lagStart; //!< start lag value
        qreal lagDecay; //!< lag decay constant
        qreal vSupply; //!< supply voltage

        /**
         * @brief isValid
         * @return is config valid
         */
        bool isValid() {
            return true; //TODO: yea
        }
    };

    /**
     * @struct MapSensorConfig
     */
    using MapSensorConfig = struct mapSensorConfig {
        qreal p0V; //!< pressure when sensor reads 0V
        qreal p5V; //!< pressure when sensor reads 5V
        qreal pAtm; //!< atmpsheric pressure
        Units::PressureUnits units; //!< units of calibration pressures

        /**
         * @brief Check if calibration is valid
         * @return true if valid
         */
        bool isValid() {
            // we're assuming absolute pressure.
            return (p0V >= 0) && (p5V != p0V);
        }
    };

    /**
     * @struct TempSensorConfig
     */
    using TempSensorConfig = struct tempSensorConfig {
        qreal rBalance; //!< balance resistor (everything should be high side)
        qreal vSupply; //!< Voltage supply (should be 5V on Dash Hardware)
        qreal t1; //!< Steinhart-Hart T1 (first calibration temperature)
        qreal t2; //!< Steinhart-Hart T2
        qreal t3; //!< Steinhart-Hart T3
        qreal r1; //!< NTC resistance at T1
        qreal r2; //!< NTC resistance at T2
        qreal r3; //!< NTC resistance at T3
        Units::TemperatureUnits units; //!< units of calibration temperature
        TemperatureSensorType type; //!< Temp Sensor type -- coolant, oil, outside/ambient...

        /**
         * @brief Check if configuration is valid
         * @return true if valid
         */
        bool isValid() {
            return (t1 >= INVALID_TEMP) &&
                   (t2 >= INVALID_TEMP) &&
                   (t3 >= INVALID_TEMP) &&
                   (r1 > 0) &&
                   (r2 > 0) &&
                   (r3 > 0) &&
                   (vSupply > 0) &&
                   (rBalance > 0);

        }
    };

    /**
     * @struct TachInputConfig
     */
    using TachInputConfig = struct tachInputConfig {
        int pulsesPerRot; //!< tach pulses per rotation
        int maxRpm; //!< max valid rpm
        int avgNumSamples; //!< number of samples to average over
    };

    /**
     * @struct VssInputConfig
     */
    using VssInputConfig = struct vssInputConfig {
        int pulsePerRot; //!< Number of pulses from VSS sensor per rotation of the tire
        qreal tireDiameter; //!< tire diameter
        Units::DistanceUnits tireDiameterUnits; //!< tire diameter units @ref DistanceUnits
        int pulsePerUnitDistance; //!< Pulses per unit distance.  Will be calculated from tire diameter if left empty
        Units::DistanceUnits distanceUnits; //!< unit of distance for pulsePerUnitDistance
        int maxSpeed; //!< Max speed -- lowest possible value it best will filter out noisy signals better
        bool useGps = false;
    };

    /**
     * @struct OdometerConfig
     */
    using OdometerConfig = struct odometerConfig {
        Units::DistanceUnits units; //!< odometer internal units
        qreal value; //!< odometer value (in above units)
        int writeInterval; //!< number of pulses between writing to back to non-volatile memory
        QString name;
    };
}

#endif // SENSOR_CONFIGS_H
