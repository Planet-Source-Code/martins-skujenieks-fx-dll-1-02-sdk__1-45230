@ECHO OFF
CLS
ECHO ---------------------------------------------------------------------------
ECHO FX.DLL 1.02 SDK Setup
ECHO ---------------------------------------------------------------------------
ECHO.
ECHO FX.DLL Version 1.02
ECHO Copyright (C) Martins Skujenieks 2003
ECHO.
ECHO Visit http://www.exe.times.lv
ECHO E-Mail: martins_s@mail.teliamtc.lv
ECHO.
ECHO.
ECHO ---------------------------------------------------------------------------
ECHO Press CTRL+C to exit . . .
PAUSE
CLS
ECHO ---------------------------------------------------------------------------
ECHO End User Licence Agreement (EULA)
ECHO ---------------------------------------------------------------------------
ECHO.
ECHO This product is provided "as is", with no guarantee of completeness or
ECHO accuracy and without warranty of any kind, express or implied.
ECHO.
ECHO In no event will developer be liable for damages of any kind that may be
ECHO incurred with your hardware, peripherals or software programs.
ECHO.
ECHO This product and all of its parts may not be copied, emulated, cloned,
ECHO rented, leased, sold, reproduced, modified, decompiled, disassembled,
ECHO otherwise reverse engineered, republished, uploaded, posted, transmitted
ECHO or distributed in any way, without prior written consent of the developer.
ECHO.
ECHO.
ECHO ---------------------------------------------------------------------------
ECHO Press CTRL+C to exit . . .
PAUSE
CLS
ECHO ---------------------------------------------------------------------------
ECHO Installing...
ECHO ---------------------------------------------------------------------------
ECHO.
COPY dll.fx release\fx.dll
COPY dll.fx samples\demo\fx.dll
ECHO.
ECHO.
ECHO Installation was successfully completed...