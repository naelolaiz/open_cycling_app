#ifndef VARIOUSSTRUCTS_H
#define VARIOUSSTRUCTS_H
#include <QBluetoothUuid>
#include <QtGlobal>
#include <string>

class FitnessMachineService
{
public:
  static QBluetoothUuid getServiceUuid();
};

class SupportedPowerRange : public FitnessMachineService
{
public:
  SupportedPowerRange(const quint8* data);
  int16_t getMinimumPowerInWatts() const;
  int16_t getMaximumPowerInWatts() const;
  uint16_t getMinimumIncrementInWatts() const;
  std::string dump();
  static QBluetoothUuid getCharUuid();

private:
  const int16_t _minimumPowerInWatts;
  const int16_t _maximumPowerInWatts;
  const uint16_t _minimumIncrementInWatts;
};

class SupportedResistanceLevelRange : public FitnessMachineService
{
public:
  SupportedResistanceLevelRange(const quint8* data);
  double getMinimumResistanceLevel() const;
  double getMaximumResistanceLevel() const;
  double getMinimumIncrement() const;
  std::string dump();
  static QBluetoothUuid getCharUuid();

private:
  const int16_t _minimumResistanceLevel;
  const int16_t _maximumResistanceLevel;
  const uint16_t _minimumIncrement;
};

class FitnessMachineStatus : public FitnessMachineService
{
public:
  FitnessMachineStatus(const quint8* data);
  std::string dump() const;
  static QBluetoothUuid getCharUuid();
};

class TrainingStatus : public FitnessMachineService
{
public:
  enum Status : quint8
  {
    OTHER = 0x00,
    IDLE = 0x01,
    WARMING_UP = 0x02,
    LOW_INTENSITY_INTERVAL = 0x03,
    HIGH_INTENSITY_INTERVAL = 0x04,
    RECOVER_INTERVAL = 0x05,
    ISOMETRIC = 0x06,
    HEART_RATE_CONTROL = 0x07,
    FITNESS_TEST = 0x08,
    SPEED_OUTSIDE_OF_CONTROL_REGION_LOW = 0x09,
    SPEED_OUTSIDE_OF_CONTROL_REGION_HIGH = 0x0A,
    COOL_DOWN = 0x0B,
    WATT_CONTROl = 0x0C,
    MANUAL_MODE = 0x0D,
    PRE_WORKOUT = 0x0E,
    POST_WORKOUT = 0x0F,
  };
  TrainingStatus(const quint8* data);
  static QBluetoothUuid getCharUuid();
  Status getStatus() const;
  const std::string& getString();
  const std::string& getExtendedString();
  std::string dump() const;

private:
  const bool _trainingStatusStringPresent;
  const bool _extendedStringPresent;
  const Status _status;
  std::string _string;
  std::string _extendedString;
};

#endif // VARIOUSSTRUCTS_H
