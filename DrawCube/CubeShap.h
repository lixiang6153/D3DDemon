#pragma once
#include "d3dbase.h"

class CCubeShap :
	public CD3DBase
{
public:
	CCubeShap(void);
	virtual ~CCubeShap(void);

public:
	virtual bool Init(HWND hWnd, int nWidth, int nHeight, bool bFullScreen = true);
	virtual void UnInit();
	virtual void Draw();

protected:
	 IDirect3DVertexBuffer9*	m_pVertexBuffer;
	 IDirect3DIndexBuffer9*		m_pIndexBuffer;
	 ID3DXMesh*					m_pD3DMesh;
};
