// VoIPDlg.cpp : implementation file
//

#include "stdafx.h"
#include "VoIP.h"
#include "VoIPDlg.h"
#include "MixOut.h"
#include "MixIn.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
//#pragma   comment(linker,"/FORCE:MULTIPLE")
#pragma comment( lib, "ws2_32.lib" )

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVoIPDlg dialog

CVoIPDlg::CVoIPDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CVoIPDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CVoIPDlg)
	m_uiSendPort = 0;
	m_uiRecvPort = 0;
	m_szServerIP = _T("");
	m_bSelf = FALSE;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CVoIPDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CVoIPDlg)
	DDX_Control(pDX, IDOK, m_bnClose);
	DDX_Control(pDX, IDC_LOGOUT, m_bnLogout);
	DDX_Control(pDX, IDC_LOCALSCREEN, m_LocalScreen);
	DDX_Control(pDX, IDC_REMOTESCREEN, m_RemoteScreen);
	DDX_Control(pDX, IDC_PGVIDEO, m_pgVideo);
	DDX_Control(pDX, IDC_PGAUDIO, m_pgAudio);
	DDX_Control(pDX, IDC_LOGIN, m_bnLogin);
	DDX_Text(pDX, IDC_SENDPORT, m_uiSendPort);
	DDX_Text(pDX, IDC_RECVPORT, m_uiRecvPort);
	DDX_CBString(pDX, IDC_SERVERIP, m_szServerIP);
	DDX_Check(pDX, IDC_CKSELF, m_bSelf);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CVoIPDlg, CDialog)
	//{{AFX_MSG_MAP(CVoIPDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_LOGIN, OnLogin)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_LOGOUT, OnLogout)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_MESSAGE(WM_AUDIODATA, OnRecvAudioMessage)
	ON_MESSAGE(WM_VIDEODATA, OnRecvVideoMessage)
	ON_BN_CLICKED(IDC_CKSELF, OnCkself)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVoIPDlg message handlers

BOOL CVoIPDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	InitALL();
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CVoIPDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CVoIPDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CVoIPDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CVoIPDlg::OnLogin() 
{
	m_bnLogin.EnableWindow( FALSE );
	m_bnClose.EnableWindow( FALSE );
	m_bnLogout.EnableWindow( TRUE );
	
	UpdateData( TRUE );

	m_CommClient.SetTransServer( m_szServerIP, m_uiSendPort );
	m_CommClient.SetLocalPort( m_uiRecvPort );
	m_CommClient.SetMessageWindows( GetSafeHwnd() );
	m_CommClient.ConnectServer();
	//m_pVideoCapture->StartCapture( m_LocalScreen.GetDC()->m_hDC );	
	capshow.Start(0,m_LocalScreen.GetSafeHwnd());
	m_pWaveRecord->StartRec();
	m_pWavePlayback->StartPlay();

}

void CVoIPDlg::OnDestroy() 
{
	// 关闭语音模块
	m_pWaveRecord->StopRec();
	m_pWavePlayback->StopPlay();

	//m_pVideoCapture->StopCapture();
	
	m_CommClient.DisconnectServer();
	delete	m_pWaveRecord;
	delete	m_pWavePlayback;
	//delete	m_pVideoCapture;

	CDialog::OnDestroy();
}

void CVoIPDlg::InitALL()
{
	// 初始化界面元素
	m_uiSendPort	= 8000;
	m_uiRecvPort	= 8002;
	m_bSelf			= FALSE;
	m_szServerIP	= "127.0.0.1";

	UpdateData( FALSE );

	m_pgAudio.SetRange( 0, 1000 );
	m_pgVideo.SetRange( 0, 1000 );
	
	m_pWaveRecord		= new CWaveRecord( &m_ACode );
	m_pWaveRecord->SetCommClient( &m_CommClient );
	m_pWavePlayback		= new CWavePlayback( &m_ACode );
	//m_pVideoCapture		= new VideoCapture;
	//m_pVideoCapture->Initialize();
	//m_pVideoCapture->SetCommClient( &m_CommClient );
	capshow.SetCommClient(&m_CommClient);

	// 调整音频
//	CMixOut	MixOut;
//
//	MixOut.Ini();
//	MixOut.SetCurrentVolume( MixOut.GetMaximalVolume() );
//	MixOut.UnIni();

}

void CVoIPDlg::OnLogout() 
{
	m_bnLogout.EnableWindow( FALSE );
	//m_pVideoCapture->StopCapture();
	m_pWaveRecord->StopRec();
	m_pWavePlayback->StopPlay();
	m_CommClient.DisconnectServer();
	m_bnLogin.EnableWindow( TRUE );
	m_bnClose.EnableWindow( TRUE );
}

void CVoIPDlg::OnButton1() 
{

	CMixIn*			pMixIn;
	
	pMixIn		= new CMixIn;
	pMixIn->Ini();
	pMixIn->SetCurrentVolume( pMixIn->GetMaximalVolume() / 2 );
	pMixIn->UnIni();
	
	delete pMixIn;

	CMixOut*		pMixOut;

	pMixOut		= new CMixOut;
	pMixOut->Ini();
	pMixOut->SetCurrentVolume( pMixOut->GetMaximalVolume() / 2 );
	pMixOut->UnIni();

	delete pMixOut;
}

LRESULT CVoIPDlg::OnRecvAudioMessage(WPARAM wParam, LPARAM lParam)
{
	PTR_SEED_HEAD	pSeedHead;
	char*			pAudioBuffer;
	UINT			uiSize;
	
	m_pgAudio.StepIt();
	if ( m_pgAudio.GetPos() == 1000 )
	{
		m_pgAudio.SetPos( 0 );
	}
	if ( wParam == 0 )
	{
		return TRUE;
	}
	pSeedHead		= (PTR_SEED_HEAD)lParam;
	pAudioBuffer	= (char*)pSeedHead + sizeof(SEED_HEAD);
	uiSize			= pSeedHead->DataLength;
	m_pWavePlayback->Playback( pAudioBuffer, uiSize );
	
	return 0;
}

LRESULT CVoIPDlg::OnRecvVideoMessage(WPARAM wParam, LPARAM lParam)
{
	PTR_SEED_HEAD	pSeedHead;
	char*			pVideoBuffer;
	UINT			uiSize;
	
	m_pgVideo.StepIt();
	if ( m_pgVideo.GetPos() == 1000 )
	{
		m_pgVideo.SetPos( 0 );
	}
	if ( wParam == 0 )
	{
		if ( !m_bSelf )
		{
			return TRUE;
		}
	}
	pSeedHead		= (PTR_SEED_HEAD)lParam;
	pVideoBuffer	= (char*)pSeedHead + sizeof(SEED_HEAD);
	uiSize			= pSeedHead->DataLength;
	//m_pVideoCapture->DrawRemoteScreen( pVideoBuffer, uiSize, m_RemoteScreen.GetDC()->m_hDC );
	CDC* pdc=m_RemoteScreen.GetDC();
	capshow.DrawRemoteScreen(pVideoBuffer,uiSize,pdc);
	m_RemoteScreen.ReleaseDC(pdc);
	return 0;
}

void CVoIPDlg::OnCkself() 
{
	UpdateData( TRUE );
}
