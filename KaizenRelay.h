//KaizenRelay.h
//Version 2.0 - 2021 December 29
//CANtrolls, LLC. - Vadim Belogorodsky

#ifndef KAIZENRELAY_H
#define KAIZENRELAY_H

#include "KaizenRelayPINS.h"
#include "KaizenRelayVARIABLES.h"
#include "KaizenRelayCAN.h"
#include "KaizenRelayEEPROM.h"
#include "KaizenRelaySERIAL.h"

//Other Function Prototypes:
void HardwareSetup();
double Interpolate(double voltage);
double RunningAverage(double a, double instData, double buffData);
bool HysteresisDigital(bool currentStatus, double x, double ONthreshold, double OFFthreshold);
bool HysteresisAnalog(); // Needs Work!!

//Function Prototypes:
void DisableInput1();
void DisableInput2();
void DisableInput3();


void HardwareSetup()
{
  //Pin Setup:
  pinMode(PIN_INPUT_1, INPUT);
  pinMode(PIN_INPUT_1_PULLUP, OUTPUT); digitalWrite(PIN_INPUT_1_PULLUP, Input_1_Pullup_Enabled);
  pinMode(PIN_INPUT_1_PULLDOWN, OUTPUT); digitalWrite(PIN_INPUT_1_PULLDOWN, Input_1_Pulldown_Enabled);
  pinMode(PIN_INPUT_1_5V, OUTPUT); digitalWrite(PIN_INPUT_1_5V, Input_1_5V_Enabled);
  
  pinMode(PIN_INPUT_2, INPUT);
  pinMode(PIN_INPUT_2_PULLUP, OUTPUT); digitalWrite(PIN_INPUT_2_PULLUP, Input_2_Pullup_Enabled);
  pinMode(PIN_INPUT_2_PULLDOWN, OUTPUT); digitalWrite(PIN_INPUT_2_PULLDOWN, Input_2_Pulldown_Enabled);

  pinMode(PIN_INPUT_3, INPUT);
  pinMode(PIN_INPUT_3_PULLUP, OUTPUT); digitalWrite(PIN_INPUT_3_PULLUP, Input_3_Pullup_Enabled);
  pinMode(PIN_INPUT_3_PULLDOWN, OUTPUT); digitalWrite(PIN_INPUT_3_PULLDOWN, Input_3_Pulldown_Enabled);

  pinMode(PIN_OUTPUT_1, OUTPUT); digitalWrite(PIN_OUTPUT_1, Input_1_Digital);
  pinMode(PIN_OUTPUT_2, OUTPUT); digitalWrite(PIN_OUTPUT_2, Input_2_Digital);
  pinMode(PIN_OUTPUT_3, OUTPUT); digitalWrite(PIN_OUTPUT_3, Input_3_Digital);
  
  pinMode(PIN_LED_RED, OUTPUT); digitalWrite(PIN_LED_RED, LED_Red_Status);
  pinMode(PIN_LED_GREEN, OUTPUT); digitalWrite(PIN_LED_GREEN, LED_Green_Status);

  pinMode(PIN_CAN_CS, OUTPUT);
  pinMode(PIN_CAN_TERM, OUTPUT); digitalWrite(PIN_CAN_TERM, !CAN_TermRes_Enabled);

  //Timer Setup
  cli(); //clear interrupts
  //set timer0 interrupt at 100Hz
  TCCR0A = 0;// set entire TCCR0A register to 0
  TCCR0B = 0;// same for TCCR0B
  TCNT0  = 0;//initialize counter value to 0
  // set compare match register for 100hz increments
  OCR0A = 155;// = (16*10^6) / (100*1024) - 1 (must be <256)
  // turn on CTC mode
  TCCR0A |= (1 << WGM01);
  // Set CS01 and CS00 bits for 1024 prescaler
  TCCR0B |= (1 << CS02) | (1 << CS00);
  // enable timer compare interrupt
  TIMSK0 |= (1 << OCIE0A);
  sei(); //allow interrupts

  //Read EEPROM Pin Config:
  GetSettingsEEPROM();
  
}

