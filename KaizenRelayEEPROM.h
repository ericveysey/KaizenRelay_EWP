//KaizenRelayEEPROM.h
//Version 2.0 - 2021 November 22
//CANtrolls, LLC. - Vadim Belogorodsky

#ifndef KAIZENRELAY_EEPROM_H
#define KAIZENRELAY_EEPROM_H

#include "KaizenRelay.h"

#include <EEPROM.h>

//EEPROM Memory Addresses
#define ADDR_Input_1_Mode 100               //byte - 1 byte
#define ADDR_Input_1_Pullup_Enabled 101     //bool - 1 bit, requires 1 byte
#define ADDR_Input_1_Pulldown_Enabled 102   //bool - 1 bit, requires 1 byte
#define ADDR_Input_1_5V_Enabled 103         //bool - 1 bit, requires 1 byte
#define ADDR_Input_1_Smoothing_Enabled 104  //bool - 1 bit, requires 1 byte
#define ADDR_Input_1_Smoothing 105          //byte - 1 byte
#define ADDR_Input_1_Invert 106             //bool - 1 bit, requires 1 byte

#define ADDR_Input_2_Mode 110               //byte - 1 byte
#define ADDR_Input_2_Pullup_Enabled 111     //bool - 1 bit, requires 1 byte
#define ADDR_Input_2_Pulldown_Enabled 112   //bool - 1 bit, requires 1 byte
#define ADDR_Input_2_Smoothing_Enabled 113  //bool - 1 bit, requires 1 byte
#define ADDR_Input_2_Smoothing 114          //byte - 1 byte
#define ADDR_Input_2_Invert 115             //bool - 1 bit, requires 1 byte

#define ADDR_Input_3_Mode 120               //byte - 1 byte
#define ADDR_Input_3_Pullup_Enabled 121     //bool - 1 bit, requires 1 byte
#define ADDR_Input_3_Pulldown_Enabled 122   //bool - 1 bit, requires 1 bytde
#define ADDR_Input_3_Smoothing_Enabled 123  //bool - 1 bit, requires 1 byte
#define ADDR_Input_3_Smoothing 124          //byte - 1 byte
#define ADDR_Input_3_Invert 125             //bool - 1 bit, requires 1 byte

#define ADDR_Output_1_Mode 130              //byte - 1 byte, 0 = Off, 1 = PWM, 2 = digital
#define ADDR_Output_1_PWMFreq 131           //byte - 2 bytes
#define ADDR_Output_1_DigInvert 133         //bool - 1 bit, requires 1 byte

//#define ADDR_Output_1_BasedOn 139           //byte - 1 byte
//#define ADDR_Output_1_AnaInvert 139         //bool - 1 bit, requires 1 byte
//#define ADDR_Output_1_AnaHys 139            //bool - 1 bit, requies 1 byte
//#define ADDR_Output_1_DigHys 139            //bool - 1 bit, requires 1 byte
//#define ADDR_Output_1_OnAt 139              //byte - 1 byte, ~0.02V resolution
//#define ADDR_Output_1_OffAt 139             //byte - 1 byte, ~0.02V resolution

#define ADDR_Output_2_Mode 140              //byte - 1 byte, 0 = Off, 1 = PWM, 2 = digital
#define ADDR_Output_2_PWMFreq 141           //byte - 2 bytese
#define ADDR_Output_2_DigInvert 143         //bool - 1 bit, requires 1 byte

//#define ADDR_Output_2_BasedOn 149           //byte - 1 byte
//#define ADDR_Output_2_AnaInvert 149         //bool - 1 bit, requires 1 byte
//#define ADDR_Output_2_AnaHys 149            //bool - 1 bit, requies 1 byte
//#define ADDR_Output_2_DigHys 149            //bool - 1 bit, requires 1 byte
//#define ADDR_Output_2_OnAt 149              //byte - 1 byte, ~0.02V resolution
//#define ADDR_Output_2_OffAt 149             //byte - 1 byte, ~0.02V resolution

#define ADDR_Output_3_Mode 150              //byte - 1 byte, 0 = Off, 1 = PWM, 2 = digital
#define ADDR_Output_3_PWMFreq 151           //byte - 2 bytes
#define ADDR_Output_3_DigInvert 153         //bool - 1 bit, requires 1 byte

//#define ADDR_Output_3_BasedOn 159           //byte - 1 byte
//#define ADDR_Output_3_AnaInvert 159         //bool - 1 bit, requires 1 byte
//#define ADDR_Output_3_AnaHys 159            //bool - 1 bit, requies 1 byte
//#define ADDR_Output_3_DigHys 159            //bool - 1 bit, requires 1 byte
//#define ADDR_Output_3_OnAt 159              //byte - 1 byte, ~0.02V resolution
//#define ADDR_Output_3_OffAt 159             //byte - 1 byte, ~0.02V resolution

#define ADDR_CAN_TermRes_Enabled 160        //bool - 1 bit, requires 1 byte
#define ADDR_CAN_BaudRate        161        //byte - 1 byte, 0 = 125kbps, 1 = 250kbps, 2 = 500kbps, 3 = 1mbps

