// WaveRecord.h: interface for the CWaveRecord class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WAVERECORD_H__02D23E96_405A_46D9_918B_9A6BEEC228B9__INCLUDED_)
#define AFX_WAVERECORD_H__02D23E96_405A_46D9_918B_9A6BEEC228B9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxmt.h>
#include "WaveIn.h"
#include "AudioCode.h"
#include "CommClient.h"

class CWaveRecord : public CWaveIn  
{
public:
	void SetCommClient(CCommClient* pClient);
	CWaveRecord(CAudioCode* pCode);
	virtual ~CWaveRecord();

	//////////////////////////////////////////////////////////////////////////
	//
	// ���ݻ�ȡ�ص�
	//
	virtual void GetData(char *pBuffer,int iLen);

	//////////////////////////////////////////////////////////////////////////
	//
	// ��ʼ��������ȡ�ӿ�
	//
	BOOL Init();
protected:
	BOOL IsHaveWav(char* pBuffer, int iLen);
	// �Ƿ�����������
	BOOL				m_bSend;
	// ������Դ��
	CCriticalSection	m_soLock;
	// ��������
	char				m_AudioBuffer[102400];
	// ������
	CAudioCode*			m_pACode;
	// ����ͨ�Žӿ�
	CCommClient*		m_pCommClient;
};

#endif // !defined(AFX_WAVERECORD_H__02D23E96_405A_46D9_918B_9A6BEEC228B9__INCLUDED_)
