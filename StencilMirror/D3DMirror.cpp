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

			// 创建纹理
			D3DXCreateTextureFromFile(m_pDirect3DDevice, _T("checker.jpg"), &m_pTextureFloor);
			D3DXCreateTextureFromFile(m_pDirect3DDevice, _T("brick0.jpg"), &m_pTextureWall);
			D3DXCreateTextureFromFile(m_pDirect3DDevice, _T("ice.bmp"), &m_pTextureMirror);

			// 设置纹理缩放类型
			m_pDirect3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
			m_pDirect3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
			m_pDirect3DDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_POINT);

			// 设置alpha混合通道来源
			m_pDirect3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_DIFFUSE);
			m_pDirect3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);

			// 设置并启用光源
			D3DXVECTOR3 lightDir(0.707f, -0.707f, 0.707f);
			D3DXCOLOR color(1.0f, 1.0f, 1.0f, 1.0f);
			D3DLIGHT9 light = InitDirectionalLight(&lightDir, &color);

			m_pDirect3DDevice->SetLight(0, &light);
			m_pDirect3DDevice->LightEnable(0, true);

			// 设置面法向量单位化,方便光源处理
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

	// 清除后缓存|深度缓存|模板缓存-置为0
	m_pDirect3DDevice->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL,0xff000000, 1.0f, 0L);
	m_pDirect3DDevice->BeginScene();

	// 绘制茶壶
	m_pDirect3DDevice->SetMaterial(&RED_MTRL);
	m_pDirect3DDevice->SetTexture(0, 0);
	D3DXMATRIX W;
	D3DXMatrixTranslation(&W,m_teapotPosition.x, m_teapotPosition.y,m_teapotPosition.z);

	m_pDirect3DDevice->SetTransform(D3DTS_WORLD, &W);
	m_pTeapot->DrawSubset(0);

	// 绘制围墙
	D3DXMATRIX I;
	D3DXMatrixIdentity(&I);
	m_pDirect3DDevice->SetTransform(D3DTS_WORLD, &I);

	m_pDirect3DDevice->SetStreamSource(0, m_pVertexBuffer, 0, sizeof(CVertex));
	m_pDirect3DDevice->SetFVF(FVF);

	// 绘制地板
	m_pDirect3DDevice->SetMaterial(&WHITE_MTRL);
	m_pDirect3DDevice->SetTexture(0, m_pTextureFloor);
	m_pDirect3DDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);

	// 绘制墙
	m_pDirect3DDevice->SetMaterial(&WHITE_MTRL);
	m_pDirect3DDevice->SetTexture(0, m_pTextureWall);
	m_pDirect3DDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 6, 4);

	// 绘制中间的镜子
	m_pDirect3DDevice->SetMaterial(&WHITE_MTRL);
	m_pDirect3DDevice->SetTexture(0,m_pTextureMirror);
	m_pDirect3DDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 18, 2);

	// 启用模板缓存
	m_pDirect3DDevice->SetRenderState(D3DRS_STENCILENABLE,    true);
	
	// 设置模板缓存参考值和模板掩码以及模板写掩码(修改的时候只能修改我规定的位,此处我们置为每一位都可以写,相当于没有设置)
	m_pDirect3DDevice->SetRenderState(D3DRS_STENCILREF,       0x1);
	m_pDirect3DDevice->SetRenderState(D3DRS_STENCILMASK,      0xffffffff);
	m_pDirect3DDevice->SetRenderState(D3DRS_STENCILWRITEMASK, 0xffffffff);

	// 设置模板测试或深度测试函数(即使模板测试通过，但深度测试不通过的<这就是这里为什么需要使用深度测试的原因>，依然不改变对应的模板值)
	// 设想下，如果箱子挡住了一部分镜子，对于这一部分，即使位于镜子范围之内，我们也看不到镜子的物体吧。这就是深度测试失败导致的。
	// 因此这时我们就不需要修改对应的模板值了。当然，就算修改了，后面真正绘制镜子物体时，还会因为深度测试失败而丢弃
	// 设置测试为一直通过，也就是后续绘制的镜子部分经模板测试验证都通过，通过后都将替换为参考值,因为都成功所以只要设置D3DRS_STENCILPASS为替换即可,
	// 也就是说将后面绘制镜子的部分模板值0都替换为参考值1，D3DCMP_ALWAYS目的就是修改模板值为参考值，一遍后续茶壶进行equal测试，只绘制为1的地方
	m_pDirect3DDevice->SetRenderState(D3DRS_STENCILFUNC,      D3DCMP_ALWAYS);
	m_pDirect3DDevice->SetRenderState(D3DRS_STENCILZFAIL,     D3DSTENCILOP_KEEP);
	m_pDirect3DDevice->SetRenderState(D3DRS_STENCILPASS,      D3DSTENCILOP_REPLACE);

	// {注意：禁止修改深度缓存和后台缓存，后面绘制镜子(只对镜子做模板校验修改),不修改颜色(后台缓存和深度缓存)
	m_pDirect3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);
	m_pDirect3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	m_pDirect3DDevice->SetRenderState(D3DRS_SRCBLEND,  D3DBLEND_ZERO);
	m_pDirect3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// 修改镜子的模板缓存区(绘制镜子的区域所有模板缓存都修改为1)
	m_pDirect3DDevice->SetStreamSource(0, m_pVertexBuffer, 0, sizeof(CVertex));
	m_pDirect3DDevice->SetFVF(FVF);
	m_pDirect3DDevice->SetMaterial(&WHITE_MTRL);
	m_pDirect3DDevice->SetTexture(0,m_pTextureMirror);

	D3DXMatrixIdentity(&I);
	m_pDirect3DDevice->SetTransform(D3DTS_WORLD, &I);
	m_pDirect3DDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 18, 2);

	// }重新启用后台缓存和深度缓存修改,准备绘制,将反射的虚拟茶壶绘制到镜子里面
	m_pDirect3DDevice->SetRenderState( D3DRS_ZWRITEENABLE, true );

	// 后续茶壶绘制只对模板值为1的地方进行绘制，绘制的原则就是当前模板缓存里的值为1 & mask = ref 0x1 &mask的部分
	// 也就是模板值为1的部分区域可以绘制并修改后台缓存,其他镜子之外的非1的区域不进行深度缓存和后台缓存的修改
	m_pDirect3DDevice->SetRenderState(D3DRS_STENCILFUNC,  D3DCMP_EQUAL);
	m_pDirect3DDevice->SetRenderState(D3DRS_STENCILPASS,  D3DSTENCILOP_KEEP);

	// 获取茶壶的反射矩阵
	D3DXMATRIX W2, T, R;
	D3DXPLANE plane(0.0f, 0.0f, 1.0f, 0.0f); // xy plane
	D3DXMatrixReflect(&R, &plane);
	D3DXMatrixTranslation(&T,m_teapotPosition.x, m_teapotPosition.y,m_teapotPosition.z); 
	W2 = T * R;

	// 清楚深度缓存,这个很关键,使得后续镜子后面的茶壶能显示到镜子里面-无深度可言
    m_pDirect3DDevice->Clear(0, 0, D3DCLEAR_ZBUFFER, 0, 1.0f, 0);
	m_pDirect3DDevice->SetRenderState(D3DRS_SRCBLEND,  D3DBLEND_DESTCOLOR);
	m_pDirect3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ZERO);

	m_pDirect3DDevice->SetTransform(D3DTS_WORLD, &W2);
	m_pDirect3DDevice->SetMaterial(&WHITE_MTRL);
	m_pDirect3DDevice->SetTexture(0, 0);

	// 由于茶壶能看见是因为顺时针三角形显示,反射后背面变为可以看见(也就是背面变正面)
	m_pDirect3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
	m_pDirect3DDevice->SetMaterial(&RED_MTRL);
	m_pTeapot->DrawSubset(0);
	m_pDirect3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	// 恢复渲染状态
	m_pDirect3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	m_pDirect3DDevice->SetRenderState( D3DRS_STENCILENABLE, false);

	m_pDirect3DDevice->EndScene();
	m_pDirect3DDevice->Present(0, 0, 0, 0);
}