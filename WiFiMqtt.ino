
const char* mqttSubscribeTopic = "esp32/ac/command";
const char* mqttPublishTopic = "esp32/test/state";

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
    String mac = WiFi.macAddress();
    mac.replace(":", "");
    String clientId = "ESP-";
    clientId += String(random(0xffff), HEX);

    while (!client.connected() && attempt < maxAttempts) {
      //Serial.printf("Connecting to MQTT (Attempt %d/%d)...\n", attempt + 1, maxAttempts);
      if (client.connect(clientId.c_str())) {
        Serial.println("Connected to MQTT broker");

        String topic = "test/" + mac + "/topic";
        Serial.println("Topic Name: " + topic);
        client.subscribe(mqttSubscribeTopic);
        client.publish(mqttPublishTopic, "ESP is online");

        return;
      } else {
        Serial.print("Failed MQTT connection. State=");
        Serial.println(client.state());
        attempt++;
        delay(2000);
      }
    }

    if (!client.connected()) {
      Serial.println("MQTT failed. Starting fallback...");
    }
  }

  if (!client.connected()) {
    reconnectMqtt();
  }

  client.loop();

  // Example payload
  //const char* payload = "Hello from ESP32!";

  // Publish to topic
  //if (client.publish(mqtt_publish_topic, payload)) {
  //Serial.println("Message published successfully");
  //} else {
  //Serial.println("Publish failed");
  //}

  const uint16_t payloadSize = 109;
  uint8_t payload[109];
  uint16_t index = 0;

  payload[index++] = R_Data.SL_Code;
  payload[index++] = R_Data.Sec_Rtc;
  payload[index++] = R_Data.Min_Rtc;
  payload[index++] = R_Data.Hour_Rtc;
  payload[index++] = R_Data.day_Rtc;
  payload[index++] = R_Data.month_Rtc;

  payload[index++] = (R_Data.Year_RTC >> 8) & 0xFF;
  payload[index++] = R_Data.Year_RTC & 0xFF;

  payload[index++] = R_Data.Ble_8Bit1;
  payload[index++] = R_Data.Ble_8Bit2;
  payload[index++] = R_Data.Ble_8Bit3;
  payload[index++] = R_Data.Ble_8Bit4;
  payload[index++] = R_Data.Ble_8Bit5;
  payload[index++] = R_Data.mode_pkr_set;
  payload[index++] = R_Data.rupees_send;

  memcpy(&payload[index], &R_Data.Set_Temp, 4);
  index += 4;
  memcpy(&payload[index], &R_Data.Coil_sensor, 4);
  index += 4;
  memcpy(&payload[index], &R_Data.Room_sensor, 4);
  index += 4;
  memcpy(&payload[index], &R_Data.Delta_Temp, 4);
  index += 4;
  memcpy(&payload[index], &R_Data.Suction_Temp, 4);
  index += 4;
  memcpy(&payload[index], &R_Data.Calculated_Suction_Pressure, 4);
  index += 4;
  memcpy(&payload[index], &R_Data.Liquid_Line_temp, 4);
  index += 4;
  memcpy(&payload[index], &R_Data.Discharge_Temp, 4);
  index += 4;
  memcpy(&payload[index], &R_Data.Calculated_Discharge_Pressure, 4);
  index += 4;
  memcpy(&payload[index], &R_Data.ODU_Ambient_Temp, 4);
  index += 4;
  memcpy(&payload[index], &R_Data.Ac_volts, 4);
  index += 4;
  memcpy(&payload[index], &R_Data.Dc_Volts, 4);
  index += 4;
  memcpy(&payload[index], &R_Data.S_cuurent, 4);
  index += 4;
  memcpy(&payload[index], &R_Data.F_Current, 4);
  index += 4;
  memcpy(&payload[index], &R_Data.Comp_current, 4);
  index += 4;

  payload[index++] = (R_Data.Comperssor_Running_RPM >> 8) & 0xFF;
  payload[index++] = R_Data.Comperssor_Running_RPM & 0xFF;

  payload[index++] = R_Data.Inv_Error;
  payload[index++] = R_Data.Falut_Inv_code;

  payload[index++] = (R_Data.Ton_sec >> 24) & 0xFF;
  payload[index++] = (R_Data.Ton_sec >> 16) & 0xFF;
  payload[index++] = (R_Data.Ton_sec >> 8) & 0xFF;
  payload[index++] = R_Data.Ton_sec & 0xFF;

  payload[index++] = (R_Data.Tof_sec >> 24) & 0xFF;
  payload[index++] = (R_Data.Tof_sec >> 16) & 0xFF;
  payload[index++] = (R_Data.Tof_sec >> 8) & 0xFF;
  payload[index++] = R_Data.Tof_sec & 0xFF;

  memcpy(&payload[index], &R_Data.R_Hour_Energy, 4);
  index += 4;
  memcpy(&payload[index], &R_Data.R_Day_Energy, 4);
  index += 4;
  memcpy(&payload[index], &R_Data.energy_day_peak, 4);
  index += 4;
  memcpy(&payload[index], &R_Data.R_Month_Energy, 4);
  index += 4;
  memcpy(&payload[index], &R_Data.energy_month_peak, 4);
  index += 4;

  // Finally publish the complete payload
  // client.publish(mqttPublishTopic, payload, payloadSize);

  if (client.publish(mqttPublishTopic, payload, payloadSize)) {
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
  if (strcmp(topic, mqttSubscribeTopic) == 0) {
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
        bitWrite(Ble_8Bit1, 7, 0);
      } else {
        bitWrite(Ble_8Bit1, 7, 1);
      }

      if (mode == 0) {
        bitWrite(Ble_8Bit2, 6, 0);
        bitWrite(Ble_8Bit2, 7, 0);
      } else if (mode == 1) {
        bitWrite(Ble_8Bit2, 6, 1);
        bitWrite(Ble_8Bit2, 7, 0);
      } else if (mode == 2) {
        bitWrite(Ble_8Bit2, 6, 0);
        bitWrite(Ble_8Bit2, 7, 1);
      } else {
        bitWrite(Ble_8Bit2, 6, 1);
        bitWrite(Ble_8Bit2, 7, 1);
      }

      if (fan == 0) {
        bitWrite(Ble_8Bit1, 3, 0);
        bitWrite(Ble_8Bit1, 4, 0);
        bitWrite(Ble_8Bit1, 5, 0);
      } else if (fan == 1) {
        bitWrite(Ble_8Bit1, 3, 1);
        bitWrite(Ble_8Bit1, 4, 0);
        bitWrite(Ble_8Bit1, 5, 0);
      } else if (fan == 2) {
        bitWrite(Ble_8Bit1, 3, 0);
        bitWrite(Ble_8Bit1, 4, 1);
        bitWrite(Ble_8Bit1, 5, 0);
      } else if (fan == 3) {
        bitWrite(Ble_8Bit1, 3, 1);
        bitWrite(Ble_8Bit1, 4, 1);
        bitWrite(Ble_8Bit1, 5, 0);
      } else {
        bitWrite(Ble_8Bit1, 3, 0);
        bitWrite(Ble_8Bit1, 4, 0);
        bitWrite(Ble_8Bit1, 5, 1);
      }

      if (swing == 0) {
        bitWrite(Ble_8Bit1, 6, 0);
      } else {
        bitWrite(Ble_8Bit1, 6, 1);
      }

      if (eco == 0) {
        bitWrite(Ble_8Bit2, 4, 0);
      } else {
        bitWrite(Ble_8Bit2, 4, 1);
      }
    } else {
      Serial.println("Invalid Payload Length");
    }
  } else {
    Serial.println("Invalid Topic");
  }
}