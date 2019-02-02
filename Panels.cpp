#include "SDK.h"
#include "Panels.h"
#include "CDrawManager.h"
#include "Util.h"
#include "ESP.h"
#include "Menu.h"
#include "Radar.h"
CScreenSize gScreenSize;
//===================================================================================
void __fastcall Hooked_PaintTraverse( PVOID pPanels, int edx, unsigned int vguiPanel, bool forceRepaint, bool allowForce )
{
	try
	{
		if (gCvars.misc_noscope && !strcmp(gInts.Panels->GetName(vguiPanel), "HudScope")) { return; }
		VMTManager& hook = VMTManager::GetHook(pPanels); 
		hook.GetMethod<void(__thiscall*)(PVOID, unsigned int, bool, bool)>(gOffsets.iPaintTraverseOffset)(pPanels, vguiPanel, forceRepaint, allowForce); //Call the original.

		static unsigned int vguiFocusOverlayPanel;

		if (vguiFocusOverlayPanel == NULL)
		{											//FocusOverlayPanel
			const char* szName = gInts.Panels->GetName(vguiPanel);
			if( szName[0] == 'F' && szName[5] == 'O' &&  szName[12] == 'P' )
			{
				vguiFocusOverlayPanel = vguiPanel;
				Intro();
			}
		}
		
		if (vguiFocusOverlayPanel == vguiPanel )
		{
			int iWidth, iHeight; //Resolution fix, so this can work in Fullscreen
			gInts.Engine->GetScreenSize(iWidth, iHeight);
			if (gScreenSize.iScreenWidth != iWidth || gScreenSize.iScreenHeight != iHeight)
				gInts.Engine->GetScreenSize(gScreenSize.iScreenWidth, gScreenSize.iScreenHeight);

			if( gInts.Engine->IsDrawingLoadingImage() || !gInts.Engine->IsInGame( ) || !gInts.Engine->IsConnected() || gInts.Engine->Con_IsVisible( ) )
			{
				gDraw.DrawString(iWidth / 2, iHeight / 2 - 370, Color::Rainbow(), "hackname | [Team Fortress 2]");
				Menu::Get().PaintTraverse();
				gRadar.DrawRadarBack();
				gInts.Panels->SetMouseInputEnabled(vguiPanel, Menu::Get().IsVisible());
	
				return; //No need to draw the rest.
			}
			else
			{
				gDraw.DrawString(iWidth / 2, iHeight / 2 - 370, Color::Rainbow(), "hackname | [Team Fortress 2]");
			}

			CBaseEntity* pLocal = gInts.EntList->GetClientEntity(me); 

			if (!pLocal)
				return;
			if (gCvars.misc_cleanScreenshot)
			{
				if (gInts.Engine->IsTakingScreenshot() || GetAsyncKeyState(VK_F12) || GetAsyncKeyState(VK_SNAPSHOT))
					return;
			}
			gESP.Run(pLocal);
			gRadar.DrawRadarBack();
			gInts.Panels->SetMouseInputEnabled(vguiPanel, Menu::Get().IsVisible());
			Menu::Get().PaintTraverse();
			
		}
	}
	catch(...)
	{
		Log::Fatal("Failed PaintTraverse");
	}

}
//===================================================================================
void Intro( void )
{
	try
	{
		gDraw.Initialize(); //Initalize the drawing class.
		gNetVars.Initialize();
	}
	catch(...)
	{
		Log::Fatal("Failed Intro");
	}
}