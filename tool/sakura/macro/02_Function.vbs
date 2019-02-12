

'関数概要テンプレート作成マクロ

'    マクロテンプレ
'    x = ""&vbCrLf 
'    x = x &""&vbCrLf

'変数宣言
Dim x
Dim y

'日付取得
y = ExpandParameter("$d")

'表示したい文をxに作成
x =    "/*------------------------------------------------------------------------------"&vbCrLf
x = x &"* OverView	: "&vbCrLf
x = x &"* Parameter	: None"&vbCrLf
x = x &"* Return	: None"&vbCrLf
x = x &"*-----------------------------------------------------------------------------*/"&vbCrLf

'xの表示
Editor.InsText(x)

