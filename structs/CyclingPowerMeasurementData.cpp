#include "CyclingPowerMeasurementData.h"
#include <QtEndian>
#include <sstream>

CyclingPowerMeasurementData::CyclingPowerMeasurementData(const quint8* data)
  : _flags(qFromLittleEndian<quint16>(data[0]))
{
  uint16_t index = 2;

  _instantPowerInWatts = data[index] + (data[index + 1] << 8);
  index += 2;
  if (isPedalBalancePresent()) {
    _pedalPowerBalance = data[index];
    index += 1;
  }
  if (isAccumulatedTorquePresent()) {
    _accumulatedTorque = data[index] + (data[index + 1] << 8);
    index += 2;
  }
  if (isWheelRevolutionDataPresent()) {
    _wheelRevolutions = data[index] + (data[index + 1] << 8) +
                        (data[index + 2] << 16) + (data[index + 3] << 24);
    //_wheelRevolutions = qFromLittleEndian<quint32>(data[index]);
    index += 4;
    _wheelRevolutionsLastEventTs = data[index] + (data[index + 1] << 8);
    index += 2;
  }
  if (isCrankRevolutionDataPresent()) {
    _crankRevolutions = data[index] + (data[index + 1] << 8);
    index += 2;
    _crankRevolutionsLastEventTs = data[index] + (data[index + 1] << 8);
    index += 2;
  }
}

double
CyclingPowerMeasurementData::getPowerBalance() const
{
  return _pedalPowerBalance * 0.5;
}

int16_t
CyclingPowerMeasurementData::getInstantPowerInWatts() const
{
  return _instantPowerInWatts;
}

QBluetoothUuid
CyclingPowerMeasurementData::getCharUuid()
{
  return QBluetoothUuid::CyclingPowerMeasurement;
}

std::string
CyclingPowerMeasurementData::dump() const
{
  std::stringstream s;
  s << "Power Balance: " << getPowerBalance() << "%" << std::endl;
  s << "Instant Power: " << getInstantPowerInWatts() << " Watts" << std::endl;
  return s.str();
}

bool
CyclingPowerMeasurementData::operator==(
  const CyclingPowerMeasurementData& other) const
{
  return this->_flags == other._flags &&
         this->_instantPowerInWatts == other._instantPowerInWatts &&
         this->_pedalPowerBalance == other._pedalPowerBalance &&
         this->_accumulatedTorque == other._accumulatedTorque &&
         this->_wheelRevolutions == other._wheelRevolutions &&
         this->_wheelRevolutionsLastEventTs ==
           other._wheelRevolutionsLastEventTs &&
         this->_crankRevolutions == other._crankRevolutions &&
         this->_crankRevolutionsLastEventTs ==
           other._crankRevolutionsLastEventTs &&
         this->_extremeMaxForceMagnitudesInNewtons ==
           other._extremeMaxForceMagnitudesInNewtons &&
         this->_extremeMinForceMagnitudesInNewtons ==
           other._extremeMinForceMagnitudesInNewtons &&
         this->_extremeMaxTorqueMagnitudesInNewtonsMetres ==
           other._extremeMaxTorqueMagnitudesInNewtonsMetres &&
         this->_extremeMinTorqueMagnitudesInNewtonsMetres ==
           other._extremeMinTorqueMagnitudesInNewtonsMetres;
  // TODO
}

bool
CyclingPowerMeasurementData::operator!=(
  const CyclingPowerMeasurementData& other) const
{
  return !(*this == other);
}

bool
CyclingPowerMeasurementData::isPedalBalancePresent()
{
  return (_flags & 1);
}

bool
CyclingPowerMeasurementData::isPedalBalanceReferencePresent()
{
  return ((_flags >> 1) & 1);
}

bool
CyclingPowerMeasurementData::isAccumulatedTorquePresent()
{
  return ((_flags >> 2) & 1);
}

bool
CyclingPowerMeasurementData::isAccumulatedTorqueSourcePresent()
{
  return ((_flags >> 3) & 1);
}

bool
CyclingPowerMeasurementData::isWheelRevolutionDataPresent()
{
  return ((_flags >> 4) & 1);
}

bool
CyclingPowerMeasurementData::isCrankRevolutionDataPresent()
{
  return ((_flags >> 5) & 1);
}

bool
CyclingPowerMeasurementData::isExtremeForceMagnitudesPresent()
{
  return ((_flags >> 6) & 1);
}

bool
CyclingPowerMeasurementData::isExtremeTorqueMagnitudesPresent()
{
  return ((_flags >> 7) & 1);
}

bool
CyclingPowerMeasurementData::isExtremeAnglesPresent()
{
  return ((_flags >> 8) & 1);
}

bool
CyclingPowerMeasurementData::isTopDeadSpotAnglePresent()
{
  return ((_flags >> 9) & 1);
}

bool
CyclingPowerMeasurementData::isBottomDeadSpotAnglePresent()
{
  return ((_flags >> 10) & 1);
}

bool
CyclingPowerMeasurementData::isAccumulatedEnergyPresent()
{
  return ((_flags >> 11) & 1);
}

bool
CyclingPowerMeasurementData::isOffsetCompensationIndicatorPresent()
{
  return ((_flags >> 12) & 1);
}
