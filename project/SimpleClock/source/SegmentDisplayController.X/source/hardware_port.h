#ifndef _HARDWARE_PORT_H_
#define _HARDWARE_PORT_H_
#ifdef __cplusplus
extern "C" {	/* } */
#endif
/*******************************************************************************
*	Author		|	Date		|	FileName
*-------------------------------------------------------------------------------
*	ken_chaan	|	2019/01/07	|	hardware_port.h
*-------------------------------------------------------------------------------
*	Description	|	ポート制御
*-------------------------------------------------------------------------------
*	Copyright (c) 2019 ken_chaan All Rights Reserved.
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
	eOUTPUT_PORT_STATUS_INT_TMR0 = eOUTPUT_PORT_MIN,
	eOUTPUT_PORT_STATUS_INT_SSP,
	eOUTPUT_PORT_STATUS_SSP_RECV,
	eOUTPUT_PORT_ERROR_PROC_FAIL,
	eOUTPUT_PORT_ERROR_SSP_RECV_1,
	eOUTPUT_PORT_ERROR_SSP_RECV_2,
	eOUTPUT_PORT_MAX,
	eOUTPUT_PORT_INVALID
} E_OUTPUT_PORT;
typedef const E_OUTPUT_PORT CE_OUTPUT_PORT;

typedef enum tagE_OUTPUT_PORT_DIGIT {
	eOUTPUT_PORT_DIGIT_MIN = 0,
	eOUTPUT_PORT_DIGIT_H10 = eOUTPUT_PORT_DIGIT_MIN,
	eOUTPUT_PORT_DIGIT_H01,
	eOUTPUT_PORT_DIGIT_M10,
	eOUTPUT_PORT_DIGIT_M01,
	eOUTPUT_PORT_DIGIT_MAX,
	eOUTPUT_PORT_DIGIT_NONE = eOUTPUT_PORT_DIGIT_MAX,
	eOUTPUT_PORT_DIGIT_INVALID
} E_OUTPUT_PORT_DIGIT;
typedef const E_OUTPUT_PORT_DIGIT CE_OUTPUT_PORT_DIGIT;

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
void HW_PORT_SetSegData( CE_OUTPUT_PORT_DIGIT digit, const U08 data );


/*------------------------------------------------------------------------------
*	End Of File
*-----------------------------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
#endif	/* _HARDWARE_PORT_H_ */
