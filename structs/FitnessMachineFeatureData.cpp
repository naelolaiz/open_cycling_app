#include "FitnessMachineFeatureData.h"
#include <sstream>

FitnessMachineFeatureData::FitnessMachineFeatureData(const quint8* data)
  : _fitnessMachineFeatures(data)
  , _targetSettingFeatures(data)
{}

const FitnessMachineFeatureData::MachineFeatures&
FitnessMachineFeatureData::getMachineFeatures() const
{
  return _fitnessMachineFeatures;
}

const FitnessMachineFeatureData::TargetSettingFeatures&
FitnessMachineFeatureData::getTargetSettingFeatures() const
{
  return _targetSettingFeatures;
}

std::string
FitnessMachineFeatureData::dump() const
{
  std::stringstream s;
  s << getMachineFeatures().dump();
  s << getTargetSettingFeatures().dump();
  return s.str();
}

FitnessMachineFeatureData::TargetSettingFeatures::TargetSettingFeatures(
  const quint8* data)
  : _targetSettingFeatures(data[4] + (data[5] << 8) + (data[6] << 16) +
                           (data[7] << 24))
{}

std::string
FitnessMachineFeatureData::TargetSettingFeatures::dump() const
{
  std::stringstream s;
  s << "speedTargetSettingSupported: " << isSpeedTargetSettingSupported()
    << std::endl;
  s << "inclinationTargetSettingSupported: "
    << isInclinationTargetSettingSupported() << std::endl;
  s << "resistanceTargetSettingSupported: "
    << isResistanceTargetSettingSupported() << std::endl;
  s << "powerTargetSettingSupported: " << isPowerTargetSettingSupported()
    << std::endl;
  s << "heartRateTargetSettingSupported: "
    << isHeartRateTargetSettingSupported() << std::endl;
  s << "targetedExpendedEnergyConfigurationSupported: "
    << isTargetedExpendedEnergyConfigurationSupported() << std::endl;
  s << "TargetedStepNumberConfigurationSupported: "
    << isTargetedStepNumberConfigurationSupported() << std::endl;
  s << "TargetedStrideNumberConfigurationSupported: "
    << isTargetedStrideNumberConfigurationSupported() << std::endl;
  s << "TargetedDistanceConfigurationSupported: "
    << isTargetedDistanceConfigurationSupported() << std::endl;
  s << "TargetedTrainingTimeConfigurationSupported: "
    << isTargetedTrainingTimeConfigurationSupported() << std::endl;
  s << "TargetedTimeinTwoHeartRateZonesConfigurationSupported: "
    << isTargetedTimeinTwoHeartRateZonesConfigurationSupported() << std::endl;
  s << "TargetedTimeinThreeHeartRateZonesConfigurationSupported: "
    << isTargetedTimeinThreeHeartRateZonesConfigurationSupported() << std::endl;
  s << "TargetedTimeinFiveHeartRateZonesConfigurationSupported: "
    << isTargetedTimeinFiveHeartRateZonesConfigurationSupported() << std::endl;
  s << "IndoorBikeSimulationParametersSupported: "
    << isIndoorBikeSimulationParametersSupported() << std::endl;
  s << "WheelCircumferenceConfigurationSupported: "
    << isWheelCircumferenceConfigurationSupported() << std::endl;
  s << "SpinDownControlSupported: " << isSpinDownControlSupported()
    << std::endl;
  s << "TargetedCadenceConfigurationSupported: "
    << isTargetedCadenceConfigurationSupported() << std::endl;
  return s.str();
}

bool
FitnessMachineFeatureData::TargetSettingFeatures::
  isSpeedTargetSettingSupported() const
{
  return (_targetSettingFeatures & 1);
}

bool
FitnessMachineFeatureData::TargetSettingFeatures::
  isInclinationTargetSettingSupported() const
{
  return ((_targetSettingFeatures >> 1) & 1);
}

