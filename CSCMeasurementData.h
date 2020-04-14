#ifndef CSCMEASUREMENTDATA_H
#define CSCMEASUREMENTDATA_H

#include <QtGlobal>
#include <cstdint>

class CSCMeasurementData
{
public:
    CSCMeasurementData(quint8 flags, const quint8 * data, const CSCMeasurementData *previousValue);

    uint32_t getWheelRevolutions() const;
    uint16_t getCrankRevolutions() const;
    double getLastWheelEventTimestampInSecs() const;

    double getLastCrankEventTimestampInSecs() const;

private:
    const bool _wheelRevolutionDataPresent{false};
    const bool _crankRevolutionDataPresent{false};
    const uint16_t _previousWheelEventTimestamp;
    const uint16_t _previousCrankEventTimestamp;
    uint64_t _accumulatedTimeForWheelEvents{0u};
    uint64_t _accumulatedTimeForCrankEvents{0u};

    uint32_t _wheelRevolutions{0u};
    uint16_t _lastWheelEventTimestamp{0u};
    uint16_t _crankRevolutions{0u};
    uint16_t _lastCrankEventTimestamp{0u};

};

#endif // CSCMEASUREMENTDATA_H
