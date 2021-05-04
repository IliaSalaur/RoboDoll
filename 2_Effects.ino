void tickRGB()
{
  int millisMod = millis() % 3;
//  bool rgbChange = (millisMod == 2) ? 1:millisMod;
  switch(millisMod)
  {
    case 0:
    digitalWrite(LED_R_PIN, HIGH);
    digitalWrite(LED_B_PIN, LOW);
    break;

    case 1:
    digitalWrite(LED_G_PIN, HIGH);
    digitalWrite(LED_R_PIN, LOW);
    break;

    case 2:
    digitalWrite(LED_B_PIN, HIGH);
    digitalWrite(LED_G_PIN, LOW);
    break;
  }
}


void cardTrick()
{
  static  uint32_t  timer = millis();
  mp3_play(2);
  DEBUG("CARD: play");
  while(millis() - timer < CARD_TIME)
  {
    DEBUG(F("DEBUG: card trick in progress"));
  }
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
      DEBUG("HEART: Servo close heart , led off");
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
      DEBUG(F("HANDLER: heart"));
      openHeart();
      break;
    case 4:
      DEBUG(F("HANDLER: head"));
      head();
      break;
  }
  mySwitch.resetAvailable();
  effectNumb = 0;
}

void bow()
{
  uint32_t timer1 = millis();
  uint32_t timer3 = millis();
  bool work = 1;
  byte stage = 2;

  bowAct.forward();
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
      bowAct.reverse();
      timer1 = millis();
      DEBUG("BOW:ACT reverse");
      stage = 3;
    }
    if (millis() - timer1 >= ACT_PERIOD && stage == 3)
    {
      bowAct.stop();
      digitalWrite(LED_R_PIN, LOW);
      digitalWrite(LED_G_PIN, LOW);
      digitalWrite(LED_B_PIN, LOW);
      mp3_stop();
      work = 0;
      DEBUG("BOW:Stop music ");
    }
  }
}

void head()
{
  headTimer = millis();
  if(state == 1)
  {
    state = 0;
    headAct.reverse();
    DEBUG(F("HEAD:Reverse, state is 0"));
  }
  else
  {
    state = 1;
    headAct.forward();
    DEBUG(F("HEAD:Forward, state is 1"));
  }
}
