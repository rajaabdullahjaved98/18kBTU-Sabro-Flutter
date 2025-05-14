

float Temp_DL = 0;
int coil_Frozen = 0;




void OutDoor_Sensor_Error()  // Start working after approx 1Min

{

  indoor_Sensor();
  OutDoor_Sensor();
  // Serial.println("");
  // Serial.print("********************************************************************************************************************************************************");
  // Serial.println("");
  //Serial.printf("In OUTDOOR_Sensor_Error*******************************************************is cheking contonously timer 30 Sec**");
  // Serial.println("");
  // Serial.print("********************************************************************************************************************************************************");
  //  Serial.println("");


  if ((Esp_32 == "RUN") && (Mode != "F") && (Delta_Achived == "NO") && (Protocol_Run == 0) && (CMW_Wire == "OK"))

  {
    if ((Liquid_Line_temp <= -8) && (Mode == "H" || Auto_Temp == "H") && (Defrost_mode == "NO") && (Defrost_Check == "Yes"))  // -5 is higher than -6, or -6 is lower then -5

    {

      flipper_ODST_Confirm.attach(10, Out_Door_Sensor_Confirm);
      Error_Found = "Defrosting";
    }

    if ((Liquid_Line_temp >= -7.9) && (Defrost_Cycle_Complete == "Yes"))  // safe Limit ofcoil temp  above -5 i.e -4.9 to 80c is safe elimit

    {
      Defrost_mode = "NO";
       bitWrite(Ble_8Bit3,4,0);//bit written defrost mode is off
    }

    if ((Discharge_Temp >= 115) && (Discharge_Temp < 190.9))  // Error limit of condseer temp check with qamar
    {

      flipper_ODST_Confirm.attach(10, Out_Door_Sensor_Confirm);
      Error_Found = "Discharge Temp";
    }

    if (Discharge_Temp <= 70)  // safe Limit of condenser temp  above -5 i.e -4.9 to 80c is safe elimit
    {
      Errors_info[11] = 0;  // check in Lab & qamar
    }

    if ((Mode == "C" || Mode == "D" || Auto_Temp == "C") && (Liquid_Line_temp >= 65))  //  coil_chock or outdoor motor not working in cooling mode.
    {
      flipper_ODST_Confirm.attach(10, Out_Door_Sensor_Confirm);
      Error_Found = "ODMS Fault";
    }

    if ((Mode == "C" || Mode == "D" || Auto_Temp == "C") && (Liquid_Line_temp < 65)) {

      Errors_info[15] = 0;
    }

    if (Ac_volts > 275 || Ac_volts < 190)

    {
      flipper_ODST_Confirm.attach(10, Out_Door_Sensor_Confirm);
      Error_Found = "AC_Vault";
    }

    if (Ac_volts > 190 && Ac_volts < 275)  // Av volts min 190 max 275
    {
      Errors_info[12] = 0;
    }

    if (S_cuurent >= 12.0) {
      flipper_ODST_Confirm.attach(10, Out_Door_Sensor_Confirm);
      Error_Found = "AC_Curent";
    }


    if (S_cuurent < 10)

    {
      Errors_info[13] = 0;
    }


    if (Falut_Inv_code != 0 && Falut_Inv_code != 0xFF && Falut_Inv_code != 0x37 && Falut_Inv_code != 0x36 && Falut_Inv_code != 0x35) {
      flipper_ODST_Confirm.attach(10, Out_Door_Sensor_Confirm);
    }


  }  // end of if  outddor sennsor power on

}  // end of  void outdoor sensor

void Out_Door_Sensor_Confirm() 
{
  flipper_ODST_Confirm.detach();
  Serial.println("");
  Serial.print("********************************************************************************************************************************************************");
  Serial.println("");
  Serial.print("***********************outdoor sensor Erro has found*******************************Checking************************************************************************Confirm");
  Serial.println("");
  Serial.print("********************************************************************************************************************************************************");
  Serial.println("");

  if (Esp_32 == "RUN" && Mode != "F" && Delta_Achived == "NO") {

    if ((Liquid_Line_temp <= -8) && (Mode == "H" || Auto_Temp == "H") && (Defrost_mode == "NO" && Defrost_Check == "Yes"))  // -5 is higher than -6, or -6 is lower then -5
    {
      Serial.println("In Defroating*********************************************************");
      Mode_Change = "Yes";

      Defrost_mode = "YES";

      Defrost_Cycle_Complete = "NO";
        bitWrite(Ble_8Bit3,4,1);//defrost mode ON
      bitWrite(Ble_8Bit3,3,0);//Defrost cycle is NO
    }
    if ((Discharge_Temp >= 115) && (Discharge_Temp < 190.9))  // Error limit of condsber temp
    {
      Errors_info[11] = 1;
    }
    if ((Mode == "C" || Mode == "D" || Auto_Temp == "C") && (Liquid_Line_temp > 65))  //  coil_chock or outdoor motor not working in cooling mode.
    {
      Errors_info[15] = 1;
    }

    if (Ac_volts > 275 || Ac_volts < 190) {
      Errors_info[12] = 1;
    }
    if (S_cuurent >= 12.0) {
      Errors_info[13] = 1;
    }


    if (Falut_Inv_code != 0 && Falut_Inv_code != 0xFF && Falut_Inv_code != 0x37 && Falut_Inv_code != 0x36 && Falut_Inv_code != 0x35) {
      Errors_info[24] = 1;  // IB fault
    }

}  // end of if  outddor sennsor power on
}  // end of  void outdoor sensor conform


