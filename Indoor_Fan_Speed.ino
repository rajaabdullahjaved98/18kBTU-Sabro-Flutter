
// for lcd ver check in full load auto temp must goto "C" in Dry & fan also on heating can we make it lvlgl 
  void Fan_Setup(){
  pinMode(fan_low, OUTPUT);
  pinMode(fan_mid, OUTPUT);
  pinMode(fan_high, OUTPUT);
  Fan_off();
  }

  void Fan_off(){
  digitalWrite(fan_low,LOW);  
  digitalWrite(fan_mid,LOW); 
  digitalWrite(fan_high,LOW); 
  bitWrite(Ble_8Bit1,5,0); //Fan off
  bitWrite(Ble_8Bit1,4,0);  // Fan off
  bitWrite(Ble_8Bit1,3,0);  // Fan Low
  }

  void Fan_low(){
  digitalWrite(fan_low,HIGH);  
  digitalWrite(fan_mid,LOW); 
  digitalWrite(fan_high,LOW); 
  bitWrite(Ble_8Bit1,5,0); //Fan Low
  bitWrite(Ble_8Bit1,4,0);  // Fan Low
  bitWrite(Ble_8Bit1,3,1);  // Fan Low
  }

  void Fan_med(){
  digitalWrite(fan_low,LOW);  
  digitalWrite(fan_mid,HIGH); 
  digitalWrite(fan_high,LOW);
  bitWrite(Ble_8Bit1,5,0); //Fan Med
  bitWrite(Ble_8Bit1,4,1);  // Fan Med
  bitWrite(Ble_8Bit1,3,0);  // Fan Med
  }

  void Fan_high(){
  digitalWrite(fan_low,LOW);  
  digitalWrite(fan_mid,LOW); 
  digitalWrite(fan_high,HIGH); 
  bitWrite(Ble_8Bit1,5,0); //Fan High
  bitWrite(Ble_8Bit1,4,1);  // Fan High
  bitWrite(Ble_8Bit1,3,1);  // Fan High
  }


void Fan_control(String Fan_Speed,String FRM)
{

    Fan_Running_Mode=FRM;
    Fan_Status=Fan_Speed;          // Fan status is Global variable here we transfer data from Ir_routine to it.

    if(Fan_Speed == "L" || (Fan_Status == "A" &&  Delta_Temp>=0 && Delta_Temp<3) )
    {
    Fan_low();   
    }
    else if(Fan_Speed == "M" || (Fan_Status == "A" && Delta_Temp>=3 && Delta_Temp<6))
    {
    Fan_med();
    }
    else if(Fan_Speed == "H" || (Fan_Status == "A" && Delta_Temp>=6))
    {
    Fan_high();
    }
    else{

    if (Stop_Stop=="No")
    Fan_Status = "M";

    }

 if( Fan_Status == "A")
 {

    bitWrite(Ble_8Bit1, 5, 1);  //Fan auto
    bitWrite(Ble_8Bit1, 4, 0);  // Fanauto
    bitWrite(Ble_8Bit1, 3, 0);
 }
 
  }





 void Heating_Fan_Control(String Status)

  {

    if(Mode=="H" ||  Auto_Temp=="H")

    {
      
     Fan_Running_Mode="H";
      bitWrite(Ble_8Bit4,4,1); //Fan H
    
  

     
      if(Coil_sensor<=37 || Defrost_mode=="YES")// 37 is tested cahngong it to 33 for prices checking

     {
      Fan_off();
      }
 
        if(Coil_sensor>39 && Defrost_mode=="NO") // coil sensor <56 in H theen on // 39 chanhing for rs 35
       {
        Fan_control(Fan_Status,"NH");
       }

}

}













