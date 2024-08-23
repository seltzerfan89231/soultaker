@echo off
setlocal enableextensions enabledelayedexpansion
set flags=-O3 -fopenmp
set name=a
set link=-L./lib/glfw/link -L./lib/AL/link -L./lib/sndfile/link -L./lib/WinSock2/link -lws2_32 -lglfw3dll -lOpenAL32 -lsndfile
set Ifiles=
set Cfiles=
for /d %%f in (".\lib\*") do (
    set "Ifiles=!Ifiles! -I%%f\include"
)
for /R .\lib %%f in (*) do (
    if %%~xf==.o set "Cfiles=!Cfiles! %%f"
)
for /R .\src %%f in (*) do (
    if %%~xf==.c set "Cfiles=!Cfiles! %%f"
)
gcc %flags% %Ifiles% %Cfiles% %link% -o %name%