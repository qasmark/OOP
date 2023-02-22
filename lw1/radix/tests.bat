@echo off

set PROGRAM="%~1"
set OUTPUT = "%TEMP%\output.txt"
rem simple tests
%PROGRAM% 16 22 -FFFFFFF > %OUTPUT% > nul || goto err
%PROGRAM% 16 22 1FFFFFFF 

rem from biggest notation to smallest
%PROGRAM% 36 2 ZZZZ 
rem reverse
%PROGRAM% 2 36 110011010000011111111 

rem too large values
%PROGRAM% 16 10 FFFFFFFF 
%PROGRAM% 16 10 -FFFFFFFF

rem err params
%PROGRAM% 0 40 ABCD 
%PROGRAM% 10 2 ABCD 
%PROGRAM% G 10 FFFFFFFF
%PROGRAM% "" "" ""

echo OK
exit 0

:err
echo Program testing failed
exit 1