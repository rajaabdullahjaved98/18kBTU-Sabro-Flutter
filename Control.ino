//uint8_t Room_Sensor_counter=0;

void Control_Center()

{
 // Serial.printf("********************************In Coontrol center  checking Delta  ********************************************************\n\n\n");
  Delta_Check();
 // Serial.printf("********************************In Control  center delata has checked checking  ********************************************************\n\n\n");
 Waitng_Mode();
  Delata_No();
  Power_OFF();
  Mode_HAS_Changed();
 Comp_Run_Normal_RPM();
 RV_Control();
  Motor_Control();
 Deforsting_Setting();
  Fan_Mode();
 Check_Stop();
}

void Waitng_Mode()
{


  if ((Delta_Achived == "NO") && (Comperssor_Running_RPM==0)) 
  {

    Running_Mode = "Control_Center";
    bitWrite(Ble_8Bit3, 7, 1);  // Control
    bitWrite(Ble_8Bit3, 6, 0);
    bitWrite(Ble_8Bit3, 5, 1);
  //  Serial.printf("\n in Control center************************************\n");
  }

}

void Delata_No()
{
   if (Delta_Temp >= .50) 
  {
    Room_Sensor_counter++;
    if(Room_Sensor_counter>15)
    
    {
      if( Delta_Achived == "YES")

      {

          flipper_Out_Door_Sensor_Timer.attach(30, OutDoor_Sensor_Error);
           Serial.printf("******************************** ***********Outdoor Sensor Attached after Delta no*********************************************\n\n\n");
      }
      bitWrite(Ble_8Bit1, 1, 0);  // delta no
      Delta_Achived = "NO";
      Room_Sensor_counter=0;
      Delta_Go=false;
    }
  }
}


void Comp_Run_Normal_RPM()

{
  if ((Comperssor_Running_RPM > 5500) && (Stop_Stop == "No"))

  {
    Serial.println(" comp**************************Runnung >5000***********************>5000******");
    Delta_Check();
    clear_rx();
    return;
  }

  if ((Esp_32 == "RUN") && (Mode != "F") && (Defrost_mode == "NO") && (Cond_mode != "Of") && (Stop_Stop == "No") && (Mode_Change == "NO"))  // normal Ruuning no delta has acived & power not off

  {
    E_Saving();
   if ((Inv_Error == "Ipm_Temp") || (Inv_Error == "Input_cuurent") || (Comp_current >= 9.0))
    {
      Comp_run(2500);
      Running_Mode = "INV_Error";
      Serial.printf("********************************In inv error run checking Delta  ********************************************************\n\n\n");
      Delta_Check();
      return;
    }

    if ((Delta_Achived == "NO") && (Mode != "D") && (Saving_Mode != 1) && (Motor_Timer == "OFF"))
    {
      
     Comp();
   }
  }
}



void Motor_Control() {
  if ((Esp_32 == "RUN") && (Defrost_mode == "NO") && (Stop_Stop == "No") && (Comperssor_Start_timer == "OF") && (Motor_Timer == "OFF") && (Mode_Change == "NO") && (Delta_Achived == "NO"))
  {
    // Serial.println("************************'going to inverter****************************************************************Control***********************  ");
    Inverter_Control();
    //  Serial.println("************************'going to inverter****************************************************************Control***********************  ");
    if (Mode == "C" || Mode == "D" || (Mode == "A" && Auto_Temp == "C"))

    {
      Lac_Control();
    }
    if (Mode == "H" || (Mode == "A" && Auto_Temp == "H")) {
      Heating_Control();
    }
  }
}

void RV_Control() {

  //Serial.println("In Rv control*********************************************************");
  if ((Esp_32 == "RUN") && (Comperssor_Start_timer == "OF") && (Stop_Stop == "No") && (Mode_Change == "NO"))

  {

    if ((Mode == "C" || Mode == "D" || Defrost_mode == "YES") || (Mode == "A" && Auto_Temp == "C"))

    {
      // Serial.println("In Rv control*******************************************************R?V valve off meaning cooling *****************");

      sending(Manual_4Way, Write, data_HB, R_Valve_Of);
       bitWrite(Ble_8Bit4,0,0); //RVS OFF
    }

    if ((Mode == "H") || (Mode == "A" && Auto_Temp == "H"))

    {

      if ((Mode_Change == "NO") && (Defrost_mode == "NO"))


      {
        if ((Comperssor_Running_RPM >= 100) && (Comperssor_Running_RPM <= 5300))
         {
          sending(Manual_4Way, Write, data_HB, R_Valve_On);  //4 way vlave off on Cooling,On on Heating,Mode 0 can do it. check this is true or not
            bitWrite(Ble_8Bit4,0,1); //RVS On
        }
        // Serial.println("In Rv control*******************************************************R/v valve heating on  ****************heating RV on *");
      }
    }
  }
}


