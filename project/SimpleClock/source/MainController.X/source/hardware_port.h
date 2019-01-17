#ifndef _HARDWARE_PORT_H_
#define _HARDWARE_PORT_H_
#ifdef __cplusplus
extern "C" {	/* } */
#endif
/*******************************************************************************
*	Author		|	Date		|	FileName
*-------------------------------------------------------------------------------
*	ken_chaan	|	2018/12/26	|	hardware_port.h
*-------------------------------------------------------------------------------
*	Description	|	ポート制御
*-------------------------------------------------------------------------------
*	Copyright (c) 2018 ken_chaan All Rights Reserved.
*******************************************************************************/

/*------------------------------------------------------------------------------
*	include
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
typedef enum tagE_OUTPUT_PORT {
	eOUTPUT_PORT_MIN = 0,
	eOUTPUT_PORT_PROC_FAIL = eOUTPUT_PORT_MIN,
	eOUTPUT_PORT_STATUS_INT_TMR0,
	eOUTPUT_PORT_STATUS_INT_TMR1,
	eOUTPUT_PORT_STATUS_INT_SSP,
	eOUTPUT_PORT_STATUS_SSP_SEND,
	eOUTPUT_PORT_ERROR_SSP_STORE,
	eOUTPUT_PORT_ERROR_SSP_SEND_START,
	eOUTPUT_PORT_ERROR_SSP_SEND_FAIL,
	eOUTPUT_PORT_MAX,
	eOUTPUT_PORT_INVALID
} E_OUTPUT_PORT;
typedef const E_OUTPUT_PORT CE_OUTPUT_PORT;

typedef enum tagE_INPUT_PORT {
	eINPUT_PORT_MIN = 0,
	eINPUT_PORT_HOUR = eINPUT_PORT_MIN,
	eINPUT_PORT_MINUTE,
	eINPUT_PORT_SEC_RESET,
	eINPUT_PORT_MAX,
	eINPUT_PORT_INVALID
} E_INPUT_PORT;
typedef const E_INPUT_PORT CE_INPUT_PORT;

typedef enum tagE_INPUT_STATE {
	eINPUT_STATE_MIN = 0,
	eINPUT_STATE_NONE = eINPUT_STATE_MIN,
	eINPUT_STATE_ONCE,
	eINPUT_STATE_CONT,
	eINPUT_STATE_MAX,
	eINPUT_STATE_INVALID
} E_INPUT_STATE;
typedef const E_INPUT_STATE CE_INPUT_STATE;

/*------------------------------------------------------------------------------
*	struct
*-----------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------
*	extern data
*-----------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------
*	extern function prototype
*-----------------------------------------------------------------------------*/
void HW_PORT_Initialize( void );
void HW_PORT_Set( CE_OUTPUT_PORT port, const BOOL state );
void HW_PORT_Update( void );
BOOL HW_PORT_Get( CE_INPUT_PORT port );


/*------------------------------------------------------------------------------
*	End Of File
*-----------------------------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
#endif	/* _HARDWARE_PORT_H_ */
