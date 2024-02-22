rem Переменная PROGRAM будет хранить первый аргумент командной строки заключённый в кавычки
set PROGRAM="%~1"

rem При запуске без параметров ожидается НЕнулевой код возврата
%PROGRAM% > nul && goto err
echo Test1 passed

rem При запуске с несуществующим файлом ожидается НЕнулевой код возврата
%PROGRAM% test-data\not-existing.txt > nul && goto err
echo Test2 passed

rem При запуске с неправильными входными данными ожидается НЕнулевой код возврата
%PROGRAM% test-data\wrong.txt > nul && goto err
echo Test3 passed

rem TODO тест на максимальное значение

rem При запуске с входной нулевой матрицей ожидается НЕнулевой код возврата
%PROGRAM% test-data\zeroes.txt > nul && goto err
echo Test4 passed

rem При запуске с входной единичной матрицей ожидается НЕнулевой код возврата
%PROGRAM% test-data\units.txt > nul && goto err
echo Test5 passed

rem При запуске с правильными параметрами ожидается нулвой код возврата
%PROGRAM% test-data\round.txt > "%TEMP%\output.txt" || goto err
fc.exe "%TEMP%\output.txt" test-data\round-inverted.txt > nul || goto err
echo Test6 passed

rem При запуске с правильными параметрами ожидается нулевой код возврата
%PROGRAM% test-data\positive.txt > "%TEMP%\output.txt" || goto err
fc.exe "%TEMP%\output.txt" test-data\positive-inverted.txt > nul || goto err
echo Test7 passed

rem При запуске с правильными параметрами ожидается нулевой код возврата
%PROGRAM% test-data\negative.txt > "%TEMP%\output.txt" || goto err
fc.exe "%TEMP%\output.txt" test-data\negative-inverted.txt >nul || goto err
echo Test8 passed

rem При запуске с правильными параметрами ожидается нулевой код возврата
%PROGRAM% test-data\mixed.txt > "%TEMP%\output.txt" || goto err
fc.exe "%TEMP%\output.txt" test-data\mixed-inverted.txt >nul || goto err
echo Test9 passed

echo All tests passed!
exit 0

:err
echo Program testing failed
exit 1