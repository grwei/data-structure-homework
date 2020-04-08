:: Use doxygen to generate docs
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

rem ask if delete original docs
call :askIfDelDocs
echo delFlag = %delFlag%
pause 

FOR /D %%i IN (%rootPath%%prefix%*) DO (
    rem since we are in root path now, %%i will be (a string)
    :: set to sub-project folder's FULL PATH iteratly, 
    rem because IN [set] is full path 
    :: echo %%i = %%i 
    rem when passing arg, string should be put in "" to avoid mis parsing
    call :delDoc "%%i"

    rem cd to each sub-project folder, where a Doxyfile should have been added. 
    :: then run doxygen.
    cd %%i
    IF EXIST Doxyfile (
        doxygen
    ) ELSE (
        echo ERROR: Need Doxyfile in path: %%i!
    )

    rem check if generate docs successful    
    IF EXIST %%i\%docFolder% (
        echo Docs generated at: %%i\%docFolder%!
    ) ELSE (
        echo ERROR: Couldn't generate docs!
    )

    rem back to root path, ready for the next loop
    cd %rootPath%
)

echo main finish!
pause
exit

rem sub-proc: init. Set project root path, sub-project folder prefix, doc folder name and index
:: Users may need to modify the following var definitions  
:init
set rootPath="%~d0%~p0"
set prefix="DS_Ch"
set idx=1
set docFolder="doc"
:: Test: pass relative path as arg, then expand to full path
::call :testArg %rootPath%%prefix%%idx%
goto :EOF

rem Sub-proc: askIfDelDocs. ask if delete original docs
:: this proc will set the global var %delFlag%
:askIfDelDocs
:: Ask an input
set /P delFlag=Delete original docs?(y/n)

:: /i means ignore case
IF /i %delFlag% == Y ( 
    echo WARNNING: Original docs will be deleted!
    set delFlag=1
    goto :EOF
) 
IF /i %delFlag% == n (
    echo Original docs maybe override.
    set delFlag=0
    goto :EOF
)
:: if input neither y(Y) or n(N), ask again
goto :askIfDelDocs 

rem Sub-proc: delete docs. 
:: this proc shuold be called in project root path. 
:: %docFolder% shuold be set properly before each call.
:: arg1: sub-proj name, ex. DS_Ch3, or "%prefix%%idx%"
:delDoc
:: rmdir /s doc
IF %delFlag% EQU 1 (
    echo.
    echo You are deleting path: %~f1\%docFolder% !
    echo.
    rmdir /s "%~f1\%docFolder%"

    rem check if delete successful
    IF EXIST "%~f1\%docFolder%" (
        echo ERROR: delete fails in path: %~f1\%docFolder%!
    ) ELSE (
        echo deleted path finished: %~f1\%docFolder%
    )
) ELSE (
    echo Original docs in path: %~f1\%docFolder% will be override!    
)
goto :EOF

rem Test: arg passing
:testArg
echo %%0 = %0
echo %%1 = %1
echo %%~f1 = "%~f1"
echo %%2 = %2

goto :EOF

:: test
:: reference: https://blog.csdn.net/xiaoding133/article/details/39253083
echo 正在运行的这个批处理：
echo %%0：%0
echo 去掉引号：%~0
echo 完全路径：%~f0
echo 所在分区：%~d0
echo 所处路径：%~p0
echo 文件名：%~n0
echo 扩展名：%~x0
echo 文件属性：%~a0
echo 修改时间：%~t0
echo 文件大小：%~z0
pause

