



void Read_EEP()
{

 for (int i = 1; i < 25; i++) 
  {
    readFromEEPROM(i);
 
  }
 
}



  void readFromEEPROM(int index) 
  {
 // Serial.printf("EEprom_get=%i::",(EEPROM_ADD_Hour+(index * Lenth_Bytes)));
  
    EEPROM.get(EEPROM_ADD_Hour+(index *Lenth_Bytes), Temp_Hour);
   
  // Serial.print("Index is=");
  // Serial.print(index);
   // Serial.printf(":Temp_Hour=%g",Temp_Hour);
    EE_Hour[index]=Temp_Hour;
    //Serial.printf(":EE_Hour[]=%g\n",EE_Hour[index]);
   


   }


    
void Read_EEP_Day()
{


 for (int i = 1; i <32; i++) 
  {
    Read_EEP_Day_Data(i);
  
  }
   
}


  void Read_EEP_Day_Data(int index) 
  {

  
   

   // Serial.printf("EEprom_get_Day=%i::",(EEPROM_ADD_Day+(index * Lenth_Bytes)));

    EEPROM.get(EEPROM_ADD_Day+(index * Lenth_Bytes),Temp_Day);
   
   //Serial.print("Index is=");
   // Serial.println(index);
   // Serial.printf("Temp_Day=%g\n",Temp_Day);
     EE_Day[index]=Temp_Day;
  // Serial.printf("EE_day[]=%g\n",EE_Day[index]);

     

   }

   

void Read_EEP_Month()
{


 for (int i = 1; i <13; i++) 
  {
    Read_EEP_Month_Data(i);
  
  }
 
}



  void Read_EEP_Month_Data(int index) 
  {

   
   /// Serial.printf("EEprom_get_Month=%i::",(EEPROM_ADD_Month+(index * Lenth_Bytes)));

    EEPROM.get(EEPROM_ADD_Month+(index * Lenth_Bytes),Temp_Month);
    

    //Serial.print("Index is=");
   // Serial.println(index);
    //Serial.printf("Temp_month=%g\n",Temp_Month);
     EE_Month[index]=Temp_Month;
    //Serial.printf("EE_Hour[]=%g\n",EE_Month[index]);
   // EE_Month[index]=Temp_Month;
   

   }


   
void Read_All()

{

  
   //  Print_Date();
     //Serial.printf( "Min changed to=%i\n Year check is =%i,Month check is =%i,Day check is =%i,Hour_DP=%i,\n",Min_Rtc,year_check,Month_check,Day_check,dataPointer_Hour);
     //Serial.printf("Min_Energy=%g,Energy_Hour=%g,Energy_Day=%g.Energy_Month=%g\n", Min_power,Energy_Hour,Energy_Day,Energy_Month);
    
    // ALL_Pointer_Hour=1;
    // ALL_Pointer_Day=1;
    // ALL_Pointer_Month=1;
     Read_EEP();
     Read_EEP_Day();
     Read_EEP_Month();
   //  print_ALL();


}

void Run_Data()

{
 Get_Time();


R_Data.Sec_Rtc=Sec_Rtc;

R_Data.Min_Rtc=Min_Rtc;

R_Data.Hour_Rtc=Hour_Rtc;

R_Data.day_Rtc=day_Rtc;

R_Data.month_Rtc=month_Rtc;

R_Data.Year_RTC=year_Rtc;

R_Data.Ble_8Bit1=Ble_8Bit1;
R_Data.Ble_8Bit2=Ble_8Bit2;
R_Data.Ble_8Bit3=Ble_8Bit3;
R_Data.Ble_8Bit4=Ble_8Bit4;
R_Data.Ble_8Bit5=Ble_8Bit5;
if (operation_mode)
{
R_Data.mode_pkr_set = 2;
R_Data.Set_Temp = CT;
R_Data.rupees_send = Cutomer_Rs;
}
else{
R_Data.mode_pkr_set = 1;
R_Data.Set_Temp = Set_Temp;
R_Data.rupees_send = 0;
}
R_Data.Coil_sensor=Coil_sensor;
R_Data.Room_sensor=Room_sensor;
R_Data.Delta_Temp=Delta_Temp;
R_Data.Suction_Temp=Suction_Temp;
R_Data.Discharge_Temp=Discharge_Temp;
R_Data.Liquid_Line_temp=Liquid_Line_temp;
R_Data.ODU_Ambient_Temp=ODU_Ambient_Temp;
R_Data.Ac_volts=Ac_volts;
R_Data.Dc_Volts=Dc_Volts;
R_Data.S_cuurent=S_cuurent;
R_Data.F_Current=F_Current;
R_Data.Comp_current=Comp_current;
R_Data.Comperssor_Running_RPM=Comperssor_Running_RPM;
Check_Error();
R_Data.Inv_Error=Error_Num;;    // From Error_onfo[]
R_Data.Falut_Inv_code=Falut_Inv_code;  // From read odu error
R_Data.Ton_sec=Ton_sec;
R_Data.Tof_sec=Tof_sec;

R_Data.R_Hour_Energy=Run_Energy_Hour;
R_Data.R_Day_Energy=Run_Energy_Day;
R_Data.R_Month_Energy=Run_Energy_Month;
R_Data.Calculated_Discharge_Pressure=Dp_Final;
R_Data.Calculated_Suction_Pressure=SL_final;



}




void Check_Error()

{
  Error_Num = 0;
 
  for (int i = 0; i < 30; i++) 
  {
  
    if ((Errors_info[i]) != 0 ) {
      Error_Num= i + 1;
      Serial.printf("BLe_Erroris=%i\n", Error_Num);
    }
  }

}

