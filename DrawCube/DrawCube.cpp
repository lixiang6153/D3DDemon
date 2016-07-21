// DrawCube.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "DrawCube.h"
#include "WindowBase.h"
#include "CubeShap.h"
#include "D3DWindow.h"


int APIENTRY _tWinMain(HINSTANCE hInstance,
					   HINSTANCE hPrevInstance,
					   LPTSTR    lpCmdLine,
					   int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine); 

	CCubeShap* pD3DShape = new CCubeShap;
	CD3DWindow objWindow(hInstance, pD3DShape);
	objWindow.Create(1920, 1080);	
	objWindow.Show();

	delete pD3DShape;
	pD3DShape = NULL;

	return 0;
}