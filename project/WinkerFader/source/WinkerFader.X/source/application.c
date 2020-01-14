/*******************************************************************************
*	Author		|	Date		|	FileName
*-------------------------------------------------------------------------------
*	kenchaan	|	2020/01/13	|	application.c
*-------------------------------------------------------------------------------
*	Description	|	アプリケーション処理
*-------------------------------------------------------------------------------
*	Copyright (c) 2020 kenchaan All Rights Reserved.
*******************************************************************************/

/*------------------------------------------------------------------------------
*	include
*-----------------------------------------------------------------------------*/
#include <xc.h>
#include "types.h"
#include "regaccess.h"
#include "hardware_ccp.h"
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
#define WINKER_AUTO_FLASH		(5)
#define FLASH_PATTERN_NUM		(100)

/*------------------------------------------------------------------------------
*	macro
*-----------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------
*	typedef
*-----------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------
*	enum
*-----------------------------------------------------------------------------*/
typedef enum tagE_FLASH_TYPE {
	eFLASH_TYPE_MIN = 0,
	eFLASH_TYPE_NONE = eFLASH_TYPE_MIN,
	eFLASH_TYPE_HAZARD,
	eFLASH_TYPE_WINKER_R,
	eFLASH_TYPE_WINKER_L,
	eFLASH_TYPE_MAX,
	eFLASH_TYPE_INVALID
} E_FLASH_TYPE;
typedef const E_FLASH_TYPE CE_FLASH_TYPE;

/*------------------------------------------------------------------------------
*	struct
*-----------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------
*	static variable
*-----------------------------------------------------------------------------*/
static E_FLASH_TYPE g_eFlashType = eFLASH_TYPE_NONE;
static U08 g_u08FlashFrameCount = 0;
static U08 g_u08FlashCount = 0;

/*------------------------------------------------------------------------------
*	static function prototype
*-----------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------
*	static const data
*-----------------------------------------------------------------------------*/
static const U08 g_cu08FlashPattern_Ary[ FLASH_PATTERN_NUM ] = {
	100, 100, 100, 100, 100, 100, 100, 100, 100, 100,
	100, 100, 100, 100, 100, 100, 100, 100, 100, 100,
	100, 100, 100, 100, 100, 100, 100, 100, 100, 100,
	100, 100, 100, 100, 100, 100, 100, 100, 100, 100,
	100, 100, 100, 100, 100, 100, 100, 100, 100, 100,
	96, 91, 87, 83, 79, 75, 72, 68, 65, 61,
	58, 55, 52, 49, 46, 43, 40, 37, 35, 33,
	30, 28, 26, 24, 22, 20, 18, 16, 15, 13,
	12, 11, 9, 8, 7, 6, 5, 4, 4, 3,
	2, 2, 1, 1, 1, 0, 0, 0, 0, 0
};

static const U08 g_u08HazardInitialPattern_Ary[ FLASH_PATTERN_NUM ] = {
	100, 100, 100, 100, 100, 100, 100, 100, 100, 100,
	100, 100, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 100, 100, 100, 100, 100, 100,
	100, 100, 100, 100, 100, 100, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 100, 100,
	100, 100, 100, 100, 100, 100, 100, 100, 100, 100,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

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
	/* 点滅状態更新 */
	if( g_eFlashType != eFLASH_TYPE_NONE ){
		/* 点滅中は状態を変えない */
		/* DO NOTHING */

	}else{
		/* スイッチ状態取得 */
		if( HW_PORT_IsActive( eINPUT_PORT_HAZARD )){
			g_eFlashType = eFLASH_TYPE_HAZARD;
		}else if( HW_PORT_IsActive( eINPUT_PORT_WINKER_R )){
			g_eFlashType = eFLASH_TYPE_WINKER_R;
		}else if( HW_PORT_IsActive( eINPUT_PORT_WINKER_L )){
			g_eFlashType = eFLASH_TYPE_WINKER_L;
		}else{
			g_eFlashType = eFLASH_TYPE_NONE;
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
	if( g_eFlashType == eFLASH_TYPE_NONE ){
		g_u08FlashFrameCount = 0;
		g_u08FlashCount = 0;
	}

	/* 点滅処理の停止/開始 */
	if( g_eFlashType == eFLASH_TYPE_NONE ){
		HW_CCP_EnableFlash( FALSE );
	}else{
		HW_CCP_EnableFlash( TRUE );
	}

	switch( g_eFlashType ){
	case eFLASH_TYPE_NONE:
		HW_PORT_Set( eOUTPUT_PORT_WINKER_R, FALSE );
		HW_PORT_Set( eOUTPUT_PORT_WINKER_L, FALSE );
		break;
	case eFLASH_TYPE_HAZARD:
		HW_PORT_Set( eOUTPUT_PORT_WINKER_R, TRUE );
		HW_PORT_Set( eOUTPUT_PORT_WINKER_L, TRUE );
		break;
	case eFLASH_TYPE_WINKER_R:
		HW_PORT_Set( eOUTPUT_PORT_WINKER_R, TRUE );
		HW_PORT_Set( eOUTPUT_PORT_WINKER_L, FALSE );
		break;
	case eFLASH_TYPE_WINKER_L:
		HW_PORT_Set( eOUTPUT_PORT_WINKER_R, FALSE );
		HW_PORT_Set( eOUTPUT_PORT_WINKER_L, TRUE );
		break;
	default:
		break;
	}

	/* 点滅出力 */
	if( g_eFlashType == eFLASH_TYPE_HAZARD ){
		if( g_u08FlashCount == 0 ){
			HW_CCP_SetDuty( g_u08HazardInitialPattern_Ary[ g_u08FlashFrameCount ]);
		}else{
			HW_CCP_SetDuty( g_cu08FlashPattern_Ary[ g_u08FlashFrameCount ]);
		}
	}else if(( g_eFlashType == eFLASH_TYPE_WINKER_R ) || ( g_eFlashType == eFLASH_TYPE_WINKER_L )){
		HW_CCP_SetDuty( g_cu08FlashPattern_Ary[ g_u08FlashFrameCount ]);
	}

	/* 状態更新 */
	g_u08FlashFrameCount++;
	if( g_u08FlashFrameCount >= FLASH_PATTERN_NUM ){
		E_FLASH_TYPE type = g_eFlashType;

		g_u08FlashFrameCount = 0;
		g_eFlashType = eFLASH_TYPE_NONE;

		if( g_u08FlashCount < 0xFF ){
			g_u08FlashCount++;
			if(( type == eFLASH_TYPE_WINKER_R ) || ( type == eFLASH_TYPE_WINKER_L )){
				if( g_u08FlashCount <= WINKER_AUTO_FLASH ){
					g_eFlashType = type;
				}
			}
		}
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
