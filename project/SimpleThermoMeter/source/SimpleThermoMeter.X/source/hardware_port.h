#ifndef _HARDWARE_PORT_H_
#define _HARDWARE_PORT_H_
#ifdef __cplusplus
extern "C" {	/* } */
#endif
/*******************************************************************************
*	Author		|	Date		|	FileName
*-------------------------------------------------------------------------------
*	kenchaan	|	2019/01/29	|	hardware_port.h
*-------------------------------------------------------------------------------
*	Description	|	ポート制御
*-------------------------------------------------------------------------------
*	Copyright (c) 2019 kenchaan All Rights Reserved.
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
typedef enum tagE_INPUT_PORT {
	eINPUT_PORT_MIN = 0,
	eINPUT_PORT_TEMP_SET = eINPUT_PORT_MIN,
	eINPUT_PORT_TEMP_UP,
	eINPUT_PORT_MAX,
	eINPUT_PORT_INVALID
} E_INPUT_PORT;
typedef const E_INPUT_PORT CE_INPUT_PORT;

typedef enum tagE_INPUT_ANALOG_PORT {
	eINPUT_ANALOG_PORT_MIN = 0,
	eINPUT_ANALOG_PORT_TEMP = eINPUT_ANALOG_PORT_MIN,
	eINPUT_ANALOG_PORT_MAX,
	eINPUT_ANALOG_PORT_INVALID
} E_INPUT_ANALOG_PORT;
typedef const E_INPUT_ANALOG_PORT CE_INPUT_ANALOG_PORT;

typedef enum tagE_OUTPUT_PORT {
	eOUTPUT_PORT_MIN = 0,
	eOUTPUT_PORT_FAN_CTRL = eOUTPUT_PORT_MIN,
	eOUTPUT_PORT_ERROR_PROC_FAIL,
	eOUTPUT_PORT_MAX,
	eOUTPUT_PORT_INVALID
} E_OUTPUT_PORT;
typedef const E_OUTPUT_PORT CE_OUTPUT_PORT;

typedef enum tagE_OUTPUT_PORT_DIGIT {
	eOUTPUT_PORT_DIGIT_MIN = 0,
	eOUTPUT_PORT_DIGIT_INT_10 = eOUTPUT_PORT_DIGIT_MIN,
	eOUTPUT_PORT_DIGIT_INT_01,
	eOUTPUT_PORT_DIGIT_DEC,
	eOUTPUT_PORT_DIGIT_MAX,
	eOUTPUT_PORT_DIGIT_NONE,
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
void HW_PORT_Update( void );
BOOL HW_PORT_IsActive( CE_INPUT_PORT port );
U16  HW_PORT_GetAnalogData( CE_INPUT_ANALOG_PORT port );
void HW_PORT_Set( CE_OUTPUT_PORT port, const BOOL isActive );
BOOL HW_PORT_GetOutputData( CE_OUTPUT_PORT port );
void HW_PORT_SetSegData( CE_OUTPUT_PORT_DIGIT digit, const U08 data );


/*------------------------------------------------------------------------------
*	End Of File
*-----------------------------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
#endif	/* _HARDWARE_PORT_H_ */
