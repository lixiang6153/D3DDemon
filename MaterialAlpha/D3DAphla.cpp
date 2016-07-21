#include "StdAfx.h"
#include "D3DAphla.h"
#include "Vertex.h"

CD3DAphla::CD3DAphla(void)
: m_pVertexBuffer(NULL)
, m_pTextureBuffer(NULL)
, m_pTeapot(NULL)
{
}

CD3DAphla::~CD3DAphla(void)
{
}

bool CD3DAphla::Init(HWND hWnd, int nWidth, int nHeight, bool bFullScreen /*= true*/)
{
	bool bRet = CD3DBase::Init(hWnd, nWidth, nHeight, bFullScreen);
	if (bRet)
	{
		m_pDirect3DDevice->CreateVertexBuffer(6*sizeof(CVertex), D3DUSAGE_WRITEONLY, FVF, D3DPOOL_MANAGED, &m_pVertexBuffer, NULL);
		if (NULL != m_pVertexBuffer)
		{
			CVertex* pVertexs = NULL;
			m_pVertexBuffer->Lock(0, 0, (void**)&pVertexs, 0);
			if (NULL != pVertexs)
			{
				pVertexs[0] = CVertex(-10.0f, -10.0f, 5.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f);
				pVertexs[1] = CVertex(-10.0f,  10.0f, 5.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f);
				pVertexs[2] = CVertex( 10.0f,  10.0f, 5.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f);

				pVertexs[3] = CVertex(-10.0f, -10.0f, 5.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f);
				pVertexs[4] = CVertex( 10.0f,  10.0f, 5.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f);
				pVertexs[5] = CVertex( 10.0f, -10.0f, 5.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f);
			}
			m_pVertexBuffer->Unlock();

			// create texture from file
			D3DXCreateTextureFromFile(m_pDirect3DDevice, _T("crate.jpg"), &m_pTextureBuffer);
			if (NULL == m_pTextureBuffer)
			{
				UnInit();
				return false;
			}
			// set mipmap and texture magnify and minimize way
			m_pDirect3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
			m_pDirect3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
			m_pDirect3DDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_POINT);

			// enable and set alpha channel
			// m_pDirect3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
			m_pDirect3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_DIFFUSE);
			m_pDirect3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);	
			m_pDirect3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			m_pDirect3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

			D3DXCreateTeapot(m_pDirect3DDevice, &m_pTeapot, NULL);
			m_TeapotMtrl = RED_MTRL;
			m_TeapotMtrl.Diffuse.a = 0.5f;  // 50% opacity

			// set light 0
			D3DLIGHT9 dirLight;
			ZeroMemory(&dirLight, sizeof(dirLight));
			dirLight.Type = D3DLIGHT_DIRECTIONAL;
			dirLight.Direction = D3DXVECTOR3(0.707f, 0.0f, 0.707f);
			dirLight.Ambient = WHITE*0.6f;
			dirLight.Diffuse = WHITE;
			dirLight.Specular = WHITE*0.2f;

			// enable light	and normalize normal
			m_pDirect3DDevice->SetLight(0, &dirLight);
			m_pDirect3DDevice->LightEnable(0, true);
			m_pDirect3DDevice->SetRenderState(D3DRS_NORMALIZENORMALS, true);
			m_pDirect3DDevice->SetRenderState(D3DRS_SPECULARENABLE, true);
			m_pDirect3DDevice->SetRenderState(D3DRS_LIGHTING, true);
		}
	}
	return true;
}

void CD3DAphla::UnInit()
{
	CD3DBase::UnInit();
	if (NULL != m_pVertexBuffer)
	{
		m_pVertexBuffer->Release();
		m_pVertexBuffer = NULL;
	}
	if (NULL != m_pTeapot)
	{
		m_pTeapot->Release();
		m_pTeapot = NULL;
	}
	if (NULL != m_pTextureBuffer)
	{
		m_pTextureBuffer->Release();
		m_pTextureBuffer = NULL;
	}
}

void CD3DAphla::Draw()
{
	// increase/decrease alpha via keyboard input
	if( ::GetAsyncKeyState('A') & 0x8000f )
		m_TeapotMtrl.Diffuse.a += 0.01f;
	if( ::GetAsyncKeyState('S') & 0x8000f )
		m_TeapotMtrl.Diffuse.a -= 0.01f;

	// force alpha to [0, 1] interval
	if(m_TeapotMtrl.Diffuse.a > 1.0f)
		m_TeapotMtrl.Diffuse.a = 1.0f;
	if(m_TeapotMtrl.Diffuse.a < 0.0f)
		m_TeapotMtrl.Diffuse.a = 0.0f;

	m_pDirect3DDevice->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0xffffffff, 1.0f, 0);
	m_pDirect3DDevice->BeginScene();

	// Draw the background
	D3DXMATRIX W;
	D3DXMatrixIdentity(&W);
	m_pDirect3DDevice->SetTransform(D3DTS_WORLD, &W);
	m_pDirect3DDevice->SetFVF(FVF);
	m_pDirect3DDevice->SetStreamSource(0, m_pVertexBuffer, 0, sizeof(CVertex));
	m_pDirect3DDevice->SetMaterial(&WHITE_MTRL);
	m_pDirect3DDevice->SetTexture(0, m_pTextureBuffer);
	m_pDirect3DDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);

	// Draw the teapot
	m_pDirect3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);

	D3DXMatrixScaling(&W, 1.5f, 1.5f, 1.5f);
	m_pDirect3DDevice->SetTransform(D3DTS_WORLD, &W);
	m_pDirect3DDevice->SetMaterial(&m_TeapotMtrl);
	m_pDirect3DDevice->SetTexture(0, 0);
	m_pTeapot->DrawSubset(0);  

	m_pDirect3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);

	m_pDirect3DDevice->EndScene();
	m_pDirect3DDevice->Present(0, 0, 0, 0);
}