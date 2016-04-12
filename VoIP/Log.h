// Log.h: interface for the CLog class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOG_H__8665DA83_FC89_4CE8_A12E_310E48DFED48__INCLUDED_)
#define AFX_LOG_H__8665DA83_FC89_4CE8_A12E_310E48DFED48__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//////////////////////////////////////////////////////////////////////////
//
// 存储块对象
//
class CMemory
{
public:
	CMemory()
	{
		m_pBuffer	= NULL;
		m_uiSize	= 0;
	}
	virtual ~CMemory()
	{
		free( m_pBuffer );
		m_pBuffer	= NULL;
		m_uiSize	= 0;
	}
public:
	char*	GetBuffer()
	{
		return m_pBuffer;
	}
	UINT	GetSize()
	{
		return m_uiSize;
	}
	void	SetBuffer(char* pBuffer, UINT uiSize)
	{
		free( m_pBuffer );
		m_pBuffer	= (char*)malloc( uiSize );
		m_uiSize	= uiSize;
		memcpy( m_pBuffer, pBuffer, uiSize );
	}
protected:
	char*	m_pBuffer;
	UINT	m_uiSize;
};

class CLog  
{
public:
	CLog();
	virtual ~CLog();
protected:
	void MSleep(int iCount, DWORD dwSleep);
	void TransMessage();
	CString		m_ClassName;

	//////////////////////////////////////////////////////////////////////////
	//
	// 日志显示
	//
	void DebugMsg(const char *pszFormat, ...);
};

#endif // !defined(AFX_LOG_H__8665DA83_FC89_4CE8_A12E_310E48DFED48__INCLUDED_)
