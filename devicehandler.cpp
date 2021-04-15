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

#include "devicehandler.h"
#include "deviceinfo.h"
#include "oca-global.h"
#include <QDebug>
#include <QRandomGenerator>
#include <QtEndian>

DeviceHandler::DeviceHandler(QObject* parent)
  : BluetoothBaseClass(parent)
  , m_measuring(false)
  , m_currentValue(0)
  , m_min(0)
  , m_max(0)
  , m_sum(0)
  , m_avg(0)
  , m_calories(0)
{}

void
DeviceHandler::setAddressType(AddressType type)
{
  switch (type)
  {
    case DeviceHandler::AddressType::PublicAddress:
      m_addressType = QLowEnergyController::PublicAddress;
      break;
    case DeviceHandler::AddressType::RandomAddress:
      m_addressType = QLowEnergyController::RandomAddress;
      break;
  }
}

DeviceHandler::AddressType
DeviceHandler::addressType() const
{
  if (m_addressType == QLowEnergyController::RandomAddress)
  {
      return DeviceHandler::AddressType::RandomAddress;
  }
  return DeviceHandler::AddressType::PublicAddress;
}

void
DeviceHandler::setDevice(DeviceInfo* device)
{
  clearMessages();
  m_currentDevice = device;

  // Disconnect and delete old connection
  if (m_control)
  {
    m_control->disconnectFromDevice();
    delete m_control;
    m_control = nullptr;
  }

  // Create new controller and connect it if device available
  if (m_currentDevice)
  {
    // Make connections
    //! [Connect-Signals-1]
    m_control =
      QLowEnergyController::createCentral(m_currentDevice->getDevice(), this);
    //! [Connect-Signals-1]
    m_control->setRemoteAddressType(m_addressType);
    //! [Connect-Signals-2]
    connect(m_control,
            &QLowEnergyController::serviceDiscovered,
            this,
            &DeviceHandler::serviceDiscovered);
    connect(m_control,
            &QLowEnergyController::discoveryFinished,
            this,
            &DeviceHandler::serviceScanDone);

    auto cantConnectError = [this](QLowEnergyController::Error error)
    {
      Q_UNUSED(error);
      setError("Cannot connect to remote device.");
    };

    connect(
      m_control,
      static_cast<void (QLowEnergyController::*)(QLowEnergyController::Error)>(
        &QLowEnergyController::error),
      this,
      cantConnectError);
    connect(m_control, &QLowEnergyController::connected, this, [this]()
      {
        setInfo("Controller connected. Search services...");
        m_control->discoverServices();
      });
    connect(m_control, &QLowEnergyController::disconnected, this, [this]()
      {
        setError("LowEnergy controller disconnected");
      });

    // Connect
    m_control->connectToDevice();
    //! [Connect-Signals-2]
  }
}

void
DeviceHandler::startMeasurement()
{
  if (aliveHR()) {
    m_start = QDateTime::currentDateTime();
    m_min = 0;
    m_max = 0;
    m_avg = 0;
    m_sum = 0;
    m_calories = 0;
    m_measuring = true;
    m_measurements.clear();
    emit measuringChanged();
  }
}

void
DeviceHandler::stopMeasurement()
{
  m_measuring = false;
  emit measuringChanged();
}

//! [Filter services]
void
DeviceHandler::serviceDiscovered(const QBluetoothUuid& gatt)
{
  if (gatt == QBluetoothUuid(QBluetoothUuid::HeartRate))
  {
    setInfo("Heart Rate service discovered. Waiting for service scan to be "
            "done...");
    m_foundHeartRateService = true;
  }
  else if (gatt == QBluetoothUuid(QBluetoothUuid::CyclingPower))
  {
    setInfo("Cycling power service discovered. Waiting for service scan to be "
            "done...");
    m_foundCyclingPowerService = true;
  }
  else if (gatt == QBluetoothUuid(QBluetoothUuid::CyclingSpeedAndCadence))
  {
    setInfo("Cycling Speed and Cadence service discovered. Waiting for service "
            "scan to be done...");
    m_foundCyclingSpeedAndCadenceService = true;
  }
  else if (gatt == FitnessMachineService::getServiceUuid())
  {
    setInfo("Fitness Machine service discovered. Waiting for service scan to "
            "be done...");
    m_foundFitnessMachineService = true;
  }
}
//! [Filter services 1]

