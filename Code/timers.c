/**********************************************************************************
 * [FILE NAME]: timer.c
 *
 * [AUTHOR]: Toka Zakaria Mohamed Ramadan
 *
 * [DATE CREATED]: Nov 5, 2020
 *
 * [Description]: Function to initialize All Timers in Atmega16
 *
 ***********************************************************************************/

#include"timers.h"

/* Global variables to hold the address of the call back function in the application */
static volatile void (*g_Timer0_callBackPtr)(void) = NULL_PTR;
static volatile void (*g_Timer1_callBackPtr)(void) = NULL_PTR;
static volatile void (*g_Timer2_callBackPtr)(void) = NULL_PTR;

/*******************************************************************************
 *                       Interrupt Service Routines                            *
 *******************************************************************************/




/**************************************************************************
 *                              Timer0
 * ************************************************************************/
ISR(TIMER0_OVF_vect)
{
	if(g_Timer0_callBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_Timer0_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
	/* Clear the flag of timer0 over flow Interrupt*/
	TIFR = SET_BIT(TIFR, TOV0);
}

ISR(TIMER0_COMP_vect)
{
	if(g_Timer0_callBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_Timer0_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
	/* Clear the flag of timer0 compare Interrupt*/
	TIFR = SET_BIT(TIFR, OCF0);
}

/**************************************************************************
 *                              Timer1
 * ************************************************************************/
ISR(TIMER1_OVF_vect)
{
	if(g_Timer1_callBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_Timer1_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
	/* Clear the flag of timer1 over flow Interrupt*/
	TIFR = SET_BIT(TIFR, TOV1);

}

ISR(TIMER1_COMPA_vect)
{
	if(g_Timer1_callBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_Timer1_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
	/* Clear the flag of timer1 compare Interrupt for channelA*/
	TIFR = SET_BIT(TIFR, OCF1A);

}

ISR(TIMER1_COMPB_vect)
{
	if(g_Timer1_callBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_Timer1_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
	/* Clear the flag of timer1 compare Interrupt for channelB*/
	TIFR = SET_BIT(TIFR, OCF1B);

}

/**************************************************************************
 *                              Timer2
 * ************************************************************************/
ISR(TIMER2_OVF_vect)
{
	if(g_Timer0_callBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_Timer2_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}

	/* Clear the flag of timer2 over flow Interrupt*/
	TIFR = SET_BIT(TIFR, TOV2);

}

ISR(TIMER2_COMP_vect)
{
	if(g_Timer2_callBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_Timer2_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
	/* Clear the flag of timer2 compare Interrupt*/
	TIFR = SET_BIT(TIFR, OCF2);
}
/*****************************************************************************************/



/***************************************************************************************************
 * [Function Name]: TIMER_init
 *
 * [Description]:  Function to Initialize Timer Driver
 *                 - Working in Interrupt Mode
 *                 - Choose Timer initial value
 *                 - Choose Timer_ID (Timer0, Timer1, Timer2)
 *                 - Choose Timer_Mode (OverFlow, Compare)
 *                 - Choose Timer compare match value if using CTC mode
 *                 - Choose Timer_Clock
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

void Timer_init(const Timer_ConfigType * Config_Ptr)
{

	switch( (Config_Ptr->timer_ID) )
	{
	/**************************************************************************
	 *                              Timer0
	 * ************************************************************************/
	case Timer0:

		/*Clear registers of Timer0 before accessing any of them*/
		TIMER0_CONTROL_REGIRSTER        &= 0X00;
		TIMER0_INITIAL_VALUE_REGISTER   &= 0X00;
		TIMER0_OUTPUT_COMPARE_REGISTER  &= 0X00;
		TIMER0_INTERRUPT_MASK_REGISTER  &= 0X00;

		/*
		 * Configure initial value for Timer0 to start count from it
		 * Anding with 0XFF to make sure the value won't exceed
		 * 255 as it is 8-bit Timer
		 */

		TIMER0_CONTROL_REGIRSTER = ( (Config_Ptr->timer_InitialValue) ) & 0XFF;

		/*
		 * Configure Clock Pre-scaler value for Timer0 in TCCR0 Register
		 * Anding with 0XF8 to make sure the first 3-bits in TCCR0 register=0
		 * ORing with the selected timer clock to include it in the first 3-bits
		 * and keep the other bits as they are
		 */

		TIMER0_CONTROL_REGIRSTER = (TIMER0_CONTROL_REGIRSTER  & TIMER0_CLOCK_MASK_CLEAR) | (Config_Ptr->timer_clock);


		switch(Config_Ptr->timer_mode)
		{
		case Overflow:

			/*
			 * Configure wave form generation mode to work with normal mode
			 * Clear WGM00 bit in TCCR0 register
			 * Clear WGM01 bit in TCCR0 register
			 */
			TIMER0_CONTROL_REGIRSTER  = CLEAR_BIT(TIMER0_CONTROL_REGIRSTER , TIMER0_WAVE_FORM_GENERATION_BIT0);
			TIMER0_CONTROL_REGIRSTER  = CLEAR_BIT(TIMER0_CONTROL_REGIRSTER , TIMER0_WAVE_FORM_GENERATION_BIT1);

			/*
			 * Configure compare output mode to work with normal port operation
			 * Decide the mode of OC0 from compare output modes with non PWM
			 * Configure COM00 bit in TCCR0 register
			 * Configure COM01 bit in TCCR0 register
			 */
			TIMER0_CONTROL_REGIRSTER = (TIMER0_CONTROL_REGIRSTER & TIMER0_COM0_MASK_CLEAR ) | ((Config_Ptr->COM)<<COM0_SHIFT_VALUE);

			/*
			 * Configure FOC0 bit in the TCCR0 register to be active
			 * As Timer0 is non-PWM
			 * Make FOC0 to be Active as it is overflow mode
			 */
			TIMER0_CONTROL_REGIRSTER = SET_BIT(TIMER0_CONTROL_REGIRSTER,TIMER0_FORCE_OUTPUT_COMPARE_BIT);

			/*
			 * Enable Timer0 overflow interrupt
			 * wait for: -Enable I-bit "mask bit" in the SREG register
			 *           -TOV0 bit in the TIFR register to be set
			 * Timer0 overflow mode is ready to work after that
			 */
			TIMER0_INTERRUPT_MASK_REGISTER = SET_BIT(TIMER0_INTERRUPT_MASK_REGISTER, TIMER0_OUTPUT_OVERFLOW_INTERRUPT);
			break;


		case PWM_PhaseCorrect:

			/*
			 * Configure OC0 as Output PIN
			 * the pin where the PWM signal is generated from MC
			 */

			OC0_DIRECTION_PORT = SET_BIT(OC0_DIRECTION_PORT, OC0_PIN);

			/*
			 *Clear force output compare bit in Timer/Counter control register
			 *to work with pulse width modulation
			 */
			TIMER0_CONTROL_REGIRSTER = CLEAR_BIT(TIMER0_CONTROL_REGIRSTER, TIMER0_FORCE_OUTPUT_COMPARE_BIT);

			/*
			 * Configure wave form generation mode to work with normal mode
			 * SET WGM00 bit in TCCR0 register
			 * Clear WGM01 bit in TCCR0 register
			 */
			TIMER0_CONTROL_REGIRSTER = SET_BIT(TIMER0_CONTROL_REGIRSTER, TIMER0_WAVE_FORM_GENERATION_BIT0);
			TIMER0_CONTROL_REGIRSTER = CLEAR_BIT(TIMER0_CONTROL_REGIRSTER, TIMER0_WAVE_FORM_GENERATION_BIT1);

			/*
			 * Configure compare output mode to work with normal port operation
			 * Decide the mode of OC0 from compare output modes with non PWM
			 * Configure COM00 bit in TCCR0 register
			 * Configure COM01 bit in TCCR0 register
			 */
			TIMER0_CONTROL_REGIRSTER = (TIMER0_CONTROL_REGIRSTER & TIMER0_COM0_MASK_CLEAR ) | ((Config_Ptr->COM)<<COM0_SHIFT_VALUE);

			/*
			 * Configure Compare match value for Timer0 to start count till reach it
			 * Anding with 0XFF to make sure the value won't exceed
			 * 255 as it is 8-bit Timer
			 */
			TIMER0_OUTPUT_COMPARE_REGISTER = ((Config_Ptr->timer_compare_MatchValue)) & 0XFF;

			break; /*End of PWM_PhaseCorrect*/


		case Compare:

			/*
			 * Configure wave form generation mode to work with normal mode
			 * Clear WGM00 bit in TCCR0 register
			 * Clear WGM01 bit in TCCR0 register
			 */
			TIMER0_CONTROL_REGIRSTER = CLEAR_BIT(TIMER0_CONTROL_REGIRSTER, TIMER0_WAVE_FORM_GENERATION_BIT0);
			TIMER0_CONTROL_REGIRSTER = SET_BIT(TIMER0_CONTROL_REGIRSTER, TIMER0_WAVE_FORM_GENERATION_BIT1);

			/*
			 * Configure compare output mode to work with normal port operation
			 * Decide the mode of OC0 from compare output modes with non PWM
			 * Configure COM00 bit in TCCR0 register
			 * Configure COM01 bit in TCCR0 register
			 */
			TIMER0_CONTROL_REGIRSTER = (TIMER0_CONTROL_REGIRSTER & TIMER0_COM0_MASK_CLEAR ) | ((Config_Ptr->COM)<<COM0_SHIFT_VALUE);

			/*
			 * Configure FOC0 bit in the TCCR0 register to be active
			 * As Timer0 is non-PWM
			 * Make FOC0 to be Active as it is compare mode
			 */
			TIMER0_CONTROL_REGIRSTER = SET_BIT(TIMER0_CONTROL_REGIRSTER, TIMER0_FORCE_OUTPUT_COMPARE_BIT);

			/*
			 * Configure Compare match value for Timer0 to start count from it
			 * Anding with 0XFF to make sure the value won't exceed
			 * 255 as it is 8-bit Timer
			 */
			TIMER0_OUTPUT_COMPARE_REGISTER = ((Config_Ptr->timer_compare_MatchValue)) & 0XFF;

			/*
			 * Enable Timer0 compare match interrupt
			 * wait for: -Enable I-bit "mask bit" in the SREG register
			 *           -OCF0 bit in the TIFR register to be set
			 * Timer0 compare match mode is ready to work after that
			 */
			TIMER0_INTERRUPT_MASK_REGISTER = SET_BIT(TIMER0_INTERRUPT_MASK_REGISTER, TIMER0_OUTPUT_COMPARE_MATCH_INTERRUPT);

			break; /*End of compare mode*/

		case FAST_PWM:
			/*
			 * Configure OC0 as Output PIN
			 * the pin where the PWM signal is generated from MC
			 */

			OC0_DIRECTION_PORT = SET_BIT(OC0_DIRECTION_PORT, OC0_PIN);

			/*
			 *Clear force output compare bit in Timer/Counter control register
			 *to work with pulse width modulation
			 */
			TIMER0_CONTROL_REGIRSTER = CLEAR_BIT(TIMER0_CONTROL_REGIRSTER, TIMER0_FORCE_OUTPUT_COMPARE_BIT);

			/*
			 * Configure wave form generation mode to work with normal mode
			 * SET WGM00 bit in TCCR0 register
			 * SET WGM01 bit in TCCR0 register
			 */
			TIMER0_CONTROL_REGIRSTER = SET_BIT(TIMER0_CONTROL_REGIRSTER, TIMER0_WAVE_FORM_GENERATION_BIT0);
			TIMER0_CONTROL_REGIRSTER = SET_BIT(TIMER0_CONTROL_REGIRSTER, TIMER0_WAVE_FORM_GENERATION_BIT1);

			/*
			 * Configure compare output mode to work with normal port operation
			 * Decide the mode of OC0 from compare output modes with non PWM
			 * Configure COM00 bit in TCCR0 register
			 * Configure COM01 bit in TCCR0 register
			 */
			TIMER0_CONTROL_REGIRSTER = (TIMER0_CONTROL_REGIRSTER & TIMER0_COM0_MASK_CLEAR ) | ((Config_Ptr->COM)<<COM0_SHIFT_VALUE);

			/*
			 * Configure Compare match value for Timer0 to start count till reach it
			 * Anding with 0XFF to make sure the value won't exceed
			 * 255 as it is 8-bit Timer
			 */
			TIMER0_OUTPUT_COMPARE_REGISTER = ((Config_Ptr->timer_compare_MatchValue)) & 0XFF;

			break;/*End of Fast PWM*/

		} /*End of internal switch case for modes for Timer 0*/

		break; /*End ofTimer0*/

		/**************************************************************************
		 *                              Timer1
		 * ************************************************************************/
		case Timer1:

			/*Clear registers of Timer1 before accessing any of them*/
			TIMER1_CONTROL_REGIRSTER_A        &= 0X00;
			TIMER1_CONTROL_REGIRSTER_B        &= 0X00;
			TIMER1_INITIAL_VALUE_REGISTER     &= 0X00;
			TIMER1_OUTPUT_COMPARE_REGISTER_A  &= 0X00;
			TIMER1_INTERRUPT_MASK_REGISTER    &= 0X00;

			/*
			 * Configure initial value for Timer1 to start count from it
			 * Anding with 0XFFFF to make sure the value won't exceed
			 *  0XFFFF as it is 16-bit Timer
			 */
			TIMER1_INITIAL_VALUE_REGISTER = ( (Config_Ptr->timer_InitialValue) ) & 0XFFFF;

			/*
			 * Configure Clock Pre-scaler value for Timer0 in TCCR1B Register
			 * Anding with 0XF8 to make sure the first 3-bits in TCCR1B register=0
			 * ORing with the selected timer clock to include it in the first 3-bits
			 * and keep the other bits as they are
			 */
			TIMER1_CONTROL_REGIRSTER_B =  (TIMER1_CONTROL_REGIRSTER_B & TIMER1_CLOCK_MASK_CLEAR) | (Config_Ptr->timer_clock);

			switch( (Config_Ptr->timer_mode) )
			{
			case Overflow:

				switch((Config_Ptr->compare_register))
				{

				case ChannelA:
					/*
					 * Configure compare output mode to work with Timer1
					 * with one mode from 4 modes in TCCR1A
					 * Configure COM1A0/COM1A1 bits in TCCR1A register
					 */
					TIMER1_CONTROL_REGIRSTER_A = (TIMER1_CONTROL_REGIRSTER_A & TIMER1_COM1A_MASK_CLEAR) | ((Config_Ptr->COM)<<COM1A_SHIFT_VALUE);

					/*
					 * Configure FOC1A bit in the TCCR1 register to be active
					 * As Timer1 is non-PWM
					 * Make FOC1A to be Active as it is overflow mode
					 */
					TIMER1_CONTROL_REGIRSTER_A =  SET_BIT(TIMER1_CONTROL_REGIRSTER_A, TIMER1_FORCE_OUTPUT_COMPARE_BIT_A);

					break; /*End of Channel A*/

				case ChannelB:

					/*
					 * Configure compare output mode to work with Timer1
					 * with one mode from 4 modes in TCCR1A
					 * Configure COM1B0/COM1B1 bits in TCCR1A register
					 */
					TIMER1_CONTROL_REGIRSTER_A = (TIMER1_CONTROL_REGIRSTER_A & TIMER1_COM1B_MASK_CLEAR) | ((Config_Ptr->COM)<<COM1B_SHIFT_VALUE);

					/*
					 * Configure FOC1B bit in the TCCR1 register to be active
					 * As Timer1 is non-PWM
					 * Make FOC1B to be Active as it is overflow mode
					 */
					TIMER1_CONTROL_REGIRSTER_A =  SET_BIT(TIMER1_CONTROL_REGIRSTER_A, TIMER1_FORCE_OUTPUT_COMPARE_BIT_B);

					break;/*End of channel B*/
				}/*End of Channel Type*/

				/*
				 * Configure wave form generation mode to work with normal mode
				 * Clear WGM10/WMG11 bit in TCCR1A register
				 */
				TIMER1_CONTROL_REGIRSTER_A =  CLEAR_BIT(TIMER1_CONTROL_REGIRSTER_A, TIMER1_WAVE_FORM_GENERATION_BIT10);
				TIMER1_CONTROL_REGIRSTER_A =  CLEAR_BIT(TIMER1_CONTROL_REGIRSTER_A, TIMER1_WAVE_FORM_GENERATION_BIT11);

				/*
				 * Configure wave form generation mode to work with normal mode
				 * Clear WGM12/WMG13 bit in TCCR1B register
				 */
				TIMER1_CONTROL_REGIRSTER_B =  CLEAR_BIT(TIMER1_CONTROL_REGIRSTER_B, TIMER1_WAVE_FORM_GENERATION_BIT12);
				TIMER1_CONTROL_REGIRSTER_B =  CLEAR_BIT(TIMER1_CONTROL_REGIRSTER_B, TIMER1_WAVE_FORM_GENERATION_BIT13);

				/*
				 * Enable Timer1 overflow interrupt
				 * wait for: -Enable I-bit "mask bit" in the SREG register
				 *           -TOV1 bit in the TIFR register to be set
				 * Timer1 overflow mode is ready to work after that
				 */
				TIMER1_INTERRUPT_MASK_REGISTER = SET_BIT(TIMER1_INTERRUPT_MASK_REGISTER,TIMER1_OUTPUT_OVERFLOW_INTERRUPT);

				break;

				case PWM_PhaseCorrect:

					/*
					 * Configure wave form generation mode to work with PWM_PhaseCorrect TOP in ICR1
					 * Clear WGM10 bit in TCCR1A register
					 * Set WGM11 bit in TCCR1A register
					 */
					TIMER1_CONTROL_REGIRSTER_A =  CLEAR_BIT(TIMER1_CONTROL_REGIRSTER_A, TIMER1_WAVE_FORM_GENERATION_BIT10);
					TIMER1_CONTROL_REGIRSTER_A =  SET_BIT(TIMER1_CONTROL_REGIRSTER_A, TIMER1_WAVE_FORM_GENERATION_BIT11);

					/*
					 * Configure wave form generation mode to work with normal mode
					 * Set WMG13 bit in TCCR1B register
					 * Clear WMG12 bit in TCCR1B register
					 */
					TIMER1_CONTROL_REGIRSTER_B =  CLEAR_BIT(TIMER1_CONTROL_REGIRSTER_B, TIMER1_WAVE_FORM_GENERATION_BIT12);
					TIMER1_CONTROL_REGIRSTER_B =  SET_BIT(TIMER1_CONTROL_REGIRSTER_B, TIMER1_WAVE_FORM_GENERATION_BIT13);


				switch((Config_Ptr->compare_register))
				{

				case ChannelA:

					/*
					 * Configure OC1A as Output PIN
					 * the pin where the PWM signal is generated from MC
					 */
					OC1A_DIRECTION_PORT = SET_BIT(OC1A_DIRECTION_PORT, OC1A_PIN);

					/*
					 * Configure FOC1A bit in the TCCR1 register to be active
					 * As Timer1 is PWM
					 * Make FOC1A to be Active as it is Fast PWM mode
					 */
					TIMER1_CONTROL_REGIRSTER_A =  CLEAR_BIT(TIMER1_CONTROL_REGIRSTER_A,TIMER1_FORCE_OUTPUT_COMPARE_BIT_A);

					/*
					 * Configure compare output mode to work with Timer1
					 * with one mode from 4 modes in TCCR1A
					 * Configure COM1A0/COM1A1 bits in TCCR1A register
					 */
					TIMER1_CONTROL_REGIRSTER_A = (TIMER1_CONTROL_REGIRSTER_A & TIMER1_COM1A_MASK_CLEAR) | ((Config_Ptr->COM)<<COM1A_SHIFT_VALUE);

					/*
					 * Configure Compare match value for Timer1 to start count till reach it
					 * Anding with 0XFFFF to make sure the value won't exceed
					 * OXFFFF as it is 16-bit Timer
					 */
					INPUT_CAPTURE_REGISRTER1 = ((Config_Ptr->timer_compare_MatchValue)) & 0XFFFF;

					break; /*End of channel A*/

				case ChannelB:
					/*
					 * Configure OC1A as Output PIN
					 * the pin where the PWM signal is generated from MC
					 */
					OC1B_DIRECTION_PORT = SET_BIT(OC1B_DIRECTION_PORT, OC1A_PIN);

					/*
					 * Configure FOC1A bit in the TCCR1 register to be active
					 * As Timer1 is PWM
					 * Make FOC1A to be Active as it is Fast PWM mode
					 */
					TIMER1_CONTROL_REGIRSTER_A =  CLEAR_BIT(TIMER1_CONTROL_REGIRSTER_A,TIMER1_FORCE_OUTPUT_COMPARE_BIT_B);

					/*
					 * Configure compare output mode to work with Timer1
					 * with one mode from 4 modes in TCCR1A
					 * Configure COM1B0/COM1B1 bits in TCCR1A register
					 */
					TIMER1_CONTROL_REGIRSTER_A = (TIMER1_CONTROL_REGIRSTER_A & TIMER1_COM1B_MASK_CLEAR) | ((Config_Ptr->COM)<<COM1B_SHIFT_VALUE);

					/*
					 * Configure Compare match value for Timer1 to start count till reach it
					 * Anding with 0XFFFF to make sure the value won't exceed
					 * OXFFFF as it is 16-bit Timer
					 */
					INPUT_CAPTURE_REGISRTER1 = ((Config_Ptr->timer_compare_MatchValue)) & 0XFFFF;

					break; /*End of channel B*/

				}/*End of Switch case Channel Type*/

					break; /*End of PWM_PhaseCorrect*/

				case Compare:

					/*
					 * Configure wave form generation mode to work with normal mode
					 * Clear WGM10/WMG11 bit in TCCR1A register
					 */
					TIMER1_CONTROL_REGIRSTER_A =  CLEAR_BIT(TIMER1_CONTROL_REGIRSTER_A, TIMER1_WAVE_FORM_GENERATION_BIT10);
					TIMER1_CONTROL_REGIRSTER_A =  CLEAR_BIT(TIMER1_CONTROL_REGIRSTER_A, TIMER1_WAVE_FORM_GENERATION_BIT11);

					/*
					 * Configure wave form generation mode to work with normal mode
					 * Clear WMG13 bit in TCCR1B register
					 * Set WMG12 bit in TCCR1B register
					 */
					TIMER1_CONTROL_REGIRSTER_B =  SET_BIT(TIMER1_CONTROL_REGIRSTER_B, TIMER1_WAVE_FORM_GENERATION_BIT12);
					TIMER1_CONTROL_REGIRSTER_B =  CLEAR_BIT(TIMER1_CONTROL_REGIRSTER_B, TIMER1_WAVE_FORM_GENERATION_BIT13);

					switch(Config_Ptr->compare_register)
					{

					case ChannelA:

						/*
						 * Configure FOC1A bit in the TCCR1 register to be active
						 * As Timer1 is non-PWM
						 * Make FOC1A to be Active as it is compare mode
						 */
						TIMER1_CONTROL_REGIRSTER_A =  SET_BIT(TIMER1_CONTROL_REGIRSTER_A,TIMER1_FORCE_OUTPUT_COMPARE_BIT_A);
						/*
						 * Configure compare output mode to work with Timer1
						 * with one mode from 4 modes in TCCR1A
						 * Configure COM1A0/COM1A1 bits in TCCR1A register
						 */
						TIMER1_CONTROL_REGIRSTER_A = (TIMER1_CONTROL_REGIRSTER_A & TIMER1_COM1A_MASK_CLEAR) | ((Config_Ptr->COM)<<COM1A_SHIFT_VALUE);
						/*
						 * Configure Compare match value for Timer1 to start count from it
						 * Anding with 0XFFFF to make sure the value won't exceed
						 * OXFFFF as it is 16-bit Timer
						 */
						TIMER1_OUTPUT_COMPARE_REGISTER_A = ((Config_Ptr->timer_compare_MatchValue)) & 0XFFFF;
						/*
						 * Enable Timer1 compare match interrupt
						 * wait for: -Enable I-bit "mask bit" in the SREG register
						 *           -OCF1 bit in the TIFR register to be set
						 * Timer1 compare match mode is ready to work after that
						 */
						TIMER1_INTERRUPT_MASK_REGISTER = SET_BIT(TIMER1_INTERRUPT_MASK_REGISTER,TIMER1_OUTPUT_COMPARE_MATCH_INTERRUPT_A);

						break; /*End of channel A*/

					case ChannelB:

						/*
						 * Configure FOC1B bit in the TCCR1 register to be active
						 * As Timer1 is non-PWM
						 * Make FOC1B to be Active as it is compare mode
						 */
						TIMER1_CONTROL_REGIRSTER_A =  SET_BIT(TIMER1_CONTROL_REGIRSTER_A,TIMER1_FORCE_OUTPUT_COMPARE_BIT_B);

						/*
						 * Configure compare output mode to work with Timer1
						 * with one mode from 4 modes in TCCR1A
						 * Configure COM1B0/COM1B1 bits in TCCR1A register
						 */
						TIMER1_CONTROL_REGIRSTER_A = (TIMER1_CONTROL_REGIRSTER_A & TIMER1_COM1B_MASK_CLEAR) | ((Config_Ptr->COM)<<COM1B_SHIFT_VALUE);

						/*
						 * Configure Compare match value for Timer1 to start count from it
						 * Anding with 0XFFFF to make sure the value won't exceed
						 * OXFFFF as it is 16-bit Timer
						 * to make it count right put OCR1A  greater than the value in OCR1B by 1
						 */
						TIMER1_OUTPUT_COMPARE_REGISTER_A = (((Config_Ptr->timer_compare_MatchValue)) & 0XFFFF) + 1;
						TIMER1_OUTPUT_COMPARE_REGISTER_B = ((Config_Ptr->timer_compare_MatchValue)) & 0XFFFF;

						/*
						 * Enable Timer1 compare match interrupt
						 * wait for: -Enable I-bit "mask bit" in the SREG register
						 *           -OCF1 bit in the TIFR register to be set
						 * Timer1 compare match mode is ready to work after that
						 */
						TIMER1_INTERRUPT_MASK_REGISTER = SET_BIT(TIMER1_INTERRUPT_MASK_REGISTER,TIMER1_OUTPUT_COMPARE_MATCH_INTERRUPT_B);

						break;/*End of channel B*/

					}/*End of Channel Type switch case*/

					break;

					case FAST_PWM:

						/*
						 * Configure wave form generation mode to work with Fast PWM TOP in ICR1
						 * Clear WGM10 bit in TCCR1A register
						 * SET WGM11 bit in TCCR1A register
						 */
						TIMER1_CONTROL_REGIRSTER_A =  CLEAR_BIT(TIMER1_CONTROL_REGIRSTER_A, TIMER1_WAVE_FORM_GENERATION_BIT10);
						TIMER1_CONTROL_REGIRSTER_A =  SET_BIT(TIMER1_CONTROL_REGIRSTER_A, TIMER1_WAVE_FORM_GENERATION_BIT11);

						/*
						 * Configure wave form generation mode to work with normal mode
						 * SET WMG13 bit in TCCR1B register
						 * Set WMG12 bit in TCCR1B register
						 */
						TIMER1_CONTROL_REGIRSTER_B =  SET_BIT(TIMER1_CONTROL_REGIRSTER_B, TIMER1_WAVE_FORM_GENERATION_BIT12);
						TIMER1_CONTROL_REGIRSTER_B =  SET_BIT(TIMER1_CONTROL_REGIRSTER_B, TIMER1_WAVE_FORM_GENERATION_BIT13);


					switch((Config_Ptr->compare_register))
					{

					case ChannelA:

						/*
						 * Configure OC1A as Output PIN
						 * the pin where the PWM signal is generated from MC
						 */
						OC1A_DIRECTION_PORT = SET_BIT(OC1A_DIRECTION_PORT, OC1A_PIN);

						/*
						 * Configure FOC1A bit in the TCCR1 register to be active
						 * As Timer1 is PWM
						 * Make FOC1A to be Active as it is Fast PWM mode
						 */
						TIMER1_CONTROL_REGIRSTER_A =  CLEAR_BIT(TIMER1_CONTROL_REGIRSTER_A,TIMER1_FORCE_OUTPUT_COMPARE_BIT_A);

						/*
						 * Configure compare output mode to work with Timer1
						 * with one mode from 4 modes in TCCR1A
						 * Configure COM1A0/COM1A1 bits in TCCR1A register
						 */
						TIMER1_CONTROL_REGIRSTER_A = (TIMER1_CONTROL_REGIRSTER_A & TIMER1_COM1A_MASK_CLEAR) | ((Config_Ptr->COM)<<COM1A_SHIFT_VALUE);

						/*
						 * Configure Compare match value for Timer1 to start count till reach it
						 * Anding with 0XFFFF to make sure the value won't exceed
						 * OXFFFF as it is 16-bit Timer
						 */
						INPUT_CAPTURE_REGISRTER1 = ((Config_Ptr->timer_compare_MatchValue)) & 0XFFFF;

						break;

					case ChannelB:
						/*
						 * Configure OC1B as Output PIN
						 * the pin where the PWM signal is generated from MC
						 */
						OC1B_DIRECTION_PORT = SET_BIT(OC1B_DIRECTION_PORT, OC1B_PIN);

						/*
						 * Configure FOC1A bit in the TCCR1 register to be active
						 * As Timer1 is PWM
						 * Make FOC1A to be Active as it is Fast PWM mode
						 */
						TIMER1_CONTROL_REGIRSTER_A =  CLEAR_BIT(TIMER1_CONTROL_REGIRSTER_A,TIMER1_FORCE_OUTPUT_COMPARE_BIT_B);

						/*
						 * Configure compare output mode to work with Timer1
						 * with one mode from 4 modes in TCCR1A
						 * Configure COM1A0/COM1A1 bits in TCCR1A register
						 */
						TIMER1_CONTROL_REGIRSTER_A = (TIMER1_CONTROL_REGIRSTER_A & TIMER1_COM1B_MASK_CLEAR) | ((Config_Ptr->COM)<<COM1B_SHIFT_VALUE);

						/*
						 * Configure Compare match value for Timer1 to start count till reach it
						 * Anding with 0XFFFF to make sure the value won't exceed
						 * OXFFFF as it is 16-bit Timer
						 */
						INPUT_CAPTURE_REGISRTER1 = ((Config_Ptr->timer_compare_MatchValue)) & 0XFFFF;

						break;

					}/*End of Switch case Channel Type*/

						break; /*End of FAST PWM*/

			} /*End of internal switch case*/

			break; /*End of Timer1*/

			/**************************************************************************
			 *                              Timer2
			 * ************************************************************************/
			case Timer2:

				/*Clear registers of Timer0 before accessing any of them*/
				TIMER2_CONTROL_REGIRSTER        &= 0X00;
				TIMER2_INITIAL_VALUE_REGISTER   &= 0X00;
				TIMER2_OUTPUT_COMPARE_REGISTER  &= 0X00;
				TIMER2_INTERRUPT_MASK_REGISTER  &= 0X00;
				/*************************************************************************/
				ASSR  &= 0X00;
				/*******************************************************************************/
				/*
				 * Configure initial value for Timer2 to start count from it
				 * Anding with 0XFF to make sure the value won't exceed
				 * 255 as it is 8-bit Timer
				 */

				TIMER2_INITIAL_VALUE_REGISTER = ( (Config_Ptr->timer_InitialValue) ) & 0XFF;

				/*
				 * Configure Clock Pre-scaler value for Timer0 in TCCR2 Register
				 * Anding with 0XF8 to make sure the first 3-bits in TCCR2 register=0
				 * ORing with the selected timer clock to include it in the first 3-bits
				 * and keep the other bits as they are
				 */

				TIMER2_CONTROL_REGIRSTER = (TIMER2_CONTROL_REGIRSTER  & TIMER2_CLOCK_MASK_CLEAR) | (Config_Ptr->timer_clock);


				switch(Config_Ptr->timer_mode)
				{
				case Overflow:

					/*
					 * Configure wave form generation mode to work with normal mode
					 * Clear WGM00 bit in TCCR0 register
					 * Clear WGM01 bit in TCCR0 register
					 */
					TIMER2_CONTROL_REGIRSTER  = CLEAR_BIT(TIMER2_CONTROL_REGIRSTER , TIMER2_WAVE_FORM_GENERATION_BIT0);
					TIMER2_CONTROL_REGIRSTER  = CLEAR_BIT(TIMER2_CONTROL_REGIRSTER , TIMER2_WAVE_FORM_GENERATION_BIT1);

					/*
					 * Configure compare output mode to work with normal port operation
					 * configure OC2
					 * Configure COM20 bit in TCCR2 register
					 * Configure COM21 bit in TCCR2 register
					 */
					TIMER2_CONTROL_REGIRSTER = (TIMER2_CONTROL_REGIRSTER & TIMER2_CLEAR_COMPARE_OUTPUT_MODE_BITS_VALUE ) | ((Config_Ptr->COM)<<COM2_SHIFT_VALUE);

					/*
					 * Configure FOC2 bit in the TCCR2 register to be active
					 * As Timer2 is non-PWM
					 * Make FOC2 to be Active as it is overflow mode
					 */
					TIMER2_CONTROL_REGIRSTER =  SET_BIT(TIMER2_CONTROL_REGIRSTER ,TIMER2_FORCE_OUTPUT_COMPARE_BIT);


					/*
					 * Enable Timer0 overflow interrupt
					 * wait for: -Enable I-bit "mask bit" in the SREG register
					 *           -TOV0 bit in the TIFR register to be set
					 * Timer0 overflow mode is ready to work after that
					 */
					TIMER2_INTERRUPT_MASK_REGISTER = SET_BIT(TIMER2_INTERRUPT_MASK_REGISTER,TIMER2_OUTPUT_OVERFLOW_INTERRUPT);

					break;

				case PWM_PhaseCorrect:

					/*
					 * Configure OC0 as Output PIN
					 * the pin where the PWM signal is generated from MC
					 */

					OC2_DIRECTION_PORT = SET_BIT(OC2_DIRECTION_PORT, OC2_PIN);

					/*
					 *Clear force output compare bit in Timer/Counter control register
					 *to work with pulse width modulation
					 */
					TIMER2_CONTROL_REGIRSTER = CLEAR_BIT(TIMER2_CONTROL_REGIRSTER, TIMER2_FORCE_OUTPUT_COMPARE_BIT);

					/*
					 * Configure wave form generation mode to work with normal mode
					 * SET WGM00 bit in TCCR0 register
					 * Clear WGM01 bit in TCCR0 register
					 */
					TIMER2_CONTROL_REGIRSTER = SET_BIT(TIMER2_CONTROL_REGIRSTER, TIMER2_WAVE_FORM_GENERATION_BIT0);
					TIMER2_CONTROL_REGIRSTER = CLEAR_BIT(TIMER2_CONTROL_REGIRSTER, TIMER2_WAVE_FORM_GENERATION_BIT1);

					/*
					 * Configure compare output mode to work with normal port operation
					 * Decide the mode of OC0 from compare output modes with non PWM
					 * Configure COM00 bit in TCCR0 register
					 * Configure COM01 bit in TCCR0 register
					 */
					TIMER2_CONTROL_REGIRSTER = (TIMER2_CONTROL_REGIRSTER & TIMER2_CLEAR_COMPARE_OUTPUT_MODE_BITS_VALUE ) | ((Config_Ptr->COM)<<COM2_SHIFT_VALUE);
					/*
					 * Configure Compare match value for Timer0 to start count till reach it
					 * Anding with 0XFF to make sure the value won't exceed
					 * 255 as it is 8-bit Timer
					 */
					TIMER2_OUTPUT_COMPARE_REGISTER = ((Config_Ptr->timer_compare_MatchValue)) & 0XFF;

					break;

				case Compare:
					/*
					 * Configure wave form generation mode to work with normal mode
					 * Clear WGM20 bit in TCCR2 register
					 * Clear WGM21 bit in TCCR2 register
					 */
					TIMER2_CONTROL_REGIRSTER  = CLEAR_BIT(TIMER2_CONTROL_REGIRSTER , TIMER2_WAVE_FORM_GENERATION_BIT0);
					TIMER2_CONTROL_REGIRSTER  = SET_BIT(TIMER2_CONTROL_REGIRSTER , TIMER2_WAVE_FORM_GENERATION_BIT1);

					/*
					 * Configure compare output mode to work with normal port operation
					 * configure OC2
					 * Configure COM20 bit in TCCR2 register
					 * Configure COM21 bit in TCCR2 register
					 */
					TIMER2_CONTROL_REGIRSTER = (TIMER2_CONTROL_REGIRSTER & TIMER2_CLEAR_COMPARE_OUTPUT_MODE_BITS_VALUE ) | ((Config_Ptr->COM)<<COM2_SHIFT_VALUE);

					/*
					 * Configure FOC2 bit in the TCCR2 register to be active
					 * As Timer2 is non-PWM
					 * Make FOC2 to be Active as it is compare mode
					 */
					TIMER2_CONTROL_REGIRSTER =  SET_BIT(TIMER2_CONTROL_REGIRSTER , TIMER2_FORCE_OUTPUT_COMPARE_BIT);

					/*
					 * Configure Compare match value for Timer2 to start count from it
					 * Anding with 0XFF to make sure the value won't exceed
					 * 255 as it is 8-bit Timer
					 */
					TIMER2_OUTPUT_COMPARE_REGISTER = ((Config_Ptr->timer_compare_MatchValue)) & 0XFF;

					/*
					 * Enable Timer2 compare match interrupt
					 * wait for: -Enable I-bit "mask bit" in the SREG register
					 *           -OCF2 bit in the TIFR register to be set
					 * Timer2 compare match mode is ready to work after that
					 */
					TIMER2_INTERRUPT_MASK_REGISTER = SET_BIT(TIMER2_INTERRUPT_MASK_REGISTER, TIMER2_OUTPUT_COMPARE_MATCH_INTERRUPT);
					break;

				case FAST_PWM:

					/*
					 * Configure OC0 as Output PIN
					 * the pin where the PWM signal is generated from MC
					 */

					OC2_DIRECTION_PORT = SET_BIT(OC2_DIRECTION_PORT, OC2_PIN);

					/*
					 *Clear force output compare bit in Timer/Counter control register
					 *to work with pulse width modulation
					 */
					TIMER2_CONTROL_REGIRSTER = CLEAR_BIT(TIMER2_CONTROL_REGIRSTER, TIMER2_FORCE_OUTPUT_COMPARE_BIT);

					/*
					 * Configure wave form generation mode to work with normal mode
					 * SET WGM00 bit in TCCR0 register
					 * SET WGM01 bit in TCCR0 register
					 */
					TIMER2_CONTROL_REGIRSTER = SET_BIT(TIMER2_CONTROL_REGIRSTER, TIMER2_WAVE_FORM_GENERATION_BIT0);
					TIMER2_CONTROL_REGIRSTER = SET_BIT(TIMER2_CONTROL_REGIRSTER, TIMER2_WAVE_FORM_GENERATION_BIT1);

					/*
					 * Configure compare output mode to work with normal port operation
					 * Decide the mode of OC0 from compare output modes with non PWM
					 * Configure COM00 bit in TCCR0 register
					 * Configure COM01 bit in TCCR0 register
					 */
					TIMER2_CONTROL_REGIRSTER = (TIMER2_CONTROL_REGIRSTER & TIMER2_CLEAR_COMPARE_OUTPUT_MODE_BITS_VALUE ) | ((Config_Ptr->COM)<<COM2_SHIFT_VALUE);

					/*
					 * Configure Compare match value for Timer0 to start count till reach it
					 * Anding with 0XFF to make sure the value won't exceed
					 * 255 as it is 8-bit Timer
					 */
					TIMER2_OUTPUT_COMPARE_REGISTER = ((Config_Ptr->timer_compare_MatchValue)) & 0XFF;

					break;

				} /*End of internal switch case*/


				break; /*End of Timer2*/

	}/*End of Super switch case*/

}/*End of the Timer_init*/


/***************************************************************************************************
 * [Function Name]: Timer_setCallBack
 *
 * [Description]:  Function to set the Call Back function address.
 *
 * [Args]:         a_Ptr, timer_type
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
void Timer_setCallBack(void(*a_ptr)(void), Timer_Type timer_type )
{

	switch(timer_type)
	{
	case Timer0:
		/* Save the address of the Call back function in a global variable */
		g_Timer0_callBackPtr = a_ptr;
		break;

	case Timer1:
		/* Save the address of the Call back function in a global variable */
		g_Timer1_callBackPtr = a_ptr;
		break;

	case Timer2:
		/* Save the address of the Call back function in a global variable */
		g_Timer2_callBackPtr = a_ptr;
		break;
	} /*End of the switch case*/

}/*End of the setCallBack function*/



void Timer_changeCompareValue(Timer_Type timerID,uint16 newCompareValue, Channel_Type channel)
{
	switch(timerID)
	{

	case Timer0:

		/*
		 * Clear Output Compare Match register for Timer0
		 * then put the new compare value in it, Anding with 0XFF to make
		 * sure the value won't exceed 255 as it is 8-bit Timer
		 */
		TIMER0_OUTPUT_COMPARE_REGISTER = (TIMER0_OUTPUT_COMPARE_REGISTER & 0X00) |
				(newCompareValue & 0XFF);
		break;

	case Timer1:
		/*
		 * Clear Output Compare Match register for Timer1
		 * then put the new compare value in it, Anding with 0XFFFF to make
		 * sure the value won't exceed 0xffff as it is 16-bit Timer
		 */
		switch(channel)
		{
		case ChannelA:
			TIMER1_OUTPUT_COMPARE_REGISTER_A = (TIMER1_OUTPUT_COMPARE_REGISTER_A & 0X0000) |  (newCompareValue & 0XFFFF);

			break;

		case ChannelB:

			TIMER1_OUTPUT_COMPARE_REGISTER_A = ( (TIMER1_OUTPUT_COMPARE_REGISTER_A & 0X0000) |  (newCompareValue & 0XFFFF) ) + 1;
			TIMER1_OUTPUT_COMPARE_REGISTER_B =   (TIMER1_OUTPUT_COMPARE_REGISTER_B & 0X0000) |  (newCompareValue & 0XFFFF);

			break;
		}

		break;

	case Timer2:

		/*
		 * Clear Output Compare Match register for Timer2
		 * then put the new compare value in it, Anding with 0XFF to make
		 * sure the value won't exceed 255 as it is 8-bit Timer
		 */
		TIMER2_OUTPUT_COMPARE_REGISTER = (TIMER2_OUTPUT_COMPARE_REGISTER & 0X00) |
				(newCompareValue & 0XFF);
		break;

	default:
		break;
	}

}

/***************************************************************************************************
 * [Function Name]: Timer_stop
 *
 * [Description]:  Function to stop the clock of the timer to stop incrementing
 *
 * [Args]:         timer_type
 *
 *
 * [In]            timer_type: -Variable from type enum Timer_Mode
 *                             -To use it to choose the type of the timer
 *                             -stop the required timer
 *
 * [Out]           NONE
 *
 * [Returns]:      NONE
 ***************************************************************************************************/
void Timer_stop(Timer_Type timer_type)
{

	switch(timer_type)
	{
	case Timer0:
		/*
		 * Clear the first 3-bits in TCCR0 register
		 * stop the clock of the timer
		 * timer0 will stop incrementing
		 */
		TIMER0_CONTROL_REGIRSTER = (TIMER0_CONTROL_REGIRSTER  & TIMER0_CLOCK_MASK_CLEAR) ;
		break;

	case Timer1:

		/*
		 * Clear the first 3-bits in TCCR1B register
		 * stop the clock of the timer
		 * timer1 will stop incrementing
		 */
		TIMER1_CONTROL_REGIRSTER_B  =  (TIMER1_CONTROL_REGIRSTER_B  & TIMER1_CLOCK_MASK_CLEAR) ;
		break;


	case Timer2:
		/*
		 * Clear the first 3-bits in TCCR2 register
		 * stop the clock of the timer
		 * timer2 will stop incrementing
		 */
		TIMER2_CONTROL_REGIRSTER = (TIMER2_CONTROL_REGIRSTER  & TIMER2_CLOCK_MASK_CLEAR) ;
		break;

	} /*End of the switch case*/


}/*End of the Timer_stop function*/


/***************************************************************************************************
 * [Function Name]: Timer_resume
 *
 * [Description]:  Function to stop the clock of the timer to stop incrementing
 *
 * [Args]:         timer_type, CLK
 *
 *
 * [In]            timer_type: -Variable from type enum Timer_Mode
 *                             -To use it to choose the type of the timer
 *                             -stop the required timer
 *
 *                  CLK:       -Variable from type enum Timer_Clock
 *                             -To use it to choose the clock of the timer
 *
 * [Out]           NONE
 *
 * [Returns]:      NONE
 ***************************************************************************************************/
void Timer_start(Timer_Type timer_type, Timer_Clock CLK)
{

	switch(timer_type)
	{
	case Timer0:
		/*
		 * Clear the first 3-bits in TCCR0 register
		 * stop the clock of the timer
		 * timer0 will stop incrementing
		 */
		TIMER0_CONTROL_REGIRSTER = (TIMER0_CONTROL_REGIRSTER  & TIMER0_CLOCK_MASK_CLEAR) | CLK ;
		break;

	case Timer1:

		/*
		 * Clear the first 3-bits in TCCR1B register
		 * stop the clock of the timer
		 * timer1 will stop incrementing
		 */
		TIMER1_CONTROL_REGIRSTER_B  =  (TIMER1_CONTROL_REGIRSTER_B  & TIMER1_CLOCK_MASK_CLEAR) | CLK;
		break;


	case Timer2:
		/*
		 * Clear the first 3-bits in TCCR2 register
		 * stop the clock of the timer
		 * timer2 will stop incrementing
		 */
		TIMER2_CONTROL_REGIRSTER = (TIMER2_CONTROL_REGIRSTER  & TIMER2_CLOCK_MASK_CLEAR) | CLK;
		break;

	} /*End of the switch case*/


}/*End of the Timer_stop function*/

/***************************************************************************************************
 * [Function Name]: Timer_DeInit
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

void Timer_DeInit(Timer_Type timer_type)
{
	switch(timer_type)
	{
	case Timer0:

		/*Clear all register in Timer0*/
		TIMER0_CONTROL_REGIRSTER        &= 0X00;
		TIMER0_INITIAL_VALUE_REGISTER   &= 0X00;
		TIMER0_OUTPUT_COMPARE_REGISTER  &= 0X00;
		TIMER0_INTERRUPT_MASK_REGISTER  &= 0X00;
		break;

	case Timer1:

		/*Clear all register in Timer1*/
		TIMER1_CONTROL_REGIRSTER_A         &= 0X00;
		TIMER1_CONTROL_REGIRSTER_B         &= 0X00;
		TIMER1_INITIAL_VALUE_REGISTER      &= 0X00;
		TIMER1_OUTPUT_COMPARE_REGISTER_A   &= 0X00;
		TIMER1_OUTPUT_COMPARE_REGISTER_B   &= 0X00;
		TIMER1_INTERRUPT_MASK_REGISTER     &= 0X00;
		INPUT_CAPTURE_REGISRTER1           &= 0X00;
		break;


	case Timer2:

		/*Clear all register in Timer2*/
		TIMER2_CONTROL_REGIRSTER        &= 0X00;
		TIMER2_INITIAL_VALUE_REGISTER   &= 0X00;
		TIMER2_OUTPUT_COMPARE_REGISTER  &= 0X00;
		TIMER2_INTERRUPT_MASK_REGISTER  &= 0X00;
		break;

	} /*End of the switch case*/


}/*end of the Timer_DeInit function*/
