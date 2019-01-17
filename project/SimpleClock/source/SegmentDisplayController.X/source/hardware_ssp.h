#ifndef _PIC16F886_HARDWARE_I2C_H_
#define _PIC16F886_HARDWARE_I2C_H_
#ifdef __cplusplus
extern "C" {	/* } */
#endif
/*******************************************************************************
*	Author		|	Date		|	FileName
*-------------------------------------------------------------------------------
*	ken_chaan	|	2019/01/15	|	hardware_ssp.h
*-------------------------------------------------------------------------------
*	Description	|	SSP制御
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


/*------------------------------------------------------------------------------
*	struct
*-----------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------
*	extern data
*-----------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------
*	extern function prototype
*-----------------------------------------------------------------------------*/
void HW_SSP_Initialize( void );
U08 HW_SSP_GetReceivedDataCount( void );
U08 HW_SSP_GetReceivedData( void );
void HW_SSP_Interrupt( void );


/*------------------------------------------------------------------------------
*	End Of File
*-----------------------------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
#endif	/* _PIC16F886_HARDWARE_I2C_H_ */
