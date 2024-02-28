rem ���������� PROGRAM ����� ������� ������ �������� ��������� ������ ����������� � �������
set PROGRAM="%~1"

rem ��� ������� ��� ���������� ��������� ��������� ��� ��������
%PROGRAM% > nul && goto err
echo Test1 passed

rem ��� ������� � ������������ ��������� ��������� ��������� ��� ��������
%PROGRAM% bad test-data\hello-world.txt "%TEMP%\output.txt" 25 > nul && goto err
echo Test2 passed

rem ��� ������� � �������������� ������� ������ ��������� ��������� ��� ��������
%PROGRAM% crypt test-data\not-existing.txt "%TEMP%\output.txt" 25 > nul && goto err
echo Test3 passed

rem ��� ������� � ������ �� �������� � ������� [0; 255] ��������� ��������� ��� ��������
%PROGRAM% crypt test-data\hello-world.txt "%TEMP%\output.txt" 256 > nul && goto err
echo Test4 passed

rem ��� ������� � ������ �� �������� � ������� [0; 255] ��������� ��������� ��� ��������
%PROGRAM% crypt test-data\hello-world.txt "%TEMP%\output.txt" -1 > nul && goto err
echo Test5 passed

rem ��������, ������� �� crypt ����
%PROGRAM% crypt test-data\hello-world.txt "%TEMP%\output_crypted_255.txt" 255 > nul || goto err
fc.exe "%TEMP%\output_crypted_255.txt" test-data\hello-world.txt > nul && goto err
echo Test6.1 passed

rem ��������, ��������� �� decrypt ����
%PROGRAM% decrypt "%TEMP%\output_crypted_255.txt" "%TEMP%\output_decrypted_255.txt" 255 > nul || goto err
fc.exe "%TEMP%\output_decrypted_255.txt" test-data\hello-world.txt > nul || goto err
echo Test6.2 passed

rem ��������, ������� �� crypt ���� ��-������� � ������ ������
%PROGRAM% crypt test-data\hello-world.txt "%TEMP%\output_crypted_0.txt" 0 > nul || goto err
fc.exe "%TEMP%\output_crypted_0.txt" test-data\hello-world.txt > nul && goto err
fc.exe "%TEMP%\output_crypted_0.txt" "%TEMP%\output_decrypted_255.txt" > nul && goto err
echo Test7 passed

rem ��������, ��������� �� decrypt ���� ��-������� � ������ ������
%PROGRAM% decrypt "%TEMP%\output_crypted_255.txt" "%TEMP%\output_decrypted_255_0.txt" 0 > nul || goto err
fc.exe "%TEMP%\output_decrypted_255_0.txt" "%TEMP%\output_decrypted_255.txt" > nul && goto err
fc.exe "%TEMP%\output_decrypted_255_0.txt" test-data\hello-world.txt > nul && goto err
echo Test8 passed

rem �������� �� ���������� � ������������ ������� �����
%PROGRAM% crypt test-data\empty.txt "%TEMP%\empty_crypted.txt" 123 > nul || goto err
fc.exe "%TEMP%\empty_crypted.txt" test-data\empty.txt > nul || goto err
echo Test9.1 passed

%PROGRAM% decrypt "%TEMP%\empty_crypted.txt" "%TEMP%\empty_decrypted.txt" 123 > nul || goto err
fc.exe "%TEMP%\empty_decrypted.txt" test-data\empty.txt > nul || goto err
echo Test9.2 passed

echo All tests passed!
exit 0

:err
echo Program testing failed
exit 1