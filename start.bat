@echo off
chcp 65001 > nul

echo Building Bank System...

g++ -std=c++17 -pthread src/*.cpp -o bank_sim.exe

if %errorlevel% == 0 (
    echo Build successful!
    echo.
    bank_sim.exe
    echo.
    pause
) else (
    echo Build failed!
    pause
)