#include "VariousStructs.h"
#include <QtEndian>

SupportedPowerRange::SupportedPowerRange(const quint8 *data)
    : _minimumPowerInWatts(qFromLittleEndian<qint16>(data[0]))
    , _maximumPowerInWatts(qFromLittleEndian<qint16>(data[2]))
    , _minimumIncrementInWatts(qFromLittleEndian<quint16>(data[4]))
{
}

int16_t SupportedPowerRange::getMinimumPowerInWatts() const
{
    return _minimumPowerInWatts;
}

int16_t SupportedPowerRange::getMaximumPowerInWatts() const
{
    return _maximumPowerInWatts;
}

uint16_t SupportedPowerRange::getMinimumIncrementInWatts() const
{
    return _minimumIncrementInWatts;
}

std::stringstream SupportedPowerRange::dump()
{
    std::stringstream s;
    s<< "min pow level in watts: "<< _minimumPowerInWatts << std::endl;
    s<< "max pow level in watts: "<< _maximumPowerInWatts << std::endl;
    s<< "min pow increment in watts: "<< _minimumIncrementInWatts << std::endl;
    return s;
}

SupportedResistanceLevelRange::SupportedResistanceLevelRange(const quint8 *data)
    : _minimumResistanceLevel(qFromLittleEndian<qint16>(data[0]))
    , _maximumResistanceLevel(qFromLittleEndian<qint16>(data[2]))
    , _minimumIncrement(qFromLittleEndian<quint16>(data[4]))
{
}

int16_t SupportedResistanceLevelRange::getMinimumResistanceLevel() const
{
    return _minimumResistanceLevel;
}

int16_t SupportedResistanceLevelRange::getMaximumResistanceLevel() const
{
    return _maximumResistanceLevel;
}

int16_t SupportedResistanceLevelRange::getMinimumIncrement() const
{
    return _minimumIncrement;
}

std::stringstream SupportedResistanceLevelRange::dump()
{
    std::stringstream s;
    s<< "min res level: "<< _minimumResistanceLevel << std::endl;
    s<< "max res level: "<< _maximumResistanceLevel << std::endl;
    s<< "min res increment: "<< _minimumIncrement << std::endl;
    return s;
}
