cd %~dp0

copy FE8_clean.gba VBA-BT.gba

cd "%~dp0Event Assembler"

Core A FE8 "-output:%~dp0VBA-BT.gba" "-input:%~dp0ROM Buildfile.event"

pause