void Lac_Control()

{
  if (Liquid_Line_temp <= 30) {
    sending(Manual_fan_speed, Write, data_HB, Motor_of);

    OD_Motor = "C_Lac_OFF";
    bitWrite(Ble_8Bit2, 3, 0);  // Lac_Off
    bitWrite(Ble_8Bit2, 2, 0);  //
    bitWrite(Ble_8Bit2, 1, 0);  //
    // BRPM=true;
    // BRPM_counter=0;
  }
  if (Liquid_Line_temp > 30.1) {
    sending(Manual_fan_speed, Write, data_HB, Motor_on);

    OD_Motor = "C_Lac_On";
    bitWrite(Ble_8Bit2, 3, 0);  // Lac_on
    bitWrite(Ble_8Bit2, 2, 0);  //
    bitWrite(Ble_8Bit2, 1, 1);  //
  }
}

void Heating_Control()

{
  if (Coil_sensor >= 62)  // in heating if Rooom Temp is 26 liitle Hot 65 error Coil over herat can Catch

  {
    Start_Delay = "No";
    bitWrite(Ble_8Bit3, 0, 0);  // staret delay no
    flipper_Delay.detach();
  }
  if (Coil_sensor < 45) {
    //sending(Manual_fan_speed,Write,data_HB,Motor_on);
    Motor("ON");
    bitWrite(Ble_8Bit2, 3, 0);  // HAc_On
    bitWrite(Ble_8Bit2, 2, 1);  //
    bitWrite(Ble_8Bit2, 1, 0);  //


    if (OD_Motor == "H_OFF") {
      flipper_Deforst_Check.attach(180, Deforst_Heating_timer);  // To Make sure now Defrost can work
    }
    OD_Motor = "H_ON";
    bitWrite(Ble_8Bit2, 3, 0);  // HAc_On
    bitWrite(Ble_8Bit2, 2, 1);  //
    bitWrite(Ble_8Bit2, 1, 0);  //
  }

  if (Coil_sensor > 55)

  {
    // sending(Manual_fan_speed,Write,data_HB,Motor_of);
    Motor("OFF");
    bitWrite(Ble_8Bit2, 3, 0);  // HAc_Off
    bitWrite(Ble_8Bit2, 2, 1);  //
    bitWrite(Ble_8Bit2, 1, 1);  //
    BRPM=true;
     BRPM_counter=0;
    OD_Motor = "H_OFF";
    Defrost_Check = "NO";       // Stop Defrost function
    bitWrite(Ble_8Bit3, 2, 0);  // deforst check no
  }
}



void Motor(String Temp_M_Data)

{
  if (Temp_M_Data == OD_Motor_Status)

  {
    // Serial.print("Motor_same***************************************************Going Back****");
    //Serial.println("");
    return;
  }
  Serial.print("Motor_Change***************************************************************************************");
  Serial.println("");

  if (Temp_M_Data == "ON")

  {
    // Protocol_Run=1;
    // flipper_Protocol_Delay.attach(60,Prot_Timer);
    sending(Manual_fan_speed, Write, data_HB, Motor_on);
  }

  if (Temp_M_Data == "OFF")

  {

    sending(Manual_fan_speed, Write, data_HB, Motor_of);
  }
}

void E_Saving()

{



  if ((Delta_Achived == "NO") &&  (Saving_Mode == 1))
  {
   // ESP.restart();
  Serial.printf("*******************************************In Saving Mode\n\n\n");
    Running_Mode = "Saving";
    Serial.printf("********************************In saving mode run checking Delta  ********************************************************\n\n\n");
     Delta_Check();
    Comp_run(1500);  // 3.75A vibaration
     Set_Temp = 27;
   
  }

  if ((Delta_Achived == "NO") && (Mode == "D"))
  {
     bitWrite(Ble_8Bit2, 7, 1);  // Mode D
        bitWrite(Ble_8Bit2, 6, 0);  // Mode D
        bitWrite(Ble_8Bit5, 7, 0);  // mode Fan must be zero
    Running_Mode = "DRY";
    Serial.printf("********************************In Dry Mode run checking Delta  ********************************************************\n\n\n");
    Delta_Check();
    Comp_run(1950);  // 3.75A vibaration
  }


}


