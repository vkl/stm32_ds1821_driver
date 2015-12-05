/*
  @file    ds1821.c
  @author  vkl 
  @version V0.0.1
  @date    3 December 2015
  @brief   ds1821 driver
*/

#include "delay.h"
#include "stm32f10x_onewire.h"
#include "ds1821.h"

void read_temperature(OneWireInit_TypeDef *onewire, char *dataint, char *datafract)
{
  long temp = 0;
  char tmp;
  char count_remain, count_per_c;
  char status = 0x0;

  tmp = count_remain = count_per_c = 0x0;
  status = 0x0;

  onewire_reset(onewire);
  onewire_write_byte(onewire, DS1821_START_CONVERT);

  /* Wait for bit7 DONE will be set */
  do
  {
    onewire_reset(onewire);
    onewire_write_byte(onewire, DS1821_READ_STATUS);
    onewire_read_byte(onewire, &status);
  } while(((status & (1 << DS1821_DONE)) >> DS1821_DONE) == 0);

  onewire_reset(onewire);
  onewire_write_byte(onewire, DS1821_READ_TEMP);
  onewire_read_byte(onewire, &tmp);

  onewire_reset(onewire);
  onewire_write_byte(onewire, DS1821_READ_COUNTER);
  onewire_read_byte(onewire, &count_remain);

  onewire_reset(onewire);
  onewire_write_byte(onewire, DS1821_LOAD_COUNTER);
    
  onewire_reset(onewire);
  onewire_write_byte(onewire, DS1821_READ_COUNTER);
  onewire_read_byte(onewire, &count_per_c);
  
  if (tmp > 0x80) { tmp = tmp - 256; }
  temp = 100 * tmp - 50;
  temp += (100 * (count_per_c - count_remain)) / count_per_c;
  *dataint = temp / 100;
  *datafract = temp % 100;

}

void write_temphigh(OneWireInit_TypeDef *onewire, char temp)
{
  onewire_reset(onewire);
  onewire_write_byte(onewire, DS1821_WRITE_TH);
  onewire_write_byte(onewire, temp);
}

void write_templow(OneWireInit_TypeDef *onewire, char temp)
{
  onewire_reset(onewire);
  onewire_write_byte(onewire, DS1821_WRITE_TL);
  onewire_write_byte(onewire, temp);
}

void read_temphigh(OneWireInit_TypeDef *onewire, char* temp)
{
  onewire_reset(onewire);
  onewire_write_byte(onewire, DS1821_READ_TH);
  onewire_read_byte(onewire, temp);
}

void read_templow(OneWireInit_TypeDef *onewire, char* temp)
{
  onewire_reset(onewire);
  onewire_write_byte(onewire, DS1821_READ_TL);
  onewire_read_byte(onewire, temp);
}

void read_status(OneWireInit_TypeDef *onewire, char *status)
{
  onewire_reset(onewire);
  onewire_write_byte(onewire, DS1821_READ_STATUS);
  onewire_read_byte(onewire, status);
}

void write_status(OneWireInit_TypeDef *onewire, char *status)
{
  onewire_reset(onewire);
  //TODO
}
