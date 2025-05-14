


// Define step constant
#define MotorInterfaceType 4




int Stepper_Current_Position=0;
int Stepper_Distence_ToGO=0;
int Stepper_Target_Position=0;



void Motor_Setup()
{

   myStepper.setMaxSpeed(1000.0);
    myStepper.setAcceleration(200.0);
     myStepper.setSpeed(100);
    
}


void Stepper_Main()

{
//Serial.printf("\n in Stepper ********************************************************************Main_Function\n");

 



 if (Power_var == 0) // First time wapda power come
  {
    myStepper.setMaxSpeed(1000.0);
    myStepper.setAcceleration(200.0);
    myStepper.setSpeed(1000);
    stepper_Home();
    Power_var = 1;
   // Serial.printf("in Swing_var ********************************************************************Power var 0");
   
  }


  if (Power_var == 1 && Esp_32=="RUN") // Remote power on 
  {
     myStepper.setMaxSpeed(1000.0);
    myStepper.setAcceleration(200.0);
    myStepper.setSpeed(1000);
   stepper_Open();
    myStepper.setMaxSpeed(100.0);
    myStepper.setAcceleration(20.0);
     myStepper.setSpeed(10);
      Power_var = 2;
    

  }

     if((Mode=="H" ||  Auto_Temp=="H") && (Coil_sensor<=37 || Defrost_mode=="YES")) //  myStepper.currentPosition() ==(50)

       {
          if (myStepper.currentPosition() !=S_Swing)
     {
        stepper_Heating_swing();
     }
        return;

       }





   if (Swing=="ON" && Esp_32=="RUN")
{
  // Serial.print("in Swing_on ********************************************************************Main_Loop");
   Serial.println();
    myStepper.setMaxSpeed(100.0);
    myStepper.setAcceleration(20.0);
     myStepper.setSpeed(10);
      
   
    stepper_swing();
    
    }

}




void stepper_Open()


{ 
   myStepper.setMaxSpeed(1000.0);
    myStepper.setAcceleration(200.0);
    myStepper.setSpeed(1000);
  
  
     // Serial.println("Going UP********************************************************************************in close*******************************************************");
     Stepper_Target_Position=S_Open;
      
         myStepper.runToNewPosition(Stepper_Target_Position);
       

         myStepper.setCurrentPosition(S_Open);
         Stepper_Current_Position=myStepper.currentPosition();
        /* Serial.printf("\n going Down***************************************************************************************** in  Steeper_Open  ****\n");
        Serial.printf("Stepper_Cuurent_Position=%u\n",Stepper_Current_Position);
        Serial.printf("Stepper_distancetogo_=%u\n",Stepper_Distence_ToGO);
        Serial.printf("Stepper_Target_Position=%u\n",Stepper_Target_Position);*/
  }

void stepper_Home()


{
    myStepper.setMaxSpeed(1000.0);
    myStepper.setAcceleration(200.0);
    myStepper.setSpeed(1000);
    
   

   // Serial.println("going Down*****************************************************************************************in open ****");
     Stepper_Target_Position=S_Home;
      // Serial.printf("going up in Stepper Home ***************************************************************************************** means Home \n");
         myStepper.runToNewPosition(Stepper_Target_Position);
         // Serial.printf("My Steeper cuurent position in open 400=%i\n",myStepper.currentPosition());
         
       
}

void stepper_swing()
  
{
  //Serial.printf("My Steeper cuurent position in Swing=%i\n",myStepper.currentPosition());
  // Serial.printf("My Steeper Target position in Swing=%i\n", Stepper_Target_Position);

    
      

      if (myStepper.currentPosition() ==S_Open )
     {
         
       

        Stepper_Target_Position=S_Swing;
     //  Serial.println("going Up*****************************************************************************************in swing S_Swing****");
        
      }

        if (myStepper.currentPosition() ==S_Swing)
     {
       
       
        Stepper_Target_Position=S_Open;
       // Serial.println("going Down*****************************************************************************************in swing S_open ****");
    
      }
           
            myStepper.runToNewPosition(Stepper_Target_Position);
           
}


void stepper_Heating_swing()
{
  myStepper.setMaxSpeed(500.0);
    myStepper.setAcceleration(30.0);
     myStepper.setSpeed(60);

      if (myStepper.currentPosition() !=S_Swing)
     {
      
       Stepper_Target_Position=S_Swing;
       Serial.println("going Up*****************************************************************************************in Stepper_Heating_swing ****");
       }
        Serial.println("rununig *********************************************Stepper Target********************************************in Stepper_Heating_swing ****");

      myStepper.runToNewPosition(Stepper_Target_Position);
      }





void Swing_Stop()

{
  
 if(myStepper.isRunning() && Power_var == 2)
  {
    Stepper_Distence_ToGO=myStepper.distanceToGo();
    Stepper_Current_Position=myStepper.currentPosition();
    Stepper_Target_Position=myStepper.targetPosition();
    myStepper.setCurrentPosition(Stepper_Target_Position);
     Run();
  }
  if(myStepper.isRunning() && (Power_var == 1 || Power_var == 0))
  {
   // Serial.printf("\n In first time opening try to stop\n ");

  }
}



void Run()

{
  //Serial.printf("Stepper_Cuurent_Position=%u\n",Stepper_Current_Position);
 
  // Serial.printf("Stepper_Target_Position=%u\n",Stepper_Target_Position);


   myStepper.setCurrentPosition(Stepper_Current_Position);
   // Serial.printf("Stepper_Cuurent_Position_After Stop =%u\n",Stepper_Current_Position);
  

  //Serial.printf("Stepper_new_Target_Position=%u\n",Stepper_Target_Position);
 }