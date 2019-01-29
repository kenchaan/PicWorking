#ifndef _HARDWARE_H_
#define _HARDWARE_H_
#ifdef __cplusplus
extern "C" {	/* } */
#endif
/*******************************************************************************
*	Author		|	Date		|	FileName
*-------------------------------------------------------------------------------
*	kenchaan	|	2019/01/29	|	hardware.h
*-------------------------------------------------------------------------------
*	Description	|	ハードウェア制御
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


/*------------------------------------------------------------------------------
*	struct
*-----------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------
*	extern data
*-----------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------
*	extern function prototype
*-----------------------------------------------------------------------------*/
void HW_Initialize( void );
void HW_StartProcess( void );
void HW_WaitFrameStart( void );
void HW_FramePreProcess( void );
void HW_FrameMainProcess( void );
void HW_FramePostProcess( void );


/*------------------------------------------------------------------------------
*	End Of File
*-----------------------------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
#endif	/* _HARDWARE_H_ */
