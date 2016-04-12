/*---------------------------------------------------------------------------*/
/* RTPAppSession.cpp
/*---------------------------------------------------------------------------*/
#include "RTPAppSession.h"
#include "rtpipv4address.h"

RTPAppSession::RTPAppSession(RTPSession* pSendSession)
{
	m_hRecvDataEvent	= CreateEvent( 
        NULL,			// default security attributes
        FALSE,			// manual-reset event
        FALSE,			// initial state is signaled
        NULL			// object name
        ); 
	
	// 初始化显示
	strcpy( m_Table, "/-\\||/-|" );
	m_Cnt	= 0;

	m_pSendSession		= pSendSession;
}

RTPAppSession::~RTPAppSession()
{
	CloseHandle( m_hRecvDataEvent );
}

/*------------------------------------------*/
/* OnRTPPacket
/*------------------------------------------*/
void RTPAppSession::OnRTPPacket(RTPPacket *pack, const RTPTime &receivetime, const RTPAddress *senderaddress)
{
	SetEvent( m_hRecvDataEvent );
	return ;

	uint8_t*		dataBuffer;
	size_t			dataLength;
	PTR_SEED_HEAD	pSeedHead;

	// 提取数据
	dataBuffer	= pack->GetPayloadData();
	dataLength	= pack->GetPayloadLength();

	// 分析数据
	pSeedHead	= (PTR_SEED_HEAD)dataBuffer;
	if ( pSeedHead->DataPostion + dataLength - sizeof(SEED_HEAD) == pSeedHead->DataLength )
	{
		//
		// 转发数据
		//
		m_lSendTotalSize	= 0;

		BeginDataAccess();

		if (GotoFirstSourceWithData())
		{
			do
			{
				RTPPacket*		pack;
				RTPTime			delay(0.50);
								
				while ((pack = GetNextPacket()) != NULL)
				{
					dataBuffer	= pack->GetPayloadData();
					dataLength	= pack->GetPayloadLength();
					
					// 必须延时，否则有数据丢失
					RTPTime::Wait(delay);
					
					// 转发暂存数据
					SendPacket((void *)dataBuffer,dataLength,0,false,100);
					
					m_lSendTotalSize	= m_lSendTotalSize + dataLength;
					printf( "转发数据：%10d bytes.\r", m_lSendTotalSize );
					
					// 删除暂存数据
					DeletePacket(pack);
				}
			} while (GotoNextSourceWithData());
		}
		
		EndDataAccess();
	}
}

void RTPAppSession::OnNewSource(RTPSourceData *dat)
{
	if (dat->IsOwnSSRC())
		return;
	
	uint32_t ip;
	uint16_t port;
	
	if (dat->GetRTPDataAddress() != 0)
	{
		const RTPIPv4Address *addr = (const RTPIPv4Address *)(dat->GetRTPDataAddress());
		ip = addr->GetIP();
		port = addr->GetPort();
	}
	else if (dat->GetRTCPDataAddress() != 0)
	{
		const RTPIPv4Address *addr = (const RTPIPv4Address *)(dat->GetRTCPDataAddress());
		ip = addr->GetIP();
		port = addr->GetPort()-1;
	}
	else
		return;
	
	RTPIPv4Address dest(ip,port);
	m_pSendSession->AddDestination(dest);
	
	struct in_addr inaddr;
	inaddr.s_addr = htonl(ip);
	printf("新建连接 <== [%s:%d]\n", inet_ntoa(inaddr), port );

	m_lRecvTotalSize	= 0;
	// 发送连接成功消息
//	SendPacket((void *)"hello",strlen("hello"),0,false,6);
}

void RTPAppSession::OnBYEPacket(RTPSourceData *dat)
{
	if (dat->IsOwnSSRC())
		return;
	
	uint32_t ip;
	uint16_t port;
	
	if (dat->GetRTPDataAddress() != 0)
	{
		const RTPIPv4Address *addr = (const RTPIPv4Address *)(dat->GetRTPDataAddress());
		ip = addr->GetIP();
		port = addr->GetPort();
	}
	else if (dat->GetRTCPDataAddress() != 0)
	{
		const RTPIPv4Address *addr = (const RTPIPv4Address *)(dat->GetRTCPDataAddress());
		ip = addr->GetIP();
		port = addr->GetPort()-1;
	}
	else
		return;
	
	RTPIPv4Address dest(ip,port);
	m_pSendSession->DeleteDestination(dest);
	
	struct in_addr inaddr;
	inaddr.s_addr = htonl(ip);
	printf("\n关闭连接 <== [%s:%d]\n", inet_ntoa(inaddr), port );
}

