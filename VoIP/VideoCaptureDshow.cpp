
#include "stdafx.h"
#include "VideoCaptureDshow.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
#pragma comment(lib,"vfw32")
#pragma comment(lib,"winmm")
CSampleGrabberCB mCB;
CVideoCaptureDshow::CVideoCaptureDshow(void)
{
	if(FAILED(CoInitialize(NULL))) /*, COINIT_APARTMENTTHREADED)))*/
	{
		AfxMessageBox("CoInitialize Failed!\r\n"); 
		return;
	}
	m_hWnd = NULL;
	m_pVW = NULL;
	m_pMC = NULL;
	m_pGB = NULL;
	m_pBF = NULL; 
	m_pGrabber = NULL; 
	m_pCapture = NULL; 
}

CVideoCaptureDshow::~CVideoCaptureDshow(void)
{
	if(m_pMC)m_pMC->StopWhenReady();
	if(m_pVW){
		m_pVW->put_Visible(OAFALSE);
		m_pVW->put_Owner(NULL);
	}
	SAFE_RELEASE(m_pMC);
	SAFE_RELEASE(m_pVW); 
	SAFE_RELEASE(m_pGB);
	SAFE_RELEASE(m_pBF);
	SAFE_RELEASE(m_pGrabber); 
	SAFE_RELEASE(m_pCapture);
	CoUninitialize() ; 
}

HRESULT CVideoCaptureDshow::Start( int iDeviceID,HWND hWnd )
{
	HRESULT hr;
	hr = InitCaptureGraphBuilder();
	if (FAILED(hr)){
		AfxMessageBox("Failed to get video interfaces!");
		return hr;
	}
	// Bind Device Filter. We know the device because the id was passed in
	if(!BindFilter(iDeviceID, &m_pBF))return S_FALSE;
	hr = m_pGB->AddFilter(m_pBF, L"Capture Filter");
	// hr = m_pCapture->RenderStream(&PIN_CATEGORY_PREVIEW, &MEDIATYPE_Video, 
	// m_pBF, NULL, NULL);
	// create a sample grabber
	hr = CoCreateInstance( CLSID_SampleGrabber, NULL, CLSCTX_INPROC_SERVER, IID_ISampleGrabber, (void**)&m_pGrabber );
	if(FAILED(hr)){
		AfxMessageBox("Fail to create SampleGrabber, maybe qedit.dll is not registered?");
		return hr;
	}
	CComQIPtr< IBaseFilter, &IID_IBaseFilter > pGrabBase( m_pGrabber );

	//设置视频格式
	AM_MEDIA_TYPE mt; 
	ZeroMemory(&mt, sizeof(AM_MEDIA_TYPE));
	mt.majortype = MEDIATYPE_Video;
	mt.subtype = MEDIASUBTYPE_RGB24; // MEDIASUBTYPE_RGB24 ; 
	hr = m_pGrabber->SetMediaType(&mt);

	if( FAILED( hr ) ){
		AfxMessageBox("Fail to set media type!");
		return hr;
	}
	hr = m_pGB->AddFilter( pGrabBase, L"Grabber" );
	if( FAILED( hr ) ){
		AfxMessageBox("Fail to put sample grabber in graph");
		return hr;
	}

	// try to render preview/capture pin
	hr = m_pCapture->RenderStream(&PIN_CATEGORY_PREVIEW, &MEDIATYPE_Video,m_pBF,pGrabBase,NULL);
	if( FAILED( hr ) )
		hr = m_pCapture->RenderStream(&PIN_CATEGORY_CAPTURE, &MEDIATYPE_Video,m_pBF,pGrabBase,NULL);

	if( FAILED( hr ) ){
		AfxMessageBox("Can’t build the graph");
		return hr;
	}

	hr = m_pGrabber->GetConnectedMediaType( &mt );
	if ( FAILED( hr) ){
		AfxMessageBox("Failt to read the connected media type");
		return hr;
	}

	VIDEOINFOHEADER * vih = (VIDEOINFOHEADER*) mt.pbFormat;
	mCB.lWidth = vih->bmiHeader.biWidth;
	mCB.lHeight = vih->bmiHeader.biHeight;
	mCB.bGrabVideo = FALSE ; 
	mCB.frame_handler = NULL ; 
	FreeMediaType(mt);
	hr = m_pGrabber->SetBufferSamples( FALSE );
	hr = m_pGrabber->SetOneShot( FALSE );
	hr = m_pGrabber->SetCallback( &mCB, 1 );

	//设置视频捕捉窗口
	m_hWnd = hWnd ; 
	SetupVideoWindow();
	hr = m_pMC->Run();//开始视频捕捉
	if(FAILED(hr)){AfxMessageBox("Couldn’t run the graph!");return hr;}
	m_enc = new CXvidEnc() ; 
	m_enc->AttachCaller(320, 240, this) ; 
	CXvidEnc::XVID_GLOBAL_INIT() ; 
	m_enc->Open() ;

	m_dec = new CXvidDec() ;
	m_dec->AttachCaller(320, 240, this) ; 
	CXvidDec::XVID_GLOBAL_INIT() ; 
	m_dec->Open() ; 
	GrabVideoFrames(TRUE,this);
	return S_OK;
}

