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

private:
  const uint16_t _flags;

  bool _moreData() const { return _flags & 1; }
  bool _averageSpeedPresent() const { return (_flags >> 1) & 1; }
  bool _instantCadencePresent() const { return ((_flags >> 2) & 1); }
  bool _averageCadencePresent() const { return ((_flags >> 3) & 1); }
  bool _totalDistancePresent() const { return ((_flags >> 4) & 1); }
  bool _resistanceLevelPresent() const { return ((_flags >> 5) & 1); }
  bool _instantPowerPresent() const { return ((_flags >> 6) & 1); }
  bool _averagePowerPresent() const { return ((_flags >> 7) & 1); }
  bool _expendedEnergyPresent() const { return ((_flags >> 8) & 1); }
  bool _heartRatePresent() const { return ((_flags >> 9) & 1); }
  bool _metabolicEquivalentPresent() const { return ((_flags >> 10) & 1); }
  bool _elapsedTimePresent() const { return ((_flags >> 11) & 1); }
  bool _remainingTimePresent() const { return ((_flags >> 12) & 1); }

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