void EnableInput1Pullup()
{
  Input_1_Mode = 1;
  Input_1_5V_Enabled = false;       digitalWrite(PIN_INPUT_1_5V, Input_1_5V_Enabled);
  Input_1_Pulldown_Enabled = false; digitalWrite(PIN_INPUT_1_PULLDOWN, Input_1_Pulldown_Enabled); 
  Input_1_Pullup_Enabled = true;    digitalWrite(PIN_INPUT_1_PULLUP, Input_1_Pullup_Enabled); 

  EEPROM.update(ADDR_Input_1_5V_Enabled, Input_1_5V_Enabled);
  EEPROM.update(ADDR_Input_1_Pulldown_Enabled, Input_1_Pulldown_Enabled);
  EEPROM.update(ADDR_Input_1_Pullup_Enabled, Input_1_Pullup_Enabled);
}

void DisableInput1Pullup()
{
  Input_1_Pullup_Enabled = false;   digitalWrite(PIN_INPUT_1_PULLUP, Input_1_Pullup_Enabled); 
  EEPROM.update(ADDR_Input_1_Pullup_Enabled, Input_1_Pullup_Enabled);
}

void EnableInput1Pulldown()
{
  Input_1_Mode = 2;
  Input_1_5V_Enabled = false;       digitalWrite(PIN_INPUT_1_5V, Input_1_5V_Enabled); 
  Input_1_Pullup_Enabled = false;   digitalWrite(PIN_INPUT_1_PULLUP, Input_1_Pullup_Enabled); 
  Input_1_Pulldown_Enabled = true;  digitalWrite(PIN_INPUT_1_PULLDOWN, Input_1_Pulldown_Enabled);

  EEPROM.update(ADDR_Input_1_5V_Enabled, Input_1_5V_Enabled);
  EEPROM.update(ADDR_Input_1_Pullup_Enabled, Input_1_Pullup_Enabled);
  EEPROM.update(ADDR_Input_1_Pulldown_Enabled, Input_1_Pulldown_Enabled);
}

void DisableInput1Pulldown()
{
  Input_1_Pulldown_Enabled = false; digitalWrite(PIN_INPUT_1_PULLDOWN, Input_1_Pulldown_Enabled); 
  EEPROM.update(ADDR_Input_1_Pulldown_Enabled, Input_1_Pulldown_Enabled);
}
void Enable5VSupply()
{
  Input_1_Mode = 9;
  Input_1_Pullup_Enabled = false;   digitalWrite(PIN_INPUT_1_PULLUP, Input_1_Pullup_Enabled); 
  Input_1_Pulldown_Enabled = false; digitalWrite(PIN_INPUT_1_PULLDOWN, Input_1_Pulldown_Enabled); 
  Input_1_5V_Enabled = true;        digitalWrite(PIN_INPUT_1_5V, Input_1_5V_Enabled); 

  EEPROM.update(ADDR_Input_1_5V_Enabled, Input_1_5V_Enabled);
  EEPROM.update(ADDR_Input_1_Pulldown_Enabled, Input_1_Pulldown_Enabled);
  EEPROM.update(ADDR_Input_1_Pullup_Enabled, Input_1_Pullup_Enabled);
}

void Disable5VSupply()
{
  Input_1_5V_Enabled = false;       digitalWrite(PIN_INPUT_1_5V, Input_1_5V_Enabled); 
  EEPROM.update(ADDR_Input_1_5V_Enabled, Input_1_5V_Enabled);
}

void DisableInput1Switches()
{
  DisableInput1Pullup();
  DisableInput1Pulldown();
  Disable5VSupply();
  DisableInput1();
}

