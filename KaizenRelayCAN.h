//KaizenRelayCAN.h
//Version 2.0 - 2021 November 9
//CANtrolls, LLC. - Vadim Belogorodsky

#ifndef KAIZENRELAY_CAN_H
#define KAIZENRELAY_CAN_H

#include "KaizenRelay.h"
#include "KaizenRelayEEPROM.h"

#include "mcp_can.h"

MCP_CAN CAN_(PIN_CAN_CS);

//Function Prototypes:
void SetupCAN_125kbps();
void SetupCAN_250kbps();
void SetupCAN_500kbps();
void SetupCAN_1000kbps();

void CANListenMsg();

void SendHWStatusCAN();

void SetupCAN_125kbps() {
  CAN_BaudRate = 125;

  //Start CAN Network at 125kbps Baudrate
  while (CAN_OK != CAN_.begin(CAN_125KBPS)) delay(100);

  //Clear CAN Read Buffer
  for (unsigned short i = 0; i < 8; i++) CAN_Read_Msg[i] = 0x00;
}

void SetupCAN_250kbps() {
  CAN_BaudRate = 250;

  //Start CAN Network at 250kbps Baudrate
  while (CAN_OK != CAN_.begin(CAN_250KBPS)) delay(100);

  //Clear CAN Read Buffer
  for (unsigned short i = 0; i < 8; i++) CAN_Read_Msg[i] = 0x00;
}

void SetupCAN_500kbps() {
  CAN_BaudRate = 500;

  //Start CAN Network at 500kbps Baudrate
  while (CAN_OK != CAN_.begin(CAN_500KBPS)) delay(100);

  //Clear CAN Read Buffer
  for (unsigned short i = 0; i < 8; i++) CAN_Read_Msg[i] = 0x00;
}

void SetupCAN_1000kbps() {
  CAN_BaudRate = 1000;

  //Start CAN Network at 1000kbps Baudrate
  while (CAN_OK != CAN_.begin(CAN_1000KBPS)) delay(100);

  //Clear CAN Read Buffer
  for (unsigned short i = 0; i < 8; i++) CAN_Read_Msg[i] = 0x00;
}

void EnableCANTermResistor() {
  CAN_TermRes_Enabled = true;
  digitalWrite(PIN_CAN_TERM, !CAN_TermRes_Enabled);
  EEPROM.update(ADDR_CAN_TermRes_Enabled, CAN_TermRes_Enabled);
}

void DisableCANTermResistor() {
  CAN_TermRes_Enabled = false;
  digitalWrite(PIN_CAN_TERM, !CAN_TermRes_Enabled);
  EEPROM.update(ADDR_CAN_TermRes_Enabled, CAN_TermRes_Enabled);
}

void SendHWStatusCAN() {
  if (CAN_Msg_Counter == 0) {
    if ((Output_1_Duty > 0) && (Output_2_Duty > 0)) CAN_Status_Msg_1[0] = (CAN_Status_Msg_1[0] | 0x01);
    else CAN_Status_Msg_1[0] = (CAN_Status_Msg_1[0] & 0x00);
    CAN_Status_Msg_1[1] = 0x64;
    CAN_Status_Msg_1[2] = ECT;
    CAN_Status_Msg_1[3] = Output_1_Duty;
    CAN_Status_Msg_1[4] = EWPTimer;
    CAN_Status_Msg_1[5] = 0xFF;
    CAN_Status_Msg_1[6] = 0xFF;
    CAN_Status_Msg_1[7] = 0xFF;

    CAN_.sendMsgBuf(Syvecs_Base_AddressTx + CAN_Msg_Counter, 0, 8, CAN_Status_Msg_1);
  }

  CAN_Msg_Counter = 0;
}


#endif
