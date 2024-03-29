//Davies Craig EWP Controller by DrivenByWire.com - Eric Veysey

void EnableGreenLED();
void DisableGreenLED();

void EnableRedLED();
void DisableRedLED();

void OutputZeroDuty();
void Output100Duty();
void OutputEWPDuty();

#include "KaizenRelay.h"

#define UseSyvecsCANRx 1
#define UseSyvecsCANTx 1
//Program Variable Area:


void setup() {
  //Setup Pins and CAN Timer:
  HardwareSetup();

  //Input Pin 1 Setup:
  //Enable5VSupply();
  //Disable5VSupply();
  //EnableInput1Pullup();
  //DisableInput1Pullup();
  //EnableInput1Pulldown();
  //DisableInput1Pulldown();
  DisableInput1Switches();

  //Input Pin 2 Setup:
  //EnableInput2Pullup();
  //DisableInput2Pullup();
  //EnableInput2Pulldown();
  //DisableInput2Pulldown();
  DisableInput2Switches();

  //Input Pin 3 Setup:
  //EnableInput3Pullup();
  //DisableInput3Pullup();
  //EnableInput3Pulldown();
  //DisableInput3Pulldown();
  DisableInput3Switches();

  //Output PWM Setup:
  //SetupPWM10Hz();
  //SetupPWM50Hz();
  SetupPWM100Hz();

  //Output Pin 1 Setup:
  Output_1_Mode = 1;

  //Output Pin 2 Setup:
  Output_2_Mode = 1;

  //Output Pin 3 Setup:
  Output_3_Mode = 0;

  //CAN Baud Rate Setup:
  //SetupCAN_125kbps();
  //SetupCAN_250kbps();
  //SetupCAN_500kbps();
  SetupCAN_1000kbps();

  //CAN Termination Resistor:
  EnableCANTermResistor();
  //DisableCANTermResistor();

  //Setup USB Interface
  Serial.begin(57600);
}

void loop() {
  //Check if CAN Messages are Available
  if (CAN_MSGAVAIL == CAN_.checkReceive()) {
    //Read in CAN Message Length and Data
    CAN_.readMsgBuf(&CAN_Read_Len, CAN_Read_Msg);

    //Read in CAN Message ID
    CAN_Read_ID = CAN_.getCanId();

    // CAN Listen
    if (UseSyvecsCANRx) {
      if (CAN_Read_ID == Syvecs_Base_AddressRx)
        CANListenMsg();
    }
    CAN_MissedMsgs = 0;
  } else CAN_MissedMsgs++;

  CAN_Timeout = (CAN_MissedMsgs > 10000);

  //Variable Overflow Handle
  if (CAN_MissedMsgs > 60000) CAN_MissedMsgs = 11000;

  if (Flag10ms) {
    Timer10ms();
    Flag10ms = false;
  }

  if (Flag20ms) {
    Timer20ms();
    Flag20ms = false;
  }

  if (Flag50ms) {
    Timer50ms();
    Flag50ms = false;
  }

  if (Flag100ms) {
    Timer100ms();
    Flag100ms = false;
  }

  if (Flag500ms) {
    Timer500ms();
    Flag500ms = false;
  }

  if (Flag1000ms) {
    Timer1000ms();
    Flag1000ms = false;
  }
}

void USB_Write() {
  //User Area for USB Writing - Message Beginning "**"
  Serial.print("**");

  //Place Your Required Text Output Here:

  //Message Ending ";"
  Serial.println(";");
}
void Timer10ms() {
  if (UseSyvecsCANTx) SendHWStatusCAN();
}

void Timer20ms() {
}

void Timer50ms() {
  SendHWStatusUSB();
}

void Timer100ms() {
}

void Timer500ms() {
}

void Timer1000ms() {
  USB_Write();

  //Generic CAN Listen
  if (UseSyvecsCANRx) {
    if (CAN_Timeout) {
      //CAN Error
      OutputZeroDuty();
      DisableGreenLED();
      DisableRedLED();
    }
  }
  // Reset EWPTimer if it ever gets out of bounds to zero
  if ((EWPTimer < 0) || (EWPTimer > 60)) {
    EWPTimer = 0;
  }

  //Increment the timer when the car is running and the ECT is under 85c
  if ((ECT <= 85) && (RPM >= 500)) {
    EWPTimer++;
  }
}



