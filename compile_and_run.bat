cd ".\compiler_files"
.\a.exe ..\test.expr    
g++ a.cpp -o test.exe
pause
.\test.exe
pause