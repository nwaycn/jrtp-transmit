// RTPTransSession.cpp: implementation of the CRTPTransSession class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "VoIP.h"
#include "RTPTransSession.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRTPTransSession::CRTPTransSession()
{
	m_hRecvDataEvent	= CreateEvent( 
        NULL,			// default security attributes
        FALSE,			// manual-reset event
        FALSE,			// initial state is signaled
        NULL			// object name
        );

	m_hStopRecvEvent	= CreateEvent( 
        NULL,			// default security attributes
        FALSE,			// manual-reset event
        FALSE,			// initial state is signaled
        NULL			// object name
        );

	m_hStoppedEvent	= CreateEvent( 
        NULL,			// default security attributes
        FALSE,			// manual-reset event
        FALSE,			// initial state is signaled
        NULL			// object name
        );

	_beginthread( RecvDataThread, NULL, this );
}

CRTPTransSession::~CRTPTransSession()
{
	SetEvent( m_hStopRecvEvent );

	if ( WaitForSingleObject( m_hStoppedEvent, 5000 ) == WAIT_TIMEOUT )
	{
		AfxMessageBox( "Timeout" );
	}

	CloseHandle( m_hRecvDataEvent );
	CloseHandle( m_hStopRecvEvent );
	CloseHandle( m_hStoppedEvent );
}

void CRTPTransSession::SetMessageWindows(HWND hWnd)
{
	m_wMessageWnd	= hWnd;
}


void CRTPTransSession::OnRTPPacket(RTPPacket *pack, const RTPTime &receivetime, const RTPAddress *senderaddress)
{
	SetEvent( m_hRecvDataEvent );
}

//////////////////////////////////////////////////////////////////////////
//
// 数据处理
//
void CRTPTransSession::DealwithData()
{
	WPARAM			wParam;
	LPARAM			lParam;
	RTPPacket*		pack;
	
	ResetEvent( m_hRecvDataEvent );

	BeginDataAccess();
	
	// check incoming packets
	if (GotoFirstSourceWithData())
	{
		do
		{			
			while ((pack = GetNextPacket()) != NULL)
			{
				uint8_t*		dataBuffer;
				size_t			dataLength;
				PTR_SEED_HEAD	pSeedHead;
				
				// 保存结束数据
				dataBuffer	= pack->GetPayloadData();
				dataLength	= pack->GetPayloadLength();
				
				pSeedHead	= (PTR_SEED_HEAD)dataBuffer;

				if ( pSeedHead->DataType == PACKET_AUDIO )
				{
					wParam		= memcmp( pSeedHead, &m_CommID, sizeof(GUID) );
					lParam		= (LPARAM)dataBuffer;
					SendMessage( m_wMessageWnd, WM_AUDIODATA, wParam, lParam );
				}
				if ( pSeedHead->DataType == PACKET_VIDEO )
				{
					wParam		= memcmp( pSeedHead, &m_CommID, sizeof(GUID) );
					lParam		= (LPARAM)dataBuffer;
					SendMessage( m_wMessageWnd, WM_VIDEODATA, wParam, lParam );
				}
				DeletePacket(pack);
			}
		} while (GotoNextSourceWithData());
	}
	
	EndDataAccess();
}

void CRTPTransSession::SetCommID(GUID CommID)
{
	m_CommID		= CommID;
}

//////////////////////////////////////////////////////////////////////////
//
// 数据接收线程
//
void CRTPTransSession::RecvDataThread(void *pParam)
{
	CRTPTransSession*		pSession;
	MSG						msg;
	RTPTime					delay(0.10);
	
	pSession		= (CRTPTransSession*)pParam;

	while ( WaitForSingleObject( pSession->m_hStopRecvEvent, 10 ) == WAIT_TIMEOUT )
	{
		while ( WaitForSingleObject( pSession->m_hRecvDataEvent, 10 ) == WAIT_TIMEOUT )
		{
			while(PeekMessage(&msg,NULL,NULL,NULL,PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		pSession->DealwithData();
	}

	SetEvent( pSession->m_hStoppedEvent );
}
