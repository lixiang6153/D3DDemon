// DrawTexture.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "DrawTexture.h"
#include "WindowBase.h"
#include "D3DWindow.h"
#include "D3DTexture.h"


int APIENTRY _tWinMain(HINSTANCE hInstance,
					   HINSTANCE hPrevInstance,
					   LPTSTR    lpCmdLine,
					   int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine); 

	CD3DTexture* pD3DTexture = new CD3DTexture;
	CD3DWindow objWindow(hInstance, pD3DTexture);
	objWindow.Create(1920, 1080);	
	objWindow.Show();

	delete pD3DTexture;
	pD3DTexture = NULL;

	return 0;
}
