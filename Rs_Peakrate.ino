float iesco_unit_slab[8]={23.59, 30.07, 34.26, 39.15, 41.36, 42.78, 43.92, 48.84};

void unit_calculate_1()
{
  if (SPM==true)
  {
    fill_SPM();
  }

   if (TPM==true)
  {
   fill_TPM();
  }

   //nameString = String(selfMAC.name); // Convert to Arduino String
 
 /*if(Name_Save==true)
 {
   Buzzer();
   Name_Save=false;

 }*/
 
}





void fill_SPM(){

if (once == 1)
{
   Met_save=true;
single_phase_unit_cost =  single_PM_data.last_month_cost;
Buzzer();
once++;
}
//Serial.printf("\nUNIT COST SINGLE PHASE METER: %f\n",single_phase_unit_cost);
}

void fill_TPM()
{

if (once == 1)
{ 
Met_save=true;
peak_time_start=three_PM_data.peak_hour_start;
peak_time_stop=three_PM_data.peak_hour_end;
peak_unit_rate = three_PM_data.peak_hour_cost;
off_peak_unit_rate = three_PM_data.off_peak_hour_cost;
Serial.printf("****************************Getting from Structure Peak_uint=%g,Off_Peak=%g*************************\n\n",peak_unit_rate,off_peak_unit_rate);
Buzzer();
once++;
}

}