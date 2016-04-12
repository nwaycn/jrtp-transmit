// WaveRecord.cpp: implementation of the CWaveRecord class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "VoIP.h"
#include "WaveRecord.h"
#include "defines.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CWaveRecord::CWaveRecord(CAudioCode* pCode)
{
	m_bSend		= TRUE;
	m_pACode	= pCode;
}

CWaveRecord::~CWaveRecord()
{

}

//////////////////////////////////////////////////////////////////////////
//
// ���ݻ�ȡ�ص�
//
void CWaveRecord::GetData(char *pBuffer, int iLen)
{
	char			oldAudio[10240];
	int				ioldSize;
	int				iEncodeSize;

	m_soLock.Lock();
	if (m_bSend)
	{
		// ����Ƿ����ھ�������
//		if ( IsHaveWav(pBuffer, iLen) )
		{
//			ioldSize	= iLen;
//
//			memcpy( oldAudio, pBuffer, ioldSize );
//
//			iEncodeSize = sizeof(m_AudioBuffer);
//			memset( m_AudioBuffer, 0, iEncodeSize );
			m_pACode->EncodeAudioData ( pBuffer, iLen, m_AudioBuffer, &iEncodeSize );

//			m_pCommClient->SendPacket( pBuffer, iLen, PACKET_AUDIO );
			m_pCommClient->SendPacket( m_AudioBuffer, iEncodeSize, PACKET_AUDIO );
		}
	}
	m_soLock.Unlock ();
	
	CWaveIn::GetData (pBuffer,iLen);
}

//////////////////////////////////////////////////////////////////////////
//
// ��ʼ��������ȡ�ӿ�
//
BOOL CWaveRecord::Init()
{
	return TRUE;
}

void CWaveRecord::SetCommClient(CCommClient *pClient)
{
	m_pCommClient	= pClient;
}

//////////////////////////////////////////////////////////////////////////
//
// ���������������
//
BOOL CWaveRecord::IsHaveWav(char *pBuffer, int iLen)
{
	int		iCount;
	UCHAR	uValue;

	iCount		= 0;
	for( int i=0;i<iLen;i++ )
	{
		uValue = (UCHAR)pBuffer[i];
		if( uValue<=125 || uValue>=129 )
		{
			iCount++;
		}
	}

	return iCount > 500;
}
