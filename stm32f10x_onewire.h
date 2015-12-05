/*
  @file    stm32f10x_onewire.h
  @author  vkl 
  @version V0.0.1
  @date    3 December 2015
  @brief   OneWire driver
*/

#ifndef __STM32F10x_ONEWIRE_H
#define __STM32F10x_ONEWIRE_H

#include "stm32f10x.h"
#include "delay.h"

typedef struct
{
  uint8_t VDD_Pin;
  uint8_t DQ_Pin;
  GPIO_TypeDef* Port;
} OneWireInit_TypeDef;

#define ONEWIRE_PIN_HIGH(PORT, PIN)     (PORT->BSRR = (1 << PIN))
#define ONEWIRE_PIN_LOW(PORT, PIN)      (PORT->BRR = (1 << PIN))
#define ONEWIRE_PIN_READ(PORT, PIN)     ((PORT->IDR & (1 << PIN)) >> PIN)
 
void onewire_init(OneWireInit_TypeDef*);
void onewire_reset(OneWireInit_TypeDef*);
void onewire_write_byte(OneWireInit_TypeDef*, char);
void onewire_read_byte(OneWireInit_TypeDef*, char*);

#endif


