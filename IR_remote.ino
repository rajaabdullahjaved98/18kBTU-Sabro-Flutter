
unsigned int Raw;
uint8_t Cal_Min;
int bitCount;
int leadingZeros;

unsigned long error200 = 4294967295;

String L_Power;  // check id power on so comerssor can run 4500


void IR_Setup()

{


  pinMode(RECVER_PIN, INPUT_PULLUP);
  IrReceiver.begin(RECVER_PIN);
  Serial.printf("in Ir Set up****************************************************************************************");
}

void IR_Receiver() {
  if (IrReceiver.decode()) {
    if (IrReceiver.decodedIRData.decodedRawData > error200 || IrReceiver.decodedIRData.numberOfBits != 24) {
      Raw = 0;
    } else {
      Raw = IrReceiver.decodedIRData.decodedRawData;
      IrReceiver.printIRResultShort(&Serial);
    }
    // Serial.print("Output Value is ");
    // Serial.println(Raw, BIN);
    // Serial.println(sizeof(Raw));


    for (int i = 0; i < 23; ++i) {

      // Serial.printf("Bit%i,=%i\n", i, bitRead(Raw, i));
    }


    // Serial.printf("Rawis=%lu\n", Raw);
    bitCount = sizeof(Raw) * 8;  // Number of bits in Raw variable
    bitCount = bitCount - 8;
    // Serial.print("Bit Count:");
    // Serial.println(bitCount);
    //  if (bitRead(Raw,)==0)
    //         bitCount+=1;
    // Count the number of leading zeros
    // leadingZeros = __builtin_clz(Raw); // Count of leading zeros in the 32-bit representation
    Raw = Raw & (0x00FFFFFF);
    // Serial.printf("Raw is : %u\n", Raw);
    //bitCount -= leadingZeros; // Adjust bit count
    //if (bitRead(Raw,23)==0)
    //bitCount+=1;
    // Serial.printf("Binary Digit Count is=%d\n", bitCount);



    if (Raw == 0b00000000000000000000000000000000) {
      Garbage_counter2++;

      // Serial.printf("Got Garabage Zeros*******************************************************************************************Garbafe\n");

      IrReceiver.resume();  // Enable receiving of the next value
      attachInterrupt(RECVER_PIN, function_ISR, CHANGE);
      flipper_Ir_Data_timer.detach();
      return;
    }

    if (Raw == 0b11111111111111111111111111111111)

    {
      Garbage_counter++;

      // Serial.printf("Got Garabage Ones*******************************************************************************************Garbafe\n");

      IrReceiver.resume();  // Enable receiving of the next value
      attachInterrupt(RECVER_PIN, function_ISR, CHANGE);
      flipper_Ir_Data_timer.detach();
      return;
    }

    if (IrReceiver.decodedIRData.protocol != PULSE_DISTANCE || (bitCount != 24)) {
      Noise_Counter++;
      Serial.println(F("Received noise or an unknown (or not yet enabled) protocol*******************************************************************************Noise***"));
      // We have an unknown protocol here, print more info
      IrReceiver.printIRResultRawFormatted(&Serial, true);
      IrReceiver.resume();  // Enable receiving of the next value
      attachInterrupt(RECVER_PIN, function_ISR, CHANGE);
      flipper_Ir_Data_timer.detach();
      return;
    }

    Serial.println();
    delay(100);
    IrReceiver.resume();  // Enable receiving of the next value
    attachInterrupt(RECVER_PIN, function_ISR, CHANGE);
     ir_interrupt_detach= false;
    flipper_Ir_Data_timer.detach();

    if (bitCount == 24) {

      Get_Result();
    }
  }
}


