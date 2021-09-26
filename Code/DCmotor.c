/**********************************************************************************
 * [FILE NAME]: motor.c
 *
 * [AUTHOR]: Toka Zakaria Mohamed Ramadan
 *
 * [DATE CREATED]: Nov 5, 2020
 *
 * [Description]: Functions will be used to work with DC motor.
 *
 ***********************************************************************************/

#include"DCmotor.h"



void DC_motor_Init(void)
{
	DC_MOTOR_DIRECTION_PORT = SET_BIT(DC_MOTOR_DIRECTION_PORT , DC_MOTOR_PIN_IN1);
	DC_MOTOR_DIRECTION_PORT = SET_BIT(DC_MOTOR_DIRECTION_PORT , DC_MOTOR_PIN_IN2);

#if ENABLE_PIN_CONNECTED_TO_MICRO

	DC_MOTOR_ENABLE_DIRECTION_PORT = SET_BIT(DC_MOTOR_ENABLE_DIRECTION_PORT , DC_MOTOR_PIN_EN1);
#endif
}
/***************************************************************************************************
 * [Function Name]: motor_on_ClockWise
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
 ***************************************************************************************************/

void DC_motor_on_ClockWise(void)
{
	DC_MOTOR_DATA_PORT = CLEAR_BIT(DC_MOTOR_DATA_PORT , DC_MOTOR_PIN_IN1);
	DC_MOTOR_DATA_PORT = SET_BIT(DC_MOTOR_DATA_PORT , DC_MOTOR_PIN_IN2);

}/*End of motor_onClockWise*/

/***************************************************************************************************
 * [Function Name]: motor_on_AntiClockWise
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
 ***************************************************************************************************/

void DC_motor_onAnti_ClockWise(void)
{
	DC_MOTOR_DATA_PORT = CLEAR_BIT( DC_MOTOR_DATA_PORT, DC_MOTOR_PIN_IN2);
	DC_MOTOR_DATA_PORT = SET_BIT (DC_MOTOR_DATA_PORT, DC_MOTOR_PIN_IN1);

}/*End of motor_onClockWise*/

/***************************************************************************************************
 * [Function Name]: motor_on_ClockWise
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
 ***************************************************************************************************/
void DC_motor_on_Stop(void)
{
	DC_MOTOR_DATA_PORT = CLEAR_BIT(DC_MOTOR_DATA_PORT , DC_MOTOR_PIN_IN2);
	DC_MOTOR_DATA_PORT = CLEAR_BIT( DC_MOTOR_DATA_PORT, DC_MOTOR_PIN_IN1);

}/*End of motor_onClockWise*/
/**************************************************************************************************/
