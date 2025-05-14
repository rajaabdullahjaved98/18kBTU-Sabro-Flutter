#ifndef INVERTER_VARIABLES_H
#define INVERTER_VARIABLES_H



// inverter Varaibles Start Here




uint8_t inverter_bytes[8]={};
uint32_t buff[40]={0};
char da[10];
uint8_t Node_adress=0x01; // node address , slave address 
uint8_t Command=0x06; // command for single reg Write , or Function code read 03, write 06
uint8_t Adress_Hbyte=0x00; // address 1st high byte
uint8_t Adress_Lbyte=0x39;// address 2nd  low byte 56 in protocl inhex 38
uint8_t Data_Hbyte=0x00; // data word 1st High byte  for write
uint8_t Data_Lbyte=0x01; // data word 2nd low byte  for write
uint8_t Crc_Hbyte=0x00; // crc 16 , hight byte 
uint8_t Crc_Lbyte=0x00; // crc 16 , Low byte 

uint8_t inverter_Sdata[8]= {Node_adress,Command,Adress_Hbyte,Adress_Lbyte,Data_Hbyte,Data_Lbyte,Crc_Hbyte,Crc_Lbyte};
String data_seq[50]={"Node","Command","A_HB","A_LB","D_HB","D_LB","Crc_HB","Crc_LB"};
String Read_data[40]={"Node","Command","Recive_Bytes","Data_Hbyte","Data_Lbyte","Crc_Hbyte","Crc_Lbyte"};


uint8_t Register_address=0x00; //All read or write adderess we use this
uint8_t data_LB=0x01;           // all data_lbyte will use this varaiable for Reading
uint8_t data_HB=0x00;
uint8_t mode_Of=0x00;
uint8_t mode_C=0x01;
uint8_t mode_H=0x02;

uint8_t    inv_Mode_Of=0x00;
uint8_t    inv_Mode_Cool=0x01;
uint8_t    inv_Mode_Heat=0x02;;
uint8_t     Fan_select_Ac=0x02;
uint8_t     Falut_Inv_code;

uint8_t      Motor_of=0x00;
uint8_t      Motor_on=0x01;
uint8_t      R_Valve_On=0x01;
uint8_t      R_Valve_Of=0x00;



 



//MODBUS valid function code table：

const uint8_t Read =0x03;           // Reading register command
const uint8_t Write=0x06;           // Write Register Command
const uint8_t  Write_Mutiple=0x10;   //Mutiple Write

// 

// Fault code Table

const uint8_t illegal_insgruction=0x01;    // The instruction received is not included in defined valid instructions.
const uint8_t illegal_data=0x02;            // The addressing address is out of the scope of definition.
const uint8_t Unsuccessful_data_writing=0x06;    // The data modification was not successful.

//


// Read & Write Parametet controlling of system.


const uint8_t Mode_Inv=0x00;  // (0: Shutdown; 1: Cooling; 2: Heating) // in cooling 4 way valve off & heating is on no needed Relay 2 replace is with mode
const uint8_t Target_frequency=0x01;  //  0.01HZ  NEW IDU  comaperssor Target Speed rps
const uint8_t Target_EEV_opening1=0x05;   //  "0: Automatic; Non zero values are manual"
const uint8_t Forced_defrosting=0x09;      //  0: None; 1: Forced manual defrosting
//const uint8_t Manual_fan_speed=0x003c;      // decimal 60 // 0: Automatically determined by ODU,"0: Automatically determined by ODU 1~7: 7 Gear speed others: rpm. value 800 means 800rpm."
//const uint8_t Fan_select=0x0044;             // deciaml 68  0:AC dual; 1:DC Fan; 2:AC Single
const uint8_t Manual_4Way=0x10;                // 0 off 1 on

const uint8_t Fan_select=0x0D;            // last program
const uint8_t Manual_fan_speed=0x0E;
const uint8_t IDU_defrost_status=0x11;    //  0, no 1 yes

// 


//  Read only

const uint8_t Actual_Operation_mode_of_ODU=0x14;
const uint8_t Real_frequency=0x15; //  new Actual comperssor  operating speed of ODU
const uint8_t Electronic_expansion_valve=0x16; //new Actual opening step of EEV pls
const uint8_t Real_DCfan_speed1=0x017;    // new Fan target speed of ODU





const uint8_t ODU_Ambient_temp_Ta=0x18;  // ODU Ambeint temp
const uint8_t Discharge_temp_To=0x19;  // Discharge temperature To	0.1℃ Discharge temperature of compressor	25 in HEX is 19 is confirmed.
const uint8_t Liquid_Line_temp_Te=0x1A;     //note:19suc & 1A dicahrge Last
const uint8_t Suction_temperature_Ts=0x1B;       //Finned coil heat exchanger temperature Te	0.1℃ 24 ODU Ambient temperature	24 is 18HEX noy connected





const uint8_t Supply_current=0x1C;  // new Input current
const uint8_t Compressor_current=0x1D;  // new Compressor current
const uint8_t Fault_code=0x1E;     // new parameter
//const uint8_t Defrosting_status=0x1F;  // new parameter
const uint8_t AC_voltage=0x20;
const uint8_t DC_voltage=0x21;
const uint8_t Speed_limiting_code=0x22; // new 0: None; 1: Input current limiting; 2: Output current limiting; 3: Temperature of IPM too high; 4: Ove-modulation; 5: Discharge temperature too high;6: Coil temperature of ODU too hig


// End of Read only


#endif