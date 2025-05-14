#include <ADS1X15.h>
ADS1115 ads; /* Use this for the 16-bit version */
const byte interruptPin = 4;




// indoor sensor Varaibles start here
double R11 = 5100.0;   // voltage divider resistor value
double Beta = 3470.0;  // Beta value
double To = 298.15;    // Temperature in Kelvin for 25 degree Celsius
double Ro = 5000.0;
double TC, TR, Vs = 5,  Rt = 0, RT1 = 0;
int16_t adc0,adc1,adc3; // we read from the ADC, we have a sixteen bit integer as a result
float volts0, volts1,volts3;
float voltmv0, voltmv1,voltmv3;
//bool start = true;



void Temp_setup()

{

 ads.begin();


}

void Temp_intilaize()

{

if(ads.isConnected())
  {
   Coil_Sensor();
    Errors_info[4] = 0;
  }

   if(!ads.isConnected() && Esp_32=="RUN")
  {
    Serial.println("Error ADS is not connected in Temp_intilaize");  
   Errors_info[4] = 1; //E7 means ADS is not properly connected
  }
 
  
}





 




void Coil_Sensor() 

{
 // Serial.println("initialize ADS.");
 if (first_time==0){
adc0 = ads.readADC(0);
  adc1 = ads.readADC(1);
  adc3 = ads.readADC(3);
  voltmv0 = adc0 * 0.1875;
  voltmv1 = adc1 * 0.1875;
  voltmv3 = adc3 * 0.1875;
  volts0 = ads.toVoltage(adc0);
  volts1 = ads.toVoltage(adc1);
  volts3 = ads.toVoltage(adc3);

  Vs=volts3;
 // Serial.print("Vs is ");
 // Serial.println(Vs);
  RT1 = R11 * (Vs - volts0) / volts0;
  TR = 1 / (1 / To + log(RT1 / Ro) / Beta);
  Room_sensor = TR - 273.15;  // Celsius
  Rt = R11 * (Vs - volts1) / volts1;
  TC = 1 / (1 / To + log(Rt / Ro) / Beta);
  Coil_sensor = TC - 273.15;  // Celsius

  first_time = 1;
  return;
}


  adc0 = ads.readADC(0);
  adc1 = ads.readADC(1);
  adc3 = ads.readADC(3);
  voltmv0 = adc0 * 0.1875;
  voltmv1 = adc1 * 0.1875;
  voltmv3 = adc3 * 0.1875;
  volts0 = ads.toVoltage(adc0);
  volts1 = ads.toVoltage(adc1);
  volts3 = ads.toVoltage(adc3);
 

  Vs=volts3;


  Rt = R11 * (Vs - volts1) / volts1;
  TC = 1 / (1 / To + log(Rt / Ro) / Beta);
  Coil_sensor = TC - 273.15;  // Celsius


 if (n<5){
 
 
  RT1 = R11 * (Vs - volts0) / volts0;
  TR = 1 / (1 / To + log(RT1 / Ro) / Beta);
  rs += TR - 273.15;  // Celsius
  n++;
  delay(10);
  delay(10);
 }
 if (n==5){
  Room_sensor = rs/5;
 
  n=0;
  rs=0;
 
  }
 /* Serial.print("Room Sensor =");
  Serial.print(Room_sensor);
  Serial.print(" Coil Sensor =");
  Serial.print(Coil_sensor);
  Serial.println("");*/
}




void Temp_Center() 

{
  if(Stop_Stop=="No") /// cant executre if error occur temp sensor may give NAN discounter minu with float set Temp controller REboot again & again.
 {

  if(Mode=="D" && Esp_32=="RUN")       // If Mode is dry Delta Temp is Fixed to 1.9

  {
   //  Delta_Temp=1.9;
   //  LEDS(HIGH,LOW);
     Fan_control(Fan_Status,"Dry_Mode");
    

  }


 



   
   L_Auto_Temp=Auto_Temp;   // Check any change in when auto mode H or C 
  Delta_TC();  // Cooling mode delta _T calclation
  Delta_TH();  // Heating mode delta_T  calclation

   if((Auto_Temp!=L_Auto_Temp) && Mode=="A" && Esp_32=="RUN")

    {
      Mode_Change="Yes";
      Serial.print("Mode cahnge******************************************yes*************************************From Auto_Temp******* ");
}
}
}


void Delta_TC() 
{
  if (Esp_32=="RUN" && (Mode == "C" || Mode=="F" || Mode=="D" ) && Set_Temp >= Room_sensor)  // in suummer cool mode Romm temp is less then set Temp e.g Room temp is 22,set Temp is 23
  {
    Delta_Temp = 0;                                                            // Delata is important 
   // Serial.printf("********************************************Making Delta in in Cooling  Zero********************\n\n\n");
  }
  if (Esp_32=="RUN" && (Mode == "C" || Mode=="F" || Mode == "A" || Mode=="D") && Set_Temp <= Room_sensor) // for Auto mode cooling reuires set suto_temp=c
  {
    Delta_Temp = Room_sensor - Set_Temp;
   // Serial.printf("********************************************Making Delta in in Cooling ********************\n\n\n");
    Auto_Temp="C";
     
     if((Mode!="D") && (Mode!="F"))
      {
        bitWrite(Ble_8Bit2, 7, 0);  // mode c
        bitWrite(Ble_8Bit2, 6, 0);  // mdec
      }
     
   
  }
}
void Delta_TH() 

{
  if (Esp_32=="RUN" && Mode == "H" && Set_Temp <= Room_sensor)  // in winter heat mode Romm temp is greater then set Temp e.g Room temp is 24,set Temp is 23
  {
    Delta_Temp = 0;
  // Serial.printf("********************************************Making Delta in in Heating Zero********************\n\n\n");
  }
 
  if (Esp_32=="RUN" && (Mode == "H" || Mode == "A") && Set_Temp >= Room_sensor) 
  {
    Delta_Temp = Set_Temp - Room_sensor;
   // Serial.printf("********************************************Making Delta in in Heating********************\n\n\n");
    Auto_Temp="H";
   
        bitWrite(Ble_8Bit2, 7, 0);  // mode H
        bitWrite(Ble_8Bit2, 6, 1);  //
       

  
   
  }
  
 
 



}



