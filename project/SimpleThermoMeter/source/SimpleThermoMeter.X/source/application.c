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
#include "hardware_port.h"
#include "hardware_rom.h"
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
static BOOL g_isSettingTemp = FALSE;
static U08 g_u08TempThreshold = 60;

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

	g_u08TempThreshold = HW_ROM_Read( 0x00 );
    if( g_u08TempThreshold > 99 ){
        g_u08TempThreshold = 99;
        HW_ROM_Write( 0x00, g_u08TempThreshold );
    }
}

/*------------------------------------------------------------------------------
* OverView	: フレーム事前処理
* Parameter	: None
* Return	: None
*-----------------------------------------------------------------------------*/
void APP_FramePreProcess( void )
{
	/* 表示更新 */
	HW_PORT_SetSegData( g_eOutputDigit, g_u08DigitData_Ary[ g_eOutputDigit ]);

	g_eOutputDigit++;
	if( g_eOutputDigit >= eOUTPUT_PORT_DIGIT_MAX ){
		g_eOutputDigit = eOUTPUT_PORT_DIGIT_MIN;
	}

	/* スイッチ処理 */
	if( HW_PORT_IsActive( eINPUT_PORT_TEMP_SET )){
		if( g_isSettingTemp ){
			g_isSettingTemp = FALSE;
			HW_ROM_Write( 0x00, g_u08TempThreshold );
		}else{
			g_isSettingTemp = TRUE;
		}
	}

	if( HW_PORT_IsActive( eINPUT_PORT_TEMP_UP )){
		if( g_isSettingTemp ){
			if( g_u08TempThreshold < 99 ){
				g_u08TempThreshold++;
			}
		}else{
			g_isSettingTemp = TRUE;
		}
	}

	if( HW_PORT_IsActive( eINPUT_PORT_TEMP_DOWN )){
		if( g_isSettingTemp ){
			if( g_u08TempThreshold > 0 ){
				g_u08TempThreshold--;
			}
		}else{
			g_isSettingTemp = TRUE;
		}
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
		U16 data = HW_PORT_GetAnalogData( eINPUT_ANALOG_PORT_TEMP );
		F32 temp = 100.0 * ( (F32)data / 1024.0 );
		if( temp >= 100.0 ){
			temp = 99.9;
		}

		/* FAN制御 */
		if( !g_isSettingTemp ){
			if( g_u08TempThreshold == 0 ){
				/* 常にON */
				HW_PORT_Set( eOUTPUT_PORT_TEMP_CTRL, TRUE );
			}else if( g_u08TempThreshold >= 99 ){
				/* 常にOFF */
				HW_PORT_Set( eOUTPUT_PORT_TEMP_CTRL, FALSE );
			}else{
				if( (F32)( g_u08TempThreshold + 1 ) < temp ){
					HW_PORT_Set( eOUTPUT_PORT_TEMP_CTRL, TRUE );
				}else if( (F32)( g_u08TempThreshold - 1 ) < temp ){
					HW_PORT_Set( eOUTPUT_PORT_TEMP_CTRL, FALSE );
				}else{
					/* 変更なし */
					/* DO NOTHING */
				}
			}
		}

		/* 表示値更新 */
		if( g_isSettingTemp ){
			/* 設定温度 */
			g_u08DigitData_Ary[ eOUTPUT_PORT_DIGIT_INT_10 ] = (U08)( g_u08TempThreshold / 10 );
			g_u08DigitData_Ary[ eOUTPUT_PORT_DIGIT_INT_01 ] = (U08)( g_u08TempThreshold % 10 );
			g_u08DigitData_Ary[ eOUTPUT_PORT_DIGIT_DEC ] = 0;
		}else{
			/* 現在温度 */
			g_u08DigitData_Ary[ eOUTPUT_PORT_DIGIT_INT_10 ] = (U08)( (U32)temp / 10 );
			g_u08DigitData_Ary[ eOUTPUT_PORT_DIGIT_INT_01 ] = (U08)( (U32)temp % 10 );
			g_u08DigitData_Ary[ eOUTPUT_PORT_DIGIT_DEC ] = (U08)( (U32)( temp * 10 ) % 10 );
		}

		if ( g_u08DigitData_Ary[ eOUTPUT_PORT_DIGIT_INT_10 ] == 0 ){
			g_u08DigitData_Ary[ eOUTPUT_PORT_DIGIT_INT_10 ] += 20;
		}
		g_u08DigitData_Ary[ eOUTPUT_PORT_DIGIT_INT_01 ] += 10;
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
