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
	100, 98, 96, 94, 91, 89, 87, 85, 83, 81,
	79, 77, 75, 74, 72, 70, 68, 66, 65, 63,
	61, 60, 58, 56, 55, 53, 52, 50, 49, 47,
	46, 44, 43, 41, 40, 39, 37, 36, 35, 34,
	33, 31, 30, 29, 28, 27, 26, 25, 24, 23,
	22, 21, 20, 19, 18, 17, 16, 16, 15, 14,
	13, 13, 12, 11, 11, 10, 9, 9, 8, 8,
	7, 7, 6, 6, 5, 5, 4, 4, 4, 3,
	3, 3, 2, 2, 2, 2, 1, 1, 1, 1,
	1, 1, 0, 0, 0, 0, 0, 0, 0, 0
};

static const U08 g_cu08HazardInitialPattern_Ary[ FLASH_PATTERN_NUM ] = {
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
		/* 点滁処理中は状態を変えない */
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
	BOOL isPos = (BOOL)(HW_PORT_IsActive( eINPUT_PORT_ILL ) &&
	                    HW_PORT_IsActive( eINPUT_PORT_POS_EN ));

	if( g_eFlashType == eFLASH_TYPE_NONE ){
		g_u08FlashFrameCount = 0;
		g_u08FlashCount = 0;
	}

	/* 点滅処理停止/開始 */
	if( g_eFlashType == eFLASH_TYPE_NONE ){
		HW_CCP_EnableFlash( FALSE );
	}else{
		HW_CCP_EnableFlash( TRUE );
	}

	switch( g_eFlashType ){
	case eFLASH_TYPE_NONE:
		HW_PORT_Set( eOUTPUT_PORT_R_EN, FALSE );
		HW_PORT_Set( eOUTPUT_PORT_L_EN, FALSE );
		HW_PORT_Set( eOUTPUT_PORT_POS_R_EN, isPos );
		HW_PORT_Set( eOUTPUT_PORT_POS_L_EN, isPos );
		break;
	case eFLASH_TYPE_HAZARD:
		HW_PORT_Set( eOUTPUT_PORT_R_EN, TRUE );
		HW_PORT_Set( eOUTPUT_PORT_L_EN, TRUE );
		HW_PORT_Set( eOUTPUT_PORT_POS_R_EN, FALSE );
		HW_PORT_Set( eOUTPUT_PORT_POS_L_EN, FALSE );
		break;
	case eFLASH_TYPE_WINKER_R:
		HW_PORT_Set( eOUTPUT_PORT_R_EN, TRUE );
		HW_PORT_Set( eOUTPUT_PORT_L_EN, FALSE );
		HW_PORT_Set( eOUTPUT_PORT_POS_R_EN, FALSE );
		HW_PORT_Set( eOUTPUT_PORT_POS_L_EN, isPos );
		break;
	case eFLASH_TYPE_WINKER_L:
		HW_PORT_Set( eOUTPUT_PORT_R_EN, FALSE );
		HW_PORT_Set( eOUTPUT_PORT_L_EN, TRUE );
		HW_PORT_Set( eOUTPUT_PORT_POS_R_EN, isPos );
		HW_PORT_Set( eOUTPUT_PORT_POS_L_EN, FALSE );
		break;
	default:
		break;
	}

	/* 点滅処理*/
	if( g_eFlashType == eFLASH_TYPE_HAZARD ){
		if( g_u08FlashCount == 0 ){
			HW_CCP_SetDuty( g_cu08HazardInitialPattern_Ary[ g_u08FlashFrameCount ]);
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
				if( g_u08FlashCount < WINKER_AUTO_FLASH ){
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
