/**********************************************************************************
 * [FILE NAME]:  external_interrupts.h
 *
 * [AUTHOR]: Toka Zakaria Mohamed Ramadan
 *
 * [DATE CREATED]: Dec 12, 2020
 *
 * [Description]: File of All types Declaration and Functions prototypes of
 *                External Interrupts configuration.
 *
 ***********************************************************************************/

#ifndef EXTERNAL_INTERRUPTS_H_
#define EXTERNAL_INTERRUPTS_H_

#include "std_types.h"
#include "micro_config.h"
#include "common_macros.h"

/**************************************************************************
 *                      Preprocessor Macros
 * ************************************************************************/

#define ENABLE                                  TRUE
#define DISABLE                                 FALSE

#define INTERNAL_PULL_UP_INT0                  ENABLE
#define INTERNAL_PULL_UP_INT1                  ENABLE
#define INTERNAL_PULL_UP_INT2                  DISABLE

#define INTERRUPT1_SENSE_CONTROL_BITS            2



#define MCU_CONTROL_REGISTER                   MCUCR
#define MCU_CONTROL_AND_STATUS_REGISTER        MCUCSR
#define GENERAL_INTERRUPT_CONTROL_REGISTER      GICR
#define GENERAL_INTERRUPT_FLAG_REGISTER         GIFR

#define INTERRUPT_SENSE_CONTROL_0_BIT_0         ISC00
#define INTERRUPT_SENSE_CONTROL_0_BIT_1         ISC01
#define INTERRUPT_SENSE_CONTROL_1_BIT_0         ISC10
#define INTERRUPT_SENSE_CONTROL_1_BIT_1         ISC11
#define INTERRUPT_SENSE_CONTROL_2               ISC2

#define EXTERNAL_INTERRUPT_FLAG_0               INTF0
#define EXTERNAL_INTERRUPT_FLAG_1               INTF1
#define EXTERNAL_INTERRUPT_FLAG_2               INTF2

#define EXTRNAL_INTERRUPT0_ENABL_BIT            INT0
#define EXTRNAL_INTERRUPT1_ENABL_BIT            INT1
#define EXTRNAL_INTERRUPT2_ENABL_BIT            INT2


#define INTERRUPT0_DIRECTION_PORT              DDRD
#define INTERRUPT1_DIRECTION_PORT              DDRD
#define INTERRUPT2_DIRECTION_PORT              DDRB

#define INTERRUPT0_DATA_PORT                   PORTD
#define INTERRUPT1_DATA_PORT                   PORTD
#define INTERRUPT2_DATA_PORT                   PORTB

#define INTERRUPT0_PIN                         PD2
#define INTERRUPT1_PIN                         PD3
#define INTERRUPT2_PIN                         PB2

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/

typedef enum
{

INTERRUPT0, INTERRUPT1, INTERRUPT2

}Interrupt_ID;


typedef enum
{

Low_level, Any_logical, Falling, Raising

}Interrupt_Control;


typedef struct
{
	Interrupt_ID  INT_ID;
	Interrupt_Control INT_control;

}External_Interrupt_ConfigType;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/***************************************************************************************************
 * [Function Name]: External_Interrupt_init
 *
 * [Description]:  Function to Initialize External Interrupt Driver
 *                 - Working in Interrupt Mode
 *                 - Choose External interrupt control edge
 *                 - Choose INTERRUPT_ID (INT0, INT1, INT2)
 *
 *
 * [Args]:         Config_Ptr
 *
 * [In]            Config_Ptr: Pointer to Timer Configuration Structure
 *
 * [Out]           NONE
 *
 * [Returns]:      NONE
 ***************************************************************************************************/
void External_Interrupt_init(const External_Interrupt_ConfigType* Config_Ptr);
/***************************************************************************************************
 * [Function Name]: Interrupt_setCallBack
 *
 * [Description]:  Function to set the Call Back function address.
 *
 * [Args]:         a_Ptr, Interrupt_ID
 *
 * [In]            a_Ptr: -Pointer to function
 *                        -To use it to save receive the function call back name
 *                        -To store it in the global pointer to function to use it in
 *
 *                 timer_type: -Variable from type enum Timer_Mode
 *                             -To use it to choose the type of the timer
 *
 * [Out]           NONE
 *
 * [Returns]:      NONE
 ***************************************************************************************************/
void Interrupt_setCallBack(void(*a_ptr)(void), Interrupt_ID Interrupt_type );
/***************************************************************************************************
 * [Function Name]: External_Interrupt_DeInit
 *
 * [Description]:  Function to DeInit the timer to start again from beginning
 *
 * [Args]:         timer_type
 *
 *
 * [In]            timer_type: -Variable from type enum Timer_Mode
 *                             -To use it to choose the type of the timer
 *                             -DeInit the required timer
 *
 * [Out]           NONE
 *
 * [Returns]:      NONE
 ***************************************************************************************************/
void External_Interrupt_Deinit(Interrupt_ID INT_ID);

#endif /* EXTERNAL_INTERRUPTS_H_ */
