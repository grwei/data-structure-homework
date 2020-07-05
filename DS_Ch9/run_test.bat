::This batch will compile and run all test.
@echo off

echo Author: Guorui Wei
echo E-mail: 313017602@qq.com

rem main proc
:main
echo main starts... 

rem Set project root path, folder prefix and index
call :init
echo Note: rootPath will be set to: %rootPath%
pause

IF EXIST %rootPath%%binFolder% (
    echo exist path: %rootPath%%binFolder%
) ELSE (
    mkdir %rootPath%%binFolder%
    echo create path: %rootPath%%binFolder%
)

:: How to write the following into a for /D ?
g++ ./src/ch9_1.cc -o ./bin/ch9_1.exe -g -Wall -Wextra -Wshadow -static-libgcc -fexec-charset=UTF-8 -finput-charset=UTF-8 -std=c++17 -I ./include

FOR /R %rootPath%%binFolder% %%i IN (*.exe) DO (
    %%i
)

echo main finish!
pause
exit

rem sub-proc: init. Set project root path, source folder name binary output folder name
:: Users may need to modify the following var definitions  
:init
set rootPath="%~dp0"
set binFolder="bin\"
set srcFolder="src\"
:: Test: pass relative path as arg, then expand to full path
::call :testArg %rootPath%%prefix%%idx%
goto :EOF
