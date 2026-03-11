@echo off >nul 2>&1
if exist input.txt (
    (echo Sample Input & type input.txt & echo. & echo Sample Output & type stand_out.txt & echo. & echo Wa Output & type text_out.txt) > WA.txt 2>nul
)
del input.txt stand_out.txt text_out.txt *.exe 2>nul >nul