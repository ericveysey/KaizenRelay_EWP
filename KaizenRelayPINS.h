//KaizenRelayPINS.h
//Version 1.0 - 2021 January 2
//CANtrolls, LLC. - Vadim Belogorodsky
//KaizenRelay Control Module PCB V3

#ifndef KAIZENRELAY_PINS_H
#define KAIZENRELAY_PINS_H

//Microcontroller Pin Assignments
//Input Pin 1
#define PIN_INPUT_1             A0
#define PIN_INPUT_1_PULLUP      10
#define PIN_INPUT_1_PULLDOWN    6
#define PIN_INPUT_1_5V          8

//Input Pin 2
#define PIN_INPUT_2             A2  
#define PIN_INPUT_2_PULLUP      A1
#define PIN_INPUT_2_PULLDOWN    12

//Input Pin 3
#define PIN_INPUT_3             A3          
#define PIN_INPUT_3_PULLUP      A4
#define PIN_INPUT_3_PULLDOWN    4

//Output Pins
#define PIN_OUTPUT_1            9  //PB5
#define PIN_OUTPUT_2            13 //PC7
#define PIN_OUTPUT_3            5  //PC6

//LED Pins
#define PIN_LED_RED             3 //PD0
#define PIN_LED_GREEN           2 //PD1

//CANbus Stuff:
#define PIN_CAN_CS              0
#define PIN_CAN_TERM            A5

#endif
