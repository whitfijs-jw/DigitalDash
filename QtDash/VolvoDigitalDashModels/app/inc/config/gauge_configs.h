#ifndef GAUGE_CONFIGS_H
#define GAUGE_CONFIGS_H

#include <qtypeinfo.h>
#include <QString>

namespace GaugeConfig {

    /**
     * @ Struc AltDisplayUnits
     */
    using AltDisplayUnits = struct altDisplayUnits {
        bool use = false;
        bool aboveCutoff = false;
        qreal cutoff;
        QString displayUnits;

        bool checkCutoff(qreal val) {
            if (aboveCutoff) {
                return val > cutoff;
            } else {
                return val < cutoff;
            }
        }
    };

    /**
     * @struct GaugeConfig
     */
    using GaugeConfig = struct gaugeConfig {
        qreal min; //!< minimum gauge value
        qreal max; //!< maxuimum gauge value
        qreal lowAlarm; //!< low alarm
        qreal highAlarm; //!< high alarm
        QString displayUnits; //!< display units
        AltDisplayUnits altDisplayUnits;
    };

    /**
     * @struct SpeedoConfig
     */
    using SpeedoConfig = struct speedoConfig {
        GaugeConfig gaugeConfig; //!< Gauge config
        QString topSource; //!< secondary display source
        QString topUnits; //!< secondary display units
    };

    /**
     * @struct TachoConfig
     */
    using TachoConfig = struct tachConfig {
        qreal maxRpm; //!< maximum rpm -- lowest possible value will help filter out noisier data
        qreal redline; //!< defines when numerical RPM indication will turn red
    };
}

#endif // GAUGE_CONFIGS_H
