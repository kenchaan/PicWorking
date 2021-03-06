#ifndef _HARDWARE_INTERRUPT_H_
#define _HARDWARE_INTERRUPT_H_
#ifdef __cplusplus
extern "C" {	/* } */
#endif
/*******************************************************************************
*	Author		|	Date		|	FileName
*-------------------------------------------------------------------------------
*	kenchaan	|	2019/01/23	|	hardware_interrupt.h
*-------------------------------------------------------------------------------
*	Description	|	割り込み制御
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
*	関数マクロ
*-----------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------
*	typedef
*-----------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------
*	enum
*-----------------------------------------------------------------------------*/
typedef enum tagE_INTERRUPT_TYPE {
	eINTERRUPT_TYPE_MIN = 0,
	eINTERRUPT_TYPE_TMR0 = eINTERRUPT_TYPE_MIN,
	eINTERRUPT_TYPE_INT,
	eINTERRUPT_TYPE_PORTB,
	eINTERRUPT_TYPE_ADC,
	eINTERRUPT_TYPE_EUSART_RECEIVE,
	eINTERRUPT_TYPE_EUSART_TRANS,
	eINTERRUPT_TYPE_MSSP,
	eINTERRUPT_TYPE_CCP1,
	eINTERRUPT_TYPE_TMR2,
	eINTERRUPT_TYPE_TMR1,
	eINTERRUPT_TYPE_OSCFAIL,
	eINTERRUPT_TYPE_C2,
	eINTERRUPT_TYPE_C1,
	eINTERRUPT_TYPE_EEPROM,
	eINTERRUPT_TYPE_BUS,
	eINTERRUPT_TYPE_ULPWU,
	eINTERRUPT_TYPE_CCP2,
	eINTERRUPT_TYPE_MAX,
	eINTERRUPT_TYPE_INVALID
} E_INTERRUPT_TYPE;
typedef const E_INTERRUPT_TYPE CE_INTERRUPT_TYPE;

/*------------------------------------------------------------------------------
*	struct
*-----------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------
*	extern data
*-----------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------
*	extern function prototype
*-----------------------------------------------------------------------------*/
void interrupt InterruptHandler( void );
void HW_INT_Initialize( void );
void HW_INT_StartProcess( void );
BOOL HW_INT_IsInterrupted( CE_INTERRUPT_TYPE type );
void HW_INT_Clear( CE_INTERRUPT_TYPE type );


/*------------------------------------------------------------------------------
*	End Of File
*-----------------------------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
#endif	/* _HARDWARE_INTERRUPT_H_ */
