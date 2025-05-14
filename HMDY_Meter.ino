
//float energy_day_peak;

//float energy_month_peak;


void new_hour()

{




  DateTime now = rtc.now();

  Get_Time();
  // Print_Date();

  Serial.println();
  Serial.println();
  Serial.println();


  //  Serial.printf( "Main LOOP::\n Min changed to=%i\n Cuurent Year is =%i,Current_month is=%i,Cuurent Day is=%i,Cuurent_Hour=%i\n",Min_Rtc,year_Rtc,month_Rtc,day_Rtc,Hour_Rtc);
  // Serial.printf( "\n LY=%i,LM=%i,LD=%i,LH=%i\n",LY,LM,LD,LH);
  //Serial.printf("Min_Energy=%g,Energy_Hour=%g,Energy_Day=%g.Energy_Month=%g\n", Energy_Min,Energy_Hour,Energy_Day,Energy_Month);
  //  Serial.print("Main LOOP:: Min changed to=");
  //  Serial.println(Min_Rtc);

  //   Serial.print("Current Year=");
  //  Serial.print(year_Rtc);

  //  Serial.print(" Curerent Month=");
  //  Serial.print(month_Rtc);

  //  Serial.print("  Current Day=");
  //  Serial.print(day_Rtc);

  //  Serial.print("  Current Hour=");
  //  Serial.print(Hour_Rtc);

  // //Serial.printf(" Min_Energy=%g,Energy_Hour=%g,Energy_Day=%g.Energy_Month=%g\n", Energy_Min,Energy_Hour,Energy_Day,Energy_Month);

  // Serial.print("  Min_Energy=");
  //  Serial.print(Energy_Min);

  //   Serial.print("  Energy_Hour=");
  //  Serial.print(Energy_Hour);

  //   Serial.print("  Energy_Day=");
  //  Serial.print(Energy_Day);

  //   Serial.print("  Energy_Month=");
  //  Serial.print(Energy_Month);

  // Serial.printf( "\n LY=%i,LM=%i,LD=%i,LH=%i\n",LY,LM,LD,LH);


  if (LH != Hour_Rtc)

  {

    Serial.print("Hour changed to=");
    Serial.println(Hour_Rtc);

    Hours();

    LH = Hour_Rtc;
  }


  if (LD != day_Rtc)

  {

    Serial.print("Day changed to=");
    Serial.println(day_Rtc);

    LD = day_Rtc;
    Energy_Day = 0;
    energy_day_peak = 0;
    Run_Energy_Day = 0;
    Hour_Clear();
  }

  if (LM != month_Rtc)

  {


    Serial.print("Month changed to=");
    Serial.println(month_Rtc);

    LM = month_Rtc;
    Energy_Month = 0;
    energy_month_peak = 0;
    Run_Energy_Month = 0;
    Day_Clear();
    Hour_Clear();
  }



  if (LY != year_Rtc)

  {

    Serial.print("Year changed to=");
    Serial.println(year_Rtc);
    Month_Clear();
    Day_Clear();
    Hour_Clear();
  }
}



void Hours()

{
  // Serial.printf("\nXsemiphore taking  in Hours \n");
  // xSemaphoreTake(xSemaphore, portMAX_DELAY);
  // EEPROM.begin(EEPROM_SIZE);

  // Store data in EEPROM
  Energy_Hour = Energy_Min / 60;
    if ((Hour_Rtc > peak_time_start) && (Hour_Rtc < peak_time_stop)){
            // if (change_peak_non_peak){
            //   //Energy_Day = 0;
            //   //Energy_Month = 0;
            //   change_peak_non_peak = false;
            // }
        energy_day_peak +=  Energy_Hour;  
        energy_month_peak += Energy_Hour; 
        //Energy_Day += Energy_Hour;
       // Energy_Month += Energy_Hour;
    }
    //else {
            // if (!change_peak_non_peak){
            //  // Energy_Day = 0;
            // //Energy_Month = 0;
            //   change_peak_non_peak = true;
            // }
       //energy_day_non_peak += Energy_Hour;     
       // Energy_Day += Energy_Hour;
       // Energy_Month += Energy_Hour;
    //}
  
  Energy_Day += Energy_Hour;
  Energy_Month += Energy_Hour;  
  //LH++;
  EE_Hour[LH+1] = Energy_Hour;
  print_master(0);
  // Serial.printf("\n\n\n");
  // Serial.printf( "Year  is =%i,Month  is =%i,Day  is =%i,Hour is=%i,\n",year_Rtc,month_Rtc,day_Rtc,Hour_Rtc);
  // Serial.println("***********************************************Hour data Writing to EPPROM****************************************************************************************\n");
  // Serial.printf("Lh is=%i,Hour_Rtc is=%i,EEprom_Put=%i\n", LH, Hour_Rtc, (EEPROM_ADD_Hour + (LH * Lenth_Bytes)));
  // Write data to EEPROM
  EEPROM.put(EEPROM_ADD_Hour + ((LH+1) * Lenth_Bytes), EE_Hour[LH+1]);
  EEPROM.commit();

  Met_Start();


  Energy_Hour = 0;
  Run_Energy_Hour = 0;
  Energy_Min = 0;
  // Serial.println("***********************************************Hour data Writing to EPPROM******ENDS**********************************************************************************");Serial.printf("\n\n\n");
  //  Serial.printf("\n\n\n");
  Days_Feed();
  Month_Feed();
  //  xSemaphoreGive(xSemaphore);
  // Serial.printf("\nXsemiphore give  in Hours \n");
  // Send_Data();
}


