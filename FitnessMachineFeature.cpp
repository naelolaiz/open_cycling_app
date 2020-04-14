#include "FitnessMachineFeature.h"

FitnessMachineFeature::FitnessMachineFeature(const quint8 *data)
    : _fitnessMachineFeatures(data)
    , _targetSettingFeatures(data)
{
}

const FitnessMachineFeature::MachineFeatures &FitnessMachineFeature::getMachineFeatures() const
{
    return _fitnessMachineFeatures;
}

const FitnessMachineFeature::TargetSettingFeatures &FitnessMachineFeature::getTargetSettingFeatures() const
{
    return _targetSettingFeatures;
}

FitnessMachineFeature::TargetSettingFeatures::TargetSettingFeatures(const quint8 *data)
    : _targetSettingFeatures(data[0] + (data[1]<<8) + (data[2]<<16) + (data[3]<<24))
    , _speedTargetSettingSupported                             (_targetSettingFeatures        & 1)
    , _inclinationTargetSettingSupported(                      (_targetSettingFeatures >> 1)  & 1)
    , _resistanceTargetSettingSupported(                       (_targetSettingFeatures >> 2 ) & 1)
    , _powerTargetSettingSupported(                            (_targetSettingFeatures >> 3 ) & 1)
    , _heartRateTargetSettingSupported(                        (_targetSettingFeatures >> 4 ) & 1)
    , _targetedExpendedEnergyConfigurationSupported(           (_targetSettingFeatures >> 5 ) & 1)
    , _TargetedStepNumberConfigurationSupported(               (_targetSettingFeatures >> 6)  & 1)
    , _TargetedStrideNumberConfigurationSupported(             (_targetSettingFeatures >> 7)  & 1)
    , _TargetedDistanceConfigurationSupported(                 (_targetSettingFeatures >> 8)  & 1)
    , _TargetedTrainingTimeConfigurationSupported(             (_targetSettingFeatures >> 9)  & 1)
    , _TargetedTimeinTwoHeartRateZonesConfigurationSupported(  (_targetSettingFeatures >> 10) & 1)
    , _TargetedTimeinThreeHeartRateZonesConfigurationSupported((_targetSettingFeatures >> 11) & 1)
    , _TargetedTimeinFiveHeartRateZonesConfigurationSupported( (_targetSettingFeatures >> 12) & 1)
    , _IndoorBikeSimulationParametersSupported(                (_targetSettingFeatures >> 13) & 1)
    , _WheelCircumferenceConfigurationSupported(               (_targetSettingFeatures >> 14) & 1)
    , _SpinDownControlSupported(                               (_targetSettingFeatures >> 15) & 1)
    , _TargetedCadenceConfigurationSupported(                  (_targetSettingFeatures >> 16) & 1)
{}

std::stringstream FitnessMachineFeature::TargetSettingFeatures::dump() const
{
    std::stringstream s;
    s << "_speedTargetSettingSupported: " << _speedTargetSettingSupported << std::endl;
    s << "_inclinationTargetSettingSupported: " << _inclinationTargetSettingSupported << std::endl;
    s << "_resistanceTargetSettingSupported: " << _resistanceTargetSettingSupported << std::endl;
    s << "_powerTargetSettingSupported: " << _powerTargetSettingSupported << std::endl;
    s << "_heartRateTargetSettingSupported: " << _heartRateTargetSettingSupported << std::endl;
    s << "_targetedExpendedEnergyConfigurationSupported: " << _targetedExpendedEnergyConfigurationSupported << std::endl;
    s << "_TargetedStepNumberConfigurationSupported: " << _TargetedStepNumberConfigurationSupported << std::endl;
    s << "_TargetedStrideNumberConfigurationSupported: " << _TargetedStrideNumberConfigurationSupported << std::endl;
    s << "_TargetedDistanceConfigurationSupported: " << _TargetedDistanceConfigurationSupported << std::endl;
    s << "_TargetedTrainingTimeConfigurationSupported: " << _TargetedTrainingTimeConfigurationSupported << std::endl;
    s << "_TargetedTimeinTwoHeartRateZonesConfigurationSupported: " << _TargetedTimeinTwoHeartRateZonesConfigurationSupported << std::endl;
    s << "_TargetedTimeinThreeHeartRateZonesConfigurationSupported: " << _TargetedTimeinThreeHeartRateZonesConfigurationSupported << std::endl;
    s << "_TargetedTimeinFiveHeartRateZonesConfigurationSupported: " << _TargetedTimeinFiveHeartRateZonesConfigurationSupported << std::endl;
    s << "_IndoorBikeSimulationParametersSupported: " << _IndoorBikeSimulationParametersSupported << std::endl;
    s << "_WheelCircumferenceConfigurationSupported: " << _WheelCircumferenceConfigurationSupported << std::endl;
    s << "_SpinDownControlSupported: " << _SpinDownControlSupported << std::endl;
    s << "_TargetedCadenceConfigurationSupported: " << _TargetedCadenceConfigurationSupported << std::endl;
    return s;
}

