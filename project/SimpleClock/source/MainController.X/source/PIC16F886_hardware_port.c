/*******************************************************************************
*	Author		|	Date		|	FileName
*-------------------------------------------------------------------------------
*	ken_chaan	|	2018/12/26	|	PIC16F886_hardware_port.c
*-------------------------------------------------------------------------------
*	Description	|	[PIC16F886]ポート制御
*-------------------------------------------------------------------------------
*	Copyright (c) 2018 ken_chaan All Rights Reserved.
*******************************************************************************/

/*------------------------------------------------------------------------------
*	include
*-----------------------------------------------------------------------------*/
#include <xc.h>
#include "types.h"
#include "regaccess.h"
#include "hardware_port.h"

/*------------------------------------------------------------------------------
*	pragma
*-----------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------
*	define
*-----------------------------------------------------------------------------*/
#define CHATTER_COUNT					((U08)5)
#define CONTINUE_COUNT					((U08)100)

/* output port */
#define PROC_FAIL_PORT					(PORTB)
#define PROC_FAIL_BIT					(0x01)
#define STATUS_INT_TMR0_PORT			(PORTB)
#define STATUS_INT_TMR0_BIT				(0x02)
#define STATUS_INT_TMR1_PORT			(PORTB)
#define STATUS_INT_TMR1_BIT				(0x04)
#define STATUS_INT_SSP_PORT				(PORTB)
#define STATUS_INT_SSP_BIT				(0x08)
#define STATUS_SSP_SEND_PORT			(PORTB)
#define STATUS_SSP_SEND_BIT				(0x10)
#define ERROR_SSP_STORE_PORT			(PORTB)
#define ERROR_SSP_STORE_BIT				(0x20)
#define ERROR_SSP_SEND_START_PORT		(PORTB)
#define ERROR_SSP_SEND_START_BIT		(0x40)
#define ERROR_SSP_SEND_FAIL_PORT		(PORTB)
#define ERROR_SSP_SEND_FAIL_BIT			(0x80)

/* input port */
#define BUTTON_HOUR_PORT				(PORTA)
#define BUTTON_HOUR_BIT					(0x01)
#define BUTTON_MINUTE_PORT				(PORTA)
#define BUTTON_MINUTE_BIT 				(0x02)
#define BUTTON_SEC_RESET_PORT			(PORTA)
#define BUTTON_SEC_RESET_BIT 			(0x04)

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
static BOOL g_isInputPortActive_Ary[ eINPUT_PORT_MAX ][ CHATTER_COUNT ];
static U08 g_u08InputPortActiveCount_Ary[ eINPUT_PORT_MAX ];

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
* OverView	: ポート初期化
* Parameter	: None
* Return	: None
*-----------------------------------------------------------------------------*/
void HW_PORT_Initialize( void )
{
	U08 i;

	/* ポートA */
	REG_WRITE_08( ANSEL, 0x00 );
	REG_WRITE_08( PORTA, 0x00 );
	REG_WRITE_08( TRISA, 0xC7 );

	/* ポートB */
	REG_RMW_08( OPTION_REG, 0xC0, 0x80 );
	REG_WRITE_08( ANSELH, 0x00 );
	REG_WRITE_08( WPUB, 0x00 );
	REG_WRITE_08( IOCB, 0x00 );
	REG_WRITE_08( PORTB, 0x00 );
	REG_WRITE_08( TRISB, 0x00 );

	/* ポートC */
	REG_WRITE_08( PORTC, 0x00 );
	REG_WRITE_08( TRISC, 0x1B );

	/* ポートE */
	/* DO NOTHING */

	/* 変数 */
	for( E_INPUT_PORT e = eINPUT_PORT_MIN; e < eINPUT_PORT_MAX; e++ ){
		for( i = 0; i < CHATTER_COUNT; i++ ){
			g_isInputPortActive_Ary[ e ][ i ] = FALSE;
		}
		g_u08InputPortActiveCount_Ary[ e ] = 0;
	}
}

