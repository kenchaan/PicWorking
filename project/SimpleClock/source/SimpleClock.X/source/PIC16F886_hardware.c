/*******************************************************************************
*	Author		|	Date		|	FileName
*-------------------------------------------------------------------------------
*	kenchaan	|	2019/01/23	|	PIC16F886_hardware.c
*-------------------------------------------------------------------------------
*	Description	|	[PIC16F886]ハードウェア制御
*-------------------------------------------------------------------------------
*	Copyright (c) 2019 kenchaan All Rights Reserved.
*******************************************************************************/

	/*             Device overview            */
	/*               ┌────┐             */
	/*        MCLR =>│RE3  RB7│-> SEG_DP    */
	/*     SW_HOUR ->│RA0  RB6│-> SEG_G     */
	/*   SW_MINUTE ->│RA1  RB5│-> SEG_F     */
	/*   SW_SECOND ->│RA2  RB4│-> SEG_E     */
	/* ST_INT_TMR0 <-│RA3  RB3│-> SEG_D     */
	/* ST_INT_TMR1 <-│RA4  RB2│-> SEG_C     */
	/*          NC <-│RA5  RB1│-> SEG_B     */
	/*         Vss ==│Vss  RB0│-> SEG_A     */
	/*         OSC ==│OSC  Vdd│== Vdd       */
	/*         OSC ==│OSC  Vss│== Vss       */
	/*       T1OSO ->│OSC  RC7│-> DIGIT_M01 */
	/*       T1OSI ->│OSC  RC6│-> DIGIT_M10 */
	/*          NC <-│RC2  RC5│-> DIGIT_H01 */
	/*       COLON <-│RC3  RC4│-> DIGIT_H10 */
	/*               └────┘             */

/*------------------------------------------------------------------------------
*	include
*-----------------------------------------------------------------------------*/
#include <xc.h>
#include "types.h"
#include "regaccess.h"
#include "hardware.h"
#include "hardware_interrupt.h"
#include "hardware_port.h"
#include "hardware_timer.h"

/*------------------------------------------------------------------------------
*	pragma
*-----------------------------------------------------------------------------*/
// CONFIG1
#pragma config FOSC = HS		// Oscillator Selection bits (HS oscillator: High-speed crystal/resonator on RA6/OSC2/CLKOUT and RA7/OSC1/CLKIN)
#pragma config WDTE = OFF		// Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = ON		// Power-up Timer Enable bit (PWRT enabled)
#pragma config MCLRE = ON		// RE3/MCLR pin function select bit (RE3/MCLR pin function is MCLR)
#pragma config CP = OFF			// Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF		// Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = ON		// Brown Out Reset Selection bits (BOR enabled)
#pragma config IESO = ON		// Internal External Switchover bit (Internal/External Switchover mode is enabled)
#pragma config FCMEN = ON		// Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is enabled)
#pragma config LVP = OFF		// Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V	// Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF		// Flash Program Memory Self Write Enable bits (Write protection off)

/*------------------------------------------------------------------------------
*	define
*-----------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------
*	macro
*-----------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------
*	typedef
*-----------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------
*	enum
*-----------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------
*	struct
*-----------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------
*	static variable
*-----------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------
*	static function prototype
*-----------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------
*	static const data
*-----------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------
*	extern const data
*-----------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------
*	function
*-----------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
* OverView	: ハードウェア初期化
* Parameter	: None
* Return	: None
*-----------------------------------------------------------------------------*/
void HW_Initialize( void )
{
	/* 基本設定 */
	REG_WRITE_08( PCON, 0x03 );

	HW_INT_Initialize();
	HW_PORT_Initialize();
	HW_TIM_Initialize();
}

/*------------------------------------------------------------------------------
* OverView	: 処理開始
* Parameter	: None
* Return	: None
*-----------------------------------------------------------------------------*/
void HW_StartProcess( void )
{
	HW_TIM_StartProcess();
	HW_INT_StartProcess();
}

/*------------------------------------------------------------------------------
* OverView	: フレーム待ち処理
* Parameter	: None
* Return	: None
*-----------------------------------------------------------------------------*/
void HW_WaitFrameStart( void )
{
	/* フレーム開始待ち */
	U32 current = HW_TIM_GetCount( eTIMER_TYPE_FRAME );
	while( HW_TIM_GetCount( eTIMER_TYPE_FRAME ) == current );
	HW_TIM_Clear( eTIMER_TYPE_FRAME );
}

/*------------------------------------------------------------------------------
* OverView	: フレーム事前処理
* Parameter	: None
* Return	: None
*-----------------------------------------------------------------------------*/
void HW_FramePreProcess( void )
{
	HW_PORT_Update();
}

/*------------------------------------------------------------------------------
* OverView	: フレーム処理
* Parameter	: None
* Return	: None
*-----------------------------------------------------------------------------*/
void HW_FrameMainProcess( void )
{
	/* DO NOTHING */
}

/*------------------------------------------------------------------------------
* OverView	: フレーム事後処理
* Parameter	: None
* Return	: None
*-----------------------------------------------------------------------------*/
void HW_FramePostProcess( void )
{
	/* DO NOTHING */
}


/*------------------------------------------------------------------------------
*	End Of File
*-----------------------------------------------------------------------------*/
