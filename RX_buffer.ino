uint8_t  received;

void clear_rx()

{
  // Serial.println("**clear RX******************************************************************************** :checking data in buffer");

  if(Serial2.available() > 0)
{
    Serial.print("RX_setup:=");
      for(int n =0; n<=62; n++)
        {

          received = Serial2.read(); // Read a Byte 
         Serial.print(received,HEX);
       Serial.print(",");

        }
         DDPNC=0;
   Suction_Temp=0; 
   Liquid_Line_temp=0;
    Discharge_Temp=0;
    ODU_Ambient_Temp=0;
   Ac_volts=0;
   Dc_Volts=0;
   S_cuurent=0;
   Comp_current=0;
   Comperssor_Running_RPM=00;
   Comperssor_send_Rpm=00;
  


        Serial.println("**********************************************************************************           :Data_Recived_Setup");
       
}

}

void dump_Rx()

{

  if(Serial2.available() > 0)
{

  

     
    // Serial.print("RX:=");
      for(int n =0; n<8; n++)
        {

          received = Serial2.read(); // Read a Byte 
      //  Serial.print(received,HEX);
      // Serial.print(",");

        }

       // Serial.println("            :Data_Dump_Recived");
       
       

}

}