void Get_Result() {
  Serial.printf("\nXsemiphore taking  in IR\n");
  xSemaphoreTake(xSemaphore, portMAX_DELAY);
  operation_mode = false;
  L_Mode = Mode;

  Set_Timer_On();   // Check timer on Data is Coming
  Set_Timer_Off();  // Check Timer off data is coming
  Cal_Time();
  Timer_Set();



  if (IR_Timer_data == "No" && IR_Timer_Cancel == "NO")  // only exeute if not Timer data
    Serial.printf("execute data*******************************************************************************************Confirm\n");

  Buzzer();
  {
    if (bitRead(Raw, 0) == 0) {
      if ((bitRead(Raw, 1) == 0) || (bitRead(Raw, 15) == 0)) {
        Power = "ON";
        ShutDown_Timer.detach();

        bitWrite(Ble_8Bit1, 7, 1);  // Power On
      }
      if ((bitRead(Raw, 1) == 1) && (bitRead(Raw, 15) == 1)) {
        Power = "OFF";
        ML_Power = "OFF";
        //  Esp_32="Stop";   // This Line is Don't run stop function

        bitWrite(Ble_8Bit1, 7, 0);  // Power OFF
      }
      if ((bitRead(Raw, 6) == 0) && (bitRead(Raw, 7) == 0)) {
        Fan_Status = "A";
         bitWrite(Ble_8Bit1, 5, 1);  //Fan auto
        bitWrite(Ble_8Bit1, 4, 0);  // Fanauto
         bitWrite(Ble_8Bit1, 3, 0);
      }
      if ((bitRead(Raw, 6) == 0) && (bitRead(Raw, 7) == 1)) {
        Fan_Status = "L";
      }
      if ((bitRead(Raw, 6) == 1) && (bitRead(Raw, 7) == 0)) {
        Fan_Status = "M";
      }
      if ((bitRead(Raw, 6) == 1) && (bitRead(Raw, 7) == 1)) {
        Fan_Status = "H";
      }
      if ((bitRead(Raw, 13) == 0) && (bitRead(Raw, 14) == 0) && (bitRead(Raw, 15) == 0)) 
      {
        Mode = "A";
         bitWrite(Ble_8Bit2, 5, 1); // Auto on
        Set_Temp = 25.00;

        
      }
      if ((bitRead(Raw, 13) == 0) && (bitRead(Raw, 14) == 0) && (bitRead(Raw, 15) == 1)) {
        Mode = "C";
       bitWrite(Ble_8Bit2, 7, 0);  // mode c
        bitWrite(Ble_8Bit2, 6, 0);  // mdec
        bitWrite(Ble_8Bit2,5,0); // Auto off
       
      }
      if ((bitRead(Raw, 13) == 0) && (bitRead(Raw, 14) == 1) && (bitRead(Raw, 15) == 0)) {
        Mode = "D";
        bitWrite(Ble_8Bit2, 7, 1);  // Mode D
        bitWrite(Ble_8Bit2, 6, 0);  // Mode D
        bitWrite(Ble_8Bit2,5,0); // Auto off
     
      }
      if ((bitRead(Raw, 13) == 0) && (bitRead(Raw, 14) == 1) && (bitRead(Raw, 15) == 1)) {
        Mode = "F";
         bitWrite(Ble_8Bit2, 7, 1);  // mode F new bits
        bitWrite(Ble_8Bit2, 6, 1);  //
        bitWrite(Ble_8Bit2,5,0); // Auto off
      }
      if ((bitRead(Raw, 13) == 1) && (bitRead(Raw, 14) == 0) && (bitRead(Raw, 15) == 0)) {
        Mode = "H";

        bitWrite(Ble_8Bit2, 7, 0);  // mode H
        bitWrite(Ble_8Bit2, 6, 1);  //
        bitWrite(Ble_8Bit2,5,0); // Auto off
       
      }

      if ((bitRead(Raw, 8) == 0) && (bitRead(Raw, 9) == 1) && (bitRead(Raw, 10) == 0) && (bitRead(Raw, 11) == 1) && (bitRead(Raw, 12) == 1)) {
        Set_Temp = 16;
      }
      if ((bitRead(Raw, 8) == 0) && (bitRead(Raw, 9) == 1) && (bitRead(Raw, 10) == 1) && (bitRead(Raw, 11) == 0) && (bitRead(Raw, 12) == 0)) {
        Set_Temp = 17;
      }
      if ((bitRead(Raw, 8) == 0) && (bitRead(Raw, 9) == 1) && (bitRead(Raw, 10) == 1) && (bitRead(Raw, 11) == 0) && (bitRead(Raw, 12) == 1)) {
        Set_Temp = 18;
      }
      if ((bitRead(Raw, 8) == 0) && (bitRead(Raw, 9) == 1) && (bitRead(Raw, 10) == 1) && (bitRead(Raw, 11) == 1) && (bitRead(Raw, 12) == 0)) {
        Set_Temp = 19;
      }
      if ((bitRead(Raw, 8) == 0) && (bitRead(Raw, 9) == 1) && (bitRead(Raw, 10) == 1) && (bitRead(Raw, 11) == 1) && (bitRead(Raw, 12) == 1)) {
        Set_Temp = 20;
      }
      if ((bitRead(Raw, 8) == 1) && (bitRead(Raw, 9) == 0) && (bitRead(Raw, 10) == 0) && (bitRead(Raw, 11) == 0) && (bitRead(Raw, 12) == 0)) {
        Set_Temp = 21;
      }
      if ((bitRead(Raw, 8) == 1) && (bitRead(Raw, 9) == 0) && (bitRead(Raw, 10) == 0) && (bitRead(Raw, 11) == 0) && (bitRead(Raw, 12) == 1)) {
        Set_Temp = 22;
      }
      if ((bitRead(Raw, 8) == 1) && (bitRead(Raw, 9) == 0) && (bitRead(Raw, 10) == 0) && (bitRead(Raw, 11) == 1) && (bitRead(Raw, 12) == 0)) {
        Set_Temp = 23;
      }
      if ((bitRead(Raw, 8) == 1) && (bitRead(Raw, 9) == 0) && (bitRead(Raw, 10) == 0) && (bitRead(Raw, 11) == 1) && (bitRead(Raw, 12) == 1)) {
        Set_Temp = 24;
      }
      if ((bitRead(Raw, 8) == 1) && (bitRead(Raw, 9) == 0) && (bitRead(Raw, 10) == 1) && (bitRead(Raw, 11) == 0) && (bitRead(Raw, 12) == 0)) {
        Set_Temp = 25;
      }
      if ((bitRead(Raw, 8) == 1) && (bitRead(Raw, 9) == 0) && (bitRead(Raw, 10) == 1) && (bitRead(Raw, 11) == 0) && (bitRead(Raw, 12) == 1)) {
        Set_Temp = 26;
      }
      if ((bitRead(Raw, 8) == 1) && (bitRead(Raw, 9) == 0) && (bitRead(Raw, 10) == 1) && (bitRead(Raw, 11) == 1) && (bitRead(Raw, 12) == 0)) {
        Set_Temp = 27;
      }
      if ((bitRead(Raw, 8) == 1) && (bitRead(Raw, 9) == 0) && (bitRead(Raw, 10) == 1) && (bitRead(Raw, 11) == 1) && (bitRead(Raw, 12) == 1)) {
        Set_Temp = 28;
      }
      if ((bitRead(Raw, 8) == 1) && (bitRead(Raw, 9) == 1) && (bitRead(Raw, 10) == 0) && (bitRead(Raw, 11) == 0) && (bitRead(Raw, 12) == 0)) {
        Set_Temp = 29;
      }
      if ((bitRead(Raw, 8) == 1) && (bitRead(Raw, 9) == 1) && (bitRead(Raw, 10) == 0) && (bitRead(Raw, 11) == 0) && (bitRead(Raw, 12) == 1)) {
        Set_Temp = 30;
      }
      if (Power == "ON")  // To Turn on Lcd on lu power is on
      {
        digitalWrite(PIN_HT1621_BL, HIGH);

        LCD_Temp(Set_Temp);  // Send Lcd Temp
      }

      if (Stop_Stop == "No")  // saving mode is off??? have to check
      {

        Defrost_Cycle_Complete = "Yes";
        Defrost_mode = "NO";
      }

      if ((bitRead(Raw, 4) == 0)) {
        Saving_Mode = 0;
       bitWrite(Ble_8Bit2,4,0);  //saving mode off
      }
      if ((bitRead(Raw, 4) == 1) && Mode != "A") {
        Saving_Mode = 1;
       bitWrite(Ble_8Bit2,4,1);  //saving mode on
       Set_Temp = 27;
      }

      if ((bitRead(Raw, 2) == 1) || (bitRead(Raw, 3) == 1)) {
        Swing = "OF";

        H_T = 0;
        bitWrite(Ble_8Bit1, 6, 0);  // Swing OFF
        Swing_Stop();
      }
      if ((bitRead(Raw, 2) == 0) && (bitRead(Raw, 3) == 0)) {
        Swing = "ON";
        H_T = 0;
        bitWrite(Ble_8Bit1, 6, 1);  // Swing On
      }

      // Serial.printf("\nIR_Data_Recived Remote =%s,Mode=%s,Swing=%s,Fan=%s,Set_Temp=%F,Auto_Temp=%s,Saving_Mode=%u\n",Power.c_str(),Mode.c_str(),Swing.c_str(),Fan_Status.c_str(),Set_Temp,Auto_Temp.c_str(),Saving_Mode);
    }
  }
  IR_Timer_data = "No";
  IR_Timer_Cancel = "NO";
  IR_Data_Changes();
  xSemaphoreGive(xSemaphore);
  Serial.printf("\nXsemiphore give  in IR \n");
  Serial.printf("\nIR_Data_Recived Remote =%s,Mode=%s,Swing=%s,Fan=%s,Set_Temp=%F,Auto_Temp=%s,Saving_Mode=%u\n", Power.c_str(), Mode.c_str(), Swing.c_str(), Fan_Status.c_str(), Set_Temp, Auto_Temp.c_str(), Saving_Mode);
}







