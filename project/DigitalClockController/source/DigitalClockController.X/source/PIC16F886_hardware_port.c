/*******************************************************************************
*	Author		|	Date		|	FileName
*-------------------------------------------------------------------------------
*	kenchaan	|	2020/05/13	|	PIC16F886_hardware_port.c
*-------------------------------------------------------------------------------
*	Description	|	[PIC16F886]ポート制御
*-------------------------------------------------------------------------------
*	Copyright (c) 2020 kenchaan All Rights Reserved.
*******************************************************************************/

/*------------------------------------------------------------------------------
*	include
*-----------------------------------------------------------------------------*/
#include <xc.h>
#include "types.h"
#include "regaccess.h"
#include "hardware.h"
#include "hardware_port.h"

/*------------------------------------------------------------------------------
*	pragma
*-----------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------
*	define
*-----------------------------------------------------------------------------*/
#define CHATTER_TH				(3)
#define CONTINUE_TH				(200)
#define CONTINUE_INTERVAL		(10)

#define SW_HOUR_PORT			(PORTA)
#define SW_HOUR_BIT				(0x01)
#define SW_MINUTE_PORT			(PORTA)
#define SW_MINUTE_BIT			(0x02)
#define SW_SECOND_RST_PORT		(PORTA)
#define SW_SECOND_RST_BIT		(0x04)

#define ERROR_PROC_FAIL_PORT	(PORTA)
#define ERROR_PROC_FAIL_BIT		(0x20)

#define DIGIT_H10_PORT			(PORTC)
#define DIGIT_H10_BIT			(0x04)
#define DIGIT_H01_PORT			(PORTC)
#define DIGIT_H01_BIT			(0x08)
#define DIGIT_M10_PORT			(PORTC)
#define DIGIT_M10_BIT			(0x10)
#define DIGIT_M01_PORT			(PORTC)
#define DIGIT_M01_BIT			(0x20)

#define SEG_DATA_PORT			(PORTB)

#define COLON_DATA				(0x80)

/*------------------------------------------------------------------------------
*	macro
*-----------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------
*	typedef
*-----------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------
*	enum
*-----------------------------------------------------------------------------*/
typedef enum tagE_OUTPUT_PORT_DIGIT {
	eOUTPUT_PORT_DIGIT_MIN = 0,
	eOUTPUT_PORT_DIGIT_HOUR_10 = eOUTPUT_PORT_DIGIT_MIN,
	eOUTPUT_PORT_DIGIT_HOUR_01,
	eOUTPUT_PORT_DIGIT_MINUTE_10,
	eOUTPUT_PORT_DIGIT_MINUTE_01,
	eOUTPUT_PORT_DIGIT_MAX,
	eOUTPUT_PORT_DIGIT_NONE,
	eOUTPUT_PORT_DIGIT_INVALID
} E_OUTPUT_PORT_DIGIT;
typedef const E_OUTPUT_PORT_DIGIT CE_OUTPUT_PORT_DIGIT;

/*------------------------------------------------------------------------------
*	struct
*-----------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------
*	static variable
*-----------------------------------------------------------------------------*/
static U08 g_u08PortActiveCount_Ary[ eINPUT_PORT_MAX ];
static U08 g_u08DigitData_Ary[ eOUTPUT_PORT_DIGIT_MAX ];
static E_OUTPUT_PORT_DIGIT g_eOutputDigit = eOUTPUT_PORT_DIGIT_MIN;

/*------------------------------------------------------------------------------
*	static function prototype
*-----------------------------------------------------------------------------*/
static void update_output_seg_data( void );
static void update_input( void );

/*------------------------------------------------------------------------------
*	static const data
*-----------------------------------------------------------------------------*/
static const U08 g_cu08SegData_Ary[ 11 ] = {
	0x3F,	/* 0  */
	0x06,	/* 1  */
	0x5B,	/* 2  */
	0x4F,	/* 3  */
	0x66,	/* 4  */
	0x6D,	/* 5  */
	0x7D,	/* 6  */
	0x27,	/* 7  */
	0x7F,	/* 8  */
	0x6F,	/* 9  */
	0x00	/*    */
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
	REG_WRITE_08( TRISC, 0x03 );

	/* ポートE */
	/* DO NOTHING */

	for( E_INPUT_PORT e = eINPUT_PORT_MIN; e < eINPUT_PORT_MAX; e++ ){
		g_u08PortActiveCount_Ary[ e ] = 0;
	}
	for( E_OUTPUT_PORT_DIGIT e = eOUTPUT_PORT_DIGIT_MIN; e < eOUTPUT_PORT_DIGIT_MAX; e++ ){
		g_u08DigitData_Ary[ e ] = 0;
	}
}

/*------------------------------------------------------------------------------
* OverView	: ポート状態更新
* Parameter	: None
* Return	: None
*-----------------------------------------------------------------------------*/
void HW_PORT_Update( void )
{
	update_output_seg_data();
	update_input();
}

/*------------------------------------------------------------------------------
* OverView	: ポート状態取得
* Parameter	: port	: 入力ポート
* Return	: TRUE	: Active
* 			: FALSE	: Not Active
*-----------------------------------------------------------------------------*/
BOOL HW_PORT_IsActive( CE_INPUT_PORT port )
{
	if( g_u08PortActiveCount_Ary[ port ] == CHATTER_TH ){
		return TRUE;
	}else if( g_u08PortActiveCount_Ary[ port ] >= CONTINUE_TH ){
		g_u08PortActiveCount_Ary[ port ] -= CONTINUE_INTERVAL;
		return TRUE;
	}

	return FALSE;
}

