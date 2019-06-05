/*******************************************************************************
* Copyright 2016 ROBOTIS CO., LTD.
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*******************************************************************************/

/** Please refer to each DYNAMIXEL eManual(http://emanual.robotis.com) for supported Operating Mode
 * Operating Mode
 *  1. OP_POSITION                (Position Mode in protocol2.0, Joint Mode in protocol1.0)
 *  2. OP_VELOCITY                (Velocity Mode in protocol2.0, Speed Mode in protocol1.0)
 *  3. OP_PWM                     (PWM Mode in protocol2.0)
 *  4. OP_EXTENDED_POSITION       (Extended Position Mode in protocol2.0, Multi-turn Mode(only MX series) in protocol1.0)
 *  5. OP_CURRENT                 (Current Mode in protocol2.0, Torque Mode(only MX64,MX106) in protocol1.0)
 *  6. OP_CURRENT_BASED_POSITION  (Current Based Postion Mode in protocol2.0 (except MX28, XL430))
 */

#include <Dynamixel2Arduino.h>

#ifdef ARDUINO_AVR_UNO
  #include <SoftwareSerial.h>
  SoftwareSerial soft_serial(7, 8); //DYNAMIXEL Shield UART RX/TX
  #define DXL_SERIAL   Serial
  #define DEBUG_SERIAL soft_serial
  const uint8_t RS485_DIR_PIN = 2; //DYNAMIXEL Shield
#elif ARDUINO_AVR_MEGA2560
  #define DXL_SERIAL   Serial
  #define DEBUG_SERIAL Serial1
  const uint8_t RS485_DIR_PIN = 2; //DYNAMIXEL Shield
#elif CommXEL_W
  #define DXL_SERIAL    Serial2
  #define DEBUG_SERIAL  Serial
  const uint8_t RS485_DIR_PIN = 15;
#else
  #define DXL_SERIAL   Serial1
  #define DEBUG_SERIAL Serial
  const uint8_t RS485_DIR_PIN = 2; //DYNAMIXEL Shield
#endif

const uint8_t DXL_ID = 1;
const float DXL_PROTOCOL_VERSION = 2.0;

Dynamixel2Arduino dxl(DXL_SERIAL, RS485_DIR_PIN);

void setup() {
  // put your setup code here, to run once:

  // Use Serial to debug.
  DEBUG_SERIAL.begin(115200);

  // Set Port baudrate to 1Mbps. This has to match with DYNAMIXEL baudrate.
  dxl.begin(1000000);
  // Set Port Protocol Version. This has to match with DYNAMIXEL protocol version.
  dxl.setPortProtocolVersion(DXL_PROTOCOL_VERSION);
  // Get DYNAMIXEL information
  dxl.ping(DXL_ID);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  // Position Control Mode in protocol2.0, Joint Mode in protocol1.0
  // Turn off torquen when configuring items in EEPROM area
  dxl.torqueOff(DXL_ID);
  dxl.setOperatingMode(DXL_ID, OP_POSITION);
  dxl.torqueOn(DXL_ID);
  if(dxl.setGoalPosition(DXL_ID, 512)){
    delay(1000);
    DEBUG_SERIAL.print("Present Position : ");
    DEBUG_SERIAL.println(dxl.getPresentPosition(DXL_ID)); DEBUG_SERIAL.println();
  }

  // Velocity Contorl Mode in protocol2.0, Speed Mode in protocol1.0
  dxl.torqueOff(DXL_ID);
  dxl.setOperatingMode(DXL_ID, OP_VELOCITY);
  dxl.torqueOn(DXL_ID);
  if(dxl.setGoalVelocity(DXL_ID, 128)){
    delay(1000);
    DEBUG_SERIAL.print("Present Velocity : ");
    DEBUG_SERIAL.println(dxl.getPresentVelocity(DXL_ID)); DEBUG_SERIAL.println();
  }

  // Extended Position Contorl Mode in protocol2.0, Multi-turn Mode(only MX series) in protocol1.0
  dxl.torqueOff(DXL_ID);
  dxl.setOperatingMode(DXL_ID, OP_EXTENDED_POSITION);
  dxl.torqueOn(DXL_ID);
  if(dxl.setGoalPosition(DXL_ID, 4096)){
    delay(1000);
    DEBUG_SERIAL.print("Present Extended Position : ");
    DEBUG_SERIAL.println(dxl.getPresentPosition(DXL_ID)); DEBUG_SERIAL.println();
  }

  // PWM Contorl Mode in protocol2.0
  dxl.torqueOff(DXL_ID);
  dxl.setOperatingMode(DXL_ID, OP_PWM);
  dxl.torqueOn(DXL_ID);
  if(dxl.setGoalPWM(DXL_ID, 200)){
    delay(1000);
    DEBUG_SERIAL.print("Present PWM : ");
    DEBUG_SERIAL.println(dxl.getPresentPWM(DXL_ID)); DEBUG_SERIAL.println();
  }
  
  // Current Contorl Mode in protocol2.0, Torque Mode(only MX64,MX106) in protocol1.0
  dxl.torqueOff(DXL_ID);
  dxl.setOperatingMode(DXL_ID, OP_CURRENT);
  dxl.torqueOn(DXL_ID);
  if(dxl.setGoalCurrent(DXL_ID, 256)){
    delay(1000);
    DEBUG_SERIAL.print("Present Current : ");
    DEBUG_SERIAL.println(dxl.getPresentCurrent(DXL_ID)); DEBUG_SERIAL.println();
  }
  
  // Current Based Postion Contorl Mode in protocol2.0 (except MX28, XL430)
  dxl.torqueOff(DXL_ID);
  dxl.setOperatingMode(DXL_ID, OP_CURRENT_BASED_POSITION);
  dxl.torqueOn(DXL_ID);
  if(dxl.setGoalPosition(DXL_ID, 8192)){
    delay(1000);
    DEBUG_SERIAL.print("Present Current Based Position : ");
    DEBUG_SERIAL.println(dxl.getPresentPosition(DXL_ID)); DEBUG_SERIAL.println();
  }
}