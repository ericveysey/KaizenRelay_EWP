//KaizenRelayVARIABLES.h
//Version 2.0 - 2021 December 29
//CANtrolls, LLC. - Vadim Belogorodsky

#ifndef KAIZENRELAY_VARIABLES_H
#define KAIZENRELAY_VARIABLES_H

//Global Variables: Inputs
bool Input_1_Pullup_Enabled = false;
bool Input_1_Pulldown_Enabled = false;
bool Input_1_5V_Enabled = false;
double Input_1_Voltage = 0.00;
bool Input_1_Smoothing_Enabled = false;
byte Input_1_Smoothing = 0;
bool Input_1_Digital = false;
bool Input_1_Invert = false;
byte Input_1_Mode = 0; //0 = Off, 1 = Analog Input, 2 = Digital Input, 3 = 5V Enabled 
byte Input_1_Cmd = 0; //0 = Off, 1 = Analog Input, 2 = Digital Input, 3 = 5V Enabled   

bool Input_2_Pullup_Enabled = false;
bool Input_2_Pulldown_Enabled = false;
double Input_2_Voltage = 0.00;
bool Input_2_Smoothing_Enabled = false;
byte Input_2_Smoothing = 0;
bool Input_2_Digital = false;
bool Input_2_Invert = false;
byte Input_2_Mode = 0; //0 = Off, 1 = Analog Input, 2 = Digital Input 
byte Input_2_Cmd = 0; //0 = Off, 1 = Analog Input, 2 = Digital Input

bool Input_3_Pullup_Enabled = false;
bool Input_3_Pulldown_Enabled = false;
double Input_3_Voltage = 0.00;
bool Input_3_Smoothing_Enabled = false;
byte Input_3_Smoothing = 0.00;
bool Input_3_Digital = false;
bool Input_3_Invert = false;
byte Input_3_Mode = 0; //0 = Off, 1 = Analog Input, 2 = Digital Input
byte Input_3_Cmd = 0; //0 = Off, 1 = Analog Input, 2 = Digital Input

//Global Variables: Outputs
byte PWMpulseCounter = 0;

byte Output_1_Mode = 0; //0 = Unused, 1 = PWM, 2 = Digital
byte Output_1_Cmd = 0;  //0 = Unused, 1 = PWM, 2 = Digital
byte Output_1_BasedOn = 0; //0 = No Input, 1 = Input 1, 2 = Input 2, 3 = Input 3, 4 = CAN
unsigned short Output_1_PWMFreq = 0;
bool Output_1_AnaInvert = false;
bool Output_1_AnaHys = false;
byte Output_1_Duty = 0;
bool Output_1_DigInvert = false;
bool Output_1_DigHys = false;
double Output_1_OnAt = 0.00;
double Output_1_OffAt = 0.00;
bool Output_1_Digital = false;

byte Output_2_Mode = 0; //0 = Unused, 1 = PWM, 2 = Digital
byte Output_2_Cmd = 0;  //0 = Unused, 1 = PWM, 2 = Digital
byte Output_2_BasedOn = 0; //0 = No Input, 1 = Input 1, 2 = Input 2, 3 = Input 3, 4 = CAN
unsigned short Output_2_PWMFreq = 0;
bool Output_2_AnaInvert = false;
bool Output_2_AnaHys = false;
byte Output_2_Duty = 0;
bool Output_2_DigInvert = false;
bool Output_2_DigHys = false;
double Output_2_OnAt = 0.00;
double Output_2_OffAt = 0.00;
bool Output_2_Digital = false;

byte Output_3_Mode = 0; //0 = Unused, 1 = PWM, 2 = Digital
byte Output_3_Cmd = 0;  //0 = Unused, 1 = PWM, 2 = Digital
byte Output_3_BasedOn = 0; //0 = No Input, 1 = Input 1, 2 = Input 2, 3 = Input 3, 4 = CAN
unsigned short Output_3_PWMFreq = 0;
bool Output_3_AnaInvert = false;
bool Output_3_AnaHys = false;
byte Output_3_Duty = 0;
bool Output_3_DigInvert = false;
bool Output_3_DigHys = false;
double Output_3_OnAt = 0.00;
double Output_3_OffAt = 0.00;
bool Output_3_Digital = false;

//Misc. Outputs
bool hysFlag = false;

//CANbus 
unsigned char CAN_Read_Msg[8];
unsigned char CAN_Read_Len = 0;
unsigned long CAN_Read_ID = 0;
bool CAN_TermRes_Enabled = false;
unsigned char CAN_Status_Msg_1[8] = {0, 0, 0, 0, 0, 0, 0, 0};
unsigned char CAN_Status_Msg_2[8] = {0, 0, 0, 0, 0, 0, 0, 0};
unsigned char CAN_Status_Msg_3[8] = {0, 0, 0, 0, 0, 0, 0, 0};
unsigned char CAN_Status_Msg_4[8] = {0, 0, 0, 0, 0, 0, 0, 0};
unsigned char CAN_Status_Msg_5[8] = {0, 0, 0, 0, 0, 0, 0, 0};
unsigned char CAN_Status_Msg_6[8] = {0, 0, 0, 0, 0, 0, 0, 0};
unsigned char CAN_Status_Msg_7[8] = {0, 0, 0, 0, 0, 0, 0, 0};
unsigned int CAN_Command_Msg_ID = 0x73A;
unsigned int CAN_BaudRate = 1000;
unsigned int CAN_MissedMsgs = 0;
bool CAN_Timeout = false;
unsigned long Syvecs_Base_AddressRx = 0x616;
unsigned long Syvecs_Base_AddressTx = 0x625;
unsigned char CAN_Msg_Counter = 0;
double ECT = 0.00;
double EWPDuty = 0;
int EWPTimer = 0;

//Global Variables: LEDs
bool LED_Green_Status = false;
bool LED_Red_Status = false;

//Global Variables: Timers
unsigned int TimerCounter = 0;
bool Flag10ms = false;
bool Flag20ms = false;
bool Flag50ms = false;
bool Flag100ms = false;
bool Flag500ms = false;
bool Flag1000ms = false;

#endif
