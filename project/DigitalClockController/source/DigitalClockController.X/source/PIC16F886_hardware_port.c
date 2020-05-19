/*******************************************************************************
*	Author		|	Date		|	FileName
*-------------------------------------------------------------------------------
*	kenchaan	|	2020/05/13	|	PIC16F886_hardware_port.c
*-------------------------------------------------------------------------------
*	Description	|	[PIC16F886]�|�[�g����
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
#define COUNTER_MAX				(1000)

#define CHATTER_TH				(3)
#define CONTINUE_TH				(200)
#define CONTINUE_INTERVAL		(10)

#define SW_HOUR_PORT			(PORTA)
#define SW_HOUR_BIT				(0x01)
#define SW_MINUTE_PORT			(PORTA)
#define SW_MINUTE_BIT			(0x02)
#define SW_SECOND_RST_PORT		(PORTA)
#define SW_SECOND_RST_BIT		(0x04)

#define ERROR_PROC_FAIL_PORT	(PORTA)
#define ERROR_PROC_FAIL_BIT		(0x20)

#define DIGIT_H10_PORT			(PORTC)
#define DIGIT_H10_BIT			(0x04)
#define DIGIT_H01_PORT			(PORTC)
#define DIGIT_H01_BIT			(0x08)
#define DIGIT_M10_PORT			(PORTC)
#define DIGIT_M10_BIT			(0x10)
#define DIGIT_M01_PORT			(PORTC)
#define DIGIT_M01_BIT			(0x20)
#define DIGIT_S10_PORT			(PORTC)
#define DIGIT_S10_BIT			(0x40)
#define DIGIT_S01_PORT			(PORTC)
#define DIGIT_S01_BIT			(0x80)

#define SEG_DATA_PORT			(PORTB)

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
static U16 g_u16PortActiveCount_Ary[ eINPUT_PORT_MAX ];

/*------------------------------------------------------------------------------
*	static function prototype
*-----------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------
*	static const data
*-----------------------------------------------------------------------------*/
static const U08 g_cu08SegData_Ary[ 22 ] = {
	0x3F,	/* 0  */
	0x06,	/* 1  */
	0x5B,	/* 2  */
	0x4F,	/* 3  */
	0x66,	/* 4  */
	0x6D,	/* 5  */
	0x7D,	/* 6  */
	0x27,	/* 7  */
	0x7F,	/* 8  */
	0x6F,	/* 9  */
	0xBF,	/* 0: */
	0x86,	/* 1: */
	0xDB,	/* 2: */
	0xCF,	/* 3: */
	0xE6,	/* 4: */
	0xED,	/* 5: */
	0xFD,	/* 6: */
	0xA7,	/* 7: */
	0xFF,	/* 8: */
	0xEF,	/* 9: */
	0x00,	/*    */
	0x80	/*  : */
};

/*------------------------------------------------------------------------------
*	extern const data
*-----------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------
*	function
*-----------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
* OverView	: �|�[�g������
* Parameter	: None
* Return	: None
*-----------------------------------------------------------------------------*/
void HW_PORT_Initialize( void )
{
	/* �|�[�gA */
	REG_WRITE_08( ANSEL, 0x00 );
	REG_WRITE_08( PORTA, 0x00 );
	REG_WRITE_08( TRISA, 0xC7 );

	/* �|�[�gB */
	REG_RMW_08( OPTION_REG, 0xC0, 0x80 );
	REG_WRITE_08( ANSELH, 0x00 );
	REG_WRITE_08( WPUB, 0x00 );
	REG_WRITE_08( IOCB, 0x00 );
	REG_WRITE_08( PORTB, 0x00 );
	REG_WRITE_08( TRISB, 0x00 );

	/* �|�[�gC */
	REG_WRITE_08( PORTC, 0x00 );
	REG_WRITE_08( TRISC, 0x03 );

	/* �|�[�gE */
	/* DO NOTHING */

	for( E_INPUT_PORT e = eINPUT_PORT_MIN; e < eINPUT_PORT_MAX; e++ ){
		g_u16PortActiveCount_Ary[ e ] = 0;
	}
}

