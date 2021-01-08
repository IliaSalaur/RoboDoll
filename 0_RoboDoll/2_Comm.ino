bool configComm()
{
  mySwitch.resetAvailable();
  while (conf.bow_butt == 0)
  {
    if (mySwitch.available())
    {
      conf.bow_butt = mySwitch.getReceivedValue();
      DEBUG("Conf bow:");
      DEBUG(conf.bow_butt);
    }
    mySwitch.resetAvailable();
  }

  while (conf.card_butt == 0)
  {
    if (mySwitch.available())
    {
      conf.card_butt = mySwitch.getReceivedValue();
      DEBUG("Conf card:");
      DEBUG(conf.card_butt);
    }
    mySwitch.resetAvailable();
  }

  while (conf.heart_butt == 0)
  {
    if (mySwitch.available())
    {
      conf.heart_butt = mySwitch.getReceivedValue();
      DEBUG("Conf heart:");
      DEBUG(conf.heart_butt);
    }
    mySwitch.resetAvailable();
  }

  if (conf.bow_butt != 0 && conf.card_butt != 0 && conf.heart_butt != 0 )
  {
    EEPROM.put(0, conf);
    DEBUG("Config Saved to EEPROM");
    return 1;
  }
  else return 0;
}

int checkComm()
{
  
  static int toReturn;
  toReturn = 0;
  uint32_t timer1;
  
  if (mySwitch.available() && millis() - timer1 >= 1000)
  {
    if (mySwitch.getReceivedValue() == conf.bow_butt )
    {
      timer1 = millis();
      last_receive = conf.bow_butt;
      toReturn = 1;


    }
    else if (mySwitch.getReceivedValue() == conf.card_butt )
    {
      last_receive = conf.card_butt;
      timer1 = millis();
      toReturn = 2;

    }
    else if (mySwitch.getReceivedValue() == conf.heart_butt )
    {
      last_receive = conf.heart_butt;
      timer1 = millis();
      toReturn = 3;
    }

  }
  else toReturn = 0;
  mySwitch.resetAvailable();
  return toReturn;
  
}
