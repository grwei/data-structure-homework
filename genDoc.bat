@rem Use doxygen to generate docs

echo Author: Guorui Wei
echo E-mail: 313017602@qq.com
pause
echo Start...

cd .\DS_Ch1
doxygen.exe
cd ..\DS_Ch2
doxygen.exe
cd ..\DS_Ch3
doxygen.exe
cd ..\DS_Ch4
doxygen
cd ..

echo Finish!
pause
