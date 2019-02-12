

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
x = "#define "

'xの表示
Editor.InsText(x)