void
DeviceHandler::serviceScanDone()
{
  setInfo("Service scan done.");

  // Delete old services if available
  for (auto*& service : std::vector<QLowEnergyService*>
        {{ m_service_heart_rate,
           m_service_cycling_power,
           m_service_fitness_machine,
           m_service_cycling_speed_and_cadence }})
  {
    if (service)
    {
      delete service;
      service = nullptr;
    }
  }

  //! [Filter HeartRate service 2]
  // If heartRateService found, create new service
  if (m_foundHeartRateService)
  {
    m_service_heart_rate = m_control->createServiceObject(
      QBluetoothUuid(QBluetoothUuid::HeartRate), this);
  }
  if (m_foundCyclingPowerService)
  {
    m_service_cycling_power = m_control->createServiceObject(
      QBluetoothUuid(QBluetoothUuid::CyclingPower), this);
  }
  if (m_foundFitnessMachineService)
  {
    m_service_fitness_machine = m_control->createServiceObject(
      FitnessMachineService::getServiceUuid(), this);
  }
  if (m_foundCyclingSpeedAndCadenceService)
  {
    m_service_cycling_speed_and_cadence = m_control->createServiceObject(
      QBluetoothUuid(QBluetoothUuid::CyclingSpeedAndCadence), this);
  }

  ///// create connections
  if (m_service_heart_rate)
  {
    connect(m_service_heart_rate,
            &QLowEnergyService::stateChanged,
            this,
            &DeviceHandler::serviceHRStateChanged);
    connect(m_service_heart_rate,
            &QLowEnergyService::characteristicChanged,
            this,
            &DeviceHandler::updateHeartRateValue);
    connect(m_service_heart_rate,
            &QLowEnergyService::descriptorWritten,
            this,
            &DeviceHandler::confirmedHRDescriptorWrite);
    m_service_heart_rate->discoverDetails();
  }
  else
  {
    setInfo("Heart Rate Service not found.");
  }

  if (m_service_cycling_power)
  {
    connect(m_service_cycling_power,
            &QLowEnergyService::stateChanged,
            this,
            &DeviceHandler::serviceCyclingPowerStateChanged);
    connect(m_service_cycling_power,
            &QLowEnergyService::characteristicChanged,
            this,
            &DeviceHandler::updatePowerValue);
    connect(m_service_cycling_power,
            &QLowEnergyService::descriptorWritten,
            this,
            &DeviceHandler::confirmedPowerDescriptorWrite);
    m_service_cycling_power->discoverDetails();
  }
  else
  {
    setInfo("Cycling Power Service not found.");
  }

  if (m_service_fitness_machine)
  {
    // 0x2acc // fitness machine feature
    // m_service_fitness_machine->readCharacteristic(QLowEnergyCharacteristic::)

    //        const QLowEnergyCharacteristic ch =
    //        m_service_fitness_machine->characteristic(QBluetoothUuid(quint16(0x2acc)));
    //        m_service_fitness_machine->readCharacteristic(
    //        for (const QLowEnergyCharacteristic &ch : chars) {
    //            qDebug() << ch.name();
    //            CharacteristicInfo cInfo(ch);
    //            m_characteristics.append(cInfo);
    //}
    connect(m_service_fitness_machine,
            &QLowEnergyService::stateChanged,
            this,
            &DeviceHandler::serviceFitnessMachineStateChanged);
    connect(m_service_fitness_machine,
            &QLowEnergyService::characteristicChanged,
            this,
            &DeviceHandler::updateFitnessBikeDataValue);
    connect(m_service_fitness_machine,
            &QLowEnergyService::descriptorWritten,
            this,
            &DeviceHandler::confirmedFitnessDescriptorWrite);
    connect(m_service_fitness_machine,
            &QLowEnergyService::characteristicRead,
            this,
            &DeviceHandler::confirmedFitnessMachineFeaturesCharacteristicRead);
    m_service_fitness_machine->discoverDetails();
  }
  else
  {
    setInfo("Fitness machine service not found.");
  }

  if (m_service_cycling_speed_and_cadence)
  {
    connect(m_service_cycling_speed_and_cadence,
            &QLowEnergyService::stateChanged,
            this,
            &DeviceHandler::serviceCyclingSpeedAndCadenceStateChanged);
    connect(m_service_cycling_speed_and_cadence,
            &QLowEnergyService::characteristicChanged,
            this,
            &DeviceHandler::updateCSCValue);
    connect(m_service_cycling_speed_and_cadence,
            &QLowEnergyService::descriptorWritten,
            this,
            &DeviceHandler::confirmedCSCDescriptorWrite);
    m_service_cycling_speed_and_cadence->discoverDetails();
  }
  else
  {
    setInfo("CSC service not found.");
  }

  //! [Filter HeartRate service 2]
}

