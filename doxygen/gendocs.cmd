@echo off
SETLOCAL
FOR /F "tokens=* USEBACKQ" %%F IN (`findstr /R "^.*[0-9]\." ..\pkgconfig\moreinttypes.pc`) DO (
SET "VERSION_STR=%%F"
)
SET "DOXYGEN_PROJECT_VERSION=%VERSION_STR:~9%"
doxygen Doxyfile html
cd ..
python3 -m http.server --directory docs/html 2>NUL:
ENDLOCAL
