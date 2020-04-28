#include "FitnessMachineControlPoint.h"

FitnessMachineControlPoint::FitnessMachineControlPoint() {}

bool
FitnessMachineControlPoint::reset()
{
  return sendCommandAndCheckReturn(RESET);
}

bool
FitnessMachineControlPoint::start()
{
  return sendCommandAndCheckReturn(START_RESUME);
}

bool
FitnessMachineControlPoint::stop()
{
  return stopPause(STOP);
}

bool
FitnessMachineControlPoint::pause()
{
  return stopPause(PAUSE);
}

bool
FitnessMachineControlPoint::setTargetResistanceLevel(double level)
{
  quint8 targetResistanceLevel = level * 10.;
  return sendCommandAndCheckReturn(SET_TARGET_RESISTANCE_LEVEL,
                                   &targetResistanceLevel);
}

bool
FitnessMachineControlPoint::setTargetPower(int16_t powerInWatts)
{
  quint8 data[2];
  data[0] = powerInWatts & 0xFF;
  data[1] = (powerInWatts >> 8) & 0xFF;
  return sendCommandAndCheckReturn(SET_TARGET_POWER, data, 2);
}

bool
FitnessMachineControlPoint::setWheelCircumference(
  double circumferenceInMilimeters)
{
  uint16_t circumferenceInt = circumferenceInMilimeters * 10.;
  quint8 data[2];
  data[0] = circumferenceInt & 0xFF;
  data[1] = (circumferenceInt >> 8) & 0xFF;
  return sendCommandAndCheckReturn(SET_WHEEL_CIRCUMFERENCE, data, 2);
}

bool
FitnessMachineControlPoint::setTargetedCadence(double rpm)
{
  uint16_t targetedCadenceInt = rpm * 2.;
  quint8 data[2];
  data[0] = targetedCadenceInt & 0xFF;
  data[1] = (targetedCadenceInt >> 8) & 0xFF;
  return sendCommandAndCheckReturn(SET_TARGETED_CADENCE, data, 2);
}

bool
FitnessMachineControlPoint::sendCommandAndCheckReturn(
  FitnessMachineControlPoint::OpCode opcode,
  quint8* data,
  uint8_t dataSize)
{
  // send REQUEST_CONTROL
  // wait OK; return false otherwise
  // send opcode and data...
  // return if result OK
  return true;
}

bool
FitnessMachineControlPoint::stopPause(
  FitnessMachineControlPoint::StopPause parameter)
{
  quint8 parameterCasted = static_cast<quint8>(parameter);
  return sendCommandAndCheckReturn(STOP_PAUSE, &parameterCasted);
}
