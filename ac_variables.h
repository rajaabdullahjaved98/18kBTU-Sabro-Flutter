#include <stdint.h>
#ifndef AC_VARIABLES_H
#define AC_VARIABLES_H





TaskHandle_t Task1;
TaskHandle_t Task2;
TaskHandle_t Task3;
TaskHandle_t Task4;
TaskHandle_t Task5;
TaskHandle_t Task6;

SemaphoreHandle_t xSemaphore = NULL;


Ticker flipper;      // ticker is software timer to avoid hardware timer mismatch
Ticker flipper_Delay;  // Delta for starting comperssor delay use in comp void delta
Ticker flipper_Compressor_SINV_timer;    // Check compersor inverter timer 3min has passed
Ticker flipper_Ir_Data_timer;   // Timer to recived data with inteprt has got data
Ticker flipper_Deforst_Check;  // // To Make sure now Defrost can work in Heating_Control()
Ticker flipper_Out_Door_Sensor_Timer; // Timer for Outdoor sendor
Ticker flipper_ODST_Confirm;
Ticker  Gas_err;       //Timer for Gas leak Error
Ticker Gas_Err_Confirm;  
Ticker flipper_Err;             // in error Led to start blinking when found Error
Ticker flipper_PButton;          // in emergency  button start or off
Ticker flipper_Protocol_Delay;   // use  for protocl works after 1 min so noise can control
Ticker flipper_Motor_on;
Ticker flipper2;     //Ton setting
Ticker flipper3;     // Tof Setting
Ticker ShutDown_Timer;
Ticker Comp_Control_Timer;
Ticker Heating_Booster;

String Send_data0="";




// Error var

//bool err = false;   // This will true one time when any eeror occur in Error_array & then become true so  flipper_Err.attach_ms(Time_Del,Led_ERR); Can exectute
bool start = false;   //  use in delta achuived & delta
bool Delta_Go=false;
//



// String  Varaibles
String Power="OFF";          // This variable's task is to check whether the Remote is 'ON' or 'OFF' using "AC_ON / AC_OFF" operations.
String Swing="OF";                 // This variable's task is to set the swing to the desired position using "Sw_START / Sw_STOP" operations.
String Fan_Status="M";             // This variables's task is to set the indoor fan speed to the desired setting using "Auto/Low/Medium/High" opeartions.
String  Mode = "C";
String Mode_Change="NO";
String L_Auto_Temp;
String Delta_Achived="NO";
String Running_Mode="PStop_Mode";
String Defrost_mode="NO"; 
String Defrost_Cycle_Complete="Yes";               // var to check defrost has achived in winter
String Defrost_Check="Yes";
String Fan_Running_Mode="N";
String Stepper_Running_Mode;
String Error_Found="None";
//String EP="NO";                                   // Use in Stop function for check Protco break or other Error
String Auto_Temp = "C";                // This variable is the temperature difference for "auto Mode" bcz in this mode room temperature is greater than set temperature.
String T_Swing="NULL";                 // Use in Swing Stop in Heating control to hold Temp data of Swing T_Swing
String OD_Motor="OFF";                 // in control center to tell ooutdoor motor on or off which control command
String OD_Motor_Status="OFF";
String Print_Error= "None";            // used in print
String Stop_Stop="No";              // main variables if any error occur stop_stop="yes"
String  Start_Delay="wait_Reset";   // This is start Dealy when power on first time
String Cond_mode="Of";        // give which mode inverter is ruuning data is feed from read/rereived actual mode of operation
String Maunal_Rv="OF";        // ? have to check
String   Inv_Error="None";    // check inverter Error
String Comperssor_Start_timer="OF"; // cs copmerssor Stop
String Last_Err="0";                  // use in print center
//String Current_Err="0";
String Esp_32="WAIT";
String L_Mode;                //chercking mode has changed so compressor can run 4500

String ML_Power="Setup";   // check id power on so comerssor can run 4500

String Motor_Timer="ON";
String CMW_Wire="OK";
String Fan_Safe="YES";

String ODMS_Error="None";
String Comperssor_RMode = "Start";
String Comperssor_Pkrs_Mode = "Start";



String nameString;

