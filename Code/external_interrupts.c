/**********************************************************************************
 * [FILE NAME]: external_interrupts.c
 *
 * [AUTHOR]: Toka Zakaria Mohamed Ramadan
 *
 * [DATE CREATED]: Dec 12, 2020
 *
 * [Description]: Function to initialize All External Interrupts.
 *
 ***********************************************************************************/


#include"external_interrupts.h"


/* Global variables to hold the address of the call back function in the application */
static volatile void (*g_INT0_callBackPtr)(void) = NULL_PTR;
static volatile void (*g_INT1_callBackPtr)(void) = NULL_PTR;
static volatile void (*g_INT2_callBackPtr)(void) = NULL_PTR;

/*******************************************************************************
 *                       Interrupt Service Routines                            *
 *******************************************************************************/




/**************************************************************************
 *                            Interrupt0                                  *
 * ************************************************************************/


ISR(INT0_vect)
{
	if(g_INT0_callBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_INT0_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}


/**************************************************************************
 *                            Interrupt1                                  *
 * ************************************************************************/

ISR(INT1_vect)
{
	if(g_INT1_callBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_INT1_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}


/**************************************************************************
 *                            Interrupt2                                  *
 * ************************************************************************/
ISR(INT2_vect)
{
	if(g_INT2_callBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_INT2_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}


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

void External_Interrupt_init(const External_Interrupt_ConfigType* Config_Ptr)
{

	switch(Config_Ptr->INT_ID)
	{

	case INTERRUPT0:

		/*configure pin of interrupt0 as input pin*/
		INTERRUPT0_DIRECTION_PORT = CLEAR_BIT(INTERRUPT0_DIRECTION_PORT, INTERRUPT0_PIN);

		/*static configuration of internal pull up resistance*/
#if (INTERNAL_PULL_UP_INT0 != DISABLE)
		{

			/*Activate internal pull up for interrupt 0*/
			INTERRUPT0_DATA_PORT = SET_BIT(INTERRUPT0_DATA_PORT, INTERRUPT0_PIN);

		}/*end of INTERNAL_PULL_UP_INT0  */
#endif


		/*configure the control edge for interrupt 0*/
		MCU_CONTROL_REGISTER = (MCU_CONTROL_REGISTER & 0XFC) | (Config_Ptr->INT_control) ;

		/*activate external interrupt 0 interrupt enable*/
		GENERAL_INTERRUPT_CONTROL_REGISTER = (GENERAL_INTERRUPT_CONTROL_REGISTER & 0XBF) | (1<<EXTRNAL_INTERRUPT0_ENABL_BIT);

		break;

	case INTERRUPT1:

		/*configure interrupt 1 pin as input pin*/
		INTERRUPT1_DIRECTION_PORT = CLEAR_BIT(INTERRUPT1_DIRECTION_PORT, INTERRUPT1_PIN);

		/*static configuration for the internal interrupt resistance*/
#if (INTERNAL_PULL_UP_INT1 != DISABLE)
		{

			/*Activate internal pull up for interrupt 0*/
			INTERRUPT1_DATA_PORT = SET_BIT(INTERRUPT1_DATA_PORT, INTERRUPT1_PIN);

		}/*end of INTERNAL_PULL_UP_INT0  */
#endif


		/*configure control edge for interrupt 1*/
		MCU_CONTROL_REGISTER = (MCU_CONTROL_REGISTER & 0XF3) | ( (Config_Ptr->INT_control)<< INTERRUPT1_SENSE_CONTROL_BITS);

		/*active external interrupt interrupt enable for interrupt 1*/
		GENERAL_INTERRUPT_CONTROL_REGISTER = (GENERAL_INTERRUPT_CONTROL_REGISTER & 0X7F) | (1<<EXTRNAL_INTERRUPT1_ENABL_BIT);

		break;

	case INTERRUPT2:

		/*configure interrupt 2 pin as input pin */
		INTERRUPT2_DIRECTION_PORT = CLEAR_BIT(INTERRUPT2_DIRECTION_PORT, INTERRUPT2_PIN);

		/*static configuration for interrupt 2 resistance*/
#if (INTERNAL_PULL_UP_INT2 != DISABLE)
		{

			/*Activate internal pull up for interrupt 0*/
			INTERRUPT2_DATA_PORT = SET_BIT(INTERRUPT2_DATA_PORT, INTERRUPT2_PIN);

		}/*end of INTERNAL_PULL_UP_INT0  */
#endif

		/*configure control edge for interrupt 2*/
		MCU_CONTROL_AND_STATUS_REGISTER = (MCU_CONTROL_AND_STATUS_REGISTER & 0XBF) | ( ((Config_Ptr->INT_control) & 0X01)<< ISC2);

		/*Active external interrupt interrupt enable*/
		GENERAL_INTERRUPT_CONTROL_REGISTER = (GENERAL_INTERRUPT_CONTROL_REGISTER & 0XCF) | (1<<EXTRNAL_INTERRUPT2_ENABL_BIT);

		break;


	}/*end of switch case*/

}/*end of External_Interrupt function*/

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

void Interrupt_setCallBack(void(*a_ptr)(void), Interrupt_ID Interrupt_type )
{

	switch(Interrupt_type)
	{
	case INTERRUPT0:
		/* Save the address of the Call back function in a global variable */
		g_INT0_callBackPtr = a_ptr;
		break;

	case INTERRUPT1:
		/* Save the address of the Call back function in a global variable */
		g_INT1_callBackPtr = a_ptr;
		break;

	case INTERRUPT2:
		/* Save the address of the Call back function in a global variable */
		g_INT2_callBackPtr = a_ptr;
		break;
	} /*End of the switch case*/

}/*End of the setCallBack function*/

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

void External_Interrupt_Deinit(Interrupt_ID INT_ID)
{

	switch(INT_ID)
	{

	case INTERRUPT0:

		/*clear all bits of interrupt 0*/
		MCU_CONTROL_REGISTER = (MCU_CONTROL_REGISTER & 0XFC);
		GENERAL_INTERRUPT_CONTROL_REGISTER = (GENERAL_INTERRUPT_CONTROL_REGISTER & 0XBF);

		break;

	case INTERRUPT1:

		/*clear all bits of interrupt 1*/
		MCU_CONTROL_REGISTER = (MCU_CONTROL_REGISTER & 0XF3);

		GENERAL_INTERRUPT_CONTROL_REGISTER = (GENERAL_INTERRUPT_CONTROL_REGISTER & 0X7F);

		break;


	case INTERRUPT2:
		/*clear all bits of interrupt 2*/
		MCU_CONTROL_AND_STATUS_REGISTER = (MCU_CONTROL_AND_STATUS_REGISTER & 0XBF);

		GENERAL_INTERRUPT_CONTROL_REGISTER = (GENERAL_INTERRUPT_CONTROL_REGISTER & 0XCF);
		break;


	}/*end of switch case*/

}/*End of External_Interrupt_Deinit function*/