HRESULT CVideoCaptureDshow::Stop()
{
	// Stop media playback
	if(m_pMC)m_pMC->StopWhenReady();
	if(m_pVW){
		m_pVW->put_Visible(OAFALSE);
		m_pVW->put_Owner(NULL);
	}
	SAFE_RELEASE(m_pMC);
	SAFE_RELEASE(m_pVW); 
	SAFE_RELEASE(m_pGB);
	SAFE_RELEASE(m_pBF);
	SAFE_RELEASE(m_pGrabber); 
	SAFE_RELEASE(m_pCapture);
	m_enc->Close() ;
	m_dec->Close() ;
	delete m_dec ; 
	delete m_enc ;
	return S_OK ; 
}

void CVideoCaptureDshow::FreeMediaType( AM_MEDIA_TYPE& mt )
{
	if (mt.cbFormat != 0) {
		CoTaskMemFree((PVOID)mt.pbFormat);
		// Strictly unnecessary but tidier
		mt.cbFormat = 0;
		mt.pbFormat = NULL;
	}
	if (mt.pUnk != NULL) {
		mt.pUnk->Release();
		mt.pUnk = NULL;
	}
}

bool CVideoCaptureDshow::BindFilter( int deviceId, IBaseFilter **pFilter )
{
	if (deviceId < 0)
		return false;

	// enumerate all video capture devices
	CComPtr<ICreateDevEnum> pCreateDevEnum;
	HRESULT hr = CoCreateInstance(CLSID_SystemDeviceEnum, NULL, CLSCTX_INPROC_SERVER,
		IID_ICreateDevEnum, (void**)&pCreateDevEnum);
	if (hr != NOERROR)
	{
		return false;
	}
	CComPtr<IEnumMoniker> pEm;
	hr = pCreateDevEnum->CreateClassEnumerator(CLSID_VideoInputDeviceCategory,&pEm, 0);
	if (hr != NOERROR) 
	{
		return false;
	}
	pEm->Reset();
	ULONG cFetched;
	IMoniker *pM;
	int index = 0;
	while(hr = pEm->Next(1, &pM, &cFetched), hr==S_OK, index <= deviceId)
	{
		IPropertyBag *pBag;
		hr = pM->BindToStorage(0, 0, IID_IPropertyBag, (void **)&pBag);
		if(SUCCEEDED(hr)) 
		{
			VARIANT var;
			var.vt = VT_BSTR;
			hr = pBag->Read(L"FriendlyName", &var, NULL);
			if (hr == NOERROR) 
			{
				if (index == deviceId)
				{
					pM->BindToObject(0, 0, IID_IBaseFilter, (void**)pFilter);
				}
				SysFreeString(var.bstrVal);
			}
			pBag->Release();
		}
		pM->Release();
		index++;
	}
	return true;
}

