const int RPM_INCREMENT = 60;
const int RPM_TOLERANCE = 60;

const int Lac_numPoints = 50;

struct Lac_DataPoint {
  float Lac_ce;  // Current Energy
  int Lac_rpm;   // Lac_rpm
};

// Sorted by Lac_ce in asLac_cending order
 Lac_DataPoint Lac_energyData[Lac_numPoints] = {
    {0.21, 1000}, {0.25, 1050}, {0.35, 1100}, {0.41, 1200}, {0.43, 1250},
    {0.45, 1300}, {0.47, 1350}, {0.50, 1400}, {0.53, 1480}, {0.55, 1440},
    {0.56, 1500}, {0.57, 1550}, {0.61, 2100}, {0.65, 2160}, {0.69, 2500},
    {0.71, 2560}, {0.73, 2620}, {0.76, 2700}, {0.77, 2740}, {0.81, 2800},
    {0.82, 2860}, {0.83, 2920}, {0.84, 2980}, {0.87, 3040}, {0.90, 3100},
    {0.95, 3160}, {1.00, 3180}, {1.03, 3240}, {1.06, 3320}, {1.09, 3380},
    {1.11, 3400}, {1.18, 3460}, {1.20, 3500}, {1.25, 3540}, {1.31, 3600},
    {1.35, 3660}, {1.38, 3720}, {1.40, 3780}, {1.42, 3800}, {1.45, 3840},
    {1.48, 3900}, {1.52, 3960}, {1.58, 4000}, {1.62, 4060}, {1.65, 4100},
    {1.68, 4160}, {1.69, 4250}, {1.70, 4300}, {1.75, 4400}, {1.77, 4500}
};




void Run_Rs()


{
  if (!BRPM || BRPM_counter >= 7) 
  {
     BRPM_counter++;

    if (BRPM_counter < 2) 
    {
      Base_RPM_PKRS = calculate_Lac_rpm(Target_Energy);
      Comperssor_RMode = "RS_BRPM";
      Comperssor_Pkrs_Mode = "RS_Base";
    }
    else if (BRPM_counter > 2 && Energy != Target_Energy)

    {
      Base_RPM_PKRS = calculateNewRPM(Comperssor_Running_RPM, Energy, Target_Energy);
      Comperssor_RMode = "adjust_RPM";
      Comperssor_Pkrs_Mode = "RS_adjust";
    }

    if (BRPM_counter >= 6) {
      BRPM = false;
      BRPM_counter = 0;
    }
    Run_Rpm = Base_RPM_PKRS;


    return;
  }



  if (Money_Equal <= 1)

  {
    Comperssor_RMode = "RS_RPM_Lock";
    Comperssor_Pkrs_Mode = "RS_Lock";
    return;
  }

  if (E_cal == false || OD_Motor_Status == "OFF")

  {
    Comperssor_RMode = "E_cal_false";
    Comperssor_Pkrs_Mode = "ODM_OFF";
    return;
  }




  if ((Energy > Target_Energy) && (OD_Motor_Status == "ON")) {

    RS_RPM = Comperssor_Running_RPM - 60;
    Comperssor_RMode = "RS_Target--";
    Comperssor_Pkrs_Mode = "RS_Target--";
    Run_Rpm = RS_RPM;
  }

  else if ((Energy < Target_Energy) && (OD_Motor_Status == "ON")) {


    RS_RPM = Comperssor_Running_RPM + 60;
    Comperssor_RMode = "RS_Target++";
    Comperssor_Pkrs_Mode = "RS_Target++";
    Run_Rpm = RS_RPM;
  }

  E_cal = false;
}





/*int calculateLac_rpm(float targetEnergy) {
    // Handle edge cases
    if (targetEnergy <= Lac_energyData[0].Lac_ce) return Lac_energyData[0].Lac_rpm;
    if (targetEnergy >= Lac_energyData[ Lac_numPoints-1].Lac_ce) return Lac_energyData[ Lac_numPoints-1].Lac_rpm;
    
    // Find the interval where the target energy lies
    int i = 0;
    while (i <  Lac_numPoints - 1 && Lac_energyData[i+1].Lac_ce < targetEnergy) {
        i++;
    }
    
    // Perform linear interpolation
    float Lac_ce0 = Lac_energyData[i].Lac_ce;
    float Lac_ce1 = Lac_energyData[i+1].Lac_ce;
    int Lac_rpm0 = Lac_energyData[i].Lac_rpm;
    int Lac_rpm1 = Lac_energyData[i+1].Lac_rpm;
    
    float t = (targetEnergy - Lac_ce0) / (Lac_ce1 - Lac_ce0);
    int interpolatedLac_rpm = static_cast<int>(Lac_rpm0 + t * (Lac_rpm1 - Lac_rpm0));
    
    return interpolatedLac_rpm;

}
*/

int calculate_Lac_rpm(float targetEnergy) {
  // Handle edge cases
  if (targetEnergy <= Lac_energyData[0].Lac_ce) return Lac_energyData[0].Lac_rpm;
  if (targetEnergy >= Lac_energyData[Lac_numPoints - 1].Lac_ce) return Lac_energyData[Lac_numPoints - 1].Lac_rpm;

  // Find the interval where the target energy lies
  int i = 0;
  while (i < Lac_numPoints - 1 && Lac_energyData[i + 1].Lac_ce < targetEnergy) {
    i++;
  }

  // Perform linear interpolation
  float Lac_ce0 = Lac_energyData[i].Lac_ce;
  float Lac_ce1 = Lac_energyData[i + 1].Lac_ce;
  int Lac_rpm0 = Lac_energyData[i].Lac_rpm;
  int Lac_rpm1 = Lac_energyData[i + 1].Lac_rpm;

  float t = (targetEnergy - Lac_ce0) / (Lac_ce1 - Lac_ce0);
  int interpolatedLac_rpm = static_cast<int>(Lac_rpm0 + t * (Lac_rpm1 - Lac_rpm0));

  return interpolatedLac_rpm;
}





float calculateNewRPM(float currentRPM, float currentEnergy, float targetEnergy) {
  if (currentEnergy == 0) {
    Serial.println("Error: Current energy cannot be zero.");
    return -1;  // Return an error value
  }

  // Calculate theoretical new RPM
  float ratio = targetEnergy / currentEnergy;
  float theoreticalRPM = currentRPM * sqrt(ratio);

  // Clamp the RPM within valid range
  theoreticalRPM = constrain(theoreticalRPM, Min_Rpm, Max_Rpm);

  // Find nearest valid RPM step (960, 1020, 1080, ..., 4500)
  int steps = round((theoreticalRPM - Min_Rpm) / RPM_INCREMENT);
  float nearestStepRPM = Min_Rpm + (steps * RPM_INCREMENT);

  // Ensure we don't exceed Max_Rpm due to rounding
  nearestStepRPM = constrain(nearestStepRPM, Min_Rpm, Max_Rpm);

  // If within tolerance of current RPM, keep current RPM
  if (fabs(theoreticalRPM - currentRPM) <= RPM_TOLERANCE) {
    return currentRPM;
  }

  // If within tolerance of a standard step, use that step
  if (fabs(theoreticalRPM - nearestStepRPM) <= RPM_TOLERANCE) {
    return nearestStepRPM;
  }

  // Default case: use the nearest standard step
  return nearestStepRPM;
}
