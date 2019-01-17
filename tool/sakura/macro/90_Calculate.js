/* JScript	(Tab=4)
 [�T�v]
	�d��B
	JScript�� eval() �����̂܂܎g�p���Ă��܂��B(JScript�̃R�[�h�����̂܂܎g���܂��B)
		�L�F�����͉����Ȃ��d��̂���ł������AJScript(JavaScript)�̓����
		������Ǝ��������Ƃ��ɂ��g���܂��B
 [�g�p���@]
	"1+2" �Ə����ꂽ�s�Ń}�N�������s����ƁA(�_�u���N�H�[�g�͕s�v)
		1+2
		3
	�̗l�ɁA���� "3" �����̍s�ɏo�͂���܂��B
	"1+2=" �̗l�ɁA���� "=" ���t���Ă��Ă��\���܂���B���̏ꍇ�A"1+2=3" �̗l��
	"=" �̌��(���m�ɂ͍s���A�͈͑I�������ꍇ�͑I���I���ʒu)�Ɍ��ʂ��o�͂���܂��B
	�͈͑I�����Ă��Ȃ��ꍇ�́A�J�[�\���s�S�̂����͂Ƃ��ĕ]������A
	�͈͑I�������ꍇ�́A���̑I��͈͂����͂Ƃ��ĕ]������܂��B
		1+2
		*3
	���2�s��I�����ă}�N�������s����ƁA
		1+2
		*3
		7
	�̗l�Ɍ��� "7" ���o�͂���܂��B
	��F
					|	����					|	����
		------------+---------------------------+---------------
		�S��		|	2*(3+4)					|	14
		��			|	Math.PI					|	3.141592653589793	(PI �͑啶���B)
					|	PI						|	3.141592653589793	(Math. �͏ȗ��B)
					|	pi						|	3.141592653589793	(pi(������)�͖{�}�N���ŗp�ӂ����ϐ��B)
		������		|	Math.sqrt(2)			|	1.4142135623730951
					|	sqrt(2)					|	1.4142135623730951	(Math. �͏ȗ��B)
		�O�p�֐�	|	Math.sin(Math.PI/2)		|	1		(����sin�B)
					|	sin(PI/2)				|	1		(Math. �͏ȗ��B)
					|	sin(rad(90))			|	1		(rad()�͖{�}�N���ŗp�ӂ����֐��B)
		�ׂ���		|	Math.pow(2,10)			|	1024	(2��10��)
					|	pow(2,10)				|	1024	(Math. �͏ȗ��B)
					|	(���F2^10 �ׂ͂���ł͂Ȃ�XOR���Z�Ȃ̂� 8 �ɂȂ�܂��B(0b0010^0b1010=0b1000))
		16�i��10�i	|	0x3F					|	63
					|	parseInt("3F",16)		|	63
		10�i��16�i	|	(63).toString(16)		|	3f
					|	Number(63).toString(16)	|	3f
					|	a=63; a.toString(16)	|	3f
					|	hex(63)					|	0x3F	(hex()�͖{�}�N���ŗp�ӂ����֐��B)
		2�i��10�i	|	parseInt("1111",2)		|	15
					|	0b1111					|	15		(0b... �͖{�}�N���ŗp�ӂ���2�i�\�L�B)
		X�i��2�i	|	(15).toString(2)		|	1111
					|	(0xF).toString(2)		|	1111
					|	bin(15)					|	0b_1111	(bin()�͖{�}�N���ŗp�ӂ����֐��B)
					|	bin(15,8)				|	0b_00001111		(��2�����Ō������w��B)
					|	bin(0x5A,4,1)			|	0b_0101_1010	(��3����true �Ō���؂�L��B)
					|	bin(0x5A,4,0)			|	0b01011010		(��3����false�Ō���؂薳���B)
		URI			|	encodeURI("http://�T�N��")
					|							|	http://%E3%82%B5%E3%82%AF%E3%83%A9
					|	decodeURI("http://%E3%82%B5%E3%82%AF%E3%83%A9")
					|							|	http://�T�N��
		���t		|	Date()					|	Sat Mar 7 12:34:56 2009	(���݂̓����B)
					|	(new Date(2009,3-1,7, 12,34,56)).toLocaleString()	(����0����n�܂�B)
					|							|	2009�N3��7�� 12:34:56
	�⑫�F
		�E"Math" �́AJScript(JavaScript)��Math�I�u�W�F�N�g�ł��B
		�EPI, sqrt(), parseInt(), toString(), decodeURI() �ȂǁAJScript(JavaScript)��
		  �v���p�e�B�⃁�\�b�h(�֐�)�A�I�u�W�F�N�g�͂��̂܂܎g���܂��B
		�EJScript(JavaScript)�ł́A�啶���E�������͋�ʂ���܂��B
		�E�{�}�N���ŗp�ӂ����ϐ��A�֐��F
				pi			�F�΁B�������BMath.PI�Ɠ����B
				0b10110100	�F"0b" �Ŏn�܂�2�i���\�L�B
				hex(n)		�F16�i���֕ϊ��B
				bin(n)		�F2�i���֕ϊ��B
				rad(n)		�F�x(��)�����W�A�� �ϊ��B
				deg(n)		�F���W�A�����x(��) �ϊ��B
	�]���Ɏ��s�����ꍇ�́A
		�EMicrosoft JScript ���s���G���[ (�܂��� �R���p�C�� �G���[)  [Line nnn] ...
		�EWSH  ���s�Ɏ��s���܂���
	�̗l�ȃG���[���b�Z�[�W���o�܂��B(��O����(try/catch)�͓��ɍs���Ă��܂���B)
	�Ȃ� [Line nnn] �͖{�}�N���� eval() �̍s�ԍ��̂��߁A�Ӗ��͂���܂���B
 [�ύX����]
	2009/11/14	���͂� "=" �ŏI���ꍇ�A�s��(��I��͈͂̒���)�Ɍ��ʂ�}������l�ύX�B
				Alt+�J�[�\�� �� ��`�͈͑I���J�n(Shift+F6) �ŋ�`�I�������ꍇ(Alt+�}�E�X��OK)�A
				��`�I����Ԃ̂܂܌��ʂ��}������ςɂȂ�̂ŏC���B
	2009/04/23	hex(-1)="0x-1" �� "-0x1" �ƂȂ�l�C���B
	2009/04/16	��`�͈͑I���ɑΉ��B(��`�͈͂̎��̍s�Ɍ��ʂ�}������B)
				���͂̕�������s���������ꍇ�A���ʂ�Popup���b�Z�[�W�\���ɏo�����͕������؂�l�߂�B
	2009/03/28	bin()�Ɉ����ǉ��A�߂�l�ύX(����؂蕶�� "_" ����ꂽ)�B
	2009/03/07	�V�K
*/
 
