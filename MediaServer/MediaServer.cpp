// MediaServer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "RTPAppSession.h"
#include "conio.h"

//#pragma comment( lib, "ws2_32.lib" )
//#pragma comment( lib, "jthread.lib" )
//#pragma comment( lib, "jrtplib.lib" )

void TransdataThread(void* pParam)
{
	RTPAppSession*	pTransSess;

	pTransSess		= (RTPAppSession*)pParam;

	while ( pTransSess->WaitForRecvData() )
	{
		pTransSess->Trans();
	}
}

int main(int argc, char* argv[])
{
	RTPSession		SendSession;	// ���ݷ���Session
	RTPAppSession	sess( &SendSession );
	uint16_t		portbase;		// ���������˿�
	
	// ��ʼ��socket
	WSADATA dat;
	WSAStartup(MAKEWORD(2,2),&dat);
	
	// Now, we'll create a RTP session, set the destination
	// and poll for incoming data.
	
	RTPUDPv4TransmissionParams transparams;
	RTPSessionParams sessparams;
	
	// IMPORTANT: The local timestamp unit MUST be set, otherwise
	//            RTCP Sender Report info will be calculated wrong
	// In this case, we'll be just use 8000 samples per second.
	sessparams.SetOwnTimestampUnit(1.0/8000.0);	
	sessparams.SetMaximumPacketSize(64000);

	//
	// ���ô���Ĭ�ϲ���
	//
	sess.SetDefaultPayloadType( 0 );
	sess.SetDefaultMark( false );
	sess.SetDefaultTimestampIncrement( 10 );

	// �������ݷ���Session
	portbase	= 8002;
	transparams.SetPortbase( portbase );
	SendSession.Create( sessparams, &transparams );

	// �������ݽ���Session
	portbase	= 8000;
	transparams.SetPortbase( portbase );
	sess.Create( sessparams, &transparams );

	// ��������ת���߳�
	_beginthread( TransdataThread, NULL, &sess );

	// Wait a number of seconds
//	RTPTime::Wait(RTPTime(160,0));
//	
//	sess.BYEDestroy(RTPTime(10,0),0,0);
	char	ans;
	while ( (ans = getch()) != 'c' )
	{
		sess.Trans();
	}

	// �ͷ���Դ
	WSACleanup();

	printf("End\n");

	return 0;
}

