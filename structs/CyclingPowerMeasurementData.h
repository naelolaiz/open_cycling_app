#ifndef CYCLINGPOWERMEASUREMENTDATA_H
#define CYCLINGPOWERMEASUREMENTDATA_H

#include <QBluetoothUuid>
#include <QtGlobal>
#include <cstdint>
#include <string>

class CyclingPowerMeasurementData
{
public:
  CyclingPowerMeasurementData(
    const quint8*
      data); // TODO: add previous state for CSC to count overflows in time
  double getPowerBalance() const;
  int16_t getInstantPowerInWatts() const;

  static QBluetoothUuid getCharUuid();

  std::string dump() const;

private:
  const uint16_t _flags;
  bool isPedalBalancePresent();
  bool isPedalBalanceReferencePresent();
  bool isAccumulatedTorquePresent();
  bool isAccumulatedTorqueSourcePresent();
  bool isWheelRevolutionDataPresent();
  bool isCrankRevolutionDataPresent();
  bool isExtremeForceMagnitudesPresent();
  bool isExtremeTorqueMagnitudesPresent();
  bool isExtremeAnglesPresent();
  bool isTopDeadSpotAnglePresent();
  bool isBottomDeadSpotAnglePresent();
  bool isAccumulatedEnergyPresent();
  bool isOffsetCompensationIndicatorPresent();

  int16_t _instantPowerInWatts{ 0 };
  uint8_t _pedalPowerBalance{ 100u };
  uint16_t _accumulatedTorque{ 0u };
  uint32_t _wheelRevolutions{ 0u };
  uint16_t _wheelRevolutionsLastEventTs{ 0u };
  uint16_t _crankRevolutions{ 0u };
  uint16_t _crankRevolutionsLastEventTs{ 0u };
  uint16_t _extremeMaxForceMagnitudesInNewtons{ 0u };
  uint16_t _extremeMinForceMagnitudesInNewtons{ 0u };
  uint16_t _extremeMaxTorqueMagnitudesInNewtonsMetres{ 0u };
  uint16_t _extremeMinTorqueMagnitudesInNewtonsMetres{ 0u };
  /// etc (usa 12 bit!)
};

#endif // CYCLINGPOWERMEASUREMENTDATA_H
