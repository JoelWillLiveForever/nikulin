@echo off
chcp 65001 >nul

if /i "%1" == "--help" goto help
if /i "%1" == "-mkdir" goto mkdir
if /i "%1" == "-copy" goto copy
if /i "%1" == "-delete" goto delete

:help
echo Опции:
echo     --help: Вывод описания скрипта
echo     -mkdir: Создание директории [-mkdir ПУТЬ_К_ДИРЕКТОРИИ]
echo     -copy: Копирование файлов в указанную директорию [-copy ПУТЬ_К_ДИРЕКТОРИИ ФАЙЛ_1 ФАЙЛ_2 ... ФАЙЛ_N]
echo     -delete: Удаление всех файлов в указанной директории [-delete ПУТЬ_К_ДИРЕКТОРИИ]
goto end

:mkdir
set DIR_NAME=%2

if exist "%DIR_NAME%\" (
    echo Ошибка! Директория %DIR_NAME%\ уже существует!
    goto end
)

rem Создать директорию в текущей папке
mkdir "%DIR_NAME%"

echo Директория %DIR_NAME%\ успешно создана!
goto end

:copy
set DESTINATION_DIR=%2

:loop
shift
if [%2] == [] goto end

set FILE=%2
xcopy /I %FILE% %DESTINATION_DIR%
goto loop

:delete
del %2

:end
