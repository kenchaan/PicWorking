/*******************************************************************************
*	Author		|	Date		|	FileName
*-------------------------------------------------------------------------------
*	kenchaan	|	2019/01/23	|	PIC16F886_hardware_timer.c
*-------------------------------------------------------------------------------
*	Description	|	[PIC16F886]タイマ制御
*-------------------------------------------------------------------------------
*	Copyright (c) 2019 kenchaan All Rights Reserved.
*******************************************************************************/

/*------------------------------------------------------------------------------
*	include
*-----------------------------------------------------------------------------*/
#include <xc.h>
#include "types.h"
#include "regaccess.h"
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
static volatile U32 g_u32TimerCount_Ary[ eTIMER_TYPE_MAX ];
static volatile BOOL g_isUpdateTimer_Ary[ eTIMER_TYPE_MAX ];
static volatile BOOL g_isEnableInterrupt_Ary[ eTIMER_TYPE_MAX ];

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
* OverView	: タイマ初期化
* Parameter	: None
* Return	: None
*-----------------------------------------------------------------------------*/
void HW_TIM_Initialize( void)
{
	/* TMR0設定(フレーム処理用) */
	/* 20MHz,1:64,0 → 3.2768msec */
	REG_RMW_08( OPTION_REG, 0x3F, 0x05 );
	REG_WRITE_08( TMR0, TMR0_DEFAULT );
	REG_SET_08( INTCON, 0x20 );

	/* TMR1設定(時間カウント用) */
	/* 32.768kHz(External),1:1,32768 → 1.0sec */
	REG_WRITE_08( T1CON, 0x0B );
	REG_WRITE_08( TMR1H, TMR1H_DEFAULT );
	REG_SET_08( PIE1, 0x01 );
}

/*------------------------------------------------------------------------------
* OverView	: タイマ処理開始
* Parameter	: None
* Return	: None
*-----------------------------------------------------------------------------*/
void HW_TIM_StartProcess( void )
{
	/* TMR0クリア */
	REG_WRITE_08( TMR0, TMR0_DEFAULT );

	/* TMR1クリア */
	REG_WRITE_08( TMR1H, TMR1H_DEFAULT );

	for( E_TIMER_TYPE e = eTIMER_TYPE_MIN; e < eTIMER_TYPE_MAX; e++ ){
		g_u32TimerCount_Ary[ e ] = 0;
		g_isUpdateTimer_Ary[ e ] = FALSE;
		g_isEnableInterrupt_Ary[ e ] = TRUE;
	}
}

/*------------------------------------------------------------------------------
* OverView	: タイマ更新有無取得
* Parameter	: index	: タイマインデックス
* Return	: TRUE	: 更新あり
* 			: FALSE	: 更新なし
*-----------------------------------------------------------------------------*/
BOOL HW_TIM_IsUpdate( CE_TIMER_TYPE index )
{
	return g_isUpdateTimer_Ary[ index ];
}

/*------------------------------------------------------------------------------
* OverView	: タイマ取得
* Parameter	: index	: タイマインデックス
* Return	: タイマ値
*-----------------------------------------------------------------------------*/
U32 HW_TIM_GetCount( CE_TIMER_TYPE index )
{
	g_isUpdateTimer_Ary[ index ] = FALSE;

	return g_u32TimerCount_Ary[ index ];
}

/*------------------------------------------------------------------------------
* OverView	: タイマ設定
* Parameter	: index	: タイマインデックス
* 			: count	: タイマ値
* Return	: None
*-----------------------------------------------------------------------------*/
void HW_TIM_SetCount( CE_TIMER_TYPE index, const U32 count )
{
	g_u32TimerCount_Ary[ index ] = count;
	g_isUpdateTimer_Ary[ index ] = TRUE;
}

/*------------------------------------------------------------------------------
* OverView	: タイマクリア
* Parameter	: index	: タイマインデックス
* Return	: None
*-----------------------------------------------------------------------------*/
void HW_TIM_Clear( CE_TIMER_TYPE index )
{
	g_u32TimerCount_Ary[ index ] = 0;
	g_isUpdateTimer_Ary[ index ] = TRUE;
}

/*------------------------------------------------------------------------------
* OverView	: タイマ割り込み許可
* Parameter	: index		: タイマインデックス
* 			: isEnable	: TRUE:有効 FALSE:無効
* Return	: None
*-----------------------------------------------------------------------------*/
void HW_TIM_EnableInterrupt( CE_TIMER_TYPE index, const BOOL isEnable )
{
	g_isEnableInterrupt_Ary[ index ] = isEnable;
}

/*------------------------------------------------------------------------------
* OverView	: タイマ周期処理
* Parameter	: index	: タイマインデックス
* Return	: None
*-----------------------------------------------------------------------------*/
void HW_TIM_Interrupt( CE_TIMER_TYPE index )
{
	if( !g_isEnableInterrupt_Ary[ index ] ){
		return;
	}

	if( g_u32TimerCount_Ary[ index ] < 0xFFFFFFFF ){
		g_u32TimerCount_Ary[ index ]++;
	}

	if( index == eTIMER_TYPE_TIME ){
		if( g_u32TimerCount_Ary[ index ] >= 172800 ){
			g_u32TimerCount_Ary[ index ] = 0;
		}
	}

	g_isUpdateTimer_Ary[ index ] = TRUE;
}


/*------------------------------------------------------------------------------
*	End Of File
*-----------------------------------------------------------------------------*/
