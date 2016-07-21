#include "StdAfx.h"
#include "CubeShap.h"
#include <assert.h>

typedef struct tagVertex
{
	tagVertex(){

	}	
	tagVertex(float x, float y, float z, D3DCOLOR color){
		_x = x; _y = y; _z = z;
		_color = color;
	}
	float _x, _y, _z;
	D3DCOLOR _color;
	static const DWORD FVF;
}Vertex;
const DWORD Vertex::FVF = D3DFVF_XYZ|D3DFVF_DIFFUSE;   // flexible vertex format


CCubeShap::CCubeShap(void)
: m_pVertexBuffer(NULL)
, m_pIndexBuffer(NULL)
{
}

CCubeShap::~CCubeShap(void)
{
}


bool CCubeShap::Init(HWND hWnd, int nWidth, int nHeight, bool bFullScreen /*= true*/)
{
	bool bRet = CD3DBase::Init(hWnd, nWidth, nHeight, bFullScreen);
	
	assert(NULL == m_pIndexBuffer);
	assert(NULL == m_pVertexBuffer);

	// 创建定点坐标和定点索引
	m_pDirect3DDevice->CreateVertexBuffer(8*sizeof(Vertex), D3DUSAGE_WRITEONLY, Vertex::FVF, D3DPOOL_MANAGED, &m_pVertexBuffer, 0);
	m_pDirect3DDevice->CreateIndexBuffer(12*3*sizeof(WORD), D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &m_pIndexBuffer, 0);

	// 初始化顶点
	Vertex* pVertes = NULL;
	m_pVertexBuffer->Lock(0, 0, (void**)&pVertes, 0);
	if (NULL != pVertes)
	{
		pVertes[0] = Vertex(-1.0f, -1.0f, -1.0f, D3DCOLOR_XRGB(255, 0, 0));
		pVertes[1] = Vertex(-1.0f, 1.0f, -1.0f, D3DCOLOR_XRGB(0, 255, 0));
		pVertes[2] = Vertex(1.0f, 1.0f, -1.0f, D3DCOLOR_XRGB(0, 0, 255));
		pVertes[3] = Vertex(1.0f, -1.0f, -1.0f, D3DCOLOR_XRGB(255, 255, 0));
		pVertes[4] = Vertex(-1.0f, -1.0f, 1.0f, D3DCOLOR_XRGB(255, 0, 255));
		pVertes[5] = Vertex(-1.0f, 1.0f, 1.0f, D3DCOLOR_XRGB(255, 255, 255));
		pVertes[6] = Vertex(1.0f, 1.0f, 1.0f, D3DCOLOR_XRGB(20, 56, 80));
		pVertes[7] = Vertex(1.0f, -1.0f, 1.0f, D3DCOLOR_XRGB(200, 150, 80));
		m_pVertexBuffer->Unlock();
	}
	m_pDirect3DDevice->SetRenderState(D3DRS_LIGHTING, false);

	// 初始化顶点索引
	WORD* pIndexs = NULL;
	m_pIndexBuffer->Lock(0, 0, (void**)&pIndexs, 0);
	if (NULL != m_pIndexBuffer)
	{
		// front side
		pIndexs[0] = 0;pIndexs[1] = 1;pIndexs[2] = 2;
		pIndexs[3] = 0;pIndexs[4] = 2;pIndexs[5] = 3;

		// back side
		pIndexs[6] = 6;pIndexs[7] = 5;pIndexs[8] = 4;
		pIndexs[9] = 6;pIndexs[10] = 4;pIndexs[11] = 7;

		// left side
		pIndexs[12] = 5;pIndexs[13] = 1;pIndexs[14] = 0;
		pIndexs[15] = 5;pIndexs[16] = 0;pIndexs[17] = 4;

		// right side
		pIndexs[18] = 3;pIndexs[19] = 2;pIndexs[20] = 6;
		pIndexs[21] = 3;pIndexs[22] = 6;pIndexs[23] = 7;

		// up side
		pIndexs[24] = 1;pIndexs[25] = 5;pIndexs[26] = 2;
		pIndexs[27] = 5;pIndexs[28] = 6;pIndexs[29] = 2;

		// down side
		pIndexs[30] = 0;pIndexs[31] = 3;pIndexs[32] = 7;
		pIndexs[33] = 0;pIndexs[34] = 7;pIndexs[35] = 4;
		m_pIndexBuffer->Unlock();
	}

	return bRet;
}

void CCubeShap::UnInit()
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
}

void CCubeShap::Draw()
{
	if(NULL == m_pDirect3DDevice)
		return;

	D3DXMATRIX rotationX, rotationY;
	ZeroMemory(&rotationX, sizeof(rotationX));
	ZeroMemory(&rotationY, sizeof(rotationY));

	static float nY = 0.0f;
	D3DXMatrixRotationX(&rotationX, D3DX_PI/4.0f);
	D3DXMatrixRotationY(&rotationY, nY);

	// > 180 degree
	nY += 0.001f;
	if (nY >= D3DX_PI*2)
	{
		nY = 0.0f;
	}

	D3DXMATRIX rotationRet = rotationX*rotationY;
	m_pDirect3DDevice->SetTransform(D3DTS_WORLD, &rotationRet);

	m_pDirect3DDevice->Clear(0, 0, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, 0xffffffff, 1.0f, 0);
	m_pDirect3DDevice->BeginScene();

	m_pDirect3DDevice->SetStreamSource(0, m_pVertexBuffer, 0, sizeof(Vertex));
	m_pDirect3DDevice->SetIndices(m_pIndexBuffer);
	m_pDirect3DDevice->SetFVF(Vertex::FVF);
	HRESULT hRet = m_pDirect3DDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 8, 0, 12);	// 8顶点12个三角形

	m_pDirect3DDevice->EndScene();
	m_pDirect3DDevice->Present(0, 0, 0, 0);
}