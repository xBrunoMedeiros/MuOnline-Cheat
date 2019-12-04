@echo off
echo "System Developed by CheatsUnknown"

:: Delete Compiler
cd ../Binary/
del /y PrjMuController.exe
cd ../Source/

:: Enter Project Directory
cd MuController

:: Compiler Resources
cd Resources
brcc32 UAC.rc
cd ..

:: Compiler Project
dcc32.exe "./PrjMuController.dpr"

:: Delete useless files
del /s *.~*
del /s *.cfg
del /s *.dof
del /s *.ddp
del /s *.dcu

:: Move to release folder
move /y PrjMuController.exe ..\Release\

:: Execute binary
cd ..\Release\
start PrjMuController.exe

:: Pause system
pause