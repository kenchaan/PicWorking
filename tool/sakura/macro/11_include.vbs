

'�֐��T�v�e���v���[�g�쐬�}�N��

'    �}�N���e���v��
'    x = ""&vbCrLf 
'    x = x &""&vbCrLf

'�ϐ��錾
Dim x
Dim y

'���t�擾
y = ExpandParameter("$d")
z = Chr(34)		' "(�_�u���N�H�[�e�[�V����)��z�ɐݒ�

'�\������������x�ɍ쐬
x = "#include " & z & ".h" & z

'x�̕\��
Editor.InsText(x)
'�J�[�\���̈ړ�
Editor.Left()
Editor.Left()
Editor.Left()

