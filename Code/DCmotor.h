/**********************************************************************************
 * [FILE NAME]: motor.h
 *
 * [AUTHOR]: Toka Zakaria Mohamed Ramadan
 *
 * [DATE CREATED]: Nov 5, 2020
 *
 * [Description]:File of All types Declaration and Functions prototypes of DC Motor.
 ***********************************************************************************/

#ifndef DCMOTOR_H_
#define DCMOTOR_H_

#include "std_types.h"
#include "micro_config.h"
#include "common_macros.h"


/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/

#define ENABLE                                  TRUE
#define DISABLE                                 FALSE
#define ENABLE_PIN_CONNECTED_TO_MICRO          ENABLE

#define DC_MOTOR_DIRECTION_PORT                  DDRB
#define DC_MOTOR_DATA_PORT                       PORTB
#define DC_MOTOR_PIN_PORT                        PINB

#define DC_MOTOR_PIN_IN1                          PB0
#define DC_MOTOR_PIN_IN2                          PB1


#define DC_MOTOR_ENABLE_DIRECTION_PORT           DDRB
#define DC_MOTOR_ENABLE_DATA_PORT                PORTB

#define DC_MOTOR_PIN_EN1                         PB3



/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
/********************************************************************************
 * [Function Name]: DC_motor_Init
 *
 * [Description]:  Function to initialize the DC motor
 *                 configure the pins of the motor as output pins
 *
 * [Args]:         NONE
 *
 * [In]            NONE
 *
 * [Out]           NONE
 *
 * [Returns]:      NONE
 *******************************************************************************/
void DC_motor_Init(void);
/********************************************************************************
 * [Function Name]: DC_motor_on_ClockWise
 *
 * [Description]:  Function to make the motor move on clockwise direction
 *
 * [Args]:         NONE
 *
 * [In]            NONE
 *
 * [Out]           NONE
 *
 * [Returns]:      NONE
 *******************************************************************************/
void DC_motor_on_ClockWise(void);
/*********************************************************************************
 * [Function Name]: DC_motor_on_AntiClockWise
 *
 * [Description]:  Function to make the motor move on  Anti clockwise direction
 *
 * [Args]:         NONE
 *
 * [In]            NONE
 *
 * [Out]           NONE
 *
 * [Returns]:      NONE
 *********************************************************************************/
void DC_motor_onAnti_ClockWise(void);
/*********************************************************************************
 * [Function Name]:DC_ motor_on_Stop
 *
 * [Description]:  Function to make the motor stop moving.
 *
 * [Args]:         NONE
 *
 * [In]            NONE
 *
 * [Out]           NONE
 *
 * [Returns]:      NONE
 *********************************************************************************/
void DC_motor_on_Stop(void);


#endif /* DCMOTOR_H_ */
