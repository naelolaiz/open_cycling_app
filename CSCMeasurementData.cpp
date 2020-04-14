#include "CSCMeasurementData.h"
#include <QtEndian>

CSCMeasurementData::CSCMeasurementData(const quint8 *data, const CSCMeasurementData * previousEvent)
    : _wheelRevolutionDataPresent  (data[0] & 1)
    , _crankRevolutionDataPresent  ((data[0] >> 1) & 1)
    , _previousWheelEventTimestamp(previousEvent  ? previousEvent->_lastWheelEventTimestamp : 0u)
    , _previousCrankEventTimestamp(previousEvent  ? previousEvent->_lastCrankEventTimestamp : 0u)
    , _accumulatedTimeForWheelEvents(previousEvent? previousEvent->_accumulatedTimeForWheelEvents : 0u)
    , _accumulatedTimeForCrankEvents(previousEvent? previousEvent->_accumulatedTimeForCrankEvents : 0u)
{
    uint16_t index = 1;
    if(_wheelRevolutionDataPresent)
    {
        _wheelRevolutions = data[index] + (data[index+1]<<8) + (data[index+2]<<16) + (data[index+3]<<24);
//        assert(_wheelRevolutions == qFromLittleEndian<quint32>(data[index]));
        index += 4;
        _lastWheelEventTimestamp = data[index] + (data[index+1]<<8);
        index += 2;
        if(_lastWheelEventTimestamp < _previousWheelEventTimestamp) // overflow happened
        {
            _accumulatedTimeForWheelEvents += 0xFFFF;
        }
    }
    if(_crankRevolutionDataPresent)
    {
        _crankRevolutions = data[index] + (data[index+1]<<8);
        index += 2;
        _lastCrankEventTimestamp = data[index] + (data[index+1]<<8);
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
