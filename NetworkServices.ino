void runNetworkCore() {
  static bool initialized = false;

  // One-time setup: Dual-mode, AP, WebSocket
  if (!initialized) {
    WiFi.mode(WIFI_AP_STA);
    Serial.println("WIFI SET TO DUAL MODE");

    loadCredentials(); // Reads routerSSID, routerPASS, deviceName
    WiFi.softAP(deviceName.c_str(), "");
    Serial.println("AP Started: " + deviceName);

    startWebSocketServer(); // Starts AsyncWebSocket
    client.setServer(mqttServer, mqttPort);
    client.setCallback(callback);
    initialized = true;
  }

  // Reconnect Wi-Fi if disconnected
  if (WiFi.status() != WL_CONNECTED && routerSSID != "" && routerPASS != "") {
    Serial.println("Attempting WiFi reconnect...");
    WiFi.begin(routerSSID.c_str(), routerPASS.c_str());

    unsigned long startTime = millis();
    while (WiFi.status() != WL_CONNECTED && millis() - startTime < 10000) {
      delay(500);
      Serial.print(".");
    }

    if (WiFi.status() == WL_CONNECTED) {
      Serial.println("\nWiFi connected!");
      Serial.println("IP: " + WiFi.localIP().toString());

      initializeMqttTopics();
    } else {
      Serial.println("\nWiFi reconnect failed.");
    }
  }

  // MQTT Reconnect (non-blocking)
  if (!client.connected()) {
    reconnectMqtt(); // Includes internal retry logic
  }

  // Maintain MQTT and WebSocket connections
  client.loop();
  ws.cleanupClients();
  webSocketSend(); // Sends state data to all WebSocket clients

  uint8_t payload[125];
  buildPayload(payload);
  // Publish to MQTT
  if (client.connected()) {
    if (client.publish(publishTopic, payload, 125)) {
      Serial.println("MQTT Payload published successfully");
    } else {
      Serial.println("MQTT Publish failed");
    }
  }
}

void buildPayload (uint8_t* payload) {
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
}