/*------------------------------------------------------------------------------
* OverView	: �|�[�g��ԍX�V
* Parameter	: None
* Return	: None
*-----------------------------------------------------------------------------*/
void HW_PORT_Update( void )
{
	if( REG_READ_08( SW_HOUR_PORT ) & SW_HOUR_BIT ){
		g_u16PortActiveCount_Ary[ eINPUT_PORT_HOUR ]++;
		g_u16PortActiveCount_Ary[ eINPUT_PORT_HOUR ] %= COUNTER_MAX;
	}else{
		g_u16PortActiveCount_Ary[ eINPUT_PORT_HOUR ] = 0;
	}

	if( REG_READ_08( SW_MINUTE_PORT ) & SW_MINUTE_BIT ){
		g_u16PortActiveCount_Ary[ eINPUT_PORT_MINUTE ]++;
		g_u16PortActiveCount_Ary[ eINPUT_PORT_MINUTE ] %= COUNTER_MAX;
	}else{
		g_u16PortActiveCount_Ary[ eINPUT_PORT_MINUTE ] = 0;
	}

	if( REG_READ_08( SW_SECOND_RST_PORT ) & SW_SECOND_RST_BIT ){
		g_u16PortActiveCount_Ary[ eINPUT_PORT_SECOND_RST ]++;
		g_u16PortActiveCount_Ary[ eINPUT_PORT_SECOND_RST ] %= COUNTER_MAX;
	}else{
		g_u16PortActiveCount_Ary[ eINPUT_PORT_SECOND_RST ] = 0;
	}
}

/*------------------------------------------------------------------------------
* OverView	: �|�[�g��Ԏ擾
* Parameter	: port	: ���̓|�[�g
* Return	: TRUE	: Active
* 			: FALSE	: Not Active
*-----------------------------------------------------------------------------*/
BOOL HW_PORT_IsActive( CE_INPUT_PORT port )
{
	if( g_u16PortActiveCount_Ary[ port ] == CHATTER_TH ){
		return TRUE;
	}else if( g_u16PortActiveCount_Ary[ port ] >= CONTINUE_TH ){
		g_u16PortActiveCount_Ary[ port ] -= CONTINUE_INTERVAL;
		return TRUE;
	}

	return FALSE;
}

/*------------------------------------------------------------------------------
* OverView	: �|�[�g�o��
* Parameter	: port		: �o�̓|�[�g
* 			: isActive	: TRUE:Active FALSE:NotActive
* Return	: None
*-----------------------------------------------------------------------------*/
void HW_PORT_Set( CE_OUTPUT_PORT port, const BOOL isActive )
{
	if( isActive ){
		switch( port ){
		case eOUTPUT_PORT_ERROR_PROC_FAIL:
			REG_SET_08( ERROR_PROC_FAIL_PORT, ERROR_PROC_FAIL_BIT );
			break;
		default:
			break;
		}
	}else{
		switch( port ){
		case eOUTPUT_PORT_ERROR_PROC_FAIL:
			REG_CLR_08( ERROR_PROC_FAIL_PORT, ERROR_PROC_FAIL_BIT );
			break;
		default:
			break;
		}
	}
}

/*------------------------------------------------------------------------------
* OverView	: �Z�O�����g�f�[�^�o��
* Parameter	: digit	: �o�͌�
* 			: data	: �o�̓f�[�^
* Return	: None
*-----------------------------------------------------------------------------*/
void HW_PORT_SetSegData( CE_OUTPUT_PORT_DIGIT digit, const U08 data )
{
	if( data >= 22 ){
		return;
	}

	/* ���� */
	REG_CLR_08( DIGIT_H10_PORT, DIGIT_H10_BIT );
	REG_CLR_08( DIGIT_H01_PORT, DIGIT_H01_BIT );
	REG_CLR_08( DIGIT_M10_PORT, DIGIT_M10_BIT );
	REG_CLR_08( DIGIT_M01_PORT, DIGIT_M01_BIT );
	REG_CLR_08( DIGIT_S10_PORT, DIGIT_S10_BIT );
	REG_CLR_08( DIGIT_S01_PORT, DIGIT_S01_BIT );

	/* �f�[�^�Z�b�g */
	REG_WRITE_08( SEG_DATA_PORT, g_cu08SegData_Ary[ data ] );

	/* �_�� */
	switch( digit ){
	case eOUTPUT_PORT_DIGIT_HOUR_10:
		REG_SET_08( DIGIT_H10_PORT, DIGIT_H10_BIT );
		break;
	case eOUTPUT_PORT_DIGIT_HOUR_01:
		REG_SET_08( DIGIT_H01_PORT, DIGIT_H01_BIT );
		break;
	case eOUTPUT_PORT_DIGIT_MINUTE_10:
		REG_SET_08( DIGIT_M10_PORT, DIGIT_M10_BIT );
		break;
	case eOUTPUT_PORT_DIGIT_MINUTE_01:
		REG_SET_08( DIGIT_M01_PORT, DIGIT_M01_BIT );
		break;
	case eOUTPUT_PORT_DIGIT_SECOND_10:
		REG_SET_08( DIGIT_S10_PORT, DIGIT_S10_BIT );
		break;
	case eOUTPUT_PORT_DIGIT_SECOND_01:
		REG_SET_08( DIGIT_S01_PORT, DIGIT_S01_BIT );
		break;
	default:
		break;
	}
}


/*------------------------------------------------------------------------------
*	End Of File
*-----------------------------------------------------------------------------*/
