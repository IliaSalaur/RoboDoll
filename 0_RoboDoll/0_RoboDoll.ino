#include <SoftwareSerial.h>
#include <Servo.h>
#include "RCSwitch.h"
#include "DFPlayer_Mini_Mp3.h"
#include <EEPROM.h>

// _________ОТЛАДКА_________
#define DEBUG_SERIAL
#define DEBUG_ON

#ifdef DEBUG_ON
#define DEBUG(x) Serial.println(x)
#else DEBUG_ON
#define DEBUG(x)
#endif
// _________ОТЛАДКА_________



// _________НАСТРОЙКИ_________
#define ACT_PIN_FWD 8
#define ACT_PIN_REV 9
#define ACT_PERIOD 7000
#define LED_R_PIN 5
#define LED_G_PIN 6
#define LED_B_PIN 7

#define RGB_PERIOD 500

#define CARD_TRICK_DURATION 30000

//#define USE_SENS_BUTT //Сенсорная кнопка
#define SENS_SWITCH_PIN 13

#define SERVO_PIN 4
#define SERVO_ANGLE 150
#define HEART_DURATION 4000
#define HEART_LED_PIN 3

// _________НАСТРОЙКИ_________


SoftwareSerial player(10 , 11); // D10 - TX D11 - RX
Servo heartServo;
RCSwitch mySwitch = RCSwitch();

bool useRGB;
bool useMP3;
uint32_t last_receive;

struct commConf
{
  uint32_t bow_butt = 0;
  uint32_t card_butt = 0;
  uint32_t heart_butt = 0;
} conf;
commConf eepConf;

void setup() {
  Serial.begin(9600);
  player.begin(9600);
  mySwitch.enableReceive(0);
  mp3_set_serial (player);  //set Serial for DFPlayer-mini mp3 module
  mp3_set_volume (30);
  heartServo.attach(SERVO_PIN);
  heartServo.write(0);
  pinMode(ACT_PIN_FWD, OUTPUT);
  pinMode(ACT_PIN_REV, OUTPUT);
  pinMode(LED_R_PIN, OUTPUT);
  pinMode(LED_G_PIN, OUTPUT);
  pinMode(LED_B_PIN, OUTPUT);
  pinMode(HEART_LED_PIN, OUTPUT);
#ifdef USE_SENS_BUTT
  pinMode(SENS_SWITCH_PIN, INPUT);
#endif

  delay(1000);
  DEBUG("EEPROM CHECK");
  EEPROM.get(0, eepConf);
  if (eepConf.bow_butt != 0 && eepConf.bow_butt != 4294967295)
  {
    DEBUG("Config finded!");
    DEBUG(eepConf.bow_butt);
    DEBUG(eepConf.card_butt);
    DEBUG(eepConf.heart_butt);
    conf.bow_butt = eepConf.bow_butt;
    conf.card_butt = eepConf.card_butt;
    conf.heart_butt = eepConf.heart_butt;
  }
  else
  {
    DEBUG("Getting config");
    while(configComm() == 0){}
    DEBUG("Config ready");
    DEBUG(conf.bow_butt);
    DEBUG(conf.card_butt);
    DEBUG(conf.heart_butt);
  }
  
}

void loop() {
  effectHandler(checkComm());

}