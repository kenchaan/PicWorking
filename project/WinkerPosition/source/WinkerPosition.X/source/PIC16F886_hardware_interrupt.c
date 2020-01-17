/*******************************************************************************
*	Author		|	Date		|	FileName
*-------------------------------------------------------------------------------
*	kenchaan	|	2020/01/17	|	PIC16F886_hardware_interrupt.c
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
volatile static BOOL g_isInterrupted_Ary[ eINTERRUPT_TYPE_MAX ];

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
		g_isInterrupted_Ary[ eINTERRUPT_TYPE_TMR0 ] = TRUE;

	//}else if( REG_READ_08( INTCON ) & 0x02 ){
	//	/* INTF */
	//	REG_CLR_08( INTCON, 0x02 );
	//	g_isInterrupted_Ary[ eINTERRUPT_TYPE_INT ] = TRUE;

	//}else if( REG_READ_08( INTCON ) & 0x01 ){
	//	/* IBIF */
	//	REG_CLR_08( INTCON, 0x01 );
	//	g_isInterrupted_Ary[ eINTERRUPT_TYPE_PORTB ] = TRUE;

	//}else if( REG_READ_08( PIR1 ) & 0x40 ){
	//	/* ADIF */
	//	REG_CLR_08( PIR1, 0x40 );
	//	g_isInterrupted_Ary[ eINTERRUPT_TYPE_ADC ] = TRUE;

	//}else if( REG_READ_08( PIR1 ) & 0x20 ){
	//	/* RCIF */
	//	REG_CLR_08( PIR1, 0x20 );
	//	g_isInterrupted_Ary[ eINTERRUPT_TYPE_EUSART_RECEIVE ] = TRUE;

	//}else if( REG_READ_08( PIR1 ) & 0x10 ){
	//	/* TXIF */
	//	REG_CLR_08( PIR1, 0x10 );
	//	g_isInterrupted_Ary[ eINTERRUPT_TYPE_EUSART_TRANS ] = TRUE;

	//}else if( REG_READ_08( PIR1 ) & 0x08 ){
	//	/* SSPIF */
	//	REG_CLR_08( PIR1, 0x08 );
	//	g_isInterrupted_Ary[ eINTERRUPT_TYPE_MSSP ] = TRUE;

	//}else if( REG_READ_08( PIR1 ) & 0x04 ){
	//	/* CCP1IF */
	//	REG_CLR_08( PIR1, 0x04 );
	//	g_isInterrupted_Ary[ eINTERRUPT_TYPE_CCP1 ] = TRUE;

	}else if( REG_READ_08( PIR1 ) & 0x02 ){
		/* TMR2IF */
		REG_WRITE_08( TMR0, TMR2_DEFAULT );
		REG_CLR_08( PIR1, 0x02 );
		g_isInterrupted_Ary[ eINTERRUPT_TYPE_TMR2 ] = TRUE;

	//}else if( REG_READ_08( PIR1 ) & 0x01 ){
	//	/* TMR1IF */
	//	REG_CLR_08( PIR1, 0x01 );
	//	g_isInterrupted_Ary[ eINTERRUPT_TYPE_TMR1 ] = TRUE;

	//}else if( REG_READ_08( PIR2 ) & 0x80 ){
	//	/* OSFIF */
	//	REG_CLR_08( PIR2, 0x80 );
	//	g_isInterrupted_Ary[ eINTERRUPT_TYPE_OSCFAIL ] = TRUE;

	//}else if( REG_READ_08( PIR2 ) & 0x40 ){
	//	/* C2IF */
	//	REG_CLR_08( PIR2, 0x40 );
	//	g_isInterrupted_Ary[ eINTERRUPT_TYPE_C2 ] = TRUE;

	//}else if( REG_READ_08( PIR2 ) & 0x20 ){
	//	/* C1IF */
	//	REG_CLR_08( PIR2, 0x20 );
	//	g_isInterrupted_Ary[ eINTERRUPT_TYPE_C1 ] = TRUE;

	//}else if( REG_READ_08( PIR2 ) & 0x10 ){
	//	/* EEIF */
	//	REG_CLR_08( PIR2, 0x10 );
	//	g_isInterrupted_Ary[ eINTERRUPT_TYPE_EEPROM ] = TRUE;

	//}else if( REG_READ_08( PIR2 ) & 0x08 ){
	//	/* BCLIF */
	//	REG_CLR_08( PIR2, 0x08 );
	//	g_isInterrupted_Ary[ eINTERRUPT_TYPE_BUS ] = TRUE;

	//}else if( REG_READ_08( PIR2 ) & 0x04 ){
	//	/* ULPWUIF */
	//	REG_CLR_08( PIR2, 0x04 );
	//	g_isInterrupted_Ary[ eINTERRUPT_TYPE_ULPWU ] = TRUE;

	//}else if( REG_READ_08( PIR2 ) & 0x01 ){
	//	/* CCP2IF */
	//	REG_CLR_08( PIR2, 0x01 );
	//	g_isInterrupted_Ary[ eINTERRUPT_TYPE_CCP2 ] = TRUE;
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

	for( E_INTERRUPT_TYPE e = eINTERRUPT_TYPE_MIN; e < eINTERRUPT_TYPE_MAX; e++ ){
		g_isInterrupted_Ary[ e ] = FALSE;
	}

	/* 割り込み許可 */
	REG_SET_08( INTCON, 0xC0 );
}

/*------------------------------------------------------------------------------
* OverView	: 割り込み状態取得
* Parameter	: type	: 割り込み種別
* Return	: TRUE	: 割り込みあり
* 			: FALSE	: 割り込みなし
*-----------------------------------------------------------------------------*/
BOOL HW_INT_IsInterrupted( CE_INTERRUPT_TYPE type )
{
	BOOL interrupted = g_isInterrupted_Ary[ type ];
	if( interrupted ){
		g_isInterrupted_Ary[ type ] = FALSE;
	}

	return interrupted;
}


/*------------------------------------------------------------------------------
*	End Of File
*-----------------------------------------------------------------------------*/