void RTPAppSession::OnRemoveSource(RTPSourceData *dat)
{
	if (dat->IsOwnSSRC())
		return;
	if (dat->ReceivedBYE())
		return;
	
	uint32_t ip;
	uint16_t port;
	
	if (dat->GetRTPDataAddress() != 0)
	{
		const RTPIPv4Address *addr = (const RTPIPv4Address *)(dat->GetRTPDataAddress());
		ip = addr->GetIP();
		port = addr->GetPort();
	}
	else if (dat->GetRTCPDataAddress() != 0)
	{
		const RTPIPv4Address *addr = (const RTPIPv4Address *)(dat->GetRTCPDataAddress());
		ip = addr->GetIP();
		port = addr->GetPort()-1;
	}
	else
		return;
	
	RTPIPv4Address dest(ip,port);
	m_pSendSession->DeleteDestination(dest);
	
	struct in_addr inaddr;
	inaddr.s_addr = htonl(ip);
	printf("\n删除连接 <== [%s:%d]\n", inet_ntoa(inaddr), port );
}

void RTPAppSession::OnPollThreadStep()
{
	SetEvent( m_hRecvDataEvent );
	
	return ;

	BeginDataAccess();
	
	// check incoming packets
	if (GotoFirstSourceWithData())
	{
		do
		{
			RTPPacket *pack;
			RTPSourceData *srcdat;
			
			srcdat = GetCurrentSourceInfo();
			
			while ((pack = GetNextPacket()) != NULL)
			{
				uint8_t*		dataBuffer;
				size_t			dataLength;

				// 分离
				dataBuffer	= pack->GetPayloadData();
				dataLength	= pack->GetPayloadLength();
				
				// 发送
				SendPacket((void *)dataBuffer,dataLength,0,false,10);

				m_lRecvTotalSize	= m_lRecvTotalSize + dataLength;
				printf( "转发数据：%10d bytes.\r", m_lRecvTotalSize );

				// 删除
				DeletePacket(pack);
			}
		} while (GotoNextSourceWithData());
	}
	
	EndDataAccess();
}

void RTPAppSession::ProcessRTPPacket(const RTPSourceData &srcdat,const RTPPacket &rtppack)
{
}


void RTPAppSession::Trans()
{
	ResetEvent( m_hRecvDataEvent );
	
	BeginDataAccess();
	
	// check incoming packets
	if (GotoFirstSourceWithData())
	{
		do
		{
			RTPPacket *pack;
			RTPSourceData *srcdat;
			
			srcdat = GetCurrentSourceInfo();
			
			while ((pack = GetNextPacket()) != NULL)
			{
				uint8_t*		dataBuffer;
				size_t			dataLength;
				RTPTime			delay(0.10);
				
				// 分离
				dataBuffer	= pack->GetPayloadData();
				dataLength	= pack->GetPayloadLength();
				
				// 必须延时，否则有数据丢失
//				RTPTime::Wait(delay);
				
				// 转发暂存数据
				m_pSendSession->SendPacket((void *)dataBuffer,dataLength,0,false,100);
				
//				m_lSendTotalSize	= m_lSendTotalSize + dataLength;
//				printf( "转发数据：%10d bytes.\r", m_lSendTotalSize );
				printf( "转发数据：-- %c --\r", m_Table[m_Cnt++] );
				m_Cnt	= m_Cnt & 0x7;
				
				// 删除
				DeletePacket(pack);
			}
		} while (GotoNextSourceWithData());
	}
	
	EndDataAccess();

//	printf("\n");
}

//////////////////////////////////////////////////////////////////////////
//
// 等待数据到达
//
BOOL RTPAppSession::WaitForRecvData()
{
	MSG			msg;
	
	while ( WaitForSingleObject( m_hRecvDataEvent, 10 ) == WAIT_TIMEOUT )
	{
		// 消息循环
		while(PeekMessage(&msg,NULL,NULL,NULL,PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return TRUE;
}
