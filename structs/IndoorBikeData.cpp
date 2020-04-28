#include "IndoorBikeData.h"
#include <QtEndian>
#include <sstream>

IndoorBikeData::IndoorBikeData(const quint8* data)
  : _flags(qFromLittleEndian<quint16>(data[0]))
{
  uint16_t index = 2;
  if (haveMoreData()) {
    _instantSpeed = data[index] + (data[index + 1] << 8);
    index += 2;
  }
  if (isAverageSpeedPresent()) {
    _averageSpeed = data[index] + (data[index + 1] << 8);
    index += 2;
  }
  if (isInstantCadencePresent()) {
    _instantCadence = data[index] + (data[index + 1] << 8);
    index += 2;
  }
  if (isAverageCadencePresent()) {
    _averageCadence = data[index] + (data[index + 1] << 8);
    index += 2;
  }
  if (isTotalDistancePresent()) {
    // TODO! !?
    //_totalDistance = qFromLittleEndian
    _totalDistance =
      data[index] + (data[index + 1] << 8) + (data[index + 2] << 16); // ?
    index += 3;
  }
  if (isResistanceLevelPresent()) {
    _resistanceLevel = data[index] + (data[index + 1] << 8);
    index += 2;
  }
  if (isInstantPowerPresent()) {
    _instantPower = data[index] + (data[index + 1] << 8);
    index += 2;
  }
  if (isAveragePowerPresent()) {
    _averagePower = data[index] + (data[index + 1] << 8);
    index += 2;
  }
  if (isExpendedEnergyPresent()) {
    _totalEnergy = data[index] + (data[index + 1] << 8);
    index += 2;
    _energyPerHour = data[index] + (data[index + 1] << 8);
    index += 2;
    _energyPerMinute = reinterpret_cast<quint8>(data[index]);
    index++;
  }
  if (isHeartRatePresent()) {
    _heartRate = reinterpret_cast<quint8>(data[index]);
    index++;
  }
  if (isMetabolicEquivalentPresent()) {
    _metabolicEquivalent = reinterpret_cast<quint8>(data[index]);
    index++;
  }
  if (isElapsedTimePresent()) {
    _elapsedTime = data[index] + (data[index + 1] << 8);
    index += 2;
  }
  if (isRemainingTimePresent()) {
    _remainingTime = data[index] + (data[index + 1] << 8);
    index += 2;
  }
}

double
IndoorBikeData::getInstantSpeedInKmPerSecond() const
{
  return _instantSpeed * 0.01;
}

double
IndoorBikeData::getAverageSpeedInKmPerSecond() const
{
  return _averageSpeed * 0.01;
}

double
IndoorBikeData::getInstantCadenceInRPM() const
{
  return _instantCadence * 0.5;
}

double
IndoorBikeData::getAverageCadenceInRPM() const
{
  return _averageCadence * 0.5;
}

uint32_t
IndoorBikeData::getTotalDistanceInMeters() const
{
  return _totalDistance;
}

int16_t
IndoorBikeData::getResistanceLevel() const
{
  return _resistanceLevel;
}

int16_t
IndoorBikeData::getInstantPowerInWatts() const
{
  return _instantPower;
}

int16_t
IndoorBikeData::getAveragePowerInWatts() const
{
  return _averagePower;
}

uint16_t
IndoorBikeData::getTotalEnergyInKiloCalorie() const
{
  return _totalEnergy;
}

uint16_t
IndoorBikeData::getEnergyPerHourInKiloCalorie() const
{
  return _energyPerHour;
}

uint8_t
IndoorBikeData::getEnergyPerMinuteInKiloCalorie() const
{
  return _energyPerMinute;
}

uint8_t
IndoorBikeData::getBPM() const
{
  return _heartRate;
}

uint8_t
IndoorBikeData::getMetabolicEquivalent() const
{
  return _metabolicEquivalent;
}

uint16_t
IndoorBikeData::getElapsedTimeInSecs() const
{
  return _elapsedTime;
}

uint16_t
IndoorBikeData::getRemainingTimeInSecs() const
{
  return _remainingTime;
}

