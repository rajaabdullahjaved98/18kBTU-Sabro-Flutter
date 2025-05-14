float POWER_FACTOR = 1.0;

float CHE=0;


bool meter_type = true;

void Cal_Power()

{

DateTime now = rtc.now();

  // Calculate power (Watts)
 // float power = VOLTAGE * CURRENT * POWER_FACTOR;
  Min_power=Ac_volts*S_cuurent*POWER_FACTOR;
  


  // Calculate energy (Wh)
  
   
    Energy = Min_power / 1000.0;
     Energy_Min+=  Energy;
    CHE=Energy_Min /60;
  // Serial.printf(" \n Power KwAc_volts=%g,S_cuurent=%g,Energy=%g\n", Ac_volts,S_cuurent,Energy);
   if (meter_type){
   Run_Energy_Hour=CHE;
   Run_Energy_Day = Energy_Day + CHE - energy_day_peak;
   Run_Energy_Month = Energy_Month + CHE - energy_month_peak;
   }
   else{
   Run_Energy_Hour=CHE;
   Run_Energy_Day = Energy_Day + CHE ;
   Run_Energy_Month = Energy_Month + CHE ;

   }

  

  // Display energy values
  
 // Serial.printf("Min_Energy+=%g, Run_Energy_Hour=%g,Run_Energy_Day=%g,Run_Energy_Month=%g\n", Energy_Min,Run_Energy_Hour,Run_Energy_Day,Run_Energy_Month);
}
  // Save energy values to EEPROM
