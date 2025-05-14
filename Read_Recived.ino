void esp_rec_data() {

  dump_Rx();



  if (Serial2.available() > 0) {
    // Serial.print("RX2_w:=");
    for (int n = 0; n < 8; n++) {

      inverter_bytes[n] = Serial2.read();  // Read a Byte
      // Serial.print(inverter_bytes[n],HEX);
      //Serial.print(",");
    }

    // Serial.println("            :Data_Write_Recived");
  }
}



void esp_read_data()


{

  dump_Rx();

  if (Serial2.available() == 0) {
    CMWire_Break++;
    Serial.printf("\nCM_WireBreak_Counter is=%i\n", CMWire_Break);
    if (CMWire_Break >= 50) {
      Serial.printf("CM_Wire is Break=%i\n", CMWire_Break);
      CMWire_Break = 0;
      Errors_info[20] = 1;
      CMW_Wire = "NOT_OK";
    }
  }

  if (Serial2.available() > 0) {
    CMWire_Break = 0;
    // Serial.print("RX1:=");

    for (int n = 0; n < 7; n++) {


      inverter_bytes[n] = Serial2.read();  // Then: Get them.
                                           /*  if((n!=2))
          {
        Serial.print(Read_data[n]);
       Serial.print("=");
         
      // Serial.print("data recived");
        Serial.print(inverter_bytes[n],HEX);
        
        Serial.print(",");
        }*/
    }

    //    Serial.println("                :Data Read Recived");
    //  Serial.println("");
  }



  int t1 = inverter_bytes[3] << 8;
  int t2 = inverter_bytes[4] << 0;
  float Temp_Temp;
  String staus = "OFF";



  if (inverter_Sdata[3] == Suction_temperature_Ts || inverter_Sdata[3] == Liquid_Line_temp_Te || inverter_Sdata[3] == Discharge_temp_To || inverter_Sdata[3] == ODU_Ambient_temp_Ta) {



    Temp_Temp = t1 | t2;
    if (Temp_Temp >= 32768)  // Convert is Temp
    {
      Temp_Temp = Temp_Temp - 65536;
    }
    Temp_Temp = Temp_Temp / 10;

    if (inverter_Sdata[3] == Suction_temperature_Ts)

    {


      Suction_Temp = Temp_Temp;

      // Serial.print(" Coil_Temp=");
      // Serial.print(coil_temp);
    }


    if (inverter_Sdata[3] == Liquid_Line_temp_Te)

    {

      Liquid_Line_temp = Temp_Temp;

      // Serial.print(" Liquid_Line_temp=");
      // Serial.print(Liquid_Line_temp);
    }

    if (inverter_Sdata[3] == Discharge_temp_To)

    {

      Discharge_Temp = Temp_Temp;

      //Serial.print(" Condenser_Temp=");
      //Serial.print(Discharge_Temp);
    }

    if (inverter_Sdata[3] == ODU_Ambient_temp_Ta)

    {

      ODU_Ambient_Temp = Temp_Temp;

      // Serial.print(" ODU_Ambient_Temp=");
      // Serial.print(ODU_Ambient_Temp);
    }





  }  /// end of coil sensors if

  if (inverter_Sdata[3] == Actual_Operation_mode_of_ODU) {

    if (t2 == 0) {

      Cond_mode = "Of";
    }
    if (t2 == 1) {

      Cond_mode = "Cool";
    }
    if (t2 == 2) {

      Cond_mode = "Heat";
    }

  }  /// enf of if mode inv


  if (inverter_Sdata[3] == AC_voltage)

  {
    //Serial.println("checking Ac voltage");
    Temp_Temp = t1 | t2;
    Ac_volts = Temp_Temp;
    Ac_volts = Ac_volts + 8.6;
  }  // enf Ac voltage

  if (inverter_Sdata[3] == DC_voltage)

  {
    //Serial.println("checking Ac voltage");
    Temp_Temp = t1 | t2;
    Dc_Volts = Temp_Temp;
  }  // enf Dc voltage

  if (inverter_Sdata[3] == Supply_current)

  {

    // int t1=inverter_bytes[3]<<8;
    // int t2 =inverter_bytes[4]<<0;

    // Serial.printf("inverter_bytes[3]=%i\n",inverter_bytes[3]);
    // Serial.printf("inverter_bytes[4]=%i\n",inverter_bytes[4]);


    //  Serial.println("checking Ac Curent");
    //  Serial.printf("::t1=%i,t2=%i\n",t1,t2);


    Temp_Temp = t1 | t2;
    // Serial.print(t1);
    // Serial.print(t2);
    // Serial.printf("::Temp_Temp=%g\n",Temp_Temp);
    Temp_Temp = Temp_Temp / 10;
    S_cuurent = Temp_Temp;
    S_cuurent = S_cuurent + .08;
    // Serial.printf("S_curent in command+.20=%g\n",S_cuurent);
    Curent_Adjusment();
  }  // enf supply current


  if (inverter_Sdata[3] == Compressor_current)

  {
    //Serial.println("checking Ac voltage");
    Temp_Temp = t1 | t2;
    Temp_Temp = Temp_Temp / 10;
    Comp_current = Temp_Temp;

  }  // enf comperssor current


  if (inverter_Sdata[3] == Speed_limiting_code)

  {

    if (t2 == 0) {

      Inv_Error = "None";
      R_Data.SL_Code = 0;
    }

    if (t2 == 1) {

      Inv_Error = "Input_cuurent";
      R_Data.SL_Code = 1;
    }

    if (t2 == 2) {

      Inv_Error = "Output_current";
      R_Data.SL_Code = 2;
    }


    if (t2 == 3) {

      Inv_Error = "Ipm_Temp";
      R_Data.SL_Code = 3;
    }

    if (t2 == 4) {

      Inv_Error = "Over_Modualtion";
      R_Data.SL_Code = 4;
    }

    if (t2 == 5) {

      Inv_Error = "Discharge_Temp_High";
    }

    if (t2 == 6) {

      Inv_Error = "Coil_Temp_High";
    }



  }  // end of Speed limit


  if (inverter_Sdata[3] == Real_frequency)

  {

    Temp_Temp = t1 | t2;
    Comperssor_Running_RPM = Temp_Temp * 60;
  }

  if (inverter_Sdata[3] == Target_frequency)

  {

    Temp_Temp = t1 | t2;
    Comperssor_send_Rpm = Temp_Temp * 60;
  }



  if (inverter_Sdata[3] == Fault_code)

  {
    Temp_Temp = t1 | t2;
    Falut_Inv_code = Temp_Temp;
  }




  if (inverter_Sdata[3] == Manual_4Way) {

    if (t2 == 0) {

      Maunal_Rv = "OF";
    }
    if (t2 == 1) {

      Maunal_Rv = "ON";
    }
  }

  if (inverter_Sdata[3] == Manual_fan_speed) {

    if (t2 == 0) {


      OD_Motor_Status = "OFF";
      bitWrite(Ble_8Bit2, 0, 0);  // odms OFF
    }
    if (t2 == 1) {

      OD_Motor_Status = "ON";
      bitWrite(Ble_8Bit2, 0, 1);  // odms On
    }
  }



}  // End of void