// ���b�Z�[�W�{�b�N�X�̃^�C�g��
var CAPTION = Editor.ExpandParameter("$M");                        // $M=�}�N����(�t���p�X)�B
CAPTION = CAPTION.substring( CAPTION.lastIndexOf("\\") + 1 );	// �t�@�C���������̎��o���B
 
// ���b�Z�[�W�{�b�N�X���o���̂�WshShell.Popup()���g�p����B
//	����(MSDN��WSH���)�F intButton = WshShell.Popup(strText,[nSecondsToWait],[strTitle],[nType])
var WshShell = new ActiveXObject("WScript.shell");
 
// �I��͈͂̍ő啶���� (���S�ׁ̈A��������B)
var intSELSTRLEN_MAX = 1024;
 
// ���ʂ�}�����邩 (true=���ʂ�}������ / false=�}�������APopup���b�Z�[�W��\������)
var blnINSERTRESULT = true;
 
// ���ʂ�}������ꍇ�ł��A���ʂ�Popup���b�Z�[�W��\�����邩 (true=���� / false=���Ȃ�)
var blnALWAYSSHOWRESULTPOPUP = false;
 
// "0b0101" �̗l�� "0b" �Ŏn�܂镶�����2�i���Ƃ��Ĉ����� (true=���� / false=���̂܂�)
var blnENABLEBINEXP = true;
 
// bin() �̖߂�l�ɁA����؂蕶�� "_" �����邩 (true=����� / false=����Ȃ�)
var blnUSE_BIN_DIGITSSEPARATOR = true;
 