// Service functions
//! [Find HRM characteristic]
void
DeviceHandler::serviceHRStateChanged(QLowEnergyService::ServiceState s)
{
  switch (s)
  {
    case QLowEnergyService::DiscoveringServices:
      setInfo(tr("Discovering HR services..."));
      break;
    case QLowEnergyService::ServiceDiscovered: {
      setInfo(tr("Service HR discovered."));

      const QLowEnergyCharacteristic hrChar =
        m_service_heart_rate->characteristic(
          QBluetoothUuid(QBluetoothUuid::HeartRateMeasurement));
      if (!hrChar.isValid())
      {
        setError("HR Data not found.");
        break;
      }

      m_notificationHrDesc =
        hrChar.descriptor(QBluetoothUuid::ClientCharacteristicConfiguration);
      if (m_notificationHrDesc.isValid())
      {
        m_service_heart_rate->writeDescriptor(m_notificationHrDesc,
                                              QByteArray::fromHex("0100"));
        m_services_running.mHeart = true;
      }
      break;
    }
    default:
      // nothing for now
      break;
  }
  emit aliveHRChanged();
}

void
DeviceHandler::serviceFitnessMachineStateChanged(
  QLowEnergyService::ServiceState s)
{
  switch (s)
  {
    case QLowEnergyService::DiscoveringServices:
      setInfo(tr("Discovering Fitness services..."));
      break;
      //////
      ///// service discovered
    case QLowEnergyService::ServiceDiscovered:
    {
      setInfo(tr("Service Fitness discovered."));
      ///////
      const QLowEnergyCharacteristic fitnessMachineFeatureChar =
        m_service_fitness_machine->characteristic(
          FitnessMachineFeatureData::getCharUuid());
      if (!fitnessMachineFeatureChar.isValid())
      {
        setError("Fitness Machine Feature Not found");
        break;
      }
      m_service_fitness_machine->readCharacteristic(fitnessMachineFeatureChar);
      ///////
      const QLowEnergyCharacteristic powerRangeChar =
        m_service_fitness_machine->characteristic(
          SupportedPowerRange::getCharUuid());
      if (!powerRangeChar.isValid())
      {
        setError("Power range Not found");
        break;
      }
      m_service_fitness_machine->readCharacteristic(powerRangeChar);
      ////////
      const QLowEnergyCharacteristic resistanceRangeChar =
        m_service_fitness_machine->characteristic(
          SupportedResistanceLevelRange::getCharUuid());
      if (!resistanceRangeChar.isValid())
      {
        setError("Resistance range Not found");
        break;
      }
      m_service_fitness_machine->readCharacteristic(resistanceRangeChar);
      ///////
      /// enable read notifications for indor bike data
      ///
      const QLowEnergyCharacteristic indoorBikeDataChar =
        m_service_fitness_machine->characteristic(
          IndoorBikeData::getCharUuid());
      if (!indoorBikeDataChar.isValid())
      {
        setError("Indoor Bike Data not found.");
        break;
      }
      ///// acquire notify of indoor bike data
      m_notificationFitnessIndoorBikeDataDesc = indoorBikeDataChar.descriptor(
        QBluetoothUuid::ClientCharacteristicConfiguration);
      if (m_notificationFitnessIndoorBikeDataDesc.isValid())
      {
        m_service_fitness_machine->writeDescriptor(
          m_notificationFitnessIndoorBikeDataDesc, QByteArray::fromHex("0100"));
        m_services_running.mFitness = true;
      }
      ///////
      /// enable read notifications fitness machine status
      ///

      const QLowEnergyCharacteristic fitnessMachineStatusChar =
        m_service_fitness_machine->characteristic(
          FitnessMachineStatus::getCharUuid());
      if (!fitnessMachineFeatureChar.isValid())
      {
        setError("Fitness machine status Not found");
        break;
      }
      m_notificationFitnessMachineStatusDesc =
        fitnessMachineStatusChar.descriptor(
          QBluetoothUuid::ClientCharacteristicConfiguration);
      if (m_notificationFitnessMachineStatusDesc.isValid())
      {
        m_service_fitness_machine->writeDescriptor(
          m_notificationFitnessMachineStatusDesc, QByteArray::fromHex("0100"));
        m_services_running.mFitnessMachineStatus = true;
      }
      ///////
      /// enable read notifications training status
      ///

      const QLowEnergyCharacteristic trainingStatusChar =
        m_service_fitness_machine->characteristic(
          TrainingStatus::getCharUuid());
      if (!trainingStatusChar.isValid())
      {
        setError("Training status Not found");
        break;
      }
      m_notificationTrainingStatusDesc = trainingStatusChar.descriptor(
        QBluetoothUuid::ClientCharacteristicConfiguration);
      if (m_notificationTrainingStatusDesc.isValid())
      {
        m_service_fitness_machine->writeDescriptor(
          m_notificationTrainingStatusDesc, QByteArray::fromHex("0100"));
        m_services_running.mTrainingStatus = true;
      }
      // m_service_fitness_machine->readCharacteristic(resistanceRangeChar);

      break;
    } /////
    /////////// service discovered
    default:
      // nothing for now
      break;
  }
  emit aliveFitnessChanged();
}

