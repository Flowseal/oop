rem %1 - �������� ������� ��������� ��������� ������ bat-����� (����� �� ����)
rem %~1 - �������� ������� ��������� ��������� ������ bat-����� � ��������� ����������� ������� (���� ��� ����)

rem ���������� PROGRAM ����� ������� ������ �������� ��������� ������ ����������� � �������
set PROGRAM="%~1"

rem ��� ������� ��� ���������� ��������� ��������� ��� ��������
%PROGRAM% > nul
if %ERRORLEVEL% EQU 0 goto err
echo Test1 passed

rem ��� ������� � �������������� ������� ������ ��������� ��������� ��� ��������
%PROGRAM% test-data\not-existing.txt "%TEMP%\fox.txt" bird cat > nul
if %ERRORLEVEL% EQU 0 goto err
echo Test2 passed

rem ��� ������� � ����������� ����������� ��������� ������� ��� ��������
%PROGRAM% test-data\fox.txt "%TEMP%\fox.txt" bird cat
if %ERRORLEVEL% NEQ 0 goto err
fc.exe "%TEMP%\fox.txt" test-data\fox.txt >nul
if %ERRORLEVEL% NEQ 0 goto err
echo Test3 passed

rem ��� ������� � ����������� ����������� ��������� ������� ��� ��������
%PROGRAM% test-data\fox.txt "%TEMP%\fox.txt" dog cat
if %ERRORLEVEL% NEQ 0 goto err
fc.exe "%TEMP%\fox.txt" test-data\fox-replace-dog-with-cat.txt >nul
if %ERRORLEVEL% NEQ 0 goto err
echo Test4 passed

rem ��� ������� � ����������� ����������� ��������� ������� ��� ��������
%PROGRAM% test-data\fox.txt "%TEMP%\fox.txt" ""  cat
if %ERRORLEVEL% NEQ 0 goto err
fc.exe "%TEMP%\fox.txt" test-data\fox.txt >nul
if %ERRORLEVEL% NEQ 0 goto err
echo Test5 passed

rem ��� ������� � ����������� ����������� ��������� ������� ��� ��������
%PROGRAM% test-data\digits.txt "%TEMP%\digits.txt" 1231234 0
if %ERRORLEVEL% NEQ 0 goto err
fc.exe "%TEMP%\digits.txt" test-data\digits-replace-1231234-with-0.txt >nul
if %ERRORLEVEL% NEQ 0 goto err
echo Test6 passed

echo All tests passed!
exit 0

:err
echo Program testing failed
exit 1