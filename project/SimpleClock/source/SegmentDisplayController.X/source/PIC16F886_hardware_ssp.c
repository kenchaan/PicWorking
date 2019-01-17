/*******************************************************************************
*	Author		|	Date		|	FileName
*-------------------------------------------------------------------------------
*	ken_chaan	|	2019/01/15	|	PIC16F886_hardware_ssp.c
*-------------------------------------------------------------------------------
*	Description	|	[PIC16F886]SSP制御
*-------------------------------------------------------------------------------
*	Copyright (c) 2019 ken_chaan All Rights Reserved.
*******************************************************************************/

/*------------------------------------------------------------------------------
*	include
*-----------------------------------------------------------------------------*/
#include <xc.h>
#include "types.h"
#include "regaccess.h"
#include "hardware_port.h"
#include "hardware_ssp.h"

/*------------------------------------------------------------------------------
*	pragma
*-----------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------
*	define
*-----------------------------------------------------------------------------*/
#define SSP_ADDR				(0x40)

#define RECV_BUF_SIZE			(32)

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
*	static variable
*-----------------------------------------------------------------------------*/
/* 受信データバッファ用 */
static volatile U08 g_u08RecvBuf_Ary[ RECV_BUF_SIZE ];
static volatile U08 g_u08RecvBufPosW = 0;
static volatile U08 g_u08RecvBufPosR = 0;

/* 受信用 */
static volatile U08 g_u08ReceivingCount = 0;
static volatile BOOL g_isSkipStoreData = FALSE;

/*------------------------------------------------------------------------------
*	static function prototype
*-----------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------
*	static const data
*-----------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------
*	extern const data
*-----------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------
*	function
*-----------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
* OverView	: SSP初期化
* Parameter	: None
* Return	: None
*-----------------------------------------------------------------------------*/
void HW_SSP_Initialize( void )
{
	/* SSP設定(I2C,Slave,400kHz,S/PInt) */
	REG_WRITE_08( SSPCON, 0x3E );
	REG_WRITE_08( SSPCON2, 0x00 );
	REG_WRITE_08( SSPSTAT, 0x00 );
	REG_WRITE_08( SSPADD, SSP_ADDR );
	REG_SET_08( PIE1, 0x08 );
}

/*------------------------------------------------------------------------------
* OverView	: SSP受信数取得
* Parameter	: None
* Return	: 受信数
*-----------------------------------------------------------------------------*/
U08 HW_SSP_GetReceivedDataCount( void )
{
	if( g_u08RecvBufPosW >= g_u08RecvBufPosR ){
		return (U08)( g_u08RecvBufPosW - g_u08RecvBufPosR );
	}else{
		return (U08)( g_u08RecvBufPosW + RECV_BUF_SIZE - g_u08RecvBufPosR );
	}
}

/*------------------------------------------------------------------------------
* OverView	: SSP受信データ取得
* Parameter	: None
* Return	: 受信データ
*-----------------------------------------------------------------------------*/
U08 HW_SSP_GetReceivedData( void )
{
	if( HW_SSP_GetReceivedDataCount() == 0 ){
		HW_PORT_Set( eOUTPUT_PORT_ERROR_SSP_RECV_1, TRUE );
		return 0;
	}

	U08 data = g_u08RecvBuf_Ary[ g_u08RecvBufPosR ];

	/* リードポインタ更新 */
	g_u08RecvBufPosR++;
	if( g_u08RecvBufPosR >= RECV_BUF_SIZE ){
		g_u08RecvBufPosR = 0;
	}

	return data;
}

/*------------------------------------------------------------------------------
* OverView	: SSP割り込み処理
* Parameter	: None
* Return	: None
*-----------------------------------------------------------------------------*/
void HW_SSP_Interrupt( void )
{
	/* 割り込み要因確認 */
	if( REG_READ_08( SSPSTAT ) & 0x08 ){
		/* スタートビット */
		g_u08ReceivingCount = 0;
		g_isSkipStoreData = TRUE;	/* 次はアドレス */
		return;

	}else if( REG_READ_08( SSPSTAT ) & 0x10 ){
		/* ストップビット */
		if(( g_u08RecvBufPosW + g_u08ReceivingCount ) >= RECV_BUF_SIZE ){
			g_u08RecvBufPosW = (U08)( g_u08RecvBufPosW + g_u08ReceivingCount - RECV_BUF_SIZE );
		}else{
			g_u08RecvBufPosW += g_u08ReceivingCount;
		}

	}else if( REG_READ_08( SSPSTAT ) & 0x01 ){
		if( g_isSkipStoreData ){
			/* アドレス */
			g_isSkipStoreData = FALSE;
			U08 dummy = REG_READ_08( SSPBUF );

		}else{
			/* データ */
			U08 writepos = (U08)( g_u08RecvBufPosW + g_u08ReceivingCount );
			if( writepos >= RECV_BUF_SIZE ){
				writepos -= RECV_BUF_SIZE;
			}
			if( writepos == g_u08RecvBufPosR ){
				HW_PORT_Set( eOUTPUT_PORT_ERROR_SSP_RECV_1, TRUE );
				U08 dummy = REG_READ_08( SSPBUF );
				return;
			}
			g_u08RecvBuf_Ary[ writepos ] = REG_READ_08( SSPBUF );
			g_u08ReceivingCount++;
		}

	}else{
		/* ありえない */
		HW_PORT_Set( eOUTPUT_PORT_ERROR_SSP_RECV_2, TRUE );
		return;
	}
}


/*------------------------------------------------------------------------------
*	End Of File
*-----------------------------------------------------------------------------*/
