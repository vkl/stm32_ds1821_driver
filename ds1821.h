/*
  @file    ds1821.h
  @author  vkl 
  @version V0.0.1
  @date    3 December 2015
  @brief   ds1821 driver
*/

#ifndef __DS1821_H
#define __DS1821_H

#define DS1821_READ_TEMP     0xAA
#define DS1821_START_CONVERT 0xEE
#define DS1821_STOP_CONVERT  0x22
#define DS1821_WRITE_TH	     0x01
#define DS1821_WRITE_TL      0x02
#define DS1821_READ_TH       0xA1
#define DS1821_READ_TL       0xA2
#define DS1821_WRITE_STATUS  0x0C
#define DS1821_READ_STATUS   0xAC
#define DS1821_READ_COUNTER  0xA0
#define DS1821_LOAD_COUNTER  0x41	

#define DS1821_DONE  7   /* DONE - 0 Temp conversation is in progress, DONE - 1 Temp conversation is complete */
#define DS1821_NVB   5   /* NVB - 0 Nonvolatile memory is not busy, NVB - 1 A write to EEPROM is in progress  */
#define DS1821_THF   4   /* THF - 0 The temp has not exceeded TH, THF - 1 The temp has been higher TH         */
#define DS1821_TLF   3   /* TLF - 0 The temp has not been lower TL, TLF - 1 The temp has been lower TL        */
#define DS1821_TR    2   /* TR - 0 1-wire mode, TR - 1 thermostat mode */
#define DS1821_POL   1   /* POL - 0 Thermostat is active low, POL - 1 Thermostat is active high */
#define DS1821_1SHOT 0   /* 1SHOT - 0 Continuouse conversation mode, 1SHOT - 1 One-shot mode */

#include "stm32f10x_onewire.h"

void read_status(OneWireInit_TypeDef*, char*);
void write_status(OneWireInit_TypeDef*, char*);

void read_temperature(OneWireInit_TypeDef*, char*, char*);

void write_temphigh(OneWireInit_TypeDef*, char);
void write_templow(OneWireInit_TypeDef*, char);

void read_temphigh(OneWireInit_TypeDef*, char*);
void read_templow(OneWireInit_TypeDef*, char*);

#endif

