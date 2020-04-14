#ifndef FITNESSMACHINEFEATURE_H
#define FITNESSMACHINEFEATURE_H

#include <QtGlobal>
#include <sstream>

class FitnessMachineFeature
{
    struct MachineFeatures
    {
        MachineFeatures(const quint8 * data);
        std::stringstream dump() const;

        const uint32_t _fitnessMachineFeatures;
        const bool _averageSpeedSupported;
        const bool _cadenceSupported;
        const bool _totalDistanceSupported;
        const bool _inclinationSupported;
        const bool _elevationGainSupported;
        const bool _paceSupported;
        const bool _stepCountSupported;
        const bool _resistanceLevelSupported;
        const bool _strideCountSupported;
        const bool _expendedEnergySupported;
        const bool _heartRateMeasurementSupported;
        const bool _metabolicEquivalentSupported;
        const bool _elapsedTimeSupported;
        const bool _remainingTimeSupported;
        const bool _powerMeasurementSupported;
        const bool _forceOnBeltAndPowerOutputSupported;
        const bool _userDataRetentionSupported;
    };
    struct TargetSettingFeatures
    {
        TargetSettingFeatures(const quint8 * data);
        std::stringstream dump() const;

        const uint32_t _targetSettingFeatures;
        const bool _speedTargetSettingSupported;
        const bool _inclinationTargetSettingSupported;
        const bool _resistanceTargetSettingSupported;
        const bool _powerTargetSettingSupported;
        const bool _heartRateTargetSettingSupported;
        const bool _targetedExpendedEnergyConfigurationSupported;
        const bool _TargetedStepNumberConfigurationSupported;
        const bool _TargetedStrideNumberConfigurationSupported;
        const bool _TargetedDistanceConfigurationSupported;
        const bool _TargetedTrainingTimeConfigurationSupported;
        const bool _TargetedTimeinTwoHeartRateZonesConfigurationSupported;
        const bool _TargetedTimeinThreeHeartRateZonesConfigurationSupported;
        const bool _TargetedTimeinFiveHeartRateZonesConfigurationSupported;
        const bool _IndoorBikeSimulationParametersSupported;
        const bool _WheelCircumferenceConfigurationSupported;
        const bool _SpinDownControlSupported;
        const bool _TargetedCadenceConfigurationSupported;
    };

public:
    FitnessMachineFeature(const quint8 * data);
    const MachineFeatures & getMachineFeatures() const;
    const TargetSettingFeatures & getTargetSettingFeatures() const;
    std::stringstream dump() const
    {
        std::stringstream s;
        s << getMachineFeatures().dump().str() ;
        s << getTargetSettingFeatures().dump().str();
        return s;
    }
private:
    const MachineFeatures _fitnessMachineFeatures;
    const TargetSettingFeatures _targetSettingFeatures;
};

#endif // FITNESSMACHINEFEATURE_H
