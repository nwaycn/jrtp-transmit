; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CVoIPDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "VoIP.h"

ClassCount=3
Class1=CVoIPApp
Class2=CVoIPDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_VOIP_DIALOG

[CLS:CVoIPApp]
Type=0
HeaderFile=VoIP.h
ImplementationFile=VoIP.cpp
Filter=N

[CLS:CVoIPDlg]
Type=0
HeaderFile=VoIPDlg.h
ImplementationFile=VoIPDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDOK

[CLS:CAboutDlg]
Type=0
HeaderFile=VoIPDlg.h
ImplementationFile=VoIPDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_VOIP_DIALOG]
Type=1
Class=CVoIPDlg
ControlCount=19
Control1=IDOK,button,1342242817
Control2=IDC_LOGIN,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_RECVPORT,edit,1350633600
Control6=IDC_STATIC,static,1342308352
Control7=IDC_SENDPORT,edit,1350633600
Control8=IDC_PGAUDIO,msctls_progress32,1350565889
Control9=IDC_PGVIDEO,msctls_progress32,1350565889
Control10=IDC_LOGOUT,button,1476460544
Control11=IDC_BUTTON1,button,1342242816
Control12=IDC_STATIC,static,1342308352
Control13=IDC_STATIC,static,1342308352
Control14=IDC_STATIC,button,1342177287
Control15=IDC_STATIC,button,1342177287
Control16=IDC_LOCALSCREEN,static,1342177284
Control17=IDC_REMOTESCREEN,static,1342177284
Control18=IDC_SERVERIP,combobox,1344343042
Control19=IDC_CKSELF,button,1342242819

