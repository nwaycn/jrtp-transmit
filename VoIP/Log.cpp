// Log.cpp: implementation of the CLog class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Log.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLog::CLog()
{
	m_ClassName		= "CLog";
}

CLog::~CLog()
{

}

//////////////////////////////////////////////////////////////////////////
//
// 日志记录
//
void CLog::DebugMsg(const char *pszFormat, ...)
{
	char buf[1024];
	
	sprintf(buf, "[%s]: ", m_ClassName );
	va_list arglist;
	va_start(arglist, pszFormat);
	vsprintf(&buf[strlen(buf)], pszFormat, arglist);
	va_end(arglist);
	strcat(buf, "\n");
	OutputDebugString(buf);
}

//////////////////////////////////////////////////////////////////////////
//
// 消息循环
//
void CLog::TransMessage()
{
	MSG			msg;

	// 消息循环
	while(PeekMessage(&msg,NULL,NULL,NULL,PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

//////////////////////////////////////////////////////////////////////////
//
// 暂停
//
void CLog::MSleep(int iCount, DWORD dwSleep)
{
	int		i;

	for( i=0;i<iCount;i++)
	{
		TransMessage();
		Sleep( dwSleep );
	}
}
