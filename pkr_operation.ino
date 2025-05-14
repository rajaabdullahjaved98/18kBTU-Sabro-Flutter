String Temp_Pkrs;

void check_peakness()

{
 if ((Hour_Rtc >= peak_time_start) && (Hour_Rtc < peak_time_stop ) && (TPM==true))

  {
    Running_Peak = peak_unit_rate;
     bitWrite(Ble_8Bit3, 1, 1);  // TPM
  }

  else if (TPM=true)
  {

    Running_Peak = off_peak_unit_rate;
     bitWrite(Ble_8Bit3, 1, 1);  // TPM
  }

  if(SPM==true)
  {

    Running_Peak = single_phase_unit_cost;
    bitWrite(Ble_8Bit3, 1, 0);  // SPM
  }


  Current_Rs_hour = Running_Peak * Run_Energy_Hour;  // Rs_consume will zero on new hoour
  Currenr_Energy_cost = Energy * Running_Peak;
 // Serial.printf("**********************************before***********************************T_E=%f,CR=%g=,RP=%g\n\n",Target_Energy,Cutomer_Rs,Running_Peak);
  Target_Energy= Cutomer_Rs/Running_Peak;
 // Serial.printf("*********************************************************************T_E=%f\n\n",Target_Energy);
  pkr_send_data.Target_energy =Target_Energy; 
  pkr_send_data.Target_price = Cutomer_Rs;
  pkr_send_data.Current_Energy = Energy;
  pkr_send_data.Current_RS = Currenr_Energy_cost;
  pkr_send_data.Current_unit_price = Running_Peak;
  pkr_send_data.current_hour_cost = Current_Rs_hour;
  Serial.printf("IN pkr operation*******************************************************Check energy*******************\n\n\n");
  E_cal=true;

  
  

  if( Cutomer_Rs>Currenr_Energy_cost)

  {
   Money_Equal=Cutomer_Rs-Currenr_Energy_cost;
  }

  if( Cutomer_Rs<Currenr_Energy_cost)

  {
   Money_Equal=Currenr_Energy_cost-Cutomer_Rs;
   

  

  }



  if(Cutomer_Rs!=LC_RS)

  {

   BRPM=true;
   BRPM_counter=0;

  }

 LC_RS=Cutomer_Rs;
}
  





  


  




