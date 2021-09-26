/**********************************************************************************
 * [FILE NAME]: app_file.c
 *
 * [AUTHOR]: Toka Zakaria Mohamed
 *
 * [DATE CREATED]: NOV 06, 2020
 *
 * [Description]: File to contain the application of Controlling Motor
 ***********************************************************************************/

#include"app_file.h"

void buttonFunction(void)
{

		/*Check if the motor spin clock wise or not*/
		if(  BIT_IS_CLEAR(DC_MOTOR_PIN_PORT, DC_MOTOR_PIN_IN1) &&
				BIT_IS_SET(DC_MOTOR_PIN_PORT, DC_MOTOR_PIN_IN2)
				)
		{
			DC_motor_onAnti_ClockWise();

		}
		/*Check if the motor spin Anti-clock wise or not*/
		else if(  BIT_IS_SET(DC_MOTOR_PIN_PORT,DC_MOTOR_PIN_IN1) &&
				BIT_IS_CLEAR(DC_MOTOR_PIN_PORT, DC_MOTOR_PIN_IN2)
				)
		{
			DC_motor_on_ClockWise();

		}

}
