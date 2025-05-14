/*#ifndef PIN_DEFINITIONS_H
#define PIN_DEFINITIONS_H




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

#endif
*/