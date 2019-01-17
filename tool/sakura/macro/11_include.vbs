

'関数概要テンプレート作成マクロ

'    マクロテンプレ
'    x = ""&vbCrLf 
'    x = x &""&vbCrLf

'変数宣言
Dim x
Dim y

'日付取得
y = ExpandParameter("$d")
z = Chr(34)		' "(ダブルクォーテーション)をzに設定

'表示したい文をxに作成
x = "#include " & z & ".h" & z

'xの表示
Editor.InsText(x)
'カーソルの移動
Editor.Left()
Editor.Left()
Editor.Left()

