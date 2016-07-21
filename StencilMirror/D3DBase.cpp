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

	// 设置照相机位置,放置点-对准点-世界坐标上方方向
	D3DXVECTOR3 stPosition(0.0f, 0.0f, -15.0f);
	D3DXVECTOR3 stTarget(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 stWorldCordUp(0.0f, 1.0f, 0.0f);

	D3DXMATRIX stViewMatrix;
	D3DXMatrixLookAtLH(&stViewMatrix, &stPosition, &stTarget, &stWorldCordUp);
	m_pDirect3DDevice->SetTransform(D3DTS_VIEW, &stViewMatrix);

	// 设置3D透视投影范围
	D3DXMATRIX stProjection;
	D3DXMatrixPerspectiveFovLH(&stProjection, D3DX_PI*0.5f, (float)nWidth/(float)nHeight, 1.0f, 1000.0f);
	m_pDirect3DDevice->SetTransform(D3DTS_PROJECTION, &stProjection);

	// 切换到线框图模式	 - 只有线条和顶点，无实体面，切记删除改代码
	//m_pDirect3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

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

D3DMATERIAL9 CD3DBase::InitMaterial(D3DXCOLOR a, D3DXCOLOR d, D3DXCOLOR s, D3DXCOLOR e, float p)
{
	D3DMATERIAL9 d3dMaterial;
	d3dMaterial.Ambient = a;
	d3dMaterial.Diffuse = d;
	d3dMaterial.Specular = s;
	d3dMaterial.Emissive = e;
	d3dMaterial.Power = p;
	return d3dMaterial;
}

D3DLIGHT9 CD3DBase::InitPointLight(D3DXVECTOR3* position, D3DXCOLOR* color)
{
	D3DLIGHT9 light;
	::ZeroMemory(&light, sizeof(light));

	light.Type      = D3DLIGHT_POINT;
	light.Ambient   = *color * 0.6f;
	light.Diffuse   = *color;
	light.Specular  = *color * 0.6f;
	light.Position  = *position;
	light.Range        = 1000.0f;
	light.Falloff      = 1.0f;
	light.Attenuation0 = 1.0f;
	light.Attenuation1 = 0.0f;
	light.Attenuation2 = 0.0f;

	return light;
}

D3DLIGHT9 CD3DBase::InitDirectionalLight(D3DXVECTOR3* direction, D3DXCOLOR* color)
{
	D3DLIGHT9 light;
	::ZeroMemory(&light, sizeof(light));

	light.Type      = D3DLIGHT_DIRECTIONAL;
	light.Ambient   = *color * 0.6f;
	light.Diffuse   = *color;
	light.Specular  = *color * 0.6f;
	light.Direction = *direction;

	return light;
}