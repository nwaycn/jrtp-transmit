// WavePlayback.cpp: implementation of the CWavePlayback class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "VoIP.h"
#include "WavePlayback.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CWavePlayback::CWavePlayback(CAudioCode* pCode)
{
	m_ClassName	= "Playback";
	m_pACode	= pCode;
}

CWavePlayback::~CWavePlayback()
{

}

BOOL CWavePlayback::Playback(char *pBuffer, UINT uiSize)
{
	int			iOut;

	iOut	= sizeof( m_AudioBuffer );
	memset( m_AudioBuffer, 0, iOut );
	m_pACode->DecodeAudioData ( pBuffer, uiSize, m_AudioBuffer, &iOut );
	Play( m_AudioBuffer, iOut );

	return TRUE;
}