void Inverter_Control() {

  if (Mode == "C" || Mode == "D" || Defrost_mode == "YES" || (Mode == "A" && Auto_Temp == "C"))

  {
    //  Serial.println("************************'in  inverter****************************************************************Control*******************Cooling****  ");
    sending(Mode_Inv, Write, data_HB, inv_Mode_Cool);
     bitWrite(Ble_8Bit5,5,1); // cond mode cool
     bitWrite(Ble_8Bit5,6,0); // cond mode cool


    return;
  }

  if (Mode == "H" || (Mode == "A" && Auto_Temp == "H")) {
    if (Defrost_mode == "NO")

    {
      //   Serial.println("************************'in  inverter****************************************************************Control*******************Heaing****  ");
      sending(Mode_Inv, Write, data_HB, inv_Mode_Heat);
       bitWrite(Ble_8Bit5,5,0); // cond mode Heat
     bitWrite(Ble_8Bit5,6,1); // cond mode Heat
    }
  }
}




void Fan_Mode() {

  if (Mode == "F" && digitalRead(Inverter_OFF_PIN) == 1) {
    Serial.println("********************************************************************************************************************'in fan modeing ");
    Running_Mode = "Fan_Mode";
    sending(Mode_Inv, Write, data_HB, inv_Mode_Of);
    sending(Manual_fan_speed, Write, data_HB, Motor_of);
    digitalWrite(Inverter_OFF_PIN, LOW);
    Protocol_Run = 1;

    flipper_Protocol_Delay.attach(60, Prot_Timer);
    DDPNC = 0;
    Suction_Temp = 0;
    Liquid_Line_temp = 0;
    Discharge_Temp = 0;
    ODU_Ambient_Temp = 0;
    Ac_volts = 0;
    Dc_Volts = 0;
    S_cuurent = 0;
    Comp_current = 0;
    Comperssor_Running_RPM = 00;
    Comperssor_send_Rpm = 00;
    Cond_mode = "Of";
  }
}




void Deforsting_Setting()

{
  if (Defrost_mode == "YES" && Comperssor_Start_timer == "OF" && Stop_Stop == "No" && Mode_Change == "NO") {
    Running_Mode = "In_Deforsting";
    bitWrite(Ble_8Bit3, 7, 0);  // DEfrosting
    bitWrite(Ble_8Bit3, 6, 0);
    bitWrite(Ble_8Bit3, 5, 1);

    Inverter_Control();

    if (Liquid_Line_temp < 10)  // start DEfrosting both Motor Should off
    {
      Comp_run(4500);
    }

    if (Liquid_Line_temp > 10) {
      Mode_Change = "Yes";
      bitWrite(Ble_8Bit1, 4, 1);  // m_change yes

      Defrost_Cycle_Complete = "Yes";
      bitWrite(Ble_8Bit3, 3, 1);  // deforst cycle yes
      Defrost_mode = "NO";
      bitWrite(Ble_8Bit3, 4, 0);  // Defrsot mode no
    }
  }  // end of if
}  // end of void defrosting

void Mode_HAS_Changed()

{
  // Serial.println("function made has*********************************************changed********only functiom **");
  if (Mode_Change == "Yes" && Stop_Stop == "No")

  {
    Serial.println(" made has*********************************************changed*******Yes****************************************YES Yes yEs mode changed****");
    Running_Mode = "Mode_Change";
    bitWrite(Ble_8Bit3, 7, 1);  // Mode Changed
    bitWrite(Ble_8Bit3, 6, 0);
    bitWrite(Ble_8Bit3, 5, 0);

    Comp_run(0);
     previous_discharge_temp=0;
    discharge_previous_psi=0;
    caliberated=false;
    R_Data.Calculated_Discharge_Pressure=0;
     Pro_to=false;
    sending(Manual_fan_speed, Write, data_HB, Motor_of);
    sending(Mode_Inv, Write, data_HB, inv_Mode_Of);
     bitWrite(Ble_8Bit5,5,0); // cond mode off
     bitWrite(Ble_8Bit5,6,0); // cond mode off
    sending(Manual_4Way, Write, data_HB, R_Valve_Of);
    bitWrite(Ble_8Bit2, 3, 1);  // Mc_off
    bitWrite(Ble_8Bit2, 2, 0);  //
    bitWrite(Ble_8Bit2, 1, 0);  //

    if (Comperssor_Running_RPM == 00)
     {
      Mode_Change = "NO";
      bitWrite(Ble_8Bit1, 4, 0);  // m_change no
      Defrost_Check = "Yes";
     bitWrite(Ble_8Bit3,2,1);
     Comperssor_Start_Timer(180);
    
     
   
    //  start = true;
      if (Defrost_mode == "YES") 
      {
        digitalWrite(fan_low, LOW);
        digitalWrite(fan_mid, LOW);
        digitalWrite(fan_high, LOW);
        Running_Mode = "Deforsting";
      }
    }
  }
}

