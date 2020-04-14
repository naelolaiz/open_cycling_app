#include "CyclingPowerMeasurementData.h"
#include <QtEndian>

CyclingPowerMeasurementData::CyclingPowerMeasurementData(quint16 flags, const quint8 * data)
    : _pedalBalancePresent(flags & 1)
    , _pedalBalanceReferencePresent((flags>>1) & 1)
    , _accumulatedTorquePresent((flags>>2) & 1)
    , _accumulatedTorqueSourcePresent((flags>>3) & 1)
    , _wheelRevolutionDataPresent((flags>>4) & 1)
    , _crankRevolutionDataPresent((flags>>5) & 1)
    , _extremeForceMagnitudesPresent((flags>>6) & 1)
    , _extremeTorqueMagnitudesPresent((flags>>7) & 1)
    , _extremeAnglesPresent((flags>>8) & 1)
    , _topDeadSpotAnglePresent((flags>>9) & 1)
    , _bottomDeadSpotAnglePresent((flags>>10) & 1)
    , _accumulatedEnergyPresent((flags>>11) & 1)
    , _offsetCompensationIndicator((flags>>12) & 1)
{
    uint16_t index =1;

    _instantPowerInWatts = qFromLittleEndian<qint16>(data[index]);
    index += 2;
    if(_pedalBalancePresent)
    {
        _pedalPowerBalance = qFromLittleEndian<quint8>(data[index]);
        index += 1;
    }
    if(_accumulatedTorquePresent)
    {
        _accumulatedTorque = qFromLittleEndian<quint16>(data[index]);
        index += 2;
    }
    if(_wheelRevolutionDataPresent)
    {
        _wheelRevolutions = qFromLittleEndian<quint32>(data[index]);
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
