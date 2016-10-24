#ifndef DEFINES_H
#define DEFINES_H

#define BTSerial Serial1
#define SerialPrint(X) Serial.print(X)
#define SerialPrintln(X) Serial.println(X)
#define SerialPrintBT(X) BTSerial.print(X)
#define SerialPrintlnBT(X) BTSerial.println(X)

// Periods
#define SENSOR_PERIOD 2
#define BIG_SENSOR_PERIOD 8
#define ODOMETR_PERIOD 5
#define DRIVE_PERIOD 2
#define LINK_PERIOD 100
#define ACTUATORS_PERIOD 0

// PIN
#define FRONT_LEFT A0
#define FRONT_RIGHT A3
#define LEFT A1
#define RIGHT A2
#define LEFT_BIG A4
#define RIGHT_BIG A5

#define ESC_PIN 2
#define SERVO_PIN 3
#define ENCODER_1 4
#define ENCODER_2 5

// Engine
#define ENG_ZERO_SPEED 1500

// -- SEVO --
#define SRV_MAX_ANGLE 150
#define SRV_CENTER 750

#endif // DEFINES_H  