void Power_OFF()  // this will execute from main off from Comp_run
{
  if (Power == "OFF") {
    Gas_err.detach();
    Gas_Err_Confirm.detach();
    flipper_Out_Door_Sensor_Timer.detach();
    flipper_ODST_Confirm.detach();
    flipper_Protocol_Delay.detach();
    flipper_Delay.detach();
    flipper_Compressor_SINV_timer.detach();
    flipper_Err.detach();
     flipper_Motor_on.detach();
     Heating_Booster.detach();
    Comp_run(0);

    Stop_Stop = "No";
    bitWrite(Ble_8Bit3, 1, 0);  // stop_stop no
    first_time=0;
  
    memset(Errors_info, 0, sizeof(Errors_info));
    start = true;  //  to make sure next time  power on one time gas timer is exected
    
    Power = "OFF";
    Running_Mode = "PStop_Mode";
    bitWrite(Ble_8Bit3, 7, 0);  // Pstop Mode
    bitWrite(Ble_8Bit3, 6, 0);
    bitWrite(Ble_8Bit3, 5, 0);
   Print_Error = "None";
   Last_Err = "0";
   H_T = 0;
    H_S = 0;
    Defrost_Check = "Yes";
    bitWrite(Ble_8Bit3,2,1);
   bitWrite(Ble_8Bit2, 4, 0);  // Esp_wait
   Coil_sensor=0;
    DDPNC = 0;
    Suction_Temp = 0;
    Liquid_Line_temp = 0;
    Discharge_Temp = 0;
    ODU_Ambient_Temp = 0;
    Ac_volts = 0;
    Dc_Volts = 0;
    S_cuurent = 0;
    Comp_current = 0;
    Comperssor_Running_RPM = 00;
    Comperssor_send_Rpm = 00;
    Cond_mode = "Of";
    Protocol_Run = 1;
    bitWrite(Ble_8Bit4, 2, 1);  // Protocol1
    Delta_Go=false;
    Errors_No = 0;
    Last_Err = "0";
    
    Start_Delay = "Wait_POFF";
    bitWrite(Ble_8Bit5, 1, 1);  // start delay wait_POFF
    bitWrite(Ble_8Bit5, 0, 1);  // staret delay wait_POFf

    Motor_Timer = "OFF";
    bitWrite(Ble_8Bit5, 0, 0);  // MT oFF
    //flipper_Motor_on.detach();

      Delta_Achived = "YES";
    CMWire_Break = 0;
    CMW_Wire = "OK";
    Prot_Counter = 0;
    //digitalWrite(PIN_HT1621_BL, LOW);
    //ht.sendCommand(HT1621::LCD_OFF);
    ML_Power = "OFF";
    Error_Found="None";
    Garbage_counter = 0;
    Garbage_counter2 = 0;
    Noise_Counter = 0;
   Running_Mode = "PStop_Mode";
   ODMS_Error="None";
   bool H_Bosster=false;
    Serial.printf("***********in Power_OFF_Function*********************************************,Esp32=%s\n", Esp_32.c_str());

    ind=0;
    TR1=0;
    TR2=0;
    TR3=0;
    TR4=0;
    TR5=0;
    FT=0;
    Pro_to=false;
    Comprun=true;
    Esp_32 = "Shut_Down";
    
      SL_final=0;
      Dp_Final=0; 
    
    R_Data.Calculated_Discharge_Pressure=0;
 
    bitWrite(Ble_8Bit2, 4, 0);  // Esp_wait
    ShutDown_Timer.attach(20, System_OFF);  // Real time clock software baseTimer after 1sec
  }
}
