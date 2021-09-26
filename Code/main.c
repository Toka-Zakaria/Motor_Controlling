/**********************************************************************************
 * [FILE NAME]: main.c
 *
 * [AUTHOR]: Toka Zakaria Mohamed
 *
 * [DATE CREATED]: NOV 06, 2020
 *
 * [Description]: File to contain the application of Controlling Motor
 ***********************************************************************************/
#include"app_file.h"


int main(void)
{

	/* Enable interrupts by setting I-bit */
	SREG  |= (1<<7);

	/*******************************************************************************
	 *                               Initialization                                *
	 *******************************************************************************/
	/*Variable to store the value of ADC */
	uint16 res_value=0;

	External_Interrupt_ConfigType  button;
	Timer_ConfigType timer;

	button.INT_ID = INTERRUPT1;
	button.INT_control = Raising;

	timer.COM = Clear;
	timer.timer_ID = Timer0;
	timer.timer_clock= F_CPU_8;
	timer.timer_mode = FAST_PWM;
	timer.timer_InitialValue =0;
	timer.timer_compare_MatchValue=0;

	Interrupt_setCallBack(buttonFunction, INTERRUPT1);


	DC_motor_Init();  /* initialize DC motor driver */
	LCD_init(); /* initialize LCD driver */
	ADC_init(); /* initialize ADC driver */
	External_Interrupt_init(&button); /* initialize external interrupt driver */
	Timer_init(&timer);   /* initialize timer driver */

	LCD_clearScreen(); /* clear LCD at the beginning */
	/* display this string "ADC Value = " only once at LCD */
	LCD_displayString("ADC Value = ");

	DC_motor_on_ClockWise();

	/*configure Resistor pin as input pin to read the value of pot*/
	CLEAR_BIT(RESISTOR_DIRECTION_REG, RESISTOR_PIN);
	/***********************Application*************************/
	while(1)
	{
		LCD_goToRowColumn(0,12); /* display the number every time at this position */
		res_value = ADC_readChannel(0); /* read channel zero where the potentiometer is connect */

		/*Timer0 is 8-bit mode so we have to devide the value of the
		 * resistance over 4 to get the range of 0:256*/
		Timer_changeCompareValue(Timer0, res_value/4, 0);
		LCD_intgerToString(res_value); /* display the ADC value on LCD screen */

	}

	return 0;
}
