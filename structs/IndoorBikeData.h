#ifndef INDOORBIKEDATA_H
#define INDOORBIKEDATA_H

#include "VariousStructs.h"
#include <QBluetoothUuid>
#include <QtGlobal>
#include <cstdint>
#include <string>

class IndoorBikeData : FitnessMachineService
{
public:
  IndoorBikeData(const quint8* data);
  double getInstantSpeedInKmPerSecond() const;
  double getAverageSpeedInKmPerSecond() const;
  double getInstantCadenceInRPM() const;
  double getAverageCadenceInRPM() const;
  uint32_t getTotalDistanceInMeters() const;
  int16_t getResistanceLevel() const;
  int16_t getInstantPowerInWatts() const;
  int16_t getAveragePowerInWatts() const;
  uint16_t getTotalEnergyInKiloCalorie() const;
  uint16_t getEnergyPerHourInKiloCalorie() const;
  uint8_t getEnergyPerMinuteInKiloCalorie() const;
  uint8_t getBPM() const;
  uint8_t getMetabolicEquivalent() const;
  uint16_t getElapsedTimeInSecs() const;
  uint16_t getRemainingTimeInSecs() const;
  std::string dump() const;
  static QBluetoothUuid getCharUuid();
  bool operator==(const IndoorBikeData& other) const;
  bool operator!=(const IndoorBikeData& other) const;

private:
  const uint16_t _flags;

  bool haveMoreData() const;
  bool isAverageSpeedPresent() const;
  bool isInstantCadencePresent() const;
  bool isAverageCadencePresent() const;
  bool isTotalDistancePresent() const;
  bool isResistanceLevelPresent() const;
  bool isInstantPowerPresent() const;
  bool isAveragePowerPresent() const;
  bool isExpendedEnergyPresent() const;
  bool isHeartRatePresent() const;
  bool isMetabolicEquivalentPresent() const;
  bool isElapsedTimePresent() const;
  bool isRemainingTimePresent() const;

  uint16_t _instantSpeed{ 0u };
  uint16_t _averageSpeed{ 0u };
  uint16_t _instantCadence{ 0u };
  uint16_t _averageCadence{ 0u };
  uint32_t _totalDistance{ 0u }; // it is a 24 bit unsigned integer
  int16_t _resistanceLevel{ 0 };
  int16_t _instantPower{ 0 };
  int16_t _averagePower{ 0 };
  uint16_t _totalEnergy{ 0u };
  uint16_t _energyPerHour{ 0u };
  uint8_t _energyPerMinute{ 0u };
  uint8_t _heartRate{ 0u };
  uint8_t _metabolicEquivalent{ 0u };
  uint16_t _elapsedTime{ 0u };
  uint16_t _remainingTime{ 0u };
};

#endif // INDOORBIKEDATA_H
