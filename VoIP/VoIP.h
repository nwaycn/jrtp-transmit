// VoIP.h : main header file for the VOIP application
//

#if !defined(AFX_VOIP_H__52ED0986_9824_467A_823C_5CDC543D86B3__INCLUDED_)
#define AFX_VOIP_H__52ED0986_9824_467A_823C_5CDC543D86B3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CVoIPApp:
// See VoIP.cpp for the implementation of this class
//

class CVoIPApp : public CWinApp
{
public:
	CVoIPApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVoIPApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CVoIPApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VOIP_H__52ED0986_9824_467A_823C_5CDC543D86B3__INCLUDED_)
