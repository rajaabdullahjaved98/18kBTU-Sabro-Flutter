




void Mini_Print_Center()

{
  Serial.printf("\nPower=%s,Mode=%s,Swing=%s,Fan=%s,Set_Temp=%g,A_Temp=%s,S_Mode=%u::", Power.c_str(), Mode.c_str(), Swing.c_str(), Fan_Status.c_str(), Set_Temp, Auto_Temp.c_str(), Saving_Mode);
Serial.printf("::Garbage_count=%i,Noise_Count=%i",Garbage_counter,Noise_Counter);
 Serial.printf("Room=%g,Coil=%g,Delta_Temp=%g\n", Room_sensor, Coil_sensor, Delta_Temp);


}

void New_Print_Center()

{
  
 
  Serial.printf("\nPower=%s,Mode=%s,Swing=%s,Fan=%s,Set_Temp=%g,A_Temp=%s,S_Mode=%u::", Power.c_str(), Mode.c_str(), Swing.c_str(), Fan_Status.c_str(), Set_Temp, Auto_Temp.c_str(), Saving_Mode);
  Serial.printf("Room=%g,Coil=%g,Delta_Temp=%g", Room_sensor, Coil_sensor, Delta_Temp);
  Serial.printf("::Esp32=%s::Inv_Relay=%i::Pro_Run=%i::,Pro_to=%i;S_Delay=%s::Running_Mode=%s\n\n", Esp_32.c_str(), digitalRead(Inverter_OFF_PIN), Protocol_Run,Pro_to, Start_Delay.c_str(),Running_Mode.c_str());
  Serial.printf("Stop_Stop=%s,Comp_Start_Timer=%s,Motor_Timer=%s,Delta_Achived=%s,Fan_Running_Mode=%s,H_S=%i,H_T=%i,Power_var=%i,EEprom_Save=%s\n\n", Stop_Stop.c_str(),Comperssor_Start_timer, Motor_Timer.c_str(), Delta_Achived.c_str(), Fan_Running_Mode.c_str(), H_S, H_T, Power_var, EEP.c_str());
  Serial.printf("OD_Motor=%s,ODM_Status=%s,Amb_Temp=%g,LL_temp=%g,Dis_Temp=%g,Suc_Temp=%g,Inv_Mode=%s,Mode_Change=%s,Room_Sensor_counter=%i\n\n", OD_Motor.c_str(), OD_Motor_Status.c_str(), ODU_Ambient_Temp, Liquid_Line_temp, Discharge_Temp, Suction_Temp, Cond_mode,Mode_Change.c_str(),Room_Sensor_counter);
  Serial.printf("Ac_volts=%g,Dc_Volts=%g,S_cuurent=%g,F_cuurent=%g,Comp_current=%g,D_Check=%s,D_Mode=%s,D_Cycle=%s,M_Rv=%s\n\n", Ac_volts, Dc_Volts,S_cuurent,F_Current, Comp_current, Defrost_Check.c_str(), Defrost_mode.c_str(), Defrost_Cycle_Complete.c_str(), Maunal_Rv.c_str());

 Serial.printf("Run_Rpm=%i,Comp_Cal_Rpm=%i,Set_RPM=%i,Compersoor_send_Rpm=%i,Comperssor_Ruuning_Rpm=%i, Comperssor_RMode=%s::Comperssor_Pkrs_Mode=%s::Comprun=%i\n\n",Run_Rpm,Comp_Cal_Rpm,Print_Set_RPM,Comperssor_send_Rpm,Comperssor_Running_RPM, Comperssor_RMode.c_str(),Comperssor_Pkrs_Mode.c_str(),Comprun);
  Serial.printf("CM_WireBreak_Counter is=%i,Cm_Wire=%s,Prot_Counter is=%i,,Inverter_Biultin_Error=%s,Garbage_count=%i,Garbage_count2=%i,Noise_Count=%i,Error_Checking=%s,ODMS_Warning=%s\n", CMWire_Break, CMW_Wire, Prot_Counter, Inv_Error.c_str(), Garbage_counter,Garbage_counter2,Noise_Counter, Error_Found.c_str(),ODMS_Error.c_str());
  Serial.print(",Falut_Inv_code=");
  Serial.print(Falut_Inv_code, HEX);
  Err_Print();
  if (Stop_Stop == "Yes" && Power == "ON") {
    Errors_Print();
  }
  Timer_Print();
  
  Serial.printf("::Time_Total=%u,Power has changed in print Loop:Last_Power=%s,CPower=%s\n", Time_Total_c, ML_Power.c_str(), Power.c_str());
  //Serial.printf("Power has changed in print Loop:Last_Power=%s,CPower=%s\n",ML_Power.c_str(),Power.c_str());
}





void Err_Print()


{

  //Serial.println("");
  Serial.print("::Error=");

  Serial.print("Error=");

  for (int i = 0; i < 30; i++) {
    Serial.print(Errors_info[i]);
  }
 // Serial.print("==");
  //Serial.print(Print_Error);
  //Serial.print(",");
 // Serial.print(Last_Err);

  Serial.printf("==,Print_Err=%s,Curent_Err=%s,Last_Err=%s",Print_Error.c_str(),Inv_Error.c_str(),Last_Err.c_str());

  if (Inv_Error != "None") 
  {
    Last_Err = Inv_Error;
  }

  if (Falut_Inv_code != 0) 
  {

    for (int i = 0; i < 20; i++) {

      if (IB_F_value1[i] == Falut_Inv_code) {
        Last_Err = IB_Fault_1[i];
      }
    }

    for (int i = 0; i < 5; i++) 
    {

      if (IB_F_value2[i] == Falut_Inv_code) 
      {
        Last_Err = IB_Fault_2[i];
      }
    }
  
  }
}


