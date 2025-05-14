void RTC_Setup()

{
  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC Coomucation Lost in Setup");
    RTC_Err = 1;
     Inv_Error="RTC_Lost_Comm";
      R_Data.SL_Code=7;
    return;
  }
  Serial.println("RTC adjustin time in  in SetUp");

 //  rtc.adjust(DateTime(year_Rtc,month_Rtc,day_Rtc, Hour_Rtc, Min_Rtc, Sec_Rtc)); // year, month, day, hour, minute, second // year, month, day, hour, minute, second

// Reset_Meter();  /// will Delete Alk Data
 Meter_staus();
  Hour_FTM();  // first time intalization when POM On or Start
}




void Set_Time()

{
  rtc.adjust(DateTime(dateTime.year, dateTime.month, dateTime.day, dateTime.hour, dateTime.minute, dateTime.second));  // year, month, day, hour, minute, second
  CTime = 0;
  RTC_Err = 0;
   Inv_Error="None";
      R_Data.SL_Code=0;
}


void Print_Date()

{
  Serial.print(year_Rtc);
  Serial.print(",");
  Serial.print(month_Rtc);
  Serial.print(",");
  Serial.print(day_Rtc);
  Serial.print(",");
  Serial.print(Hour_Rtc);
  Serial.print(":");
  Serial.print(Min_Rtc);
  Serial.print(":");
  Serial.print(Sec_Rtc);
  Serial.println("");
}

void Get_Time()

{


  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC Coomucation Lost in run time");
    RTC_Err = 1;
    return;
  }
  DateTime now = rtc.now();
  Sec_Rtc = now.second();
  Min_Rtc = now.minute();
  Hour_Rtc = now.hour();
  day_Rtc = now.day();
  month_Rtc = now.month();
  year_Rtc = now.year();

  if (year_Rtc == 2000 && month_Rtc == 1 && day_Rtc == 1) {
    Serial.println("RTC lost power, From Start in Meter_Status \n");
    RTC_Err = 2;
      Inv_Error="RTC_Cell_Dead";
      R_Data.SL_Code=8;
  }
}



void Set_Time_inc()

{

  Min_Rtc = Min_Rtc + 10;
  if (Min_Rtc >= 59) {
    Min_Rtc = 0;
    Hour_Rtc++;
  }


  if (Hour_Rtc >= 24) {

    Hour_Rtc = 0;

    day_Rtc++;
  }

  if (day_Rtc > 31) {
    day_Rtc = 1;
    month_Rtc++;
  }

  if (month_Rtc > 12) {
    month_Rtc = 1;
    year_Rtc++;
  }
  rtc.adjust(DateTime(year_Rtc, month_Rtc, day_Rtc, Hour_Rtc, Min_Rtc, Sec_Rtc));  // year, month, day, hour, minute, second // year, month, day, hour, minute, second

  delay(50);


}
