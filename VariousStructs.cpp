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

double
SupportedResistanceLevelRange::getMinimumResistanceLevel() const
{
  return _minimumResistanceLevel * 0.1;
}

double
SupportedResistanceLevelRange::getMaximumResistanceLevel() const
{
  return _maximumResistanceLevel * 0.1;
}

double
SupportedResistanceLevelRange::getMinimumIncrement() const
{
  return _minimumIncrement * 0.1;
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

FitnessMachineStatus::FitnessMachineStatus(const quint8* data) {}

std::string
FitnessMachineStatus::dump() const
{
  std::stringstream s;
  s << "TODO!" << std::endl;
  return s.str();
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

std::string
TrainingStatus::dump() const
{
  std::stringstream s;
  s << "Status: ";
  switch (_status) {
    case OTHER:
      s << "OTHER" << std::endl;
      break;
    case IDLE:
      s << "IDLE" << std::endl;
      break;
    case WARMING_UP:
      s << "WARMING UP" << std::endl;
      break;
    case LOW_INTENSITY_INTERVAL:
      s << "LOW INTENSITY INTERVAL" << std::endl;
      break;
    case HIGH_INTENSITY_INTERVAL:
      s << "HIGH INTENSITY INTERVAL" << std::endl;
      break;
    case RECOVER_INTERVAL:
      s << "RECOVER INTERVAL" << std::endl;
      break;
    case ISOMETRIC:
      s << "ISOMETRIC" << std::endl;
      break;
    case HEART_RATE_CONTROL:
      s << "HEART RATE CONTROL" << std::endl;
      break;
    case FITNESS_TEST:
      s << "FITNESS TEST" << std::endl;
      break;
    case SPEED_OUTSIDE_OF_CONTROL_REGION_LOW:
      s << "SPEED OUTSIDE OF CONTROL REGION LOW" << std::endl;
      break;
    case SPEED_OUTSIDE_OF_CONTROL_REGION_HIGH:
      s << "SPEED OUTSIDE OF CONTROL REGION HIGH" << std::endl;
      break;
    case COOL_DOWN:
      s << "COOL DOWN" << std::endl;
      break;
    case WATT_CONTROl:
      s << "WATT CONTROL" << std::endl;
      break;
    case MANUAL_MODE:
      s << "MANUAL MODE" << std::endl;
      break;
    case PRE_WORKOUT:
      s << "PRE WORKOUT" << std::endl;
      break;
    case POST_WORKOUT:
    default:
      s << "POST WORKOUT" << std::endl;
  }
  if (_trainingStatusStringPresent) {
    s << "Status string: " << _string << std::endl;
  }
  if (_extendedStringPresent) {
    s << "Status extended string: " << _extendedString << std::endl;
  }
  return s.str();
}

QBluetoothUuid
FitnessMachineService::getServiceUuid()
{
  return QBluetoothUuid(quint32(0x1826));
}
