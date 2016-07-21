#include "StdAfx.h"
#include "D3DLight.h"

CD3DLight::CD3DLight(void)
{
	for(int i = 0; i < 4; ++i)
	{
		m_D3DMeshPtrs[i] = NULL;
	}
}

CD3DLight::~CD3DLight(void)
{
}

bool CD3DLight::Init(HWND hWnd, int nWidth, int nHeight, bool bFullScreen /*= true*/)
{
	bool bRet = CD3DBase::Init(hWnd, nWidth, nHeight, bFullScreen);
	if (bRet)
	{
		D3DXCreateTeapot(m_pDirect3DDevice, &m_D3DMeshPtrs[0], NULL);
		D3DXCreateSphere(m_pDirect3DDevice,1.0f,20,20,&m_D3DMeshPtrs[1],NULL);
		D3DXCreateTorus(m_pDirect3DDevice,0.5f,1.0f,20,20,&m_D3DMeshPtrs[2],NULL);
		D3DXCreateCylinder(m_pDirect3DDevice,1.5f, 0.5f, 2.0f, 20, 20, &m_D3DMeshPtrs[3], NULL);

		D3DXMatrixTranslation(&m_D3dPositions[0],  0.0f,  2.0f, 0.0f);
		D3DXMatrixTranslation(&m_D3dPositions[1],  0.0f, -2.0f, 0.0f);
		D3DXMatrixTranslation(&m_D3dPositions[2], -3.0f,  0.0f, 0.0f);
		D3DXMatrixTranslation(&m_D3dPositions[3],  3.0f,  0.0f, 0.0f);


		m_D3dMaterials[0] = RED_MTRL;
		m_D3dMaterials[1] = BLUE_MTRL;
		m_D3dMaterials[2] = GREEN_MTRL;
		m_D3dMaterials[3] = YELLOW_MTRL;

		D3DXVECTOR3 pos(0.0f, 0.0f, 0.0f);
		D3DXVECTOR3 direction(1.0f, -0.0f, 0.25f);
		D3DXCOLOR  color = WHITE;

		// 线光源|点光源
		D3DLIGHT9  Light = InitDirectionalLight(&direction, &color);
		//D3DLIGHT9  Light = InitPointLight(&pos, &color);

		m_pDirect3DDevice->SetRenderState(D3DRS_LIGHTING, true);
		m_pDirect3DDevice->SetLight(0, &Light);
		m_pDirect3DDevice->LightEnable(0, true);

		m_pDirect3DDevice->SetRenderState(D3DRS_NORMALIZENORMALS, true);
		m_pDirect3DDevice->SetRenderState(D3DRS_SPECULARENABLE, true);
	}
	return bRet;
}

void CD3DLight::UnInit()
{
	CD3DBase::UnInit();
	for(int i = 0; i < 4; ++i)
	{
		if (NULL != m_D3DMeshPtrs[i])
		{
			m_D3DMeshPtrs[i]->Release();
			m_D3DMeshPtrs[i] = NULL;
		}
	}
}

void CD3DLight::Draw()
{
	if(NULL == m_pDirect3DDevice)
		return ;

	static float angle = (3.0f*D3DX_PI)/2.0f;
	static float height = 5.0f;

	if (GetAsyncKeyState(VK_LEFT) & 0x8000f)
		angle -= 0.005f;
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000f)
		angle += 0.005f;
	if (GetAsyncKeyState(VK_UP) & 0x8000f)
		height += 0.05f;
	if (GetAsyncKeyState(VK_DOWN)&0x8000f)
		height -= 0.05f;

	D3DXVECTOR3 position(cosf(angle)*7.0f, height, sinf(angle)*7.0f);
	D3DXVECTOR3 target(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 up(0.0, 1.0f, 0.0f);
	D3DXMATRIX view;
	D3DXMatrixLookAtLH(&view, &position, &target, &up);
	m_pDirect3DDevice->SetTransform(D3DTS_VIEW, &view);

	m_pDirect3DDevice->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0x00000000, 1.0f, 0);
	m_pDirect3DDevice->BeginScene();

	for(int i = 0; i < 4; i++)
	{
		m_pDirect3DDevice->SetMaterial(&m_D3dMaterials[i]);
		m_pDirect3DDevice->SetTransform(D3DTS_WORLD, &m_D3dPositions[i]);
		m_D3DMeshPtrs[i]->DrawSubset(0);
	}

	m_pDirect3DDevice->EndScene();
	m_pDirect3DDevice->Present(0, 0, 0, 0);
}
