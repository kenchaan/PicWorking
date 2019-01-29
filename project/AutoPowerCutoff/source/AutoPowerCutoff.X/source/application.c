/*******************************************************************************
*	Author		|	Date		|	FileName
*-------------------------------------------------------------------------------
*	kenchaan	|	2019/01/29	|	application.c
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
#include "hardware_interrupt.h"
#include "hardware_port.h"
#include "hardware_timer.h"
#include "application.h"

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
static U08 g_u08DigitData_Ary[ eOUTPUT_PORT_DIGIT_MAX ];
static E_OUTPUT_PORT_DIGIT g_eOutputDigit = eOUTPUT_PORT_DIGIT_MIN;
static BOOL g_isCountingTime = FALSE;

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
	for( E_OUTPUT_PORT_DIGIT e = eOUTPUT_PORT_DIGIT_MIN; e < eOUTPUT_PORT_DIGIT_MAX; e++ ){
		g_u08DigitData_Ary[ e ] = 0;
	}

	/* POWER ON */
	HW_PORT_Set( eOUTPUT_PORT_POWER_CONTROL, TRUE );
}

/*------------------------------------------------------------------------------
* OverView	: フレーム事前処理
* Parameter	: None
* Return	: None
*-----------------------------------------------------------------------------*/
void APP_FramePreProcess( void )
{
	U32 count = HW_TIM_GetTimeCount();
	U08 h = (U08)(  (U32)( count / 2 ) / 3600 );
	U08 m = (U08)(( (U32)( count / 2 ) % 3600 ) / 60 );
	U08 s = (U08)(  (U32)( count / 2 ) % 60 );
	U08 ss = (U08)( count % 2 );

	/* スイッチ処理 */
	if ( !g_isCountingTime ){
		if( HW_PORT_IsActive( eINPUT_PORT_HOUR )){
			h++;
			if( h >= 99 ){
				h = 0;
			}
			s = 0;
			ss = 0;
		}

		if( HW_PORT_IsActive( eINPUT_PORT_MINUTE )){
			m++;
			if( m >= 60 ){
				m = 0;
			}
			s = 0;
			ss = 0;
		}

		if( HW_PORT_IsActive( eINPUT_PORT_START )){
			HW_TIM_EnableTimeCount( TRUE );
			g_isCountingTime = TRUE;
		}
	}

	if( HW_PORT_IsActive( eINPUT_PORT_CANCEL )){
		if( g_isCountingTime ){
			HW_TIM_EnableTimeCount( FALSE );
			g_isCountingTime = FALSE;
		}else{
			h = 0;
			m = 0;
			s = 0;
			ss = 0;
		}
	}

	U32 updated = ( (U32)h * 3600 + (U32)m * 60 + (U32)s ) * 2 + (U32)ss;
	if( updated != count ){
		HW_TIM_SetTimeCount( updated );
	}
}

/*------------------------------------------------------------------------------
* OverView	: フレーム処理
* Parameter	: None
* Return	: None
*-----------------------------------------------------------------------------*/
void APP_FrameMainProcess( void )
{
	if( g_eOutputDigit == eOUTPUT_PORT_DIGIT_MIN ){
		/* 時間更新 */
		if( HW_TIM_IsUpdatedTime() ){
			U32 count = HW_TIM_GetTimeCount();
			if( count == 0 && g_isCountingTime ){
				/* カウント終了 */
				HW_TIM_EnableTimeCount( FALSE );
				g_isCountingTime = FALSE;
				/* POWER OFF */
				HW_PORT_Set( eOUTPUT_PORT_POWER_CONTROL, FALSE );
				/* ここで電源がおちるはず、放置 */
			}

			U08 h = (U08)(  (U32)( count / 2 ) / 3600 );
			U08 m = (U08)(( (U32)( count / 2 ) % 3600 ) / 60 );
			// U08 s = (U08)(  (U32)( count / 2 ) % 60 );
			g_u08DigitData_Ary[ eOUTPUT_PORT_DIGIT_HOUR_10 ] = (U08)( h / 10 );
			g_u08DigitData_Ary[ eOUTPUT_PORT_DIGIT_HOUR_01 ] = (U08)( h % 10 );
			g_u08DigitData_Ary[ eOUTPUT_PORT_DIGIT_MINUTE_10 ] = (U08)( m / 10 );
			g_u08DigitData_Ary[ eOUTPUT_PORT_DIGIT_MINUTE_01 ] = (U08)( m % 10 );

			if( g_u08DigitData_Ary[ eOUTPUT_PORT_DIGIT_HOUR_10 ] == 0 ){
				g_u08DigitData_Ary[ eOUTPUT_PORT_DIGIT_HOUR_10 ] = 20;
			}
			g_u08DigitData_Ary[ eOUTPUT_PORT_DIGIT_HOUR_01 ] += 10;

			/* 状態点灯 */
			if( g_isCountingTime ){
				if(( count % 2 ) == 0 ){
					HW_PORT_Set( eOUTPUT_PORT_STATUS_COUNT, TRUE );
				}else{
					HW_PORT_Set( eOUTPUT_PORT_STATUS_COUNT, FALSE );
				}
			}else{
				HW_PORT_Set( eOUTPUT_PORT_STATUS_COUNT, TRUE );
			}
		}
	}

	HW_PORT_SetSegData( g_eOutputDigit, g_u08DigitData_Ary[ g_eOutputDigit ]);

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
