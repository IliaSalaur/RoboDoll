/*
  void bow()          //ПОКЛОН
  {
  bool first = 0;
  byte finish = 0;
  uint32_t timer1;
  uint32_t timer2;
  uint32_t timer3;
  while (finish < 2)
  {
    if (first == 0)
    {
      timer1 = millis();
      timer2 = millis();
      first = 1;
      digitalWrite(ACT_PIN_FWD, HIGH);
      mp3_play(1);
      DEBUG(F("BOW:ACT is on , music is playing"));
    }

    if (millis() - timer3 >= RGB_PERIOD)
    {
      tickRGB();
      timer3 = millis();
      DEBUG("BOW:RGB tick");
    }

    if (millis() - timer1 >= ACT_PERIOD)
    {
      timer2 = millis();
      timer1 = millis();
      digitalWrite(ACT_PIN_FWD, LOW);
      digitalWrite(ACT_PIN_REV, HIGH);

      finish = 1;
      DEBUG("BOW:ACT reverse");
    }

    if (millis() - timer2 >= ACT_PERIOD && finish == 1)
    {
      digitalWrite(ACT_PIN_REV, LOW);
      digitalWrite(LED_R_PIN, LOW);
      digitalWrite(LED_G_PIN, LOW);
      digitalWrite(LED_B_PIN, LOW);
      mp3_stop();
      finish = 2;
      DEBUG("BOW:Stop music ");

    }
  }
  }
*/

void tickRGB()
{
  digitalWrite(LED_R_PIN, random(1));
  digitalWrite(LED_G_PIN, random(1));
  digitalWrite(LED_B_PIN, random(1));
}


void cardTrick()
{
  mp3_play(2);
  DEBUG("CARD: play");
}


void openHeart()
{
  uint32_t timer1;
  bool first = 0;
  while (1)
  {
    if (first == 0)
    {
      timer1 = millis();
      heartServo.write(SERVO_ANGLE);
      digitalWrite(HEART_LED_PIN, HIGH);
      DEBUG("HEART: Servo open heart, led on");
      first = 1;
    }

    if (millis() - timer1 >= HEART_DURATION)
    {
      heartServo.write(0);
      digitalWrite(HEART_LED_PIN, LOW);
      DEBUG("HEART: Servo closw heart , led off");
      break;
    }
  }
}


void effectHandler(int effectNumb)
{
  switch (effectNumb)
  {
    case 1:
      DEBUG("HANDLER: bow");
      bow();
      break;
    case 2:
      DEBUG("HANDLER: cardtrick");
      cardTrick();
      break;
    case 3:
      DEBUG("HANDLER: heart");
      openHeart();
      break;
  }
  effectNumb = 0;
}

void bow()
{
  uint32_t timer1 = millis();
  uint32_t timer3 = millis();
  bool work = 1;
  byte stage = 2;

  digitalWrite(ACT_PIN_FWD, HIGH);
  mp3_play(1);

  DEBUG(F("BOW:ACT is on , music is playing"));
  while (work == 1)
  {
    if (millis() - timer3 >= RGB_PERIOD) {
      tickRGB();
      timer3 = millis();
      DEBUG("BOW:RGB tick");
    }
    if (millis() - timer1 >= ACT_PERIOD && stage == 2) {
      digitalWrite(ACT_PIN_FWD, LOW);
      digitalWrite(ACT_PIN_REV, HIGH);
      timer1 = millis();
      DEBUG("BOW:ACT reverse");
      stage = 3;
    }
    if (millis() - timer1 >= ACT_PERIOD && stage == 3)
    {
      digitalWrite(ACT_PIN_REV, LOW);
      digitalWrite(LED_R_PIN, LOW);
      digitalWrite(LED_G_PIN, LOW);
      digitalWrite(LED_B_PIN, LOW);
      mp3_stop();
      work = 0;
      DEBUG("BOW:Stop music ");
    }
  }
}
