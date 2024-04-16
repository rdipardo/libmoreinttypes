@echo off
SETLOCAL
FOR /F "tokens=* USEBACKQ" %%F IN (`findstr /R "^.*[0-9]\." ..\pkgconfig\moreinttypes.pc`) DO (
SET "VERSION_STR=%%F"
)
:: https://www.doxygen.nl/manual/faq.html#faq_cmdline
( type Doxyfile & echo PROJECT_NUMBER=%VERSION_STR:~9% ) | doxygen -
cd ..
python3 -m http.server --directory docs/html 2>NUL:
ENDLOCAL
