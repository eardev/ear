@echo off
rar a -r -m1 ear _other client common server server_http server_out
if %ERRORLEVEL% NEQ 0 pause
move /Y ear.rar ..\..\..\..\dev\
if %ERRORLEVEL% NEQ 0 pause

echo _
echo _
echo _
echo        ��������  ��   ��   �� �� ��
echo        ��������  ��  ���   �� �� ��
echo        ��    ��  �� ���    �� �� ��
echo        ��    ��  �����     �� �� ��
echo        ��    ��  �����     �� �� ��
echo        ��    ��  �� ���    �� �� ��
echo        ��������  ��  ���           
echo        ��������  ��   ��   �� �� ��
echo _
echo _
echo _
pause
