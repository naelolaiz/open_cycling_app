#ifndef VARIOUSSTRUCTS_H
#define VARIOUSSTRUCTS_H
#include <QtGlobal>
#include <sstream>

class SupportedPowerRange
{
    //         00002ad6-0000-1000-8000-00805f9b34fb
public:
    SupportedPowerRange(const quint8 * data);
    int16_t getMinimumPowerInWatts() const;
    int16_t getMaximumPowerInWatts() const;
    uint16_t getMinimumIncrementInWatts() const;
    std::stringstream dump();
private:
    const int16_t _minimumPowerInWatts;
    const int16_t _maximumPowerInWatts;
    const uint16_t _minimumIncrementInWatts;

};

class SupportedResistanceLevelRange
{
public:
    SupportedResistanceLevelRange(const quint8 * data);
    int16_t getMinimumResistanceLevel() const;
    int16_t getMaximumResistanceLevel() const;
    int16_t getMinimumIncrement() const;
    std::stringstream dump();
private:
    const int16_t _minimumResistanceLevel;
    const int16_t _maximumResistanceLevel;
    const uint16_t _minimumIncrement;
};

#endif // VARIOUSSTRUCTS_H