HRESULT CVideoCaptureDshow::InitCaptureGraphBuilder()
{
	HRESULT hr;

	// 创建IGraphBuilder接口
	hr=CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER, IID_IGraphBuilder, (void **)&m_pGB);
	// 创建ICaptureGraphBuilder2接口
	hr = CoCreateInstance (CLSID_CaptureGraphBuilder2 , NULL, CLSCTX_INPROC,
		IID_ICaptureGraphBuilder2, (void **) &m_pCapture);
	if (FAILED(hr))return hr;
	m_pCapture->SetFiltergraph(m_pGB);
	hr = m_pGB->QueryInterface(IID_IMediaControl, (void **)&m_pMC);
	if (FAILED(hr))return hr;
	hr = m_pGB->QueryInterface(IID_IVideoWindow, (LPVOID *) &m_pVW);
	if (FAILED(hr))return hr;
	m_hdib	= ::DrawDibOpen();
	return hr;
}

HRESULT CVideoCaptureDshow::SetupVideoWindow()
{
	HRESULT hr;
	hr = m_pVW->put_Owner((OAHWND)m_hWnd);
	if (FAILED(hr))return hr;
	hr = m_pVW->put_WindowStyle(WS_CHILD | WS_CLIPCHILDREN);
	if (FAILED(hr))return hr;
	ResizeVideoWindow();
	hr = m_pVW->put_Visible(OATRUE);
	return hr;
}

void CVideoCaptureDshow::ResizeVideoWindow()
{
	if (m_pVW){
		//让图像充满整个窗口
		CRect rc;
		::GetClientRect(m_hWnd,&rc);
		m_pVW->SetWindowPosition(0, 0, rc.right, rc.bottom);
	} 
}

void CVideoCaptureDshow::GrabVideoFrames( BOOL bGrabVideoFrames, CCamFrameHandler * frame_handler )
{
	mCB.frame_handler = frame_handler ; 
	mCB.bGrabVideo = bGrabVideoFrames ; 
}

void CVideoCaptureDshow::PostEncHandler( unsigned char * xvid, int key, int xvid_len )
{
	m_pCommClient->SendPacket((char *)xvid,xvid_len,PACKET_VIDEO);
}

void CVideoCaptureDshow::PostDecHandler( unsigned char * image, int used_bytes )
{
#if 0
	PAINTSTRUCT ps;
	::BeginPaint(hwndStill, &ps);

	SetStretchBltMode(hdcStill, COLORONCOLOR);
	StretchDIBits( 
		hdcStill, 0, 0, 
		320, 240, 
		0, 0, 320, 240, 
		image, (BITMAPINFO*) pbih, 
		DIB_RGB_COLORS, 
		SRCCOPY );

	if (image)
	{
		delete image;
		image = NULL;
	}
	::EndPaint(hwndStill, &ps);
	::ReleaseDC( hwndStill, hdcStill );   
#endif
#if 1
	::DrawDibDraw(
		m_hdib,
		*remotedc,
		0,		// dest : left pos
		0,		// dest : top pos
		-1,					 // don't zoom x
		-1,					 // don't zoom y
		//&m_bmpinfo.bmiHeader,			 // bmp header info
		&m_bmpheader,
		image,					 // bmp data
		0,					 // src :left
		0,					 // src :top
		IMAGE_WIDTH,				 // src : width
		IMAGE_HEIGHT,				 // src : height
		DDF_SAME_DRAW			 // use prev params....
		);
#endif
#if 0
	int i, j, k ;
	k = 0 ; 
	//CDC * pdc = GetDlgItem(IDC_RES_SCR)->GetDC() ; 
// 	CWnd* wnd = remotedc->GetWindow();
// 	wnd->GetWindowRect()
	
	for(i = 240-1 ; i >= 0 ; i--) {
		for(j = 0  ; j <320 ; j++) {
			remotedc->SetPixel(j,i, RGB(image[k+2], image[k+1], image[k])) ; 
			k += 3 ; 
		}
	}
	//DrawDib()

	
#endif
}

void CVideoCaptureDshow::CamFrameData( double dblSampleTime, BYTE * pBuffer, long lBufferSize )
{
	m_enc->Encode(pBuffer) ; 
}

void CVideoCaptureDshow::SetCommClient( CCommClient* pClient )
{
	m_pCommClient	= pClient;
}

void CVideoCaptureDshow::DrawRemoteScreen( char *data, UINT size, CDC* dc )
{
	m_dec->Decode((unsigned char*)data, size) ; 
	remotedc = dc;
}