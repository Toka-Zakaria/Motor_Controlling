/**********************************************************************************
 * [FILE NAME]: app_file.h
 *
 * [AUTHOR]: Toka Zakaria Mohamed
 *
 * [DATE CREATED]: NOV 06, 2020
 *
 * [Description]: Header file of Controlling Motor
 ***********************************************************************************/

#ifndef APP_FILE_H_
#define APP_FILE_H_


#include "micro_config.h"
#include "std_types.h"
#include "common_macros.h"
#include"lcd.h"
#include"timers.h"
#include"external_interrupts.h"
#include"adc.h"
#include"DCmotor.h"


#define RESISTOR_PORT_REG              PORTA
#define RESISTOR_DIRECTION_REG         DDRA
#define RESISTOR_PIN_REG               PINA
#define RESISTOR_PIN                   PA0

void buttonFunction(void);


#endif /* APP_FILE_H_ */
