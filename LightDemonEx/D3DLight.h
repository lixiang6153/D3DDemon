#pragma once
#include "d3dbase.h"

class CD3DLight :
	public CD3DBase
{
public:
	CD3DLight(void);
	virtual ~CD3DLight(void);

public:
	virtual bool Init(HWND hWnd, int nWidth, int nHeight, bool bFullScreen = true);
	virtual void UnInit();
	virtual void Draw();

protected:
	ID3DXMesh*		m_D3DMeshPtrs[4];
	D3DMATERIAL9	m_D3dMaterials[4];
	D3DXMATRIX		m_D3dPositions[4];
};
