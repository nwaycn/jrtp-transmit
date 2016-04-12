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
	
	// ��ʼ����ʾ
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

	// ��ȡ����
	dataBuffer	= pack->GetPayloadData();
	dataLength	= pack->GetPayloadLength();

	// ��������
	pSeedHead	= (PTR_SEED_HEAD)dataBuffer;
	if ( pSeedHead->DataPostion + dataLength - sizeof(SEED_HEAD) == pSeedHead->DataLength )
	{
		//
		// ת������
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
					
					// ������ʱ�����������ݶ�ʧ
					RTPTime::Wait(delay);
					
					// ת���ݴ�����
					SendPacket((void *)dataBuffer,dataLength,0,false,100);
					
					m_lSendTotalSize	= m_lSendTotalSize + dataLength;
					printf( "ת�����ݣ�%10d bytes.\r", m_lSendTotalSize );
					
					// ɾ���ݴ�����
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
	printf("�½����� <== [%s:%d]\n", inet_ntoa(inaddr), port );

	m_lRecvTotalSize	= 0;
	// �������ӳɹ���Ϣ
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
	printf("\n�ر����� <== [%s:%d]\n", inet_ntoa(inaddr), port );
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
	printf("\nɾ������ <== [%s:%d]\n", inet_ntoa(inaddr), port );
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

				// ����
				dataBuffer	= pack->GetPayloadData();
				dataLength	= pack->GetPayloadLength();
				
				// ����
				SendPacket((void *)dataBuffer,dataLength,0,false,10);

				m_lRecvTotalSize	= m_lRecvTotalSize + dataLength;
				printf( "ת�����ݣ�%10d bytes.\r", m_lRecvTotalSize );

				// ɾ��
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
				
				// ����
				dataBuffer	= pack->GetPayloadData();
				dataLength	= pack->GetPayloadLength();
				
				// ������ʱ�����������ݶ�ʧ
//				RTPTime::Wait(delay);
				
				// ת���ݴ�����
				m_pSendSession->SendPacket((void *)dataBuffer,dataLength,0,false,100);
				
//				m_lSendTotalSize	= m_lSendTotalSize + dataLength;
//				printf( "ת�����ݣ�%10d bytes.\r", m_lSendTotalSize );
				printf( "ת�����ݣ�-- %c --\r", m_Table[m_Cnt++] );
				m_Cnt	= m_Cnt & 0x7;
				
				// ɾ��
				DeletePacket(pack);
			}
		} while (GotoNextSourceWithData());
	}
	
	EndDataAccess();

//	printf("\n");
}

//////////////////////////////////////////////////////////////////////////
//
// �ȴ����ݵ���
//
BOOL RTPAppSession::WaitForRecvData()
{
	MSG			msg;
	
	while ( WaitForSingleObject( m_hRecvDataEvent, 10 ) == WAIT_TIMEOUT )
	{
		// ��Ϣѭ��
		while(PeekMessage(&msg,NULL,NULL,NULL,PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return TRUE;
}
