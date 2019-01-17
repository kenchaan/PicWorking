/*******************************************************************************
*	Author		|	Date		|	FileName
*-------------------------------------------------------------------------------
*	ken_chaan	|	2019/01/07	|	PIC16F886_hardware_port.c
*-------------------------------------------------------------------------------
*	Description	|	[PIC16F886]ポート制御
*-------------------------------------------------------------------------------
*	Copyright (c) 2019 ken_chaan All Rights Reserved.
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
/* output port */
#define STATUS_INT_TMR0_PORT			(PORTB)
#define STATUS_INT_TMR0_BIT				(0x01)
#define STATUS_INT_SSP_PORT				(PORTB)
#define STATUS_INT_SSP_BIT				(0x02)
#define STATUS_SSP_RECV_PORT			(PORTB)
#define STATUS_SSP_RECV_BIT				(0x04)
#define ERROR_PROC_FAIL_PORT			(PORTB)
#define ERROR_PROC_FAIL_BIT				(0x08)
#define ERROR_SSP_RECV_1_PORT			(PORTB)
#define ERROR_SSP_RECV_1_BIT			(0x10)
#define ERROR_SSP_RECV_2_PORT			(PORTB)
#define ERROR_SSP_RECV_2_BIT			(0x20)

#define DIGIT_H10_PORT					(PORTA)
#define DIGIT_H10_BIT					(0x01)
#define DIGIT_H01_PORT					(PORTA)
#define DIGIT_H01_BIT					(0x02)
#define DIGIT_M10_PORT					(PORTA)
#define DIGIT_M10_BIT					(0x04)
#define DIGIT_M01_PORT					(PORTA)
#define DIGIT_M01_BIT					(0x08)

#define SEG_PORTA_MASK					(0x30)
#define SEG_PORTC_MASK					(0xE7)

#define SEG_DP_PORT						(PORTC)
#define SEG_DP_BIT						(0x80)

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
static const U08 g_cu08SegDataPortA_Ary[ 11 ] = {
	0x30,	/* 0 */
	0x20,	/* 1 */
	0x30,	/* 2 */
	0x30,	/* 3 */
	0x20,	/* 4 */
	0x10,	/* 5 */
	0x10,	/* 6 */
	0x30,	/* 7 */
	0x30,	/* 8 */
	0x30,	/* 9 */
	0x00	/*   */
};

static const U08 g_cu08SegDataPortC_Ary[ 11 ] = {
	0x27,	/* 0 */
	0x01,	/* 1 */
	0x46,	/* 2 */
	0x43,	/* 3 */
	0x61,	/* 4 */
	0x63,	/* 5 */
	0x67,	/* 6 */
	0x21,	/* 7 */
	0x67,	/* 8 */
	0x63,	/* 9 */
	0x00	/*   */
};

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
	/* ポートA */
	REG_WRITE_08( ANSEL, 0x00 );
	REG_WRITE_08( PORTA, 0x00 );
	REG_WRITE_08( TRISA, 0xC0 );

	/* ポートB */
	REG_RMW_08( OPTION_REG, 0xC0, 0x80 );
	REG_WRITE_08( ANSELH, 0x00 );
	REG_WRITE_08( WPUB, 0x00 );
	REG_WRITE_08( IOCB, 0x00 );
	REG_WRITE_08( PORTB, 0x00 );
	REG_WRITE_08( TRISB, 0x00 );

	/* ポートC */
	REG_WRITE_08( PORTC, 0x00 );
	REG_WRITE_08( TRISC, 0x18 );

	/* ポートE */
	/* DO NOTHING */
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
		case eOUTPUT_PORT_STATUS_INT_TMR0:
			REG_SET_08( STATUS_INT_TMR0_PORT, STATUS_INT_TMR0_BIT );
			break;
		case eOUTPUT_PORT_STATUS_INT_SSP:
			REG_SET_08( STATUS_INT_SSP_PORT, STATUS_INT_SSP_BIT);
			break;
		case eOUTPUT_PORT_STATUS_SSP_RECV:
			REG_SET_08( STATUS_SSP_RECV_PORT, STATUS_SSP_RECV_BIT );
			break;
		case eOUTPUT_PORT_ERROR_PROC_FAIL:
			REG_SET_08( ERROR_PROC_FAIL_PORT, ERROR_PROC_FAIL_BIT );
			break;
		case eOUTPUT_PORT_ERROR_SSP_RECV_1:
			REG_SET_08( ERROR_SSP_RECV_1_PORT, ERROR_SSP_RECV_1_BIT );
			break;
		case eOUTPUT_PORT_ERROR_SSP_RECV_2:
			REG_SET_08( ERROR_SSP_RECV_2_PORT, ERROR_SSP_RECV_2_BIT );
			break;
		default:
			break;
		}
	}else{
		switch( port ){
		case eOUTPUT_PORT_ERROR_PROC_FAIL:
			REG_CLR_08( ERROR_PROC_FAIL_PORT, ERROR_PROC_FAIL_BIT );
			break;
		case eOUTPUT_PORT_STATUS_INT_TMR0:
			REG_CLR_08( STATUS_INT_TMR0_PORT, STATUS_INT_TMR0_BIT );
			break;
		case eOUTPUT_PORT_STATUS_INT_SSP:
			REG_CLR_08( STATUS_INT_SSP_PORT, STATUS_INT_SSP_BIT);
			break;
		case eOUTPUT_PORT_STATUS_SSP_RECV:
			REG_CLR_08( STATUS_SSP_RECV_PORT, STATUS_SSP_RECV_BIT );
			break;
		case eOUTPUT_PORT_ERROR_SSP_RECV_1:
			REG_CLR_08( ERROR_SSP_RECV_1_PORT, ERROR_SSP_RECV_1_BIT );
			break;
		case eOUTPUT_PORT_ERROR_SSP_RECV_2:
			REG_CLR_08( ERROR_SSP_RECV_2_PORT, ERROR_SSP_RECV_2_BIT );
			break;
		default:
			break;
		}
	}
}