void Days_Feed()


{
  // Energy_Day=0;

  uint8_t Last_Day = LD;

  // Serial.printf("\n\n\n");
  // Serial.println("*********************************************** POW_Getting day data******Starts**********************************************************************************");
  // Serial.printf("\n\n");
  //Serial.printf("\n Current_Day=%i,Energay_Day=%g \n",day_Rtc,Energy_Day);
  //if ((Hour_Rtc > peak_time_start) && (Hour_Rtc < peak_time_stop)){
  EE_Day_Peak[Last_Day] = energy_day_peak;
  //EE_Day[Last_Day] = 0;
  //}
//else{
  EE_Day[Last_Day] = Energy_Day-energy_day_peak;
  //EE_Day_Peak[Last_Day] = 0;
//}
//EE_Day[Last_Day] = Energy_Day;
print_master(0);
print_master(0);
  //   EEPROM.begin(EEPROM_SIZE);
  //Serial.printf("EEprom_Put=%i\n",EEPROM_ADD_Day+(Last_Day * Lenth_Bytes));
  uint32_t change_1 = 0;
  uint16_t EE_Day_Peak_uint_16[32] = {0};
  uint16_t EE_Day_uint_16[32] = {0};

 // for (int i = 1 ; i<32 ; i++){
    float change = 0;
   // if ((i > peak_time_start) && (i < peak_time_stop))
   // {
      change = EE_Day_Peak[Last_Day]*100;
      change_1 = *((uint32_t *)&change);
      EE_Day_Peak_uint_16[Last_Day] = (0xFFFF)&(change_1);
     // EE_Day_uint_16[i] = 0;
   // }

   // else{
      change = EE_Day[Last_Day]*100;
      change_1 = *((uint32_t *)&change);
      EE_Day_uint_16[Last_Day] = (0xFFFF)&(change_1);
     // EE_Day_Peak_uint_16[i] = 0;
    //}


 // }
  //EEPROM.put(EEPROM_ADD_Day + ((Last_Day) * Lenth_Bytes), EE_Day_uint_16[Last_Day]);
  //EEPROM.put(EEPROM_ADD_Day + ((Last_Day) * (Lenth_Bytes))+2, EE_Day_Peak_uint_16[Last_Day]);

  EEPROM.put(EEPROM_ADD_Day + (Last_Day * Lenth_Bytes), EE_Day[Last_Day]);// important 
  EEPROM.put(((EEPROM_ADD_Day + (32 * Lenth_Bytes)) + (Last_Day * Lenth_Bytes)), EE_Day_Peak[Last_Day]);

  //EEPROM.put(EEPROM_ADD_Day+(Last_Day * sizeof(EE_Day)), EE_Day[Last_Day]);
  EEPROM.commit();
}


void Month_Feed()


