#pragma once
#include "d3dbase.h"

class CD3DTexture :
	public CD3DBase
{
public:
	CD3DTexture(void);
	virtual ~CD3DTexture(void);

public:
	virtual bool Init(HWND hWnd, int nWidth, int nHeight, bool bFullScreen = true);
	virtual void UnInit();
	virtual void Draw();  

protected:
	IDirect3DVertexBuffer9*		m_pVertexBuffer;
	IDirect3DIndexBuffer9*		m_pIndexBuffer;
	IDirect3DTexture9*			m_pTextureBuffer;
};
