@echo off
if exist earsvc.exe del earsvc.exe
rc /nologo resource.rc
cl /Feearsvc /nologo /MT /EHsc /O2t /DNDEBUG /DUSE_AES_DEC *.cpp sqlite\*.cpp sqlite\*.c ..\client\aes.c ..\client\crc32.c -link /MACHINE:X86 /TSAWARE /STACK:131072 kernel32.lib user32.lib advapi32.lib shlwapi.lib shell32.lib ws2_32.lib crypt32.lib resource.res
if %ERRORLEVEL% NEQ 0 pause
if exist *.res del *.res
if exist *.obj del *.obj
move /Y earsvc.exe ..\server_out\
if %ERRORLEVEL% NEQ 0 pause
