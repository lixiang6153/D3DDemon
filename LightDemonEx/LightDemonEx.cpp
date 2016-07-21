// LightDemonEx.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "LightDemonEx.h"
#include "WindowBase.h"
#include "D3DWindow.h"
#include "D3DLight.h"


int APIENTRY _tWinMain(HINSTANCE hInstance,
					   HINSTANCE hPrevInstance,
					   LPTSTR    lpCmdLine,
					   int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine); 

	CD3DLight* pD3DShape = new CD3DLight;
	CD3DWindow objWindow(hInstance, pD3DShape);
	objWindow.Create(1920, 1080);	
	objWindow.Show();

	delete pD3DShape;
	pD3DShape = NULL;

	return 0;
}