Dim typ
Dim fix
Dim x


typ = Editor.GetSelectedString(0)
fix  = Mid( typ, 3 )

x = "typedef enum tag" & typ & " {" &vbCrLf
x = x & "	e" & fix & "_ = 0," &vbCrLf
x = x & "	e" & fix & "_," &vbCrLf
x = x & "	e" & fix & "_MAX," &vbCrLf
x = x & "	e" & fix & "_INVALID" &vbCrLf
x = x & "} " & typ & ";" &vbCrLf
x = x & "typedef const " & typ & " C" & typ & ";"

Editor.InsText(x)