{
  // Energy_Month=0;

  uint8_t Last_Months = LM;

  //Serial.printf("\n\n\n");
  //Serial.println("*********************************************** POW_Getting Months data******Starts**********************************************************************************");
  //Serial.printf("\n\n");
  //Serial.printf("\n Current_Month=%i,Energay_Month=%g \n",month_Rtc,Energy_Month);
  // if ((Hour_Rtc > peak_time_start) && (Hour_Rtc < peak_time_stop))
  // EE_Month_Peak[Last_Months] = Energy_Month;
  // else
  EE_Month_Peak[Last_Months] = energy_month_peak;
  EE_Month[Last_Months] = Energy_Month - energy_month_peak;

  //  EEPROM.begin(EEPROM_SIZE);

print_master(0);
print_master(0);
  //  Serial.printf("EEprom_Put=%i\n",EEPROM_ADD_Month+(Last_Months * sizeof(Month_Data)));
  // Write data to EEPROM
  EEPROM.put(EEPROM_ADD_Month + (Last_Months * Lenth_Bytes), EE_Month[Last_Months]);
  EEPROM.put(((EEPROM_ADD_Month + (13 * Lenth_Bytes))+(Last_Months * Lenth_Bytes)), EE_Month_Peak[Last_Months]);
  EEPROM.commit();
  // Serial.printf("\n\n\n");
  // Serial.println("***********************************************Month POW   Getting day data******Ends**********************************************************************************");
  //Serial.printf("\n\n\n");
  //  Serial.println("*************************************************************EEPROM POF****&& Days change Check*****************Ends*********************************************");
}





void Met_Start()

{
  Get_Time();
  S_Data.Hour = Hour_Rtc;
  S_Data.day = day_Rtc;
  S_Data.month = month_Rtc;
  S_Data.year = year_Rtc;


  // Serial.printf("\n\n\n");

  Serial.println("***********************************************Meter Writing to EPPROM** Hours inf**************************************************************************************");
 Serial.printf("\n Meter Writing Date Time=");
  Serial.print("Year=");
  Serial.print(S_Data.year);
  Serial.print(",Month= ");
  Serial.print(S_Data.month);
  Serial.print(",Day= ");
  Serial.print(S_Data.day);
  Serial.print(" ,Hour: ");
  Serial.println(S_Data.Hour);


  //EEPROM.begin(EEPROM_SIZE);

  Serial.printf("Meter Start_add is=%i\n", EEPROM_ADD_Meter_Start);
  // Write S_S_Data to EEPROM
  // EEPROM.put(EEPROM_ADD_Meter_Start+( DPS * sizeof(Meter_Start)), S_Data[ DPS]);
  EEPROM.put(EEPROM_ADD_Meter_Start, S_Data);


  EEPROM.commit();
  //Serial.println("***********************************************Meter to EPPROM******ENDS**********************************************************************************");

  // Serial.printf("\n\n\n");
}


void Meter_staus()

