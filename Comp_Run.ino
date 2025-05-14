
// delta achives also 25 but take more time as min Rpm 1500 && coil>38 motor on

// Protocol Run to 180 so in heating its enough time for 5000 RPM to make coil >38 as liquied line is -10 so defrost should avoid


float Max_Temp = 9;
float Min_Temp = .05;
uint16_t Comp_Cal_Rpm = 0;

//for 146 comperssor


uint16_t Max_Rpm = 4500;
uint16_t Min_Rpm = 960;
uint16_t Run_Rpm = 0;
uint16_t First_RPM = 3600;






// for 125 comperssor
/*
uint16_t Max_Rpm = 3000;
uint16_t Min_Rpm = 1000;
uint16_t Run_Rpm = 0;
uint16_t First_RPM = 2000;

*/









// Copmerssor Local Var
uint16_t Set_RPM = 0;
uint16_t Print_Set_RPM = 0;
uint8_t Comp_HB = 0X00;
uint8_t Comp_LB = 0X00;
uint16_t Last_RPM = 00;
uint16_t Curent_RPM = 00;
uint8_t Prot_Counter = 0;



//String Comperssor_RMode = "Start";

void Comp()

{
  
if ((operation_mode==true) && (Start_Delay == "No") && (Comprun == true))
 {
     Run_Rs();
     Comprun = false;
     Set_Temp = CT;
       Run_Rpm = constrain(Run_Rpm, Min_Rpm, Max_Rpm);
      Comp_run(Run_Rpm);
    //  Serial.printf("********************************************************in op mode*****************************\n\n\n");
      Running_Mode = "Normal_Mode";
         bitWrite(Ble_8Bit3, 7, 1);  // Normal
      bitWrite(Ble_8Bit3, 6, 1);
      bitWrite(Ble_8Bit3, 5, 0);
     return;

 }

if ((Mode == "H" || Auto_Temp == "H") && (H_Bosster==true) && (Comperssor_Running_RPM >= 800))

{
    Comperssor_RMode = "Booster return";
   Comperssor_Pkrs_Mode="Booster return";

  return;
}

  if (((Mode == "C" || Mode == "D") || (Mode == "H" || Auto_Temp == "H")|| (Mode == "A" && Auto_Temp == "C")) && (Comprun == true)) 
  {  // if checked

    New_Run();
    Comprun = false;
  }
}




void New_Run()

{

   Run_Rpm = Min_Rpm + ((Delta_Temp - Min_Temp) * (Max_Rpm - Min_Rpm) / (Max_Temp - Min_Temp));
   Check_Temp_run();
   First_time();
    Comp_Cal_Rpm = Run_Rpm;
    Run_Rpm = constrain(Run_Rpm, Min_Rpm, Max_Rpm);
   Comp_run(Run_Rpm);

}

  void First_time()

  {
    if (Start_Delay == "Yes") 
  {
    Run_Rpm = First_RPM;
    Running_Mode = "First_Time";
     Comperssor_RMode = "FT";
   Comperssor_Pkrs_Mode="First_Time";
   bitWrite(Ble_8Bit3, 7, 1);  // First time
    bitWrite(Ble_8Bit3, 6, 1);
    bitWrite(Ble_8Bit3, 5, 1);
  }

    if (Start_Delay == "No")   // only runnuing mode
    {
      //Serial.printf("in Cooling  S_delay is no \n");
      Running_Mode = "Normal_Mode";
      bitWrite(Ble_8Bit3, 7, 1);  // Normal
      bitWrite(Ble_8Bit3, 6, 1);
      bitWrite(Ble_8Bit3, 5, 0);
    }
}

void  Check_Temp_run()

{
  if (Start_Delay != "No")   // only runnuing mode
    {
      return;
    }

 Run_Rpm = Min_Rpm + ((Delta_Temp - Min_Temp) * (Max_Rpm - Min_Rpm) / (Max_Temp - Min_Temp));
  Comperssor_RMode = "Normal in >1";
   Comperssor_Pkrs_Mode="Normal>1<9";
  if ((Mode == "H" || Auto_Temp == "H") && (Coil_sensor <= 40) && ( Comperssor_Running_RPM < 3600) && (Start_Delay == "No"))  // only for Heating mode
  {
    Run_Rpm = 3800;
    Run_Rpm = constrain(Run_Rpm, Min_Rpm, Max_Rpm);
    Comperssor_RMode = "Heating+100PM<42";
     Comperssor_Pkrs_Mode="Heating Bosster";
     H_Bosster=true;
     Heating_Booster.attach(300,Go_Booster);
 }
}



