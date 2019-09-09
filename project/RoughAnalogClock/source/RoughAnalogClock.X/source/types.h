#ifndef _TYPES_H_
#define _TYPES_H_
#ifdef __cplusplus
extern "C" {	/* } */
#endif
/*******************************************************************************
*	Author		|	Date		|	FileName
*-------------------------------------------------------------------------------
*	kenchaan	|	2019/09/09	|	types.h
*-------------------------------------------------------------------------------
*	Description	|	共通型定義
*-------------------------------------------------------------------------------
*	Copyright (c) 2019 kenchaan All Rights Reserved.
*******************************************************************************/

/*------------------------------------------------------------------------------
*	include
*-----------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------
*	define
*-----------------------------------------------------------------------------*/
#ifndef NULL
 #define NULL					((void *)0)
#endif

#define FALSE					(0)
#define TRUE					(1)

/*------------------------------------------------------------------------------
*	macro
*-----------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------
*	typedef
*-----------------------------------------------------------------------------*/
/* 符号付き整数 */
typedef signed char				S08;		/*  8ビット */
typedef signed short			S16;		/* 16ビット */
typedef signed long				S32;		/* 32ビット */

/* 符号無し整数 */
typedef unsigned char			U08;		/*  8ビット */
typedef unsigned short			U16;		/* 16ビット */
typedef unsigned long			U32;		/* 32ビット */

/* 浮動小数点数 */
typedef float					F32;		/* 32ビット */

/* ブール型 */
typedef char					BOOL;

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



/*------------------------------------------------------------------------------
*	End Of File
*-----------------------------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
#endif	/* _TYPES_H_ */
