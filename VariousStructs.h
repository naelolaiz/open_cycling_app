#ifndef VARIOUSSTRUCTS_H
#define VARIOUSSTRUCTS_H
#include <QtGlobal>
#include <sstream>

class SupportedPowerRange
{
public:
    SupportedPowerRange(const quint8 * data);
    int16_t getMinimumPowerInWatts() const;
    int16_t getMaximumPowerInWatts() const;
    uint16_t getMinimumIncrementInWatts() const;
    std::stringstream dump();
    static quint32 getCharUuid()
    {
        //         00002ad6-0000-1000-8000-00805f9b34fb
        return quint32(0x2ad6);
    }
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
    static quint32 getCharUuid();
private:
    const int16_t _minimumResistanceLevel;
    const int16_t _maximumResistanceLevel;
    const uint16_t _minimumIncrement;
};

class FitnessMachineStatus
{
public:
    static quint32 getCharUuid();

};

class TrainingStatus
{
public:
    static quint32 getCharUuid();

};

#endif // VARIOUSSTRUCTS_H
