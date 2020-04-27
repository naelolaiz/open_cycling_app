#ifndef FITNESSMACHINEFEATURE_H
#define FITNESSMACHINEFEATURE_H

#include <QBluetoothUuid>
#include <QtGlobal>
#include <string>

class FitnessMachineFeatureData
{
  class MachineFeatures
  {
  private:
    const uint32_t _fitnessMachineFeatures;

  public:
    MachineFeatures(const quint8* data);
    std::string dump() const;

    bool isAverageSpeedSupported() const;
    bool isCadenceSupported() const;
    bool isTotalDistanceSupported() const;
    bool isInclinationSupported() const;
    bool isElevationGainSupported() const;
    bool isPaceSupported() const;
    bool isStepCountSupported() const;
    bool isResistanceLevelSupported() const;
    bool isStrideCountSupported() const;
    bool isExpendedEnergySupported() const;
    bool isHeartRateMeasurementSupported() const;
    bool isMetabolicEquivalentSupported() const;
    bool isElapsedTimeSupported() const;
    bool isRemainingTimeSupported() const;
    bool isPowerMeasurementSupported() const;
    bool isForceOnBeltAndPowerOutputSupported() const;
    bool isUserDataRetentionSupported() const;
  };
  class TargetSettingFeatures
  {
  private:
    const uint32_t _targetSettingFeatures;

  public:
    TargetSettingFeatures(const quint8* data);
    std::string dump() const;

    bool isSpeedTargetSettingSupported() const;
    bool isInclinationTargetSettingSupported() const;
    bool isResistanceTargetSettingSupported() const;
    bool isPowerTargetSettingSupported() const;
    bool isHeartRateTargetSettingSupported() const;
    bool isTargetedExpendedEnergyConfigurationSupported() const;
    bool isTargetedStepNumberConfigurationSupported() const;
    bool isTargetedStrideNumberConfigurationSupported() const;
    bool isTargetedDistanceConfigurationSupported() const;
    bool isTargetedTrainingTimeConfigurationSupported() const;
    bool isTargetedTimeinTwoHeartRateZonesConfigurationSupported() const;
    bool isTargetedTimeinThreeHeartRateZonesConfigurationSupported() const;
    bool isTargetedTimeinFiveHeartRateZonesConfigurationSupported() const;
    bool isIndoorBikeSimulationParametersSupported() const;
    bool isWheelCircumferenceConfigurationSupported() const;
    bool isSpinDownControlSupported() const;
    bool isTargetedCadenceConfigurationSupported() const;
  };

public:
  FitnessMachineFeatureData(const quint8* data);
  const MachineFeatures& getMachineFeatures() const;
  const TargetSettingFeatures& getTargetSettingFeatures() const;
  static QBluetoothUuid getCharUuid();
  std::string dump() const;

private:
  const MachineFeatures _fitnessMachineFeatures;
  const TargetSettingFeatures _targetSettingFeatures;
};

#endif // FITNESSMACHINEFEATURE_H
