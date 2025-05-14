//if Buzzer Beep then Epprom data is saves & EEP is YES


String T_Temp;  // this string use to convert from float to string for eeprom data & give back from string to float after EEprom read
String T_Eco;
String T_OP;
String T_CRs;
#define POWER_Address 2000


void EEprom_Confirm()

{


  if (EEP == "YES")

  {
    // Serial.println("");
    Serial.print("In EEprom*****************************************************************************SAved*******************************************Yes");
    if (store)
    {
      EEPROM.write(addressmac,connect.isPaired);
      for (int i=0;i<6;i++)
      EEPROM.write((addressmac+1)+i,broadcastAddress[i]);
      store=false;
    }
   
   Meter_Data();
   EEPROM_Write();
    EEP = "NO";

  }
}


void EEPROM_Write()


{
 
  Serial.printf("\nIn EEprom*********************************************************************************************Data_Saved_Write\n");
  


//  EEPROM.begin(EEPROM_SIZE);
  T_Temp = String(Set_Temp);  // this will convert float to string
  T_Eco = String(Saving_Mode);
  T_OP=String(operation_mode);
  T_CRs=String(Cutomer_Rs);
  for (int i = 0; i < 65; ++i) {
    EEPROM.write(i, '0');
  }

  // if( Power=="Stop") // if wapda off when system is going to off
  // {

  // EEPROM.writeString(Eeprom_add_Power,"OF");

  // }
  EEPROM.writeString(Eeprom_add_Power, Power);
  EEPROM.writeString(Eeprom_add_Swing, Swing);
  EEPROM.writeString(Eeprom_add_Fan, Fan_Status);
  EEPROM.writeString(Eeprom_add_Mode, Mode);
  EEPROM.writeString(Eeprom_add_Temp, T_Temp);
  EEPROM.writeString(Eeprom_add_Eco,T_Eco);
  EEPROM.writeString(Eeprom_add_OP_Mode,T_OP);
  EEPROM.writeString(Eeprom_add_Cutomer_Rs,T_CRs);
   EEPROM.writeString(Eeprom_add_Name,nameString);
  EEPROM.commit();


  //  delay(100);
 // Serial.println();
 // Serial.println();


/* for (int i = 0; i < 65; ++i)

  {

    Serial.print(i);
    Serial.print(",");
    Serial.print(char(EEPROM.read(i)));
    Serial.print(",");
  }*/
// Eeprom_Read();
}


void Eeprom_Read()

{
  connect.isPaired=EEPROM.read(1550);
   Met_Type = EEPROM.read(POWER_Address);

  if (Met_Type==0 || Met_Type==255)
  {

  }
  else if (Met_Type==1)
  {
 SPM = true;
 TPM = false;
 EEPROM.get(POWER_Address+1,single_phase_unit_cost);

  }
  else if (Met_Type==3)
  {
 SPM = false;
 TPM = true;
   Serial.print("Met_Type_in select=");
  Serial.println(Met_Type);


    peak_time_start = EEPROM.read(POWER_Address+1);
    peak_time_stop = EEPROM.read(POWER_Address+2);
    float Tpeak=  EEPROM.get(POWER_Address+3,peak_unit_rate);
    float Toff_peak= EEPROM.get(POWER_Address+7,off_peak_unit_rate);
    Serial.printf("PT_Start=%i,PT_Stop=%,Tpeak=%g,Toff_peak=%g\n\n",peak_time_start,peak_time_stop,Tpeak,Toff_peak);

  }
  
  Serial.print("Met_Type=");
  Serial.println(Met_Type);


  if (connect.isPaired==255 || connect.isPaired==0){
    connect.isPaired=0;
    selfMAC.pair_status = connect.isPaired;
for (int i = 0; i<6;i++)
broadcastAddress[i]=255;  
  }
  else{
    selfMAC.pair_status = connect.isPaired;
for (int i = 0; i<6;i++)
broadcastAddress[i]=EEPROM.read(1551+i);
  }




  Serial.print("Data_EEprom_Power=");
  Power = EEPROM.readString(Eeprom_add_Power);
  Serial.println(Power);
  if (Power == "ON")

  {
    bitWrite(Ble_8Bit1,7,1);  // Power On
    
  }

  else {

     bitWrite(Ble_8Bit1,7,0);  // Power OFF

   
  }


  Serial.print("Data_EEprom_Swing=");
  Swing = EEPROM.readString(Eeprom_add_Swing);
  Serial.println(Swing);

  Serial.print("Data_EEprom_Fan=");
  Fan_Status = EEPROM.readString(Eeprom_add_Fan);
  //Serial.println(Fan_Status);

  if(Fan_Status!="L" &&  Fan_Status!="M" && Fan_Status!="H" && Fan_Status!="A")

  {
    Fan_Status="M";
   
  }
  Serial.println(Fan_Status);
  

  Serial.print("Data_EEprom_Mode=");
  Mode = EEPROM.readString(Eeprom_add_Mode);
  Serial.println(Mode);

  


  Serial.print("Data_EEprom_Temp");
  T_Temp = EEPROM.readString(Eeprom_add_Temp);
  Set_Temp = T_Temp.toFloat();
  Serial.println(Set_Temp);
  CT=Set_Temp;
  

  
  T_Eco = EEPROM.readString(Eeprom_add_Eco);
  Serial.printf("\nTeco=%s\n",T_Eco.c_str());
  Saving_Mode = T_Eco.toInt();
   Serial.print("Data_EEprom_Ec=");
  Serial.println(Saving_Mode);

  Serial.print("Data_EEprom_OP_mode=");
  T_OP = EEPROM.readString(Eeprom_add_OP_Mode);
  operation_mode = T_OP.toInt();
  Serial.println(operation_mode);

   Serial.print("Data_EEprom_Cutomer_Rs=");
  T_CRs = EEPROM.readString(Eeprom_add_Cutomer_Rs);
  Cutomer_Rs = T_CRs.toFloat();
  Serial.println(Cutomer_Rs);


   Serial.print("Data_EEprom_Nam=");
    nameString= EEPROM.readString(Eeprom_add_Name);
    nameString.toCharArray(selfMAC.name,sizeof(selfMAC.name));
   Serial.println(nameString);







 Lcd_Send();


  
}  // void Eepromn Read


