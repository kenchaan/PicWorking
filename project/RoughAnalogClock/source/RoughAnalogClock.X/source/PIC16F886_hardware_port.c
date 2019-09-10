/*******************************************************************************
*	Author		|	Date		|	FileName
*-------------------------------------------------------------------------------
*	kenchaan	|	2019/09/09	|	PIC16F886_hardware_port.c
*-------------------------------------------------------------------------------
*	Description	|	[PIC16F886]ポート制御
*-------------------------------------------------------------------------------
*	Copyright (c) 2019 kenchaan All Rights Reserved.
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
#define SW_SELECT_PORT			(PORTA)
#define SW_SELECT_BIT			(0x04)

#define ERROR_PROC_FAIL_PORT	(PORTC)
#define ERROR_PROC_FAIL_BIT		(0x04)

#define DIGIT_0_PORT			(PORTC)
#define DIGIT_0_BIT				(0x10)
#define DIGIT_1_PORT			(PORTC)
#define DIGIT_1_BIT				(0x20)
#define DIGIT_2_PORT			(PORTC)
#define DIGIT_2_BIT				(0x40)
#define DIGIT_3_PORT			(PORTC)
#define DIGIT_3_BIT				(0x80)

#define SEG_DATA_PORT			(PORTB)

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
	eOUTPUT_PORT_DIGIT_0 = eOUTPUT_PORT_DIGIT_MIN,
	eOUTPUT_PORT_DIGIT_1,
	eOUTPUT_PORT_DIGIT_2,
	eOUTPUT_PORT_DIGIT_3,
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

static E_CLOCK_TYPE g_eClockType = eCLOCK_TYPE_ANALOG;
static U08 g_u08Hour_Ary[ 2 ]   = { 0, 0 };
static U08 g_u08Minute_Ary[ 2 ] = { 0, 0 };
static U08 g_u08Second_Ary[ 2 ] = { 0, 0 };

static E_OUTPUT_PORT_DIGIT g_eCurrentOutputDigit = eOUTPUT_PORT_DIGIT_MIN;

/*------------------------------------------------------------------------------
*	static function prototype
*-----------------------------------------------------------------------------*/
static void update_output( void );
static U08 get_output_data_analog( void );
static U08 get_output_data_digital( void );
static void update_input( void );

/*------------------------------------------------------------------------------
*	static const data
*-----------------------------------------------------------------------------*/
static const U08 g_cu08SegDataAnalog_Ary[ 6 ] = {
	0x01,	/* 0,  6 */
	0x02,	/* 1,  7 */
	0x04,	/* 2,  8 */
	0x08,	/* 3,  9 */
	0x10,	/* 4, 10 */
	0x20	/* 5, 11 */
};

static const U08 g_cu08SegDataDigital_Ary[ 20 ] = {
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
	0xBF,	/* 0. */
	0x86,	/* 1. */
	0xDB,	/* 2. */
	0xCF,	/* 3. */
	0xE6,	/* 4. */
	0xED,	/* 5. */
	0xFD,	/* 6. */
	0xA7,	/* 7. */
	0xFF,	/* 8. */
	0xEF	/* 9. */
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
}

