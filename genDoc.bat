@rem Use doxygen to generate docs
@echo off

echo Author: Guorui Wei
echo E-mail: 313017602@qq.com
pause
echo Start...

cd .\DS_Ch1
doxygen
cd ..\DS_Ch2
doxygen
cd ..\DS_Ch3
doxygen
cd ..\DS_Ch4
doxygen
cd ..

echo Finish!
pause