void Lcd_Send()

{

  if  (Fan_Status == "A")
 { 
   bitWrite(Ble_8Bit2,3,1); //Fan auto
   bitWrite(Ble_8Bit2,2,1);  // Fanauto
   bitWrite(Ble_8Bit2,1,0); 
 } 

 if  (Fan_Status == "L")
 { 
   bitWrite(Ble_8Bit1,5,0); //Fan Low
    bitWrite(Ble_8Bit1,4,0);  // Fan Low
    bitWrite(Ble_8Bit1,3,1);  // Fan Low
 }

 if  (Fan_Status == "M")
 { 
    bitWrite(Ble_8Bit1,5,0); //Fan Med
    bitWrite(Ble_8Bit1,4,1);  // Fan Med
    bitWrite(Ble_8Bit1,3,0);  // Fan Med
 }

   if(Fan_Status == "H")
 { 
    bitWrite(Ble_8Bit1,5,0); //Fan High
    bitWrite(Ble_8Bit1,4,1);  // Fan High
    bitWrite(Ble_8Bit1,3,1);  // Fan High
 }


   if( Mode == "A")
  {   
   bitWrite(Ble_8Bit2, 5, 1); 
  }

    if( Mode == "C")
  {   
  bitWrite(Ble_8Bit2,7,0); 
  bitWrite(Ble_8Bit2,6,0); 
   bitWrite(Ble_8Bit2, 5, 0); // Auto off

  }

   if( Mode == "H")
  {   
   bitWrite(Ble_8Bit2,7,0);
    bitWrite(Ble_8Bit2,6,1);
    bitWrite(Ble_8Bit2,5,0); // Auto off

  }

   if( Mode == "D")
  {   
    bitWrite(Ble_8Bit2,7,1); 
    bitWrite(Ble_8Bit2,6,0);
    bitWrite(Ble_8Bit2,5,0); // Auto off
  }

   if( Mode == "F")
  {   
  bitWrite(Ble_8Bit2, 7, 1);  
  bitWrite(Ble_8Bit2, 6, 1); 
   bitWrite(Ble_8Bit2,5,0); // Auto off
  }


     if(Saving_Mode == 0) 
  {
   bitWrite(Ble_8Bit2,4,0); //saving mode of
  }

    if(Saving_Mode == 1) 
  {
   bitWrite(Ble_8Bit2,4,1); //saving mode on
  }




    if(Swing == "OF") 
  {
    bitWrite(Ble_8Bit1,6,0);  // Swing OFF
  }

    if(Swing == "ON") 
  {
     bitWrite(Ble_8Bit1,6,1);  // Swing On
  }
     

}

void Meter_Data()

{


 if ((TPM==true) && (Met_save==true))
    {
    EEPROM.write(POWER_Address,3);
    EEPROM.write(POWER_Address+1,peak_time_start);
    EEPROM.write(POWER_Address+2,peak_time_stop);
    EEPROM.put(POWER_Address+3, peak_unit_rate);
    EEPROM.put(POWER_Address+7,off_peak_unit_rate);
    Serial.printf("\nIn EEprom***************************************************3phase******************************************Data_Saved_Write\n");
  
    Met_save=false;
    }

   if ((SPM==true) && (Met_save==true))
    {
   EEPROM.write(POWER_Address,1);
   EEPROM.put(POWER_Address+1, single_phase_unit_cost);
    Serial.printf("\nIn EEprom***************************************************single_phase******************************************Data_Saved_Write\n");
    Met_save=false;

    }
    }

