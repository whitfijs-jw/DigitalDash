#ifndef SCREEN_CONFIGS_H
#define SCREEN_CONFIGS_H

#include <qtypeinfo.h>
#include <QString>

namespace ScreenConfigs {
    /**
     * screen configuration settings
     */
    using ScreenConfig_t = struct SCREEN_CONFIG {
        bool use = false; //!< default don't use
        qreal screenRotationAngle = 180; //!< default for pi
    };
}

#endif // SCREEN_CONFIGS_H
