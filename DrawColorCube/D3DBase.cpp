#include "StdAfx.h"
#include "D3DBase.h"
#include <assert.h>

CD3DBase::CD3DBase(void)
: m_pDirect3DDevice(NULL)
{
}

CD3DBase::~CD3DBase(void)
{
	UnInit();
}

bool CD3DBase::Init(HWND hWnd, int nWidth, int nHeight, bool bFullScreen/* = true*/)
{
	assert(NULL == m_pDirect3DDevice);
	IDirect3D9* pDirect3d9 = Direct3DCreate9(D3D_SDK_VERSION);
	if (NULL == pDirect3d9)
		return false;

	D3DCAPS9 stCaps;
	memset(&stCaps, 0, sizeof(stCaps));
	if (FAILED(pDirect3d9->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &stCaps)))
	{
		pDirect3d9->Release();
		return false;
	}

	int nVertexProcess = 0;
	if (stCaps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
		nVertexProcess = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	else
		nVertexProcess = D3DCREATE_SOFTWARE_VERTEXPROCESSING;

	D3DPRESENT_PARAMETERS d3dpp;
	memset(&d3dpp, 0, sizeof(d3dpp));
	d3dpp.BackBufferWidth				= nWidth;
	d3dpp.BackBufferHeight				= nHeight;
	d3dpp.BackBufferFormat				= D3DFMT_A8R8G8B8;
	d3dpp.BackBufferCount				= 1;
	d3dpp.MultiSampleType				= D3DMULTISAMPLE_NONE;
	d3dpp.MultiSampleQuality			= 0;
	d3dpp.SwapEffect					= D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow					= hWnd;
	d3dpp.Windowed						= bFullScreen;
	d3dpp.FullScreen_RefreshRateInHz	= D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval			= D3DPRESENT_INTERVAL_IMMEDIATE;
	d3dpp.EnableAutoDepthStencil		= true;
	d3dpp.AutoDepthStencilFormat		= D3DFMT_D24S8;
	d3dpp.Flags							= 0;

	if (FAILED(pDirect3d9->CreateDevice(D3DADAPTER_DEFAULT,
										 D3DDEVTYPE_HAL,
										 hWnd,
										 nVertexProcess,
										 &d3dpp,
										 &m_pDirect3DDevice)))
	{
		d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
		if (FAILED(pDirect3d9->CreateDevice(D3DADAPTER_DEFAULT,
											 D3DDEVTYPE_HAL,
											 hWnd,
											 nVertexProcess,
											 &d3dpp,
											 &m_pDirect3DDevice)))
		{
			pDirect3d9->Release();
			return false;
		}
	}

	pDirect3d9->Release();
	return true;
}

void CD3DBase::UnInit()
{
	if (NULL != m_pDirect3DDevice)
	{
		m_pDirect3DDevice->Release();
		m_pDirect3DDevice = NULL;
	}
}

void CD3DBase::Draw()
{
	
}

void CD3DBase::Setup(int nWidth, int nHeight)
{
	if(NULL == m_pDirect3DDevice)
		return;

	// 设置照相机位置,放置点-对准点-世界坐标上方方向
	D3DXVECTOR3 stPosition(0.0f, 0.0f, -10.0f);
	D3DXVECTOR3 stTarget(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 stWorldCordUp(0.0f, 1.0f, 0.0f);

	D3DXMATRIX stViewMatrix;
	D3DXMatrixLookAtLH(&stViewMatrix, &stPosition, &stTarget, &stWorldCordUp);
	m_pDirect3DDevice->SetTransform(D3DTS_VIEW, &stViewMatrix);

	// 设置3D透视投影范围
	D3DXMATRIX stProjection;
	D3DXMatrixPerspectiveFovLH(&stProjection, D3DX_PI*0.5f, (float)nWidth/(float)nHeight, 1.0f, 1000.0f);
	m_pDirect3DDevice->SetTransform(D3DTS_PROJECTION, &stProjection);

	// 切换到线框图模式	 -设置后只有点和线，看不到实体面
	//m_pDirect3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
}