void
DeviceHandler::serviceCyclingSpeedAndCadenceStateChanged(
  QLowEnergyService::ServiceState s)
{
  switch (s)
  {
    case QLowEnergyService::DiscoveringServices:
      setInfo(tr("Discovering CSC services..."));
      break;
    case QLowEnergyService::ServiceDiscovered:
    {
      setInfo(tr("Service CSC discovered."));
      const QLowEnergyCharacteristic cscMeasurementChar =
        m_service_cycling_speed_and_cadence->characteristic(
          QBluetoothUuid::CSCMeasurement);
      if (!cscMeasurementChar.isValid())
      {
        setError("CSC Data not found.");
        break;
      }

      m_notificationCyclingSpeedAndCadenceDesc = cscMeasurementChar.descriptor(
        QBluetoothUuid::ClientCharacteristicConfiguration);
      if (m_notificationCyclingSpeedAndCadenceDesc.isValid())
      {
        m_service_cycling_speed_and_cadence->writeDescriptor(
          m_notificationCyclingSpeedAndCadenceDesc,
          QByteArray::fromHex("0100"));
        m_services_running.mCSC = true;
      }
      break;
    }
    default:
      // nothing for now
      break;
  }
  emit aliveCSCChanged();
}

void
DeviceHandler::serviceCyclingPowerStateChanged(
  QLowEnergyService::ServiceState s)
{
  switch (s)
  {
    case QLowEnergyService::DiscoveringServices:
      setInfo(tr("Discovering Power services..."));
      break;
    case QLowEnergyService::ServiceDiscovered:
    {
      setInfo(tr("Service Power discovered."));
      const QLowEnergyCharacteristic powerMeasurementChar =
        m_service_cycling_power->characteristic(
          QBluetoothUuid::CyclingPowerMeasurement);
      if (!powerMeasurementChar.isValid())
      {
        setError("Power Measurement Data not found.");
        break;
      }

      m_notificationCyclingPowerDesc = powerMeasurementChar.descriptor(
        QBluetoothUuid::ClientCharacteristicConfiguration);
      if (m_notificationCyclingPowerDesc.isValid())
      {
        m_service_cycling_power->writeDescriptor(m_notificationCyclingPowerDesc,
                                                 QByteArray::fromHex("0100"));
        m_services_running.mPower = true;
      }
      break;
    }
    default:
      // nothing for now
      break;
  }
  emit alivePowerChanged();
}
//! [Find HRM characteristic]

