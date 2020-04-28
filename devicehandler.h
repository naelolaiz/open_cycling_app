/***************************************************************************
**
** Copyright (C) 2017 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the QtBluetooth module of the Qt
*Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef DEVICEHANDLER_H
#define DEVICEHANDLER_H

#include "bluetoothbaseclass.h"
#include "structs/CSCMeasurementData.h"
#include "structs/CyclingPowerMeasurementData.h"
#include "structs/FitnessMachineFeatureData.h"
#include "structs/IndoorBikeData.h"
#include "structs/VariousStructs.h"

#include <QDateTime>
#include <QTimer>
#include <QVector>

#include <QLowEnergyController>
#include <QLowEnergyService>

class DeviceInfo;

class DeviceHandler : public BluetoothBaseClass
{
  Q_OBJECT

  Q_PROPERTY(bool measuring READ measuring NOTIFY measuringChanged)

  Q_PROPERTY(bool aliveHR READ aliveHR NOTIFY aliveHRChanged)
  Q_PROPERTY(bool aliveCSC READ aliveCSC NOTIFY aliveCSCChanged)
  Q_PROPERTY(bool alivePower READ alivePower NOTIFY alivePowerChanged)
  Q_PROPERTY(bool aliveFitness READ aliveFitness NOTIFY aliveFitnessChanged)

  Q_PROPERTY(int hr READ hr NOTIFY statsChanged)
  Q_PROPERTY(int maxHR READ maxHR NOTIFY statsChanged)
  Q_PROPERTY(int minHR READ minHR NOTIFY statsChanged)
  Q_PROPERTY(float average READ average NOTIFY statsChanged)
  Q_PROPERTY(int time READ time NOTIFY statsChanged)
  Q_PROPERTY(float calories READ calories NOTIFY statsChanged)

  // CyclingPowerMeasurementData
  Q_PROPERTY(double powerBalance READ getPedalBalance NOTIFY statsChanged)
  Q_PROPERTY(int powerInWatts READ getPowerInWatts NOTIFY statsChanged)

  // CSCMeasurementData
  Q_PROPERTY(
    unsigned int wheelRevolutions READ getWheelRevolutions NOTIFY statsChanged)
  Q_PROPERTY(double wheelRevsTs READ getWheelRevsTs NOTIFY statsChanged)
  Q_PROPERTY(
    unsigned int crankRevolutions READ getCrankRevolutions NOTIFY statsChanged)
  Q_PROPERTY(double crankRevsTs READ getCrankRevsTs NOTIFY statsChanged)

  // IndoorBikeData
  Q_PROPERTY(double instantSpeed READ getInstantSpeed NOTIFY statsChanged)
  Q_PROPERTY(double averageSpeed READ getAverageSpeed NOTIFY statsChanged)
  Q_PROPERTY(
    double instantCadenceInRPM READ getInstantCadenceInRPM NOTIFY statsChanged)
  Q_PROPERTY(
    double averageCadenceInRPM READ getAverageCadenceInRPM NOTIFY statsChanged)
  Q_PROPERTY(
    unsigned int totalDistanceInM READ getTotalDistanceInM NOTIFY statsChanged)
  Q_PROPERTY(int resistanceLevel READ getResistanceLevel NOTIFY statsChanged)
  Q_PROPERTY(
    int instantPowerInWatts READ getInstantPowerInWatts NOTIFY statsChanged)
  Q_PROPERTY(
    int averagePowerInWatts READ getAveragePowerInWatts NOTIFY statsChanged)

  //////////////
  // configuration and status reports
  Q_PROPERTY(int minimumPowerInWatts READ getMinimumPowerInWatts NOTIFY
               powerRangeStatsChanged)
  Q_PROPERTY(int maximumPowerInWatts READ getMaximumPowerInWatts NOTIFY
               powerRangeStatsChanged)
  Q_PROPERTY(
    int stepPowerInWatts READ getStepPowerInWatts NOTIFY powerRangeStatsChanged)

  Q_PROPERTY(double minimumResistanceLevel READ getMinimumResistanceLevel NOTIFY
               resistanceLevelChanged)
  Q_PROPERTY(double maximumResistanceLevel READ getMaximumResistanceLevel NOTIFY
               resistanceLevelChanged)
  Q_PROPERTY(double stepResistanceLevel READ getStepResistanceLevel NOTIFY
               resistanceLevelChanged)

  ///

  Q_PROPERTY(AddressType addressType READ addressType WRITE setAddressType)

public:
  enum class AddressType
  {
    PublicAddress,
    RandomAddress
  };
  Q_ENUM(AddressType)

  DeviceHandler(QObject* parent = nullptr);

  void setDevice(DeviceInfo* device);
  void setAddressType(AddressType type);
  AddressType addressType() const;

  bool measuring() const;
  bool aliveHR() const;
  bool alivePower() const;
  bool aliveCSC() const;
  bool aliveFitness() const;

  // Statistics
  int hr() const;
  int time() const;
  float average() const;
  int maxHR() const;
  int minHR() const;
  float calories() const;

  double getPedalBalance() const;
  int16_t getPowerInWatts() const;
  uint32_t getWheelRevolutions() const;
  double getWheelRevsTs() const;
  uint32_t getCrankRevolutions() const;
  double getCrankRevsTs() const;
  double getInstantSpeed() const;
  double getAverageSpeed() const;
  double getInstantCadenceInRPM() const;
  double getAverageCadenceInRPM() const;
  uint32_t getTotalDistanceInM() const;
  int16_t getResistanceLevel() const;
  int16_t getInstantPowerInWatts() const;
  int16_t getAveragePowerInWatts() const;
  ////
  int16_t getMinimumPowerInWatts() const;
  int16_t getMaximumPowerInWatts() const;
  int16_t getStepPowerInWatts() const;
  double getMinimumResistanceLevel() const;
  double getMaximumResistanceLevel() const;
  double getStepResistanceLevel() const;

signals:
  void measuringChanged();
  void aliveHRChanged();
  void alivePowerChanged();
  void aliveCSCChanged();
  void aliveFitnessChanged();

  void statsChanged();

  void powerRangeStatsChanged();
  void resistanceLevelChanged();

public slots:
  void startMeasurement();
  void stopMeasurement();
  void disconnectService();

private:
  // QLowEnergyController
  void serviceDiscovered(const QBluetoothUuid&);
  void serviceScanDone();

  // QLowEnergyService
  void serviceHRStateChanged(QLowEnergyService::ServiceState s);
  void serviceFitnessMachineStateChanged(QLowEnergyService::ServiceState s);
  void serviceCyclingSpeedAndCadenceStateChanged(
    QLowEnergyService::ServiceState s);
  void serviceCyclingPowerStateChanged(QLowEnergyService::ServiceState s);

  void updateHeartRateValue(const QLowEnergyCharacteristic& c,
                            const QByteArray& value);
  void updateFitnessBikeDataValue(const QLowEnergyCharacteristic& c,
                                  const QByteArray& value);
  void updateCSCValue(const QLowEnergyCharacteristic& c,
                      const QByteArray& value);
  void updatePowerValue(const QLowEnergyCharacteristic& c,
                        const QByteArray& value);
  void confirmedHRDescriptorWrite(const QLowEnergyDescriptor& d,
                                  const QByteArray& value);

  void confirmedFitnessMachineFeaturesCharacteristicRead(
    const QLowEnergyCharacteristic& info,
    const QByteArray& value);
  void confirmedFitnessDescriptorWrite(const QLowEnergyDescriptor& d,
                                       const QByteArray& value);
  void confirmedCSCDescriptorWrite(const QLowEnergyDescriptor& d,
                                   const QByteArray& value);
  void confirmedPowerDescriptorWrite(const QLowEnergyDescriptor& d,
                                     const QByteArray& value);

private:
  void addHRMeasurement(int value);
  void addFitnessBikeDataMeasurement(const IndoorBikeData& bikeData);
  void addCSCMeasurement(const CSCMeasurementData& data);
  void addPowerMeasurement(const CyclingPowerMeasurementData& data);
  void addFitnessMachineStatusMeasurement(const FitnessMachineStatus& data);
  void addTrainingStatusMeasurement(const TrainingStatus& data);

  void tryToStop();

  QLowEnergyController* m_control = nullptr;

  QLowEnergyService* m_service_heart_rate = nullptr;
  QLowEnergyService* m_service_fitness_machine = nullptr;
  QLowEnergyService* m_service_cycling_speed_and_cadence = nullptr;
  QLowEnergyService* m_service_cycling_power = nullptr;

  std::vector<bool> m_services_running{
    false, false, false, false, false, false
  }; // heart, fitness, csc, power, fitness machine status, training status

  QLowEnergyDescriptor m_notificationHrDesc;
  QLowEnergyDescriptor m_notificationFitnessIndoorBikeDataDesc;
  QLowEnergyDescriptor m_notificationCyclingSpeedAndCadenceDesc;
  QLowEnergyDescriptor m_notificationCyclingPowerDesc;
  QLowEnergyDescriptor m_notificationFitnessMachineStatusDesc;
  QLowEnergyDescriptor m_notificationTrainingStatusDesc;

  DeviceInfo* m_currentDevice = nullptr;

  bool m_foundHeartRateService{ false };
  bool m_foundCyclingPowerService{ false };
  bool m_foundFitnessMachineService{ false };
  bool m_foundCyclingSpeedAndCadenceService{ false };

  bool m_measuring;
  int m_currentValue, m_min, m_max, m_sum;

  std::unique_ptr<IndoorBikeData> m_currentIndoorBikeData;
  std::unique_ptr<CSCMeasurementData> m_currentCSCData;
  std::unique_ptr<CyclingPowerMeasurementData> m_currentPowerData;
  std::unique_ptr<FitnessMachineFeatureData> m_currentFitnessMachineFeature;
  std::unique_ptr<SupportedPowerRange> m_currentSupportedPowerRange;
  std::unique_ptr<SupportedResistanceLevelRange>
    m_currentSupportedResistanceLevelRange;
  std::unique_ptr<FitnessMachineStatus> m_currentFitnessMachineStatus;
  std::unique_ptr<TrainingStatus> m_currentTrainingStatus;

  float m_avg, m_calories;

  // Statistics
  QDateTime m_start;
  QDateTime m_stop;

  QVector<int> m_measurements;
  QLowEnergyController::RemoteAddressType m_addressType =
    QLowEnergyController::PublicAddress;
};

#endif // DEVICEHANDLER_H
