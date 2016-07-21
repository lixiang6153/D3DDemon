#pragma once
#include "d3dbase.h"

class CD3DAphla :
	public CD3DBase
{
public:
	CD3DAphla(void);
	virtual ~CD3DAphla(void);

public:
	virtual bool Init(HWND hWnd, int nWidth, int nHeight, bool bFullScreen = true);
	virtual void UnInit();
	virtual void Draw();

protected:
	IDirect3DVertexBuffer9*		m_pVertexBuffer;
	IDirect3DTexture9*			m_pTextureBuffer;
	ID3DXMesh*					m_pTeapot;
	D3DMATERIAL9				m_TeapotMtrl;
};