{

  if ((RTC_Err != 0))

  {

    Serial.printf("RTC Error\n");
    return;
  }

  Get_Time();

  Run_Energy_Hour = 0;
  Energy = 0;

  Serial.printf("\n\n");
  Serial.printf("Meter Reading Starts************************************************************************\n");

  Meter_Start_t S_Data;
  //Hours_S_Data S_Data;

  //  EEPROM.begin(EEPROM_SIZE);

  // Serial.printf("EEprom_get=%i\n",EEPROM_ADD_Hour+(index * sizeof(PowerS_Data));

  Serial.printf("EEprom_get From Meter Locatin =%i\n", (EEPROM_ADD_Meter_Start));
  // Serial.print(EEPROM_ADD_Hour+(index * sizeof(Hours_S_Data)));

  EEPROM.get(EEPROM_ADD_Meter_Start, S_Data);

  Serial.printf("\n Meter Reading Date Time=");
  Serial.print("Year=");
  Serial.print(S_Data.year);
  Serial.print(",Month= ");
  Serial.print(S_Data.month);
  Serial.print(",Day= ");
  Serial.print(S_Data.day);
  Serial.print(" ,Hour: ");
  Serial.println(S_Data.Hour);
  









  if ((S_Data.year == year_Rtc) && (S_Data.month == month_Rtc) && (S_Data.day == day_Rtc)) {

    Serial.println(" Only Hour May changed  means get day data only");
    Read_EEP_Day();

    // EEPROM.begin(EEPROM_SIZE);

    Serial.printf("EEprom_get_Day_Data from Loaction =%i::\n", (EEPROM_ADD_Day + (day_Rtc * Lenth_Bytes)));

    EEPROM.get(EEPROM_ADD_Day + (day_Rtc * Lenth_Bytes), Temp_Day);
    EEPROM.get((EEPROM_ADD_Day + (32 * Lenth_Bytes)) + (day_Rtc * Lenth_Bytes), Temp_Day_P);
    // EEPROM.get(EEPROM_ADD_Day+(index * Lenth_Bytes), data);

    Serial.print("Power=");
    Serial.println(Temp_Day);

    Energy_Day = Temp_Day;
    Run_Energy_Day = Temp_Day;
    energy_day_peak = Temp_Day_P;



    Serial.printf("Meter Reading Energy Day%g=,Run_Eday=%g\n", Energy_Day, Run_Energy_Day);
  }



  if ((S_Data.year == year_Rtc) && (S_Data.month == month_Rtc)) {

    Serial.println(" Only Day Has changed means hours should Clear && Month data shout get ");
    Read_EEP_Month();



    // EEPROM.begin(EEPROM_SIZE);

    Serial.printf("EEprom_get_Month_Data from Location =%i::\n", (EEPROM_ADD_Month + (month_Rtc * Lenth_Bytes)));

    EEPROM.get(EEPROM_ADD_Month + (month_Rtc * Lenth_Bytes), Temp_Month);
    EEPROM.get(EEPROM_ADD_Month + (13 * Lenth_Bytes) + (month_Rtc * Lenth_Bytes), Temp_Month_P);
    // EEPROM.get(EEPROM_ADD_Month+(index * sizeof(Month_Data)), data);

    Serial.print("Power=");
    Serial.println(Temp_Month);

    Energy_Month = Temp_Month;
    Run_Energy_Month = Temp_Month;
    energy_month_peak = Temp_Month_P;


    Serial.printf("Meter Reading Energy Month =%g,Run_EM=%g \n,", Energy_Month, Run_Energy_Month);

    Serial.println("Meter Reading Ends Here************************************************************************************\n\n");
  }


  if ((S_Data.year != year_Rtc)) {

    Serial.printf("Year Has changed=%i,Last Year is \n", year_Rtc, S_Data.year);
    Month_Clear();
    Day_Clear();
    Hour_Clear();
  }



  if ((S_Data.month != month_Rtc)) {

    Serial.printf("Month Has changed=%i,Last months is=%i \n", month_Rtc, S_Data.month);

    Day_Clear();
    Hour_Clear();
  }

  if ((S_Data.day != day_Rtc)) {

    Serial.printf("DayHas changed=%i,Last months is=%i \n", month_Rtc, S_Data.month);


    Hour_Clear();
  }
}



void Reset_Meter() {

  Hour_Clear();
  Day_Clear();
  Month_Clear();
  Run_Energy_Hour = 0;
  Run_Energy_Day = 0;
  Run_Energy_Month = 0;
  energy_day_peak = 0;
  energy_month_peak = 0;
  Meter_staus();
  Serial.printf("Meter Has RESET********************************************************************************************************\n\n\n");
}


void Hour_Clear()

{

  Serial.printf("Hourr Has Clear********************************************************************************************************\n");
  for (int i = 1; i < 25; i++) {

    EEPROM.put(EEPROM_ADD_Hour + (i * Lenth_Bytes), 0);
  }
  EEPROM.commit();
}



void Day_Clear()

{
  Serial.printf("Day Has clear********************************************************************************************************\n");
  for (int i = 1; i < 32; i++) {


    EEPROM.put(EEPROM_ADD_Day + (i * Lenth_Bytes), 0);
    EEPROM.put(((EEPROM_ADD_Day + (32 * Lenth_Bytes)) + (i * Lenth_Bytes)), 0);
  }

  EEPROM.commit();
}



void Month_Clear()

{
  Serial.printf("Month Has clear********************************************************************************************************\n");
  for (int i = 1; i < 13; i++) {



    EEPROM.put(EEPROM_ADD_Month + (i * Lenth_Bytes), 0);
    EEPROM.put(((EEPROM_ADD_Month + (13 * Lenth_Bytes))+(i * Lenth_Bytes)), 0);
  }

  EEPROM.commit();
}






void Hour_FTM()

{
  //
  Get_Time();
  Serial.printf("First time intalizatin\n");
  Print_Date();

  LH = Hour_Rtc;
  LD = day_Rtc;
  LM = month_Rtc;
  LY = year_Rtc;


  Serial.printf("First time intalizatin Ends************************\n");
}
