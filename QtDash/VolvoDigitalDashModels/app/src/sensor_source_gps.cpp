#include <sensor_source_gps.h>

GpsSource::GpsSource(QObject *parent, Config *config, QString name) :
    SensorSource(parent, config, name) {
    mLastData.insert(GpsDataChannel::HEADING_CARDINAL, "");
    mLastData.insert(GpsDataChannel::HEADING_DEGREES, 0.0);
    mLastData.insert(GpsDataChannel::SPEED_METERS_PER_SEC, 0.0);
    mLastData.insert(GpsDataChannel::SPEED_MILES_PER_HOUR, 0.0);
    mLastData.insert(GpsDataChannel::SPEED_KILOMETERS_PER_HOUR, 0.0);

    // serial port
    QVariantMap params;
    // TODO: get port from config? Find ACMx port?
    QString port = "/dev/ttyACM0";
    params["serialnmea.serial_port"] = port;
    QStringList sources = QGeoPositionInfoSource::availableSources();

    std::cout << "number of available data sources: " << sources.size() << std::endl;
    for (int i = 0; i < sources.size(); i++) {
        std::cout << sources.at(i).toLocal8Bit().constData() << std::endl;
    }

    QSerialPort * serialPort = new QSerialPort(this->parent());
    serialPort->setPortName(port);
    serialPort->setBaudRate(QSerialPort::Baud115200);
    serialPort->setDataBits(QSerialPort::Data8);
    serialPort->setParity(QSerialPort::NoParity);
    serialPort->setStopBits(QSerialPort::OneStop);
    serialPort->open(QIODevice::ReadOnly);

    if(serialPort->isOpen()) {
        QNmeaPositionInfoSource *source = new QNmeaPositionInfoSource(QNmeaPositionInfoSource::RealTimeMode);
        source->setDevice(serialPort);

        if(source){
            connect(source, &QNmeaPositionInfoSource::positionUpdated,
                    this, &GpsSource::updatePosition);

            source->setUpdateInterval(100);

            source->startUpdates();

            QObject::connect(this, &GpsSource::stop,
                             source, &QNmeaPositionInfoSource::stopUpdates);
        }
    }
}

QString GpsSource::getUnits(int channel) {
    switch ((GpsDataChannel)channel) {
    case GpsDataChannel::HEADING_CARDINAL:
        return "direction";
    case GpsDataChannel::HEADING_DEGREES:
        return "degrees";
    case GpsDataChannel::SPEED_METERS_PER_SEC:
        return "m/s";
    case GpsDataChannel::SPEED_MILES_PER_HOUR:
        return "mph";
    case GpsDataChannel::SPEED_KILOMETERS_PER_HOUR:
        return "kph";
    default:
        return "";
    }
}

void GpsSource::updatePosition(QGeoPositionInfo data) {
    if (data.hasAttribute(QGeoPositionInfo::Direction)) {
        qreal heading = data.attribute(QGeoPositionInfo::Direction);

#ifdef RASPBERRY_PI
        // setting time -- this is gross
        if (!mTimeSet) {
            auto ts = data.timestamp();

            auto coord = data.coordinate();
            auto tz = guessAtTheTimeZone(coord);
            //ts.setTimeZone(tz);

            std::cout << "Timezone? maybe?: " << tz.abbreviation(ts).toStdString() << std::endl;

            QString pg = "/bin/date";
            QStringList args;
            args << "-s" << ts.toString("yyyy-MM-dd hh:mm:ss") << "-u";

            QProcess *proc = new QProcess(this);

            QObject::connect(proc, static_cast<void(QProcess::*)(int, QProcess::ExitStatus)>(&QProcess::finished),
                             [=](int exitCode, QProcess::ExitStatus exitStatus) {
                                 (void)exitStatus;
                                 std::cout << "finished date set: " << exitCode << std::endl;
                             });

            proc->startDetached(pg, args);
            mTimeSet = true;

            std::cout << "Set Time to: " << ts.toString("yyyy-MM-dd hh:mm:ss").toStdString() << std::endl;
        }
#endif

        QString headingString = headingToDirectionString(heading);
        //std::cout << "heading: " << heading << " (" << headingString.toStdString() << ")" << std::endl;

        emit dataReady(heading, (int) GpsDataChannel::HEADING_DEGREES);
        emit dataReady(headingString, (int) GpsDataChannel::HEADING_CARDINAL);

        mLastData.insert(GpsDataChannel::HEADING_DEGREES, heading);
        mLastData.insert(GpsDataChannel::HEADING_CARDINAL, headingString);
    }
    double speed = data.attribute(QGeoPositionInfo::GroundSpeed);

    qreal speedMph = SensorUtils::convert(speed, Units::UNITS_MPH, Units::UNITS_METERS_PER_SECOND);
    qreal speedKph = SensorUtils::convert(speed, Units::UNITS_KPH, Units::UNITS_METERS_PER_SECOND);

    mLastData.insert(GpsDataChannel::SPEED_METERS_PER_SEC, speed);
    mLastData.insert(GpsDataChannel::SPEED_MILES_PER_HOUR, speedMph);
    mLastData.insert(GpsDataChannel::SPEED_KILOMETERS_PER_HOUR, speedKph);

    emit dataReady(speed, (int) GpsDataChannel::SPEED_METERS_PER_SEC);
    emit dataReady(speedMph, (int) GpsDataChannel::SPEED_MILES_PER_HOUR);
    emit dataReady(speedKph, (int) GpsDataChannel::SPEED_KILOMETERS_PER_HOUR);
}

QTimeZone GpsSource::guessAtTheTimeZone(QGeoCoordinate coord) {
    // this is more gross
    std::cout << "Current longitude: " << coord.longitude() << std::endl;

    int offset = qRound(coord.longitude() / 15.0) * 3600;
    return QTimeZone(offset);
}

GpsSource::CardinalDirection GpsSource::headingToDirection(qreal angle) {
    if (angle < 0) {
        angle += 360.0;
    }

    int iAngle = std::floor(angle);
    iAngle = std::floor(static_cast<qreal>(iAngle) + 22.5);
    int dir = (iAngle % 360) / 45;

    return (CardinalDirection) dir;
}

QString GpsSource::headingToDirectionString(qreal angle) {
    auto dir = headingToDirection(angle);

    switch (dir) {
    case CardinalDirection::NORTH:
    case CardinalDirection::NORTH_1:
        return "N";
    case CardinalDirection::NORTH_EAST:
        return "NE";
    case CardinalDirection::EAST:
        return "E";
    case CardinalDirection::SOUTH_EAST:
        return "SE";
    case CardinalDirection::SOUTH:
        return "S";
    case CardinalDirection::SOUTH_WEST:
        return "SW";
    case CardinalDirection::WEST:
        return "W";
    case CardinalDirection::NORTH_WEST:
        return "NW";
    default:
        return "N";
    }

    return "";
}
