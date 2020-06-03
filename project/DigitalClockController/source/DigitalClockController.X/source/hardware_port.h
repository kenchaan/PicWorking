#ifndef _HARDWARE_PORT_H_
#define _HARDWARE_PORT_H_
#ifdef __cplusplus
extern "C" {	/* } */
#endif
/*******************************************************************************
*	Author		|	Date		|	FileName
*-------------------------------------------------------------------------------
*	kenchaan	|	2020/05/13	|	hardware_port.h
*-------------------------------------------------------------------------------
*	Description	|	�|�[�g����
*-------------------------------------------------------------------------------
*	Copyright (c) 2020 kenchaan All Rights Reserved.
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
	eINPUT_PORT_HOUR = eINPUT_PORT_MIN,
	eINPUT_PORT_MINUTE,
	eINPUT_PORT_SECOND_RST,
	eINPUT_PORT_MAX,
	eINPUT_PORT_INVALID
} E_INPUT_PORT;
typedef const E_INPUT_PORT CE_INPUT_PORT;

typedef enum tagE_OUTPUT_PORT {
	eOUTPUT_PORT_MIN = 0,
	eOUTPUT_PORT_ERROR_PROC_FAIL = eOUTPUT_PORT_MIN,
	eOUTPUT_PORT_MAX,
	eOUTPUT_PORT_INVALID
} E_OUTPUT_PORT;
typedef const E_OUTPUT_PORT CE_OUTPUT_PORT;


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
void HW_PORT_Set( CE_OUTPUT_PORT port, const BOOL isActive );
void HW_PORT_SetSegData( const U08 data[] );


/*------------------------------------------------------------------------------
*	End Of File
*-----------------------------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
#endif	/* _HARDWARE_PORT_H_ */