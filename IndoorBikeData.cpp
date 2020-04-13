#include "IndoorBikeData.h"
#include <QtEndian>

IndoorBikeData::IndoorBikeData(quint16 flags, const quint8 *data)
    :
      _moreData                   ( flags & 1),
      _averageSpeedPresent        ((flags >> 1)  & 1),
      _instantCadencePresent      ((flags >> 2)  & 1),
      _averageCadencePresent      ((flags >> 3)  & 1),
      _totalDistancePresent       ((flags >> 4)  & 1),
      _resistanceLevelPresent     ((flags >> 5)  & 1),
      _instantPowerPresent        ((flags >> 6)  & 1),
      _averagePowerPresent        ((flags >> 7)  & 1),
      _expendedEnergyPresent      ((flags >> 8)  & 1),
      _heartRatePresent           ((flags >> 9)  & 1),
      _metabolicEquivalentPresent ((flags >> 10) & 1),
      _elapsedTimePresent         ((flags >> 11) & 1),
      _remainingTimePresent       ((flags >> 12) & 1)
{
    uint16_t index=1;
    if(_moreData)
    {
        _instantSpeed = qFromLittleEndian<quint16>(data[index]);
        index += 2;
    }
    if (_averageSpeedPresent)
    {
        _averageSpeed = qFromLittleEndian<quint16>(data[index]);
        index += 2;
    }
    if (_instantCadencePresent)
    {
        _instantCadence = qFromLittleEndian<quint16>(data[index]);
        index += 2;
    }
    if (_averageCadencePresent)
    {
        _averageCadence = qFromLittleEndian<quint16>(data[index]);
        index +=2;
    }
    if (_totalDistancePresent)
    {
        // TODO! !?
        //_totalDistance = qFromLittleEndian
        _totalDistance = data[index] + (data[index+1]<<8) + (data[index+2]<<8); // ?
        index += 3;
    }
    if (_resistanceLevelPresent)
    {
        _resistanceLevel = qFromLittleEndian<qint16>(data[index]);
        index += 2;
    }
    if (_instantPowerPresent)
    {
        _instantPower = qFromLittleEndian<qint16>(data[index]);
        index += 2;
    }
    if (_averagePowerPresent)
    {
        _averagePower = qFromLittleEndian<qint16>(data[index]);
        index += 2;
    }
    if(_expendedEnergyPresent)
    {
        _totalEnergy = qFromLittleEndian<quint16>(data[index]);
        index += 2;
        _energyPerHour = qFromLittleEndian<quint16>(data[index]);
        index += 2;
        _energyPerMinute = qFromLittleEndian<quint8>(data[index]);
        index++;
    }
    if(_heartRatePresent)
    {
        _heartRate = qFromLittleEndian<quint8>(data[index]);
        index++;
    }
    if(_metabolicEquivalentPresent)
    {
        _metabolicEquivalent = qFromLittleEndian<quint8>(data[index]);
        index++;
    }
    if(_elapsedTimePresent)
    {
        _elapsedTime = qFromLittleEndian<quint16>(data[index]);
        index += 2;
    }
    if(_remainingTimePresent)
    {
        _remainingTime = qFromLittleEndian<quint16>(data[index]);
        index += 2;

    }
}

double IndoorBikeData::getInstantSpeedInKmPerSecond() const
{
    return _instantSpeed * 0.01;
}

double IndoorBikeData::getAverageSpeedInKmPerSecond() const
{
    return _averageSpeed * 0.01;
}

double IndoorBikeData::getInstantCadenceInRPM() const
{
    return _instantCadence * 0.5;
}

double IndoorBikeData::getAverageCadenceInRPM() const
{
    return _averageCadence * 0.5;
}

uint32_t IndoorBikeData::getTotalDistanceInMeters() const
{
    return _totalDistance;
}

int16_t IndoorBikeData::getResistanceLevel() const
{
    return _resistanceLevel;
}

int16_t IndoorBikeData::getInstantPowerInWatts() const
{
    return _instantPower;
}

int16_t IndoorBikeData::getAveragePowerInWatts() const
{
    return _averagePower;
}

uint16_t IndoorBikeData::getTotalEnergyInKiloCalorie() const
{
    return _totalEnergy;
}

uint16_t IndoorBikeData::getEnergyPerHourInKiloCalorie() const
{
    return _energyPerHour;
}

uint8_t IndoorBikeData::getEnergyPerMinuteInKiloCalorie() const
{
    return _energyPerMinute;
}

uint8_t IndoorBikeData::getBPM() const
{
    return _heartRate;
}

uint8_t IndoorBikeData::getMetabolicEquivalent() const
{
    return _metabolicEquivalent;
}

uint16_t IndoorBikeData::getElapsedTimeInSecs() const
{
    return _elapsedTime;
}

uint16_t IndoorBikeData::getRemainingTimeInSecs() const
{
    return _remainingTime;
}
