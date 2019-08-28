rem -- Make sure you remove #include "stdafx.h" if copied from IDE
rem -- To compile use "cl p2.cpp" or "cl p2.cpp /clr"
rem
cl p2.cpp /clr
rem
rem -- To test, try different values
rem
rem #1 Test ascending sorting
rem
p2 .\p2.data1 1
p2 .\p2.data2 1
rem
rem #2 Test descending sorting
rem
p2 .\p2.data1 2
p2 .\p2.data2 2
rem

