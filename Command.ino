
void command_center()

{
  if(Esp_32=="RUN" && Mode!="F" )   //if No Error  then execute

  {

  

   sending(Actual_Operation_mode_of_ODU,Read,data_HB,data_LB);
  // delay(10);
   sending(ODU_Ambient_temp_Ta,Read,data_HB,data_LB);
   //delay(10);
   sending(Liquid_Line_temp_Te,Read,data_HB,data_LB);
   //delay(10);
   sending(Discharge_temp_To,Read,data_HB,data_LB);
   delay(10);
   sending(Suction_temperature_Ts,Read,data_HB,data_LB);
  

   sending(AC_voltage,Read,data_HB,data_LB);
  // Serial.printf("Sending command Ac_voltage=%i\n",AC_voltage);
   //delay(10);
   sending(DC_voltage,Read,data_HB,data_LB);
  // Serial.printf("Sending command DC_voltage=%i\n",DC_voltage);
   //delay(10);
  
   sending(Fault_code,Read,data_HB,data_LB);
  // Serial.printf("Sending command Fault_code=%i\n",Fault_code);
  // delay(10);
   sending(Speed_limiting_code,Read,data_HB,data_LB);
  // Serial.printf("Sending command Speed_Limiting=%i\n",Speed_limiting_code);
  // delay(10);
   sending(Real_frequency,Read,data_HB,data_LB);
  // Serial.printf("Sending command Real_freguency=%i\n",Real_frequency);
  // delay(10);
   sending(Target_frequency,Read,data_HB,data_LB);
  // Serial.printf("Sending command Target_frequency=%i\n",Target_frequency);
  // delay(10);
   // sending(Defrosting_status,Read,data_HB,data_LB);
   //delay(10);
   //sending(Manual_4Way,Read,data_HB,data_LB);
   //Serial.printf("Sending command mnuaal rv =%i\n",Manual_4Way);
   //delay(10);
   sending(Manual_4Way,Read,data_HB,data_LB);
   //delay(10);
   sending(Manual_fan_speed,Read,data_HB,data_LB);

    sending(Supply_current,Read,data_HB,data_LB);
   //Serial.printf("Sending command Supply Current=%i\n",Supply_current);
  // delay(10);
   sending(Compressor_current,Read,data_HB,data_LB);
 //  Serial.printf("Sending command Compressor_Current=%i\n",Compressor_current);
  // delay(10);

  }

}


