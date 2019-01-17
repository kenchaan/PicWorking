/* JScript	(Tab=4)
 [概要]
	電卓。
	JScriptの eval() をそのまま使用しています。(JScriptのコードがそのまま使えます。)
		記：当初は何げない電卓のつもりでしたが、JScript(JavaScript)の動作を
		ちょっと試したいときにも使えます。
 [使用方法]
	"1+2" と書かれた行でマクロを実行すると、(ダブルクォートは不要)
		1+2
		3
	の様に、結果 "3" が次の行に出力されます。
	"1+2=" の様に、後ろに "=" が付いていても構いません。その場合、"1+2=3" の様に
	"=" の後ろ(正確には行末、範囲選択した場合は選択終了位置)に結果が出力されます。
	範囲選択していない場合は、カーソル行全体が入力として評価され、
	範囲選択した場合は、その選択範囲が入力として評価されます。
		1+2
		*3
	上の2行を選択してマクロを実行すると、
		1+2
		*3
		7
	の様に結果 "7" が出力されます。
	例：
					|	入力					|	結果
		------------+---------------------------+---------------
		全般		|	2*(3+4)					|	14
		π			|	Math.PI					|	3.141592653589793	(PI は大文字。)
					|	PI						|	3.141592653589793	(Math. は省略可。)
					|	pi						|	3.141592653589793	(pi(小文字)は本マクロで用意した変数。)
		平方根		|	Math.sqrt(2)			|	1.4142135623730951
					|	sqrt(2)					|	1.4142135623730951	(Math. は省略可。)
		三角関数	|	Math.sin(Math.PI/2)		|	1		(正弦sin。)
					|	sin(PI/2)				|	1		(Math. は省略可。)
					|	sin(rad(90))			|	1		(rad()は本マクロで用意した関数。)
		べき乗		|	Math.pow(2,10)			|	1024	(2の10乗)
					|	pow(2,10)				|	1024	(Math. は省略可。)
					|	(註：2^10 はべき乗ではなくXOR演算なので 8 になります。(0b0010^0b1010=0b1000))
		16進→10進	|	0x3F					|	63
					|	parseInt("3F",16)		|	63
		10進→16進	|	(63).toString(16)		|	3f
					|	Number(63).toString(16)	|	3f
					|	a=63; a.toString(16)	|	3f
					|	hex(63)					|	0x3F	(hex()は本マクロで用意した関数。)
		2進→10進	|	parseInt("1111",2)		|	15
					|	0b1111					|	15		(0b... は本マクロで用意した2進表記。)
		X進→2進	|	(15).toString(2)		|	1111
					|	(0xF).toString(2)		|	1111
					|	bin(15)					|	0b_1111	(bin()は本マクロで用意した関数。)
					|	bin(15,8)				|	0b_00001111		(第2引数で桁揃え指定。)
					|	bin(0x5A,4,1)			|	0b_0101_1010	(第3引数true で桁区切り有り。)
					|	bin(0x5A,4,0)			|	0b01011010		(第3引数falseで桁区切り無し。)
		URI			|	encodeURI("http://サクラ")
					|							|	http://%E3%82%B5%E3%82%AF%E3%83%A9
					|	decodeURI("http://%E3%82%B5%E3%82%AF%E3%83%A9")
					|							|	http://サクラ
		日付		|	Date()					|	Sat Mar 7 12:34:56 2009	(現在の日時。)
					|	(new Date(2009,3-1,7, 12,34,56)).toLocaleString()	(月は0から始まる。)
					|							|	2009年3月7日 12:34:56
	補足：
		・"Math" は、JScript(JavaScript)のMathオブジェクトです。
		・PI, sqrt(), parseInt(), toString(), decodeURI() など、JScript(JavaScript)の
		  プロパティやメソッド(関数)、オブジェクトはそのまま使えます。
		・JScript(JavaScript)では、大文字・小文字は区別されます。
		・本マクロで用意した変数、関数：
				pi			：π。小文字。Math.PIと同じ。
				0b10110100	："0b" で始まる2進数表記。
				hex(n)		：16進数へ変換。
				bin(n)		：2進数へ変換。
				rad(n)		：度(°)→ラジアン 変換。
				deg(n)		：ラジアン→度(°) 変換。
	評価に失敗した場合は、
		・Microsoft JScript 実行時エラー (または コンパイル エラー)  [Line nnn] ...
		・WSH  実行に失敗しました
	の様なエラーメッセージが出ます。(例外処理(try/catch)は特に行っていません。)
	なお [Line nnn] は本マクロの eval() の行番号のため、意味はありません。
 [変更履歴]
	2009/11/14	入力が "=" で終わる場合、行末(や選択範囲の直後)に結果を挿入する様変更。
				Alt+カーソル や 矩形範囲選択開始(Shift+F6) で矩形選択した場合(Alt+マウスはOK)、
				矩形選択状態のまま結果が挿入され変になるので修正。
	2009/04/23	hex(-1)="0x-1" → "-0x1" となる様修正。
	2009/04/16	矩形範囲選択に対応。(矩形範囲の次の行に結果を挿入する。)
				入力の文字数や行数が長い場合、結果のPopupメッセージ表示に出す入力文字列を切り詰める。
	2009/03/28	bin()に引数追加、戻り値変更(桁区切り文字 "_" を入れた)。
	2009/03/07	新規
*/
 
