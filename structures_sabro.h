#ifndef STRUCTURES_SABRO_H
#define STRUCTURES_SABRO_H

  
struct Meter_Start_t
{
   int year;
   uint8_t month;
   uint8_t day;
   uint8_t Hour;
   
} ;
Meter_Start_t S_Data; // Array to store 24 hours of data




struct remote_side_pair_t{
uint8_t request;
uint32_t authenticator;
};

remote_side_pair_t incoming_remote , outgoing_remote;
 
 
struct Running_Data_t
 {
    uint8_t  SL_Code;
    uint8_t  Sec_Rtc=0;
    uint8_t  Min_Rtc=0;
    uint8_t  Hour_Rtc=0;
    uint8_t  day_Rtc=0;
    uint8_t  month_Rtc=0;
    uint16_t Year_RTC=0;
    uint8_t  Ble_8Bit1;
    uint8_t  Ble_8Bit2;
    uint8_t  Ble_8Bit3;
    uint8_t  Ble_8Bit4;
    uint8_t  Ble_8Bit5;
    uint8_t  mode_pkr_set;
    uint8_t  rupees_send;
    float    Set_Temp=25.00;
    float    Coil_sensor = 0;                // indoor coil sensor data
    float    Room_sensor = 0;
    float    Delta_Temp = 0;  //     This variable is the temperature difference for "Cool Mode" bcz in this mode room temperature is greater than set temperature.
    float    Suction_Temp=0;
    float    Calculated_Suction_Pressure; 
    float    Liquid_Line_temp=0;
    float    Discharge_Temp=0;
    float    Calculated_Discharge_Pressure;
    float    ODU_Ambient_Temp=0;
    float    Ac_volts=0;
    float    Dc_Volts=0;
    float    S_cuurent=0;
    float    F_Current=0;
    float    Comp_current=0;
    uint16_t Comperssor_Running_RPM=00;
    uint8_t  Inv_Error=0;
    uint8_t  Falut_Inv_code;
    uint32_t Ton_sec;    // 
    uint32_t Tof_sec;


    float    R_Hour_Energy;
    float    R_Day_Energy;
    float    energy_day_peak;
    float    R_Month_Energy;
    float    energy_month_peak;
};

Running_Data_t R_Data; // Array to store 24 hours of data

struct DateTimeStruct_t{
  uint8_t check;
  uint8_t second;
  uint8_t minute;
  uint8_t hour;
  uint8_t day;
  uint8_t month;
  uint16_t year;
} DateTimeStruct;

// Global variables
DateTimeStruct_t dateTime;


struct connection_t{
uint8_t data_kindness;
uint8_t isPaired=0;
uint32_t authenticatoR;
};

connection_t connect;



struct mac_data_t {
  char name[20]="Sohail_Room"; // save in EEprom
  uint8_t pair_status;
  uint32_t authenticator=1184005016;
};
mac_data_t selfMAC;


struct protocol_esp_t{
  uint8_t request_type;
  uint8_t request_id;
};
protocol_esp_t protocol_msg;


struct four_byte_data_t {
uint8_t temp_screen;
uint16_t control_screen;
};
four_byte_data_t Control_Screen; 

struct single_phase_meter_data_t {
  uint8_t message_type;
  float last_month_cost;
};

single_phase_meter_data_t single_PM_data;

struct three_phase_meter_data_t {
  uint8_t message_type;
  uint8_t peak_hour_start;
  uint8_t peak_hour_end;
  float peak_hour_cost;
  float off_peak_hour_cost;
};
three_phase_meter_data_t three_PM_data;

struct pkr_mode_data_t{
uint8_t message_type = 16;
float Current_Energy;
float Current_RS;
float Target_energy;
float Target_price;
float Current_unit_price;
float current_hour_cost;
};
pkr_mode_data_t pkr_send_data;



#endif