// ���͂� "=" �ŏI���ꍇ�A�s��(��I��͈͂̒���)�Ɍ��ʂ�}�����邩 (true=���� / false=���Ȃ�)
//	false �̏ꍇ�A���̍s(��I��͈͂̒���)�Ɍ��ʂƉ��s��}������B
var blnINSERTAFTEREQUAL = true;
 
 
 
//--------------
// ���C��
Main();
WshShell = "";		// �I�u�W�F�N�g�̉��(? �����Ă����v)
 
 
 
function Main()
{
	var codeString;			// eval() �̈����B
	var result;				// eval() �̌��ʁB
	var blnInsertAfterEqual;// ���͂� "=" �ŏI���ꍇ�A�s��(��I��͈͂̒���)�Ɍ��ʂ�}������B
							// ("=" �ŏI���Ȃ��ꍇ�A���̍s�Ɍ��ʂƉ��s��}������B)
	var popupCodeString;	// ���ʂ�Popup���b�Z�[�W�\���p�̓��͕�����B
	var numNL, i, c;		// ���͂̍s���J�E���g�p�B(���ʂ�Popup���b�Z�[�W�\���Ŏg�p�B)
	var blnInsertResult;	// ���ʂ�}�����邩�ǂ����B
	var EOL;				// ���s������B(���s�R�[�h(CRLF/CR/LF)�̕�����B)
	var ans;				// WshShell.Popup() �̖߂�l�B
	var s;
	
	var pi		= Math.PI;	// �������� "pi" ���g�p�\�ɁB
	
	// �]�����镶����B
	switch( Editor.IsTextSelected() ){
	case 0:
	default:
		// �͈͑I������Ă��Ȃ��ꍇ�A�J�[�\���̂���s�̕�������g���B
		codeString = Editor.GetLineStr( 0 );
		break;
	case 1:
	case 2:
		// �͈͑I������Ă���ꍇ�A�I��͈͂̕�������g���B
		codeString = Editor.GetSelectedString(0);
		break;
	// ��`�͈͑I���ɑΉ��B
	//case 2:
	//	WshShell.Popup("��`�I���ɂ͑Ή����Ă��܂���B", 0, CAPTION, 48 );
	//	return;
	}
	if( codeString.length > intSELSTRLEN_MAX ){
		ans = WshShell.Popup(
			"���������������܂��B\n" +
			"���S�̂��߁A�ő� " + intSELSTRLEN_MAX + " �����ɐ������Ă��܂��B" +
			"\n\n�����܂���?", 0, CAPTION,
			1|48|256 );			// 1=MB_OKCANCEL, 48=MB_ICONEXCLAMATION, 256=MB_DEFBUTTON2
		if( ans != 1 ) return;	// 1=IDOK
	}
	
	// ���͂� "=" �ŏI���ꍇ�A�s��(��I��͈͂̒���)�Ɍ��ʂ�}������B
	blnInsertAfterEqual = (codeString.search( /=\s*$/ ) != -1) && (blnINSERTAFTEREQUAL);
	
	// "=" �ŏI���ꍇ�A"=" �̎�O�܂ł����o���B
	codeString = codeString.replace( /=\s*$/, "" );		// "\s"�͋󔒗ށB
	
	// "0b0101" �̗l�� "0b" �Ŏn�܂镶�����2�i���Ƃ��Ĉ����B(���l�ɕϊ��B)
	if( blnENABLEBINEXP ){
		// bin()�̖߂�l���A"0b_1011_0100" �̗l�Ɍ���؂蕶�� "_" ������l��
		// �����̂ŁA�����������l�ɂ���B
		//	codeString = codeString.replace( /0[Bb]([01]+)/g,
		//		function( $0, $1 ){ return parseInt( $1, 2 ); } );
		codeString = codeString.replace( /0[Bb]([01_]+)/g,
			function( $0, $1 ){ return parseInt( $1.replace( /_/g, "" ), 2 ); } );
	}
	
	
	//
	// �]�������s�B
	//
	with( Math )	// "Math.sqrt(x)" �� "sqrt(x)" �̗l�� "Math." ���ȗ��\�ɂ���B
	{
		result = eval( codeString );
	}
	
	// ���ʂ�}�����邩�ǂ����B
	blnInsertResult = blnINSERTRESULT;
	if( (result == undefined)
		|| ((typeof result != "string") && (!isFinite( result )))		// Infinity, NaN (, ��)
		|| ((typeof result == "string") && (result == ""))				// �󕶎���
		|| (codeString.length > 1024 )
		|| (Editor.ExpandParameter("${R?�ǐ�$:$:$}") == "�ǐ�") ){
		// codeString ���󕶎����󔒗ށ�undefined�A0���聨Infinity�A����������sqrt()��NaN ���Ԃ�B
		// ���̏ꍇ�A���܂�Ӗ��������̂Ō��ʂ͑}�����Ȃ��B�����Popup���b�Z�[�W��\������B(���̕����e�؂����B)
		// �G�f�B�^���u�ǂݎ���p�v�̏ꍇ���APopup���b�Z�[�W��\������B
		blnInsertResult = false;
	}
	
	// ���ʂ�Popup���b�Z�[�W�\������B
	if( (!blnInsertResult) || (blnALWAYSSHOWRESULTPOPUP) ){
		// ���ʂ�Popup���b�Z�[�W�\���p�̓��͕�����B
		// �����Ɣ��Ɏ��Ԃ��|��������A��ʓ��Ɏ��܂�Ȃ������肷��̂Ő؂�l�߂�B
		popupCodeString = codeString.substr( 0, 1024 );				// �ő啶�����ɐ؂�l�߂�B
		for(numNL=0, i=0;  i < popupCodeString.length;  i++){		// �s���J�E���g�B
			c = popupCodeString.charCodeAt( i );
			if( (c == 0x0D) || (c == 0x0A) ){
				numNL++;
				if( (c == 0x0D) && (popupCodeString.charCodeAt( i + 1 ) == 0x0A) ) i++;
				if( numNL >= 20 ){
					// ���͂̍s������������̂ŁA�ő�s���ɐ؂�l�߂�B
					i++;
					popupCodeString = popupCodeString.substr( 0, i );	// �ő�s���ɐ؂�l�߂�B
					break;
				}
			}
		}
		if( popupCodeString.length < codeString.length ){
			popupCodeString += "(...�ȉ���...)";
		}
		WshShell.Popup( "���� = [" + popupCodeString + "]\n\neval() = [" + result + "]", 0, CAPTION );
	}
	if( !blnInsertResult ) return;
	
	// ���ʂ�}������B(���j�FUndo��1��ōςޗl�ɂ���B)
	EOL = ["\r\n", "\r", "\n"][ Editor.GetLineCode() ];		// ���s�R�[�h�̕�����B(CRLF/CR/LF)
	if( Editor.IsTextSelected() != 1 ){		// �͈͑I������Ă��Ȃ��A�܂��͋�`�I���̏ꍇ�B
		// ���̍s�̐擪�Ɉړ��B(S_Jump()��̌��ʒu�͍s�̐擪�ɂȂ�B)
		if( Editor.IsTextSelected() == 2 ){
			// ��`�I���̏ꍇ�A��U�A�I���I���s(�܂�Ԃ��P��)�ɃW�����v(�܂�Ԃ��P��)�B
			Editor.Jump( Editor.GetSelectLineTo(), 0 );
		}
		Editor.CancelMode();		// �I����Ԃ̉����B(��`�͈͑I���J�n���Ă����ꍇ�ɕK�v�B)
		Editor.Jump( parseInt( Editor.ExpandParameter("$y") ) +1, 1 );
		if( blnInsertAfterEqual ){
			// "=" �ŏI���ꍇ�A�s���Ɍ��ʂ�}������B(���s�͑}�����Ȃ��B)
			if( Editor.ExpandParameter("$x") == 1 ){		// EOF�s�łȂ���΁A��̍s�̍s���ցB
				Editor.Left();
			}
			s = "" + result;		// ������ɕϊ��B(s=result ���� "sqrt(2)=" �Ȃǎ����̌��ʂ������ς��B)
			Editor.InsText( s );
		}else{
			// "=" �ŏI���Ȃ��ꍇ�A���̍s�Ɍ���(�Ɖ��s)��}������B
			s = result + EOL;
			Editor.InsText( s );
			Editor.Left();
		}
	}else{									// �͈͑I������Ă���ꍇ�B
		if( blnInsertAfterEqual ){
			// "=" �ŏI���ꍇ�A�I��͈͂̒���Ɍ��ʂ�}������B(���s�͑}�����Ȃ��B)
			s = Editor.GetSelectedString(0) + result;
			Editor.InsText( s );		// �I��͈͂�u�������B
		}else{
			// "=" �ŏI���Ȃ��ꍇ�A���̍s�Ɍ���(�Ɖ��s)��}������B
			if( Editor.GetSelectedString(0).search("[\r\n]$") == -1 ){
				// ���s�ŏI����Ă��Ȃ��ꍇ�B
				// (�I��͈͂̒��オ���s�̏ꍇ�A1�s�]���ɋ󂭗l�Ɍ����Ă��܂����B)
				s = Editor.GetSelectedString(0) + EOL + result + EOL;
			}else{
				// ���s�ŏI����Ă���ꍇ�B
				s = Editor.GetSelectedString(0) + result + EOL;
			}
			Editor.InsText( s );		// �I��͈͂�u�������B
			Editor.Left();
		}
	}
	// �ĕ`�悵�Ȃ��ƍX�V��ԂɂȂ�Ȃ��B([�t�@�C����(�X�V)] �̂悤�ɂȂ�Ȃ��B)
	Editor.Redraw();
}
 
 
function hex( num )		// 16�i���֕ϊ��B
{
	//return "0x" + num.toString( 16 ).toUpperCase();
	var s = Math.abs( num ).toString( 16 ).toUpperCase();
	if( s.length & 1 ) s = "0" + s;		// ���������������B(0�p�f�B���O)
	return ((num < 0)? "-" : "") + "0x" + s;
}
 