/*------------------------------------------------------------------------------
* OverView	: 出力ポート設定
* Parameter	: port	: ポート
* 			: state	: TRUE:ON FALSE:OFF
* Return	: None
*-----------------------------------------------------------------------------*/
void HW_PORT_Set( CE_OUTPUT_PORT port, const BOOL state )
{
	if( state ){
		switch( port ){
		case eOUTPUT_PORT_PROC_FAIL:
			REG_SET_08( PROC_FAIL_PORT, PROC_FAIL_BIT );
			break;
		case eOUTPUT_PORT_STATUS_INT_TMR0:
			REG_SET_08( STATUS_INT_TMR0_PORT, STATUS_INT_TMR0_BIT );
			break;
		case eOUTPUT_PORT_STATUS_INT_TMR1:
			REG_SET_08( STATUS_INT_TMR1_PORT, STATUS_INT_TMR1_BIT );
			break;
		case eOUTPUT_PORT_STATUS_INT_SSP:
			REG_SET_08( STATUS_INT_SSP_PORT, STATUS_INT_SSP_BIT);
			break;
		case eOUTPUT_PORT_STATUS_SSP_SEND:
			REG_SET_08( STATUS_SSP_SEND_PORT, STATUS_SSP_SEND_BIT );
			break;
		case eOUTPUT_PORT_ERROR_SSP_STORE:
			REG_SET_08( ERROR_SSP_STORE_PORT, ERROR_SSP_STORE_BIT );
			break;
		case eOUTPUT_PORT_ERROR_SSP_SEND_START:
			REG_SET_08( ERROR_SSP_SEND_START_PORT, ERROR_SSP_SEND_START_BIT );
			break;
		case eOUTPUT_PORT_ERROR_SSP_SEND_FAIL:
			REG_SET_08( ERROR_SSP_SEND_FAIL_PORT, ERROR_SSP_SEND_FAIL_BIT );
			break;
		default:
			break;
		}
	}else{
		switch( port ){
		case eOUTPUT_PORT_PROC_FAIL:
			REG_CLR_08( PROC_FAIL_PORT, PROC_FAIL_BIT );
			break;
		case eOUTPUT_PORT_STATUS_INT_TMR0:
			REG_CLR_08( STATUS_INT_TMR0_PORT, STATUS_INT_TMR0_BIT );
			break;
		case eOUTPUT_PORT_STATUS_INT_TMR1:
			REG_CLR_08( STATUS_INT_TMR1_PORT, STATUS_INT_TMR1_BIT );
			break;
		case eOUTPUT_PORT_STATUS_INT_SSP:
			REG_CLR_08( STATUS_INT_SSP_PORT, STATUS_INT_SSP_BIT);
			break;
		case eOUTPUT_PORT_STATUS_SSP_SEND:
			REG_CLR_08( STATUS_SSP_SEND_PORT, STATUS_SSP_SEND_BIT );
			break;
		case eOUTPUT_PORT_ERROR_SSP_STORE:
			REG_CLR_08( ERROR_SSP_STORE_PORT, ERROR_SSP_STORE_BIT );
			break;
		case eOUTPUT_PORT_ERROR_SSP_SEND_START:
			REG_CLR_08( ERROR_SSP_SEND_START_PORT, ERROR_SSP_SEND_START_BIT );
			break;
		case eOUTPUT_PORT_ERROR_SSP_SEND_FAIL:
			REG_CLR_08( ERROR_SSP_SEND_FAIL_PORT, ERROR_SSP_SEND_FAIL_BIT );
			break;
		default:
			break;
		}
	}
}

/*------------------------------------------------------------------------------
* OverView	: 入力ポート更新
* Parameter	: None
* Return	: None
*-----------------------------------------------------------------------------*/
void HW_PORT_Update( void )
{
	U08 i;

	/* 入力ポート状態取得 */
	U08 inputs[ eINPUT_PORT_MAX ];
	inputs[ eINPUT_PORT_HOUR ] = (U08)( REG_READ_08( BUTTON_HOUR_PORT ) & BUTTON_HOUR_BIT );
	inputs[ eINPUT_PORT_MINUTE ] = (U08)( REG_READ_08( BUTTON_MINUTE_PORT ) & BUTTON_MINUTE_BIT );
	inputs[ eINPUT_PORT_SEC_RESET ] = (U08)( REG_READ_08( BUTTON_SEC_RESET_PORT ) & BUTTON_SEC_RESET_BIT );

	/* チャタリングチェック */
	for( E_INPUT_PORT e = eINPUT_PORT_MIN; e < eINPUT_PORT_MAX; e++ ){
		for( i = 0; i < CHATTER_COUNT - 1; i++ ){
			g_isInputPortActive_Ary[ e ][ i ] = g_isInputPortActive_Ary[ e ][ (U08)( i + 1 )];
		}
		if( inputs[ e ] != 0 ){
			g_isInputPortActive_Ary[ e ][ CHATTER_COUNT - 1 ] = TRUE;
		}else{
			g_isInputPortActive_Ary[ e ][ CHATTER_COUNT - 1 ] = FALSE;
		}
	}

	for( E_INPUT_PORT e = eINPUT_PORT_MIN; e < eINPUT_PORT_MAX; e++ ){
		/* 確定 */
		U08 count = 0;
		for( i = 0; i < CHATTER_COUNT; i++ ){
			if( g_isInputPortActive_Ary[ e ][ i ] ){
				count++;
			}
		}
		BOOL isPushed = FALSE;
		if( count == CHATTER_COUNT ){
			isPushed = TRUE;
		}

		/* 長押しチェック */
		if( !isPushed ){
			g_u08InputPortActiveCount_Ary[ e ] = 0;
		}else{
			if( g_u08InputPortActiveCount_Ary[ e ] < CONTINUE_COUNT ){
				g_u08InputPortActiveCount_Ary[ e ]++;
			}
		}
	}
}

/*------------------------------------------------------------------------------
* OverView	: 入力ポート取得
* Parameter	: port	: ポート
* Return	: TRUE:ON FALSE:OFF
*-----------------------------------------------------------------------------*/
BOOL HW_PORT_Get( CE_INPUT_PORT port )
{
	switch( g_u08InputPortActiveCount_Ary[ port ] ){
	case 0:
		return FALSE;
	case 1:
		return TRUE;
	case CONTINUE_COUNT:
		return TRUE;
	default:
		return FALSE;
	}

}

/*------------------------------------------------------------------------------
*	End Of File
*-----------------------------------------------------------------------------*/