/*------------------------------------------------------------------------------
* OverView	: 出力ポートセグデータ設定
* Parameter	: digit	: 桁
* 			: data	: セグデータ(0(0)～9(9),10(空白))
* Return	: None
*-----------------------------------------------------------------------------*/
void HW_PORT_SetSegData( CE_OUTPUT_PORT_DIGIT digit, const U08 data )
{
	if( data > 10 ){
		return;
	}

	/* 全桁消灯 */
	REG_CLR_08( DIGIT_H10_PORT, DIGIT_H10_BIT );
	REG_CLR_08( DIGIT_H01_PORT, DIGIT_H01_BIT );
	REG_CLR_08( DIGIT_M10_PORT, DIGIT_M10_BIT );
	REG_CLR_08( DIGIT_M01_PORT, DIGIT_M01_BIT );

	/* 出力 */
	REG_RMW_08( PORTA, SEG_PORTA_MASK, g_cu08SegDataPortA_Ary[ data ]);
	REG_RMW_08( PORTC, SEG_PORTC_MASK, g_cu08SegDataPortC_Ary[ data ]);
	if( digit == eOUTPUT_PORT_DIGIT_H01 ){
		REG_SET_08( SEG_DP_PORT, SEG_DP_BIT );
	}

	/* 指定桁点灯 */
	switch( digit ){
	case eOUTPUT_PORT_DIGIT_H10:
		REG_SET_08( DIGIT_H10_PORT, DIGIT_H10_BIT );
		REG_CLR_08( DIGIT_H01_PORT, DIGIT_H01_BIT );
		REG_CLR_08( DIGIT_M10_PORT, DIGIT_M10_BIT );
		REG_CLR_08( DIGIT_M01_PORT, DIGIT_M01_BIT );
		break;
	case eOUTPUT_PORT_DIGIT_H01:
		REG_CLR_08( DIGIT_H10_PORT, DIGIT_H10_BIT );
		REG_SET_08( DIGIT_H01_PORT, DIGIT_H01_BIT );
		REG_CLR_08( DIGIT_M10_PORT, DIGIT_M10_BIT );
		REG_CLR_08( DIGIT_M01_PORT, DIGIT_M01_BIT );
		break;
	case eOUTPUT_PORT_DIGIT_M10:
		REG_CLR_08( DIGIT_H10_PORT, DIGIT_H10_BIT );
		REG_CLR_08( DIGIT_H01_PORT, DIGIT_H01_BIT );
		REG_SET_08( DIGIT_M10_PORT, DIGIT_M10_BIT );
		REG_CLR_08( DIGIT_M01_PORT, DIGIT_M01_BIT );
		break;
	case eOUTPUT_PORT_DIGIT_M01:
		REG_CLR_08( DIGIT_H10_PORT, DIGIT_H10_BIT );
		REG_CLR_08( DIGIT_H01_PORT, DIGIT_H01_BIT );
		REG_CLR_08( DIGIT_M10_PORT, DIGIT_M10_BIT );
		REG_SET_08( DIGIT_M01_PORT, DIGIT_M01_BIT );
		break;
	case eOUTPUT_PORT_DIGIT_NONE:
		REG_CLR_08( DIGIT_H10_PORT, DIGIT_H10_BIT );
		REG_CLR_08( DIGIT_H01_PORT, DIGIT_H01_BIT );
		REG_CLR_08( DIGIT_M10_PORT, DIGIT_M10_BIT );
		REG_CLR_08( DIGIT_M01_PORT, DIGIT_M01_BIT );
		break;
	default:
		return;
	}
}


/*------------------------------------------------------------------------------
*	End Of File
*-----------------------------------------------------------------------------*/