/*------------------------------------------------------------------------------
* OverView	: ポート出力
* Parameter	: port		: 出力ポート
* 			: isActive	: TRUE:Active FALSE:NotActive
* Return	: None
*-----------------------------------------------------------------------------*/
void HW_PORT_Set( CE_OUTPUT_PORT port, const BOOL isActive )
{
	if( isActive ){
		switch( port ){
		case eOUTPUT_PORT_ERROR_PROC_FAIL:
			REG_SET_08( ERROR_PROC_FAIL_PORT, ERROR_PROC_FAIL_BIT );
			break;
		default:
			break;
		}
	}else{
		switch( port ){
		case eOUTPUT_PORT_ERROR_PROC_FAIL:
			REG_CLR_08( ERROR_PROC_FAIL_PORT, ERROR_PROC_FAIL_BIT );
			break;
		default:
			break;
		}
	}
}

/*------------------------------------------------------------------------------
* OverView	: セグメントデータ設定
* Parameter	: data	: 出力データ
* Return	: None
*-----------------------------------------------------------------------------*/
void HW_PORT_SetSegData( const U08 data[] )
{
	g_u08DigitData_Ary[ eOUTPUT_PORT_DIGIT_HOUR_10 ] = data[ 0 ];
	g_u08DigitData_Ary[ eOUTPUT_PORT_DIGIT_HOUR_01 ] = data[ 1 ];
	g_u08DigitData_Ary[ eOUTPUT_PORT_DIGIT_MINUTE_10 ] = data[ 2 ];
	g_u08DigitData_Ary[ eOUTPUT_PORT_DIGIT_MINUTE_01 ] = data[ 3 ];
}

/*------------------------------------------------------------------------------
* OverView	: セグメントデータ出力更新
* Parameter	: None
* Return	: None
*-----------------------------------------------------------------------------*/
static void update_output_seg_data( void )
{
	/* 消灯 */
	REG_CLR_08( DIGIT_H10_PORT, DIGIT_H10_BIT );
	REG_CLR_08( DIGIT_H01_PORT, DIGIT_H01_BIT );
	REG_CLR_08( DIGIT_M10_PORT, DIGIT_M10_BIT );
	REG_CLR_08( DIGIT_M01_PORT, DIGIT_M01_BIT );

	/* データセット */
	U08 data;
	if( eOUTPUT_PORT_DIGIT_HOUR_01 == g_eOutputDigit ){
		data = (U08)( g_cu08SegData_Ary[ g_u08DigitData_Ary[ g_eOutputDigit ]] | COLON_DATA );
	}else{
		data = g_cu08SegData_Ary[ g_u08DigitData_Ary[ g_eOutputDigit ]];
	}
	REG_WRITE_08( SEG_DATA_PORT, data );

	/* 点灯 */
	switch( g_eOutputDigit ){
	case eOUTPUT_PORT_DIGIT_HOUR_10:
		REG_SET_08( DIGIT_H10_PORT, DIGIT_H10_BIT );
		break;
	case eOUTPUT_PORT_DIGIT_HOUR_01:
		REG_SET_08( DIGIT_H01_PORT, DIGIT_H01_BIT );
		break;
	case eOUTPUT_PORT_DIGIT_MINUTE_10:
		REG_SET_08( DIGIT_M10_PORT, DIGIT_M10_BIT );
		break;
	case eOUTPUT_PORT_DIGIT_MINUTE_01:
		REG_SET_08( DIGIT_M01_PORT, DIGIT_M01_BIT );
		break;
	default:
		break;
	}

	g_eOutputDigit++;
	if( g_eOutputDigit >= eOUTPUT_PORT_DIGIT_MAX ){
		g_eOutputDigit = eOUTPUT_PORT_DIGIT_MIN;
	}
}

/*------------------------------------------------------------------------------
* OverView	: 入力データ更新
* Parameter	: None
* Return	: None
*-----------------------------------------------------------------------------*/
static void update_input( void )
{
	if( REG_READ_08( SW_HOUR_PORT ) & SW_HOUR_BIT ){
		if( g_u08PortActiveCount_Ary[ eINPUT_PORT_HOUR ] < 0xFF ){
			g_u08PortActiveCount_Ary[ eINPUT_PORT_HOUR ]++;
		}
	}else{
		g_u08PortActiveCount_Ary[ eINPUT_PORT_HOUR ] = 0;
	}

	if( REG_READ_08( SW_MINUTE_PORT ) & SW_MINUTE_BIT ){
		if( g_u08PortActiveCount_Ary[ eINPUT_PORT_MINUTE ] < 0xFF ){
			g_u08PortActiveCount_Ary[ eINPUT_PORT_MINUTE ]++;
		}
	}else{
		g_u08PortActiveCount_Ary[ eINPUT_PORT_MINUTE ] = 0;
	}

	if( REG_READ_08( SW_SECOND_RST_PORT ) & SW_SECOND_RST_BIT ){
		if( g_u08PortActiveCount_Ary[ eINPUT_PORT_SECOND_RST ] < 0xFF ){
			g_u08PortActiveCount_Ary[ eINPUT_PORT_SECOND_RST ]++;
		}
	}else{
		g_u08PortActiveCount_Ary[ eINPUT_PORT_SECOND_RST ] = 0;
	}
}


/*------------------------------------------------------------------------------
*	End Of File
*-----------------------------------------------------------------------------*/
