#ifndef MAIN_INCLUDE_H
#define MAIN_INCLUDE_H


#include <IRremote.hpp>  // include the library
#include <Ticker.h>  // no

#include <math.h>
#include <Wire.h>
#include <EEPROM.h>
#include <HardwareSerial.h>
#include <esp_now.h>
#include <WiFi.h>
#include <esp_task_wdt.h>
#include "soc/timer_group_struct.h"
#include "soc/timer_group_reg.h"
#include <ToneESP32.h>
#include <AccelStepper.h>
#include "HT1621.h"
#include "errors_sabro.h"
#include "inverter_variables.h"
#include "structures_sabro.h"
//#include "pin_definitions.h"
#include "New_Pin.h"



#include <RTClib.h>


#include <esp_system.h>
#include <Arduino.h>

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "driver/gpio.h"





// Create an RTC object
RTC_DS3231 rtc;


#if CONFIG_IDF_TARGET_ESP32  // ESP32/PICO-D4
#include "esp32/rom/rtc.h"
#elif CONFIG_IDF_TARGET_ESP32S2
#include "esp32s2/rom/rtc.h"
#elif CONFIG_IDF_TARGET_ESP32C2
#include "esp32c2/rom/rtc.h"
#elif CONFIG_IDF_TARGET_ESP32C3
#include "esp32c3/rom/rtc.h"
#elif CONFIG_IDF_TARGET_ESP32S3
#include "esp32s3/rom/rtc.h"
#elif CONFIG_IDF_TARGET_ESP32C6
#include "esp32c6/rom/rtc.h"
#elif CONFIG_IDF_TARGET_ESP32H2
#include "esp32h2/rom/rtc.h"
#else
#error Target CONFIG_IDF_TARGET is not supported
#endif

#include <WiFi.h>
#include <WebServer.h>
#include <ESPAsyncWebServer.h>
#include <AsyncTCP.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <WiFiClientSecure.h>
#include <Prefernces.h>

Preferences preferences;
WiFiClient esp32Client;
PubSubClient client(esp32Client);

#include "ac_variables.h"

#endif