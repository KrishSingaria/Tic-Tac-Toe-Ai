@echo off
echo Activating Emscripten Environment...
call C:\Users\krish\emsdk\emsdk_env.bat

echo.
echo --- Compiling C++ to Wasm ---
cmd /c emcc --bind main.cpp game.cpp -o game.html -s EXPORTED_RUNTIME_METHODS="['UTF8ToString']"

echo.
echo The compiler exited with error code: %errorlevel%
echo.

if errorlevel 1 (
    echo !!!!! SCRIPT DETECTED A FAILURE !!!!!
    pause
    exit /b
)

echo.
echo --- Cleaning up ---
del game.html

echo.
echo --- Build Successful! ---
echo Your game.js and game.wasm files are updated.
pause