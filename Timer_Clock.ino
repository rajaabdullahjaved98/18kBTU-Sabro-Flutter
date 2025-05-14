
int s_count=0;    // Real time clock Varaibles
int m_count=00;
int h_count=0;




void sec()
{
  s_count=s_count+1;
  if(Timer_on=="ON")  // 
  {
   // Serial.println("in timer checking");
    -- Ton_sec;    
  }
  if(Timer_of=="ON")  // 
  {
    //Serial.println("in timer checking");
    -- Tof_sec;    
  }
  if(s_count>=60)
  {
    s_count=0;
    ++m_count; 
  }
  if(m_count>=60)
  {
    m_count=0;
    ++h_count;
  }
  // if(EEP=="YES")
  //{ 
  //EEPROM_Write();
  // EEP="NO";
  // }  
}
void Timer_Set()
{
  if(Timer_on=="ON" && Ton_Set=="Yes")
  {
    //Ton_Mints_Count=(Ton_Mints_Count*60)+(Ton_Hours_Count*60);
    Ton_Sec_Left=Timer_Fsecond;
    Ton_sec=Timer_Fsecond;
    Serial.print("in timer on=");
    Serial.println(Ton_Sec_Left);
    Ton_Set="No";     // means timer will set value every time timer is on & value is change Ton_set will remain "NO" only eecure one time to calulate the min
    flipper2.attach(Ton_Sec_Left,tim_on); 
   }
   if(Timer_of=="ON" && Tof_Set=="Yes")
   {
     //Tof_Mints_Count=(Tof_Mints_Count*60)+(Tof_Hours_Count*60);
     Tof_Sec_Left=Timer_Fsecond;
      Serial.print("in timer off=");
    Serial.println(Tof_Sec_Left);

     Tof_sec=Tof_Sec_Left;
     Tof_Set="No";     // means timer will set value every time timer is on & value is change Ton_set will remain "NO" only eecure one time to calulate the min
     flipper3.attach(Tof_Sec_Left,tim_of); 
   }
}
void tim_on()
{      
  //Power="ON";
// Eeprom_Read();
  Power="ON";
  Timer_on="OF";
   
/*
  if(Mode =="C")
     {
      //LEDS(HIGH,LOW,LOW);
     }


    if(Mode =="D")
     {
       //LEDS(HIGH,LOW,HIGH);
    }

     if( Mode == "F")
      {
        // LEDS(LOW,LOW,HIGH);
      }
    
    if(Mode =="H")
     {
      // LEDS(LOW,HIGH,LOW);
     }
      Fan_Status="M";   */
    // Fan_control(Fan_Status);    // pass the fan speed tturn on fan
 
 F_Hour=00;
 F_Min=00;
  Ton_sec=0;
  flipper2.detach();
   bitWrite(Ble_8Bit5,4,0);  //Timer on is off 
}


void tim_of()
{     
 // Buzzer(); 
 
   
    Power="OFF";
   Timer_of="OF";
  
 
   //Swing_Stop();            // for Storte Swing data


   F_Hour=00;
   F_Min=00;
   Tof_sec=0;
   flipper3.detach();
    bitWrite(Ble_8Bit5,3,0);  //Timerof is off 


}

void Timer_Print()
{
  Serial.println("");
 Serial.print("Real_Time_Start="); 
    Serial.print(h_count);
    Serial.print(":");
    Serial.print(m_count);
    Serial.print(":");
    Serial.print(s_count);
    Serial.print(",");
    
    //Serial.println("");
     Serial.print("Timer_On="); 
    Serial.print(Timer_on);
    Serial.print(",");
    Serial.print("Timer_OF="); 
    Serial.print(Timer_of);
   // Serial.println(",");
   
    
    
   // Serial.println();
      
    
        if(Timer_on=="ON")
        {
          
          Serial.print("::Timer_on_sec="); 
          Serial.print(Ton_sec);
          
          
        }

        
        if(Timer_of=="ON")
        {
          
          Serial.print("::Timer_of_sec="); 
          Serial.print(Tof_sec);
          
          
        }

    
      Serial.println();




}