bool ReadInput1Digital(bool invert)
{
  if(Input_1_Pullup_Enabled) Input_1_Mode = 7;
  else if (Input_1_Pulldown_Enabled) Input_1_Mode = 8;
  else Input_1_Mode = 6;

  Input_1_Invert = invert;
  EEPROM.update(ADDR_Input_1_Invert, Input_1_Invert);

  if(invert) return (!digitalRead(PIN_INPUT_1));
  else return digitalRead(PIN_INPUT_1);
}

double ReadInput1Analog(double smoothing)
{
  if(Input_1_Pullup_Enabled) Input_1_Mode = 4;
  else if (Input_1_Pulldown_Enabled) Input_1_Mode = 5;
  else Input_1_Mode = 3;

  if(smoothing > 0) 
  {
    if(smoothing < 0) smoothing = 0;
    if(smoothing > 100) smoothing = 100;
    Input_1_Smoothing_Enabled = true;
    EEPROM.update(ADDR_Input_1_Smoothing_Enabled, Input_1_Smoothing_Enabled);
    EEPROM.update(ADDR_Input_1_Smoothing, smoothing);
    double tempSmoothing = ((-0.0018 * smoothing) + 0.2);
    return RunningAverage(tempSmoothing, (analogRead(PIN_INPUT_1) * 5.0 / 1023.0), Input_1_Voltage);
  }
  else 
  {
    Input_1_Smoothing_Enabled = false;
    EEPROM.update(ADDR_Input_1_Smoothing_Enabled, Input_1_Smoothing_Enabled);
    EEPROM.update(ADDR_Input_1_Smoothing, 0);
    return (analogRead(PIN_INPUT_1) * 5.0 / 1023.0);  
  }
}

void DisableInput1()
{
  Input_1_Mode = 0;
}




void EnableInput2Pullup()
{
  Input_2_Mode = 1;
  Input_2_Pulldown_Enabled = false; digitalWrite(PIN_INPUT_2_PULLDOWN, Input_2_Pulldown_Enabled);
  Input_2_Pullup_Enabled = true;    digitalWrite(PIN_INPUT_2_PULLUP, Input_2_Pullup_Enabled);

  EEPROM.update(ADDR_Input_2_Pulldown_Enabled, Input_2_Pulldown_Enabled);
  EEPROM.update(ADDR_Input_2_Pullup_Enabled, Input_2_Pullup_Enabled);
}

void DisableInput2Pullup()
{
  Input_2_Pullup_Enabled = false;   digitalWrite(PIN_INPUT_2_PULLUP, Input_2_Pullup_Enabled);
  EEPROM.update(ADDR_Input_2_Pullup_Enabled, Input_2_Pullup_Enabled);
}

void EnableInput2Pulldown()
{
  Input_2_Mode = 2;
  Input_2_Pullup_Enabled = false;   digitalWrite(PIN_INPUT_2_PULLUP, Input_2_Pullup_Enabled);
  Input_2_Pulldown_Enabled = true;  digitalWrite(PIN_INPUT_2_PULLDOWN, Input_2_Pulldown_Enabled);

  EEPROM.update(ADDR_Input_2_Pullup_Enabled, Input_2_Pullup_Enabled);
  EEPROM.update(ADDR_Input_2_Pulldown_Enabled, Input_2_Pulldown_Enabled);
}

void DisableInput2Pulldown()
{
  Input_2_Pulldown_Enabled = false; digitalWrite(PIN_INPUT_2_PULLDOWN, Input_2_Pulldown_Enabled);
  EEPROM.update(ADDR_Input_2_Pulldown_Enabled, Input_2_Pulldown_Enabled);
}

void DisableInput2Switches()
{
  DisableInput2Pullup();
  DisableInput2Pulldown();
  DisableInput2();
}
bool ReadInput2Digital(bool invert)
{
  if(Input_2_Pullup_Enabled) Input_2_Mode = 7;
  else if (Input_2_Pulldown_Enabled) Input_2_Mode = 8;
  else Input_2_Mode = 6;

  Input_2_Invert = invert;
  EEPROM.update(ADDR_Input_2_Invert, Input_2_Invert);

  if(invert) return (!digitalRead(PIN_INPUT_2));
  else return digitalRead(PIN_INPUT_2);
  
}

