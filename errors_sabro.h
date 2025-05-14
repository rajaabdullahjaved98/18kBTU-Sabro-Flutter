#ifndef ERRORS_SABRO_H
#define ERRORS_SABRO_H


uint8_t Errors_info[35]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

//error start with letter E
String Error_Data[10]={
                       "Room Sensor Discount or Short",//Errors_info[0]
                       "Coil Sensor short or Discconected",//Errors_info[1]
                       "Indoor coil sensor ice/Motor_Fault",//Errors_info[2]
                       "Gas is Less",//Errors_info[3]
                       "ADS is not connected[]",//Errors_info[4]
                       "Indoor_Coil_over_Heat/Motor_Fault"//Errors_info[5]
                       };

//error start with letter F
String Error_Data1[10]={
                        "Suction Temp limit",
                        "Discharge Temp Limit",
                        "Ac volt",
                        "Main Current",
                        "Speed_limiting_code_See List",
                        "Out_Door_Motor or Coil is chock",
                        "Protocl_Error"
                        };

//error start with letter H
String Error_Data2[10]={
                        "Communation Wire Break",
                        "OutDoor_ABT_Temp_Short or Discoonect",
                        "LLine Temp Short  or Discoonect",
                        "Dicharge_Temp_Short  or Discoonect",
                        "IB Fault",
                        "Suction_Temp_Short or Disconnect"
                        };


String IB_Fault_1[20]={
                        "Outdoor EEPROM fault",
                        "Outdoor communication fault",
                        "Outdoor air temp sensor fault",
                        "Outdoor LLine temp sensor fault",
                        "Discharge temp sensor fault",
                        "CT sensor fault",
                        "Compressor operating fault",
                        "Outdoor fan operating fault",
                        "Outdoor suck temp sensor fault",
                        "Module temp high protect",
                        "Input Vac overhigh",
                        "Input Vac underlow",
                        "Input Vac freq error",
                        "Other Errors",
                        "Discharge temp protection",
                        "High load protection",
                        "Input current control fault",
                        "Indoor anti-freezing"
                        };

String IB_Fault_2[5]={
                        "Low DC voltage control fault",
                        "Compressor protector action fault",
                        "Demagnetization protection control fault",
                        "PFC over-current fault",
                        "Abnormal total power fault"
                        };

uint8_t IB_F_value1[20]={0x05,0x06,0x35,0x36,0x37,0x39,0x55,0x59,0x61,0x62,0x64,0x65,0x66,0x69,0x71,0x72,0x73,0x74};
uint8_t IB_F_value2[5]={0x76,0x77,0x79,0x81,0x82};




#endif