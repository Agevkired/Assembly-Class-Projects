rem -- Make sure you comment out "#include "stdafx.h" if you run in command line
rem -- To compile use "cl p3.cpp" or "cl p3.cpp /clr"
rem
cl p3.cpp /clr
rem
rem -- To test, try different values
rem
rem #1 Test existing elements with exact match
rem
p3 .\p3.data1 Jon
p3 .\p3.data1 shane
p3 .\p3.data1 TONY
rem
rem #2 Test case insensitivity
rem
p3 .\p3.data1 Chris
p3 .\p3.data1 BryAN
rem
rem #3 Test partial search & non-existent elements
rem
p3 .\p3.data1 Art
p3 .\p3.data1 garbage
rem
rem #4 Test list with odd # of names
rem
p3 .\p3.data2 DAVe
p3 .\p3.data2 Jona
rem
pause