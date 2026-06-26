@echo off
chcp 65001 > nul

echo Building Bank System...

g++ -std=c++17 -pthread src/*.cpp -o bank_sim.exe

if %errorlevel% == 0 (
    echo Build successful!
    echo.
    start "Bank Menu" cmd /k "bank_sim.exe"
    timeout /t 2 /nobreak > nul
    start "Bank Logs" powershell -NoExit -Command "Write-Host 'BANK LOGS' -ForegroundColor Green; Write-Host ''; Write-Host 'Waiting for logs...' -ForegroundColor Yellow; Get-Content -Path .\bank.log -Wait -Tail 10"
    exit
) else (
    echo Build failed!
    pause
)