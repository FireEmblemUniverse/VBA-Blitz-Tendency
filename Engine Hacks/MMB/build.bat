
SET startDir=C:\devkitPro\devkitARM\bin\
SET as="%startDir%arm-none-eabi-as"

cd %~dp0Internal

for %%s in (*.s) do %as% -g -mcpu=arm7tdmi -mthumb-interwork %%s -o "%%~ns.elf"

cd %~dp0Modules

for %%s in (*.s) do %as% -g -mcpu=arm7tdmi -mthumb-interwork %%s -o "%%~ns.elf"

pause