void Set_Timer_Off()


{

  // ================== Timer Code ===================

  // ================== Timer OFF Code Start ===================
  if (bitRead(Raw, 0) == 1 && bitRead(Raw, 1) == 1 && (bitRead(Raw, 2) == 1)) {
    Serial.println("Timer OFF Commond is Running");

    if (Esp_32 == "RUN") {
      Timer_of = "ON";
      bitWrite(Ble_8Bit5, 2, 1);  //Timerof is on
      bitWrite(Ble_8Bit5, 1, 1);  //Timerof is on
      Tof_Set = "Yes";
      Buzzer();
    }

    IR_Timer_data = "Yes";  // yes means data of timer is coming



  }  // First if End (Timer OFF Code End)

  if (bitRead(Raw, 0) == 1 && bitRead(Raw, 1) == 0 && (bitRead(Raw, 2) == 1))  // timer on Off code
  {
    Serial.println("  Timer Off  is DEActive");
    if (Esp_32 == "RUN") {
      Timer_of = "OF";
      bitWrite(Ble_8Bit5, 2, 0);  //Timerof is off
      bitWrite(Ble_8Bit5, 1, 1);  //Timerof is off
      F_Hour = 00;
      F_Min = 00;
      Tof_sec = 0;
      flipper3.detach();  //Deattach Timer
      Tof_Sec_Left = 0;
      Tof_Set = "No";

      digitalWrite(PIN_HT1621_BL, LOW);  //Turn Off B_Light

      Buzzer();
    }

    IR_Timer_Cancel = "YES";
  }

}  // End of void Timer Off

