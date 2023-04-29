//KaizenRelaySERIAL.h
//Version 2.0 - 2021 November 22
//CANtrolls, LLC. - Vadim Belogorodsky
//QT Kaizen Relay Manager V0

#ifndef KAIZENRELAY_SERIAL_H
#define KAIZENRELAY_SERIAL_H

#include "KaizenRelay.h"

//Global Variables: Serial
String SerialInput = ""; 
String SerialIndex = ""; 
String SerialData = "";
byte USB_Counter = 0;


//Function Prototypes:
void SendHWStatusUSB();
void ReadHWStatusUSB();

void SendHWStatusUSB()
{
  if(USB_Counter == 0)
  {
    Serial.print("10:"); Serial.print(Input_1_Mode); Serial.println(";");
    Serial.print("11:"); Serial.print(Input_1_Pullup_Enabled); Serial.println(";");
    Serial.print("12:"); Serial.print(Input_1_Pulldown_Enabled); Serial.println(";");  
    Serial.print("13:"); Serial.print(Input_1_5V_Enabled); Serial.println(";");
    Serial.print("14:"); Serial.print(Input_1_Voltage); Serial.println(";");
  }

  if(USB_Counter == 1)
  { 
    Serial.print("15:"); Serial.print(Input_1_Digital); Serial.println(";");
    Serial.print("16:"); Serial.print(Input_1_Smoothing_Enabled); Serial.println(";");
    Serial.print("17:"); Serial.print(Input_1_Smoothing); Serial.println(";");
    Serial.print("18:"); Serial.print(Input_1_Invert); Serial.println(";");
    //Serial.print("19:"); Serial.print(""); Serial.println(";");
  }

  if(USB_Counter == 2)
  {
    Serial.print("20:"); Serial.print(Input_2_Mode); Serial.println(";");
    Serial.print("21:"); Serial.print(Input_2_Pullup_Enabled); Serial.println(";");
    Serial.print("22:"); Serial.print(Input_2_Pulldown_Enabled); Serial.println(";");
    Serial.print("23:"); Serial.print(Input_2_Voltage); Serial.println(";");
    Serial.print("24:"); Serial.print(Input_2_Digital); Serial.println(";");    
  }

  if(USB_Counter == 3)
  {  
    Serial.print("25:"); Serial.print(Input_2_Smoothing_Enabled); Serial.println(";");
    Serial.print("26:"); Serial.print(Input_2_Smoothing); Serial.println(";");
    Serial.print("27:"); Serial.print(Input_2_Invert); Serial.println(";");
    //Serial.print("28:"); Serial.print(""); Serial.println(";");
    //Serial.print("29:"); Serial.print(""); Serial.println(";");
  }

  if(USB_Counter == 4)
  {
    Serial.print("30:"); Serial.print(Input_3_Mode); Serial.println(";");
    Serial.print("31:"); Serial.print(Input_3_Pullup_Enabled); Serial.println(";");
    Serial.print("32:"); Serial.print(Input_3_Pulldown_Enabled); Serial.println(";");
    Serial.print("33:"); Serial.print(Input_3_Voltage); Serial.println(";");
    Serial.print("34:"); Serial.print(Input_3_Digital); Serial.println(";");
  }

  if(USB_Counter == 5)
  {
    Serial.print("35:"); Serial.print(Input_3_Smoothing_Enabled); Serial.println(";");
    Serial.print("36:"); Serial.print(Input_3_Smoothing); Serial.println(";");
    Serial.print("37:"); Serial.print(Input_3_Invert); Serial.println(";");
    //Serial.print("38:"); Serial.print(""); Serial.println(";");
    //Serial.print("39:"); Serial.print(""); Serial.println(";");
  }
    
  if(USB_Counter == 6)
  {
    Serial.print("40:"); Serial.print(Output_1_Mode); Serial.println(";");
    Serial.print("41:"); Serial.print(Output_1_PWMFreq); Serial.println(";");
    Serial.print("42:"); Serial.print(Output_1_Duty); Serial.println(";");
    Serial.print("43:"); Serial.print(Output_1_Digital); Serial.println(";");
    Serial.print("44:"); Serial.print(Output_1_DigInvert); Serial.println(";");
  }

  if(USB_Counter == 7)
  {
    Serial.print("50:"); Serial.print(Output_2_Mode); Serial.println(";");
    Serial.print("51:"); Serial.print(Output_2_PWMFreq); Serial.println(";");
    Serial.print("52:"); Serial.print(Output_2_Duty); Serial.println(";");
    Serial.print("53:"); Serial.print(Output_2_Digital); Serial.println(";");
    Serial.print("54:"); Serial.print(Output_2_DigInvert); Serial.println(";");
  }

  if(USB_Counter == 8)
  {
    Serial.print("60:"); Serial.print(Output_3_Mode); Serial.println(";");
    Serial.print("61:"); Serial.print(Output_3_PWMFreq); Serial.println(";");
    Serial.print("62:"); Serial.print(Output_3_Duty); Serial.println(";");
    Serial.print("63:"); Serial.print(Output_3_Digital); Serial.println(";");
    Serial.print("64:"); Serial.print(Output_3_DigInvert); Serial.println(";");
  }
  
  if(USB_Counter == 9)
  {
    Serial.print("70:"); Serial.print(LED_Red_Status); Serial.println(";");
    Serial.print("71:"); Serial.print(LED_Green_Status); Serial.println(";");
    Serial.print("72:"); Serial.print(CAN_TermRes_Enabled); Serial.println(";");
    Serial.print("73:"); Serial.print(CAN_BaudRate); Serial.println(";");
  }
  
  USB_Counter++;
  if(USB_Counter > 9) USB_Counter = 0;
}

void ReadHWStatusUSB()
{
  if(SerialIndex == "301")
  {
    EnableGreenLED();
    if(SerialInput.indexOf(":1") > 0)
    {
      for (unsigned int i = 0 ; i < EEPROM.length(); i++) EEPROM.update(i, 0);
    }
  } 
  DisableGreenLED(); 
}

#endif
