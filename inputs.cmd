@echo off
rundll32.exe utils.dll,ShowInputBox %1

set /p RESULT=<result.txt
echo %RESULT%
