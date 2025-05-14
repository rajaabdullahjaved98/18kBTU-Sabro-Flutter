

void Check_Stop()

{

   if(Stop_Stop=="Yes")
   
{

  if(Power=="OFF")

  {
   Power_OFF();
   return;

  }
  Running_Mode="Error_Control";
   bitWrite(Ble_8Bit3,7,0); // Error_control
    bitWrite(Ble_8Bit3,6,1);
    bitWrite(Ble_8Bit3,5,0);

  Gas_err.detach();
  Gas_Err_Confirm.detach();
  flipper_Out_Door_Sensor_Timer.detach();
  flipper_ODST_Confirm.detach();
     
  Serial.print("Error execution***********************************************************************************************");
  Serial.println("");
  
      Swing = "OF";
      Swing_Stop();
     Comp_run(0);
     caliberated = false;

     
      sending(Manual_fan_speed,Write,data_HB,Motor_of);
      OD_Motor="Error_Stop_OFF";
      bitWrite(Ble_8Bit2,3,1); // E_off
       bitWrite(Ble_8Bit2,2,0); // 
       bitWrite(Ble_8Bit2,1,1); // 
      sending(Mode_Inv,Write,data_HB,inv_Mode_Of);
       bitWrite(Ble_8Bit5,5,0); // cond mode off
     bitWrite(Ble_8Bit5,6,0); // cond mode off
     sending(Manual_4Way,Write,data_HB,R_Valve_Of);
     digitalWrite(fan_low,LOW);  // Added by me to stop indoor fan
    digitalWrite(fan_mid,LOW); 
    digitalWrite(fan_high,LOW); 
     bitWrite(Ble_8Bit1,5,0); //Fan off
      bitWrite(Ble_8Bit1,4,0);  // Fan off
       previous_discharge_temp=0;
    discharge_previous_psi=0;
    caliberated=false;
    R_Data.Calculated_Discharge_Pressure=0;
    // ALL_OFF_FAN();                                  // Added by Rana Feed back

    }  // end of if 

}






