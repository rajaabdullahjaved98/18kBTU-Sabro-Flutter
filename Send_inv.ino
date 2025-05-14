
 #include <Crc16.h>


Crc16 crc; 
unsigned short value = crc.getCrc();

void sending(uint8_t Temp_Register_address,uint8_t Temp_Write,uint8_t Temp_data_HB,uint8_t Temp_data_LB)

{

//Serial.printf("I am in sending Esp32=%s\n",Esp_32.c_str());
//Serial.printf("\send staus of :Last_Power=%S,CPower=%s\n",ML_Power.c_str(),Power.c_str());

inverter_Sdata[1]=Temp_Write;
inverter_Sdata[3]=Temp_Register_address;
inverter_Sdata[4]=Temp_data_HB;
inverter_Sdata[5]=Temp_data_LB;
Crc_cal();
invt_send();
delay(130);           // Delay Required to Recived data 20ms other wise old data will be send set it 100 other wise protocol error

    if(Temp_Write==Write)
   {
    esp_rec_data();
  Protocol_Confirm();
  }
   if(Temp_Write==Read)
   {
   esp_read_data();
   }

}




void Crc_cal()

{

uint8_t crc_low, crc_high;

crc.clearCrc();
value = crc.Modbus(inverter_Sdata,0,6);  // working
crc_high = value << 0;
crc_low = value >> 8;

inverter_Sdata[7]=crc_low;
inverter_Sdata[6]=crc_high;
Crc_Hbyte=crc_high;
Crc_Lbyte=crc_low;

}


void invt_send()

{

  buff[4]={0};
 // Serial.println("");
//Serial.print("TX:");
 for (int i =0; i<8;i++)
    
    {
     Serial2.write(inverter_Sdata[i]);
    }
    // Send_Print();
   }


 void Send_Print()

 {

  for (int i =0; i<8;i++)     /// for print use this
    
    {
      sprintf(da, "%02X",inverter_Sdata[i]);
      
    //  if((i!=2))
      {
        Serial.print(data_seq[i]);
       Serial.print("=");
      //Serial.print(inverter_Sdata[i]);
       // Serial.print("  ,In Hex");
        Serial.print("=0x");
        Serial.print(da);
        Serial.print(":");
      }
      
    }
  
    Serial.println("");




 }