void pprint_ALL() 
{

  Serial.printf("in Print All*************************************************\n");

 
 for (int i = 1; i <25; i++) 
  {
     Serial.printf(":Hour=%i",i);
    
    Serial.printf(",Power=%g",EE_Hour[i]);
   
    
   // Serial.print("\n\n");

  }
     Serial.print("\n\n");

    for (int i = 1; i < 32; i++) 
  {
     Serial.printf(":Day=%i",i);
     Serial.print(",Power=");
     Serial.print(EE_Day[i]);
    
    // Serial.print("\n\n");
  }
    Serial.print("\n\n");
   for (int i = 1; i < 13; i++) 
  {




     Serial.printf(":Month=%i",i);
   
    Serial.print(":Month Power= ");
    Serial.print(EE_Month[i]);



   // Serial.print("\n\n");

  }

  Serial.print("\n\n");

  
}



void Run_Print()

{

Serial.printf("In Run Data::Time=%i:%i:%i::RTC_Err=%i::",R_Data.Hour_Rtc,R_Data.Min_Rtc,R_Data.Sec_Rtc,RTC_Err);
 Serial.printf("Date: %i/%i/%i::\n",R_Data.day_Rtc,R_Data.month_Rtc,R_Data.Year_RTC);
 //Serial.printf(",BLe1=%i,BLe2=%i,BLe3=%i,BLe4=%i,BLe5=%i,Set_Temp=%g,Coil_Temp=%g,Delta=%g,",R_Data.Ble_8Bit1,R_Data.Ble_8Bit2,R_Data.Ble_8Bit3,R_Data.Ble_8Bit4,R_Data.Ble_8Bit5,R_Data.Set_Temp,R_Data.Coil_sensor,R_Data.Delta_Temp);
 //Serial.printf("S_Temp=%g,LL_TEmp=%g,D_TEmp=%g,ABMT_TEmp=%g",R_Data.Suction_Temp,R_Data.Liquid_Line_temp,R_Data.Discharge_Temp,R_Data.ODU_Ambient_Temp);
//Serial.printf("Ac=%g,Dc=%g,S_Curent=%g,F_current=%g,C_Cuurent%g,RPM=%i,Inv_Error=%i,F_Code=%i,Ton_Sec=%i,Tof_Sec=%i\n\n",R_Data.Ac_volts,R_Data.Dc_Volts,R_Data.S_cuurent,R_Data.F_Current,R_Data.Comp_current,R_Data.Comperssor_Running_RPM,R_Data.Inv_Error,R_Data.Falut_Inv_code,R_Data.Ton_sec,R_Data.Tof_sec);
Serial.printf("REnergy_Hour=%g,REnergy_Day=%g.REnergy_Month=%f,",R_Data.R_Hour_Energy,R_Data.R_Day_Energy,R_Data.R_Month_Energy);
 Serial.printf("Min_Energy+=%g, ::Run_Energy_Hour=%g,Run_Energy_Day=%g,Run_Energy_Month=%g,\n\n", Energy_Min,Run_Energy_Hour,Run_Energy_Day,Run_Energy_Month);
//  Serial.printf("::Volts=%g,S_cuurent=%g,Energy+=%g\n\n", Ac_volts,S_cuurent,Energy);
  Serial.printf("Peak_Rate=%g,OFF_Peak=%g,R_Peak%g,Rs_consume=%g,",peak_unit_rate,off_peak_unit_rate,Running_Peak,Current_Rs_hour);
   Serial.printf("Current_Energy=%g,Target_Energy=%g,CEnergy_Cost=%g,Cutomer_Rs=%g,Money_Diffl=%g \n\n",Energy,Target_Energy,Currenr_Energy_cost,Cutomer_Rs,Money_Equal);
   Serial.printf("CT=%g,PT_Start=%i,PT_Stop=%i,TPM=%i,SPM=%i,OP=%i,BRPM_PKRS=%i,RS_RPM=%i,BRPM=%i,BRPM_counter=%i,E_cal=%i,MT=%i,Met_save=%i\n",CT,peak_time_start,peak_time_stop,TPM,SPM,operation_mode,Base_RPM_PKRS,RS_RPM,BRPM,BRPM_counter,E_cal,Met_Type,Met_save);
  Serial.printf("DP_New=%g,Dp_Final=%g,SL_New=%g,SL_final=%g,H_Bosster=%i,Name:%s,Delta_Go=%i\n\n",DP_New,Dp_Final,SL_New,SL_final,H_Bosster,nameString.c_str(),Delta_Go);
}

void print_master(uint16_t print_option)

{



}

void EP_Print()

{


    peak_time_start = EEPROM.read(POWER_Address+1);
    peak_time_stop = EEPROM.read(POWER_Address+2);
    float Tpeak=  EEPROM.get(POWER_Address+3,peak_unit_rate);
    float Toff_peak= EEPROM.get(POWER_Address+7,off_peak_unit_rate);
    Serial.printf("PT_Start=%i,PT_Stop=%,Tpeak=%g,Toff_peak=%g\n\n",peak_time_start,peak_time_stop,Tpeak,Toff_peak);






}

