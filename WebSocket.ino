void startAccessPoint() {
  WiFi.softAP(deviceName.c_str(), "12345678");
  Serial.println("AP Started: " + deviceName);
}

void saveCredentials(String ssid, String pass, String name) {
  preferences.begin("wifi", false);
  preferences.putString("ssid", ssid);
  preferences.putString("pass", pass);
  preferences.putString("name", name);
  preferences.end();
}

void loadCredentials() {
  preferences.begin("wifi", true);
  routerSSID = preferences.getString("ssid", "");
  routerPASS = preferences.getString("pass", "");
  deviceName = preferences.getString("name", "ESP_AP");
  preferences.end();
}

void onWebSocketMessage(void *arg, uint8_t *data, size_t len) {
  AwsFrameInfo *info = (AwsFrameInfo *)arg;

  if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT) {
    String msg = String((char *)data);
    Serial.println("Received: " + msg);

    DynamicJsonDocument doc(256);
    DeserializationError error = deserializeJson(doc, msg);

    if (error) {
      Serial.println("JSON deserialization failed.");
      return;
    }

    if (doc["type"] == "wifi-credentials") {
      routerSSID = doc["ssid"].as<String>();
      routerPASS = doc["password"].as<String>();
      deviceName = doc["deviceName"].as<String>();
      shouldAttemptWiFi = true;

      saveCredentials(routerSSID, routerPASS, deviceName);

      Serial.println("Router SSID: " + routerSSID);
      Serial.println("Router Password: " + routerPASS);
      Serial.println("Device Name: " + deviceName);

      DynamicJsonDocument ack(256);
      ack["type"] = "acknowledgement";
      ack["status"] = "success";
      ack["deviceName"] = deviceName;
      ack["mac"] = mac;
      String ackJson;
      serializeJson(ack, ackJson);
      ws.textAll(ackJson);
    }

    else if (doc.containsKey("powerOn")) {
      bool power = doc["powerOn"];
      int temp = doc["temp"];
      int fanSpeed = doc["fanSpeed"];
      int mode = doc["mode"];
      bool swing = doc["swing"];
      bool eco = doc["eco"];

      Serial.println("== Received Control Command ==");
      Serial.printf("Power: %s\n", power ? "ON" : "OFF");
      Serial.printf("Temp: %d\n", temp);
      Serial.printf("Mode: %d\n", mode);
      Serial.printf("Fan Speed: %d\n", fanSpeed);
      Serial.printf("Swing: %s\n", swing ? "ON" : "OFF");
      Serial.printf("Eco: %s\n", eco ? "ON" : "OFF");

      // Control values to AC hardware or internal logic
      if (power == 0) {
        // AC POWER OFF
        Power = "OFF";
        bitWrite(Ble_8Bit1, 7, 0);

      } else {
        // AC POWER ON
        Power = "ON";
        bitWrite(Ble_8Bit1, 7, 1);
      }

      Set_Temp = (float)temp;

      if (fanSpeed == 0) {
        // bitWrite(Ble_8Bit1, 3, 0);
        // bitWrite(Ble_8Bit1, 4, 0);
        // bitWrite(Ble_8Bit1, 5, 0);
      } else if (fanSpeed == 1) {
        Fan_Status = "L";
        bitWrite(Ble_8Bit1, 3, 1);
        bitWrite(Ble_8Bit1, 4, 0);
        bitWrite(Ble_8Bit1, 5, 0);
      } else if (fanSpeed == 2) {
        Fan_Status = "M";
        bitWrite(Ble_8Bit1, 3, 0);
        bitWrite(Ble_8Bit1, 4, 1);
        bitWrite(Ble_8Bit1, 5, 0);
      } else if (fanSpeed == 3) {
        Fan_Status = "H";
        bitWrite(Ble_8Bit1, 3, 1);
        bitWrite(Ble_8Bit1, 4, 1);
        bitWrite(Ble_8Bit1, 5, 0);
      } else if (fanSpeed == 4) {
        Fan_Status = "A";
        bitWrite(Ble_8Bit1, 3, 0);
        bitWrite(Ble_8Bit1, 4, 0);
        bitWrite(Ble_8Bit1, 5, 1);
      } else {

      }

      if (mode == 0) {
        // COOLING MODE
        Mode = "C";
        bitWrite(Ble_8Bit2, 6, 0);
        bitWrite(Ble_8Bit2, 7, 0);

        // AUTO MODE OFF
        bitWrite(Ble_8Bit2, 5, 0);
      
      } else if (mode == 1) {
        // FAN MODE
        Mode = "F";
        bitWrite(Ble_8Bit2, 6, 1);
        bitWrite(Ble_8Bit2, 7, 0);

        // SAVING MODE OFF
        Saving_Mode = 0;
        bitWrite(Ble_8Bit2, 4, 0);

        // AUTO MODE OFF
        bitWrite(Ble_8Bit2, 5, 0);

      } else if (mode == 2) {
        // HEATING MODE
        Mode = "H";
        bitWrite(Ble_8Bit2, 6, 0);
        bitWrite(Ble_8Bit2, 7, 1);

        // AUTO MODE OFF
        bitWrite(Ble_8Bit2, 5, 0);

      } else if (mode == 4) {
        // DRY MODE
        Mode = "D";
        bitWrite(Ble_8Bit2, 6, 1);
        bitWrite(Ble_8Bit2, 7, 1);

        // SAVING MODE OFF
        Saving_Mode = 0;
        bitWrite(Ble_8Bit2, 4, 0);

        // AUTO MODE OFF
        bitWrite(Ble_8Bit2, 5, 0);

      } else {
        // AUTO MODE
        Mode = "A";
        bitWrite(Ble_8Bit2, 5, 1);
      
        // SAVING MODE OFF
        Saving_Mode = 0;
        bitWrite(Ble_8Bit2, 4, 0);
      }

      if (swing == 0) {
        Swing = "OF";
        Swing_Stop();
        bitWrite(Ble_8Bit1, 6, 0);
      } else {
        Swing = "ON";
        bitWrite(Ble_8Bit1, 6, 1);
      }

      if (eco == 0) {
        Saving_Mode = 0;
        bitWrite(Ble_8Bit2, 4, 0);
      } else {
        Saving_Mode = 1;
        bitWrite(Ble_8Bit2, 4, 1);
      }
      Buzzer();
      // Optional: acknowledge control packet
      DynamicJsonDocument ack(128);
      ack["type"] = "control-ack";
      ack["status"] = "received";
      String ackJson;
      serializeJson(ack, ackJson);
      ws.textAll(ackJson);
    }
  }
}

