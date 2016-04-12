# Microsoft Developer Studio Project File - Name="MediaServer" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=MediaServer - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "MediaServer.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "MediaServer.mak" CFG="MediaServer - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "MediaServer - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "MediaServer - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "MediaServer - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "..\jrtp" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD BASE RSC /l 0x804 /d "NDEBUG"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386 /out:"..\Bin\MediaServer.exe"

!ELSEIF  "$(CFG)" == "MediaServer - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W2 /Gm /GX /ZI /Od /I "..\jrtp" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /D "RTP_SUPPORT_THREAD" /YX /FD /GZ /c
# ADD BASE RSC /l 0x804 /d "_DEBUG"
# ADD RSC /l 0x804 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /out:"..\Bin\MediaServer.exe" /pdbtype:sept /libpath:"..\lib"

!ENDIF 

# Begin Target

# Name "MediaServer - Win32 Release"
# Name "MediaServer - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\MediaServer.cpp
# End Source File
# Begin Source File

SOURCE=.\RTPAppSession.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\RTPAppSession.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# Begin Group "JRTP"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\jrtp\jmutex.cpp
# End Source File
# Begin Source File

SOURCE=..\jrtp\jmutex.h
# End Source File
# Begin Source File

SOURCE=..\jrtp\jmutexautolock.h
# End Source File
# Begin Source File

SOURCE=..\jrtp\jthread.cpp
# End Source File
# Begin Source File

SOURCE=..\jrtp\jthread.h
# End Source File
# Begin Source File

SOURCE=..\jrtp\rtcpapppacket.cpp
# End Source File
# Begin Source File

SOURCE=..\jrtp\rtcpapppacket.h
# End Source File
# Begin Source File

SOURCE=..\jrtp\rtcpbyepacket.cpp
# End Source File
# Begin Source File

SOURCE=..\jrtp\rtcpbyepacket.h
# End Source File
# Begin Source File

SOURCE=..\jrtp\rtcpcompoundpacket.cpp
# End Source File
# Begin Source File

SOURCE=..\jrtp\rtcpcompoundpacket.h
# End Source File
# Begin Source File

SOURCE=..\jrtp\rtcpcompoundpacketbuilder.cpp
# End Source File
# Begin Source File

SOURCE=..\jrtp\rtcpcompoundpacketbuilder.h
# End Source File
# Begin Source File

SOURCE=..\jrtp\rtcppacket.cpp
# End Source File
# Begin Source File

SOURCE=..\jrtp\rtcppacket.h
# End Source File
# Begin Source File

SOURCE=..\jrtp\rtcppacketbuilder.cpp
# End Source File
# Begin Source File

SOURCE=..\jrtp\rtcppacketbuilder.h
# End Source File
# Begin Source File

SOURCE=..\jrtp\rtcprrpacket.cpp
# End Source File
# Begin Source File

SOURCE=..\jrtp\rtcprrpacket.h
# End Source File
# Begin Source File

SOURCE=..\jrtp\rtcpscheduler.cpp
# End Source File
# Begin Source File

SOURCE=..\jrtp\rtcpscheduler.h
# End Source File
# Begin Source File

SOURCE=..\jrtp\rtcpsdesinfo.cpp
# End Source File
# Begin Source File

SOURCE=..\jrtp\rtcpsdesinfo.h
# End Source File
# Begin Source File

SOURCE=..\jrtp\rtcpsdespacket.cpp
# End Source File
# Begin Source File

SOURCE=..\jrtp\rtcpsdespacket.h
# End Source File
# Begin Source File

SOURCE=..\jrtp\rtcpsrpacket.cpp
# End Source File
# Begin Source File

SOURCE=..\jrtp\rtcpsrpacket.h
# End Source File
# Begin Source File

SOURCE=..\jrtp\rtcpunknownpacket.h
# End Source File
# Begin Source File

SOURCE=..\jrtp\rtpaddress.h
# End Source File
# Begin Source File

SOURCE=..\jrtp\rtpcollisionlist.cpp
# End Source File
# Begin Source File

SOURCE=..\jrtp\rtpcollisionlist.h
# End Source File
# Begin Source File

SOURCE=..\jrtp\rtpconfig.h
# End Source File
# Begin Source File

SOURCE=..\jrtp\rtpconfig_win.h
# End Source File
# Begin Source File

SOURCE=..\jrtp\rtpdebug.cpp
# End Source File
# Begin Source File

