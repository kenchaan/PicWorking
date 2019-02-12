	//MultiRepExp.js
	//Grep結果から正規表現で一気に置換します。
	//複数キーワード置換対応。
	
	var oFileSys = new ActiveXObject("Scripting.FileSystemObject");
	var oShell = new ActiveXObject("WScript.Shell");
	var oVbScript = new ActiveXObject("ScriptControl");
	
	function VbsInputBox(sMessage, sTitle, sDefault){
		oVbScript.Language = "VBScript";
		oVbScript.AddCode("Function InputBox2(sMessage, sTitle, sDefault) InputBox2 = InputBox(sMessage, sTitle, sDefault) End Function");
		var sResult = oVbScript.Run("InputBox2", sMessage, sTitle, sDefault);
		return sResult;
	}
	
	Main();
	
	function Main(){
		Editor.SelectAll(0);
		var sAllText = Editor.GetSelectedString();
		if(sAllText.indexOf("□検索条件") < 0){
			oShell.Popup("Grepを先に実行してください。", 0 , "MultiRepExp");
			return;
		}
	
		//キーワード複数入力
		var aRegExp = new Array();
		while(true){
			var sSearch = VbsInputBox("検索するテキストを入力してください。\n（空欄で次へ進む）", "MultiRepExp", "");
			if(sSearch == null)	return;
			if(sSearch == "")	break;
			var sTransfer = VbsInputBox("置換後のテキストを入力してください。", "MultiRepExp", sSearch);
			if(sTransfer == null)	return;
			var oRegExp = new RegExp(sSearch, "gm");
			oRegExp.sBefore = sSearch;
			oRegExp.sAfter = sTransfer;
			aRegExp.push(oRegExp);
		}
		if(aRegExp.length == 0){
			return;
		}
	
		var sMessage = "置換しますか？\n";
		for(var nLoop = 0; nLoop < aRegExp.length; nLoop++){
			sMessage += "置換前：" + aRegExp[nLoop].sBefore + "\n";
			sMessage += "置換後：" + aRegExp[nLoop].sAfter + "\n";
		}
		if(oShell.Popup(sMessage, 0 , "MultiRepExp", 1) != 1){
			return;
		}
	
		//Grep画面を解析
		var aSearchPath = new Array();
		sAllText = sAllText.substr(sAllText.indexOf("□検索条件"));
		sAllText = sAllText.substr(sAllText.indexOf("\r\n\r\n"));
		var aAllTextLine = sAllText.split("\r\n");
		var oPathCheck = new ActiveXObject("Scripting.Dictionary");
	
		for(var nLoop3 = 0; nLoop3 < aAllTextLine.length; nLoop3++){
			var sLine = aAllTextLine[nLoop3];
			if(sLine.indexOf("  [") >= 0){
				sLine = sLine.substr(0, sLine.indexOf("  [") + 2);
				sLine = sLine.substr(0, sLine.lastIndexOf(((sLine.indexOf(")  ") >= 0)? "(": "  ")));
				if(oFileSys.FileExists(sLine) && !oPathCheck(sLine)){
					oPathCheck(sLine) = true;
					aSearchPath.push(sLine);
				}
			}
		}
	
		//ひたすら置換
		for(var nLoop = 0; nLoop < aSearchPath.length; nLoop++){
			var sPath = aSearchPath[nLoop];
			try{
				var oFile = oFileSys.OpenTextFile(sPath, 1);
				if(oFile.AtEndOfStream){
					oFile.Close();
					continue;
				}
			}
			catch(excep){
				oShell.Popup("読み込みエラーです。\n" + sPath + "\n" + excep, 0 , "MultiRepExp");
				return;
			}
	
			var sText = oFile.ReadAll();
			oFile.Close();
			for(var nLoop4 = 0; nLoop4 < aRegExp.length; nLoop4++){
				var sText = sText.replace(aRegExp[nLoop4], aRegExp[nLoop4].sAfter);
			}
			try{
				var oDestFile = oFileSys.CreateTextFile(sPath, true)
				oDestFile.Write(sText)
				oDestFile.Close();
			}
			catch(excep){
				oShell.Popup("書き込みエラーです。\n" + sPath + "\n" + excep, 0 , "MultiRepExp");
				return;
			}
		}
		oShell.Popup("正常終了しました。", 0 , "MultiRepExp");
	}

