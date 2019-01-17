/*******************************************************************************
*	Author		|	Date		|	FileName
*-------------------------------------------------------------------------------
*	ken_chaan	|	2019/01/07	|	PIC16F886_hardware.c
*-------------------------------------------------------------------------------
*	Description	|	[PIC16F886]ハードウェア制御
*-------------------------------------------------------------------------------
*	Copyright (c) 2019 ken_chaan All Rights Reserved.
*******************************************************************************/

	/*             Device overview                */
	/*               ┌────┐                 */
	/*        MCLR =>│RE3  RB7│-> ICE           */
	/*   DIGIT_H10 <-│RA0  RB6│-> ICE           */
	/*   DIGIT_H01 <-│RA1  RB5│-> ERR_SSP_RECV  */
	/*   DIGIT_M10 <-│RA2  RB4│-> ERR_SSP_RECV  */
	/*   DIGIT_M01 <-│RA3  RB3│-> ERR_PROC_FAIL */
	/*       SEG_A <-│RA4  RB2│-> ST_SSP_RECV   */
	/*       SEG_B <-│RA5  RB1│-> ST_INT_SSP    */
	/*         Vss ==│Vss  RB0│-> ST_INT_TMR0   */
	/*         OSC ==│OSC  Vdd│== Vdd           */
	/*         OSC ==│OSC  Vss│== Vss           */
	/*       SEG_C <-│RC0  RC7│-> SEG_DP        */
	/*       SEG_D <-│RC1  RC6│-> SEG_G         */
	/*       SEG_E <-│RC2  RC5│-> SEG_F         */
	/*         I2C =>│SCL  SDA│<= I2C           */
	/*               └────┘                 */

/*------------------------------------------------------------------------------
*	include
*-----------------------------------------------------------------------------*/
#include <xc.h>
#include "types.h"
#include "regaccess.h"
#include "hardware_interrupt.h"
#include "hardware_port.h"
#include "hardware_ssp.h"
#include "hardware_timer.h"
#include "hardware.h"

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
	HW_SSP_Initialize();
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
	/* DO NOTHING */
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
	/* 処理落ちチェック */
	if( HW_TIM_GetCount( eTIMER_TYPE_FRAME ) != 0 ){
		/* 処理落ち */
		HW_PORT_Set( eOUTPUT_PORT_ERROR_PROC_FAIL, TRUE );
	}else{
		HW_PORT_Set( eOUTPUT_PORT_ERROR_PROC_FAIL, FALSE );
	}
}


/*------------------------------------------------------------------------------
*	End Of File
*-----------------------------------------------------------------------------*/