uint8_t Saving_Mode=0;;                      // Error Proirty
uint8_t Power_var=0;       // used in main loop for on & off swing runs only one time used Stepper_Err_led
uint8_t Protocol_Run=1;
uint8_t Error_Num;
// Heating Swing varibale
uint8_t H_S=0;
uint8_t H_T=0;
uint8_t DDPNC=0;

uint8_t Ble_8Bit1;
uint8_t Ble_8Bit2;
uint8_t Ble_8Bit3;
uint8_t Ble_8Bit4;
uint8_t Ble_8Bit5;
uint8_t Errors_No=0; // used in Err led
uint8_t CMWire_Break=0;
uint8_t new_data1;  // used in Espnow

uint8_t ind = 0;
uint8_t TR1=0;
  uint8_t  TR2=0;
  uint8_t  TR3=0;
  uint8_t  TR4=0;
   uint8_t TR5=0;
   uint8_t FT=0;


uint8_t Room_Sensor_counter=0;
uint8_t first_time=0;
bool R1,R2,R3;     // used in espnow
bool Pro_to=false;
bool Comprun=true;

bool four_byte_bool_f=false;
bool pkr_set_temp = true;

 // Comperssor Variables Global
 uint16_t Comperssor_Running_RPM=00;
   uint16_t Comperssor_send_Rpm=00;
   bool H_Bosster=false;
// End Comperssor Var






float Set_Temp=22.00;
float Set_Lcd_Temp;                 // This variables's task is to set the desired temperature for AC starting from "16 degree to 30 degree".
float Coil_sensor = 25.5;                // indoor coil sensor data
float Room_sensor = 23.5;
float Delta_Temp = 0;  //     This variable is the temperature difference for "Cool Mode" bcz in this mode room temperature is greater than set temperature.
float    Suction_Temp=0; 
float    Liquid_Line_temp=0;
float    Discharge_Temp=0;
float    ODU_Ambient_Temp=0;
float    Ac_volts=0;
float    Dc_Volts=0;
float    S_cuurent=0;
float    F_Current=0;
float    Comp_current=0;
 static uint8_t n=0;
 static float rs=0;
 
uint32_t   LTon_Sec_Left=0;
uint32_t   NTon_Sec_Left=0;

uint32_t   Ton_Sec_Left=0;
uint32_t    Tof_Sec_Left=0;



//

//New_run Rs variables
float peak_unit_rate = 87;// office
float off_peak_unit_rate = 73; // office

//float peak_unit_rate = 48;  // Home
//float off_peak_unit_rate = 41.68; // Home
uint8_t peak_time_start = 19;
uint8_t peak_time_stop = 23;
float Running_Peak=1;
float Currenr_Energy_cost=0;
float Target_Energy=0;
float Money_Equal=0;



float Target_Rpm=0;
float Cutomer_Rs=50;
float LC_RS=0;
float Last_Rs=0;
float Current_Rs_hour;
bool operation_mode = false;// false means ac is operation conventionally in set temp mode true means it is working in pkr mode 
float CT=28;
uint8_t price_range_low = 10;
uint8_t price_range_high = 90;
uint16_t Max_RPM_PKRS = 4200;
uint16_t Min_RPM_PKRS = 1000;
uint16_t Base_RPM_PKRS;
uint16_t RS_RPM=2600;
uint16_t RS_LockRPM=0;
bool BRPM=true;
uint8_t BRPM_counter=0;
bool E_cal=false;

bool TPM = false;
bool SPM = false;
bool small_screen_request = false;
uint8_t small_screen_mac[6];
float single_phase_unit_cost;
uint8_t once = 0;
uint8_t Met_Type=0;
bool Met_save=false;
float DP_New=0;
float Dp_Final=0;
float SL_New=0;
float SL_final=0;
bool Name_Save=false;



// Eeprom varaibles

String EEP="NO"; // Varaible for if yes write EEprom current data

int Eeprom_add_Power=0;
int Eeprom_add_Swing=4;
int Eeprom_add_Fan=8;
int Eeprom_add_Mode=12;
int Eeprom_add_Temp=16;
int Eeprom_add_Eco=24;
int Eeprom_add_OP_Mode=26;
int Eeprom_add_Cutomer_Rs=30;
int Eeprom_add_Name=40;



// End of EEprom Variables











 




// Timer Global varabiles

