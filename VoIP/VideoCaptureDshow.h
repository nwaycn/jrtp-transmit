#ifndef __VIDEODSHOW__HHH
#define __VIDEODSHOW__HHH
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <atlbase.h>
#include <windows.h>
#include <dshow.h>
#include <Vfw.h>
#include "CommClient.h"
#include "XvidEnc.h" // video encoder
#include "XvidDec.h" // video decoder 
#pragma include_alias( "dxtrans.h", "qedit.h" )
#define __IDxtCompositor_INTERFACE_DEFINED__

#define __IDxtAlphaSetter_INTERFACE_DEFINED__

#define __IDxtJpeg_INTERFACE_DEFINED__

#define __IDxtKey_INTERFACE_DEFINED__
#pragma once
#define QCIF_WIDTH  176
#define QCIF_HEIGHT 144
//#define QCIF_WIDTH  320
//#define QCIF_HEIGHT 240

#define IMAGE_WIDTH       QCIF_WIDTH
#define IMAGE_HEIGHT      QCIF_HEIGHT

#include <Qedit.h> // ISampleGrabberCB
#ifndef SAFE_RELEASE
#define SAFE_RELEASE( x ) \
	if ( NULL != x ) \
{ \
	x->Release( ); \
	x = NULL; \
}
#endif

class CCamFrameHandler {
public:
	virtual void CamFrameData(double dblSampleTime, BYTE * pBuffer, long lBufferSize) = 0 ; 
};

class CSampleGrabberCB : public ISampleGrabberCB 
{
public:
	long				   lWidth ; 
	long				   lHeight ; 
	CCamFrameHandler	*  frame_handler ; 
	BOOL				   bGrabVideo ; 
public:
	CSampleGrabberCB(){ 
		lWidth = 0 ; 
		lHeight = 0 ; 
		bGrabVideo = FALSE ; 
		frame_handler = NULL ; 
	} 
	STDMETHODIMP_(ULONG) AddRef() { return 2; }
	STDMETHODIMP_(ULONG) Release() { return 1; }
	STDMETHODIMP QueryInterface(REFIID riid, void ** ppv) {
		if( riid == IID_ISampleGrabberCB || riid == IID_IUnknown ){ 
			*ppv = (void *) static_cast<ISampleGrabberCB*> ( this );
			return NOERROR;
		} 
		return E_NOINTERFACE;
	}

	STDMETHODIMP SampleCB( double SampleTime, IMediaSample * pSample )  {
		return 0;
	}

	STDMETHODIMP BufferCB( double dblSampleTime, BYTE * pBuffer, long lBufferSize ){
		if (!pBuffer) return E_POINTER;
		if(bGrabVideo && frame_handler) frame_handler->CamFrameData(dblSampleTime, pBuffer, lBufferSize) ; 
		return 0;
	}
};



class CVideoCaptureDshow: public CXvidEncHandler, public CXvidDecHandler, public CCamFrameHandler
{
	friend class CSampleGrabberCB;
public:
	CVideoCaptureDshow(void);
	~CVideoCaptureDshow(void);

	void GrabVideoFrames(BOOL bGrabVideoFrames, CCamFrameHandler * frame_handler); 
	HRESULT Start(int iDeviceID,HWND hWnd);
	HRESULT Stop(); 
	int EnumDevices(HWND hList);
	
private:
	HWND					m_hWnd;
	IGraphBuilder *			m_pGB;
	ICaptureGraphBuilder2*	m_pCapture;
	IBaseFilter*			m_pBF;
	IMediaControl*			m_pMC;
	IVideoWindow*			m_pVW;
	ISampleGrabber*			m_pGrabber;
protected:
	void FreeMediaType(AM_MEDIA_TYPE& mt);
	bool BindFilter(int deviceId, IBaseFilter **pFilter);
	void ResizeVideoWindow();
	HRESULT SetupVideoWindow();
	HRESULT InitCaptureGraphBuilder();

public: // override the CXvidEncHandler
	void PostEncHandler(unsigned char * xvid, int key, int xvid_len) ; 

public:
	void PostDecHandler(unsigned char * image, int used_bytes) ;
public: // override the CCamFrameHandler
	void CamFrameData(double dblSampleTime, BYTE * pBuffer, long lBufferSize) ; 
	void SetCommClient(CCommClient* pClient);
	//////////////////////////////////////////////////////////////////////////
	//
	// 回放远程视频
	//
	void DrawRemoteScreen(char *data, UINT size, CDC* dc);
private:
	// 数据通信接口
	CCommClient*	m_pCommClient;
	//编解码器
	CXvidEnc *		m_enc ; 
	CXvidDec *		m_dec ; 
	CDC* remotedc;
	HDRAWDIB		m_hdib;
	BITMAPINFOHEADER m_bmpheader;
	BITMAPINFO m_bmpinfo;


};
#endif