double ReadInput2Analog(double smoothing)
{
  if(Input_2_Pullup_Enabled) Input_2_Mode = 4;
  else if (Input_2_Pulldown_Enabled) Input_2_Mode = 5;
  else Input_2_Mode = 3;

  if(smoothing > 0) 
  {
    if(smoothing < 0) smoothing = 0;
    if(smoothing > 100) smoothing = 100;
    Input_2_Smoothing_Enabled = true;
    EEPROM.update(ADDR_Input_2_Smoothing_Enabled, Input_2_Smoothing_Enabled);
    EEPROM.update(ADDR_Input_2_Smoothing, smoothing);
    double tempSmoothing = ((-0.0018 * smoothing) + 0.2);
    return RunningAverage(tempSmoothing, (analogRead(PIN_INPUT_2) * 5.0 / 1023.0), Input_2_Voltage);
  }
  else 
  {
    Input_2_Smoothing_Enabled = false;
    EEPROM.update(ADDR_Input_2_Smoothing_Enabled, Input_2_Smoothing_Enabled);
    EEPROM.update(ADDR_Input_2_Smoothing, 0);
    return (analogRead(PIN_INPUT_2) * 5.0 / 1023.0);  
  } 
}

void DisableInput2()
{
  Input_2_Mode = 0;
}




void EnableInput3Pullup()
{
  Input_3_Mode = 1;
  Input_3_Pulldown_Enabled = false;  digitalWrite(PIN_INPUT_3_PULLDOWN, Input_3_Pulldown_Enabled);
  Input_3_Pullup_Enabled = true;     digitalWrite(PIN_INPUT_3_PULLUP, Input_3_Pullup_Enabled);

  EEPROM.update(ADDR_Input_3_Pulldown_Enabled, Input_3_Pulldown_Enabled);
  EEPROM.update(ADDR_Input_3_Pullup_Enabled, Input_3_Pullup_Enabled);
}

void DisableInput3Pullup()
{
  Input_3_Pullup_Enabled = false;    digitalWrite(PIN_INPUT_3_PULLUP, Input_3_Pullup_Enabled);
  EEPROM.update(ADDR_Input_3_Pullup_Enabled, Input_3_Pullup_Enabled);
}

void EnableInput3Pulldown()
{
  Input_3_Mode = 2;
  Input_3_Pullup_Enabled = false;    digitalWrite(PIN_INPUT_3_PULLUP, Input_3_Pullup_Enabled);
  Input_3_Pulldown_Enabled = true;   digitalWrite(PIN_INPUT_3_PULLDOWN, Input_3_Pulldown_Enabled);

  EEPROM.update(ADDR_Input_3_Pullup_Enabled, Input_3_Pullup_Enabled);
  EEPROM.update(ADDR_Input_3_Pulldown_Enabled, Input_3_Pulldown_Enabled);
}

void DisableInput3Pulldown()
{
  Input_3_Pulldown_Enabled = false;   digitalWrite(PIN_INPUT_3_PULLDOWN, Input_3_Pulldown_Enabled);
  EEPROM.update(ADDR_Input_3_Pulldown_Enabled, Input_3_Pulldown_Enabled);
}

void DisableInput3Switches()
{
  DisableInput3Pullup();
  DisableInput3Pulldown();
  DisableInput3();
}

bool ReadInput3Digital(bool invert)
{
  if(Input_3_Pullup_Enabled) Input_3_Mode = 7;
  else if (Input_3_Pulldown_Enabled) Input_3_Mode = 8;
  else Input_3_Mode = 6;

  Input_3_Invert = invert;
  EEPROM.update(ADDR_Input_3_Invert, Input_3_Invert);
  
  if(invert) return (!digitalRead(PIN_INPUT_3));
  else return digitalRead(PIN_INPUT_3);
}

