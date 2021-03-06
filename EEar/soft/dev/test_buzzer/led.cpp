
#include "include.h"



COutputPin::COutputPin(GPIO_TypeDef *_port,uint16_t _pin,uint32_t _clk)
{
  p_port = _port;
  m_pin = _pin;

  RCC_AHB1PeriphClockCmd(_clk,ENABLE);

  GPIO_InitTypeDef i;
  i.GPIO_Pin = m_pin;
  i.GPIO_Mode = GPIO_Mode_OUT;
  i.GPIO_OType = GPIO_OType_PP;
  i.GPIO_PuPd = GPIO_PuPd_UP;
  i.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(p_port,&i);
}


COutputPin::~COutputPin()
{
}


void COutputPin::On()
{
  GPIO_SetBits(p_port,m_pin);
}


void COutputPin::Off()
{
  GPIO_ResetBits(p_port,m_pin);
}


void COutputPin::Toggle()
{
  GPIO_ToggleBits(p_port,m_pin);
}


void COutputPin::SetState(bool state)
{ 
  if ( state ) 
     {
       On(); 
     }
  else 
     {
       Off(); 
     }
}



uint16_t CBoardLED::leds[4] = {GPIO_Pin_12,GPIO_Pin_13,GPIO_Pin_14,GPIO_Pin_15};

CBoardLED::CBoardLED(EBoardLeds led,bool init_on) : COutputPin(GPIOD,leds[led],RCC_AHB1Periph_GPIOD)
{
  if ( init_on )
     {
       On();
     }
  else
     {
       Off();
     }
}






