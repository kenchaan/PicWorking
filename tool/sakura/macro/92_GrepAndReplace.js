	//MultiRepExp.js
	//Grep���ʂ��琳�K�\���ň�C�ɒu�����܂��B
	//�����L�[���[�h�u���Ή��B
	
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
		if(sAllText.indexOf("����������") < 0){
			oShell.Popup("Grep���Ɏ��s���Ă��������B", 0 , "MultiRepExp");
			return;
		}
	
		//�L�[���[�h��������
		var aRegExp = new Array();
		while(true){
			var sSearch = VbsInputBox("��������e�L�X�g����͂��Ă��������B\n�i�󗓂Ŏ��֐i�ށj", "MultiRepExp", "");
			if(sSearch == null)	return;
			if(sSearch == "")	break;
			var sTransfer = VbsInputBox("�u����̃e�L�X�g����͂��Ă��������B", "MultiRepExp", sSearch);
			if(sTransfer == null)	return;
			var oRegExp = new RegExp(sSearch, "gm");
			oRegExp.sBefore = sSearch;
			oRegExp.sAfter = sTransfer;
			aRegExp.push(oRegExp);
		}
		if(aRegExp.length == 0){
			return;
		}
	
		var sMessage = "�u�����܂����H\n";
		for(var nLoop = 0; nLoop < aRegExp.length; nLoop++){
			sMessage += "�u���O�F" + aRegExp[nLoop].sBefore + "\n";
			sMessage += "�u����F" + aRegExp[nLoop].sAfter + "\n";
		}
		if(oShell.Popup(sMessage, 0 , "MultiRepExp", 1) != 1){
			return;
		}
	
		//Grep��ʂ����
		var aSearchPath = new Array();
		sAllText = sAllText.substr(sAllText.indexOf("����������"));
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
	
		//�Ђ�����u��
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
				oShell.Popup("�ǂݍ��݃G���[�ł��B\n" + sPath + "\n" + excep, 0 , "MultiRepExp");
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
				oShell.Popup("�������݃G���[�ł��B\n" + sPath + "\n" + excep, 0 , "MultiRepExp");
				return;
			}
		}
		oShell.Popup("����I�����܂����B", 0 , "MultiRepExp");
	}

