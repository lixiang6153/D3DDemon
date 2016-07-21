#include "StdAfx.h"
#include "D3DPyramid.h"

struct Vertex 
{
	Vertex()
	{

	}
	Vertex(float x, float y, float z, float nx, float ny, float nz)
	{
		_x = x; _y = y; _z = z; _nx = nx; _ny = ny; _nz = nz;
	}
	float _x, _y, _z;
	float _nx, _ny, _nz;
	static const DWORD FVF;
};
const DWORD Vertex::FVF = D3DFVF_XYZ | D3DFVF_NORMAL;


CD3DLight::CD3DLight(void)
: m_pVertexBuffer(NULL)
{
}

CD3DLight::~CD3DLight(void)
{
}

bool CD3DLight::Init(HWND hWnd, int nWidth, int nHeight, bool bFullScreen/* = true*/)
{
	bool bRet = CD3DBase::Init(hWnd, nWidth, nHeight, bFullScreen);
	if (bRet)
	{
		m_pDirect3DDevice->CreateVertexBuffer(12*sizeof(Vertex), D3DUSAGE_WRITEONLY, Vertex::FVF, D3DPOOL_MANAGED, &m_pVertexBuffer, NULL);
		if(NULL == m_pVertexBuffer)
		{
			UnInit();
			return false;
		}

		Vertex* pVertex = NULL;
		m_pVertexBuffer->Lock(0, 0, (void**)&pVertex, 0);
		if (NULL == pVertex)
		{
			UnInit();
			return false;
		}

		// front face
		pVertex[0] = Vertex(-1.0f, 0.0f, -1.0f, 0.0f, 0.707f, -0.707f);
		pVertex[1] = Vertex( 0.0f, 1.0f,  0.0f, 0.0f, 0.707f, -0.707f);
		pVertex[2] = Vertex( 1.0f, 0.0f, -1.0f, 0.0f, 0.707f, -0.707f);

		// left face
		pVertex[3] = Vertex(-1.0f, 0.0f,  1.0f, -0.707f, 0.707f, 0.0f);
		pVertex[4] = Vertex( 0.0f, 1.0f,  0.0f, -0.707f, 0.707f, 0.0f);
		pVertex[5] = Vertex(-1.0f, 0.0f, -1.0f, -0.707f, 0.707f, 0.0f);

		// right face
		pVertex[6] = Vertex( 1.0f, 0.0f, -1.0f, 0.707f, 0.707f, 0.0f);
		pVertex[7] = Vertex( 0.0f, 1.0f,  0.0f, 0.707f, 0.707f, 0.0f);
		pVertex[8] = Vertex( 1.0f, 0.0f,  1.0f, 0.707f, 0.707f, 0.0f);

		// back face
		pVertex[9]  = Vertex( 1.0f, 0.0f,  1.0f, 0.0f, 0.707f, 0.707f);
		pVertex[10] = Vertex( 0.0f, 1.0f,  0.0f, 0.0f, 0.707f, 0.707f);
		pVertex[11] = Vertex(-1.0f, 0.0f,  1.0f, 0.0f, 0.707f, 0.707f);

		m_pVertexBuffer->Unlock();


		D3DMATERIAL9 mtrlWhite = WHITE_MTRL;
		m_pDirect3DDevice->SetMaterial(&mtrlWhite);

		D3DLIGHT9 light;
		ZeroMemory(&light, sizeof(light));
		light.Type = D3DLIGHT_DIRECTIONAL;
		light.Ambient = WHITE*0.6f;
		light.Diffuse = WHITE;
		light.Specular = WHITE*0.3f;
		light.Direction = D3DXVECTOR3(1.0f, 0.0f, 0.0f);

		m_pDirect3DDevice->SetRenderState(D3DRS_LIGHTING, true);
		m_pDirect3DDevice->SetLight(0, &light);
		m_pDirect3DDevice->LightEnable(0, true);
	}
	return bRet;
}

void CD3DLight::UnInit()
{
	CD3DBase::UnInit();
	if (NULL != m_pVertexBuffer)
	{
		m_pVertexBuffer->Release();
		m_pVertexBuffer = NULL;
	}
}

void CD3DLight::Draw()
{
	if(NULL == m_pDirect3DDevice)
		return ;

	static float nY = 0.0f;
	D3DXMATRIX yRotation;
	D3DXMatrixRotationY(&yRotation, nY);
	nY += 0.005f;
	if (nY >= D3DX_PI*2)
	{
		nY = 0.0f;
	}
	m_pDirect3DDevice->SetTransform(D3DTS_WORLD, &yRotation);

	m_pDirect3DDevice->Clear(0, 0, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, BLACK, 1.0, 0);

	m_pDirect3DDevice->BeginScene();
	m_pDirect3DDevice->SetStreamSource(0, m_pVertexBuffer, 0, sizeof(Vertex));
	m_pDirect3DDevice->SetFVF(Vertex::FVF);
	m_pDirect3DDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 4);
	m_pDirect3DDevice->EndScene();

	m_pDirect3DDevice->Present(0, 0, 0, 0);
}