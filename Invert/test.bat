rem ���������� PROGRAM ����� ������� ������ �������� ��������� ������ ����������� � �������
set PROGRAM="%~1"

rem ��� ������� ��� ���������� ��������� ��������� ��� ��������
%PROGRAM% > nul && goto err
echo Test1 passed

rem ��� ������� � �������������� ������ ��������� ��������� ��� ��������
%PROGRAM% test-data\not-existing.txt > nul && goto err
echo Test2 passed

rem ��� ������� � ������������� �������� ������� ��������� ��������� ��� ��������
%PROGRAM% test-data\wrong.txt > nul && goto err
echo Test3 passed

rem TODO ���� �� ������������ ��������

rem ��� ������� � ������� ������� �������� ��������� ��������� ��� ��������
%PROGRAM% test-data\zeroes.txt > nul && goto err
echo Test4 passed

rem ��� ������� � ������� ��������� �������� ��������� ��������� ��� ��������
%PROGRAM% test-data\units.txt > nul && goto err
echo Test5 passed

rem ��� ������� � ����������� ����������� ��������� ������ ��� ��������
%PROGRAM% test-data\round.txt > "%TEMP%\output.txt" || goto err
fc.exe "%TEMP%\output.txt" test-data\round-inverted.txt > nul || goto err
echo Test6 passed

rem ��� ������� � ����������� ����������� ��������� ������� ��� ��������
%PROGRAM% test-data\positive.txt > "%TEMP%\output.txt" || goto err
fc.exe "%TEMP%\output.txt" test-data\positive-inverted.txt > nul || goto err
echo Test7 passed

rem ��� ������� � ����������� ����������� ��������� ������� ��� ��������
%PROGRAM% test-data\negative.txt > "%TEMP%\output.txt" || goto err
fc.exe "%TEMP%\output.txt" test-data\negative-inverted.txt >nul || goto err
echo Test8 passed

rem ��� ������� � ����������� ����������� ��������� ������� ��� ��������
%PROGRAM% test-data\mixed.txt > "%TEMP%\output.txt" || goto err
fc.exe "%TEMP%\output.txt" test-data\mixed-inverted.txt >nul || goto err
echo Test9 passed

echo All tests passed!
exit 0

:err
echo Program testing failed
exit 1