//	function bin( num )		// 2�i���֕ϊ��B
//	{
//		var s = num.toString( 2 );
//		s = "000".substring( (s.length -1) % 4 ) + s;		// ��������4�������ɁB
//		//s = "0000000".substring( (s.length -1) % 8 ) + s;		// ��������8�������ɁB
//		return "0b" + s;
//	}
 
function bin( num, digits, useSeparator )		// 2�i���֕ϊ��B
{
	// �����F
	//	num			�F�ϊ����̐��l�B
	//	digits		�F������(����)��digits�������ɂ���B(0�p�f�B���O)
	//					�l=1�`8�B�ȗ����̃f�t�H���g��4�B
	//					��F=1		�F1��"0b1" (0�p�f�B���O����)
	//						=4		�F1��"0b0001", 16��"0b00010000"
	//						=8		�F1��"0b00000001", 256��"0b0000000100000000"
	//	useSeparator�Fdigits�������ɁA����؂蕶�� "_" �����ďo�͂��邩�B(���Ղ��ׁ̈B)
	//					�l=true / false�B(�܂��� ��0 / 0 �B)
	//					�ȗ����̃f�t�H���g�� blnUSE_BIN_DIGITSSEPARATOR �B
	//					��F=false	�F"0b01011010"
	//						=true	�F"0b_0101_1010"(digits=4), "0b_01011010"(digits=8)
	// digits �ȍ~�̈����͏ȗ��\�ł����A�ȗ��ł���̂͌�납��ł��B
	// ��Fbin(65), bin(65,8) �͗L���Bbin(65,,false) �̓G���[�B
	var s;
	if( (typeof digits != "number") || (digits < 1) || (digits > 8) ){
		digits = 4;		// �f�t�H���g�l�B
	}
	if( typeof useSeparator == "undefined" ){
		useSeparator = blnUSE_BIN_DIGITSSEPARATOR;		// �f�t�H���g�l�B
	}
	s = Math.abs( num ).toString( 2 );
	// ��������digits�������ɁB
	s = "0000000".substr( 0, digits - (s.length - 1) % digits - 1 ) + s;
	// digits�������ɁA����؂蕶�� "_" ��}���B(digits=1�Ȃ猅��؂薳���Ƃ��Ă����B)
	if( (useSeparator) && (digits > 1) ){
		s = s.replace( RegExp( "([01]{" + digits + "})", "g" ),  "_$1" );
	}
	s = "0b" + s;
	if( num < 0 ) s = "-" + s;
	return s;
}
 
function rad( deg )		// �x(��)�����W�A�� �ϊ��B
{
	return deg * Math.PI / 180.0;
}
 
function deg( rad )		// ���W�A�����x(��) �ϊ��B
{
	return rad / Math.PI * 180.0;
}

