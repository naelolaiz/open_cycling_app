/***************************************************************************
**
** Copyright (C) 2017 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the QtBluetooth module of the Qt Toolkit.
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

import QtQuick 2.5
import QtQuick.Controls 2.5

GamePage {
    id: measurePage

    errorMessage: deviceHandler.error
    infoMessage: deviceHandler.info

    function close()
    {
        deviceHandler.stopMeasurement();
        deviceHandler.disconnectService();
        app.prevPage();
    }

    Column {
        id: leftOldColumn
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.top: parent.top
        anchors.topMargin: 80
        spacing: GameSettings.fieldHeight * 0.5

        Rectangle {
            id: rectangleOnLeftOldColumn
            anchors.horizontalCenter: parent.horizontalCenter
            width: Math.min(measurePage.width, measurePage.height-GameSettings.fieldHeight*4) - 2*GameSettings.fieldMargin
            height: width
            color: "White" //GameSettings.viewColor

            Text {
                anchors.top: parent.top
                anchors.left: parent.left
                id: power
                text: "Power: "+ deviceHandler.powerInWatts +" Watts"
            }
            Text {
                id: balance
                anchors.left: power.right
                anchors.top: parent.top
                anchors.leftMargin: 10
                text: deviceHandler.powerBalance + "%"
            }
            Text {
                anchors.left: parent.left
                anchors.top: balance.bottom
                id: crankRevolutions
                text: "Crank Revolutions: " + deviceHandler.crankRevolutions
            }
            Text {
                id: crankTS
                anchors.left: crankRevolutions.right
                anchors.leftMargin: 10
                anchors.top: balance.bottom
                text: deviceHandler.crankRevsTs + " seg"
            }
            Text {
                anchors.top: crankRevolutions.bottom
                anchors.left: parent.left
                id: wheelRevs
                text: "Wheel revolutions: " + deviceHandler.wheelRevolutions
            }
            Text {
                id: wheelRevsTS
                anchors.left: wheelRevs.right
                anchors.leftMargin: 10
                anchors.top: crankRevolutions.bottom
                text: deviceHandler.wheelRevsTs + " seg"
            }
            Text {
                id: instantSpeed
                anchors.left: parent.left
                anchors.top: wheelRevs.bottom
                text: "Instant velocity: " + deviceHandler.instantSpeed + " Km/s"
            }
            Text {
                id: instantCadence
                anchors.left: parent.left
                anchors.top: instantSpeed.bottom
                text: "Instant cadence: " + deviceHandler.instantCadenceInRPM + " RPM"
            }
            Text {
                id: totalDistance
                anchors.left: parent.left
                anchors.top: instantCadence.bottom
                text: "Total distance: " + deviceHandler.totalDistanceInM + " meters"
            }
            Text {
                id: resistanceLevel
                anchors.left: parent.left
                anchors.top: totalDistance.bottom
                text: "Resistance level: " + deviceHandler.resistanceLevel
            }
        }
    }
    Column {
        id: middleColumn
        anchors.left: leftOldColumn.right
        anchors.leftMargin: 10
        anchors.top: leftOldColumn.top

        Rectangle
        {
            id: rectangleOnMiddleColumn
            width: Math.min(measurePage.width, measurePage.height-GameSettings.fieldHeight*4) - 2*GameSettings.fieldMargin
            height: width
            color: "White" //GameSettings.viewColor2
            Text {
                text:  "testing..."
            }
        }
    }
    Column {
        id: rightColumn
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.left: middleColumn.right
        anchors.leftMargin: 10
        anchors.top: leftOldColumn.top
        Rectangle
        {
            id: rectangleOnRightColumn
            width: Math.min(measurePage.width, measurePage.height-GameSettings.fieldHeight*4) - 2*GameSettings.fieldMargin
            height: width
            color: "White" //GameSettings.viewColor2
            Text {
                id: margs1
                anchors.left: rectangleOnRightColumn.left
                anchors.leftMargin: 10
                anchors.topMargin: 20
                text: "Power target(" + powerTarget.from + "-" + powerTarget.to + "): "
            }

            SpinBox {
                id: powerTarget
                editable: true
                anchors.left: margs1.right
                anchors.topMargin: 20
                anchors.right: rectangleOnRightColumn.right
                anchors.rightMargin: 10
                from: deviceHandler.minimumPowerInWatts
                to: deviceHandler.maximumPowerInWatts
                stepSize: deviceHandler.stepPowerInWatts
                onValueChanged: console.log("value changed to: " + value)
            }
            Text {
                id: margs2
                anchors.left: rectangleOnRightColumn.left
                anchors.leftMargin: 10
                anchors.top: powerTarget.bottom
                anchors.topMargin: 10
                text: "resistance target(" + deviceHandler.minimumResistanceLevel + "-" + deviceHandler.maximumResistanceLevel + "): "
            }

            SpinBox {
                id: resistanceTarget
                editable: true
                anchors.left: margs2.right
                anchors.top: powerTarget.bottom
                anchors.topMargin: 10
                property int decimals: 1
                property real realValue: value / 10.
                validator: DoubleValidator {
                        bottom: Math.min(resistanceTarget.from, resistanceTarget.to)
                        top:  Math.max(resistanceTarget.from, resistanceTarget.to)
                    }
                textFromValue: function(value, locale) {
                        return Number(value / 10).toLocaleString(locale, 'f', resistanceTarget.decimals)
                    }

                valueFromText: function(text, locale) {
                        return Number.fromLocaleString(locale, text) * 10
                    }
                from: deviceHandler.minimumResistanceLevel * 10
                to: deviceHandler.maximumResistanceLevel * 10
                stepSize: deviceHandler.stepResistanceLevel * 10
                onValueChanged: console.log("value changed to: " + realValue)
            }
            Button {
                id: sendNewResistanceTarget
                anchors.verticalCenter: resistanceTarget.verticalCenter
                anchors.left:resistanceTarget.right
                anchors.right: rectangleOnRightColumn.right
                anchors.rightMargin: 10
                text: "send"
                onPressed: console.log("sending" + resistanceTarget.realValue)
            }
        }
    }
}
