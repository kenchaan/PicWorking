/*******************************************************************************
*	Author		|	Date		|	FileName
*-------------------------------------------------------------------------------
*	kenchaan	|	2019/01/22	|	PIC16F886_hardware_interrupt.c
*-------------------------------------------------------------------------------
*	Description	|	[PIC16F886]割り込み制御
*-------------------------------------------------------------------------------
*	Copyright (c) 2019 kenchaan All Rights Reserved.
*******************************************************************************/

/*------------------------------------------------------------------------------
*	include
*-----------------------------------------------------------------------------*/
#include <xc.h>
#include "types.h"
#include "regaccess.h"
#include "hardware_timer.h"
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
	if( REG_READ_08( INTCON ) & 0x04 ){
		/* T0IF */
		REG_WRITE_08( TMR0, TMR0_DEFAULT );
		REG_CLR_08( INTCON, 0x04 );
		HW_TIM_Interrupt( eTIMER_TYPE_FRAME );

	// }else if( REG_READ_08( INTCON ) & 0x02 ){
	// 	/* INTF */
	// 	REG_CLR_08( INTCON, 0x02 );

	// }else if( REG_READ_08( INTCON ) & 0x01 ){
	// 	/* IBIF */
	// 	REG_CLR_08( INTCON, 0x01 );

	// }else if( REG_READ_08( PIR1 ) & 0x40 ){
	// 	/* ADIF */
	// 	REG_CLR_08( PIR1, 0x40 );

	// }else if( REG_READ_08( PIR1 ) & 0x20 ){
	// 	/* RCIF */
	// 	REG_CLR_08( PIR1, 0x20 );

	// }else if( REG_READ_08( PIR1 ) & 0x10 ){
	// 	/* TXIF */
	// 	REG_CLR_08( PIR1, 0x10 );

	// }else if( REG_READ_08( PIR1 ) & 0x08 ){
	// 	/* SSPIF */
	// 	REG_CLR_08( PIR1, 0x08 );

	// }else if( REG_READ_08( PIR1 ) & 0x04 ){
	// 	/* CCP1IF */
	// 	REG_CLR_08( PIR1, 0x04 );

	// }else if( REG_READ_08( PIR1 ) & 0x02 ){
	// 	/* TMR2IF */
	// 	REG_CLR_08( PIR1, 0x02 );

	// }else if( REG_READ_08( PIR1 ) & 0x01 ){
	// 	/* TMR1IF */
	// 	REG_CLR_08( PIR1, 0x01 );

	// }else if( REG_READ_08( PIR2 ) & 0x80 ){
	// 	/* OSFIF */
	// 	REG_CLR_08( PIR2, 0x80 );

	// }else if( REG_READ_08( PIR2 ) & 0x40 ){
	// 	/* C2IF */
	// 	REG_CLR_08( PIR2, 0x40 );

	// }else if( REG_READ_08( PIR2 ) & 0x20 ){
	// 	/* C1IF */
	// 	REG_CLR_08( PIR2, 0x20 );

	// }else if( REG_READ_08( PIR2 ) & 0x10 ){
	// 	/* EEIF */
	// 	REG_CLR_08( PIR2, 0x10 );

	// }else if( REG_READ_08( PIR2 ) & 0x08 ){
	// 	/* BCLIF */
	// 	REG_CLR_08( PIR2, 0x08 );

	// }else if( REG_READ_08( PIR2 ) & 0x04 ){
	// 	/* ULPWUIF */
	// 	REG_CLR_08( PIR2, 0x04 );

	// }else if( REG_READ_08( PIR2 ) & 0x01 ){
	// 	/* CCP2IF */
	// 	REG_CLR_08( PIR2, 0x01 );
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
