#ifndef _HARDWARE_TIMER_H_
#define _HARDWARE_TIMER_H_
#ifdef __cplusplus
extern "C" {	/* } */
#endif
/*******************************************************************************
*	Author		|	Date		|	FileName
*-------------------------------------------------------------------------------
*	ken_chaan	|	2019/01/07	|	hardware_timer.h
*-------------------------------------------------------------------------------
*	Description	|	タイマ制御
*-------------------------------------------------------------------------------
*	Copyright (c) 2019 ken_chaan All Rights Reserved.
*******************************************************************************/

/*------------------------------------------------------------------------------
*	include
*-----------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------
*	define
*-----------------------------------------------------------------------------*/
#define TMR0_DEFAULT			((U08)(0x00))

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
U32 HW_TIM_GetCount( CE_TIMER_TYPE index );
void HW_TIM_Clear( CE_TIMER_TYPE index );
void HW_TIM_Interrupt( CE_TIMER_TYPE index );


/*------------------------------------------------------------------------------
*	End Of File
*-----------------------------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
#endif	/* _HARDWARE_TIMER_H_ */
