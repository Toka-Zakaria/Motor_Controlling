/**********************************************************************************
 * [FILE NAME]: timer.h
 *
 * [AUTHOR]: Toka Zakaria Mohamed Ramadan
 *
 * [DATE CREATED]: Nov 5, 2020
 *
 * [Description]: File of All types Declaration and Functions prototypes of timer
 *                configuration.
 *
 ***********************************************************************************/


#ifndef TIMERS_H_
#define TIMERS_H_

#include "std_types.h"
#include "micro_config.h"
#include "common_macros.h"

/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/

/**************************************************************************
 *                              Timer0
 * ************************************************************************/
/*TIMER0 REGISTERS*/
#define TIMER0_CONTROL_REGIRSTER                     TCCR0
#define TIMER0_INITIAL_VALUE_REGISTER                TCNT0
#define TIMER0_OUTPUT_COMPARE_REGISTER               OCR0
#define TIMER0_INTERRUPT_MASK_REGISTER               TIMSK
#define TIMER0_INTERRUPT_FLAG_REGISTER               TIFR

/*TIMER0_CONTROL_REGIRSTER*/
#define TIMER0_FORCE_OUTPUT_COMPARE_BIT              FOC0
#define TIMER0_WAVE_FORM_GENERATION_BIT0             WGM00
#define TIMER0_WAVE_FORM_GENERATION_BIT1             WGM01
#define TIMER0_COMPARE_OUTPUT_MODE_BIT0              COM00
#define TIMER0_COMPARE_OUTPUT_MODE_BIT1              COM01
#define TIMER0_CLOCK_SELECT_BIT0                     CS00
#define TIMER0_CLOCK_SELECT_BIT1                     CS01
#define TIMER0_CLOCK_SELECT_BIT2                     CS02

/*TIMER0_INTERRUPT_FLAG_REGISTER*/
#define TIMER0_OUTPUT_OVERFLOW_INTERRUPT             TOIE0
#define TIMER0_OUTPUT_COMPARE_MATCH_INTERRUPT        OCIE0

#define TIMER0_CLOCK_MASK_CLEAR                0XF8
#define TIMER0_COM0_MASK_CLEAR                 0XCF
#define COM0_SHIFT_VALUE                               4
#define OC0_PIN                                        PB3
#define OC0_DATA_PORT                                  PORTB
#define OC0_DIRECTION_PORT                             DDRB
/***********************************************************************/

/**************************************************************************
 *                              Timer1
 * ************************************************************************/

/*TIMER1 REGISTERS*/
#define TIMER1_CONTROL_REGIRSTER_A             TCCR1A
#define TIMER1_CONTROL_REGIRSTER_B             TCCR1B
#define TIMER1_INITIAL_VALUE_REGISTER          TCNT1
#define TIMER1_INITIAL_VALUE_LOW_REGISTER      TCNT1L
#define TIMER1_INITIAL_VALUE_HIGH_REGISTER     TCNT1H
#define TIMER1_OUTPUT_COMPARE_REGISTER_A       OCR1A
#define TIMER1_OUTPUT_COMPARE_REGISTER_B       OCR1B
#define TIMER1_INTERRUPT_MASK_REGISTER         TIMSK
#define TIMER1_INTERRUPT_FLAG_REGISTER         TIFR

/*TIMER1_CONTROL_REGIRSTER*/
#define TIMER1_FORCE_OUTPUT_COMPARE_BIT_A       FOC1A
#define TIMER1_FORCE_OUTPUT_COMPARE_BIT_B       FOC1B

#define TIMER1_WAVE_FORM_GENERATION_BIT12      WGM12
#define TIMER1_WAVE_FORM_GENERATION_BIT13      WGM13

#define TIMER1_WAVE_FORM_GENERATION_BIT10      WGM10
#define TIMER1_WAVE_FORM_GENERATION_BIT11      WGM11


/*TIMER1_INTERRUPT_FLAG_REGISTER*/
#define TIMER1_OUTPUT_OVERFLOW_INTERRUPT       TOIE1
#define TIMER1_OUTPUT_COMPARE_MATCH_INTERRUPT_A  OCIE1A
#define TIMER1_OUTPUT_COMPARE_MATCH_INTERRUPT_B  OCIE1B

#define INPUT_CAPTURE_REGISRTER1                      ICR1

#define OC1A_PIN                                        PD5
#define OC1A_DATA_PORT                                  PORTD
#define OC1A_DIRECTION_PORT                             DDRD

