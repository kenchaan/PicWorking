/*******************************************************************************
*	Author		|	Date		|	FileName
*-------------------------------------------------------------------------------
*	ken_chaan	|	2018/12/26	|	PIC16F886_hardware_ssp.c
*-------------------------------------------------------------------------------
*	Description	|	[PIC16F886]SSP制御
*-------------------------------------------------------------------------------
*	Copyright (c) 2018 ken_chaan All Rights Reserved.
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
#define SEND_BUF_NUM			(1)
#define SEND_BUF_SIZE			(32)

/*------------------------------------------------------------------------------
*	macro
*-----------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------
*	typedef
*-----------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------
*	enum
*-----------------------------------------------------------------------------*/
typedef enum tagE_SEND_STATE {
	eSEND_STATE_MIN = 0,
	eSEND_STATE_IDLE = eSEND_STATE_MIN,
	eSEND_STATE_ADDRESS,
	eSEND_STATE_DATA,
	eSEND_STATE_STOP_BIT,
	eSEND_STATE_MAX,
	eSEND_STATE_INVALID
} E_SEND_STATE;
typedef const E_SEND_STATE CE_SEND_STATE;

/*------------------------------------------------------------------------------
*	struct
*-----------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------
*	static variable
*-----------------------------------------------------------------------------*/
/* 送信データ蓄積バッファ用 */
static U08 g_u08SendStoreBuf_Ary[ SEND_BUF_NUM ][ SEND_BUF_SIZE ];
static U08 g_u08SendStoreBufPosW_Ary[ SEND_BUF_NUM ];
static U08 g_u08SendStoreBufPosR_Ary[ SEND_BUF_NUM ];

/* 送信用 */
static volatile U08 g_u08SendingBuf_Ary[ SEND_BUF_SIZE ];
static volatile E_SEND_STATE g_eSendState;
static volatile U08 g_u08SendingSize;
static volatile U08 g_u08SendingAddr;
static volatile U08 g_u08SendingIndex;

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
	U08 i;

	/* SSP設定(I2C,Master,400kHz,50kHz) */
	REG_WRITE_08( SSPCON, 0x28 );
	REG_WRITE_08( SSPCON2, 0x00 );
	REG_WRITE_08( SSPSTAT, 0x00 );
	REG_WRITE_08( SSPADD, 0x63 );
	REG_SET_08( PIE1, 0x08 );

	/* 変数初期化 */
	for( i = 0; i < SEND_BUF_NUM; i++ ){
		g_u08SendStoreBufPosW_Ary[ i ] = 0;
		g_u08SendStoreBufPosR_Ary[ i ] = 0;
	}
	g_eSendState = eSEND_STATE_IDLE;
}

/*------------------------------------------------------------------------------
* OverView	: SSP送信データ蓄積
* Parameter	: number	: バッファ番号
* 			: pData		: 送信データ
* 			: size		: 送信データサイズ
* Return	: TRUE	: 成功
* 			: FALSE	: 失敗
*-----------------------------------------------------------------------------*/
BOOL HW_SSP_StoreSendData( const U08 number, const U08 * const pData, const U08 size )
{
	/* サイズの確認 */
	if( size >= SEND_BUF_SIZE ){
		HW_PORT_Set( eOUTPUT_PORT_ERROR_SSP_STORE, TRUE );
		return FALSE;
	}

	/* ライトポインタがリードポインタを追い越さないかどうかチェック */
	U16 readpos;
	if( g_u08SendStoreBufPosW_Ary[ number ] >= g_u08SendStoreBufPosR_Ary[ number ]){
		readpos = (U16)( g_u08SendStoreBufPosR_Ary[ number ] + SEND_BUF_SIZE );
	}else{
		readpos = g_u08SendStoreBufPosR_Ary[ number ];
	}
	U08 maxsize = (U08)(( readpos - g_u08SendStoreBufPosW_Ary[ number ]) - 1 );
	if( maxsize < size ){
		HW_PORT_Set( eOUTPUT_PORT_ERROR_SSP_STORE, TRUE );
		return FALSE;
	}

	/* 蓄積バッファに書き込み */
	for( U08 i = 0; i < size; i++ ){
		U08 writepos = g_u08SendStoreBufPosW_Ary[ number ];
		g_u08SendStoreBuf_Ary[ number ][ writepos ] = pData[ i ];

		/* ライトポインタ更新 */
		g_u08SendStoreBufPosW_Ary[number]++;
		if( g_u08SendStoreBufPosW_Ary[ number ] >= SEND_BUF_SIZE ){
			g_u08SendStoreBufPosW_Ary[ number ] = 0;
		}
	}

	return TRUE;
}

