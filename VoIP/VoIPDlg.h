// VoIPDlg.h : header file
//

#if !defined(AFX_VOIPDLG_H__FC2C2A51_E0F0_4134_96F0_A41A2558455F__INCLUDED_)
#define AFX_VOIPDLG_H__FC2C2A51_E0F0_4134_96F0_A41A2558455F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "WaveRecord.h"
#include "WavePlayback.h"
//#include "VideoCapture.h"
#include "CommClient.h"
#include "VideoCaptureDshow.h"

/////////////////////////////////////////////////////////////////////////////
// CVoIPDlg dialog

class CVoIPDlg : public CDialog
{
// Construction
public:
	void InitALL();
	CVoIPDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CVoIPDlg)
	enum { IDD = IDD_VOIP_DIALOG };
	CButton	m_bnClose;
	CButton	m_bnLogout;
	CStatic	m_LocalScreen;
	CStatic	m_RemoteScreen;
	CProgressCtrl	m_pgVideo;
	CProgressCtrl	m_pgAudio;
	CButton	m_bnLogin;
	UINT	m_uiSendPort;
	UINT	m_uiRecvPort;
	CString	m_szServerIP;
	BOOL	m_bSelf;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVoIPDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CVoIPDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnLogin();
	afx_msg void OnDestroy();
	afx_msg void OnLogout();
	afx_msg void OnButton1();
	afx_msg LRESULT OnRecvAudioMessage(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnRecvVideoMessage(WPARAM wParam, LPARAM lParam);
	afx_msg void OnCkself();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
protected:
	CAudioCode			m_ACode;	
	CCommClient			m_CommClient;
	CWaveRecord*		m_pWaveRecord;
	CWavePlayback*		m_pWavePlayback;

	// 视频采集对象
	//VideoCapture*		m_pVideoCapture;
	CVideoCaptureDshow capshow;

	//////////////////////////////////////////////////////////////////////////
	//
	// 视频采集回调
	//
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VOIPDLG_H__FC2C2A51_E0F0_4134_96F0_A41A2558455F__INCLUDED_)
