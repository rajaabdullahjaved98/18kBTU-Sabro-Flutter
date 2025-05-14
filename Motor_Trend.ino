// // -5 is higher than -6, or -6 is lower then -5
// Define arrays to store observed data
/* ind=0;
        TR1=0;
        TR2=0;
        TR3=0;
        TR4=0;
        TR5=0;*/


float Suction_Temp_data[30];
float Delta_Temp_data[30];
float Discharge_Temp_data[30];
float Coil_sensor_data[30];

void Trend_Ckh()

{
  // If Checked//
  if ((((Mode == "H" || Mode == "A") && (Auto_Temp == "H"))) && (OD_Motor == "H_ON") && (OD_Motor_Status == "ON") && (Delta_Achived == "NO") && (Protocol_Run == 0) && (CMW_Wire == "OK"))  // Heating Outdooe motor Fault
  {

    if ((Suction_Temp <= -5) && (Defrost_Check == "Yes")) {

      Trend();
      ODMS_Error = "Heating_ODMS_Warning";
       R_Data.SL_Code=9;
    }

    if ((Suction_Temp >= 1) && (Defrost_Check == "Yes")) {

      ODMS_Error = "None";
      memset(Suction_Temp_data, 0, sizeof(Suction_Temp_data));
      memset(Delta_Temp_data, 0, sizeof(Delta_Temp_data));
      memset(Discharge_Temp_data, 0, sizeof(Discharge_Temp_data));
      memset(Coil_sensor_data, 0, sizeof(Coil_sensor_data));

      ind = 0;
      TR1 = 0;
      TR2 = 0;
      TR3 = 0;
      TR4 = 0;
      TR5 = 0;
      FT = 0;
       R_Data.SL_Code=0;
    }
  }
}

void Trend()

{

  Suction_Temp_data[ind] = Suction_Temp;
  Delta_Temp_data[ind] = Delta_Temp;
  Discharge_Temp_data[ind] = Discharge_Temp;
  Coil_sensor_data[ind] = Coil_sensor;

  // Check if  Suction_Temp has dropped below -5 and reached -10

  // Print observed data
  Serial.println("*********************************************************Observed data********************************************Start************");
  for (int i = 0; i < ind; i++) {
    Serial.print(" Suction_Temp: ");
    Serial.print(Suction_Temp_data[i]);
    Serial.print(", Delta_Temp : ");
    Serial.print(Delta_Temp_data[i]);
    Serial.print(", Discharge_Temp: ");
    Serial.print(Discharge_Temp_data[i]);
    Serial.print(", Coil_sensor: ");
    Serial.println(Coil_sensor_data[i]);
  }

  // Check trend of other variables
  Serial.println("Trend of other variables:");

  if (Suction_Temp_data[ind - 1] < Suction_Temp_data[ind - 2]) {
    Serial.println("Suction_Temp_datais decreasing");
    TR1++;

  } else {
    Serial.println("Suction_Temp_datais not decreasing");
  }


  if (Delta_Temp_data[ind - 1] > Delta_Temp_data[ind - 2]) {
    Serial.println("Delta_Temp  is increasing");
    TR2++;
  } else {
    Serial.println("Delta_Temp  is not decreasing");
  }
  if (Discharge_Temp_data[ind - 1] < Discharge_Temp_data[ind - 2]) {
    Serial.println("Discharge_Temp is decreasing");
    TR3++;
  } else {
    Serial.println("Discharge_Temp is not decreasing");
  }
  if (Coil_sensor_data[ind - 1] < Coil_sensor_data[ind - 2]) {
    Serial.println("Coil_sensor is decreasing");
    TR4++;
  } else {
    Serial.println("Coil_sensor is not decreasing");
  }
  Trend_Anyl();
  Serial.printf("index is =%i,Ft=%i\n", ind, FT);
  Serial.println("*********************************************************Observed data********************************************End************");

 

  ind++;

  if (ind > 25) {
    memset(Suction_Temp_data, 0, sizeof(Suction_Temp_data));
    memset(Delta_Temp_data, 0, sizeof(Delta_Temp_data));
    memset(Discharge_Temp_data, 0, sizeof(Discharge_Temp_data));
    memset(Coil_sensor_data, 0, sizeof(Coil_sensor_data));
    ind = 0;
    TR1 = 0;
    TR2 = 0;
    TR3 = 0;
    TR4 = 0;
    TR5 = 0;
    FT = 0;
  }
}


void Trend_Anyl() 
{
if(Suction_Temp <= -8.55)

{

 TR1=TR1+10;

}

if(Suction_Temp <= -10.00)

{

 TR1=TR1+30;

}

  FT = TR1 + TR2 + TR3 + TR4;

  if (ind>=2 && FT >= 30)

  {

    Serial.printf("***********************Confrim ODMS Not Working**********************\n");
     Errors_info[15] = 1;
  }

}

 
 
  void Motor_Chk_cooling()

  {
    if ((Mode == "C" || Mode == "D") || (Mode == "A" && Auto_Temp == "C") && (Delta_Achived == "NO") && (Protocol_Run == 0) && (CMW_Wire == "OK"))  // Cooling Mode Odms fault

    {

      if ((Discharge_Temp > 55) && (Liquid_Line_temp > 55))

      {

        Temp_DL = Discharge_Temp - Liquid_Line_temp;

        if (Temp_DL <= 15)

        {

          ODMS_Error = "Cooling_ODMS_Fault";
          R_Data.SL_Code=9;
        }

        if (Temp_DL > 15.1)

        {

          ODMS_Error = "None";
          bitWrite(Ble_8Bit5, 0, 1);
        }
      }
    }
  }
