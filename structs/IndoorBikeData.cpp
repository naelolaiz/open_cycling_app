#include "IndoorBikeData.h"
#include <QtEndian>
#include <sstream>

IndoorBikeData::IndoorBikeData(const quint8* data)
  : _flags(qFromLittleEndian<quint16>(data[0]))
{
  uint16_t index = 2;
  if (_moreData()) {
    _instantSpeed = data[index] + (data[index + 1] << 8);
    index += 2;
  }
  if (_averageSpeedPresent()) {
    _averageSpeed = data[index] + (data[index + 1] << 8);
    index += 2;
  }
  if (_instantCadencePresent()) {
    _instantCadence = data[index] + (data[index + 1] << 8);
    index += 2;
  }
  if (_averageCadencePresent()) {
    _averageCadence = data[index] + (data[index + 1] << 8);
    index += 2;
  }
  if (_totalDistancePresent()) {
    // TODO! !?
    //_totalDistance = qFromLittleEndian
    _totalDistance =
      data[index] + (data[index + 1] << 8) + (data[index + 2] << 16); // ?
    index += 3;
  }
  if (_resistanceLevelPresent()) {
    _resistanceLevel = data[index] + (data[index + 1] << 8);
    index += 2;
  }
  if (_instantPowerPresent()) {
    _instantPower = data[index] + (data[index + 1] << 8);
    index += 2;
  }
  if (_averagePowerPresent()) {
    _averagePower = data[index] + (data[index + 1] << 8);
    index += 2;
  }
  if (_expendedEnergyPresent()) {
    _totalEnergy = data[index] + (data[index + 1] << 8);
    index += 2;
    _energyPerHour = data[index] + (data[index + 1] << 8);
    index += 2;
    _energyPerMinute = reinterpret_cast<quint8>(data[index]);
    index++;
  }
  if (_heartRatePresent()) {
    _heartRate = reinterpret_cast<quint8>(data[index]);
    index++;
  }
  if (_metabolicEquivalentPresent()) {
    _metabolicEquivalent = reinterpret_cast<quint8>(data[index]);
    index++;
  }
  if (_elapsedTimePresent()) {
    _elapsedTime = data[index] + (data[index + 1] << 8);
    index += 2;
  }
  if (_remainingTimePresent()) {
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
  if (_averageSpeedPresent())
    s << "average speed: " << getAverageSpeedInKmPerSecond() << " Km/s"
      << std::endl;
  if (_instantCadencePresent())
    s << "Instant Cadence:" << getInstantCadenceInRPM() << " RPM" << std::endl;
  if (_averageCadencePresent())
    s << "Average Cadence: " << getAverageCadenceInRPM() << " RPM" << std::endl;
  if (_totalDistancePresent())
    s << "Total Distance: " << getTotalDistanceInMeters() << " meters"
      << std::endl;
  if (_resistanceLevelPresent())
    s << "Resistance Level: " << getResistanceLevel() << " (unitless) "
      << std::endl;
  if (_instantPowerPresent())
    s << "Instant Power: " << getInstantPowerInWatts() << " Watts" << std::endl;
  if (_averagePowerPresent())
    s << "Average Power: " << getAveragePowerInWatts() << " Watts" << std::endl;
  if (_expendedEnergyPresent())
    s << "Total Energy: " << getTotalEnergyInKiloCalorie() << " KiloCalorie"
      << std::endl
      << "Energy Per Hour: " << getEnergyPerHourInKiloCalorie()
      << " KiloCalorie" << std::endl
      << "Energy Per Minute: " << getEnergyPerMinuteInKiloCalorie()
      << " KiloCalorie" << std::endl;
  if (_heartRatePresent())
    s << "Heart Rate: " << getBPM() << " BPM" << std::endl;
  if (_metabolicEquivalentPresent())
    s << "Metabolic Equivalent: " << getMetabolicEquivalent();
  if (_elapsedTimePresent())
    s << "Elapsed Time: " << getElapsedTimeInSecs() << " secs" << std::endl;
  if (_remainingTimePresent())
    s << "Remaining Time: " << getRemainingTimeInSecs() << " secs" << std::endl;

  return s.str();
}

QBluetoothUuid
IndoorBikeData::getCharUuid()
{
  return QBluetoothUuid(quint32(0x2ad2));
}