#define ADDR_CAN_Command_Msg_ID 99999


void GetSettingsEEPROM()
{
  //Input 1
  EEPROM.get(ADDR_Input_1_Pullup_Enabled, Input_1_Pullup_Enabled);      
  EEPROM.get(ADDR_Input_1_Pulldown_Enabled, Input_1_Pulldown_Enabled);
  EEPROM.get(ADDR_Input_1_5V_Enabled, Input_1_5V_Enabled);
  EEPROM.get(ADDR_Input_1_Smoothing_Enabled, Input_1_Smoothing_Enabled);
  EEPROM.get(ADDR_Input_1_Smoothing, Input_1_Smoothing);
  EEPROM.get(ADDR_Input_1_Invert, Input_1_Invert);
  EEPROM.get(ADDR_Input_1_Mode, Input_1_Cmd);  

  //Input 2
  EEPROM.get(ADDR_Input_2_Pullup_Enabled, Input_2_Pullup_Enabled);      
  EEPROM.get(ADDR_Input_2_Pulldown_Enabled, Input_2_Pulldown_Enabled);
  EEPROM.get(ADDR_Input_2_Smoothing_Enabled, Input_2_Smoothing_Enabled);
  EEPROM.get(ADDR_Input_2_Smoothing, Input_2_Smoothing);
  EEPROM.get(ADDR_Input_2_Invert, Input_2_Invert);
  EEPROM.get(ADDR_Input_2_Mode, Input_2_Cmd);

  //Input 3
  EEPROM.get(ADDR_Input_3_Pullup_Enabled, Input_3_Pullup_Enabled);      
  EEPROM.get(ADDR_Input_3_Pulldown_Enabled, Input_3_Pulldown_Enabled);
  EEPROM.get(ADDR_Input_3_Smoothing_Enabled, Input_3_Smoothing_Enabled);
  EEPROM.get(ADDR_Input_3_Smoothing, Input_3_Smoothing);
  EEPROM.get(ADDR_Input_3_Invert, Input_3_Invert);
  EEPROM.get(ADDR_Input_3_Mode, Input_3_Cmd);

  //Output 1
  EEPROM.get(ADDR_Output_1_Mode, Output_1_Cmd);
  EEPROM.get(ADDR_Output_1_PWMFreq, Output_1_PWMFreq);
  EEPROM.get(ADDR_Output_1_DigInvert, Output_1_DigInvert);
  //EEPROM.get(ADDR_Output_1_BasedOn, Output_1_BasedOn);
  //EEPROM.get(ADDR_Output_1_AnaInvert, Output_1_AnaInvert);
  //EEPROM.get(ADDR_Output_1_AnaHys, Output_1_AnaHys);
  //EEPROM.get(ADDR_Output_1_DigHys, Output_1_DigHys);
  //EEPROM.get(ADDR_Output_1_OnAt, Output_1_OnAt);
  //EEPROM.get(ADDR_Output_1_OffAt, Output_1_OffAt);

  //Output 2
  EEPROM.get(ADDR_Output_2_Mode, Output_2_Cmd);
  EEPROM.get(ADDR_Output_2_PWMFreq, Output_2_PWMFreq);
  EEPROM.get(ADDR_Output_2_DigInvert, Output_2_DigInvert);
//  EEPROM.get(ADDR_Output_2_BasedOn, Output_2_BasedOn);
//  EEPROM.get(ADDR_Output_2_AnaInvert, Output_2_AnaInvert);
//  EEPROM.get(ADDR_Output_2_AnaHys, Output_2_AnaHys);
//  EEPROM.get(ADDR_Output_2_DigHys, Output_2_DigHys);
//  EEPROM.get(ADDR_Output_2_OnAt, Output_2_OnAt);
//  EEPROM.get(ADDR_Output_2_OffAt, Output_2_OffAt);

  //Output 3
  EEPROM.get(ADDR_Output_3_Mode, Output_3_Cmd);
  EEPROM.get(ADDR_Output_3_PWMFreq, Output_3_PWMFreq);
  EEPROM.get(ADDR_Output_3_DigInvert, Output_3_DigInvert);
  //EEPROM.get(ADDR_Output_3_BasedOn, Output_3_BasedOn);
  //EEPROM.get(ADDR_Output_3_AnaInvert, Output_3_AnaInvert);
  //EEPROM.get(ADDR_Output_3_AnaHys, Output_3_AnaHys);
  //EEPROM.get(ADDR_Output_3_DigHys, Output_3_DigHys);
  //EEPROM.get(ADDR_Output_3_OnAt, Output_3_OnAt);
  //EEPROM.get(ADDR_Output_3_OffAt, Output_3_OffAt);

  //CANbus
  EEPROM.get(ADDR_CAN_TermRes_Enabled, CAN_TermRes_Enabled);
  EEPROM.get(ADDR_CAN_BaudRate, CAN_BaudRate); 
}

#endif
