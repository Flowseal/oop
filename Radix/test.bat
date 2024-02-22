rem Переменная PROGRAM будет хранить первый аргумент командной строки заключённый в кавычки
set PROGRAM="%~1"

rem При запуске без параметров ожидается НЕнулевой код возврата
%PROGRAM% > nul && goto err
echo Test1 passed

rem notation < 2: ожидается НЕнулевой код возврата
%PROGRAM% 1 0 100 > nul && goto err
echo Test2 passed

rem notation > 32: ожидается НЕнулевой код возврата
%PROGRAM% 33 0 100 > nul && goto err
echo Test3 passed

rem invalid value: ожидается НЕнулевой код возврата
%PROGRAM% 12 10 - > nul && goto err
echo Test4 passed

rem value 102 не может существовать в двоичной СИ: ожидается НЕнулевой код возврата
%PROGRAM% 2 10 102 > nul && goto err
echo Test5 passed

rem При запуске с правильными параметрами ожидается нулевой код возврата
%PROGRAM% 16 10 1F > "%TEMP%\output.txt" || goto err
fc.exe "%TEMP%\output.txt" test-data\16-10-1F.txt >nul || goto err
echo Test6 passed

rem При запуске с правильными параметрами ожидается нулевой код возврата
%PROGRAM% 16 10 -1F > "%TEMP%\output.txt" || goto err
fc.exe "%TEMP%\output.txt" test-data\16-10-1F-negative.txt >nul || goto err
echo Test7 passed

rem При запуске с правильными параметрами ожидается нулевой код возврата
%PROGRAM% 2 36 11110 > "%TEMP%\output.txt" || goto err
fc.exe "%TEMP%\output.txt" test-data\2-36-11110.txt >nul || goto err
echo Test8 passed

rem При запуске с правильными параметрами ожидается нулевой код возврата
%PROGRAM% 5 13 1234 > "%TEMP%\output.txt" || goto err
fc.exe "%TEMP%\output.txt" test-data\5-13-1234.txt >nul || goto err
echo Test9 passed

rem ZIK0ZJ (MAX_INT) не приведёт к overflow: ожидается нулевой код возврата
%PROGRAM% 36 10 ZIK0ZJ > "%TEMP%\output.txt" || goto err
fc.exe "%TEMP%\output.txt" test-data\36-10-ZIK0ZJ.txt >nul || goto err
echo Test10 passed

rem ZIK0ZK (MAX_INT+1) приведёт к overflow: ожидается НЕнулевой код возврата
%PROGRAM% 36 10 ZIK0ZK > nul && goto err
echo Test11 passed

rem -ZIK0ZK (MIN_INT) не приведёт к underflow: ожидается нулевой код возврата
%PROGRAM% 36 10 -ZIK0ZK > "%TEMP%\output.txt" || goto err
fc.exe "%TEMP%\output.txt" test-data\36-10--ZIK0ZK.txt >nul || goto err
echo Test12 passed

rem -ZIK0ZL (MIN_INT-1) приведёт к underflow: ожидается НЕнулевой код возврата
%PROGRAM% 36 10 -ZIK0ZL > nul && goto err
echo Test13 passed

rem TODO добавить тест на sourceNotation==destintaitonNotation
rem TODO добавить тест на мин/макс int

echo All tests passed!
exit 0

:err
echo Program testing failed
exit 1