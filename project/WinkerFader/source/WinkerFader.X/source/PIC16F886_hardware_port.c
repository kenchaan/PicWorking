/*******************************************************************************
*	Author		|	Date		|	FileName
*-------------------------------------------------------------------------------
*	kenchaan	|	2020/01/13	|	PIC16F886_hardware_port.c
*-------------------------------------------------------------------------------
*	Description	|	[PIC16F886]ポート制御
*-------------------------------------------------------------------------------
*	Copyright (c) 2020 kenchaan All Rights Reserved.
*******************************************************************************/

/*------------------------------------------------------------------------------
*	include
*-----------------------------------------------------------------------------*/
#include <xc.h>
#include "types.h"
#include "regaccess.h"
#include "hardware.h"
#include "hardware_port.h"

/*------------------------------------------------------------------------------
*	pragma
*-----------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------
*	define
*-----------------------------------------------------------------------------*/
#define CHATTER_TH				(3)

#define INPUT_SW_HAZARD_PORT	(PORTA)
#define INPUT_SW_HAZARD_BIT		(0x01)
#define INPUT_SW_WINKER_R_PORT	(PORTA)
#define INPUT_SW_WINKER_R_BIT	(0x02)
#define INPUT_SW_WINKER_L_PORT	(PORTA)
#define INPUT_SW_WINKER_L_BIT	(0x04)

#define OUTPUT_PWM_PORT			(PORTC)
#define OUTPUT_PWM_BIT			(0x04)
#define OUTPUT_WINKER_R_PORT	(PORTC)
#define OUTPUT_WINKER_R_BIT		(0x01)
#define OUTPUT_WINKER_L_PORT	(PORTC)
#define OUTPUT_WINKER_L_BIT		(0x02)

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
static U08 g_u08PortActiveCount_Ary[ eINPUT_PORT_MAX ];

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
* OverView	: ポート初期化
* Parameter	: None
* Return	: None
*-----------------------------------------------------------------------------*/
void HW_PORT_Initialize( void )
{
	/* ポートA */
	REG_WRITE_08( ANSEL, 0x00 );
	REG_WRITE_08( PORTA, 0x00 );
	REG_WRITE_08( TRISA, 0xC7 );

	/* ポートB */
	REG_RMW_08( OPTION_REG, 0xC0, 0x80 );
	REG_WRITE_08( ANSELH, 0x00 );
	REG_WRITE_08( WPUB, 0x00 );
	REG_WRITE_08( IOCB, 0x00 );
	REG_WRITE_08( PORTB, 0x00 );
	REG_WRITE_08( TRISB, 0x00 );

	/* ポートC */
	REG_WRITE_08( PORTC, 0x00 );
	REG_WRITE_08( TRISC, 0x00 );

	/* ポートE */
	/* DO NOTHING */

	for( E_INPUT_PORT e = eINPUT_PORT_MIN; e < eINPUT_PORT_MAX; e++ ){
		g_u08PortActiveCount_Ary[ e ] = 0;
	}
}

/*------------------------------------------------------------------------------
* OverView	: ポート状態更新
* Parameter	: None
* Return	: None
*-----------------------------------------------------------------------------*/
void HW_PORT_Update( void )
{
	if( REG_READ_08( INPUT_SW_HAZARD_PORT ) & INPUT_SW_HAZARD_BIT ){
		if( g_u08PortActiveCount_Ary[ eINPUT_PORT_HAZARD ] < 0xFF ){
			g_u08PortActiveCount_Ary[ eINPUT_PORT_HAZARD ]++;
		}
	}else{
		g_u08PortActiveCount_Ary[ eINPUT_PORT_HAZARD ] = 0;
	}

	if( REG_READ_08( INPUT_SW_WINKER_R_PORT ) & INPUT_SW_WINKER_R_BIT ){
		if( g_u08PortActiveCount_Ary[ eINPUT_PORT_WINKER_R ] < 0xFF ){
			g_u08PortActiveCount_Ary[ eINPUT_PORT_WINKER_R ]++;
		}
	}else{
		g_u08PortActiveCount_Ary[ eINPUT_PORT_WINKER_R ] = 0;
	}

	if( REG_READ_08( INPUT_SW_WINKER_L_PORT ) & INPUT_SW_WINKER_L_BIT ){
		if( g_u08PortActiveCount_Ary[ eINPUT_PORT_WINKER_L ] < 0xFF ){
			g_u08PortActiveCount_Ary[ eINPUT_PORT_WINKER_L ]++;
		}
	}else{
		g_u08PortActiveCount_Ary[ eINPUT_PORT_WINKER_L ] = 0;
	}
}

/*------------------------------------------------------------------------------
* OverView	: ポート状態取得
* Parameter	: port	: 入力ポート
* Return	: TRUE	: Active
* 			: FALSE	: Not Active
*-----------------------------------------------------------------------------*/
BOOL HW_PORT_IsActive( CE_INPUT_PORT port )
{
	if( g_u08PortActiveCount_Ary[ port ] >= CHATTER_TH ){
		return TRUE;
	}else{
		return FALSE;
	}
}

/*------------------------------------------------------------------------------
* OverView	: ポート出力
* Parameter	: port		: 出力ポート
* 			: isActive	: TRUE:Active FALSE:NotActive
* Return	: None
*-----------------------------------------------------------------------------*/
void HW_PORT_Set( CE_OUTPUT_PORT port, const BOOL isActive )
{
	if( isActive ){
		switch( port ){
		case eOUTPUT_PORT_PWM:
			REG_SET_08( OUTPUT_PWM_PORT, OUTPUT_PWM_BIT );
			break;
		case eOUTPUT_PORT_WINKER_R:
			REG_SET_08( OUTPUT_WINKER_R_PORT, OUTPUT_WINKER_R_BIT );
			break;
		case eOUTPUT_PORT_WINKER_L:
			REG_SET_08( OUTPUT_WINKER_L_PORT, OUTPUT_WINKER_L_BIT );
			break;
		default:
			break;
		}

	}else{
		switch( port ){
		case eOUTPUT_PORT_PWM:
			REG_CLR_08( OUTPUT_PWM_PORT, OUTPUT_PWM_BIT );
			break;
		case eOUTPUT_PORT_WINKER_R:
			REG_CLR_08( OUTPUT_WINKER_R_PORT, OUTPUT_WINKER_R_BIT );
			break;
		case eOUTPUT_PORT_WINKER_L:
			REG_CLR_08( OUTPUT_WINKER_L_PORT, OUTPUT_WINKER_L_BIT );
			break;
		default:
			break;
		}
	}
}


/*------------------------------------------------------------------------------
*	End Of File
*-----------------------------------------------------------------------------*/