double ReadInput3Analog(double smoothing)
{
  if(Input_3_Pullup_Enabled) Input_3_Mode = 4;
  else if (Input_3_Pulldown_Enabled) Input_3_Mode = 5;
  else Input_3_Mode = 3;

  if(smoothing > 0) 
  {
    if(smoothing < 0) smoothing = 0;
    if(smoothing > 100) smoothing = 100;
    Input_3_Smoothing_Enabled = true;
    EEPROM.update(ADDR_Input_3_Smoothing_Enabled, Input_3_Smoothing_Enabled);
    EEPROM.update(ADDR_Input_3_Smoothing, smoothing);
    double tempSmoothing = ((-0.0018 * smoothing) + 0.2);
    return RunningAverage(tempSmoothing, (analogRead(PIN_INPUT_3) * 5.0 / 1023.0), Input_3_Voltage);
  }
  else 
  {
    Input_3_Smoothing_Enabled = false;
    EEPROM.update(ADDR_Input_3_Smoothing_Enabled, Input_3_Smoothing_Enabled);
    EEPROM.update(ADDR_Input_3_Smoothing, 0);
    return (analogRead(PIN_INPUT_3) * 5.0 / 1023.0);  
  } 
}

void DisableInput3()
{
  Input_3_Mode = 0;
}




void EnableGreenLED()
{
  LED_Green_Status = true;            digitalWrite(PIN_LED_GREEN, LED_Green_Status);
}

void DisableGreenLED()
{
  LED_Green_Status = false;           digitalWrite(PIN_LED_GREEN, LED_Green_Status);
}

void EnableRedLED()
{
  LED_Red_Status = true;               digitalWrite(PIN_LED_RED, LED_Red_Status);
}

void DisableRedLED()
{
  LED_Red_Status = false;              digitalWrite(PIN_LED_RED, LED_Red_Status);
}

void EnableOutput1Digital()
{
  Output_1_Mode = 2;
  Output_1_Digital = true;
  digitalWrite(PIN_OUTPUT_1, Output_1_Digital);
  
}

void DisableOutput1Digital()
{
  Output_1_Digital = false;
  digitalWrite(PIN_OUTPUT_1, Output_1_Digital);
}

void DisableOutput1()
{
  Output_1_Mode = 0;
  Output_1_Duty = 0;
  digitalWrite(PIN_OUTPUT_1, LOW);
}

void EnableOutput2Digital()
{
  Output_2_Mode = 2;
  Output_2_Digital = true;
  digitalWrite(PIN_OUTPUT_2, Output_2_Digital);
}

void DisableOutput2Digital()
{
  Output_2_Digital = false;
  digitalWrite(PIN_OUTPUT_2, Output_2_Digital);
}

void DisableOutput2()
{
  Output_2_Mode = 0;
  Output_2_Duty = 0;
  digitalWrite(PIN_OUTPUT_2, LOW);
}

void EnableOutput3Digital()
{
  Output_3_Mode = 2;
  Output_3_Digital = true;
  digitalWrite(PIN_OUTPUT_3, Output_3_Digital);
}

void DisableOutput3Digital()
{
  Output_3_Digital = false;
  digitalWrite(PIN_OUTPUT_3, Output_3_Digital);
}

void DisableOutput3()
{
  Output_3_Mode = 0;
  Output_3_Duty = 0;
  digitalWrite(PIN_OUTPUT_3, LOW);
}




void SetupPWM10Hz()
{
  // TIMER 1 for interrupt frequency 1000 Hz:
  cli(); // stop interrupts
  TCCR1A = 0; // set entire TCCR1A register to 0
  TCCR1B = 0; // same for TCCR1B
  TCNT1  = 0; // initialize counter value to 0
  // set compare match register for 1000 Hz increments
  OCR1A = 15999; // = 16000000 / (1 * 1000) - 1 (must be <65536)
  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set CS12, CS11 and CS10 bits for 1 prescaler
  TCCR1B |= (0 << CS12) | (0 << CS11) | (1 << CS10);
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);
  sei(); // allow interrupts  

  Output_1_PWMFreq = 10;
  Output_2_PWMFreq = 10;
  Output_3_PWMFreq = 10;
}