void indoor_Sensor()

{

  if ((Esp_32 == "RUN") && (Mode != "F")) 
  {


    if (Room_sensor <= -40 || isnan(Room_sensor) || Room_sensor >= 100) {
      Errors_info[0] = 1;  //Error[0]=1 Means Room Sensor is Short/Disconnected
    }
    if (Room_sensor >= -5 && Room_sensor <= 80) {
      Errors_info[0] = 0;
    }
    if (Coil_sensor <= -40 || isnan(Coil_sensor) || Coil_sensor >= 100) {
      Errors_info[1] = 1;  // Error[1]=1 Means Coil Sensor is Short/Disconnected
    }
    if (Coil_sensor >= -20 && Coil_sensor <= 80) {
      Errors_info[1] = 0;
    }

    if (Coil_sensor <= -8.00 && Esp_32 == "RUN" && (Mode == "C" || Mode == "D" || Auto_Temp == "C")) {
      Errors_info[2] = 1;  // Error means Indoor coil is frozen in cooling mode but heating it will ignore so unit can run even coil is frozen
    }

    if (Coil_sensor >= 0.00 && Coil_sensor <= 80 && Esp_32 == "RUN" && (Mode == "C" || Mode == "D" || Auto_Temp == "C")) {
      Errors_info[2] = 0;
    }

    if (Coil_sensor >= 65 && Esp_32 == "RUN" && (Mode == "H" || Auto_Temp == "H"))  //  indoor motor not working or coil over heat
    {
      Errors_info[5] = 1;
    }

    if ((Coil_sensor >= 0.00 && Coil_sensor < 65) && Esp_32 == "RUN" && (Mode == "H" || Auto_Temp == "H")) {
      Errors_info[5] = 0;
    }


  }  // end of if
}



void OutDoor_Sensor()  // This fuction check Outdoor sensor are fine
{
  if (Esp_32 == "RUN" && Mode != "F" && Delta_Achived == "NO" && CMW_Wire == "OK") {
    if (Falut_Inv_code == 0 && (Discharge_Temp != -64 && ODU_Ambient_Temp != -64 && Liquid_Line_temp != -64 && Suction_Temp != -64)) {
      Errors_info[21] = 0;
      Errors_info[22] = 0;
      Errors_info[23] = 0;
      Errors_info[25] = 0;

      //  Serial.printf("ODS making 0******************************************************\n");
    }
    if (Falut_Inv_code == 0) {
      Errors_info[24] = 0;
    }
    if (Falut_Inv_code == 0x35 || ODU_Ambient_Temp == 191 || ODU_Ambient_Temp == -64)  // 35h,36h,37h //otdoor coil temp short

    {
      Errors_info[21] = 1;
      //  Serial.printf("ODS making 1**************************************************1****\n");
    }

    if (Falut_Inv_code == 0x36 || Liquid_Line_temp == 191 || Liquid_Line_temp == -64)  // 35h,36h,37h // Suction Temp Short
    {
      Errors_info[22] = 1;
    }
    if (Falut_Inv_code == 0x37 || Discharge_Temp == 191 || Discharge_Temp == -64)  // 35h,36h,37h discharge temp Short
    {
      Errors_info[23] = 1;
    }

    if (Suction_Temp == 191 || Suction_Temp == -64)  // 35h,36h,37h discharge temp Short
    {
      Errors_info[25] = 1;
    }
  }
}




void Gas_leak()

