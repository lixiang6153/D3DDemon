#pragma once
#include "d3dbase.h"

class CD3DMirror :
	public CD3DBase
{
public:
	CD3DMirror(void);
	virtual ~CD3DMirror(void);

public:
	virtual bool Init(HWND hWnd, int nWidth, int nHeight, bool bFullScreen = true);
	virtual void UnInit();
	virtual void Draw();

protected:
	IDirect3DVertexBuffer9*	m_pVertexBuffer;
	IDirect3DTexture9*		m_pTextureWall;
	IDirect3DTexture9*		m_pTextureMirror;
	IDirect3DTexture9*		m_pTextureFloor;
	ID3DXMesh*				m_pTeapot;
	D3DXVECTOR3				m_teapotPosition;
};