//! [Reading value]
void
DeviceHandler::updateHeartRateValue(const QLowEnergyCharacteristic& c,
                                    const QByteArray& value)
{
  // ignore any other characteristic change -> shouldn't really happen though
  if (c.uuid() != QBluetoothUuid(QBluetoothUuid::HeartRateMeasurement))
  {
    return;
  }

  auto data = reinterpret_cast<const quint8*>(value.constData());
  quint8 flags = *data;

  // Heart Rate
  int hrvalue = 0;
  if (flags & 0x1) // HR 16 bit? otherwise 8 bit
  {
    hrvalue = static_cast<int>(qFromLittleEndian<quint16>(data[1]));
  }
  else
  {
    hrvalue = static_cast<int>(data[1]);
  }

  addHRMeasurement(hrvalue);
}

void
DeviceHandler::updateFitnessBikeDataValue(const QLowEnergyCharacteristic& c,
                                          const QByteArray& value)
{
  // ignore any other characteristic change -> shouldn't really happen though
  if (c.uuid() == IndoorBikeData::getCharUuid())
  {
    const IndoorBikeData indoorBikeData(
      reinterpret_cast<const quint8*>(value.constData()));
    addFitnessBikeDataMeasurement(indoorBikeData);
  }
  if (c.uuid() == FitnessMachineStatus::getCharUuid())
  {
    const FitnessMachineStatus fitnessMachineStatus(
      reinterpret_cast<const quint8*>(value.constData()));
    addFitnessMachineStatusMeasurement(fitnessMachineStatus);
  }
  if (c.uuid() == TrainingStatus::getCharUuid())
  {
    const TrainingStatus trainingStatus(
      reinterpret_cast<const quint8*>(value.constData()));
    addTrainingStatusMeasurement(trainingStatus);
  }
}

void
DeviceHandler::updateCSCValue(const QLowEnergyCharacteristic& c,
                              const QByteArray& value)
{
  if (c.uuid() != CSCMeasurementData::getCharUuid())
  {
    return;
  }
  const CSCMeasurementData measurementData(
    reinterpret_cast<const quint8*>(value.constData()), m_currentCSCData.get());
  addCSCMeasurement(measurementData);
}

void
DeviceHandler::updatePowerValue(const QLowEnergyCharacteristic& c,
                                const QByteArray& value)
{
  if (c.uuid() != CyclingPowerMeasurementData::getCharUuid())
  {
    return;
  }

  const CyclingPowerMeasurementData measurementData(
    reinterpret_cast<const quint8*>(value.constData()));
  addPowerMeasurement(measurementData);
}

//! [Reading value]
void
DeviceHandler::confirmedHRDescriptorWrite(const QLowEnergyDescriptor& d,
                                          const QByteArray& value)
{
  if (d.isValid() && d == m_notificationHrDesc &&
      value == QByteArray::fromHex("0000"))
  {
    // disabled notifications -> assume disconnect intent
    m_services_running.mHeart = false;
    tryToStop();
  }
}

void
DeviceHandler::confirmedFitnessMachineFeaturesCharacteristicRead(
  const QLowEnergyCharacteristic& info,
  const QByteArray& value)
{
  if (!info.isValid())
  {
    qDebug() << "FitnessMachineFeaturesCharRead not good!";
  }
  const auto* data = reinterpret_cast<const quint8*>(value.constData());

  if (info.uuid() == FitnessMachineFeatureData::getCharUuid())
  {
      m_currentFitnessMachineFeature.reset(new FitnessMachineFeatureData(data));
      qDebug() << m_currentFitnessMachineFeature->dump().c_str();
  }
  else if (info.uuid() == SupportedPowerRange::getCharUuid())
  {
      m_currentSupportedPowerRange.reset(new SupportedPowerRange(data));
      qDebug() << m_currentSupportedPowerRange->dump().c_str();
      emit powerRangeStatsChanged();
  }
  else if (info.uuid() == SupportedResistanceLevelRange::getCharUuid())
  {
      m_currentSupportedResistanceLevelRange.reset(new SupportedResistanceLevelRange(data));
      qDebug() << m_currentSupportedResistanceLevelRange->dump().c_str();
      emit resistanceLevelChanged();
  }
}

