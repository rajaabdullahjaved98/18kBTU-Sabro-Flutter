
#include <ToneESP32.h>



int de1= 50; // for Buzzer delay





int buttonState_power;             // the current reading from the input pin
int lastButtonState_power = LOW;   // the previous reading from the input pin
int powercount=0;
uint8_t B_Read;
String  B_Status="False";
uint8_t B_Logic=0;






void Button_Setup()

{

 
  pinMode(p_button, INPUT);
  Serial.println("In LED Set_UP");

}






void Buzzer()
{
//buzzer.tone(NOTE_DS7,de1);
EEP="YES";                        // if Buzzer Beep then Epprom data is saves

  

//Serial.print("In Buzzer*********************************************************************************************");
}

void Buzzer_Tone()
{
//buzzer.playSabroThree();
//buzzer.tone(NOTE_DS7,de1);
                       // if Buzzer Beep then Epprom data is saves
//Serial.print("In Buzzer*********************************************************************************************");
}

void Buzzer_pair(){
//buzzer.playPair();
}

void Buzzer_unpair(){
//buzzer.playUnpair();
}


void time_beep(){
 // Buzzer_pair();
  delay(100);
 // Buzzer_unpair();
}








// Errors leds Function





void pushbutton()
{
  //long lastDebounceTime = 0;  // the last time the output pin was toggled
 // long debounceDelay =(50);    // the debounce time; increase if the output flickers
  B_Read = digitalRead(p_button);
//  Serial.printf("\nIN Push_Button function ,Buton_Logic is=%u\n",B_Read);
  
  if (B_Read==0 && B_Status=="False") 
  {
flipper_PButton.attach(5,Check_Button); 
B_Status="True";  // is Trure
  
  }
}

void Check_Button()

{

   B_Read = digitalRead(p_button);
   Buzzer();
   Serial.printf("\nIN Button,Buton_Logic is=%u\n",B_Read);
  // Serial.println("");
  // Serial.print("B_Logic=");
  // Serial.print(B_Logic);

 
 if (B_Read==0 )

 {
  
 if(  Power == "OFF" && B_Logic==0)

 {
 Power="ON";
 B_Logic=1;
  Mode = "A";
 bitWrite(Ble_8Bit2, 5, 1); // Auto on

  Fan_control("H","P_BUtton");
 Serial.print("IN Button*************************************************************************Power on ******");
 Serial.printf("\nIN Button,Buton_Logic is=%u\n",B_Logic);
 
  }
 
 if( Esp_32=="RUN" && B_Logic==0)

 {

 //flipper_Main_Stop.attach(3,Compressor_Stop);  // 3* 10 time_counter sec comperssor Rpm Decreased timer in comp_run  main Stop fuction 
 Power = "OFF" ;
 Serial.print("IN Button*************************************************************************Power off ******");
 Serial.printf("\nIN Button,Buton_Logic is=%u\n",B_Logic);


 }

} 

 flipper_PButton.detach();


delay(2000);
B_Status="False"; 
B_Logic=0;

}



