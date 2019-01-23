/*******************************************************************************
*	Author		|	Date		|	FileName
*-------------------------------------------------------------------------------
*	kenchaan	|	2019/01/22	|	application.c
*-------------------------------------------------------------------------------
*	Description	|	アプリケーション処理
*-------------------------------------------------------------------------------
*	Copyright (c) 2019 kenchaan All Rights Reserved.
*******************************************************************************/

/*------------------------------------------------------------------------------
*	include
*-----------------------------------------------------------------------------*/
#include <xc.h>
#include "types.h"
#include "regaccess.h"
#include "application.h"
#include "hardware_port.h"
#include "hardware_timer.h"

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
static U08 g_u08FrameCount = 0;
static U08 g_u08State = 0;

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
* OverView	: アプリケーション初期化
* Parameter	: None
* Return	: None
*-----------------------------------------------------------------------------*/
void APP_Initialize( void )
{
	/* DO NOTHING */
}

/*------------------------------------------------------------------------------
* OverView	: フレーム事前処理
* Parameter	: None
* Return	: None
*-----------------------------------------------------------------------------*/
void APP_FramePreProcess( void )
{
	/* DO NOTHING */
}

/*------------------------------------------------------------------------------
* OverView	: フレーム処理
* Parameter	: None
* Return	: None
*-----------------------------------------------------------------------------*/
void APP_FrameMainProcess( void )
{
	g_u08FrameCount++;
	if( g_u08FrameCount >= 10 ){
		g_u08FrameCount = 0;

		g_u08State++;
		if( g_u08State >= 40 ){
			g_u08State = 0;
		}
		REG_WRITE_08( PORTA, 0x00 );
		REG_WRITE_08( PORTB, 0x00 );
		REG_WRITE_08( PORTC, 0x00 );
	}

	switch( g_u08State ){
	case 0:
		REG_SET_08( PORTB, 0x01 );
		break;
	case 1:
		REG_SET_08( PORTB, 0x03 );
		break;
	case 2:
		REG_SET_08( PORTB, 0x07 );
		break;
	case 3:
		REG_SET_08( PORTB, 0x0F );
		break;
	case 4:
		REG_SET_08( PORTB, 0x1F );
		break;
	case 5:
		REG_SET_08( PORTB, 0x3F );
		break;
	case 6:
		REG_SET_08( PORTB, 0x7F );
		break;
	case 7:
		REG_SET_08( PORTB, 0xFF );
		break;
	case 8:
		REG_SET_08( PORTA, 0x01 );
		REG_SET_08( PORTC, 0x01 );
		break;
	case 9:
		REG_SET_08( PORTA, 0x01 );
		REG_SET_08( PORTC, 0x03 );
		break;
	case 10:
		REG_SET_08( PORTA, 0x01 );
		REG_SET_08( PORTC, 0x07 );
		break;
	case 11:
		REG_SET_08( PORTA, 0x01 );
		REG_SET_08( PORTC, 0x0F );
		break;
	case 12:
		REG_SET_08( PORTA, 0x01 );
		REG_SET_08( PORTC, 0x1F );
		break;
	case 13:
		REG_SET_08( PORTA, 0x01 );
		REG_SET_08( PORTC, 0x3F );
		break;
	case 14:
		REG_SET_08( PORTA, 0x01 );
		REG_SET_08( PORTC, 0x7F );
		break;
	case 15:
		REG_SET_08( PORTA, 0x01 );
		REG_SET_08( PORTC, 0xFF );
		break;
	case 16:
		REG_SET_08( PORTA, 0x02 );
		REG_SET_08( PORTC, 0x01 );
		break;
	case 17:
		REG_SET_08( PORTA, 0x02 );
		REG_SET_08( PORTC, 0x03 );
		break;
	case 18:
		REG_SET_08( PORTA, 0x02 );
		REG_SET_08( PORTC, 0x07 );
		break;
	case 19:
		REG_SET_08( PORTA, 0x02 );
		REG_SET_08( PORTC, 0x0F );
		break;
	case 20:
		REG_SET_08( PORTA, 0x02 );
		REG_SET_08( PORTC, 0x1F );
		break;
	case 21:
		REG_SET_08( PORTA, 0x02 );
		REG_SET_08( PORTC, 0x3F );
		break;
	case 22:
		REG_SET_08( PORTA, 0x02 );
		REG_SET_08( PORTC, 0x7F );
		break;
	case 23:
		REG_SET_08( PORTA, 0x02 );
		REG_SET_08( PORTC, 0xFF );
		break;
	case 24:
		REG_SET_08( PORTA, 0x04 );
		REG_SET_08( PORTC, 0x01 );
		break;
	case 25:
		REG_SET_08( PORTA, 0x04 );
		REG_SET_08( PORTC, 0x03 );
		break;
	case 26:
		REG_SET_08( PORTA, 0x04 );
		REG_SET_08( PORTC, 0x07 );
		break;
	case 27:
		REG_SET_08( PORTA, 0x04 );
		REG_SET_08( PORTC, 0x0F );
		break;
	case 28:
		REG_SET_08( PORTA, 0x04 );
		REG_SET_08( PORTC, 0x1F );
		break;
	case 29:
		REG_SET_08( PORTA, 0x04 );
		REG_SET_08( PORTC, 0x3F );
		break;
	case 30:
		REG_SET_08( PORTA, 0x04 );
		REG_SET_08( PORTC, 0x7F );
		break;
	case 31:
		REG_SET_08( PORTA, 0x04 );
		REG_SET_08( PORTC, 0xFF );
		break;
	case 32:
		REG_SET_08( PORTA, 0x08 );
		REG_SET_08( PORTC, 0x01 );
		break;
	case 33:
		REG_SET_08( PORTA, 0x08 );
		REG_SET_08( PORTC, 0x03 );
		break;
	case 34:
		REG_SET_08( PORTA, 0x08 );
		REG_SET_08( PORTC, 0x07 );
		break;
	case 35:
		REG_SET_08( PORTA, 0x08 );
		REG_SET_08( PORTC, 0x0F );
		break;
	case 36:
		REG_SET_08( PORTA, 0x08 );
		REG_SET_08( PORTC, 0x1F );
		break;
	case 37:
		REG_SET_08( PORTA, 0x08 );
		REG_SET_08( PORTC, 0x3F );
		break;
	case 38:
		REG_SET_08( PORTA, 0x08 );
		REG_SET_08( PORTC, 0x7F );
		break;
	case 39:
		REG_SET_08( PORTA, 0x08 );
		REG_SET_08( PORTC, 0xFF );
		break;
	default:
		g_u08State = 0;
		break;
	}
}

/*------------------------------------------------------------------------------
* OverView	: フレーム事後処理
* Parameter	: None
* Return	: None
*-----------------------------------------------------------------------------*/
void APP_FramePostProcess( void )
{
	/* DO NOTHING */
}


/*------------------------------------------------------------------------------
*	End Of File
*-----------------------------------------------------------------------------*/