SOURCE=..\jrtp\rtpdebug.h
# End Source File
# Begin Source File

SOURCE=..\jrtp\rtpdefines.h
# End Source File
# Begin Source File

SOURCE=..\jrtp\rtperrors.cpp
# End Source File
# Begin Source File

SOURCE=..\jrtp\rtperrors.h
# End Source File
# Begin Source File

SOURCE=..\jrtp\rtphashtable.h
# End Source File
# Begin Source File

SOURCE=..\jrtp\rtpinternalsourcedata.cpp
# End Source File
# Begin Source File

SOURCE=..\jrtp\rtpinternalsourcedata.h
# End Source File
# Begin Source File

SOURCE=..\jrtp\rtpipv4address.cpp
# End Source File
# Begin Source File

SOURCE=..\jrtp\rtpipv4address.h
# End Source File
# Begin Source File

SOURCE=..\jrtp\rtpipv4destination.h
# End Source File
# Begin Source File

SOURCE=..\jrtp\rtpipv6address.cpp
# End Source File
# Begin Source File

SOURCE=..\jrtp\rtpipv6address.h
# End Source File
# Begin Source File

SOURCE=..\jrtp\rtpipv6destination.h
# End Source File
# Begin Source File

SOURCE=..\jrtp\rtpkeyhashtable.h
# End Source File
# Begin Source File

SOURCE=..\jrtp\rtplibraryversion.cpp
# End Source File
# Begin Source File

SOURCE=..\jrtp\rtplibraryversion.h
# End Source File
# Begin Source File

SOURCE=..\jrtp\rtpmemorymanager.h
# End Source File
# Begin Source File

SOURCE=..\jrtp\rtpmemoryobject.h
# End Source File
# Begin Source File

SOURCE=..\jrtp\rtppacket.cpp
# End Source File
# Begin Source File

SOURCE=..\jrtp\rtppacket.h
# End Source File
# Begin Source File

SOURCE=..\jrtp\rtppacketbuilder.cpp
# End Source File
# Begin Source File

SOURCE=..\jrtp\rtppacketbuilder.h
# End Source File
# Begin Source File

SOURCE=..\jrtp\rtppollthread.cpp
# End Source File
# Begin Source File

SOURCE=..\jrtp\rtppollthread.h
# End Source File
# Begin Source File

SOURCE=..\jrtp\rtprandom.cpp
# End Source File
# Begin Source File

SOURCE=..\jrtp\rtprandom.h
# End Source File
# Begin Source File

SOURCE=..\jrtp\rtprawpacket.h
# End Source File
# Begin Source File

SOURCE=..\jrtp\rtpsession.cpp
# End Source File
# Begin Source File

SOURCE=..\jrtp\rtpsession.h
# End Source File
# Begin Source File

SOURCE=..\jrtp\rtpsessionparams.cpp
# End Source File
# Begin Source File

SOURCE=..\jrtp\rtpsessionparams.h
# End Source File
# Begin Source File

SOURCE=..\jrtp\rtpsessionsources.cpp
# End Source File
# Begin Source File

SOURCE=..\jrtp\rtpsessionsources.h
# End Source File
# Begin Source File

SOURCE=..\jrtp\rtpsourcedata.cpp
# End Source File
# Begin Source File

SOURCE=..\jrtp\rtpsourcedata.h
# End Source File
# Begin Source File

SOURCE=..\jrtp\rtpsources.cpp
# End Source File
# Begin Source File

SOURCE=..\jrtp\rtpsources.h
# End Source File
# Begin Source File

SOURCE=..\jrtp\rtpstructs.h
# End Source File
# Begin Source File

SOURCE=..\jrtp\rtptimeutilities.cpp
# End Source File
# Begin Source File

SOURCE=..\jrtp\rtptimeutilities.h
# End Source File
# Begin Source File

SOURCE=..\jrtp\rtptransmitter.h
# End Source File
# Begin Source File

SOURCE=..\jrtp\rtptypes.h
# End Source File
# Begin Source File

SOURCE=..\jrtp\rtptypes_win.h
# End Source File
# Begin Source File

SOURCE=..\jrtp\rtpudpv4transmitter.cpp
# End Source File
# Begin Source File

SOURCE=..\jrtp\rtpudpv4transmitter.h
# End Source File
# Begin Source File

SOURCE=..\jrtp\rtpudpv6transmitter.cpp
# End Source File
# Begin Source File

SOURCE=..\jrtp\rtpudpv6transmitter.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
