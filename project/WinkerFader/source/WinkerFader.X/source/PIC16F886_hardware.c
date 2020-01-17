/*******************************************************************************
*	Author		|	Date		|	FileName
*-------------------------------------------------------------------------------
*	kenchaan	|	2020/01/13	|	PIC16F886_hardware.c
*-------------------------------------------------------------------------------
*	Description	|	[PIC16F886]ハードウェア制御
*-------------------------------------------------------------------------------
*	Copyright (c) 2020 kenchaan All Rights Reserved.
*******************************************************************************/

	/*             Device overview                  */
	/*               ┌────┐                   */
	/*        MCLR =>│RE3  RB7│-> NC              */
	/*   SW_HAZARD ->│RA0  RB6│-> NC              */
	/* SW_WINKER_R ->│RA1  RB5│-> NC              */
	/* SW_WINKER_R ->│RA2  RB4│-> NC              */
	/*         ILL ->│RA3  RB3│-> NC              */
	/*   SW_POS_EN ->│RA4  RB2│-> NC              */
	/* POS_LUM_VOL ->│RA5  RB1│-> NC              */
	/*         Vss ==│Vss  RB0│-> NC              */
	/*         OSC ==│OSC  Vdd│== Vdd             */
	/*         OSC ==│OSC  Vss│== Vss             */
	/*          NC <-│RC0  RC7│-> OUTPUT_POS_L_EN */
	/*          NC <-│RC1  RC6│-> OUTPUT_POS_R_EN */
	/*         PWM <-│RC2  RC5│-> OUTPUT_L_EN     */
	/*          NC <-│RC3  RC4│-> OUTPUT_R_EN     */
	/*               └────┘                   */

/*------------------------------------------------------------------------------
*	include
*-----------------------------------------------------------------------------*/
#include <xc.h>
#include "types.h"
#include "regaccess.h"
#include "hardware.h"
#include "hardware_ccp.h"
#include "hardware_interrupt.h"
#include "hardware_port.h"
#include "hardware_timer.h"
#include "hardware_wdt.h"

/*------------------------------------------------------------------------------
*	pragma
*-----------------------------------------------------------------------------*/
// CONFIG1
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator: High-speed crystal/resonator on RA6/OSC2/CLKOUT and RA7/OSC1/CLKIN)
#pragma config WDTE = ON        // Watchdog Timer Enable bit (WDT enabled)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#pragma config MCLRE = ON       // RE3/MCLR pin function select bit (RE3/MCLR pin function is MCLR)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = ON       // Brown Out Reset Selection bits (BOR enabled)
#pragma config IESO = ON        // Internal External Switchover bit (Internal/External Switchover mode is enabled)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is enabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

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

	HW_WDT_Initialize();
	HW_INT_Initialize();
	HW_PORT_Initialize();
	HW_TIM_Initialize();
	HW_CCP_Initialize();
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
	while( TRUE ){
		if( HW_INT_IsInterrupted( eINTERRUPT_TYPE_TMR0 )){
			break;
		}
	}
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
	HW_WDT_Clear();
}


/*------------------------------------------------------------------------------
*	End Of File
*-----------------------------------------------------------------------------*/
