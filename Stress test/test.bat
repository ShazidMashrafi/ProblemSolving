@echo off
setlocal enabledelayedexpansion

:: Compile the C++ files
g++ correct.cpp -o correct.exe
g++ gen.cpp -o gen.exe
g++ wrong.cpp -o wrong.exe

:: Initialize the test counter
set /a i=1

:loop
:: Generate the input file
gen.exe !i! > input_file

:: Run the correct and wrong force solution
correct.exe < input_file > correctAnswer
wrong.exe < input_file > myAnswer

:: Compare the outputs
FC /B myAnswer correctAnswer >nul
if errorlevel 1 (
    echo.
    echo WA on the following test:
    type input_file
    echo Your answer is:
    type myAnswer
    echo.
    echo Correct answer is:
    type correctAnswer
    goto :eof
)

:: If the outputs matched, increment the test counter and loop
echo Passed test: !i!
set /a i+=1
goto :loop