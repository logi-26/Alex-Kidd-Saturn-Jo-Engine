@ECHO Off
SET PATH=..\Compiler\SH_COFF\Other Utilities;..\Compiler\SH_COFF\sh-coff\bin;..\Compiler\SN;..\Compiler\TOOLS;%PATH%
make re

if exist sl_coff.iso (
"..\Emulators\yabause\yabause.exe" -a -i sl_coff.cue
) else (
echo Please compile first !
)
