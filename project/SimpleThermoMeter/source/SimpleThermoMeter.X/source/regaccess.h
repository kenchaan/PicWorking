#ifndef _REGACCESS_H_
#define _REGACCESS_H_
#ifdef __cplusplus
extern "C" {	/* } */
#endif
/*******************************************************************************
*	Author		|	Date		|	FileName
*-------------------------------------------------------------------------------
*	ken_chaan	|	2018/11/16	|	regaccess.h
*-------------------------------------------------------------------------------
*	Description	|	レジスタアクセス
*-------------------------------------------------------------------------------
*	Copyright (c) 2018 ken_chaan All Rights Reserved.
*******************************************************************************/

/*------------------------------------------------------------------------------
*	include
*-----------------------------------------------------------------------------*/
#include <xc.h>

/*------------------------------------------------------------------------------
*	define
*-----------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------
*	macro
*-----------------------------------------------------------------------------*/
//#define REG_READ_08(addr)				( *(volatile U08 *)(addr) )
//#define REG_WRITE_08(addr,data)			( *(volatile U08 *)(addr) = (U08)(data) )
//#define REG_SET_08(addr,data)			( *(volatile U08 *)(addr) |= (U08)(data) )
//#define REG_CLR_08(addr,data)			( *(volatile U08 *)(addr) &= (U08)~(data) )
//#define REG_RMW_08(addr,mask,data)		( *(volatile U08 *)(addr) = (U08)(( REG_READ_08(addr) & (U08)~(mask) ) | ( (U08)(data) & (U08)(mask) ) ))

#define REG_READ_08(addr)				(addr)
#define REG_READ_16(addr)				(addr)
#define REG_WRITE_08(addr,data)			((addr) = (U08)(data))
#define REG_WRITE_16(addr,data)			((addr) = (U16)(data))
#define REG_SET_08(addr,data)			((addr) |= (U08)(data))
#define REG_CLR_08(addr,data)			((addr) &= (U08)~(data))
#define REG_RMW_08(addr,mask,data)		((addr) = (U08)((REG_READ_08(addr) & (U08)~(mask)) | ((U08)(data) & (U08)(mask))))

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



/*------------------------------------------------------------------------------
*	End Of File
*-----------------------------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
#endif	/* _REGACCESS_H_ */
