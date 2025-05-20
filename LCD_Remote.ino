void lcd_control_check() {
  if (four_byte_bool_f) {
    L_Mode = Mode;
    if (operation_mode == false) {
      Set_Temp = Control_Screen.temp_screen;
    }

    if (operation_mode == true) {
      Cutomer_Rs = Control_Screen.temp_screen;
      Saving_Mode = 0;
      bitWrite(Ble_8Bit2, 4, 0);  //saving mode off
      Serial.printf("*********************Making operation Mode true select in Lcd**************************************************************\n\n\n");
    }


    if (bitRead(Control_Screen.control_screen, 0)) {
      Power = "ON";
      bitWrite(Ble_8Bit1, 7, 1);
    } else {
      Power = "OFF";
      bitWrite(Ble_8Bit1, 7, 0);
    }
    if (bitRead(Control_Screen.control_screen, 1)) {
      Swing = "ON";
      bitWrite(Ble_8Bit1, 6, 1);
    } else {
      Swing = "OF";
      Swing_Stop();
      bitWrite(Ble_8Bit1, 6, 0);
    }
    if (bitRead(Control_Screen.control_screen, 2) && (Mode == "C" || Mode == "H") && (operation_mode == false)) {
      Serial.printf("*********************Making  saving in  Lcd On *********************\n\n");
      Saving_Mode = 1;
      bitWrite(Ble_8Bit2, 4, 1);  //saving mode on
      Set_Temp = 27;
    } else {
      Saving_Mode = 0;
      bitWrite(Ble_8Bit2, 4, 0);  //saving mode off
    }
    uint8_t s_value = 4 * bitRead(Control_Screen.control_screen, 5) + 2 * bitRead(Control_Screen.control_screen, 4) + bitRead(Control_Screen.control_screen, 3);
    switch (s_value) {
      case 1:
        Mode = "A";
        bitWrite(Ble_8Bit2, 5, 1);
        Saving_Mode = 0;
        bitWrite(Ble_8Bit2, 4, 0);  //saving mode off
        Serial.printf("*********************Mode Auto select in Lcd\n\n");
        break;  // auto on
      case 2:
        Mode = "C";
        bitWrite(Ble_8Bit2, 7, 0);
        bitWrite(Ble_8Bit2, 6, 0);
        bitWrite(Ble_8Bit2, 5, 0);  // Auto off
        Serial.printf("*********************Mode Cooling select in Lcd\n\n");
        break;
      case 3:
        Mode = "F";
        bitWrite(Ble_8Bit2, 7, 1);
        bitWrite(Ble_8Bit2, 6, 1);
        bitWrite(Ble_8Bit2, 5, 0);  // Auto off
        Saving_Mode = 0;
        bitWrite(Ble_8Bit2, 4, 0);  //saving mode off
        Serial.printf("*********************Mode Fan select in Lcd\n\n");
        break;  // mode fan new bit
      case 4:
        Mode = "H";
        bitWrite(Ble_8Bit2, 7, 0);
        bitWrite(Ble_8Bit2, 6, 1);
        bitWrite(Ble_8Bit2, 5, 0);  // Auto off
        Serial.printf("*********************Mode Heat select in Lcd\n\n");
        break;
      case 5:
        Mode = "D";
        bitWrite(Ble_8Bit2, 7, 1);
        bitWrite(Ble_8Bit2, 6, 0);
        bitWrite(Ble_8Bit2, 5, 0);  // Auto off
        Saving_Mode = 0;
        bitWrite(Ble_8Bit2, 4, 0);  //saving mode off
        Serial.printf("*********************Mode dry select in Lcd\n\n");
        break;

      default: break;
    }
    s_value = 4 * bitRead(Control_Screen.control_screen, 8) + 2 * bitRead(Control_Screen.control_screen, 7) + bitRead(Control_Screen.control_screen, 6);
    switch (s_value) {
      case 1:
        Fan_Status = "L";
        bitWrite(Ble_8Bit1, 5, 0);
        bitWrite(Ble_8Bit1, 4, 0);
        bitWrite(Ble_8Bit1, 3, 1);
        break;
      case 2:
        Fan_Status = "M";
        bitWrite(Ble_8Bit1, 5, 0);
        bitWrite(Ble_8Bit1, 4, 1);
        bitWrite(Ble_8Bit1, 3, 0);
        break;
      case 3:
        Fan_Status = "H";
        bitWrite(Ble_8Bit1, 5, 0);
        bitWrite(Ble_8Bit1, 4, 1);
        bitWrite(Ble_8Bit1, 3, 1);
        break;
      case 4:
        Fan_Status = "A";
        bitWrite(Ble_8Bit1, 5, 1);
        bitWrite(Ble_8Bit1, 4, 0);
        bitWrite(Ble_8Bit1, 3, 0);
        break;
      default: break;
    }
    // Serial.println("Remote data Accquired");
    four_byte_bool_f = false;
    IR_Data_Changes();
    Buzzer();
  }
}