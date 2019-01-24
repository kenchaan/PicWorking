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
typedef enum tagE_TIMER_TYPE {
	eTIMER_TYPE_MIN = 0,
	eTIMER_TYPE_FRAME = eTIMER_TYPE_MIN,
	eTIMER_TYPE_TIME,
	eTIMER_TYPE_MAX,
	eTIMER_TYPE_INVALID
} E_TIMER_TYPE;
typedef const E_TIMER_TYPE CE_TIMER_TYPE;

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
BOOL HW_TIM_IsUpdate( CE_TIMER_TYPE index );
U32  HW_TIM_GetCount( CE_TIMER_TYPE index );
void HW_TIM_SetCount( CE_TIMER_TYPE index, const U32 count );
void HW_TIM_Clear( CE_TIMER_TYPE index );
void HW_TIM_EnableInterrupt( CE_TIMER_TYPE index, const BOOL isEnable );
void HW_TIM_Interrupt( CE_TIMER_TYPE index );


/*------------------------------------------------------------------------------
*	End Of File
*-----------------------------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
#endif	/* _HARDWARE_TIMER_H_ */