// メッセージボックスのタイトル
var CAPTION = Editor.ExpandParameter("$M");                        // $M=マクロ名(フルパス)。
CAPTION = CAPTION.substring( CAPTION.lastIndexOf("\\") + 1 );	// ファイル名部分の取り出し。
 
// メッセージボックスを出すのにWshShell.Popup()を使用する。
//	書式(MSDNのWSHより)： intButton = WshShell.Popup(strText,[nSecondsToWait],[strTitle],[nType])
var WshShell = new ActiveXObject("WScript.shell");
 
// 選択範囲の最大文字数 (安全の為、制限する。)
var intSELSTRLEN_MAX = 1024;
 
// 結果を挿入するか (true=結果を挿入する / false=挿入せず、Popupメッセージを表示する)
var blnINSERTRESULT = true;
 
// 結果を挿入する場合でも、結果のPopupメッセージを表示するか (true=する / false=しない)
var blnALWAYSSHOWRESULTPOPUP = false;
 
// "0b0101" の様に "0b" で始まる文字列を2進数として扱うか (true=扱う / false=そのまま)
var blnENABLEBINEXP = true;
 
// bin() の戻り値に、桁区切り文字 "_" を入れるか (true=入れる / false=入れない)
var blnUSE_BIN_DIGITSSEPARATOR = true;
 
// 入力が "=" で終わる場合、行末(や選択範囲の直後)に結果を挿入するか (true=する / false=しない)
//	false の場合、次の行(や選択範囲の直後)に結果と改行を挿入する。
var blnINSERTAFTEREQUAL = true;
 
 
 
//--------------
// メイン
Main();
WshShell = "";		// オブジェクトの解放(? 無くても大丈夫)
 
 
 
