// RTPTransSession.h: interface for the CRTPTransSession class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RTPTRANSSESSION_H__11BA506C_0011_4866_A961_91F29E0AEC88__INCLUDED_)
#define AFX_RTPTRANSSESSION_H__11BA506C_0011_4866_A961_91F29E0AEC88__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "rtpsession.h"
#include "rtppacket.h"
#include "rtpudpv4transmitter.h"
#include "rtpipv4address.h"
#include "rtpsessionparams.h"
#include "rtperrors.h"
#include "rtpsourcedata.h"

#include "defines.h"

class CRTPTransSession : public RTPSession  
{
public:
	CRTPTransSession();
	virtual ~CRTPTransSession();

	//////////////////////////////////////////////////////////////////////////
	//
	// ���ݵ���
	//
	virtual void OnRTPPacket(RTPPacket *pack, const RTPTime &receivetime, const RTPAddress *senderaddress);
	void SetCommID(GUID CommID);
	void SetMessageWindows(HWND hWnd);
	
protected:
	// ����ͨ��ID 
	GUID				m_CommID;
	// ��Ϣͨ�Ŵ��ھ��
	HWND				m_wMessageWnd;
	// ���ݵ�����Ϣ
	HANDLE				m_hRecvDataEvent;
	// ����������Ϣ
	HANDLE				m_hStopRecvEvent;
	// ���������Ϣ
	HANDLE				m_hStoppedEvent;
	
	//////////////////////////////////////////////////////////////////////////
	//
	// ���ݴ���
	//
	void DealwithData();

	//////////////////////////////////////////////////////////////////////////
	//
	// ���ݽ����߳�
	//
	static void RecvDataThread(void* pParam);
};

#endif // !defined(AFX_RTPTRANSSESSION_H__11BA506C_0011_4866_A961_91F29E0AEC88__INCLUDED_)
