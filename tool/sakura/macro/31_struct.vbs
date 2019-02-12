Dim typ
Dim x

typ = Editor.GetSelectedString(0)

x = "typedef enum tag" & typ & " {" &vbCrLf
x = x & "	;" &vbCrLf
x = x & "} " & typ & ", *P" & typ & ";" &vbCrLf
x = x & "typedef const " & typ & " C" & typ & ", *CP" & typ & ";"

Editor.InsText(x)