function Main()
{
	var codeString;			// eval() の引数。
	var result;				// eval() の結果。
	var blnInsertAfterEqual;// 入力が "=" で終わる場合、行末(や選択範囲の直後)に結果を挿入する。
							// ("=" で終わらない場合、次の行に結果と改行を挿入する。)
	var popupCodeString;	// 結果のPopupメッセージ表示用の入力文字列。
	var numNL, i, c;		// 入力の行数カウント用。(結果のPopupメッセージ表示で使用。)
	var blnInsertResult;	// 結果を挿入するかどうか。
	var EOL;				// 改行文字列。(改行コード(CRLF/CR/LF)の文字列。)
	var ans;				// WshShell.Popup() の戻り値。
	var s;
	
	var pi		= Math.PI;	// 小文字の "pi" を使用可能に。
	
	// 評価する文字列。
	switch( Editor.IsTextSelected() ){
	case 0:
	default:
		// 範囲選択されていない場合、カーソルのある行の文字列を使う。
		codeString = Editor.GetLineStr( 0 );
		break;
	case 1:
	case 2:
		// 範囲選択されている場合、選択範囲の文字列を使う。
		codeString = Editor.GetSelectedString(0);
		break;
	// 矩形範囲選択に対応。
	//case 2:
	//	WshShell.Popup("矩形選択には対応していません。", 0, CAPTION, 48 );
	//	return;
	}
	if( codeString.length > intSELSTRLEN_MAX ){
		ans = WshShell.Popup(
			"文字数が多すぎます。\n" +
			"安全のため、最大 " + intSELSTRLEN_MAX + " 文字に制限しています。" +
			"\n\n続けますか?", 0, CAPTION,
			1|48|256 );			// 1=MB_OKCANCEL, 48=MB_ICONEXCLAMATION, 256=MB_DEFBUTTON2
		if( ans != 1 ) return;	// 1=IDOK
	}
	
	// 入力が "=" で終わる場合、行末(や選択範囲の直後)に結果を挿入する。
	blnInsertAfterEqual = (codeString.search( /=\s*$/ ) != -1) && (blnINSERTAFTEREQUAL);
	
	// "=" で終わる場合、"=" の手前までを取り出す。
	codeString = codeString.replace( /=\s*$/, "" );		// "\s"は空白類。
	
	// "0b0101" の様に "0b" で始まる文字列を2進数として扱う。(数値に変換。)
	if( blnENABLEBINEXP ){
		// bin()の戻り値を、"0b_1011_0100" の様に桁区切り文字 "_" を入れる様に
		// したので、これを扱える様にする。
		//	codeString = codeString.replace( /0[Bb]([01]+)/g,
		//		function( $0, $1 ){ return parseInt( $1, 2 ); } );
		codeString = codeString.replace( /0[Bb]([01_]+)/g,
			function( $0, $1 ){ return parseInt( $1.replace( /_/g, "" ), 2 ); } );
	}
	
	
	//
	// 評価を実行。
	//
	with( Math )	// "Math.sqrt(x)" → "sqrt(x)" の様に "Math." を省略可能にする。
	{
		result = eval( codeString );
	}
	
	// 結果を挿入するかどうか。
	blnInsertResult = blnINSERTRESULT;
	if( (result == undefined)
		|| ((typeof result != "string") && (!isFinite( result )))		// Infinity, NaN (, 他)
		|| ((typeof result == "string") && (result == ""))				// 空文字列
		|| (codeString.length > 1024 )
		|| (Editor.ExpandParameter("${R?読専$:$:$}") == "読専") ){
		// codeString が空文字列や空白類→undefined、0割り→Infinity、引数無しのsqrt()→NaN が返る。
		// この場合、あまり意味が無いので結果は挿入しない。代わりにPopupメッセージを表示する。(その方が親切そう。)
		// エディタが「読み取り専用」の場合も、Popupメッセージを表示する。
		blnInsertResult = false;
	}
	
	// 結果をPopupメッセージ表示する。
	if( (!blnInsertResult) || (blnALWAYSSHOWRESULTPOPUP) ){
		// 結果のPopupメッセージ表示用の入力文字列。
		// 長いと非常に時間が掛かったり、画面内に収まらなかったりするので切り詰める。
		popupCodeString = codeString.substr( 0, 1024 );				// 最大文字数に切り詰める。
		for(numNL=0, i=0;  i < popupCodeString.length;  i++){		// 行数カウント。
			c = popupCodeString.charCodeAt( i );
			if( (c == 0x0D) || (c == 0x0A) ){
				numNL++;
				if( (c == 0x0D) && (popupCodeString.charCodeAt( i + 1 ) == 0x0A) ) i++;
				if( numNL >= 20 ){
					// 入力の行数が長すぎるので、最大行数に切り詰める。
					i++;
					popupCodeString = popupCodeString.substr( 0, i );	// 最大行数に切り詰める。
					break;
				}
			}
		}
		if( popupCodeString.length < codeString.length ){
			popupCodeString += "(...以下略...)";
		}
		WshShell.Popup( "入力 = [" + popupCodeString + "]\n\neval() = [" + result + "]", 0, CAPTION );
	}
	if( !blnInsertResult ) return;
	
	// 結果を挿入する。(方針：Undoは1回で済む様にする。)
	EOL = ["\r\n", "\r", "\n"][ Editor.GetLineCode() ];		// 改行コードの文字列。(CRLF/CR/LF)
	if( Editor.IsTextSelected() != 1 ){		// 範囲選択されていない、または矩形選択の場合。
		// 次の行の先頭に移動。(S_Jump()後の桁位置は行の先頭になる。)
		if( Editor.IsTextSelected() == 2 ){
			// 矩形選択の場合、一旦、選択終了行(折り返し単位)にジャンプ(折り返し単位)。
			Editor.Jump( Editor.GetSelectLineTo(), 0 );
		}
		Editor.CancelMode();		// 選択状態の解除。(矩形範囲選択開始していた場合に必要。)
		Editor.Jump( parseInt( Editor.ExpandParameter("$y") ) +1, 1 );
		if( blnInsertAfterEqual ){
			// "=" で終わる場合、行末に結果を挿入する。(改行は挿入しない。)
			if( Editor.ExpandParameter("$x") == 1 ){		// EOF行でなければ、上の行の行末へ。
				Editor.Left();
			}
			s = "" + result;		// 文字列に変換。(s=result だと "sqrt(2)=" など実数の結果が少し変わる。)
			Editor.InsText( s );
		}else{
			// "=" で終わらない場合、次の行に結果(と改行)を挿入する。
			s = result + EOL;
			Editor.InsText( s );
			Editor.Left();
		}
	}else{									// 範囲選択されている場合。
		if( blnInsertAfterEqual ){
			// "=" で終わる場合、選択範囲の直後に結果を挿入する。(改行は挿入しない。)
			s = Editor.GetSelectedString(0) + result;
			Editor.InsText( s );		// 選択範囲を置き換え。
		}else{
			// "=" で終わらない場合、次の行に結果(と改行)を挿入する。
			if( Editor.GetSelectedString(0).search("[\r\n]$") == -1 ){
				// 改行で終わっていない場合。
				// (選択範囲の直後が改行の場合、1行余分に空く様に見えてしまうが。)
				s = Editor.GetSelectedString(0) + EOL + result + EOL;
			}else{
				// 改行で終わっている場合。
				s = Editor.GetSelectedString(0) + result + EOL;
			}
			Editor.InsText( s );		// 選択範囲を置き換え。
			Editor.Left();
		}
	}
	// 再描画しないと更新状態にならない。([ファイル名(更新)] のようにならない。)
	Editor.Redraw();
}
 
 
function hex( num )		// 16進数へ変換。
{
	//return "0x" + num.toString( 16 ).toUpperCase();
	var s = Math.abs( num ).toString( 16 ).toUpperCase();
	if( s.length & 1 ) s = "0" + s;		// 文字数を偶数化。(0パディング)
	return ((num < 0)? "-" : "") + "0x" + s;
}
 