void onWebSocketEvent(AsyncWebSocket *server, AsyncWebSocketClient *client,
                      AwsEventType type, void *arg, uint8_t *data, size_t len) {
  if (type == WS_EVT_CONNECT) {
    Serial.println("WebSocket client connected");
    Buzzer();
    // digitalWrite(2, HIGH);

    if (mac.length() > 0) {
      DynamicJsonDocument doc(128);
      doc["type"] = "device-info";
      doc["mac"] = mac;
      String json;
      serializeJson(doc, json);
      client->text(json);
    } else {
      client->text("MAC not set yet");
    }

  } else if (type == WS_EVT_DATA) {
    onWebSocketMessage(arg, data, len);
  } else if (type == WS_EVT_DISCONNECT) {
    Serial.println("WebSocket client disconnected");
    // digitalWrite(2, LOW);
  }
}

void startWebSocketServer() {
  ws.onEvent(onWebSocketEvent);
  server.addHandler(&ws);
  server.begin();
  Serial.println("WebSocket server started");
}

void webSocketSend() {
  const uint16_t payloadSize = 125;
  uint8_t payload[125];
  uint16_t index = 0;

  payload[index++] = R_Data.SL_Code; // 0
  payload[index++] = R_Data.Sec_Rtc; // 1
  payload[index++] = R_Data.Min_Rtc; // 2
  payload[index++] = R_Data.Hour_Rtc; // 3
  payload[index++] = R_Data.day_Rtc; // 4
  payload[index++] = R_Data.month_Rtc; // 5

  payload[index++] = (R_Data.Year_RTC >> 8) & 0xFF; // 6
  payload[index++] = R_Data.Year_RTC & 0xFF; // 7

  payload[index++] = R_Data.Ble_8Bit1; // 8
  payload[index++] = R_Data.Ble_8Bit2; // 9
  payload[index++] = R_Data.Ble_8Bit3; // 10
  payload[index++] = R_Data.Ble_8Bit4; // 11
  payload[index++] = R_Data.Ble_8Bit5; // 12
  payload[index++] = R_Data.mode_pkr_set; // 13
  payload[index++] = R_Data.rupees_send; // 14

  memcpy(&payload[index], &R_Data.Set_Temp, 4); // 15 - 18
  index += 4;
  memcpy(&payload[index], &R_Data.Coil_sensor, 4); // 19 - 22
  index += 4;
  memcpy(&payload[index], &R_Data.Room_sensor, 4); // 23 - 26
  index += 4;
  memcpy(&payload[index], &R_Data.Delta_Temp, 4); // 27 - 30
  index += 4;
  memcpy(&payload[index], &R_Data.Suction_Temp, 4); // 31 - 34
  index += 4;
  memcpy(&payload[index], &R_Data.Calculated_Suction_Pressure, 4); // 35 - 38
  index += 4;
  memcpy(&payload[index], &R_Data.Liquid_Line_temp, 4); // 39 - 42
  index += 4;
  memcpy(&payload[index], &R_Data.Discharge_Temp, 4); // 43 - 46
  index += 4;
  memcpy(&payload[index], &R_Data.Calculated_Discharge_Pressure, 4); // 47 - 50
  index += 4;
  memcpy(&payload[index], &R_Data.ODU_Ambient_Temp, 4); // 51 - 54
  index += 4;
  memcpy(&payload[index], &R_Data.Ac_volts, 4); // 55 - 58
  index += 4;
  memcpy(&payload[index], &R_Data.Dc_Volts, 4); // 59 - 62
  index += 4;
  memcpy(&payload[index], &R_Data.S_cuurent, 4); // 63 - 66
  index += 4;
  memcpy(&payload[index], &R_Data.F_Current, 4); // 67 - 70
  index += 4;
  memcpy(&payload[index], &R_Data.Comp_current, 4); // 71 - 74
  index += 4;

  payload[index++] = (R_Data.Comperssor_Running_RPM >> 8) & 0xFF; // 75
  payload[index++] = R_Data.Comperssor_Running_RPM & 0xFF; // 76

  payload[index++] = R_Data.Inv_Error; // 77
  payload[index++] = R_Data.Falut_Inv_code; // 78

  payload[index++] = (R_Data.Ton_sec >> 24) & 0xFF; // 79
  payload[index++] = (R_Data.Ton_sec >> 16) & 0xFF; // 80
  payload[index++] = (R_Data.Ton_sec >> 8) & 0xFF; // 81
  payload[index++] = R_Data.Ton_sec & 0xFF; // 82

  payload[index++] = (R_Data.Tof_sec >> 24) & 0xFF; // 83
  payload[index++] = (R_Data.Tof_sec >> 16) & 0xFF; // 84
  payload[index++] = (R_Data.Tof_sec >> 8) & 0xFF; // 85
  payload[index++] = R_Data.Tof_sec & 0xFF; // 86

  memcpy(&payload[index], &R_Data.R_Hour_Energy, 4); // 87 - 90
  index += 4;
  memcpy(&payload[index], &R_Data.R_Day_Energy, 4); // 91 - 94
  index += 4;
  memcpy(&payload[index], &R_Data.energy_day_peak, 4); // 95 - 98
  index += 4;
  memcpy(&payload[index], &R_Data.R_Month_Energy, 4); // 99 - 102
  index += 4;
  memcpy(&payload[index], &R_Data.energy_month_peak, 4); // 103 - 106
  index += 4;
  memcpy(&payload[index], &pkr_send_data.current_hour_cost, 4); // 107 - 110
  index += 4;
  memcpy(&payload[index], &pkr_send_data.Current_RS, 4); // 111 - 114
  index += 4;
  memcpy(&payload[index], &pkr_send_data.Current_Energy, 4); // 115 - 118
  index += 4;
  memcpy(&payload[index], &pkr_send_data.Current_unit_price, 4); // 119 - 122
  index += 4;

  ws.binaryAll(payload, 125);
  Serial.println("STATE SENT TO MOBILE THROUGH WEBSOCKET.");
}