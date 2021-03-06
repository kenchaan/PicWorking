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
#include "hardware_interrupt.h"
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
static volatile U32 g_u32TimeCount = 0;
static volatile BOOL g_isUpdatedTime = FALSE;

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
	/* 32.768kHz(External),1:1,49152 → 0.5sec */
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
}

/*------------------------------------------------------------------------------
* OverView	: タイマ更新
* Parameter	: None
* Return	: None
*-----------------------------------------------------------------------------*/
void HW_TIM_Update( void )
{
	if( HW_INT_IsInterrupted( eINTERRUPT_TYPE_TMR1 )){
		g_u32TimeCount++;
		g_isUpdatedTime = TRUE;
	}
}

/*------------------------------------------------------------------------------
* OverView	: タイマ更新有無取得
* Parameter	: None
* Return	: TRUE	: 更新あり
* 			: FALSE	: 更新なし
*-----------------------------------------------------------------------------*/
BOOL HW_TIM_IsUpdatedTime( void )
{
	return g_isUpdatedTime;
}

/*------------------------------------------------------------------------------
* OverView	: 時間カウント取得
* Parameter	: None
* Return	: 時間カウント値
*-----------------------------------------------------------------------------*/
U32 HW_TIM_GetTimeCount( void )
{
	return g_u32TimeCount;
}

/*------------------------------------------------------------------------------
* OverView	: 時間カウント設定
* Parameter	: count	: 時間カウント値
* Return	: None
*-----------------------------------------------------------------------------*/
void HW_TIM_SetTimeCount( const U32 count )
{
	g_u32TimeCount = count;
	g_isUpdatedTime = TRUE;
}

/*------------------------------------------------------------------------------
* OverView	: 時間カウントクリア
* Parameter	: None
* Return	: None
*-----------------------------------------------------------------------------*/
void HW_TIM_ClearTimeCount( void )
{
	g_u32TimeCount = 0;
	g_isUpdatedTime = TRUE;
}


/*------------------------------------------------------------------------------
*	End Of File
*-----------------------------------------------------------------------------*/
