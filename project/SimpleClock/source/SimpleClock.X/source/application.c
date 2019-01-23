/*******************************************************************************
*	Author		|	Date		|	FileName
*-------------------------------------------------------------------------------
*	kenchaan	|	2019/01/23	|	application.c
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
static U08 g_u08DigitData_Ary[ eOUTPUT_PORT_DIGIT_MAX ] = { 0, 0, 0, 0 };
static E_OUTPUT_PORT_DIGIT g_eOutputDigit = eOUTPUT_PORT_DIGIT_MIN;

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
	/* スイッチ処理 */
	if( HW_PORT_IsActive( eINPUT_PORT_HOUR )){
		HW_TIM_EnableInterrupt( eTIMER_TYPE_TIME, FALSE );
		U32 count = ( HW_TIM_GetCount( eTIMER_TYPE_TIME ) + 3600 ) % 86400;
		HW_TIM_SetCount( eTIMER_TYPE_TIME, count );
		HW_TIM_EnableInterrupt( eTIMER_TYPE_TIME, TRUE );
	}

	if( HW_PORT_IsActive( eINPUT_PORT_MINUTE )){
		HW_TIM_EnableInterrupt( eTIMER_TYPE_TIME, FALSE );
		U32 count = ( HW_TIM_GetCount( eTIMER_TYPE_TIME ) + 60 ) % 86400;
		HW_TIM_SetCount( eTIMER_TYPE_TIME, count );
		HW_TIM_EnableInterrupt( eTIMER_TYPE_TIME, TRUE );
	}

	if( HW_PORT_IsActive( eINPUT_PORT_SECOND )){
		HW_TIM_EnableInterrupt( eTIMER_TYPE_TIME, FALSE );
		U32 count = ( (U32)( HW_TIM_GetCount( eTIMER_TYPE_TIME ) / 60 ) ) * 60;
		HW_TIM_SetCount( eTIMER_TYPE_TIME, count );
		HW_TIM_EnableInterrupt( eTIMER_TYPE_TIME, TRUE );
	}
}

/*------------------------------------------------------------------------------
* OverView	: フレーム処理
* Parameter	: None
* Return	: None
*-----------------------------------------------------------------------------*/
void APP_FrameMainProcess( void )
{
	U08 data;

	switch( g_eOutputDigit ){
	case eOUTPUT_PORT_DIGIT_HOUR_10:
		/* 時間更新 */
		{
			U32 count = HW_TIM_GetCount( eTIMER_TYPE_TIME );
			U08 h = (U08)( count / 3600 );
			U08 m = (U08)(( count % 3600 ) / 60 );
			// U08 s = (U08)( count % 60 );
			g_u08DigitData_Ary[ eOUTPUT_PORT_DIGIT_HOUR_10 ] = (U08)( h / 10 );
			g_u08DigitData_Ary[ eOUTPUT_PORT_DIGIT_HOUR_01 ] = (U08)( h % 10 );
			g_u08DigitData_Ary[ eOUTPUT_PORT_DIGIT_MINUTE_10 ] = (U08)( m / 10 );
			g_u08DigitData_Ary[ eOUTPUT_PORT_DIGIT_MINUTE_01 ] = (U08)( m % 10 );
		}

		data = g_u08DigitData_Ary[ eOUTPUT_PORT_DIGIT_HOUR_10 ];
		if( data == 0 ){
			data = 10;
		}
		break;

	case eOUTPUT_PORT_DIGIT_HOUR_01:
		data = g_u08DigitData_Ary[ eOUTPUT_PORT_DIGIT_HOUR_01 ];
		break;
	case eOUTPUT_PORT_DIGIT_MINUTE_10:
		data = g_u08DigitData_Ary[ eOUTPUT_PORT_DIGIT_MINUTE_10 ];
		break;
	case eOUTPUT_PORT_DIGIT_MINUTE_01:
		data = g_u08DigitData_Ary[ eOUTPUT_PORT_DIGIT_MINUTE_01 ];
		break;
	default:
		data = 0;
		break;
	}

	HW_PORT_SetSegData( g_eOutputDigit, data );

	g_eOutputDigit++;
	if( g_eOutputDigit >= eOUTPUT_PORT_DIGIT_MAX ){
		g_eOutputDigit = eOUTPUT_PORT_DIGIT_MIN;
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
