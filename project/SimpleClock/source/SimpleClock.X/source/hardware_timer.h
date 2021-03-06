#ifndef _HARDWARE_TIMER_H_
#define _HARDWARE_TIMER_H_
#ifdef __cplusplus
extern "C" {	/* } */
#endif
/*******************************************************************************
*	Author		|	Date		|	FileName
*-------------------------------------------------------------------------------
*	kenchaan	|	2019/01/23	|	hardware_timer.h
*-------------------------------------------------------------------------------
*	Description	|	タイマ制御
*-------------------------------------------------------------------------------
*	Copyright (c) 2019 kenchaan All Rights Reserved.
*******************************************************************************/

/*------------------------------------------------------------------------------
*	include
*-----------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------
*	define
*-----------------------------------------------------------------------------*/
#define TMR0_DEFAULT			(0x00)
#define TMR1H_DEFAULT			(0xC0)

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
*	extern data
*-----------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------
*	extern function prototype
*-----------------------------------------------------------------------------*/
void HW_TIM_Initialize( void);
void HW_TIM_StartProcess( void );
void HW_TIM_Update( void );
BOOL HW_TIM_IsUpdatedTime( void );
U32  HW_TIM_GetTimeCount( void );
void HW_TIM_SetTimeCount( const U32 count );
void HW_TIM_ClearTimeCount( void );
void HW_TIM_EnableUpdateCount( const BOOL isEnable );


/*------------------------------------------------------------------------------
*	End Of File
*-----------------------------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
#endif	/* _HARDWARE_TIMER_H_ */