/*------------------------------------------------------------------------------
* OverView	: SSP送信開始
* Parameter	: number	: バッファ番号
* 			: addr		: 送信先アドレス
* Return	: TRUE	: 成功
* 			: FALSE	: 失敗
*-----------------------------------------------------------------------------*/
BOOL HW_SSP_StartSend( const U08 number, const U08 addr )
{
	U08 i;

	if(( g_eSendState != eSEND_STATE_IDLE ) || ( REG_READ_08( SSPCON2 ) & 0x1F )){
		HW_PORT_Set( eOUTPUT_PORT_ERROR_SSP_SEND_START, TRUE );
		return FALSE;
	}

	/* 送信サイズ計算 */
	U16 writepos;
	if( g_u08SendStoreBufPosR_Ary[ number ] <= g_u08SendStoreBufPosW_Ary[ number ]){
		writepos = g_u08SendStoreBufPosW_Ary[ number ];
	}else{
		writepos = (U16)( g_u08SendStoreBufPosW_Ary[ number ] + SEND_BUF_SIZE );
	}
	g_u08SendingSize = writepos - g_u08SendStoreBufPosR_Ary[ number ];

	if( g_u08SendingSize == 0 ){
		/* 送信データなし */
		return TRUE;
	}

	/* 送信用バッファにコピー */
	for( i = 0; i < g_u08SendingSize; i++ ){
		U08 readpos = g_u08SendStoreBufPosR_Ary[ number ];
		g_u08SendingBuf_Ary[ i ] = g_u08SendStoreBuf_Ary[ number ][ readpos ];

		/* リードポインタ更新 */
		g_u08SendStoreBufPosR_Ary[ number ]++;
		if( g_u08SendStoreBufPosR_Ary[ number ] >= SEND_BUF_SIZE ){
			g_u08SendStoreBufPosR_Ary[ number ] = 0;
		}
	}

	g_u08SendingAddr = addr;
	g_u08SendingIndex = 0;

	HW_PORT_Set( eOUTPUT_PORT_STATUS_SSP_SEND, TRUE );

	/* スタートビット送信 */
	REG_CLR_08( PIR1, 0x08 );
	REG_SET_08( SSPCON2, 0x01 );

	g_eSendState = eSEND_STATE_ADDRESS;

	return TRUE;
}

/*------------------------------------------------------------------------------
* OverView	: SSP割り込み処理
* Parameter	: None
* Return	: None
*-----------------------------------------------------------------------------*/
void HW_SSP_Interrupt( void )
{
	switch( g_eSendState ){
	case eSEND_STATE_IDLE:
		/* アイドル確認 */
		if( REG_READ_08( SSPCON2 ) & 0x1F ){
			HW_PORT_Set( eOUTPUT_PORT_ERROR_SSP_SEND_FAIL, TRUE );
			HW_PORT_Set( eOUTPUT_PORT_STATUS_SSP_SEND, FALSE );
		}
		return;

	case eSEND_STATE_ADDRESS:
		/* スタートビット状態確認 */
		if( REG_READ_08( SSPCON2 ) & 0x01 ){
			/* スタートビットクリア */
			REG_CLR_08( SSPCON2, 0x01 );
			HW_PORT_Set( eOUTPUT_PORT_ERROR_SSP_SEND_FAIL, TRUE );
			HW_PORT_Set( eOUTPUT_PORT_STATUS_SSP_SEND, FALSE );
			g_eSendState = eSEND_STATE_IDLE;
			return;
		}

		/* アドレス送信 */
		REG_WRITE_08( SSPBUF, (U08)(( g_u08SendingAddr << 1 ) + 0 ));

		g_eSendState = eSEND_STATE_DATA;
		break;

	case eSEND_STATE_DATA:
		/* ACK確認 */
		if( !( REG_READ_08( SSPCON2 ) & 0x40 )){
			HW_PORT_Set( eOUTPUT_PORT_ERROR_SSP_SEND_FAIL, TRUE );
			HW_PORT_Set( eOUTPUT_PORT_STATUS_SSP_SEND, FALSE );
			/* ストップビット送信 */
			REG_SET_08( SSPCON2, 0x04 );
			g_eSendState = eSEND_STATE_IDLE;
			return;
		}

		/* データ送信 */
		REG_WRITE_08( SSPBUF, g_u08SendingBuf_Ary[ g_u08SendingIndex++ ]);

		if( g_u08SendingIndex < g_u08SendingSize ){
			g_eSendState = eSEND_STATE_DATA;
		}else{
			g_eSendState = eSEND_STATE_STOP_BIT;
		}
		break;

	case eSEND_STATE_STOP_BIT:
		/* ACK確認 */
		if( !( REG_READ_08( SSPCON2 ) & 0x40 )){
			HW_PORT_Set( eOUTPUT_PORT_ERROR_SSP_SEND_FAIL, TRUE );
			HW_PORT_Set( eOUTPUT_PORT_STATUS_SSP_SEND, FALSE );
			/* ストップビット送信 */
			REG_SET_08( SSPCON2, 0x04 );
			g_eSendState = eSEND_STATE_IDLE;
			return;
		}

		/* ストップビット送信 */
		REG_SET_08( SSPCON2, 0x04 );
		g_eSendState = eSEND_STATE_IDLE;
		break;

	default:
		/* ありえない */
		HW_PORT_Set( eOUTPUT_PORT_ERROR_SSP_SEND_FAIL, TRUE );
		HW_PORT_Set( eOUTPUT_PORT_STATUS_SSP_SEND, FALSE );
		g_eSendState = eSEND_STATE_IDLE;
		break;
	}
}


/*------------------------------------------------------------------------------
*	End Of File
*-----------------------------------------------------------------------------*/
