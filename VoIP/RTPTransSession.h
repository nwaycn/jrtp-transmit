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
	// 数据到达
	//
	virtual void OnRTPPacket(RTPPacket *pack, const RTPTime &receivetime, const RTPAddress *senderaddress);
	void SetCommID(GUID CommID);
	void SetMessageWindows(HWND hWnd);
	
protected:
	// 本次通信ID 
	GUID				m_CommID;
	// 消息通信窗口句柄
	HWND				m_wMessageWnd;
	// 数据到达消息
	HANDLE				m_hRecvDataEvent;
	// 结束接收消息
	HANDLE				m_hStopRecvEvent;
	// 结束完成消息
	HANDLE				m_hStoppedEvent;
	
	//////////////////////////////////////////////////////////////////////////
	//
	// 数据处理
	//
	void DealwithData();

	//////////////////////////////////////////////////////////////////////////
	//
	// 数据接收线程
	//
	static void RecvDataThread(void* pParam);
};

#endif // !defined(AFX_RTPTRANSSESSION_H__11BA506C_0011_4866_A961_91F29E0AEC88__INCLUDED_)
