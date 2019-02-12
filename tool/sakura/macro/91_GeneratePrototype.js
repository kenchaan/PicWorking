
		//プロトタイプ宣言自動生成マクロ
		//自身のコーディングルールに対応
		//その他は知りません

		//[a-zA-Z_]+[0-9a-zA-Z_]*[ \t]*(?=\()
		//strName[now] = line.match(/^[a-zA-Z_]+[0-9a-zA-Z_]*[ \t]*[a-zA-Z_]+[0-9a-zA-Z_]*[ \t]*[a-zA-Z_]+[0-9a-zA-Z_]*[ \t]*\(.*\)(?!;)/);
		//globalName[globalNow] = line.match(/^[[a-zA-Z_]+[0-9a-zA-Z_]*[ \t]*]+[a-zA-Z_]+[0-9a-zA-Z_]*[ \t]*\(.*\)(?!;)/)
		//			e.GoLineTop(0);
		//			e.GoLineEnd_Sel();
		//			line = e.GetSelectedString(0);
		//			line = e.Replace(line,'');
		//			line = e.Replace('[\\r\\n]+', '', 4);
		//			line = e.Replace('^[\\r\\n]+', '', 4);


	var e = Editor;
	var strName = new Array();
	var globalName = new Array();
	var objWsh = new ActiveXObject("WScript.Shell");
	var maxLine = GetLineCount(0);
	var now = 0;
	var globalNow = 0;
	var maxElement = 0;

	///* ファイル先頭へ移動 */
	e.GoFileTop;

	do {		///* ファイル先頭から最終行までチェック */
		var line = e.GetLineStr(0);
		if (line.match(/^(static)+[ \t]*[a-zA-Z_]+[0-9a-zA-Z_]*[ \t]*.*[a-zA-Z_]+[0-9a-zA-Z_]*[ \t]*\(.*\)(?!;)[\r\n]/)) {
			///* ファイル内関数 */
			e.GoLineTop(0);
			e.GoLineEnd_Sel();
			line = e.GetSelectedString(0);
			strName[now] = line + ";\r\n";		//←宣言の形で配列に格納する。
			now++;
		} else if (line.match(/^[a-zA-Z_]+[0-9a-zA-Z_]*[ \t]*.*[a-zA-Z_]+[0-9a-zA-Z_]*[ \t]*\(.*\)(?!;)[\r\n]/)) {
			///* ファイル外関数 */
			e.GoLineTop(0);
			e.GoLineEnd_Sel();
			line = e.GetSelectedString(0);
			globalName[globalNow] = line + ";\r\n";		//←宣言の形で配列に格納する。
			globalNow++;
		}
		e.Down();
	} while ( e.ExpandParameter('$y') < maxLine );

	maxElement = now;
	now = 0;

	///* ファイル先頭へ移動 */
	e.GoFileTop;

	///* ファイル内関数が宣言済みかチェック */
	do {		///* ファイル先頭から最終行までチェック */
		var line = e.GetLineStr(0);
		if (line.match(/^(static)+[ \t]*[a-zA-Z_]+[0-9a-zA-Z_]*[ \t]*.*[a-zA-Z_]+[0-9a-zA-Z_]*[ \t]*\(.*\);[\r\n]/)) {
			///* 一致( 宣言されてる ) */
			line = e.Replace(line, '');		///* 消す */
			maxLine--;						///* 最大行数が減る */
			e.Up(0);
		}
		e.Down();
	} while ( e.ExpandParameter('$y') < maxLine );

	///* ファイル先頭へ移動 */
	e.GoFileTop;

	do {
		var line = e.GetLineStr(0);
		if (line.match("static function prototype")){
			///* 宣言の場所を探して */
			break;
		}
		e.Down();
	} while ( e.ExpandParameter('$y') < maxLine );

	///* 書き出す位置を決定 */
	e.Down();
	e.Down();

	do {	///* 先にファイル内関数を書き出す */
		e.InsText(strName[now]);
		now++;
	} while( now < maxElement );

	maxElement = globalNow;
	now = 0;

	if( globalNow != 0 ){
		e.Char(13);
		e.InsText("/*-------------------------------------------------------------------------")
		e.Char(13);
		e.InsText("*	extern function prototype  ヘッダーコピペ用");
		e.Char(13);
		e.InsText("*------------------------------------------------------------------------*/");
		e.Char(13);

		do {	///* その後ファイル外関数を書き出します */
			e.InsText(globalName[now]);
			now++;
		} while( now < globalNow );
	}

	///* 終わり */