// ================== Timer ON Code Start ===================
void Set_Timer_On()


{

  if (bitRead(Raw, 0) == 1 && bitRead(Raw, 1) == 1 && (bitRead(Raw, 2) == 0)) {
    Serial.println("Timer ON Commond is Running");

    if (Esp_32 == "RUN") {
      Timer_on = "ON";
      bitWrite(Ble_8Bit5, 4, 1);  //Timer On is On
      bitWrite(Ble_8Bit5, 3, 1);  //Timer On is On
      IR_Timer_data = "Yes";      // yes maen timer data is coming
      Ton_Set = "Yes";
      Buzzer();
    }
    IR_Timer_data = "Yes";  // yes maen timer data is coming



  }  // First if End (Timer ON Code End)




  if (bitRead(Raw, 0) == 1 && bitRead(Raw, 1) == 0 && (bitRead(Raw, 2) == 0))

  {
    Serial.println("Timer On is DEActive");

    if (Esp_32 == "RUN") {
      Timer_on = "OF";            // Timer on Cancel code
      bitWrite(Ble_8Bit5, 4, 0);  //Timer On is OF
      bitWrite(Ble_8Bit5, 3, 1);  //Timer On is OF
      F_Hour = 00;
      F_Min = 00;
      Ton_sec = 0;
      flipper2.detach();
      Ton_Sec_Left = 0;
      Ton_Set = "No";

      Buzzer();
    }

    IR_Timer_Cancel = "YES";
  }

}  // End of void Timer on

