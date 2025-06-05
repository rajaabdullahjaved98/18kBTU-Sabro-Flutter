


void WiFiMqtt() {
  /* if (WiFi.status() != WL_CONNECTED) {
    WiFi.begin(ssid, password);
    Serial.println("Connecting to WiFi...");

    while (WiFi.status() != WL_CONNECTED) {
      Serial.print(".");
    }

    Serial.println(WiFi.localIP());
  } */

  // client.setBufferSize(256);
  // client.setKeepAlive(60);
  // client.setSocketTimeout(60);
  //client.setProtocol(MQTT_VERSION_3_1_1);

  if (!client.connected()) {
    int attempt = 0;
    const int maxAttempts = 5;
    

    while (!client.connected() && attempt < maxAttempts) {
      //Serial.printf("Connecting to MQTT (Attempt %d/%d)...\n", attempt + 1, maxAttempts);
      if (client.connect(clientId.c_str())) {
        Serial.println("Connected to MQTT broker");

        String topic = "sabro/ac/" + mac + "/state";
        Serial.print("Topic Name: ");
        Serial.println(publishTopic);
        client.subscribe(subscribeTopic);
        client.publish(publishTopic, "ESP is online");

        return;
      } else {
        Serial.print("Failed MQTT connection. State=");
        Serial.println(client.state());
        attempt++;
        delay(5000);
      }
    }

    if (!client.connected()) {
      Serial.println("MQTT failed. Starting fallback...");
    }
  }

  // if (!client.connected()) {
    //reconnectMqtt();
  // }

  client.loop();

  // Example payload
  //const char* payload = "Hello from ESP32!";

  // Publish to topic
  //if (client.publish(mqtt_publish_topic, payload)) {
  //Serial.println("Message published successfully");
  //} else {
  //Serial.println("Publish failed");
  //}

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

  // Finally publish the complete payload
  // client.publish(mqttPublishTopic, payload, payloadSize);

  if (client.publish(publishTopic, payload, payloadSize)) {
    Serial.println("Publish successful");
    // Serial.println("Payload: ");
    // for (int i = 0; i < payloadSize; i++) {
    // Serial.println(payload[i]);
    // }

  } else {
    Serial.println("Publish failed");
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
  if (strcmp(topic, subscribeTopic) == 0) {
    if (length == 6) {
      bool power = payload[0];
      int temperature = payload[1];
      int mode = payload[2];
      int fan = payload[3];
      bool swing = payload[4];
      bool eco = payload[5];

      Serial.println("---PAYLOAD FROM FLUTTER---");
      Serial.print("POWER: ");
      Serial.println(power);
      Serial.print("TEMP: ");
      Serial.println(temperature);
      Serial.print("MODE: ");
      Serial.println(mode);
      Serial.print("FAN: ");
      Serial.println(fan);
      Serial.print("SWING: ");
      Serial.println(swing);
      Serial.print("ECO: ");
      Serial.println(eco);

      Set_Temp = (float)temperature;

      if (power == 0) {
        // AC POWER OFF
        Power = "OFF";
        bitWrite(Ble_8Bit1, 7, 0);

      } else {
        // AC POWER ON
        Power = "ON";
        bitWrite(Ble_8Bit1, 7, 1);
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

      if (fan == 0) {
        // bitWrite(Ble_8Bit1, 3, 0);
        // bitWrite(Ble_8Bit1, 4, 0);
        // bitWrite(Ble_8Bit1, 5, 0);
      } else if (fan == 1) {
        Fan_Status = "L";
        bitWrite(Ble_8Bit1, 3, 1);
        bitWrite(Ble_8Bit1, 4, 0);
        bitWrite(Ble_8Bit1, 5, 0);
      } else if (fan == 2) {
        Fan_Status = "M";
        bitWrite(Ble_8Bit1, 3, 0);
        bitWrite(Ble_8Bit1, 4, 1);
        bitWrite(Ble_8Bit1, 5, 0);
      } else if (fan == 3) {
        Fan_Status = "H";
        bitWrite(Ble_8Bit1, 3, 1);
        bitWrite(Ble_8Bit1, 4, 1);
        bitWrite(Ble_8Bit1, 5, 0);
      } else if (fan == 4) {
        Fan_Status = "A";
        bitWrite(Ble_8Bit1, 3, 0);
        bitWrite(Ble_8Bit1, 4, 0);
        bitWrite(Ble_8Bit1, 5, 1);
      } else {

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
    } else {
      Serial.println("Invalid Payload Length");
    }
    Buzzer();
  } else {
    Serial.println("Invalid Topic");
  }
}