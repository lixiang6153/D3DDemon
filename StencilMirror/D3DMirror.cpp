#include "StdAfx.h"
#include "D3DMirror.h"
#include "Vertex.h"

CD3DMirror::CD3DMirror(void)
: m_pVertexBuffer(NULL)
, m_pTextureWall(NULL)
, m_pTextureMirror(NULL)
, m_pTextureFloor(NULL)
, m_pTeapot(NULL)
{
	m_teapotPosition = D3DXVECTOR3(0.0f, 3.0f, -7.5f);
}

CD3DMirror::~CD3DMirror(void)
{
}

bool CD3DMirror::Init(HWND hWnd, int nWidth, int nHeight, bool bFullScreen/* = true*/)
{
	bool bRet = CD3DBase::Init(hWnd, nWidth, nHeight, bFullScreen);
	if (bRet)
	{
		// Create and specify geometry.  For this sample we draw a floor
		// and a wall with a mirror on it.  We put the floor, wall, and
		// mirror geometry in one vertex buffer.
		//
		//   |----|----|----|
		//   |Wall|Mirr|Wall|
		//   |    | or |    |
		//   /--------------/
		//  /   Floor      /
		// /--------------/
		m_pDirect3DDevice->CreateVertexBuffer(4*2*3*sizeof(CVertex), D3DUSAGE_WRITEONLY, FVF, D3DPOOL_MANAGED, &m_pVertexBuffer, NULL);
		if (NULL != m_pVertexBuffer)
		{
			CVertex* pVertex = NULL;
			m_pVertexBuffer->Lock(0, 0, (void**)&pVertex, 0);
			if (NULL != pVertex)
			{
				// floor
				pVertex[0] = CVertex(-7.5f, 0.0f, -10.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f);
				pVertex[1] = CVertex(-7.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f);
				pVertex[2] = CVertex(7.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f);

				pVertex[3] = CVertex(-7.5f, 0.0f, -10.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f);
				pVertex[4] = CVertex(7.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f);
				pVertex[5] = CVertex(7.5f, 0.0f,-10.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f);

				// wall	- left
				pVertex[6] = CVertex(-7.5f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f);
				pVertex[7] = CVertex(-7.5f, 5.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f);
				pVertex[8] = CVertex(-2.5f, 5.0f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f);

				pVertex[9] = CVertex(-7.5f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f);
				pVertex[10] = CVertex(-2.5f, 5.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f);
				pVertex[11] = CVertex(-2.5f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f);

				// wall - right
				pVertex[12] = CVertex(2.5f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f);
				pVertex[13] = CVertex(2.5f, 5.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f);
				pVertex[14] = CVertex(7.5f, 5.0f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f);

				pVertex[15] = CVertex(2.5f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f);
				pVertex[16] = CVertex(7.5f, 5.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f);
				pVertex[17] = CVertex(7.5f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f);

				// mirror
				pVertex[18] = CVertex(-2.5f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f);
				pVertex[19] = CVertex(-2.5f, 5.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f);
				pVertex[20] = CVertex(2.5f, 5.0f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f);

				pVertex[21] = CVertex(-2.5f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f);
				pVertex[22] = CVertex(2.5f, 5.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f);
				pVertex[23] = CVertex(2.5f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f);
			}
			m_pVertexBuffer->Unlock();

			D3DXCreateTeapot(m_pDirect3DDevice, &m_pTeapot, 0);

			// ��������
			D3DXCreateTextureFromFile(m_pDirect3DDevice, _T("checker.jpg"), &m_pTextureFloor);
			D3DXCreateTextureFromFile(m_pDirect3DDevice, _T("brick0.jpg"), &m_pTextureWall);
			D3DXCreateTextureFromFile(m_pDirect3DDevice, _T("ice.bmp"), &m_pTextureMirror);

			// ����������������
			m_pDirect3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
			m_pDirect3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
			m_pDirect3DDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_POINT);

			// ����alpha���ͨ����Դ
			m_pDirect3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_DIFFUSE);
			m_pDirect3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);

			// ���ò����ù�Դ
			D3DXVECTOR3 lightDir(0.707f, -0.707f, 0.707f);
			D3DXCOLOR color(1.0f, 1.0f, 1.0f, 1.0f);
			D3DLIGHT9 light = InitDirectionalLight(&lightDir, &color);

			m_pDirect3DDevice->SetLight(0, &light);
			m_pDirect3DDevice->LightEnable(0, true);

			// �����淨������λ��,�����Դ����
			m_pDirect3DDevice->SetRenderState(D3DRS_NORMALIZENORMALS, true);
			m_pDirect3DDevice->SetRenderState(D3DRS_SPECULARENABLE, true);
		}
	}
	return bRet;
}