void Delta_Check() 
{
  
  //if ((Delta_Temp == 0) || (Delta_Temp < .01) && (Delta_Go==false))
  if ((Delta_Temp == 0 && Delta_Go == false) || (Delta_Temp < 0.01 && Delta_Go == false)) 
  {
    
    Comp_run(0);
    caliberated = false;
   Serial.printf("********************************In Delta function********************************************************\n\n\n");

    Motor("OFF");


    // sending(Manual_4Way, Write, data_HB, R_Valve_Of);
    Running_Mode = "Delta_Achived";
    bitWrite(Ble_8Bit3, 7, 0);  // Delata_Mode
    bitWrite(Ble_8Bit3, 6, 1);
    bitWrite(Ble_8Bit3, 5, 1);

    if (Start_Delay == "No" && Delta_Achived == "NO")

    {
      Start_Delay = "Wait";

    
    }
    Gas_err.detach();
    Gas_Err_Confirm.detach();
     if((Room_sensor >= -5) && (Room_sensor <= 80) &&  !isnan(Room_sensor)) 
    {
    flipper_Out_Door_Sensor_Timer.detach();
    Serial.printf("********************************In Delta ***********Outdoor Sensor Deaatch*********************************************\n\n\n");

    }
    flipper_ODST_Confirm.detach();
    Heating_Booster.detach();
    Delta_Achived = "YES";
    Pro_to = false;
    Protocol_Run = 1;
    bitWrite(Ble_8Bit1, 1, 1);  // delta Yes
    start = true;
     BRPM_counter=0;

    Comp_Cal_Rpm = 0;
   
     H_Bosster=false;
   SL_final=0;
   Dp_Final=0;
   Comperssor_Start_Timer(180);
   if (operation_mode==true)
   {

    BRPM==true;
   }

   Delta_Go=true;;/// Delta routine  execute on time

  }
}




void Comp_run(uint16_t Temp_CRPM)

{

 if ((Comperssor_Running_RPM >= 800) && (Pro_to == false))

  {
    Pro_to = true;
    flipper_Protocol_Delay.attach(180, Prot_Timer);
    Gas_err.attach(900, Gas_leak);  //Timer will run for 15 minutes 900 SEC
   
    Start_Delay = "Yes";
    flipper_Delay.attach(90, Delay);
    BRPM=true;
     BRPM_counter=0;
    Serial.printf("************************************ attach Pro,Gas,ODSt Timer**********************************************************\n");
  }

  Curent_RPM = Temp_CRPM;
  Last_RPM = Curent_RPM;
  Set_RPM = (Temp_CRPM) / 60;
  Print_Set_RPM = Set_RPM;
  Comp_HB = Set_RPM >> 8;
  Comp_LB = Set_RPM << 0;
  sending(Target_frequency, Write, Comp_HB, Comp_LB);
  delay(20);
  Set_RPM = 0;
}




void Delay() {

  //Serial.println("in delay **************************************");
  //Protocol_Run=1;
  //flipper_Protocol_Delay.attach(60,Prot_Timer);
  Start_Delay = "No";

  flipper_Delay.detach();
}


void Comperssor_Start_Timer(uint8_t CST_TIME)

{
  Start_Delay = "Wait_CST";

  Protocol_Run = 1;
  // Serial.print("value of port timer=");
  // Serial.println(PROT_TIME);
  //flipper_Protocol_Delay.attach(PROT_TIME,Prot_Timer); /// 3Min no errro check
  Comperssor_Start_timer = "ON";
  Motor_Timer = "ON";


  //flipper_Compressor_SINV_timer.attach(125,CST);  //  2 min for for Heat valve
  flipper_Compressor_SINV_timer.attach(CST_TIME, CST);  //  4.1 min for for Heat valve
}

void CST()

{
  flipper_Compressor_SINV_timer.detach();

  //flipper_Protocol_Delay.attach(60,Prot_Timer);
  Comperssor_Start_timer = "OF";

  Start_Delay = "Wait_CSTO";

  // when Compressor from Stop to Run after 3 min timer, runs start_delay yes mean Runs of 4500RPM for 1Min
  //flipper_Delay.attach(30,Delay); //  130 orginal This will ***********fault for heating give compressor Runs atleat 1min delay
  flipper_Motor_on.attach(10, Motor_Go);  // Inverter_timer 3min 5 sec,CST 2 min 10 sec, delta 130 is approx 60 sec after comperssor start.
}

void Motor_Go() {

  //Serial.println(" motor go *********************************************Timer off ***********************************************Motor timer off****");
  Motor_Timer = "OFF";
  Start_Delay = "Yes";

  flipper_Motor_on.detach();

  Serial.println(" Yes**************************firsttime buffer***********************Buffer clear Rx******");
}

void Deforst_Heating_timer()

{

  Defrost_Check = "Yes";

  flipper_Deforst_Check.detach();
}


void Prot_Timer()

{
  Serial.printf("\n In Prot_Timer********************************************************************************\n");
  Protocol_Run = 0;
  flipper_Protocol_Delay.detach();
}

void Go_Booster()

{

 H_Bosster=false;
Heating_Booster.detach();

}
