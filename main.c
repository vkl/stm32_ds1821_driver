/**
  @file    main.c
  @author  vkl 
  @version V0.0.1
  @date    4 December 2015
  @brief   DS1821 STM32VLDiscovery demo
**/

#include "stm32f10x.h"
#include "delay.h"
#include "stm32f10x_onewire.h"
#include "ds1821.h"

char dataint;
char datafract;

OneWireInit_TypeDef OneWire_cfg;

void main(void)
{
  char tmp = 0x0;
  char status = 0x0;

  //Enable clock for GPIOC
  RCC->APB2ENR |= RCC_APB2ENR_IOPCEN; 
 
  //Enable clock for TIMER7 
  RCC->APB1ENR |= RCC_APB1ENR_TIM7EN;

  OneWire_cfg.DQ_Pin = 13;
  OneWire_cfg.VDD_Pin = 14;
  OneWire_cfg.Port = GPIOC; 
 
  onewire_init(&OneWire_cfg);

  read_temperature(&OneWire_cfg, &dataint, &datafract);

  /* Write TH & TL */
  write_temphigh(&OneWire_cfg, 23); 
  write_templow(&OneWire_cfg, 22);
  
  /* Read TH & TL */
  read_temphigh(&OneWire_cfg, &tmp);
  read_templow(&OneWire_cfg, &tmp);

  read_status(&OneWire_cfg, &status);

  read_temperature(&OneWire_cfg, &dataint, &datafract);

  read_status(&OneWire_cfg, &status);

  while (1)
  {
  }
}

