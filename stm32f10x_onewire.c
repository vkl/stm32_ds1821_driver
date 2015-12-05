/*
  @file    stm32f10x_onewire.c
  @author  vkl 
  @version V0.0.1
  @date    3 December 2015
  @brief   OneWire driver
*/

#include "stm32f10x_onewire.h"
#include "stm32f10x.h"


void onewire_init(OneWireInit_TypeDef *OneWire_Init)
{
  /* CRL configuration */
  if (((uint16_t)(1 << OneWire_Init->DQ_Pin)) & ((uint16_t)0x00FF))
  {
    /* Clear MODE and CNF bits */
    OneWire_Init->Port->CRL &= ~(0xF << (OneWire_Init->DQ_Pin * 4));
    OneWire_Init->Port->CRL &= ~(0xF << (OneWire_Init->VDD_Pin * 4)); 
    /* Set Input pull CNF1 bit 1*/
    OneWire_Init->Port->CRL |= (0x1 << ((OneWire_Init->DQ_Pin * 4) + 3)); 
  }
  /* CRH configuration */
  else if (((int16_t)(1 << OneWire_Init->DQ_Pin)) & ((uint16_t)0xFF00))
  {
    /* Clear MODE and CNF bits */
    OneWire_Init->Port->CRH &= ~(0xF << ((OneWire_Init->DQ_Pin - 8) * 4));
    OneWire_Init->Port->CRH &= ~(0xF << ((OneWire_Init->VDD_Pin - 8) * 4));
    /* Set Input pull CNF1 bit 1*/
    OneWire_Init->Port->CRH |= (0x1 << (((OneWire_Init->DQ_Pin - 8) * 4) + 3)); 
  }
}

void onewire_reset(OneWireInit_TypeDef *OneWire_Init)
{
  /* Reset pulse */
  ONEWIRE_PIN_LOW(OneWire_Init->Port, OneWire_Init->DQ_Pin);
  delay_us(480);
  ONEWIRE_PIN_HIGH(OneWire_Init->Port, OneWire_Init->DQ_Pin);

  delay_us(60);

  /* Check for presense pulse */
  if (ONEWIRE_PIN_READ(OneWire_Init->Port, OneWire_Init->DQ_Pin) != 0) { return; }
  delay_us(240);
  if (ONEWIRE_PIN_READ(OneWire_Init->Port, OneWire_Init->DQ_Pin) == 0) { return; }
}

void onewire_write_byte(OneWireInit_TypeDef *OneWire_Init, char data)
{
  unsigned char i = 0;
  for(i=0; i<=7; i++)
  {
    ONEWIRE_PIN_LOW(OneWire_Init->Port, OneWire_Init->DQ_Pin);
    delay_us(15);
    if (data & (1 << i)) { ONEWIRE_PIN_HIGH(OneWire_Init->Port, OneWire_Init->DQ_Pin); }
    delay_us(45);
    ONEWIRE_PIN_HIGH(OneWire_Init->Port, OneWire_Init->DQ_Pin);
    delay_us(1);
  }
}

void onewire_read_byte(OneWireInit_TypeDef *OneWire_Init, char* data)
{
  unsigned char i = 0;
  *data = 0x0;
  for(i=0; i<=7; i++)
  {
    ONEWIRE_PIN_LOW(OneWire_Init->Port, OneWire_Init->DQ_Pin);
    delay_us(1);
    ONEWIRE_PIN_HIGH(OneWire_Init->Port, OneWire_Init->DQ_Pin);
    delay_us(15);
    *data |= (ONEWIRE_PIN_READ(OneWire_Init->Port, OneWire_Init->DQ_Pin) << i); 
    delay_us(45);
  }
}
