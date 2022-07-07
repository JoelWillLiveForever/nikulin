@echo off
chcp 65001 >nul

if /i "%1" == "--help" goto help
if /i "%1" == "-clear" goto clear
if /i "%1" == "-detail" goto detail

rem Запуск цикла, когда первый аргумент пуст:
:loop

rem Условие выхода из цикла:
if [%1] == [] goto end

rem Файл, имя файла и его расширение:
set CURRENT_FILE=%1
set FILE_NAME=%~n1
set FILE_EXTENSION=%~x1

rem Проверка поддерживаемого расширения и компиляция:
if not "%FILE_EXTENSION%" == ".c" (
    if not "%FILE_EXTENSION%" == ".cpp" (
	echo Ошибка! Тип файла %CURRENT_FILE% неподдерживается!
	goto end
    )
)

echo Компиляция файла %CURRENT_FILE%
if "%FILE_EXTENSION%" == ".c" (
    gcc %CURRENT_FILE% -o %FILE_NAME%_c.exe
)
if "%FILE_EXTENSION%" == ".cpp" (
    g++ %CURRENT_FILE% -o %FILE_NAME%_cpp.exe
)

shift
goto loop

rem Описание работы команды
:help
echo Usage: [OPTION] [FILES_LIST_TO_COMPILE: FILE_1 FILE_2 ... FILE_N]
echo Supported file types: .c; .cpp;
echo Options:
echo     --help: Get script description;
echo     -clear: Remove all compilation files;
echo     -detail: Compilation of all stages of compilation.
goto end

rem Удаление всех скомпилированных файлов
:clear
del *.i *.ii *.s *.o *.exe
goto end

rem Цикл для компиляции со всеми стадиями:
:detail

rem Условие выхода из цикла:
if [%2] == [] goto end

rem Файл, имя файла и его расширение:
set CURRENT_FILE=%2
set FILE_NAME=%~n2
set FILE_EXTENSION=%~x2

rem Проверка поддерживаемого расширения и компиляция:
if not "%FILE_EXTENSION%" == ".c" (
    if not "%FILE_EXTENSION%" == ".cpp" (
	echo Ошибка! Тип файла %CURRENT_FILE% неподдерживается!
	goto end
    )
)

echo Компиляция файла %CURRENT_FILE%
if "%FILE_EXTENSION%" == ".c" (
    gcc -E %CURRENT_FILE% -o %FILE_NAME%_c.i
    gcc -S %FILE_NAME%_c.i -o %FILE_NAME%_c.s
    as %FILE_NAME%_c.s -o %FILE_NAME%_c.o
    gcc %FILE_NAME%_c.o -o %FILE_NAME%_c.exe
)
if "%FILE_EXTENSION%" == ".cpp" (
    g++ -E %CURRENT_FILE% -o %FILE_NAME%_cpp.ii
    g++ -S %FILE_NAME%_cpp.ii -o %FILE_NAME%_cpp.s
    as %FILE_NAME%_cpp.s -o %FILE_NAME%_cpp.o
    g++ %FILE_NAME%_cpp.o -o %FILE_NAME%_cpp.exe 
)

shift
goto detail 

:end
