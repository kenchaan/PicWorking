
		//�v���g�^�C�v�錾���������}�N��
		//���g�̃R�[�f�B���O���[���ɑΉ�
		//���̑��͒m��܂���

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

	///* �t�@�C���擪�ֈړ� */
	e.GoFileTop;

	do {		///* �t�@�C���擪����ŏI�s�܂Ń`�F�b�N */
		var line = e.GetLineStr(0);
		if (line.match(/^(static)+[ \t]*[a-zA-Z_]+[0-9a-zA-Z_]*[ \t]*.*[a-zA-Z_]+[0-9a-zA-Z_]*[ \t]*\(.*\)(?!;)[\r\n]/)) {
			///* �t�@�C�����֐� */
			e.GoLineTop(0);
			e.GoLineEnd_Sel();
			line = e.GetSelectedString(0);
			strName[now] = line + ";\r\n";		//���錾�̌`�Ŕz��Ɋi�[����B
			now++;
		} else if (line.match(/^[a-zA-Z_]+[0-9a-zA-Z_]*[ \t]*.*[a-zA-Z_]+[0-9a-zA-Z_]*[ \t]*\(.*\)(?!;)[\r\n]/)) {
			///* �t�@�C���O�֐� */
			e.GoLineTop(0);
			e.GoLineEnd_Sel();
			line = e.GetSelectedString(0);
			globalName[globalNow] = line + ";\r\n";		//���錾�̌`�Ŕz��Ɋi�[����B
			globalNow++;
		}
		e.Down();
	} while ( e.ExpandParameter('$y') < maxLine );

	maxElement = now;
	now = 0;

	///* �t�@�C���擪�ֈړ� */
	e.GoFileTop;

	///* �t�@�C�����֐����錾�ς݂��`�F�b�N */
	do {		///* �t�@�C���擪����ŏI�s�܂Ń`�F�b�N */
		var line = e.GetLineStr(0);
		if (line.match(/^(static)+[ \t]*[a-zA-Z_]+[0-9a-zA-Z_]*[ \t]*.*[a-zA-Z_]+[0-9a-zA-Z_]*[ \t]*\(.*\);[\r\n]/)) {
			///* ��v( �錾����Ă� ) */
			line = e.Replace(line, '');		///* ���� */
			maxLine--;						///* �ő�s�������� */
			e.Up(0);
		}
		e.Down();
	} while ( e.ExpandParameter('$y') < maxLine );

	///* �t�@�C���擪�ֈړ� */
	e.GoFileTop;

	do {
		var line = e.GetLineStr(0);
		if (line.match("static function prototype")){
			///* �錾�̏ꏊ��T���� */
			break;
		}
		e.Down();
	} while ( e.ExpandParameter('$y') < maxLine );

	///* �����o���ʒu������ */
	e.Down();
	e.Down();

	do {	///* ��Ƀt�@�C�����֐��������o�� */
		e.InsText(strName[now]);
		now++;
	} while( now < maxElement );

	maxElement = globalNow;
	now = 0;

	if( globalNow != 0 ){
		e.Char(13);
		e.InsText("/*-------------------------------------------------------------------------")
		e.Char(13);
		e.InsText("*	extern function prototype  �w�b�_�[�R�s�y�p");
		e.Char(13);
		e.InsText("*------------------------------------------------------------------------*/");
		e.Char(13);

		do {	///* ���̌�t�@�C���O�֐��������o���܂� */
			e.InsText(globalName[now]);
			now++;
		} while( now < globalNow );
	}

	///* �I��� */




