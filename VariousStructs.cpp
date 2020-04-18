#include "VariousStructs.h"
#include <QtEndian>
#include <sstream>

SupportedPowerRange::SupportedPowerRange(const quint8* data)
  : _minimumPowerInWatts(data[0] + (data[1] << 8))
  , _maximumPowerInWatts(data[2] +
                         (data[3] << 8)) // qFromLittleEndian<qint16>(data[2]))
  , _minimumIncrementInWatts(data[4] + (data[5] << 8))
{}

int16_t
SupportedPowerRange::getMinimumPowerInWatts() const
{
  return _minimumPowerInWatts;
}

int16_t
SupportedPowerRange::getMaximumPowerInWatts() const
{
  return _maximumPowerInWatts;
}

uint16_t
SupportedPowerRange::getMinimumIncrementInWatts() const
{
  return _minimumIncrementInWatts;
}

std::string
SupportedPowerRange::dump()
{
  std::stringstream s;
  s << "min pow level in watts: " << _minimumPowerInWatts << std::endl;
  s << "max pow level in watts: " << _maximumPowerInWatts << std::endl;
  s << "min pow increment in watts: " << _minimumIncrementInWatts << std::endl;
  return s.str();
}

QBluetoothUuid
SupportedPowerRange::getCharUuid()
{
  return QBluetoothUuid(quint32(0x2ad8));
}

SupportedResistanceLevelRange::SupportedResistanceLevelRange(const quint8* data)
  : _minimumResistanceLevel(data[0] + (data[1] << 8))
  , _maximumResistanceLevel(data[2] + (data[3] << 8))
  , _minimumIncrement(data[4] + (data[5] << 8))
{}

int16_t
SupportedResistanceLevelRange::getMinimumResistanceLevel() const
{
  return _minimumResistanceLevel;
}

int16_t
SupportedResistanceLevelRange::getMaximumResistanceLevel() const
{
  return _maximumResistanceLevel;
}

int16_t
SupportedResistanceLevelRange::getMinimumIncrement() const
{
  return _minimumIncrement;
}

std::string
SupportedResistanceLevelRange::dump()
{
  std::stringstream s;
  s << "min res level: " << _minimumResistanceLevel << std::endl;
  s << "max res level: " << _maximumResistanceLevel << std::endl;
  s << "min res increment: " << _minimumIncrement << std::endl;
  return s.str();
}

QBluetoothUuid
SupportedResistanceLevelRange::getCharUuid()
{
  //         00002ad6-0000-1000-8000-00805f9b34fb
  return QBluetoothUuid(quint32(0x2ad6));
}

QBluetoothUuid
FitnessMachineStatus::getCharUuid()
{
  // 0x2ada
  return QBluetoothUuid(quint32(0x2ada));
}

TrainingStatus::TrainingStatus(const quint8* data)
  : _trainingStatusStringPresent(data[0] & 1)
  , _extendedStringPresent((data[0] >> 1) & 1)
  , _status(static_cast<Status>(data[1]))
{
  size_t index = 2;
  if (_trainingStatusStringPresent) {
    while (data[index] != 0) {
      _string += data[index];
      index++;
    }
  }
  if (_extendedStringPresent) {
    while (data[index] != 0) {
      _extendedString += data[index];
      index++;
    }
  }
}

QBluetoothUuid
TrainingStatus::getCharUuid()
{
  // 0x2ad3
  return QBluetoothUuid(quint32(0x2ad3));
}

TrainingStatus::Status
TrainingStatus::getStatus() const
{
  return _status;
}

const std::string&
TrainingStatus::getString()
{
  return _string;
}

const std::string&
TrainingStatus::getExtendedString()
{
  return _extendedString;
}

QBluetoothUuid
FitnessMachineService::getServiceUuid()
{
  return QBluetoothUuid(quint32(0x1826));
}
