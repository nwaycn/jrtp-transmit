// CommClient.h: interface for the CCommClient class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COMMCLIENT_H__765C02F7_1650_4A04_9566_54820C554DEA__INCLUDED_)
#define AFX_COMMCLIENT_H__765C02F7_1650_4A04_9566_54820C554DEA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "RTPTransSession.h"

class CCommClient  
{
public:
	void DisconnectServer();
	void SetTransServer(const char *szServerIP, UINT uiServerPort);
	void SetMessageWindows(HWND hWnd);
	void SetLocalPort(UINT uiLocalPort);
	BOOL ConnectServer();
	CCommClient();
	virtual ~CCommClient();

	//////////////////////////////////////////////////////////////////////////
	//
	// ·¢ËÍÊý¾Ý
	//
	BOOL SendPacket(const char* pDataBuffer, UINT uiDataSize, UINT DataType);
protected:
	CRTPTransSession	m_TransSession;
	CRTPTransSession	m_RecvSession;
	CString				m_szServerIP;
	UINT				m_uiServerPort;
	UINT				m_uiLocalPort;
	HWND				m_wMessageWnd;
	DWORD				m_Sequence;
	GUID				m_CommID;
};

#endif // !defined(AFX_COMMCLIENT_H__765C02F7_1650_4A04_9566_54820C554DEA__INCLUDED_)
