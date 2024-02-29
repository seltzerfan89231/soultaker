@echo off
setlocal enableextensions enabledelayedexpansion
set Cfiles=%Cfiles% .\lib\glad\src\glad_gl.o
set Cfiles=%Cfiles% .\lib\stb\src\stb_image.o
for /R .\src %%f in (*) do (
    if %%~xf==.c set "Cfiles=!Cfiles! %%f"
)
gcc -Wall -Wextra -Wpedantic -I./lib/glad/include -I./lib/ht/include -I./lib/glfw/include -I./lib/stb/include -I./lib/gtype/include -I./lib/gvec/include -L./lib/glfw/link %Cfiles% -lglfw3dll -o prog
prog
del prog.exe