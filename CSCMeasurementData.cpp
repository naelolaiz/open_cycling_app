#include "CSCMeasurementData.h"
#include <QtEndian>

CSCMeasurementData::CSCMeasurementData(quint8 flags, const quint8 *data, const CSCMeasurementData * previousEvent)
    : _wheelRevolutionDataPresent  (flags & 1)
    , _crankRevolutionDataPresent  ((flags >> 1) & 1)
    , _previousWheelEventTimestamp(previousEvent  ? previousEvent->_lastWheelEventTimestamp : 0u)
    , _previousCrankEventTimestamp(previousEvent  ? previousEvent->_lastCrankEventTimestamp : 0u)
    , _accumulatedTimeForWheelEvents(previousEvent? previousEvent->_accumulatedTimeForWheelEvents : 0u)
    , _accumulatedTimeForCrankEvents(previousEvent? previousEvent->_accumulatedTimeForCrankEvents : 0u)
{
    uint16_t index = 1;
    if(_wheelRevolutionDataPresent)
    {
        _wheelRevolutions = qFromLittleEndian<quint32>(data[index]);
        index += 4;
        _lastWheelEventTimestamp = qFromLittleEndian<quint16>(data[index]);
        index += 2;
        if(_lastWheelEventTimestamp < _previousWheelEventTimestamp) // overflow happened
        {
            _accumulatedTimeForWheelEvents += 0xFFFF;
        }
    }
    if(_crankRevolutionDataPresent)
    {
        _crankRevolutions = qFromLittleEndian<quint16>(data[index]);
        index += 2;
        _lastCrankEventTimestamp = qFromLittleEndian<quint16>(data[index]);
        index += 2;
        if(_lastCrankEventTimestamp < _previousCrankEventTimestamp) // overflow happened
        {
            _accumulatedTimeForCrankEvents += 0xFFFF;
        }
    }

}

uint32_t CSCMeasurementData::getWheelRevolutions() const
{
    return _wheelRevolutions;
}

uint16_t CSCMeasurementData::getCrankRevolutions() const
{
    return _crankRevolutions;
}

double CSCMeasurementData::getLastWheelEventTimestampInSecs() const
{
    return (_accumulatedTimeForWheelEvents + _lastWheelEventTimestamp) / 1024.;
}

double CSCMeasurementData::getLastCrankEventTimestampInSecs() const
{
    return (_accumulatedTimeForCrankEvents + _lastCrankEventTimestamp) / 1024.;
}
