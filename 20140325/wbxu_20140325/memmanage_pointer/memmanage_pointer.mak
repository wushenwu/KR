# Microsoft Developer Studio Generated NMAKE File, Based on memmanage_pointer.dsp
!IF "$(CFG)" == ""
CFG=memmanage_pointer - Win32 Debug
!MESSAGE No configuration specified. Defaulting to memmanage_pointer - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "memmanage_pointer - Win32 Release" && "$(CFG)" != "memmanage_pointer - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "memmanage_pointer.mak" CFG="memmanage_pointer - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "memmanage_pointer - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "memmanage_pointer - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "memmanage_pointer - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\memmanage_pointer.exe"


CLEAN :
	-@erase "$(INTDIR)\fit.obj"
	-@erase "$(INTDIR)\memmanage.obj"
	-@erase "$(INTDIR)\table.obj"
	-@erase "$(INTDIR)\ui.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\memmanage_pointer.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)\memmanage_pointer.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\memmanage_pointer.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib  kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:no /pdb:"$(OUTDIR)\memmanage_pointer.pdb" /machine:I386 /out:"$(OUTDIR)\memmanage_pointer.exe" 
LINK32_OBJS= \
	"$(INTDIR)\fit.obj" \
	"$(INTDIR)\memmanage.obj" \
	"$(INTDIR)\table.obj" \
	"$(INTDIR)\ui.obj"

"$(OUTDIR)\memmanage_pointer.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "memmanage_pointer - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\memmanage_pointer.exe" "$(OUTDIR)\memmanage_pointer.bsc"


CLEAN :
	-@erase "$(INTDIR)\fit.obj"
	-@erase "$(INTDIR)\fit.sbr"
	-@erase "$(INTDIR)\memmanage.obj"
	-@erase "$(INTDIR)\memmanage.sbr"
	-@erase "$(INTDIR)\table.obj"
	-@erase "$(INTDIR)\table.sbr"
	-@erase "$(INTDIR)\ui.obj"
	-@erase "$(INTDIR)\ui.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\memmanage_pointer.bsc"
	-@erase "$(OUTDIR)\memmanage_pointer.exe"
	-@erase "$(OUTDIR)\memmanage_pointer.ilk"
	-@erase "$(OUTDIR)\memmanage_pointer.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MLd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\memmanage_pointer.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ  /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\memmanage_pointer.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\fit.sbr" \
	"$(INTDIR)\memmanage.sbr" \
	"$(INTDIR)\table.sbr" \
	"$(INTDIR)\ui.sbr"

"$(OUTDIR)\memmanage_pointer.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib  kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:yes /pdb:"$(OUTDIR)\memmanage_pointer.pdb" /debug /machine:I386 /out:"$(OUTDIR)\memmanage_pointer.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\fit.obj" \
	"$(INTDIR)\memmanage.obj" \
	"$(INTDIR)\table.obj" \
	"$(INTDIR)\ui.obj"

"$(OUTDIR)\memmanage_pointer.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("memmanage_pointer.dep")
!INCLUDE "memmanage_pointer.dep"
!ELSE 
!MESSAGE Warning: cannot find "memmanage_pointer.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "memmanage_pointer - Win32 Release" || "$(CFG)" == "memmanage_pointer - Win32 Debug"
SOURCE=.\fit.c

!IF  "$(CFG)" == "memmanage_pointer - Win32 Release"


"$(INTDIR)\fit.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "memmanage_pointer - Win32 Debug"


"$(INTDIR)\fit.obj"	"$(INTDIR)\fit.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\memmanage.c

!IF  "$(CFG)" == "memmanage_pointer - Win32 Release"


"$(INTDIR)\memmanage.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "memmanage_pointer - Win32 Debug"


"$(INTDIR)\memmanage.obj"	"$(INTDIR)\memmanage.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\table.c

!IF  "$(CFG)" == "memmanage_pointer - Win32 Release"


"$(INTDIR)\table.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "memmanage_pointer - Win32 Debug"


"$(INTDIR)\table.obj"	"$(INTDIR)\table.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\ui.c

!IF  "$(CFG)" == "memmanage_pointer - Win32 Release"


"$(INTDIR)\ui.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "memmanage_pointer - Win32 Debug"


"$(INTDIR)\ui.obj"	"$(INTDIR)\ui.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 


!ENDIF 

