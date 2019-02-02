#pragma once
//===================================================================================
#include "SDK.h"
#include "Panels.h"
#include "Font.h"

#define RED(COLORCODE)	((int) ( COLORCODE >> 24) )
#define BLUE(COLORCODE)	((int) ( COLORCODE >> 8 ) & 0xFF )
#define GREEN(COLORCODE)	((int) ( COLORCODE >> 16 ) & 0xFF )
#define ALPHA(COLORCODE)	((int) COLORCODE & 0xFF )
#define COLORCODE(r,g,b,a)((DWORD)((((r)&0xff)<<24)|(((g)&0xff)<<16)|(((b)&0xff)<<8)|((a)&0xff)))
//===================================================================================
static HFont g_DefaultFont;
static HFont g_ESPFont;
class CDrawManager
{
public:
	void Initialize( );
	void DrawString( int x, int y, Color clrColor, const wchar_t *pszText, HFont font = g_DefaultFont, bool CenterX = false, bool CenterY = false);
	void DrawString( int x, int y, Color clrColor, const char *pszText, ... );
	byte GetESPHeight( );
	RECT get_text_size(const char* _Input, int font);
	void outline(int x, int y, int w, int h, Color clrColor);
	void rect(int x, int y, int w, int h, Color clrColor);
	void text(int x, int y, Color clrColor, const char* _Input, ...);
	void DrawCircle(float x, float y, float r, float s, Color color);
	void DrawCircleForRadar(float x, float y, float r, float s, Color color);

	void FillRadar(float x, float y, float r, float s, Color color);
	void DrawLine(int x0, int y0, int x1, int y1, Color clrColor);
	void DrawLineEx(int x, int y, int w, int h, Color clrColor);
	void DrawBox( Vector vOrigin, int r, int g, int b, int alpha, int box_width, int radius );
	void DrawRectRadar(int x, int y, int w, int h, Color clrColor);
	void DrawRect( int x, int y, int w, int h, Color clrColor);
	void OutlineRect( int x, int y, int w, int h, Color clrColor);
	void DrawFillbox(int x, int y, int w, int h, TColor clrColor);
	void DrawCrosshair(int iValue);
	void DrawCornerBox(int x, int y, int w, int h, int cx, int cy, Color Col); 
	bool WorldToScreen( Vector &vOrigin, Vector &vScreen );
	Color GetPlayerColor(CBaseEntity* pLocal,  CBaseEntity* pEntity);
	void DrawCornerFaceBox(int x, int y, int w, int h, int cx, int cy, Color Col);
	
};
//===================================================================================
extern CDrawManager gDraw;
//===================================================================================