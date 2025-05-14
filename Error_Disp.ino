

void Error_Stop_Stop()

{
  Print_Error = "None";
  for (int i = 0; i < 30; i++)

  {

    if (Errors_info[i] != 0)  // when Error occur it set Stop_Stop Yes && wait for 30 sec to stop_timer change from 1 to 2 to confirm error
    {

    Stop_Stop = "Yes";
 
       Serial.println("Stop Everything*********************in*********************************Errors*********************Erorr_STOP_STOP");

      if (i < 10) {

        Print_Error = Error_Data[i];
        return;
      }
      if (i >= 10 && i < 20)

      {

        Print_Error = Error_Data1[i - 10];
        return;
      }

      if (i >= 20 && i <= 30)

      {

        Print_Error = Error_Data2[i - 20];
        return;
      }

    }  // main if

  }  // for

}  // void



void Error_Disp()

{
    if(Esp_32=="RUN")
 {
     for (int i =0; i<30;i++)
  {
     if(Errors_info[i]!=0)  // when Error occur it will run only one time so ticker timer can inatalixe again & again
    {
      //  Serial.println("Stop Everything*********************in*********************************Errors*********************Erorr_Disp");
       Errors_No=i;
       Stop_Stop="Yes";
       Serial.printf("Errors_No=%u\n",Errors_No);
       //print(Errors_No);
       // Serial.println("");
       
         Fan_control("OF","Error_OFF"); // Stop Fan
        

      LCD_Error_Disp(Errors_No);
    } //end of if

  }  // ENd of for


 } // end if power on
} // end of void




void  LCD_Error_Disp(uint8_t Er_No)

{

    ALL_OF();

   
    switch (Er_No) 
 {
     case 0:
     Error_0();
     break;

     case 1:
     Error_1();
     break;

     case 2:
     Error_2();
     break;


     case 3:
     Error_3();
     break;

     case 4:
     Error_4();
     break;

     case 5:
     Error_5();
     break;

     case 6:
     Error_6();
     break;

     case 7:
     Error_7();
     break;

     case 8:
     Error_8();
     break;

     case 9:
     Error_9();
     break;

     case 10:
     Error_10();
     break;

     case 11:
     Error_11();
     break;

     case 12:
     Error_12();
     break;

     case 13:
     Error_13();
     break;

     case 14:
     Error_14();
     break;

     case 15:
     Error_15();
     break;

     case 20:
     Error_20();
     break;

     case 21:
     Error_21();
     break;

     case 22:
     Error_22();
     break;

     case 23:
     Error_23();
     break;

     case 24:
     Error_24();
     break;

     case 25:
     Error_25();
     break;



 }







}



void Errors_Print()

{

//Serial.println("Stop Everything******************************Loop************************Error_Print");
       Serial.print("Errors_No_in_loop=");
    Serial.print(Errors_No);
    Serial.println("");
     Serial.println("");

}

