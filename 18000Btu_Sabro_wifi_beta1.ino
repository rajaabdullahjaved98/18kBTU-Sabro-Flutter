




#include "main_include.h"

void IRAM_ATTR function_ISR() {
  ir_interrupt_detach= true;
  ir_time_check=millis();
  detachInterrupt(digitalPinToInterrupt(RECVER_PIN));
  flipper_Ir_Data_timer.attach_ms(50, IR_Receiver);
  // never used Serial print or SPi or other time consumed fuction here
}



void setup()
{
  Serial.begin(921600);
  // Serial.setDebugOutput(true);
   pinMode(Inverter_OFF_PIN,OUTPUT);
   //Wire.begin(8, 7);  // new pin Scl & Sda use for sabro card
   // Serial2.begin(2400, SERIAL_8E1, RXD2, TXD2);// 2Hp board
    Serial2.begin(2400, SERIAL_8E1, RXD2, TXD2);
    if( SELECTED_DEVICE == ESP32S3_WROOM_Z)
  {
    Wire.begin(8,9);  // new pin Scl & Sda use for sabro card
  }
  
  Serial.setDebugOutput(true);
 
 Motor_Setup();
 
 
 Temp_setup();
 
  Fan_Setup();
  Button_Setup();
 IR_Setup();
  LCd_Setup();
  
   Buzzer_Tone();
    
    clear_rx();     // Just to clear Buffer rx reciving 16bytes
    Reset_info();
    
     xSemaphore=xSemaphoreCreateMutex();
   
   

esp_task_wdt_deinit();  
esp_task_wdt_config_t wdt_config = {
                .timeout_ms = WDT_TIMEOUT * 1000, // Convert seconds to milliseconds
                .idle_core_mask = (1 << 0)|(1<<1),         // Monitor core 1 and 0 
                .trigger_panic = true             // Enable panic
            };
            esp_task_wdt_init(&wdt_config);       // Pass the pointer to the configuration structure
            esp_task_wdt_add(NULL); 
  digitalWrite(Inverter_OFF_PIN,LOW); // Turn the inverter on 
    

    attachInterrupt(RECVER_PIN, function_ISR, CHANGE);
    flipper.attach(1,sec); // Real time clock software baseTimer after 1sec
  
 
    EE_Month[0] = 21;
    EE_Month_Peak[0] = 22;
    EE_Day[0] = 19;
    EE_Day_Peak[0] = 20;
 
  
   Comperssor_Start_Timer(20);
//  EEPROM.begin(2048);
  EEPROM.begin(2248);
   int eeSize = EEPROM.length();
  Serial.print("EEPROM size:********************************************************************************************== ");
  Serial.println(eeSize);

           
  
  RTC_Setup();
   Eeprom_Read();
  Espnow_setup();
  Task_Setup();

  
        
 
 
}








void loop() 
{
  Time_Total_s=millis();
  Start_Prepare();
  if(Esp_32=="RUN")
 {
      //Serial.printf("\ESP32 run in Loop");
   Remote();
   
   Inverter();
    
  }
    Time_Total_e=millis();
    Time_Total_c=Time_Total_e-Time_Total_s;
  New_Print_Center();
  Run_Print();
  // Pack_print();
  //pprint_ALL();
  // EP_Print();
  check_ir();
 // Mini_Print_Center();
   delay(1000);  /// only to get display
   // pushbutton();/// Push Button rotouine Runs evertime wheather power on or off its emergency switch
   
     esp_task_wdt_reset();
}






 void Remote()

 {

  Temp_intilaize();// main routinue to calcutate TEmp sensor value & intailizat 15 min timer Gas_Err coil_Center call from here
  Temp_Center();  // Note must not Executed if Temp sensor Error esp can Reboot due to Tsensor-Nan so if Stop is NO execute function fan Auto also there
  
   Error_Stop_Stop();  // To make Sure if Error occur variable Stop_Stop must be Yes Double saftey fo Error. can do Stop_Stop=yes
   Error_Disp(); // this fuction control Led Blinking on Error. can do stop_stop=Yes
   LCD_DATA_Update();
    Trend_Ckh();  // in heating Mode chk outdoor Fault
     Motor_Chk_cooling(); // in cooling mode Outmotor waring alarm
   
 
  }

 void Inverter()

 {
 command_center();
 Control_Center();
}

void Start_Prepare()
{
         if(Power!=ML_Power)
    {
          if(Power=="ON")
          {   digitalWrite(Inverter_OFF_PIN,HIGH); // Turn the inverter on 
             Esp_32="RUN";
             
             vTaskResume(Task1);
              vTaskResume(Task2);
              vTaskResume(Task3);
              vTaskResume(Task4);
             vTaskResume(Task5);
               vTaskResume(Task6);
                flipper_Out_Door_Sensor_Timer.attach(30, OutDoor_Sensor_Error);


       
         digitalWrite(PIN_HT1621_BL, HIGH); 
              ht.sendCommand(HT1621::LCD_ON);
              LCD_Temp(Set_Temp);    // Send Lcd Temp
            clear_rx();
             delay(1000);
            Comperssor_Start_Timer(20);
           
            Serial.printf("\Making Esp32 RUN:Last_Power=%S,CPower=%s\n",ML_Power.c_str(),Power.c_str());
        }

            // Serial.printf("\nPower has changed in main Loop:Last_Power=%S,CPower=%s\n",ML_Power.c_str(),Power.c_str());
    }
              ML_Power=Power;
}



