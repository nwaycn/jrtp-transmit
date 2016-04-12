# Microsoft Developer Studio Project File - Name="VoIP" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=VoIP - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "VoIP.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "VoIP.mak" CFG="VoIP - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "VoIP - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "VoIP - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "VoIP - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\jrtp" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 G729a.lib /nologo /subsystem:windows /machine:I386 /out:"..\Bin\VoIP.exe" /libpath:"..\Bin"

!ELSEIF  "$(CFG)" == "VoIP - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\jrtp" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 G729a.lib /nologo /subsystem:windows /debug /machine:I386 /out:"..\Bin\VoIP.exe" /pdbtype:sept /libpath:"..\Bin"

!ENDIF 

# Begin Target

# Name "VoIP - Win32 Release"
# Name "VoIP - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\CommClient.cpp
# End Source File
# Begin Source File

SOURCE=.\Log.cpp
# End Source File
# Begin Source File

SOURCE=.\RTPTransSession.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\VoIP.cpp
# End Source File
# Begin Source File

SOURCE=.\VoIP.rc
# End Source File
# Begin Source File

SOURCE=.\VoIPDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\WavePlayback.cpp
# End Source File
# Begin Source File

SOURCE=.\WaveRecord.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\CommClient.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\RTPTransSession.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\VoIP.h
# End Source File
# Begin Source File

SOURCE=.\VoIPDlg.h
# End Source File
# Begin Source File

SOURCE=.\WavePlayback.h
# End Source File
# Begin Source File

SOURCE=.\WaveRecord.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\VoIP.ico
# End Source File
# Begin Source File

SOURCE=.\res\VoIP.rc2
# End Source File
# Begin Source File

SOURCE=".\²¥·Å´óÌü.ico"
# End Source File
# End Group
# Begin Group "AudioCoder"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\AudioCode.cpp
# End Source File
# Begin Source File

SOURCE=.\AudioCode.h
# End Source File
# Begin Source File

SOURCE=.\MixIn.cpp
# End Source File
# Begin Source File

SOURCE=.\MixIn.h
# End Source File
# Begin Source File

SOURCE=.\MixOut.cpp
# End Source File
# Begin Source File

SOURCE=.\MixOut.h
# End Source File
# Begin Source File

SOURCE=.\WaveIn.cpp
# End Source File
# Begin Source File

SOURCE=.\WaveIn.h
# End Source File
# Begin Source File

SOURCE=.\WaveOut.cpp
# End Source File
# Begin Source File

SOURCE=.\WaveOut.h
# End Source File
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
# Begin Group "Encoder"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\encoder\coder.cpp
# End Source File
# Begin Source File

SOURCE=.\encoder\countbit.cpp
# End Source File
# Begin Source File

SOURCE=.\encoder\dct.cpp
# End Source File
# Begin Source File

SOURCE=.\encoder\Global.cpp
# End Source File
# Begin Source File

SOURCE=.\encoder\huffman.cpp
# End Source File
# Begin Source File

SOURCE=.\encoder\libr263.cpp
# End Source File
# Begin Source File

SOURCE=.\encoder\mot_est.cpp
# End Source File
# Begin Source File

SOURCE=.\encoder\pred.cpp
# End Source File
# Begin Source File

SOURCE=.\encoder\quant.cpp
# End Source File
# Begin Source File

SOURCE=.\encoder\rlib.cpp
# End Source File
# Begin Source File

SOURCE=.\encoder\stream.cpp
# End Source File
# End Group
# Begin Group "Decoder"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\decoder\convert.cpp
# End Source File
# Begin Source File

SOURCE=.\decoder\DGlobal.cpp
# End Source File
# Begin Source File

SOURCE=.\decoder\GetBits.cpp
# End Source File
# Begin Source File

SOURCE=.\decoder\GetBlk.cpp
# End Source File
# Begin Source File

SOURCE=.\decoder\GetHdr.cpp
# End Source File
# Begin Source File

SOURCE=.\decoder\GetPic.cpp
# End Source File
# Begin Source File

SOURCE=.\decoder\GetVlc.cpp
# End Source File
# Begin Source File

SOURCE=.\decoder\Idct.cpp
# End Source File
# Begin Source File

SOURCE=.\decoder\Idctref.cpp
# End Source File
# Begin Source File

SOURCE=.\decoder\Indices.cpp
# End Source File
# Begin Source File

SOURCE=.\decoder\Recon.cpp
# End Source File
# Begin Source File

SOURCE=.\decoder\Sac.cpp
# End Source File
# Begin Source File

SOURCE=.\decoder\Sactbls.cpp
# End Source File
# Begin Source File

SOURCE=.\decoder\Tmndec.cpp
# End Source File
# Begin Source File

SOURCE=.\decoder\YuvToRgb.cpp
# End Source File
# End Group
# Begin Group "VideoCoder"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\VideoCapture.cpp
# End Source File
# Begin Source File

SOURCE=.\VideoCapture.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