ISR(TIMER1_COMPA_vect)  //Timer1 Interrupt
{
  PWMpulseCounter++;
  if (PWMpulseCounter >= 99) PWMpulseCounter = 0;

  if (PWMpulseCounter < Output_1_Duty) PORTB = PORTB | 0b00100000;
  else PORTB = PORTB & 0b11011111;

  if (PWMpulseCounter < Output_2_Duty) PORTC = PORTC | 0b10000000;
  else PORTC = PORTC & 0b01111111;
}


void CANListenMsg() {
  //Read CANBus messages from Syvecs
  if (CAN_Read_ID == (Syvecs_Base_AddressRx)) {
    // Read 16bit ECT CAN Frame
    if ((CAN_Read_Msg[0]) || (CAN_Read_Msg[1])) {
      ECT = ((CAN_Read_Msg[0] * 256) + CAN_Read_Msg[1]) / 10;
    }
    // Read 16bit EWPDuty CAN Frame
    if ((((CAN_Read_Msg[2] * 256) + CAN_Read_Msg[3]) / 81.92) <= 100) {
      EWPDuty = ((CAN_Read_Msg[2] * 256) + CAN_Read_Msg[3]) / 81.92;
    } else {
      //If we can't read the duty, we will operate the pump as a safety precaution
      Output100Duty();
      EWPTimer = 0;
      EnableRedLED();
    }
    // Read 16bit RPM CAN Frame
    if ((CAN_Read_Msg[4]) || (CAN_Read_Msg[5])) {
      RPM = ((CAN_Read_Msg[4] * 256) + CAN_Read_Msg[5]);
    }
    // Read 16bit CAL CAN Frame
    if ((CAN_Read_Msg[6]) || (CAN_Read_Msg[7])) {
      CAL = ((CAN_Read_Msg[6] * 256) + CAN_Read_Msg[7]);
    }


    if ((ECT <= 50) && (EWPTimer <= 9) && (RPM >= 500)) {
      OutputEWPDuty();
      EnableGreenLED();
    } else if ((ECT <= 50) && (EWPTimer == 10) && (RPM >= 500)) {
      OutputZeroDuty();
      DisableGreenLED();
    } else if ((ECT <= 50) && (EWPTimer >= 40) && (RPM >= 500)) {
      EWPTimer = 0;
    }

    if ((ECT >= 51) && (ECT <= 70) && (EWPTimer <= 9) && (RPM >= 500)) {
      OutputEWPDuty();
      EnableGreenLED();
    } else if ((ECT >= 51) && (ECT <= 70) && (EWPTimer == 10) && (RPM >= 500)) {
      OutputZeroDuty();
      DisableGreenLED();
    } else if ((ECT >= 51) && (ECT <= 70) && (EWPTimer >= 20) && (RPM >= 500)) {
      EWPTimer = 0;
    }

    if ((ECT >= 71) && (ECT <= 85) && (EWPTimer <= 5) && (RPM >= 500)) {
      OutputEWPDuty();
      EnableGreenLED();
    } else if ((ECT >= 71) && (ECT <= 85) && (EWPTimer == 6) && (RPM >= 500)) {
      OutputZeroDuty();
      DisableGreenLED();
    } else if ((ECT >= 71) && (ECT <= 85) && (EWPTimer >= 7) && (RPM >= 500)) {
      EWPTimer = 0;
    }

    if (ECT >= 86) {
      OutputEWPDuty();
      EnableGreenLED();
      EWPTimer = 0;
    }

    if ((CAL == 12) && (RPM == 0)) {
      Output100Duty();
      EnableGreenLED();
    }

    if ((CAL != 12) && (RPM == 0) && (ECT <= 85)) {
      OutputZeroDuty();
      DisableGreenLED();
    }
  }
}

void OutputZeroDuty() {

  Output_1_Duty = 0;
  Output_2_Duty = 0;
}

void Output100Duty() {

  Output_1_Duty = 100;
  Output_2_Duty = 100;
}

void OutputEWPDuty() {

  Output_1_Duty = EWPDuty;
  Output_2_Duty = EWPDuty;
}