FitnessMachineFeature::MachineFeatures::MachineFeatures(const quint8 *data)

    : _fitnessMachineFeatures(data[4] + (data[5]<<8) + (data[6]<<16) + (data[7]<<24))
    , _averageSpeedSupported(_fitnessMachineFeatures & 1)
    ,_cadenceSupported((_fitnessMachineFeatures >>1 ) &1)
    , _totalDistanceSupported((_fitnessMachineFeatures>>2)&1)
    , _inclinationSupported((_fitnessMachineFeatures>>3)&1)
    , _elevationGainSupported((_fitnessMachineFeatures>>4)&1)
    , _paceSupported((_fitnessMachineFeatures>>5)&1)
    , _stepCountSupported((_fitnessMachineFeatures>>6)&1)
    , _resistanceLevelSupported((_fitnessMachineFeatures>>7)&1)
    , _strideCountSupported((_fitnessMachineFeatures>>8)&1)
    , _expendedEnergySupported((_fitnessMachineFeatures>>9)&1)
    , _heartRateMeasurementSupported((_fitnessMachineFeatures>>10)&1)
    , _metabolicEquivalentSupported((_fitnessMachineFeatures>>11)&1)
    , _elapsedTimeSupported((_fitnessMachineFeatures>>12)&1)
    , _remainingTimeSupported((_fitnessMachineFeatures>>13)&1)
    , _powerMeasurementSupported((_fitnessMachineFeatures>>14)&1)
    , _forceOnBeltAndPowerOutputSupported((_fitnessMachineFeatures>>15)&1)
    , _userDataRetentionSupported((_fitnessMachineFeatures>>16)&1)
{
}

std::stringstream FitnessMachineFeature::MachineFeatures::dump() const
{
    std::stringstream s;
    s << "_averageSpeedSupported: " << _averageSpeedSupported << std::endl;
    s << "_cadenceSupported: " << _cadenceSupported << std::endl;
    s << "_totalDistanceSupported: " << _totalDistanceSupported << std::endl;
    s << "_inclinationSupported: " << _inclinationSupported << std::endl;
    s << "_elevationGainSupported: " << _elevationGainSupported << std::endl;
    s << "_paceSupported: " << _paceSupported << std::endl;
    s << "_stepCountSupported: " << _stepCountSupported << std::endl;
    s << "_resistanceLevelSupported: " << _resistanceLevelSupported << std::endl;
    s << "_strideCountSupported: " << _strideCountSupported << std::endl;
    s << "_expendedEnergySupported: " << _expendedEnergySupported << std::endl;
    s << "_heartRateMeasurementSupported: " << _heartRateMeasurementSupported << std::endl;
    s << "_metabolicEquivalentSupported: " << _metabolicEquivalentSupported << std::endl;
    s << "_elapsedTimeSupported: " << _elapsedTimeSupported << std::endl;
    s << "_remainingTimeSupported: " << _remainingTimeSupported << std::endl;
    s << "_powerMeasurementSupported: " << _powerMeasurementSupported << std::endl;
    s << "_forceOnBeltAndPowerOutputSupported: " << _forceOnBeltAndPowerOutputSupported << std::endl;
    s << "_userDataRetentionSupported: " << _userDataRetentionSupported << std::endl;
    return s;
}