//	function bin( num )		// 2進数へ変換。
//	{
//		var s = num.toString( 2 );
//		s = "000".substring( (s.length -1) % 4 ) + s;		// 文字数を4文字ずつに。
//		//s = "0000000".substring( (s.length -1) % 8 ) + s;		// 文字数を8文字ずつに。
//		return "0b" + s;
//	}
 
function bin( num, digits, useSeparator )		// 2進数へ変換。
{
	// 引数：
	//	num			：変換元の数値。
	//	digits		：文字数(桁数)をdigits文字ずつにする。(0パディング)
	//					値=1～8。省略時のデフォルトは4。
	//					例：=1		：1→"0b1" (0パディング無し)
	//						=4		：1→"0b0001", 16→"0b00010000"
	//						=8		：1→"0b00000001", 256→"0b0000000100000000"
	//	useSeparator：digits文字毎に、桁区切り文字 "_" を入れて出力するか。(見易さの為。)
	//					値=true / false。(または 非0 / 0 。)
	//					省略時のデフォルトは blnUSE_BIN_DIGITSSEPARATOR 。
	//					例：=false	："0b01011010"
	//						=true	："0b_0101_1010"(digits=4), "0b_01011010"(digits=8)
	// digits 以降の引数は省略可能ですが、省略できるのは後ろからです。
	// 例：bin(65), bin(65,8) は有効。bin(65,,false) はエラー。
	var s;
	if( (typeof digits != "number") || (digits < 1) || (digits > 8) ){
		digits = 4;		// デフォルト値。
	}
	if( typeof useSeparator == "undefined" ){
		useSeparator = blnUSE_BIN_DIGITSSEPARATOR;		// デフォルト値。
	}
	s = Math.abs( num ).toString( 2 );
	// 文字数をdigits文字ずつに。
	s = "0000000".substr( 0, digits - (s.length - 1) % digits - 1 ) + s;
	// digits文字毎に、桁区切り文字 "_" を挿入。(digits=1なら桁区切り無しとしておく。)
	if( (useSeparator) && (digits > 1) ){
		s = s.replace( RegExp( "([01]{" + digits + "})", "g" ),  "_$1" );
	}
	s = "0b" + s;
	if( num < 0 ) s = "-" + s;
	return s;
}
 
function rad( deg )		// 度(°)→ラジアン 変換。
{
	return deg * Math.PI / 180.0;
}
 
function deg( rad )		// ラジアン→度(°) 変換。
{
	return rad / Math.PI * 180.0;
}

