rem Use doxygen to generate docs
@echo off

echo Author: Guorui Wei
echo E-mail: 313017602@qq.com

rem main proc
:main
call :init
echo delFlag = %delFlag%
echo main start...
pause

cd .\DS_Ch1
call :delDoc delFlag
doxygen

cd ..\DS_Ch2
call :delDoc delFlag
doxygen

cd ..\DS_Ch3
call :delDoc delFlag
doxygen

cd ..\DS_Ch4
call :delDoc delFlag
doxygen
cd ..

echo main finish!
pause
exit

rem Sub-proc: initialize. ask if delete original docs
:init
rem Ask an input
set /P delFlag=Delete original docs?(y/n)

IF /i %delFlag% == Y (
    echo WARNNING: Original docs will be deleted!
    set delFlag=1
    pause
    goto :EOF
) 

IF /i %delFlag% == n (
    echo Original docs maybe override.
    set delFlag=0
    pause
    goto :EOF
)
rem if input neither y(Y) or n(N), ask again
goto :init 
goto :EOF

rem Sub-proc: delete ./doc recursively
:delDoc
rem rmdir .\doc\ -Confirm -Recurse
IF %1 EQU 1 (
    rmdir .\doc\ -Recurse
    echo Original doc deleted!
) ELSE (
    echo Original doc override!    
)
pause
goto :EOF