void Curent_Adjusment()

{
  if (OD_Motor_Status == "ON" && Power == "ON")
  {
   S_cuurent = S_cuurent + .34;  // my Home not using this// changing from .46
  }

  if ((Mode == "H") || (Mode == "A" && Auto_Temp == "H"))
  {
   S_cuurent = S_cuurent + .032;
  }

  if (Fan_Status== "L" || (Fan_Status == "A" && Delta_Temp >= 0 && Delta_Temp < 3)) 
  {
     S_cuurent = S_cuurent + .18;
  }

 if (Fan_Status == "M" || (Fan_Status == "A" && Delta_Temp >= 3 && Delta_Temp < 6)) 
 {
  S_cuurent = S_cuurent + .19;
 }

  if (Fan_Status== "H" || (Fan_Status == "A" && Delta_Temp >= 6)) 
 {
   S_cuurent = S_cuurent + .20;
  }

  /*if  ((Comperssor_Running_RPM<2400) && (Comperssor_Running_RPM>1100))
  {

  S_cuurent = S_cuurent - .24;

  }


 if ((Comperssor_Running_RPM>2400) && (Comperssor_Running_RPM<4000) && (Mode=="C"))
 {
   S_cuurent = S_cuurent - .12;
 }*/


F_Current = S_cuurent;


}