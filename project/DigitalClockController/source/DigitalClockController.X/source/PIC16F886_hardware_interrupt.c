/*******************************************************************************
*	Author		|	Date		|	FileName
*-------------------------------------------------------------------------------
*	kenchaan	|	2020/05/13	|	PIC16F886_hardware_interrupt.c
*-------------------------------------------------------------------------------
*	Description	|	[PIC16F886]割り込み制御
*-------------------------------------------------------------------------------
*	Copyright (c) 2020 kenchaan All Rights Reserved.
*******************************************************************************/

/*------------------------------------------------------------------------------
*	include
*-----------------------------------------------------------------------------*/
#include <xc.h>
#include "types.h"
#include "regaccess.h"
#include "hardware_timer.h"
#include "application.h"
#include "hardware_interrupt.h"

/*------------------------------------------------------------------------------
*	pragma
*-----------------------------------------------------------------------------*/


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
* OverView	: 割り込みハンドラ
* Parameter	: None
* Return	: None
*-----------------------------------------------------------------------------*/
void interrupt InterruptHandler( void )
{
	/* T0IF */
	if( REG_READ_08( INTCON ) & 0x04 ){
		REG_WRITE_08( TMR0, TMR0_DEFAULT );
		REG_CLR_08( INTCON, 0x04 );

		/* アプリケーションメイン処理 */
		APP_FrameProcess();

	/* TMR1IF */
	}else if( REG_READ_08( PIR1 ) & 0x01 ){
		REG_WRITE_08( TMR1H, TMR1H_DEFAULT );
		REG_CLR_08( PIR1, 0x01 );

		/* 時間カウント処理 */
		HW_TIM_Update();
	}
}

/*------------------------------------------------------------------------------
* OverView	: 割り込み初期化
* Parameter	: None
* Return	: None
*-----------------------------------------------------------------------------*/
void HW_INT_Initialize( void )
{
	/* 割り込み禁止 */
	REG_WRITE_08( INTCON, 0x00 );
	REG_WRITE_08( PIE1, 0x00 );
	REG_WRITE_08( PIE2, 0x00 );
}

/*------------------------------------------------------------------------------
* OverView	: 割り込み処理開始
* Parameter	: None
* Return	: None
*-----------------------------------------------------------------------------*/
void HW_INT_StartProcess( void )
{
	/* 割り込み状態初期化 */
	REG_CLR_08( INTCON, 0x07 );
	REG_CLR_08( PIR1, 0x7F );
	REG_CLR_08( PIR2, 0xFD );

	/* 割り込み許可 */
	REG_SET_08( INTCON, 0xC0 );
}


/*------------------------------------------------------------------------------
*	End Of File
*-----------------------------------------------------------------------------*/