void
DeviceHandler::confirmedFitnessDescriptorWrite(const QLowEnergyDescriptor& d,
                                               const QByteArray& value)
{
  if (!d.isValid())
  {
      return;
  }
  if (value == QByteArray::fromHex("0000"))
  {
      if (d == m_notificationFitnessIndoorBikeDataDesc)
      {
          // disabled notifications -> assume disconnect intent
          m_services_running.mFitness = false;
      }
      else if (d == m_notificationFitnessMachineStatusDesc)
      {
          // disabled notifications -> assume disconnect intent
          m_services_running.mFitnessMachineStatus = false;
      }
      else if (d == m_notificationTrainingStatusDesc)
      {
          // disabled notifications -> assume disconnect intent
          m_services_running.mTrainingStatus = false;
      }
      tryToStop();
  }
}

void
DeviceHandler::confirmedCSCDescriptorWrite(const QLowEnergyDescriptor& d,
                                           const QByteArray& value)
{
  if (d.isValid() &&
      d == m_notificationCyclingSpeedAndCadenceDesc &&
      value == QByteArray::fromHex("0000"))
  {
      // disabled notifications -> assume disconnect intent
      m_services_running.mCSC = false;
      tryToStop();
  }
}

void
DeviceHandler::confirmedPowerDescriptorWrite(const QLowEnergyDescriptor& d,
                                             const QByteArray& value)
{
  if (d.isValid() &&
      d == m_notificationCyclingPowerDesc &&
      value == QByteArray::fromHex("0000"))
  {
      // disabled notifications -> assume disconnect intent
      m_services_running.mPower = false;
      tryToStop();
  }
}

void
DeviceHandler::disconnectService()
{
  std::vector<QLowEnergyService**> servicesToDelete;
  auto disableNotifications =
    [&servicesToDelete](const QLowEnergyDescriptor& descriptor,
                        QLowEnergyService** service)
    {
      const bool notificationCurrentlyEnabled =
        descriptor.isValid() && (*service) &&
        descriptor.value() == QByteArray::fromHex("0100");

      if (notificationCurrentlyEnabled)
      {
          (*service)->writeDescriptor(descriptor, QByteArray::fromHex("0000"));
      }
      else
      {
          servicesToDelete.push_back(service);
      }
    };

  typedef std::tuple<const QLowEnergyDescriptor&, QLowEnergyService**, bool&> ServiceAttributesTuple;

  const std::vector<ServiceAttributesTuple> servicesTuples
  {
    { m_notificationHrDesc,                     &m_service_heart_rate,                m_foundHeartRateService },
    { m_notificationCyclingPowerDesc,           &m_service_cycling_power,             m_foundCyclingPowerService },
    { m_notificationFitnessIndoorBikeDataDesc,  &m_service_fitness_machine,           m_foundFitnessMachineService },
    { m_notificationCyclingSpeedAndCadenceDesc, &m_service_cycling_speed_and_cadence, m_foundCyclingSpeedAndCadenceService }
  };

  for (auto& tuple : servicesTuples)
  {
      std::get<2>(tuple) = false;
      disableNotifications(std::get<0>(tuple), std::get<1>(tuple));
  }

  if (servicesToDelete.size() > 0 && m_control)
  {
      m_control->disconnectFromDevice();
  }
  for (auto** service : servicesToDelete)
  {
      delete *service;
      *service = nullptr;
  }
}

bool
DeviceHandler::measuring() const
{
  return m_measuring;
}

bool
DeviceHandler::aliveHR() const
{
  if (m_service_heart_rate)
  {
      return m_service_heart_rate->state() == QLowEnergyService::ServiceDiscovered;
  }

  return false;
}

bool
DeviceHandler::alivePower() const
{
  if (m_service_cycling_power)
  {
    return m_service_cycling_power->state() == QLowEnergyService::ServiceDiscovered;
  }
  return false;
}