void Cal_Time()

{
  if ((IR_Timer_data == "Yes") && (Esp_32 == "RUN"))  // Only Excute if Ir timer data is yes

  {


    Serial.println("Timer Data_Recived");
    bitWrite(Cal_Min, 0, (bitRead(Raw, 15)));
    bitWrite(Cal_Min, 1, (bitRead(Raw, 14)));
    bitWrite(Cal_Min, 2, (bitRead(Raw, 13)));
    bitWrite(Cal_Min, 3, (bitRead(Raw, 12)));
    bitWrite(Cal_Min, 4, (bitRead(Raw, 11)));
    bitWrite(Cal_Min, 5, (bitRead(Raw, 10)));
    bitWrite(Cal_Min, 6, (bitRead(Raw, 9)));
    bitWrite(Cal_Min, 7, 0);
    bitWrite(F_Hour, 0, (bitRead(Raw, 8)));
    bitWrite(F_Hour, 1, (bitRead(Raw, 7)));
    bitWrite(F_Hour, 2, (bitRead(Raw, 6)));
    bitWrite(F_Hour, 3, (bitRead(Raw, 5)));
    bitWrite(F_Hour, 4, (bitRead(Raw, 4)));
    bitWrite(F_Hour, 5, (bitRead(Raw, 3)));
    bitWrite(F_Hour, 6, 0);
    bitWrite(F_Hour, 7, 0);
    Serial.print("Time is ");
    Serial.print(F_Hour, HEX);
    Serial.print(":");
    Serial.print(Cal_Min, HEX);
    Serial.println(" ");

    Serial.print("Cal_Hour_Final=");
    Serial.print(F_Hour, HEX);
    Serial.println("");
    Serial.print("Cal_Min_Final=");
    Serial.print(Cal_Min, HEX);
    Serial.println("");
    Timer_Fsecond = (DectoHex(F_Hour) * 3600) + (DectoHex(Cal_Min) * 60);
    Serial.print(Timer_Fsecond);
    Serial.println(" ");
    // Timer_Fsecond=0;
    // return (second);
  }
}


int DectoHex(int var) {
  int Raw1, Raw2, send;
  Raw1 = (var / 16) % 16;
  Raw2 = var % 16;
  send = Raw1 * 10 + Raw2;
  return (send);
}









void IR_Data_Changes()

{


  if (Mode != L_Mode && Power == "ON" && Stop_Stop == "No") 
  { 
    Mode_Change = "Yes";
    Auto_Temp = "C";
    bitWrite(Ble_8Bit1, 3, 1);  // auto c
    bitWrite(Ble_8Bit1, 4, 1);  // m_change yes
     if (Esp_32 == "RUN" && Mode != "F")
    {
      digitalWrite(Inverter_OFF_PIN, HIGH);
    }
     Serial.printf("Mode changes****************************************YES******************************************from Mode IR_Data_Change****\n ");
  }

  if (Power != L_Power) {

    if (Power == "ON")  // means First timer Power on
    {
    }
  }


}  // End of Main



void check_ir(){

  if (ir_interrupt_detach && ir_time_check>(millis()+300)){
    IrReceiver.resume();  // Enable receiving of the next value
    attachInterrupt(RECVER_PIN, function_ISR, CHANGE);
    ir_interrupt_detach= false;
    flipper_Ir_Data_timer.detach();
    return;
  }
  else
  return;
}