void SetupPWM50Hz()
{
  // TIMER 1 for interrupt frequency 5000 Hz:
  cli(); // stop interrupts
  TCCR1A = 0; // set entire TCCR1A register to 0
  TCCR1B = 0; // same for TCCR1B
  TCNT1  = 0; // initialize counter value to 0
  // set compare match register for 5000 Hz increments
  OCR1A = 3199; // = 16000000 / (1 * 5000) - 1 (must be <65536)
  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set CS12, CS11 and CS10 bits for 1 prescaler
  TCCR1B |= (0 << CS12) | (0 << CS11) | (1 << CS10);
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);
  sei(); // allow interrupts

  Output_1_PWMFreq = 50;
  Output_2_PWMFreq = 50;
  Output_3_PWMFreq = 50;
}

void SetupPWM100Hz()
{
  // TIMER 1 for interrupt frequency 10000 Hz:
  cli(); // stop interrupts
  TCCR1A = 0; // set entire TCCR1A register to 0
  TCCR1B = 0; // same for TCCR1B
  TCNT1  = 0; // initialize counter value to 0
  // set compare match register for 10000 Hz increments
  OCR1A = 1599; // = 16000000 / (1 * 10000) - 1 (must be <65536)
  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set CS12, CS11 and CS10 bits for 1 prescaler
  TCCR1B |= (0 << CS12) | (0 << CS11) | (1 << CS10);
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);
  sei(); // allow interrupts

  Output_1_PWMFreq = 100;
  Output_2_PWMFreq = 100;
  Output_3_PWMFreq = 100;
}

ISR(TIMER0_COMPA_vect) //100Hz Interrupt Timer0 - 10ms
{
  TimerCounter++;
  Flag10ms = true;
  if(!(TimerCounter % 2)) Flag20ms = true;
  if(!(TimerCounter % 5)) Flag50ms = true;
  if(!(TimerCounter % 10)) Flag100ms = true;
  if(!(TimerCounter % 50)) Flag500ms = true;
  if(!(TimerCounter % 100)) Flag1000ms = true;

  if(TimerCounter > 50000) TimerCounter = 0;
}

double Interpolate(double voltage)
{
    double x_axis[] = { 0.25,  0.50, 1.00, 1.50, 2.00, 3.00, 3.50, 4.00, 4.25, 4.50, 4.75};
    double y_axis[] =  {140, 120, 110, 100,  90,  70,  15,  10,   0, -10, -20};
    int numDataPoints = 11;
    
    if(voltage <= x_axis[0]) return y_axis[0];

    if(voltage >= x_axis[numDataPoints-1]) return y_axis[numDataPoints-1];

    uint8_t pos = 1;
    while(voltage > x_axis[pos]) pos++;

    if(voltage == x_axis[pos]) return y_axis[pos];

    return (voltage-x_axis[pos-1]) * (y_axis[pos]-y_axis[pos-1]) /
            (x_axis[pos] - x_axis[pos-1]) + y_axis[pos-1];
}

double RunningAverage(double a, double instData, double buffData)
{
  //'a' can range from 0.0 to 1.0
  //Larger values of 'a' ( >0.2 ) cause the readings to be less buffered,
  return (a * instData) + ((1.0 - a) * buffData);
}

bool HysteresisDigital(bool currentStatus, double x, double ONthreshold, double OFFthreshold)
{
  if(currentStatus)
  {
    if(x <= OFFthreshold) return false;
  }
  else
  {
    if(x >= ONthreshold) return true;
  }
}

bool HysteresisAnalog()
{
  //Needs Work
  return false;
}

#endif