bool
FitnessMachineFeatureData::TargetSettingFeatures::
  isResistanceTargetSettingSupported() const
{
  return ((_targetSettingFeatures >> 2) & 1);
}

bool
FitnessMachineFeatureData::TargetSettingFeatures::
  isPowerTargetSettingSupported() const
{
  return ((_targetSettingFeatures >> 3) & 1);
}

bool
FitnessMachineFeatureData::TargetSettingFeatures::
  isHeartRateTargetSettingSupported() const
{
  return ((_targetSettingFeatures >> 4) & 1);
}

bool
FitnessMachineFeatureData::TargetSettingFeatures::
  isTargetedExpendedEnergyConfigurationSupported() const
{
  return ((_targetSettingFeatures >> 5) & 1);
}

bool
FitnessMachineFeatureData::TargetSettingFeatures::
  isTargetedStepNumberConfigurationSupported() const
{
  return ((_targetSettingFeatures >> 6) & 1);
}

bool
FitnessMachineFeatureData::TargetSettingFeatures::
  isTargetedStrideNumberConfigurationSupported() const
{
  return ((_targetSettingFeatures >> 7) & 1);
}

bool
FitnessMachineFeatureData::TargetSettingFeatures::
  isTargetedDistanceConfigurationSupported() const
{
  return ((_targetSettingFeatures >> 8) & 1);
}

bool
FitnessMachineFeatureData::TargetSettingFeatures::
  isTargetedTrainingTimeConfigurationSupported() const
{
  return ((_targetSettingFeatures >> 9) & 1);
}

bool
FitnessMachineFeatureData::TargetSettingFeatures::
  isTargetedTimeinTwoHeartRateZonesConfigurationSupported() const
{
  return ((_targetSettingFeatures >> 10) & 1);
}

bool
FitnessMachineFeatureData::TargetSettingFeatures::
  isTargetedTimeinThreeHeartRateZonesConfigurationSupported() const
{
  return ((_targetSettingFeatures >> 11) & 1);
}

bool
FitnessMachineFeatureData::TargetSettingFeatures::
  isTargetedTimeinFiveHeartRateZonesConfigurationSupported() const
{
  return ((_targetSettingFeatures >> 12) & 1);
}

bool
FitnessMachineFeatureData::TargetSettingFeatures::
  isIndoorBikeSimulationParametersSupported() const
{
  return ((_targetSettingFeatures >> 13) & 1);
}

bool
FitnessMachineFeatureData::TargetSettingFeatures::
  isWheelCircumferenceConfigurationSupported() const
{
  return ((_targetSettingFeatures >> 14) & 1);
}

bool
FitnessMachineFeatureData::TargetSettingFeatures::isSpinDownControlSupported()
  const
{
  return ((_targetSettingFeatures >> 15) & 1);
}

bool
FitnessMachineFeatureData::TargetSettingFeatures::
  isTargetedCadenceConfigurationSupported() const
{
  return ((_targetSettingFeatures >> 16) & 1);
}

FitnessMachineFeatureData::MachineFeatures::MachineFeatures(const quint8* data)

  : _fitnessMachineFeatures(data[0] + (data[1] << 8) + (data[2] << 16) +
                            (data[3] << 24))
{}