/*------------------------------------------------------------------------------
* OverView	: ポート状態更新
* Parameter	: None
* Return	: None
*-----------------------------------------------------------------------------*/
void HW_PORT_Update( void )
{
	update_output();
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
	switch( port ){
	case eINPUT_PORT_HOUR:
	case eINPUT_PORT_MINUTE:
		if( g_u08PortActiveCount_Ary[ port ] == CHATTER_TH ){
			return TRUE;
		}else if( g_u08PortActiveCount_Ary[ port ] >= CONTINUE_TH ){
			g_u08PortActiveCount_Ary[ port ] -= CONTINUE_INTERVAL;
			return TRUE;
		}else{
			return FALSE;
		}

	case eINPUT_PORT_SELECT:
		if( g_u08PortActiveCount_Ary[ port ] >= CHATTER_TH ){
			return TRUE;
		}else{
			return FALSE;
		}

	default:
		return FALSE;
	}
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
* OverView	: 時計種別設定
* Parameter	: type	: 時計種別
* Return	: None
*-----------------------------------------------------------------------------*/
void HW_PORT_SetClockType( CE_CLOCK_TYPE type )
{
	g_eClockType = type;
}

/*------------------------------------------------------------------------------
* OverView	: 時間設定
* Parameter	: hour		: 時
* 			: minute	: 分
* 			: second	: 秒
* Return	: None
*-----------------------------------------------------------------------------*/
void HW_PORT_SetTime( const U08 hour, const U08 minute, const U08 second )
{
	g_u08Hour_Ary[ 1 ] = hour;
	g_u08Minute_Ary[ 1 ] = minute;
	g_u08Second_Ary[ 1 ] = second;
}

/*------------------------------------------------------------------------------
* OverView	: ポート出力更新
* Parameter	: None
* Return	: None
*-----------------------------------------------------------------------------*/
static void update_output( void )
{
	if( g_eCurrentOutputDigit == eOUTPUT_PORT_DIGIT_MIN ){
		g_u08Hour_Ary[ 0 ] = g_u08Hour_Ary[ 1 ];
		g_u08Minute_Ary[ 0 ] = g_u08Minute_Ary[ 1 ];
		g_u08Second_Ary[ 0 ] = g_u08Second_Ary[ 1 ];
	}

	/* 消灯 */
	REG_CLR_08( DIGIT_0_PORT, DIGIT_0_BIT );
	REG_CLR_08( DIGIT_1_PORT, DIGIT_1_BIT );
	REG_CLR_08( DIGIT_2_PORT, DIGIT_2_BIT );
	REG_CLR_08( DIGIT_3_PORT, DIGIT_3_BIT );

	/* データセット */
	U08 data = 0x00;
	switch( g_eClockType ){
	case eCLOCK_TYPE_ANALOG:
		data = get_output_data_analog();
		break;
	case eCLOCK_TYPE_DIGITAL:
		data = get_output_data_digital();
		break;
	default:
		break;
	}
	REG_WRITE_08( SEG_DATA_PORT, data );

	/* 点灯 */
	switch( g_eCurrentOutputDigit ){
	case eOUTPUT_PORT_DIGIT_0:
		REG_SET_08( DIGIT_0_PORT, DIGIT_0_BIT );
		break;
	case eOUTPUT_PORT_DIGIT_1:
		REG_SET_08( DIGIT_1_PORT, DIGIT_1_BIT );
		break;
	case eOUTPUT_PORT_DIGIT_2:
		REG_SET_08( DIGIT_2_PORT, DIGIT_2_BIT );
		break;
	case eOUTPUT_PORT_DIGIT_3:
		REG_SET_08( DIGIT_3_PORT, DIGIT_3_BIT );
		break;
	default:
		break;
	}

	g_eCurrentOutputDigit++;
	if( g_eCurrentOutputDigit >= eOUTPUT_PORT_DIGIT_MAX ){
		g_eCurrentOutputDigit = eOUTPUT_PORT_DIGIT_MIN;
	}
}

/*------------------------------------------------------------------------------
* OverView	: アナログ用出力データ取得
* Parameter	: None
* Return	: 出力データ
*-----------------------------------------------------------------------------*/
static U08 get_output_data_analog( void )
{
	U32 count =	(U32)g_u08Hour_Ary[ 0 ] * 3600 +
				(U32)g_u08Minute_Ary[ 0 ] * 60 +
				(U32)g_u08Second_Ary[ 0 ];
	if( count < 150 ){
		count += 43200;
	}
	count -= 150;

	U08 hPos = (U08)( count / 3600 );
	U08 mPos = (U08)( (U08)(( count % 3600 ) / 60 ) / 5 );

	switch( g_eCurrentOutputDigit ){
	case eOUTPUT_PORT_DIGIT_0:
	case eOUTPUT_PORT_DIGIT_1:
		return (U08)(	g_cu08SegDataAnalog_Ary[ (U08)( hPos % 6 )] +
						g_cu08SegDataAnalog_Ary[ (U08)( mPos % 6 )]);
	case eOUTPUT_PORT_DIGIT_2:
	case eOUTPUT_PORT_DIGIT_3:
		return g_cu08SegDataAnalog_Ary[ (U08)( mPos % 6 )];
	default:
		return 0x00;
	}
}

/*------------------------------------------------------------------------------
* OverView	: デジタル用出力データ取得
* Parameter	: None
* Return	: 出力データ
*-----------------------------------------------------------------------------*/
static U08 get_output_data_digital( void )
{
	switch( g_eCurrentOutputDigit ){
	case eOUTPUT_PORT_DIGIT_0:
		return g_cu08SegDataDigital_Ary[ (U08)( g_u08Hour_Ary[ 0 ] / 10 )];
	case eOUTPUT_PORT_DIGIT_1:
		return g_cu08SegDataDigital_Ary[ (U08)(( g_u08Hour_Ary[ 0 ] % 10 ) + 10 )];
	case eOUTPUT_PORT_DIGIT_2:
		return g_cu08SegDataDigital_Ary[ (U08)( g_u08Minute_Ary[ 0 ] / 10 )];
	case eOUTPUT_PORT_DIGIT_3:
		return g_cu08SegDataDigital_Ary[ (U08)( g_u08Minute_Ary[ 0 ] % 10 )];
	default:
		return 0x00;
	}
}

/*------------------------------------------------------------------------------
* OverView	: ポート入力更新
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

	if( REG_READ_08( SW_SELECT_PORT ) & SW_SELECT_BIT ){
		if( g_u08PortActiveCount_Ary[ eINPUT_PORT_SELECT ] < 0xFF ){
			g_u08PortActiveCount_Ary[ eINPUT_PORT_SELECT ]++;
		}
	}else{
		g_u08PortActiveCount_Ary[ eINPUT_PORT_SELECT ] = 0;
	}
}


/*------------------------------------------------------------------------------
*	End Of File
*-----------------------------------------------------------------------------*/