bool
DeviceHandler::aliveCSC() const
{
  if (m_service_cycling_speed_and_cadence)
  {
      return m_service_cycling_speed_and_cadence->state() == QLowEnergyService::ServiceDiscovered;
  }
  return false;
}

bool
DeviceHandler::aliveFitness() const
{
  if (m_service_fitness_machine)
  {
      return m_service_fitness_machine->state() == QLowEnergyService::ServiceDiscovered;
  }
  return false;
}

int
DeviceHandler::hr() const
{
  return m_currentValue;
}

int
DeviceHandler::time() const
{
  return m_start.secsTo(m_stop);
}

int
DeviceHandler::maxHR() const
{
  return m_max;
}

int
DeviceHandler::minHR() const
{
  return m_min;
}

float
DeviceHandler::average() const
{
  return m_avg;
}

float
DeviceHandler::calories() const
{
  return m_calories;
}

double
DeviceHandler::getPedalBalance() const
{
  if (!m_currentPowerData)
  {
    return 0.;
  }
  return m_currentPowerData->getPowerBalance();
}

int16_t
DeviceHandler::getPowerInWatts() const
{
  if (!m_currentPowerData)
  {
    return 0;
  }
  return m_currentPowerData->getInstantPowerInWatts();
}

uint32_t
DeviceHandler::getWheelRevolutions() const
{
  if (!m_currentCSCData)
  {
    return 0u;
  }
  return m_currentCSCData->getWheelRevolutions();
}

double
DeviceHandler::getWheelRevsTs() const
{
  if (!m_currentCSCData)
  {
    return 0u;
  }
  return m_currentCSCData->getLastWheelEventTimestampInSecs();
}

uint32_t
DeviceHandler::getCrankRevolutions() const
{
  if (!m_currentCSCData)
  {
    return 0u;
  }
  return m_currentCSCData->getCrankRevolutions();
}

double
DeviceHandler::getCrankRevsTs() const
{
  if (!m_currentCSCData)
  {
    return 0u;
  }
  return m_currentCSCData->getLastCrankEventTimestampInSecs();
}

double
DeviceHandler::getInstantSpeed() const
{
  if (!m_currentIndoorBikeData)
  {
    return 0.;
  }
  return m_currentIndoorBikeData->getInstantSpeedInKmPerSecond();
}

double
DeviceHandler::getAverageSpeed() const
{
  if (!m_currentIndoorBikeData)
  {
    return 0.;
  }
  return m_currentIndoorBikeData->getAverageSpeedInKmPerSecond();
}

double
DeviceHandler::getInstantCadenceInRPM() const
{
  if (!m_currentIndoorBikeData)
  {
    return 0.;
  }
  return m_currentIndoorBikeData->getInstantCadenceInRPM();
}

double
DeviceHandler::getAverageCadenceInRPM() const
{
  if (!m_currentIndoorBikeData)
  {
    return 0.;
  }
  return m_currentIndoorBikeData->getAverageCadenceInRPM();
}

uint32_t
DeviceHandler::getTotalDistanceInM() const
{
  if (!m_currentIndoorBikeData)
  {
    return 0u;
  }
  return m_currentIndoorBikeData->getTotalDistanceInMeters();
}

int16_t
DeviceHandler::getResistanceLevel() const
{
  if (!m_currentIndoorBikeData)
  {
    return 0;
  }
  return m_currentIndoorBikeData->getResistanceLevel();
}

int16_t
DeviceHandler::getInstantPowerInWatts() const
{
  if (!m_currentIndoorBikeData)
  {
    return 0;
  }
  return m_currentIndoorBikeData->getInstantPowerInWatts();
}

int16_t
DeviceHandler::getAveragePowerInWatts() const
{
  if (!m_currentIndoorBikeData)
  {
    return 0;
  }
  return m_currentIndoorBikeData->getAveragePowerInWatts();
}

int16_t
DeviceHandler::getMinimumPowerInWatts() const
{
  if (!m_currentSupportedPowerRange)
  {
    return 0;
  }
  return m_currentSupportedPowerRange->getMinimumPowerInWatts();
}