std::string
FitnessMachineFeatureData::MachineFeatures::dump() const
{
  std::stringstream s;
  s << "averageSpeedSupported: " << isAverageSpeedSupported() << std::endl;
  s << "cadenceSupported: " << isCadenceSupported() << std::endl;
  s << "totalDistanceSupported: " << isTotalDistanceSupported() << std::endl;
  s << "inclinationSupported: " << isInclinationSupported() << std::endl;
  s << "elevationGainSupported: " << isElevationGainSupported() << std::endl;
  s << "paceSupported: " << isPaceSupported() << std::endl;
  s << "stepCountSupported: " << isStepCountSupported() << std::endl;
  s << "resistanceLevelSupported: " << isResistanceLevelSupported()
    << std::endl;
  s << "strideCountSupported: " << isStrideCountSupported() << std::endl;
  s << "expendedEnergySupported: " << isExpendedEnergySupported() << std::endl;
  s << "heartRateMeasurementSupported: " << isHeartRateMeasurementSupported()
    << std::endl;
  s << "metabolicEquivalentSupported: " << isMetabolicEquivalentSupported()
    << std::endl;
  s << "elapsedTimeSupported: " << isElapsedTimeSupported() << std::endl;
  s << "remainingTimeSupported: " << isRemainingTimeSupported() << std::endl;
  s << "powerMeasurementSupported: " << isPowerMeasurementSupported()
    << std::endl;
  s << "forceOnBeltAndPowerOutputSupported: "
    << isForceOnBeltAndPowerOutputSupported() << std::endl;
  s << "userDataRetentionSupported: " << isUserDataRetentionSupported()
    << std::endl;
  return s.str();
}

bool
FitnessMachineFeatureData::MachineFeatures::isAverageSpeedSupported() const
{
  return (_fitnessMachineFeatures & 1);
}

bool
FitnessMachineFeatureData::MachineFeatures::isCadenceSupported() const
{
  return ((_fitnessMachineFeatures >> 1) & 1);
}

bool
FitnessMachineFeatureData::MachineFeatures::isTotalDistanceSupported() const
{
  return ((_fitnessMachineFeatures >> 2) & 1);
}

bool
FitnessMachineFeatureData::MachineFeatures::isInclinationSupported() const
{
  return ((_fitnessMachineFeatures >> 3) & 1);
}

bool
FitnessMachineFeatureData::MachineFeatures::isElevationGainSupported() const
{
  return ((_fitnessMachineFeatures >> 4) & 1);
}

bool
FitnessMachineFeatureData::MachineFeatures::isPaceSupported() const
{
  return ((_fitnessMachineFeatures >> 5) & 1);
}

bool
FitnessMachineFeatureData::MachineFeatures::isStepCountSupported() const
{
  return ((_fitnessMachineFeatures >> 6) & 1);
}

bool
FitnessMachineFeatureData::MachineFeatures::isResistanceLevelSupported() const
{
  return ((_fitnessMachineFeatures >> 7) & 1);
}

bool
FitnessMachineFeatureData::MachineFeatures::isStrideCountSupported() const
{
  return ((_fitnessMachineFeatures >> 8) & 1);
}

bool
FitnessMachineFeatureData::MachineFeatures::isExpendedEnergySupported() const
{
  return ((_fitnessMachineFeatures >> 9) & 1);
}

bool
FitnessMachineFeatureData::MachineFeatures::isHeartRateMeasurementSupported()
  const
{
  return ((_fitnessMachineFeatures >> 10) & 1);
}

bool
FitnessMachineFeatureData::MachineFeatures::isMetabolicEquivalentSupported()
  const
{
  return ((_fitnessMachineFeatures >> 11) & 1);
}

bool
FitnessMachineFeatureData::MachineFeatures::isElapsedTimeSupported() const
{
  return ((_fitnessMachineFeatures >> 12) & 1);
}

bool
FitnessMachineFeatureData::MachineFeatures::isRemainingTimeSupported() const
{
  return ((_fitnessMachineFeatures >> 13) & 1);
}

bool
FitnessMachineFeatureData::MachineFeatures::isPowerMeasurementSupported() const
{
  return ((_fitnessMachineFeatures >> 14) & 1);
}

bool
FitnessMachineFeatureData::MachineFeatures::
  isForceOnBeltAndPowerOutputSupported() const
{
  return ((_fitnessMachineFeatures >> 15) & 1);
}

bool
FitnessMachineFeatureData::MachineFeatures::isUserDataRetentionSupported() const
{
  return ((_fitnessMachineFeatures >> 16) & 1);
}

QBluetoothUuid
FitnessMachineFeatureData::getCharUuid()
{
  return QBluetoothUuid(quint32(0x2acc));
}
