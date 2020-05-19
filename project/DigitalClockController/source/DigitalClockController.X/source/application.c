/*******************************************************************************
*	Author		|	Date		|	FileName
*-------------------------------------------------------------------------------
*	kenchaan	|	2020/05/13	|	application.c
*-------------------------------------------------------------------------------
*	Description	|	�A�v���P�[�V��������
*-------------------------------------------------------------------------------
*	Copyright (c) 2020 kenchaan All Rights Reserved.
*******************************************************************************/

/*------------------------------------------------------------------------------
*	include
*-----------------------------------------------------------------------------*/
#include <xc.h>
#include "types.h"
#include "regaccess.h"
#include "hardware_interrupt.h"
#include "hardware_port.h"
#include "hardware_timer.h"
#include "application.h"

/*------------------------------------------------------------------------------
*	pragma
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
*	static variable
*-----------------------------------------------------------------------------*/
static U08 g_u08DigitData_Ary[ eOUTPUT_PORT_DIGIT_MAX ];
static E_OUTPUT_PORT_DIGIT g_eOutputDigit = eOUTPUT_PORT_DIGIT_MIN;
static U32 g_u32PreTimeCount = 0;

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
* OverView	: �A�v���P�[�V����������
* Parameter	: None
* Return	: None
*-----------------------------------------------------------------------------*/
void APP_Initialize( void )
{
	for( E_OUTPUT_PORT_DIGIT e = eOUTPUT_PORT_DIGIT_MIN; e < eOUTPUT_PORT_DIGIT_MAX; e++ ){
		g_u08DigitData_Ary[ e ] = 0;
	}
}

/*------------------------------------------------------------------------------
* OverView	: �t���[������
* Parameter	: None
* Return	: None
*-----------------------------------------------------------------------------*/
void APP_FrameProcess( void )
{
	U32 count = HW_TIM_GetTimeCount();
	U08 h = (U08)(  (U32)( count / 2 ) / 3600 );
	U08 m = (U08)(( (U32)( count / 2 ) % 3600 ) / 60 );
	U08 s = (U08)(  (U32)( count / 2 ) % 60 );
	U08 ss = (U08)( count % 2 );

	/* �X�C�b�`���� */
	if( HW_PORT_IsActive( eINPUT_PORT_HOUR )){
		h++;
		h %= 24;
	}
	if( HW_PORT_IsActive( eINPUT_PORT_MINUTE )){
		m++;
		m %= 60;
	}
	if( HW_PORT_IsActive( eINPUT_PORT_SECOND_RST )){
		s = 0;
	}
	U32 updated = ( (U32)h * 3600 + (U32)m * 60 + (U32)s ) * 2 + (U32)ss;
	if( updated != count ){
		HW_TIM_SetTimeCount( updated );
	}

	if( g_eOutputDigit == eOUTPUT_PORT_DIGIT_MIN ){
		/* ���ԍX�V */
		U32 count = HW_TIM_GetTimeCount();
		count %= 172800;
		if( count != g_u32PreTimeCount ){
			HW_TIM_SetTimeCount( count );

			g_u08DigitData_Ary[ eOUTPUT_PORT_DIGIT_HOUR_10 ] = (U08)( h / 10 );
			g_u08DigitData_Ary[ eOUTPUT_PORT_DIGIT_HOUR_01 ] = (U08)( h % 10 );
			g_u08DigitData_Ary[ eOUTPUT_PORT_DIGIT_MINUTE_10 ] = (U08)( m / 10 );
			g_u08DigitData_Ary[ eOUTPUT_PORT_DIGIT_MINUTE_01 ] = (U08)( m % 10 );
			g_u08DigitData_Ary[ eOUTPUT_PORT_DIGIT_SECOND_10 ] = (U08)( s / 10 );
			g_u08DigitData_Ary[ eOUTPUT_PORT_DIGIT_SECOND_01 ] = (U08)( s % 10 );

			if( g_u08DigitData_Ary[ eOUTPUT_PORT_DIGIT_HOUR_10 ] == 0 ){
				g_u08DigitData_Ary[ eOUTPUT_PORT_DIGIT_HOUR_10 ] = 20;
			}

			/* �_�� */
			if(( count % 2 ) == 0 ){
				g_u08DigitData_Ary[ eOUTPUT_PORT_DIGIT_HOUR_01 ] += 10;
				g_u08DigitData_Ary[ eOUTPUT_PORT_DIGIT_MINUTE_01 ] += 10;
			}

			g_u32PreTimeCount = count;
		}
	}

	HW_PORT_SetSegData( g_eOutputDigit, g_u08DigitData_Ary[ g_eOutputDigit ]);

	g_eOutputDigit++;
	if( !EXIST_SECOND_DIGITS && ( g_eOutputDigit > eOUTPUT_PORT_DIGIT_MINUTE_01 )){
		g_eOutputDigit = eOUTPUT_PORT_DIGIT_MAX;
	}
	if( g_eOutputDigit >= eOUTPUT_PORT_DIGIT_MAX ){
		g_eOutputDigit = eOUTPUT_PORT_DIGIT_MIN;
	}
}


/*------------------------------------------------------------------------------
*	End Of File
*-----------------------------------------------------------------------------*/
