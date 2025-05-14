

void Pressure_Cal()

{
  if(Start_Delay != "No")

  {

    return;
  }

   DP_New=387+1.2903*( Discharge_Temp -54.3);
    Dp_Final=DP_New;

    SL_New=(112*log(Suction_Temp)-143.8);
    SL_final=(257.9+(1.24*Suction_Temp)-(2.05*Discharge_Temp));


  if((Comperssor_Running_RPM>800) && (Comperssor_Running_RPM<1500))

  {
   DP_New=387+1.2903*( Discharge_Temp -54.3);
   Dp_Final=DP_New-30;

  }

  if(Comperssor_Running_RPM>4000) 

  {
   DP_New=387+1.2903*( Discharge_Temp -54.3);
   Dp_Final=DP_New+20;

  }

}
