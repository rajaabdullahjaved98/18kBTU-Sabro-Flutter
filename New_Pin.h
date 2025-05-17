#ifndef PIN_DEFINITIONS_H
#define PIN_DEFINITIONS_H

#define NONE_SELECTED   0
#define OLD_ESP         1
#define ESP32S3_WROOM_Z 2
#define ESP32_ONE_TON   3

// #define SELECTED_DEVICE ESP32S3_WROOM_Z

#define SELECTED_DEVICE OLD_ESP  


#if SELECTED_DEVICE == OLD_ESP
    
#define MotorInterfaceType 4
#define PIN_HT1621_BL     23  // LEd light
#define PIN_HT1621_CS     19 //GPIO_19
#define PIN_HT1621_RW     18 //GPIO_18
#define PIN_HT1621_DATA   5 //GPIO_5
#define RXD2 16
#define TXD2 17
#define WDT_TIMEOUT 20
# define fan_low 13   // indoor fan speed low relay D13
# define fan_mid 12   // indoor fan speed mid relay D12
# define fan_high 27  // indoor fan speed high relay D27
#define Inverter_OFF_PIN 4
#define PIN_HT1621_BL     23  // Lcd backlight
#define RECVER_PIN  14       // use for Ir Interpt 
#define p_button 34  // Push button d34
#define BUZZER_PIN 15
#define BUZZER_CHANNEL 0

HT1621 ht(PIN_HT1621_CS, PIN_HT1621_RW, PIN_HT1621_DATA);
AccelStepper myStepper(MotorInterfaceType, 32, 25, 33, 26);
ToneESP32 buzzer(BUZZER_PIN, BUZZER_CHANNEL);



#elif SELECTED_DEVICE == ESP32S3_WROOM_Z
      
#define MotorInterfaceType 4
#define PIN_HT1621_BL     4  // LEd light
#define PIN_HT1621_CS     3 //GPIO_19
#define PIN_HT1621_RW     2 //GPIO_18
#define PIN_HT1621_DATA   1 //GPIO_5
#define RXD2 18
#define TXD2 17
#define WDT_TIMEOUT 20
# define fan_low 11  // indoor fan speed low relay D13
# define fan_mid 12   // indoor fan speed mid relay D12
# define fan_high 13  // indoor fan speed high relay D27
#define Inverter_OFF_PIN 10
#define RECVER_PIN  14       // use for Ir Interpt 
#define p_button 6  // Push button d34
#define BUZZER_PIN 38
#define BUZZER_CHANNEL 0

HT1621 ht(PIN_HT1621_CS, PIN_HT1621_RW, PIN_HT1621_DATA);
AccelStepper myStepper(MotorInterfaceType, 39, 41, 40, 42);
ToneESP32 buzzer(BUZZER_PIN, BUZZER_CHANNEL);



#elif SELECTED_DEVICE == ESP32_ONE_TON

     
#define MotorInterfaceType 4
#define PIN_HT1621_BL     23  // LEd light
#define PIN_HT1621_CS     19 //GPIO_19
#define PIN_HT1621_RW     18 //GPIO_18
#define PIN_HT1621_DATA   5 //GPIO_5
#define RXD2 16
#define TXD2 17
#define WDT_TIMEOUT 20
# define fan_low 13   // indoor fan speed low relay D13
# define fan_mid 12   // indoor fan speed mid relay D12
# define fan_high 27  // indoor fan speed high relay D27
#define Inverter_OFF_PIN 4
#define PIN_HT1621_BL     23  // Lcd backlight
#define RECVER_PIN  14       // use for Ir Interpt 
#define p_button 34  // Push button d34
#define BUZZER_PIN 15
#define BUZZER_CHANNEL 0

HT1621 ht(PIN_HT1621_CS, PIN_HT1621_RW, PIN_HT1621_DATA);
AccelStepper myStepper(MotorInterfaceType, 32, 25, 33, 26);
ToneESP32 buzzer(BUZZER_PIN, BUZZER_CHANNEL);



#else
    // Error if no valid device is selected
    #error "No valid device selected! Please select OLD_ESP or ESP32S3_WROOM_Z."
#endif


#endif // End of WROOM_H