int16_t
DeviceHandler::getMaximumPowerInWatts() const
{
  if (!m_currentSupportedPowerRange)
  {
    return 0;
  }
  return m_currentSupportedPowerRange->getMaximumPowerInWatts();
}

int16_t
DeviceHandler::getStepPowerInWatts() const
{
  if (!m_currentSupportedPowerRange)
  {
    return 0;
  }
  return m_currentSupportedPowerRange->getMinimumIncrementInWatts();
}

double
DeviceHandler::getMinimumResistanceLevel() const
{
  if (!m_currentSupportedResistanceLevelRange)
  {
    return 0.;
  }
  return m_currentSupportedResistanceLevelRange->getMinimumResistanceLevel();
}

double
DeviceHandler::getMaximumResistanceLevel() const
{
  if (!m_currentSupportedResistanceLevelRange)
  {
    return 0.;
  }
  return m_currentSupportedResistanceLevelRange->getMaximumResistanceLevel();
}

double
DeviceHandler::getStepResistanceLevel() const
{
  if (!m_currentSupportedResistanceLevelRange)
  {
    return 0.;
  }
  return m_currentSupportedResistanceLevelRange->getMinimumIncrement();
}

void
DeviceHandler::addHRMeasurement(int value)
{
  m_currentValue = value;

  // If measuring and value is appropriate
  if (m_measuring && value > 30 && value < 250)
  {
    m_stop = QDateTime::currentDateTime();
    m_measurements << value;

    m_min = m_min == 0 ? value : qMin(value, m_min);
    m_max = qMax(value, m_max);
    m_sum += value;
    m_avg = (double)m_sum / m_measurements.size();
    m_calories =
      ((-55.0969 + (0.6309 * m_avg) + (0.1988 * 94) + (0.2017 * 24)) / 4.184) *
      60 * time() / 3600;
  }

  emit statsChanged();
}

void
DeviceHandler::addFitnessBikeDataMeasurement(const IndoorBikeData& bikeData)
{
  // first time, or new data
  if (!m_currentIndoorBikeData ||
      (m_currentIndoorBikeData && *m_currentIndoorBikeData != bikeData))
  {
    qDebug() << bikeData.dump().c_str();
  }
  m_currentIndoorBikeData.reset(new IndoorBikeData(bikeData));
  emit statsChanged();
}

void
DeviceHandler::addCSCMeasurement(const CSCMeasurementData& data)
{
  if (!m_currentCSCData || (m_currentCSCData && *m_currentCSCData != data))
  {
    qDebug() << data.dump().c_str();
  }
  m_currentCSCData.reset(new CSCMeasurementData(data));
  emit statsChanged();
}

void
DeviceHandler::addPowerMeasurement(const CyclingPowerMeasurementData& data)
{
  if (!m_currentPowerData ||
      (m_currentPowerData && *m_currentPowerData != data))
  {
    qDebug() << data.dump().c_str();
  }
  m_currentPowerData.reset(new CyclingPowerMeasurementData(data));
  emit statsChanged();
}

void
DeviceHandler::addFitnessMachineStatusMeasurement(
  const FitnessMachineStatus& data)
{
  qDebug() << data.dump().c_str();
  m_currentFitnessMachineStatus.reset(new FitnessMachineStatus(data));
  emit statsChanged();
}

void
DeviceHandler::addTrainingStatusMeasurement(const TrainingStatus& data)
{
  qDebug() << data.dump().c_str();
  m_currentTrainingStatus.reset(new TrainingStatus(data));
  emit statsChanged();
}

void
DeviceHandler::tryToStop()
{
  if (!m_services_running.isAnyActive())
  {
    m_control->disconnectFromDevice();
    if (m_service_heart_rate)
    {
      delete m_service_heart_rate;
      m_service_heart_rate = nullptr;
    }
    if (m_service_cycling_power)
    {
      delete m_service_cycling_power;
      m_service_cycling_power = nullptr;
    }
    if (m_service_cycling_speed_and_cadence)
    {
      delete m_service_cycling_speed_and_cadence;
      m_service_cycling_speed_and_cadence = nullptr;
    }
    if (m_service_fitness_machine)
    {
      delete m_service_fitness_machine;
      m_service_fitness_machine = nullptr;
    }
  }
}
