#include <map_test.h>

void MapTest::testGetAbsolutePressure()
{
    QFETCH(qreal, pressure0V);
    QFETCH(qreal, pressure5V);
    QFETCH(int, units);
    QFETCH(qreal, volts);
    QFETCH(qreal, expected_kpa);
    QFETCH(qreal, expected_psi);

    MapSensor * sensor = new MapSensor(pressure0V, pressure5V, 5.0, (Units::PressureUnits)units);

    // kpa values
    qreal actual = sensor->getAbsolutePressure(volts, Units::PressureUnits::KPA);
    qreal expected = expected_kpa;
    qreal delta = MapTest::DELTA;
    qDebug() << "Actual: " << actual << " Expected: " << expected;
    QVERIFY(actual-delta <= expected && actual+delta >=expected);

    // psi values
    actual = sensor->getAbsolutePressure(volts, Units::PressureUnits::PSI);
    expected = expected_psi;
    delta = MapTest::DELTA * .145038;
    qDebug() << "Actual: " << actual << " Expected: " << expected;
    QVERIFY(actual-delta <= expected && actual+delta >=expected);

    // bar values (kPa / 100)
    actual = sensor->getAbsolutePressure(volts, Units::PressureUnits::BAR);
    expected = expected_kpa / 100.0;
    delta = MapTest::DELTA / 100.0;
    qDebug() << "Actual: " << actual << " Expected: " << expected;
    QVERIFY(actual-delta <= expected && actual+delta >=expected);

    delete(sensor);
}

void MapTest::testGetAbsolutePressure_data() {
    typedef struct {
        qreal oneBar;
        qreal twoBar;
        qreal threeBar;
    } map_pressures_t;

    QMap<qreal, map_pressures_t> GMMapExpectedValues;

    // some values I found on the internet, perfect
    GMMapExpectedValues[0.00] = {10.0, 8.8, 3.6};
    GMMapExpectedValues[0.25] = {15, 18, 17};
    GMMapExpectedValues[0.50] = {20, 28, 33};
    GMMapExpectedValues[0.75] = {24, 38, 48};
    GMMapExpectedValues[1.00] = {29, 48, 64};
    GMMapExpectedValues[1.25] = {34, 58, 80};
    GMMapExpectedValues[1.50] = {39, 68, 96};
    GMMapExpectedValues[1.75] = {43, 78, 111};
    GMMapExpectedValues[2.00] = {48, 88, 127};
    GMMapExpectedValues[2.25] = {53, 98, 143};
    GMMapExpectedValues[2.50] = {58, 108, 159};
    GMMapExpectedValues[2.75] = {62, 118, 174};
    GMMapExpectedValues[3.00] = {67, 128, 190};
    GMMapExpectedValues[3.25] = {72, 138, 206};
    GMMapExpectedValues[3.50] = {77, 148, 222};
    GMMapExpectedValues[3.75] = {82, 158, 237};
    GMMapExpectedValues[4.00] = {87, 168, 253};
    GMMapExpectedValues[4.25] = {91, 178, 269};
    GMMapExpectedValues[4.50] = {96, 188, 285};
    GMMapExpectedValues[4.75] = {100, 198, 300};
    GMMapExpectedValues[5.0] = {105, 208, 315};

    QTest::addColumn<qreal>("pressure0V");
    QTest::addColumn<qreal>("pressure5V");
    QTest::addColumn<int>("units");
    QTest::addColumn<qreal>("volts");
    QTest::addColumn<qreal>("expected_kpa");
    QTest::addColumn<qreal>("expected_psi");

    QMapIterator<qreal, map_pressures_t> iter(GMMapExpectedValues);
    while(iter.hasNext()) {
        iter.next();
        QString rowName;

        // kPa calibration data
        QTextStream(&rowName) << "1bar-" << iter.key();
        QTest::newRow(rowName.toStdString().c_str())
                << 10.0
                << 105.0
                << (int) Units::PressureUnits::KPA
                << iter.key()
                << iter.value().oneBar
                << iter.value().oneBar * .145038;

        rowName.clear();
        QTextStream(&rowName) << "2bar-" << iter.key();
        QTest::newRow(rowName.toStdString().c_str())
                << 8.8
                << 208.0
                << (int) Units::PressureUnits::KPA
                << iter.key()
                << iter.value().twoBar
                << iter.value().twoBar * .145038;

        rowName.clear();
        QTextStream(&rowName) << "3bar-" << iter.key();
        QTest::newRow(rowName.toStdString().c_str())
                << 3.6
                << 315.0
                << (int) Units::PressureUnits::KPA
                << iter.key()
                << iter.value().threeBar
                << iter.value().threeBar * .145038;

        // psi calibration data
        rowName.clear();
        QTextStream(&rowName) << "1bar-" << iter.key() <<"-psi-calib";
        QTest::newRow(rowName.toStdString().c_str())
                << 10.0 * .145038
                << 105.0 * .145038
                << (int) Units::PressureUnits::PSI
                << iter.key()
                << iter.value().oneBar
                << iter.value().oneBar * .145038;

        rowName.clear();
        QTextStream(&rowName) << "2bar-" << iter.key() <<"-psi-calib";
        QTest::newRow(rowName.toStdString().c_str())
                << 8.8 * .145038
                << 208.0 * .145038
                << (int) Units::PressureUnits::PSI
                << iter.key()
                << iter.value().twoBar
                << iter.value().twoBar * .145038;

        rowName.clear();
        QTextStream(&rowName) << "3bar-" << iter.key() <<"-psi-calib";
        QTest::newRow(rowName.toStdString().c_str())
                << 3.6 * .145038
                << 315.0 * .145038
                << (int) Units::PressureUnits::PSI
                << iter.key()
                << iter.value().threeBar
                << iter.value().threeBar * .145038;
    }
}