void CD3DMirror::UnInit()
{
	CD3DBase::UnInit();
	if (NULL != m_pVertexBuffer)
	{
		m_pVertexBuffer->Release();
		m_pVertexBuffer = NULL;
	}
	if (NULL != m_pTextureWall)
	{
		m_pTextureWall->Release();
		m_pTextureWall = NULL;
	}
	if (NULL != m_pTextureMirror)
	{
		m_pTextureMirror->Release();
		m_pTextureMirror = NULL;
	}
	if (NULL != m_pTextureFloor)
	{
		m_pTextureFloor->Release();
		m_pTextureFloor = NULL;
	}
	if (NULL != m_pTeapot)
	{
		m_pTeapot->Release();
		m_pTeapot = NULL;
	}

}

void CD3DMirror::Draw()
{
	static float radius = 20.0f;

	float timeDelta = 0.01f;
	if( ::GetAsyncKeyState(VK_LEFT) & 0x8000f )
		m_teapotPosition.x -= 3.0f * timeDelta;

	if( ::GetAsyncKeyState(VK_RIGHT) & 0x8000f )
		m_teapotPosition.x += 3.0f * timeDelta;

	if( ::GetAsyncKeyState(VK_UP) & 0x8000f )
		radius -= 2.0f * timeDelta;

	if( ::GetAsyncKeyState(VK_DOWN) & 0x8000f )
		radius += 2.0f * timeDelta;


	static float angle = (3.0f * D3DX_PI) / 2.0f;

	if( ::GetAsyncKeyState('A') & 0x8000f )
		angle -= 0.5f * timeDelta;

	if( ::GetAsyncKeyState('S') & 0x8000f )
		angle += 0.5f * timeDelta;

	D3DXVECTOR3 position( cosf(angle) * radius, 3.0f, sinf(angle) * radius );
	D3DXVECTOR3 target(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);
	D3DXMATRIX V;
	D3DXMatrixLookAtLH(&V, &position, &target, &up);
	m_pDirect3DDevice->SetTransform(D3DTS_VIEW, &V);

	// ����󻺴�|��Ȼ���|ģ�建��-��Ϊ0
	m_pDirect3DDevice->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL,0xff000000, 1.0f, 0L);
	m_pDirect3DDevice->BeginScene();

	// ���Ʋ��
	m_pDirect3DDevice->SetMaterial(&RED_MTRL);
	m_pDirect3DDevice->SetTexture(0, 0);
	D3DXMATRIX W;
	D3DXMatrixTranslation(&W,m_teapotPosition.x, m_teapotPosition.y,m_teapotPosition.z);

	m_pDirect3DDevice->SetTransform(D3DTS_WORLD, &W);
	m_pTeapot->DrawSubset(0);

	// ����Χǽ
	D3DXMATRIX I;
	D3DXMatrixIdentity(&I);
	m_pDirect3DDevice->SetTransform(D3DTS_WORLD, &I);

	m_pDirect3DDevice->SetStreamSource(0, m_pVertexBuffer, 0, sizeof(CVertex));
	m_pDirect3DDevice->SetFVF(FVF);

	// ���Ƶذ�
	m_pDirect3DDevice->SetMaterial(&WHITE_MTRL);
	m_pDirect3DDevice->SetTexture(0, m_pTextureFloor);
	m_pDirect3DDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);

	// ����ǽ
	m_pDirect3DDevice->SetMaterial(&WHITE_MTRL);
	m_pDirect3DDevice->SetTexture(0, m_pTextureWall);
	m_pDirect3DDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 6, 4);

	// �����м�ľ���
	m_pDirect3DDevice->SetMaterial(&WHITE_MTRL);
	m_pDirect3DDevice->SetTexture(0,m_pTextureMirror);
	m_pDirect3DDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 18, 2);

	// ����ģ�建��
	m_pDirect3DDevice->SetRenderState(D3DRS_STENCILENABLE,    true);
	
	// ����ģ�建��ο�ֵ��ģ�������Լ�ģ��д����(�޸ĵ�ʱ��ֻ���޸��ҹ涨��λ,�˴�������Ϊÿһλ������д,�൱��û������)
	m_pDirect3DDevice->SetRenderState(D3DRS_STENCILREF,       0x1);
	m_pDirect3DDevice->SetRenderState(D3DRS_STENCILMASK,      0xffffffff);
	m_pDirect3DDevice->SetRenderState(D3DRS_STENCILWRITEMASK, 0xffffffff);

	// ����ģ����Ի���Ȳ��Ժ���(��ʹģ�����ͨ��������Ȳ��Բ�ͨ����<���������Ϊʲô��Ҫʹ����Ȳ��Ե�ԭ��>����Ȼ���ı��Ӧ��ģ��ֵ)
	// �����£�������ӵ�ס��һ���־��ӣ�������һ���֣���ʹλ�ھ��ӷ�Χ֮�ڣ�����Ҳ���������ӵ�����ɡ��������Ȳ���ʧ�ܵ��µġ�
	// �����ʱ���ǾͲ���Ҫ�޸Ķ�Ӧ��ģ��ֵ�ˡ���Ȼ�������޸��ˣ������������ƾ�������ʱ��������Ϊ��Ȳ���ʧ�ܶ�����
	// ���ò���Ϊһֱͨ����Ҳ���Ǻ������Ƶľ��Ӳ��־�ģ�������֤��ͨ����ͨ���󶼽��滻Ϊ�ο�ֵ,��Ϊ���ɹ�����ֻҪ����D3DRS_STENCILPASSΪ�滻����,
	// Ҳ����˵��������ƾ��ӵĲ���ģ��ֵ0���滻Ϊ�ο�ֵ1��D3DCMP_ALWAYSĿ�ľ����޸�ģ��ֵΪ�ο�ֵ��һ������������equal���ԣ�ֻ����Ϊ1�ĵط�
	m_pDirect3DDevice->SetRenderState(D3DRS_STENCILFUNC,      D3DCMP_ALWAYS);
	m_pDirect3DDevice->SetRenderState(D3DRS_STENCILZFAIL,     D3DSTENCILOP_KEEP);
	m_pDirect3DDevice->SetRenderState(D3DRS_STENCILPASS,      D3DSTENCILOP_REPLACE);

	// {ע�⣺��ֹ�޸���Ȼ���ͺ�̨���棬������ƾ���(ֻ�Ծ�����ģ��У���޸�),���޸���ɫ(��̨�������Ȼ���)
	m_pDirect3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);
	m_pDirect3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	m_pDirect3DDevice->SetRenderState(D3DRS_SRCBLEND,  D3DBLEND_ZERO);
	m_pDirect3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// �޸ľ��ӵ�ģ�建����(���ƾ��ӵ���������ģ�建�涼�޸�Ϊ1)
	m_pDirect3DDevice->SetStreamSource(0, m_pVertexBuffer, 0, sizeof(CVertex));
	m_pDirect3DDevice->SetFVF(FVF);
	m_pDirect3DDevice->SetMaterial(&WHITE_MTRL);
	m_pDirect3DDevice->SetTexture(0,m_pTextureMirror);

	D3DXMatrixIdentity(&I);
	m_pDirect3DDevice->SetTransform(D3DTS_WORLD, &I);
	m_pDirect3DDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 18, 2);

	// }�������ú�̨�������Ȼ����޸�,׼������,����������������Ƶ���������
	m_pDirect3DDevice->SetRenderState( D3DRS_ZWRITEENABLE, true );

	// �����������ֻ��ģ��ֵΪ1�ĵط����л��ƣ����Ƶ�ԭ����ǵ�ǰģ�建�����ֵΪ1 & mask = ref 0x1 &mask�Ĳ���
	// Ҳ����ģ��ֵΪ1�Ĳ���������Ի��Ʋ��޸ĺ�̨����,��������֮��ķ�1�����򲻽�����Ȼ���ͺ�̨������޸�
	m_pDirect3DDevice->SetRenderState(D3DRS_STENCILFUNC,  D3DCMP_EQUAL);
	m_pDirect3DDevice->SetRenderState(D3DRS_STENCILPASS,  D3DSTENCILOP_KEEP);

	// ��ȡ����ķ������
	D3DXMATRIX W2, T, R;
	D3DXPLANE plane(0.0f, 0.0f, 1.0f, 0.0f); // xy plane
	D3DXMatrixReflect(&R, &plane);
	D3DXMatrixTranslation(&T,m_teapotPosition.x, m_teapotPosition.y,m_teapotPosition.z); 
	W2 = T * R;

	// �����Ȼ���,����ܹؼ�,ʹ�ú������Ӻ���Ĳ������ʾ����������-����ȿ���
    m_pDirect3DDevice->Clear(0, 0, D3DCLEAR_ZBUFFER, 0, 1.0f, 0);
	m_pDirect3DDevice->SetRenderState(D3DRS_SRCBLEND,  D3DBLEND_DESTCOLOR);
	m_pDirect3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ZERO);

	m_pDirect3DDevice->SetTransform(D3DTS_WORLD, &W2);
	m_pDirect3DDevice->SetMaterial(&WHITE_MTRL);
	m_pDirect3DDevice->SetTexture(0, 0);

	// ���ڲ���ܿ�������Ϊ˳ʱ����������ʾ,��������Ϊ���Կ���(Ҳ���Ǳ��������)
	m_pDirect3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
	m_pDirect3DDevice->SetMaterial(&RED_MTRL);
	m_pTeapot->DrawSubset(0);
	m_pDirect3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	// �ָ���Ⱦ״̬
	m_pDirect3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	m_pDirect3DDevice->SetRenderState( D3DRS_STENCILENABLE, false);

	m_pDirect3DDevice->EndScene();
	m_pDirect3DDevice->Present(0, 0, 0, 0);
}