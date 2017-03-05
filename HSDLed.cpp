#include "HSDLed.h"

HSDLed::HSDLed()
:
m_behavior(OFF),
m_color(NONE),
m_isOn(false),
m_onTime(blinkOnTime),
m_offTime(blinkOffTime),
m_previousMillis(0)
{
}

void HSDLed::setOn(Color color)
{
  m_behavior = ON;
  m_color = color;
  m_isOn = true;
}

void HSDLed::setOff()
{
  m_behavior = OFF;
  m_color = NONE;
  m_isOn = false;
}

void HSDLed::setBlinking(Color color)
{
  if( (m_behavior != BLINKING) && (m_color != color) ) 
  {
    m_behavior = BLINKING;
    m_color = color;
    m_isOn = true;
    m_previousMillis = 0;
    m_onTime = blinkOnTime;
    m_offTime = blinkOffTime;
  }
}

void HSDLed::setFlashing(Color color)
{
  if( (m_behavior != FLASHING) && (m_color != color) ) 
  {
    m_behavior = FLASHING;
    m_color = color;
    m_isOn = true;
    m_previousMillis = 0;
    m_onTime = flashOnTime;
    m_offTime = flashOffTime;
  }
}

HSDLed::Color HSDLed::getColor()
{
  return m_isOn ? m_color : NONE;
}

void HSDLed::update()
{
  if( (m_behavior == BLINKING) || (m_behavior == FLASHING) )
  {
    // check to see if it's time to change the state of the LED
    unsigned long currentMillis = millis();
  
    if(!m_isOn && (currentMillis - m_previousMillis >= m_onTime))
    {
      m_isOn = true;
      m_previousMillis = currentMillis; 
    }
    else if (m_isOn && (currentMillis - m_previousMillis >= m_offTime))
    {
      m_isOn = false;
      m_previousMillis = currentMillis;
    }
  }
}

