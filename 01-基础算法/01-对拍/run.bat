@echo off
cls
echo 编译中...
echo.

:: 编译所有程序
g++ -o rand.exe rand.cpp -std=c++17 -O2 2>nul
if errorlevel 1 (echo ? rand.cpp 失败 & pause & exit)
echo ? rand

g++ -o stand.exe stand.cpp -std=c++17 -O2 2>nul
if errorlevel 1 (echo ? stand.cpp 失败 & pause & exit)
echo ? stand

g++ -o text.exe text.cpp -std=c++17 -O2 2>nul
if errorlevel 1 (echo ? text.cpp 失败 & pause & exit)
echo ? text

g++ -o duipai.exe duipai.cpp -std=c++17 -O2 2>nul
if errorlevel 1 (echo ? duipai.cpp 失败 & pause & exit)
echo ? duipai

echo.
echo 编译成功
echo.
echo Ctrl+C 退出
echo.

duipai.exe
pause