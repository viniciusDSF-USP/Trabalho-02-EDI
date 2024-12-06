@echo off

set "A=lib/avl"
set "B=lib/filme"
set "C=lib/aluno"

if "%1"=="clean" goto clean

gcc -c %A%.c -o %A%.o

gcc -c %B%.c -o %B%.o

gcc -c %C%.c -o %C%.o

gcc -c main.c -o main.o

gcc main.o %A%.o %B%.o %C%.o -o main.exe -Wall
.\main.exe

goto end

:clean
del *.o
del lib\*.o
del main.exe
goto end

:end