{

  if (Esp_32 == "RUN") {
    Serial.println("in Gas_Leak *****************Error_Tab*****************************************************************************************************************");

    if (Delta_Achived == "NO" && Mode != "F") 
    {
      if ((Coil_sensor >= 21) && (Comperssor_Running_RPM >= 2500 && Comperssor_Running_RPM <= 5300) && (Mode == "C" || Mode == "D" || Auto_Temp == "C")) {
        Gas_Err_Confirm.attach(300, Gas_Leak_Confirm);  //Timer will run for 5 minutes 300 SEC
                                                        //  Serial.println("in confirming *****************Error_*****************************************************************************************************Gas Error************");
      }
      if ((Coil_sensor < 21) && (Mode == "C" || Mode == "D" || Auto_Temp == "C")) {
        Errors_info[3] = 0;
      }
      if ((Coil_sensor <= 20) && (Comperssor_Running_RPM >= 2500 && Comperssor_Running_RPM <= 5300) && (Mode == "H" || Auto_Temp == "H")) {
        Gas_Err_Confirm.attach(300, Gas_Leak_Confirm);  //Timer will run for 5 minutes 300 SEC
                                                        // Serial.printf("in confirming **Heatring***************Error_*****************************************************************************************************Gas Error*Heating***********\n");
      }
      if ((Coil_sensor >= 20.1) && (Mode == "H" || Auto_Temp == "H")) {
        Errors_info[3] = 0;
      }
         Gas_Warning();

    }
  }
}


void Gas_Leak_Confirm()

{
  Gas_Err_Confirm.detach();
  if ((Coil_sensor >= 21) && (Comperssor_Running_RPM >= 2500 && Comperssor_Running_RPM <= 5300) && (Mode == "C" || Mode == "D" || Auto_Temp == "C")) {
    Errors_info[3] = 1;  //E6 Error means There is no Gas in compressor this errro Gas_error is attach in Temp_intilaize()
  }
  if ((Coil_sensor <= 20) && (Comperssor_Running_RPM >= 2500 && Comperssor_Running_RPM <= 5300) && (Mode == "H" || Auto_Temp == "H")) {
    Errors_info[3] = 1;  //E6 Error means There is no Gas in compressor
  }
}

void Gas_Warning()


{
  if ((Coil_sensor >= 21) && (Comperssor_Running_RPM >= 900 && Comperssor_Running_RPM <= 2000) && (Mode == "C" || Mode == "D" || Auto_Temp == "C")) 
{
  R_Data.SL_Code=5;
}
if ((Coil_sensor < 21) && (Comperssor_Running_RPM >= 900 && Comperssor_Running_RPM <= 2000) && (Mode == "C" || Mode == "D" || Auto_Temp == "C")) 
{
R_Data.SL_Code=0;
}

if ((Coil_sensor <= 20) && (Comperssor_Running_RPM >= 900 && Comperssor_Running_RPM <= 2000) && (Mode == "H" || Auto_Temp == "H")) 
{
  R_Data.SL_Code=5;
}

if ((Coil_sensor > 20) && (Comperssor_Running_RPM >= 900 && Comperssor_Running_RPM <= 2000) && (Mode == "H" || Auto_Temp == "H")) 
{
  R_Data.SL_Code=0;

}
}



void Protocol_Confirm()  // is called from send_inv function every time data send


{
  if (Mode == "F" || CMW_Wire == "NOT_OK") {

    return;
  }


  if ((inverter_bytes[6] == inverter_Sdata[6]) && (inverter_bytes[7] == inverter_Sdata[7]))

  {

    //Serial.printf("Inverter_Bytes[6]%x && Inverter_Bytes[7]%x\n",inverter_bytes[6],G1,inverter_bytes[7],G2);

    Errors_info[16] = 0;
    //  Serial.printf("Data_Protocol_confirmed_**********************************=%i\n",DDPNC);
    DDPNC = 0;
  }


  if (((inverter_bytes[6] != inverter_Sdata[6]) || (inverter_bytes[7] != inverter_Sdata[7])) && (Protocol_Run == 0)) {
    DDPNC++;
    Serial.printf("Data_Protocol_not_confirmed_counting=%i,Protocl_Run=%i\n", DDPNC, Protocol_Run);
    // Error();
    if (DDPNC >= 20) {

      Error();
    }
  }

  inverter_Sdata[1] = 0x00;
  inverter_Sdata[3] = 0x00;

  inverter_Sdata[4] = 0x00;  // make 0x00 so other data remsins same
  inverter_Sdata[5] = 0x00;
}



void Error()


{
  Serial.print("Error in data recived=");
  Errors_info[16] = 1;

  for (int n = 0; n < 8; n++) {



    Serial.print(data_seq[n]);
    Serial.print("=0x");

    Serial.print(inverter_bytes[n], HEX);
    Serial.print(",");
  }
  Serial.println("");
}
