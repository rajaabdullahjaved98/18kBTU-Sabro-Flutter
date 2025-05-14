
String Update = "Yes";





void Task_Setup()

{


  xTaskCreatePinnedToCore(Stepper, "Task1", 10000, NULL, 1, &Task1, 0);     // Stepper
  xTaskCreatePinnedToCore(Fan_Run, "Task2", 4000, NULL, 1, &Task2, 0);      // indoor fan
  xTaskCreatePinnedToCore(Eeprom_Save, "Task3", 4000, NULL, 1, &Task3, 1);  // EEprom Save
  xTaskCreatePinnedToCore(EspNow, "Task4", 4000, NULL, 1, &Task4, 0);       // Espnow
  xTaskCreatePinnedToCore(Min_KW, "Task5", 4000, NULL, 1, &Task5, 0);
  xTaskCreatePinnedToCore(Comp_Task, "Task6", 4000, NULL, 1, &Task6, 1);

}







void EspNow(void* pvParameters)  // core o program must have wifi
{
  for (;;)  // must used permant for loop for core programming
  {
   Run_Data();
   // Espnow_Run_Data();
   static unsigned long lastMqtt = 0;

   if ((millis () - lastMqtt) > 5000){
   WiFiMqtt();
   lastMqtt = millis ();
   }

    if (CTime == 1)  // Lcd has send coomand to chane time Ctime will zero in TRc Set_time Ctime will 1 on espnow Routine

    {
      Set_Time();
    }

    if (POM_RESET == 786786373)   // All EEPROM Meter Reaet
    {

      Reset_Meter();
      POM_RESET = 0;
    }
     if ((Update == "Yes") && (RTC_Err == 0))
   {
     
     Cal_Power();
    check_peakness();
   // trend_analysis();
    
   // run_run();
     // Set_Time_inc();
      new_hour();
      Read_All();
      //Espnow_ALL_Data();
      Update = "No";
    }

     if (RTC_Err == 2)  // If Cell in RTC Lost send data to Lcd
    {
      Read_All();
      //Espnow_ALL_Data();
      Update = "No";
    }

  lcd_control_check();
    vTaskDelay(1000 / portTICK_PERIOD_MS);  // 10 seconds
  }
}




void Stepper(void* pvParameters)  // core o program must have wifi
{
  for (;;)  // must used permant for loop for core programming
  {
    Stepper_Main();
    vTaskDelay(pdMS_TO_TICKS(500));

    // Serial.print("Task1 running on core************************************************************************************** ");
    // Serial.println(xPortGetCoreID());
  }
}  // end of void




void Fan_Run(void* pvParameters)  // core o program must have wifi
{
  for (;;)  // must used permant for loop for core programming
  {
    // Serial.println("***********in Task3****************");
    if (Esp_32 == "RUN" && Stop_Stop == "No")  // ALL Fan_run routines Runs From Here
    {
      if (Mode == "H" || Auto_Temp == "H") {
        Heating_Fan_Control("N");
      }

      if (Mode != "H" && Auto_Temp != "H") {
        //  Serial.printf("\n in Task Fan=%s\n", Fan_Status.c_str());
        Fan_control(Fan_Status, "NC");
        bitWrite(Ble_8Bit4, 4, 0);  //Fan Nc
      }
    }
    Pressure_Cal();
     unit_calculate_1();
    // Serial.println("***********in Fan Run****************Task2\n");
    vTaskDelay(pdMS_TO_TICKS(10000));
  }
}


void Eeprom_Save(void* pvParameters)  // core o program must have wifi
{
  for (;;)  // must used permant for loop for core programming
  {
    if (Esp_32 == "RUN" && Stop_Stop == "No")  // ALL Fan_run routines Runs From Here
    {
      EEprom_Confirm();
    }
   
    //Serial.println("***********in EEprom save****************Task3*****************************\n");
    vTaskDelay(5000 / portTICK_PERIOD_MS);
  }
}

void Min_KW(void* pvParameters)  // core o program must have wifi
{
  for (;;)  // must used permant for loop for core programming
  {
    Update = "Yes";
    if (rtc.begin()) {
      if (RTC_Err != 2) {
        // Serial.printf("RTC in Task Making Error =0 ***********************************************************************\n");
        RTC_Err = 0;
         Inv_Error="None";
      R_Data.SL_Code=0;
      }
    }
   
   

    vTaskDelay(60000 / portTICK_PERIOD_MS);  // 60 seconds
  }
}



void Comp_Task(void* pvParameters)  // core o program must have wifi
{
  for (;;)  // must used permant for loop for core programming
  {
    Comprun=true;
   Serial.printf("Comp_Task Making Comprun **********************************************************************true*\n");
   

    vTaskDelay(pdMS_TO_TICKS(40000)); //60 sec
  }
}





void System_OFF()  // core o program must have wifi
{



  Serial.printf("\n Function**********************************************************************************Syetem_Off\n");


  if (Esp_32 == "Shut_Down" && Power == "OFF")  // ALL Fan_run routines Runs From Here

  {
    digitalWrite(fan_low, LOW);
    digitalWrite(fan_mid, LOW);
    digitalWrite(fan_high, LOW);
    sending(Manual_fan_speed, Write, data_HB, Motor_of);
    sending(Mode_Inv, Write, data_HB, inv_Mode_Of);
   // sending(Manual_4Way, Write, data_HB, R_Valve_Of); // check fors sound in heating


    Serial.printf("\nShut_down********************************************************Inverter Board **************************************Sytem ShutDown\n");
    digitalWrite(Inverter_OFF_PIN, LOW);
    digitalWrite(PIN_HT1621_BL, LOW);
    ht.sendCommand(HT1621::LCD_OFF);
    EEP = "YES";
    Swing_Stop();
    Buzzer_Tone();
    stepper_Home();
    caliberated = false;


    EEprom_Confirm();
    delay(100);
    vTaskSuspend(Task1);
    delay(100);
    vTaskSuspend(Task2);
    delay(100);
    vTaskSuspend(Task3);
    delay(100);
    //vTaskSuspend(Task4);
    //delay(100);
    vTaskSuspend(Task5);
    delay(100);
    vTaskSuspend(Task6);
    delay(100);
    Power_var = 0;
   
  }

  ShutDown_Timer.detach();
}
