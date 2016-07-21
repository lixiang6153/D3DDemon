#include "StdAfx.h"
#include "D3DTexture.h"
#include "Vertex.h"

CD3DTexture::CD3DTexture(void)
: m_pVertexBuffer(NULL)
, m_pIndexBuffer(NULL)
, m_pTextureBuffer(NULL)
{
}

CD3DTexture::~CD3DTexture(void)
{
}

bool CD3DTexture::Init(HWND hWnd, int nWidth, int nHeight, bool bFullScreen /*= true*/)
{
	bool bRet = CD3DBase::Init(hWnd, nWidth, nHeight, bFullScreen);
	if (bRet)
	{
		m_pDirect3DDevice->CreateVertexBuffer(24*sizeof(CVertex), D3DUSAGE_WRITEONLY, FVF, D3DPOOL_MANAGED, &m_pVertexBuffer, NULL);
		if (NULL != m_pVertexBuffer)
		{
			CVertex* pVertexs = NULL;
			m_pVertexBuffer->Lock(0, 0, (void**)&pVertexs, 0);
			if (NULL != pVertexs)
			{
				// front 0123
				pVertexs[0] = CVertex(-1.0f, -1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 3.0f);
				pVertexs[1] = CVertex(-1.0f, 1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f);
				pVertexs[2] = CVertex(1.0f, 1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 3.0f, 0.0f);
				pVertexs[3] = CVertex(1.0f, -1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 3.0f, 3.0f);

				// back 7546
				pVertexs[4] = CVertex(-1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);
				pVertexs[5] = CVertex(1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f);
				pVertexs[6] = CVertex(1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
				pVertexs[7] = CVertex(-1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);

				// left 0761
				pVertexs[8] = CVertex(-1.0f, -1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
				pVertexs[9] = CVertex(-1.0f, -1.0f, 1.0f,  -1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
				pVertexs[10] = CVertex(-1.0f, 1.0f, 1.0f,  -1.0f, 0.0f, 0.0f, 1.0f, 0.0f);
				pVertexs[11] = CVertex(-1.0f, 1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f);

				// right 3245
				pVertexs[12] = CVertex(1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
				pVertexs[13] = CVertex(1.0f, 1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
				pVertexs[14] = CVertex(1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f);
				pVertexs[15] = CVertex(1.0f, -1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f);

				// up 1642
				pVertexs[16] = CVertex(-1.0f, 1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f);
				pVertexs[17] = CVertex(-1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f);
				pVertexs[18] = CVertex(1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f);
				pVertexs[19] = CVertex(1.0f, 1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f);

				// down 0357
				pVertexs[20] = CVertex(-1.0f, -1.0f, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f);
				pVertexs[21] = CVertex(1.0f, -1.0f, -1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f);
				pVertexs[22] = CVertex(1.0f, -1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f);
				pVertexs[23] = CVertex(-1.0f, -1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f);
			}
			m_pVertexBuffer->Unlock();
		}

 		m_pDirect3DDevice->CreateIndexBuffer(36*sizeof(WORD), D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &m_pIndexBuffer, NULL);
		if (NULL != m_pIndexBuffer)
		{
			WORD* pIndies = NULL;
			m_pIndexBuffer->Lock(0, 0, (void**)&pIndies, 0);
			if (NULL != pIndies)
			{
				// fill in the front face index data
				pIndies[0] = 0; pIndies[1] = 1; pIndies[2] = 2;
				pIndies[3] = 0; pIndies[4] = 2; pIndies[5] = 3;

				// fill in the back face index data
				pIndies[6] = 4; pIndies[7]  = 5; pIndies[8]  = 6;
				pIndies[9] = 4; pIndies[10] = 6; pIndies[11] = 7;

				// fill in the top face index data
				pIndies[12] = 8; pIndies[13] =  9; pIndies[14] = 10;
				pIndies[15] = 8; pIndies[16] = 10; pIndies[17] = 11;

				// fill in the bottom face index data
				pIndies[18] = 12; pIndies[19] = 13; pIndies[20] = 14;
				pIndies[21] = 12; pIndies[22] = 14; pIndies[23] = 15;

				// fill in the left face index data
				pIndies[24] = 16; pIndies[25] = 17; pIndies[26] = 18;
				pIndies[27] = 16; pIndies[28] = 18; pIndies[29] = 19;

				// fill in the right face index data
				pIndies[30] = 20; pIndies[31] = 21; pIndies[32] = 22;
				pIndies[33] = 20; pIndies[34] = 22; pIndies[35] = 23;
			}
		}
		m_pIndexBuffer->Unlock();

		D3DLIGHT9 dirLight;
		ZeroMemory(&dirLight, sizeof(dirLight));
		D3DXVECTOR3 dir(1.0f, -1.0f, 0.0f);
		D3DXCOLOR color = WHITE;
		dirLight = InitDirectionalLight(&dir, &color);
		m_pDirect3DDevice->SetLight(0, &dirLight);
		m_pDirect3DDevice->LightEnable(0, true);
		m_pDirect3DDevice->SetRenderState(D3DRS_LIGHTING, true);
		m_pDirect3DDevice->SetRenderState(D3DRS_NORMALIZENORMALS, true);

		D3DXCreateTextureFromFile(m_pDirect3DDevice, _T("crate.jpg"), &m_pTextureBuffer);
		if (NULL != m_pTextureBuffer)
		{
			m_pDirect3DDevice->SetTexture(0, m_pTextureBuffer);
			m_pDirect3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
			m_pDirect3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
			m_pDirect3DDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
		}

		D3DLIGHT9 light;
		::ZeroMemory(&light, sizeof(light));
		light.Type      = D3DLIGHT_DIRECTIONAL;
		light.Ambient   = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
		light.Diffuse   = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		light.Specular  = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f);
		light.Direction = D3DXVECTOR3(1.0f, -1.0f, 0.0f);
		m_pDirect3DDevice->SetLight(0, &light);
		m_pDirect3DDevice->LightEnable(0, true);

		m_pDirect3DDevice->SetRenderState(D3DRS_NORMALIZENORMALS, true);
		m_pDirect3DDevice->SetRenderState(D3DRS_SPECULARENABLE, true);

		D3DXCreateTextureFromFile(m_pDirect3DDevice,_T("crate.jpg"),&m_pTextureBuffer);
		m_pDirect3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
		m_pDirect3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
		m_pDirect3DDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);

		// 设置纹理寻址模式
		m_pDirect3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_MIRROR);
		m_pDirect3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_MIRROR);
	}
	return bRet;
}

void CD3DTexture::UnInit()
{
	CD3DBase::UnInit();
	if (NULL != m_pVertexBuffer)
	{
		m_pVertexBuffer->Release();
		m_pVertexBuffer = NULL;
	}
	if (NULL != m_pIndexBuffer)
	{
		m_pIndexBuffer->Release();
		m_pIndexBuffer = NULL;
	}
	if (NULL != m_pTextureBuffer)
	{
		m_pTextureBuffer->Release();
		m_pTextureBuffer = NULL;
	}
}

void CD3DTexture::Draw()
{
	if(NULL == m_pDirect3DDevice)
		return ;

	static float angle  = (3.0f * D3DX_PI) / 2.0f;
	static float height = 2.0f;

	if( ::GetAsyncKeyState(VK_LEFT) & 0x8000f )
		angle -= 0.005f ;

	if( ::GetAsyncKeyState(VK_RIGHT) & 0x8000f )
		angle += 0.005f;

	if( ::GetAsyncKeyState(VK_UP) & 0x8000f )
		height += 0.005f;

	if( ::GetAsyncKeyState(VK_DOWN) & 0x8000f )
		height -= 0.005f;

	D3DXVECTOR3 position( cosf(angle) * 3.0f, height, sinf(angle) * 3.0f );
	D3DXVECTOR3 target(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);
	D3DXMATRIX V;
	D3DXMatrixLookAtLH(&V, &position, &target, &up);
	m_pDirect3DDevice->SetTransform(D3DTS_VIEW, &V);

	m_pDirect3DDevice->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0xffffffff, 1.0f, 0);
	m_pDirect3DDevice->BeginScene();

	m_pDirect3DDevice->SetMaterial(&WHITE_MTRL);
	m_pDirect3DDevice->SetTexture(0, m_pTextureBuffer);

	m_pDirect3DDevice->SetStreamSource(0, m_pVertexBuffer, 0, sizeof(CVertex));
	m_pDirect3DDevice->SetIndices(m_pIndexBuffer);
	m_pDirect3DDevice->SetFVF(FVF);
	m_pDirect3DDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0,24,0,12);

	m_pDirect3DDevice->EndScene();
	m_pDirect3DDevice->Present(0, 0, 0, 0); 
}