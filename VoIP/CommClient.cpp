// CommClient.cpp: implementation of the CCommClient class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "VoIP.h"
#include "CommClient.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCommClient::CCommClient()
{
	WSADATA				dat;

	// ��ʼ��Socket
	WSAStartup(MAKEWORD(2,2),&dat);

	m_Sequence		= 0;
}

CCommClient::~CCommClient()
{
	// �ͷ���Դ
	WSACleanup();	
}

//////////////////////////////////////////////////////////////////////////
//
// ����ת��������
//
BOOL CCommClient::ConnectServer()
{
	RTPUDPv4TransmissionParams		transparams;
	RTPSessionParams				sessparams;
	int								status;
	uint32_t						utServerIP;
	RTPIPv4Address					addr;
		
	// ����ͨ��ID
	CoCreateGuid( &m_CommID );
	m_TransSession.SetCommID( m_CommID );
	
	// ת��Server��ַ
	utServerIP		= ntohl( inet_addr( m_szServerIP ) );
	
	sessparams.SetOwnTimestampUnit( 1.0/8000.0 );
	sessparams.SetMaximumPacketSize( 64000 );
	sessparams.SetAcceptOwnPackets( true );
	sessparams.SetSourceTimeoutMultiplier( 50 );
	sessparams.SetUsePollThread( true );
	transparams.SetPortbase( 7000 );
	m_TransSession.Create( sessparams, &transparams );
	m_TransSession.SetMessageWindows( m_wMessageWnd );

	RTPIPv4Address SendAddr( utServerIP, m_uiServerPort );
	status = m_TransSession.AddDestination( SendAddr );
	transparams.SetPortbase( 7002 );
	m_RecvSession.Create( sessparams, &transparams );
	m_RecvSession.SetMessageWindows( m_wMessageWnd );
	
	RTPIPv4Address RecvAddr( utServerIP, m_uiLocalPort );
	status = m_RecvSession.AddDestination( RecvAddr );
	m_TransSession.SetDefaultPayloadType( 0 );
	m_TransSession.SetDefaultMark( false );
	m_TransSession.SetDefaultTimestampIncrement( 10 );
	

	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
//
// ���ñ��ض˿�
//
void CCommClient::SetLocalPort(UINT uiLocalPort)
{
	m_uiLocalPort	= uiLocalPort;
}

//////////////////////////////////////////////////////////////////////////
//
// ������Ϣ֪ͨ���ھ��
//
void CCommClient::SetMessageWindows(HWND hWnd)
{
	m_wMessageWnd	= hWnd;
}

void CCommClient::SetTransServer(const char *szServerIP, UINT uiServerPort)
{
	m_szServerIP	= szServerIP;
	m_uiServerPort	= uiServerPort;
}

//////////////////////////////////////////////////////////////////////////
//
// ��������
//
BOOL CCommClient::SendPacket(const char *pDataBuffer, UINT uiDataSize, UINT DataType)
{
	char*			pSendBuffer;
	PTR_SEED_HEAD	pSeedHead;
	int				iSendSize;
	
	iSendSize		= uiDataSize + sizeof(SEED_HEAD);
	pSendBuffer		= (char*)malloc( iSendSize );
	memset( pSendBuffer, 0, iSendSize );
	
	pSeedHead		= (PTR_SEED_HEAD)pSendBuffer;
	memcpy( pSeedHead, &m_CommID, sizeof(GUID) );
	pSeedHead->DataLength	= uiDataSize;
	pSeedHead->DataPostion	= m_Sequence++;
	pSeedHead->DataType		= DataType;

	memcpy( pSendBuffer+sizeof(SEED_HEAD), pDataBuffer, uiDataSize );

	// ��������
	m_TransSession.SendPacket( pSendBuffer, iSendSize );

	free( pSendBuffer );

	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
//
// ע��������
//
void CCommClient::DisconnectServer()
{
	m_TransSession.BYEDestroy(RTPTime(10,0),0,0);
}
