/*---------------------------------------------------------------------------*/
/* RtpSessionWrapper.h
/* Since the RTPSession class creates a background thread that processes
/*  incomming RTP & RTCP packets, the class is derived from so that the
/*  callback methods can be overridden.
/*---------------------------------------------------------------------------*/
#ifndef _RTPAPPSESSION_H_
#define _RTPAPPSESSION_H_

#include "rtpsession.h"
#include "rtppacket.h"
#include "rtpudpv4transmitter.h"
#include "rtpipv4address.h"
#include "rtpsessionparams.h"
#include "rtperrors.h"
#include "rtpsourcedata.h"

#include "..\VoIP\defines.h"


/*------------------------------------------*/
/* RTPAppSession
/*------------------------------------------*/
class RTPAppSession : public RTPSession
{
public:
	BOOL WaitForRecvData();
	RTPAppSession(RTPSession* pSendSession);
	~RTPAppSession();
	
	void Trans();
	virtual void OnRTPPacket(RTPPacket *pack, const RTPTime &receivetime, const RTPAddress *senderaddress);
protected:
	long		m_lSendTotalSize;
	long		m_lRecvTotalSize;
	HANDLE		m_hRecvDataEvent;

	int			m_Cnt;
	char		m_Table[10];

	// ·¢ËÍSession
	RTPSession*		m_pSendSession;

	void OnNewSource(RTPSourceData *dat);
	void OnBYEPacket(RTPSourceData *dat);
	void OnRemoveSource(RTPSourceData *dat);
	void OnPollThreadStep();
	void ProcessRTPPacket(const RTPSourceData &srcdat,const RTPPacket &rtppack);
};

#endif