#define OC1B_PIN                                        PD4
#define OC1B_DATA_PORT                                  PORTD
#define OC1B_DIRECTION_PORT                             DDRD

#define COM1A_SHIFT_VALUE                               6
#define COM1B_SHIFT_VALUE                               4

#define TIMER1_CLOCK_MASK_CLEAR                           0XF8

#define TIMER1_COM1A_MASK_CLEAR                           0X3F
#define TIMER1_COM1B_MASK_CLEAR                            0XCF



/*************************************************************************/



/**************************************************************************
 *                              Timer2
 * ************************************************************************/
/*TIMER2 REGISTERS*/
#define TIMER2_CONTROL_REGIRSTER             TCCR2
#define TIMER2_INITIAL_VALUE_REGISTER        TCNT2
#define TIMER2_OUTPUT_COMPARE_REGISTER       OCR2
#define TIMER2_INTERRUPT_MASK_REGISTER       TIMSK
#define TIMER2_INTERRUPT_FLAG_REGISTER       TIFR

/*TIMER2_CONTROL_REGIRSTER*/
#define TIMER2_FORCE_OUTPUT_COMPARE_BIT       FOC2
#define TIMER2_WAVE_FORM_GENERATION_BIT0      WGM20
#define TIMER2_WAVE_FORM_GENERATION_BIT1      WGM21
#define TIMER2_COMPARE_OUTPUT_MODE_BIT0       COM20
#define TIMER2_COMPARE_OUTPUT_MODE_BIT1       COM21
#define TIMER2_CLOCK_SELECT_BIT0              CS20
#define TIMER2_CLOCK_SELECT_BIT1              CS21
#define TIMER2_CLOCK_SELECT_BIT2              CS22

/*TIMER2_INTERRUPT_FLAG_REGISTER*/
#define TIMER2_OUTPUT_OVERFLOW_INTERRUPT       TOIE2
#define TIMER2_OUTPUT_COMPARE_MATCH_INTERRUPT  OCIE2

#define TIMER2_CLEAR_COMPARE_OUTPUT_MODE_BITS_VALUE     0XCF
#define TIMER2_CLOCK_MASK_CLEAR                           0XF8

#define COM2_SHIFT_VALUE                               4
#define OC2_PIN                                        PD7
#define OC2_DATA_PORT                                  PORTD
#define OC2_DIRECTION_PORT                             DDRD


/****************************************************************************/


/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/

typedef enum
{
	NO_CLOCK,F_CPU_CLOCK,F_CPU_8,F_CPU_64,F_CPU_256,F_CPU_1024
}Timer_Clock;


typedef enum
{
	Timer0,Timer1,Timer2
}Timer_Type;

typedef enum
{
	Overflow, PWM_PhaseCorrect, Compare, FAST_PWM

}Timer_Mode;


typedef enum
{
	ChannelA, ChannelB
}Channel_Type;

typedef enum
{
	Disconnected, Toggle, Clear, Set
}Compare_Output_mode;

typedef struct
{
	uint32 timer_InitialValue;
	uint32 timer_compare_MatchValue;
	Timer_Type  timer_ID;
	Timer_Clock timer_clock;
	Timer_Mode  timer_mode;
	Compare_Output_mode COM;
	Channel_Type compare_register;

}Timer_ConfigType;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description:  Function to Initialize Timer Driver
 *                 - Working in Interrupt Mode
 *                 - Choose Timer initial value
 *                 - Choose Timer_ID (Timer0, Timer1, Timer2)
 *                 - Choose Timer_Mode (OverFlow, Compare)
 *                 - Choose Timer compare match value if using CTC mode
 *                 - Choose Timer_Clock
 */
void Timer_init(const Timer_ConfigType * Config_Ptr);

/*
 * Description: Function to set the Call Back function address.
 */
void Timer_setCallBack(void(*a_ptr)(void), Timer_Type timer_type );

/*
 * Description: Function to stop the clock of the timer to stop incrementing.
 */

void Timer_stop(Timer_Type timer_type);

/*
 * Description: Function to resume the clock of the timer to stop incrementing.
 */

void Timer_start(Timer_Type timer_type, Timer_Clock CLK);

/*
 * Description: Function to DeInit the timer to start again from beginning
 */
void Timer_DeInit(Timer_Type timer_type);

/*
 * Description: Function to reset the timer compare match
 */
void Timer_changeCompareValue(Timer_Type timerID,uint16 newCompareValue, Channel_Type channel);

#endif /* TIMERS_H_ */
