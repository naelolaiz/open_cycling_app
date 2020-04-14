#include "CyclingPowerMeasurementData.h"
#include <QtEndian>

CyclingPowerMeasurementData::CyclingPowerMeasurementData(const quint8 * data)
    : _flags(qFromLittleEndian<quint16>(data[0]))
    , _pedalBalancePresent(_flags & 1)
    , _pedalBalanceReferencePresent((_flags>>1) & 1)
    , _accumulatedTorquePresent((_flags>>2) & 1)
    , _accumulatedTorqueSourcePresent((_flags>>3) & 1)
    , _wheelRevolutionDataPresent((_flags>>4) & 1)
    , _crankRevolutionDataPresent((_flags>>5) & 1)
    , _extremeForceMagnitudesPresent((_flags>>6) & 1)
    , _extremeTorqueMagnitudesPresent((_flags>>7) & 1)
    , _extremeAnglesPresent((_flags>>8) & 1)
    , _topDeadSpotAnglePresent((_flags>>9) & 1)
    , _bottomDeadSpotAnglePresent((_flags>>10) & 1)
    , _accumulatedEnergyPresent((_flags>>11) & 1)
    , _offsetCompensationIndicator((_flags>>12) & 1)
{
    uint16_t index = 2;

    _instantPowerInWatts = qFromLittleEndian<qint16>(data[index]);
    index += 2;
    if(_pedalBalancePresent)
    {
        _pedalPowerBalance = data[index];
        index += 1;
    }
    if(_accumulatedTorquePresent)
    {
        _accumulatedTorque = qFromLittleEndian<quint16>(data[index]);
        index += 2;
    }
    if(_wheelRevolutionDataPresent)
    {
        _wheelRevolutions = data[index] + (data[index+1]<<8) + (data[index+2]<<16) + (data[index+3]<<24);
        //_wheelRevolutions = qFromLittleEndian<quint32>(data[index]);
        index += 4;
        _wheelRevolutionsLastEventTs = qFromLittleEndian<quint16>(data[index]);
        index += 2;
    }
    if(_crankRevolutionDataPresent)
    {
        _crankRevolutions = qFromLittleEndian<quint16>(data[index]);
        index += 2;
        _crankRevolutionsLastEventTs = qFromLittleEndian<quint16>(data[index]);
        index += 2;
    }
}

double CyclingPowerMeasurementData::getPowerBalance() const
{
    return _pedalPowerBalance * 0.5;
}

int16_t CyclingPowerMeasurementData::getInstantPowerInWatts() const
{
    return _instantPowerInWatts;
}