String Timer_on="OF"; // It will be on when IR reccvied timer on command
String Timer_of="OF"; // // It will be on when IR reccvied timer on command

String Ton_Set="No";   // means timer is activated
String Tof_Set="No";  // means timer is activeted
String MTON="NO";

String IR_Timer_data="No"; // yes means data of timer is coming is use in IR so other temp,fan data can ignore only Recived timer data
String IR_Timer_Cancel="NO";
uint8_t F_Hour;  // used to calulate time on/off hour in Ir fuction & Timer_clock
uint8_t F_Min;   // // used to calulate time on/off Min  in Ir fuction & Timer_clock
int second=1; // used for flipper timer to activate after 1 sec
uint32_t Timer_Fsecond = 0;    // used for Timer Fsec caluation
uint32_t Ton_sec;    // 
uint32_t Tof_sec;
uint16_t Garbage_counter=0;
uint16_t Garbage_counter2=0;
uint16_t Noise_Counter=0;
//uint8_t Lcd_Timon=0;


// timer var ends here

// Stepper variables


uint16_t S_Home=800;
uint16_t S_Open=10;
uint16_t S_Swing=500;

// stepper var ends here





//E_Data[]=E0..E10
//E_Data1[]=F0..F9
//E_Data2[]=H0..H9








  unsigned long Time_Total_s;
   unsigned long Time_Total_e;
   unsigned long Time_Total_c;
    unsigned long Timer_On_Lc;
    unsigned long Timer_On_Cc;

  //*************************************************PM Var Starts Here*****************************************************************//



  // Time & Date set*******************************************************************************************************************************
  uint8_t Sec_Rtc=0;
  uint8_t Min_Rtc=03;
  uint8_t Hour_Rtc=21;
  uint8_t day_Rtc=9;
  uint8_t month_Rtc=12;
  uint16_t year_Rtc=2024;
  uint8_t Week_Day=0;

  // Time & Date set*******************************************************************************************************************************

// Pressure var

float previous_discharge_temp;
float current_discharge_temp;
float discharge_previous_psi;
float discharge_current_psi;

// end pressure


uint8_t peerMAC_broad_Mac[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
uint8_t broadcastAddress[6];

// EEPROM Variables Here

// Define constants
int EEPROM_ADD_Hour = 100;
int EEPROM_ADD_Meter_Start = 70;
int EEPROM_ADD_Day = 500;
int EEPROM_ADD_Month = 900;
#define EEPROM_SIZE 2048 // This is 1-Byte
bool store=false;
#define addressmac 1550

// EEPROM VAR Ends here

// Energy Var Starts herer
float Energy;
 float Min_power = 0.0;
 float Energy_Min = 0.0;
  float Energy_Hour=0;
  float Energy_Day=0;
  float Energy_Month=0;
  float energy_day_peak;
  float energy_month_peak;
   float Run_Energy_Hour=0;
  float Run_Energy_Day=0;
  float Run_Energy_Month=0;

  float EE_Hour[25];
  float EE_Day[33];
  float EE_Month[14];
  float EE_Day_Peak[33];
  float EE_Month_Peak[14];

  uint8_t Lenth_Bytes=4;

 float Temp_Hour,Temp_Day,Temp_Month,Temp_Day_P,Temp_Month_P;

 //bool Power_OFF=false;

 String In_Error="Hello";


 


uint8_t LH,LD,LM=0;
int LY=0;

//

  uint8_t RTC_Err=0;
  uint32_t POM_RESET;
  uint8_t CTime=0;

bool ir_interrupt_detach= false;
unsigned long ir_time_check;
bool caliberated = false;

////// MQTT AND WIFI VARIABLES //////
String routerSSID = "";
String routerPASS = "";
String deviceName = "ESP_AP";

const char* ssid = "Sabro_design";
const char* password = "STPL@sabro";

const char* mqttServer = "192.168.18.104";
const uint16_t mqttPort = 1883;
const char* mqttUser = "test_device";
const char* mqttPassword = "Test1234";

String mac;
bool isInternetAvailable = false;
bool isMQTTConnected = false;
bool shouldAttemptWiFi = false;
String mqttSubscribeTopic;
String mqttPublishTopic;
String clientId;

const char* subscribeTopic = nullptr;
const char* publishTopic = nullptr;


#endif