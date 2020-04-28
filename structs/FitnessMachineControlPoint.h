#ifndef FITNESSMACHINECONTROLPOINT_H
#define FITNESSMACHINECONTROLPOINT_H

#include <QBluetoothUuid>
#include <QtGlobal>
#include <cstdint>
#include <string>

class FitnessMachineControlPoint
{
public:
  FitnessMachineControlPoint();

  // control methods
  bool reset();
  bool start();
  bool stop();
  bool pause();
  bool setTargetResistanceLevel(double level);
  bool setTargetPower(int16_t powerInWatts);
  bool setWheelCircumference(double circumferenceInMilimeters);
  bool setTargetedCadence(double rpm);

private:
  enum OpCode : quint8
  {
    REQUEST_CONTROL = 0x00,
    RESET = 0x01,
    SET_TARGET_SPEED = 0x02,
    SET_TARGET_INCLINATION = 0x03,
    SET_TARGET_RESISTANCE_LEVEL = 0x04,
    SET_TARGET_POWER = 0x05,
    SET_TARGET_HEART_RATE = 0x06,
    START_RESUME = 0x07,
    STOP_PAUSE = 0x08,
    SET_TARGETED_EXPENDED_ENERGY = 0x09,
    SET_TARGETED_NUMBER_OF_STEPS = 0x0A,
    SET_TARGETED_NUMBER_OF_STRIDES = 0x0B,
    SET_TARGETED_DISTANCE = 0x0C,
    SET_TARGETED_TRAINING_TIME = 0x0D,
    SET_TARGETED_TIME_IN_TWO_HRZ = 0x0E,
    SET_TARGETED_TIME_IN_THREE_HRZ = 0x0F,
    SET_TARGETED_TIME_IN_FIVE_HRZ = 0x10,
    SET_INDOOR_BIKE_SIMULATION_PARAMETERS = 0x11,
    SET_WHEEL_CIRCUMFERENCE = 0x12,
    SPIN_DOWN_CONTROL = 0x13,
    SET_TARGETED_CADENCE = 0x14,
    RESPONSE_CODE = 0x80
  };
  enum StopPause : quint8
  {
    STOP = 0x01,
    PAUSE = 0x02
  };
  enum ResponseResultCode : quint8
  {
    SUCCESS = 0x01,
    OPCODE_NOT_SUPPORTED = 0x02,
    INVALID_PARAMETER = 0x03,
    OPERATION_FAILED = 0x04,
    CONTROL_NOT_PERMITTED = 0x05
  };

  bool sendCommandAndCheckReturn(OpCode opcode,
                                 quint8* data = nullptr,
                                 uint8_t dataSize = 1)
  {
    // send REQUEST_CONTROL
    // wait OK; return false otherwise
    // send opcode and data...
    // return if result OK
    return true;
  }
  bool stopPause(StopPause parameter)
  {
    quint8 parameterCasted = static_cast<quint8>(parameter);
    return sendCommandAndCheckReturn(STOP_PAUSE, &parameterCasted);
  }
};

#endif // FITNESSMACHINECONTROLPOINT_H