std::string
IndoorBikeData::dump() const
{
  std::stringstream s;
  s << "Instant Speed: " << getInstantSpeedInKmPerSecond() << " Km/s"
    << std::endl;
  if (isAverageSpeedPresent())
    s << "average speed: " << getAverageSpeedInKmPerSecond() << " Km/s"
      << std::endl;
  if (isInstantCadencePresent())
    s << "Instant Cadence:" << getInstantCadenceInRPM() << " RPM" << std::endl;
  if (isAverageCadencePresent())
    s << "Average Cadence: " << getAverageCadenceInRPM() << " RPM" << std::endl;
  if (isTotalDistancePresent())
    s << "Total Distance: " << getTotalDistanceInMeters() << " meters"
      << std::endl;
  if (isResistanceLevelPresent())
    s << "Resistance Level: " << getResistanceLevel() << " (unitless) "
      << std::endl;
  if (isInstantPowerPresent())
    s << "Instant Power: " << getInstantPowerInWatts() << " Watts" << std::endl;
  if (isAveragePowerPresent())
    s << "Average Power: " << getAveragePowerInWatts() << " Watts" << std::endl;
  if (isExpendedEnergyPresent())
    s << "Total Energy: " << getTotalEnergyInKiloCalorie() << " KiloCalorie"
      << std::endl
      << "Energy Per Hour: " << getEnergyPerHourInKiloCalorie()
      << " KiloCalorie" << std::endl
      << "Energy Per Minute: " << getEnergyPerMinuteInKiloCalorie()
      << " KiloCalorie" << std::endl;
  if (isHeartRatePresent())
    s << "Heart Rate: " << getBPM() << " BPM" << std::endl;
  if (isMetabolicEquivalentPresent())
    s << "Metabolic Equivalent: " << getMetabolicEquivalent();
  if (isElapsedTimePresent())
    s << "Elapsed Time: " << getElapsedTimeInSecs() << " secs" << std::endl;
  if (isRemainingTimePresent())
    s << "Remaining Time: " << getRemainingTimeInSecs() << " secs" << std::endl;

  return s.str();
}

QBluetoothUuid
IndoorBikeData::getCharUuid()
{
  return QBluetoothUuid(quint32(0x2ad2));
}

bool
IndoorBikeData::operator==(const IndoorBikeData& other) const
{
  return this->_flags == other._flags &&
         this->_instantSpeed == other._instantSpeed &&
         this->_averageSpeed == other._averageSpeed &&
         this->_instantCadence == other._instantCadence &&
         this->_averageCadence == other._averageCadence &&
         this->_totalDistance == other._totalDistance &&
         this->_resistanceLevel == other._resistanceLevel &&
         this->_instantPower == other._instantPower &&
         this->_averagePower == other._averagePower &&
         this->_totalEnergy == other._totalEnergy &&
         this->_energyPerHour == other._energyPerHour &&
         this->_energyPerMinute == other._energyPerMinute &&
         this->_heartRate == other._heartRate &&
         this->_metabolicEquivalent == other._metabolicEquivalent &&
         this->_elapsedTime == other._elapsedTime &&
         this->_remainingTime == other._remainingTime;
}

bool
IndoorBikeData::operator!=(const IndoorBikeData& other) const
{
  return !(*this == other);
}

bool
IndoorBikeData::haveMoreData() const
{
  return _flags & 1;
}

bool
IndoorBikeData::isAverageSpeedPresent() const
{
  return (_flags >> 1) & 1;
}

bool
IndoorBikeData::isInstantCadencePresent() const
{
  return ((_flags >> 2) & 1);
}

bool
IndoorBikeData::isAverageCadencePresent() const
{
  return ((_flags >> 3) & 1);
}

bool
IndoorBikeData::isTotalDistancePresent() const
{
  return ((_flags >> 4) & 1);
}

bool
IndoorBikeData::isResistanceLevelPresent() const
{
  return ((_flags >> 5) & 1);
}

bool
IndoorBikeData::isInstantPowerPresent() const
{
  return ((_flags >> 6) & 1);
}

bool
IndoorBikeData::isAveragePowerPresent() const
{
  return ((_flags >> 7) & 1);
}

bool
IndoorBikeData::isExpendedEnergyPresent() const
{
  return ((_flags >> 8) & 1);
}

bool
IndoorBikeData::isHeartRatePresent() const
{
  return ((_flags >> 9) & 1);
}

bool
IndoorBikeData::isMetabolicEquivalentPresent() const
{
  return ((_flags >> 10) & 1);
}

bool
IndoorBikeData::isElapsedTimePresent() const
{
  return ((_flags >> 11) & 1);
}

bool
IndoorBikeData::isRemainingTimePresent() const
{
  return ((_flags >> 12) & 1);
}
