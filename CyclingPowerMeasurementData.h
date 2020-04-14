#ifndef CYCLINGPOWERMEASUREMENTDATA_H
#define CYCLINGPOWERMEASUREMENTDATA_H

#include <QtGlobal>
#include <cstdint>

class CyclingPowerMeasurementData
{
public:
    CyclingPowerMeasurementData(quint16 flags, const quint8 * data); // todo: add previous state for CSC
    double getPowerBalance() const;
    int16_t getInstantPowerInWatts() const;
private:
    const bool _pedalBalancePresent;
    const bool _pedalBalanceReferencePresent;
    const bool _accumulatedTorquePresent;
    const bool _accumulatedTorqueSourcePresent;
    const bool _wheelRevolutionDataPresent;
    const bool _crankRevolutionDataPresent;
    const bool _extremeForceMagnitudesPresent;
    const bool _extremeTorqueMagnitudesPresent;
    const bool _extremeAnglesPresent;
    const bool _topDeadSpotAnglePresent;
    const bool _bottomDeadSpotAnglePresent;
    const bool _accumulatedEnergyPresent;
    const bool _offsetCompensationIndicator;

    int16_t _instantPowerInWatts{0};
    uint8_t _pedalPowerBalance{100u};
    uint16_t _accumulatedTorque{0u};
    uint32_t _wheelRevolutions{0u};
    uint16_t _wheelRevolutionsLastEventTs{0u};
    uint16_t _crankRevolutions{0u};
    uint16_t _crankRevolutionsLastEventTs{0u};
    uint16_t _extremeMaxForceMagnitudesInNewtons{0u};
    uint16_t _extremeMinForceMagnitudesInNewtons{0u};
    uint16_t _extremeMaxTorqueMagnitudesInNewtonsMetres{0u};
    uint16_t _extremeMinTorqueMagnitudesInNewtonsMetres{0u};
 /// etc (usa 12 bit!)



};

#endif // CYCLINGPOWERMEASUREMENTDATA_H
