#include "CDrawManager.h"
//===================================================================================
CDrawManager gDraw;
#define M_PI 3.14159265358979323846
#define ESP_HEIGHT 14
//===================================================================================


// ---------------------------------------------------------
// Purpose: Passing position to drawing functions.
// Usage: Position{_x, _y}
// ---------------------------------------------------------
struct Position
{
public:

	int		x;
	int		y;
};


// ---------------------------------------------------------
// Usage: FilledCircle{Position{_x, _y}, 10f}
// ---------------------------------------------------------
struct FilledCircle
{
public:

	Position     pos;
	float		 radius;
};

// ---------------------------------------------------------
// Purpose: 
// ---------------------------------------------------------
struct Vertex_t
{
public:

	float	x;
	float	y;

private:

	float	tex_x = 0.f;
	float	tex_y = 0.f;
};
inline void ClampFl(float &fl)
{
	if (fl > 1)
		fl = 1;
	else if (fl < 0)
		fl = 0;
}
SColor hsv2rgb(float hue, float saturation, float brightness, int alpha)
{
	while (hue >= 1)
		hue -= 1;
	while (hue <= 0)
		hue += 1;

	ClampFl(saturation);
	ClampFl(brightness);

	float h = hue == 1.0f ? 0 : hue * 6.0f;
	float f = h - (int)h;
	float p = brightness * (1.0f - saturation);
	float q = brightness * (1.0f - saturation * f);
	float t = brightness * (1.0f - (saturation * (1.0f - f)));

	if (h < 1)
	{
		return SColor(
			(unsigned char)(brightness * 255),
			(unsigned char)(t * 255),
			(unsigned char)(p * 255),
			alpha
		);
	}
	else if (h < 2)
	{
		return SColor(
			(unsigned char)(q * 255),
			(unsigned char)(brightness * 255),
			(unsigned char)(p * 255),
			alpha
		);
	}
	else if (h < 3)
	{
		return SColor(
			(unsigned char)(p * 255),
			(unsigned char)(brightness * 255),
			(unsigned char)(t * 255),
			alpha
		);
	}
	else if (h < 4)
	{
		return SColor(
			(unsigned char)(p * 255),
			(unsigned char)(q * 255),
			(unsigned char)(brightness * 255),
			alpha
		);
	}
	else if (h < 5)
	{
		return SColor(
			(unsigned char)(t * 255),
			(unsigned char)(p * 255),
			(unsigned char)(brightness * 255),
			alpha
		);
	}
	else
	{
		return SColor(
			(unsigned char)(brightness * 255),
			(unsigned char)(p * 255),
			(unsigned char)(q * 255),
			alpha
		);
	}
}
void CDrawManager::Initialize( )
{
	if ( gInts.Surface == NULL )
		return;

	gInts.Engine->GetScreenSize( gScreenSize.iScreenWidth, gScreenSize.iScreenHeight );
	g_DefaultFont = gInts.Surface->CreateFont( );	//This is better than Arial
	g_ESPFont = gInts.Surface->CreateFont();
	gInts.Surface->SetFontGlyphSet( g_DefaultFont, "Tahoma", ESP_HEIGHT, 500, 0, 0, 0x200 );
	gInts.Surface->SetFontGlyphSet(g_ESPFont, "Tahoma", 10, 500, 0, 0, 0x200);
	
}
//===================================================================================
Color CDrawManager::GetPlayerColor(CBaseEntity* pLocal, CBaseEntity* pEntity)
{
	for (int i = 0; i < 65; i++)
	{
		if (pLocal->GetIndex() == gCvars.iAimbotIndex)
			return Color::Yellow();
		//else if (!gCvars.PlayerMode[pPlayer->GetIndex()])
		//	return Color(0, 255, 255, 255);
		//else if (gCvars.PlayerMode[pPlayer->GetIndex()] == 2)
		//	return Color::Yellow();
		else
		{		
			if (pLocal->GetTeamNum() == pEntity->GetTeamNum())
				return Color(0, 255, 0, 255);
			else if (pLocal->GetTeamNum() != pEntity->GetTeamNum())
				return Color(255, 0, 0, 255);
		}
	}
	return Color(0, 0, 0, 0); //no reason for this to be here, i just wanna look smart
}
//===================================================================================
void CDrawManager::DrawString( int x, int y, Color clrColor, const wchar_t *pszText, HFont font, bool CenterX, bool CenterY)
{
	if( pszText == NULL )
		return;

	if (CenterX || CenterY)
	{
		int wide, tall;
		gInts.Surface->GetTextSize(font, pszText, wide, tall);
		if (CenterX)
			x -= wide / 2;
		if (CenterY)
			y -= tall / 2;
	}

	gInts.Surface->DrawSetTextPos( x, y );
	gInts.Surface->DrawSetTextFont( font );
	gInts.Surface->DrawSetTextColor( clrColor.r(), clrColor.g(), clrColor.b(), clrColor.a() );
	gInts.Surface->DrawPrintText( pszText, wcslen( pszText ) );
}
void CDrawManager::rect(int x, int y, int w, int h, Color clrColor)
{
	gInts.Surface->DrawSetColor(clrColor.r(), clrColor.g(), clrColor.b(), clrColor.a());
	gInts.Surface->DrawFilledRect(x, y, x + w, y + h);
}
void CDrawManager::outline(int x, int y, int w, int h, Color clrColor)
{
	gInts.Surface->DrawSetColor(clrColor.r(), clrColor.g(), clrColor.b(), clrColor.a());
	gInts.Surface->DrawOutlinedRect(x, y, x + w, y + h);
}
//===================================================================================
void CDrawManager::DrawString( int x, int y, Color clrColor, const char *pszText, ... )
{
	if( pszText == NULL )
		return;

	va_list va_alist;
	char szBuffer[1024] = { '\0' };
	wchar_t szString[1024] = { '\0' };

	va_start( va_alist, pszText );
	vsprintf_s( szBuffer, pszText, va_alist );
	va_end( va_alist );

	wsprintfW( szString, L"%S", szBuffer );

	gInts.Surface->DrawSetTextPos( x, y );
	gInts.Surface->DrawSetTextFont( g_DefaultFont );
	gInts.Surface->DrawSetTextColor( clrColor.r(), clrColor.g(), clrColor.b(), clrColor.a() );
	gInts.Surface->DrawPrintText( szString, wcslen( szString ) );
}

void CDrawManager::text(int x, int y, Color clrColor, const char* _Input, ...)
{
	int apple = 0;
	char Buffer[2048] = { '\0' };
	va_list Args;
	va_start(Args, _Input);
	vsprintf_s(Buffer, _Input, Args);
	va_end(Args);
	size_t Size = strlen(Buffer) + 1;
	wchar_t* WideBuffer = new wchar_t[Size];
	mbstowcs_s(0, WideBuffer, Size, Buffer, Size - 1);

	gInts.Surface->DrawSetTextColor(clrColor.r(), clrColor.g(), clrColor.b(), clrColor.a());
	gInts.Surface->DrawSetTextFont(g_DefaultFont);
	gInts.Surface->DrawSetTextPos(x, y);
	gInts.Surface->DrawPrintText(WideBuffer, wcslen(WideBuffer));
}



//===================================================================================
byte CDrawManager::GetESPHeight( )
{
	return ESP_HEIGHT;
}
//===================================================================================
void CDrawManager::DrawLine(int x, int y, int x1, int y1, Color clrColor)
{
	gInts.Surface->DrawSetColor(clrColor.r(), clrColor.g(), clrColor.b(), clrColor.a());
	gInts.Surface->DrawLine(x, y, x1, y1);
}
//===================================================================================
void CDrawManager::DrawLineEx(int x, int y, int w, int h, Color clrColor)
{
	gInts.Surface->DrawSetColor(clrColor.r(), clrColor.g(), clrColor.b(), clrColor.a());
	gInts.Surface->DrawLine(x, y, x + w, y + h);
}
//===================================================================================
void CDrawManager::DrawRect( int x, int y, int w, int h, Color clrColor)
{
	gInts.Surface->DrawSetColor( clrColor.r(), clrColor.g(), clrColor.b(), clrColor.a() );
	gInts.Surface->DrawFilledRect( x, y, x + w, y + h );
}
void CDrawManager::DrawFillbox(int x, int y, int w, int h, TColor clrColor)
{
	gInts.Surface->DrawSetColor(clrColor.r(), clrColor.g(), clrColor.b(), clrColor.a());
	gInts.Surface->DrawFilledRect(x, y, x + w, y + h);
}
//===================================================================================
void CDrawManager::OutlineRect( int x, int y, int w, int h, Color clrColor)
{
	gInts.Surface->DrawSetColor( clrColor.r(), clrColor.g(), clrColor.b(), clrColor.a() );
	gInts.Surface->DrawOutlinedRect( x, y, x + w, y + h );
}
//===================================================================================
void CDrawManager::DrawBox( Vector vOrigin, int r, int g, int b, int alpha, int box_width, int radius )
{
	Vector vScreen;

	if( !WorldToScreen( vOrigin, vScreen ) )
		return;

	int radius2 = radius<<1;

	OutlineRect( vScreen.x - radius + box_width, vScreen.y - radius + box_width, radius2 - box_width, radius2 - box_width, Color::Black() );
	OutlineRect( vScreen.x - radius - 1, vScreen.y - radius - 1, radius2 + ( box_width + 2 ), radius2 + ( box_width + 2 ), Color::Black() );
	DrawRect( vScreen.x - radius + box_width, vScreen.y - radius, radius2 - box_width, box_width, Color( r, g, b, alpha ));
	DrawRect( vScreen.x - radius, vScreen.y + radius, radius2, box_width, Color( r, g, b, alpha ));
	DrawRect( vScreen.x - radius, vScreen.y - radius, box_width, radius2, Color( r, g, b, alpha ));
	DrawRect( vScreen.x + radius, vScreen.y - radius, box_width, radius2 + box_width, Color( r, g, b, alpha ) );
}

void CDrawManager::DrawRectRadar(int x,int y,int w,int h, Color clrColor)
{
	gDraw.outline(x, y, w, h, clrColor);
	gDraw.outline(x, y , w, h , Color(21, 255, 21));
	gDraw.outline(x , y , w , h , Color(21, 255, 21));
}

void CDrawManager::DrawCircle(float x, float y, float r, float s, Color color)
{
	float Step = M_PI * 2.0 / s;
	for (float a = 0; a < (M_PI * 2.0); a += Step)
	{
		float x1 = r * cos(a) + x;
		float y1 = r * sin(a) + y;
		float x2 = r * cos(a + Step) + x;
		float y2 = r * sin(a + Step) + y;
		DrawLine(x1, y1, x2, y2, color);
	}
}
void CDrawManager::DrawCircleForRadar(float x, float y, float r, float s, Color color)
{
	float Step = M_PI * 2.0 / s;
	for (float a = 0; a < (M_PI * 2.0); a += Step)
	{
		float x1 = r * cos(a) + x;
		float y1 = r * sin(a) + y;
		float x2 = r * cos(a + Step) + x;
		float y2 = r * sin(a + Step) + y;
		DrawLine(x1, y1, x2, y2, color);	
		gInts.Surface->DrawFilledRect(x1, y1, x2, y2);
	
	}
}


void polygon(int count, Vertex_t* Vertexs, Color color)
{
	static int Texture = gInts.Surface->CreateNewTextureID(true);
	unsigned char buffer[4] = { 255, 255, 255, 255 };

	gInts.Surface->DrawSetTextureRGBA(Texture, buffer, 1, 1);
	gInts.Surface->DrawSetColor(color.r(), color.g(), color.b(), color.a());
	gInts.Surface->DrawSetTexture(Texture);

	
}


void CDrawManager::FillRadar(float x, float y, float r, float s, Color color)
{
	float Step = M_PI * 2.0 / s;
	for (float a = 0; a < (M_PI * 2.0); a += Step)
	{
		float x1 = r * cos(a) + x;
		float y1 = r * sin(a) + y;
		float x2 = r * cos(a + Step) + x;
		float y2 = r * sin(a + Step) + y;
		
		gInts.Surface->DrawSetColor(color.r(), color.g(), color.b(), color.a());
		gInts.Surface->DrawFilledRect(x1, y1, x2, y2);
	
	}
}

//===================================================================================
bool CDrawManager::WorldToScreen( Vector &vOrigin, Vector &vScreen )
{
	const matrix3x4& worldToScreen = gInts.Engine->WorldToScreenMatrix(); //Grab the world to screen matrix from CEngineClient::WorldToScreenMatrix

	float w = worldToScreen[3][0] * vOrigin[0] + worldToScreen[3][1] * vOrigin[1] + worldToScreen[3][2] * vOrigin[2] + worldToScreen[3][3]; //Calculate the angle in compareson to the player's camera.
	vScreen.z = 0; //Screen doesn't have a 3rd dimension.

	if( w > 0.001 ) //If the object is within view.
	{
		float fl1DBw = 1 / w; //Divide 1 by the angle.
		vScreen.x = (gScreenSize.iScreenWidth / 2) + ( 0.5 * ((worldToScreen[0][0] * vOrigin[0] + worldToScreen[0][1] * vOrigin[1] + worldToScreen[0][2] * vOrigin[2] + worldToScreen[0][3]) * fl1DBw) * gScreenSize.iScreenWidth + 0.5); //Get the X dimension and push it in to the Vector.
		vScreen.y = (gScreenSize.iScreenHeight / 2) - ( 0.5 * ((worldToScreen[1][0] * vOrigin[0] + worldToScreen[1][1] * vOrigin[1] + worldToScreen[1][2] * vOrigin[2] + worldToScreen[1][3]) * fl1DBw) * gScreenSize.iScreenHeight + 0.5); //Get the Y dimension and push it in to the Vector.
		return true;
	}

	return false;
}

void CDrawManager::DrawCrosshair(int iValue)
{
	int m_iScreenWidth = gScreenSize.iScreenWidth;
	int m_iScreenHeight = gScreenSize.iScreenHeight;

	int x = m_iScreenWidth / 2;
	int y = m_iScreenHeight / 2;
	switch (iValue)
	{
	case 1:
		DrawRect(x - 14, y, 9, 1, Color(0, 255, 0, 255));
		DrawRect(x + 5, y, 9, 1, Color(0, 255, 255, 255));
		DrawRect(x, y - 14, 1, 9, Color(255, 0, 255, 255));
		DrawRect(x, y + 5, 1, 9, Color(0, 0, 255, 255));
		DrawRect(x, y, 1, 1, Color(255, 0, 0, 255));
	break;
	}

}

void CDrawManager::DrawCornerFaceBox(int x, int y, int w, int h, int cx, int cy, Color Col)
{
	gDraw.DrawLine(x, y, x + (w / cx), y, Col);
	gDraw.DrawLine(x, y, x, y + (h / cy), Col);

	gDraw.DrawLine(x + w, y, x + w - (w / cx), y, Col);
	gDraw.DrawLine(x + w, y, x + w, y + (h / cy), Col);

	gDraw.DrawLine(x, y + h, x + (w / cx), y + h, Col);
	gDraw.DrawLine(x, y + h, x, y + h - (h / cy), Col);

	gDraw.DrawLine(x + w, y + h, x + w - (w / cx), y + h, Col);
	gDraw.DrawLine(x + w, y + h, x + w, y + h - (h / cy), Col);
}

void CDrawManager::DrawCornerBox(int x, int y, int w, int h, int cx, int cy, Color Col)
{
	gDraw.DrawLine(x, y, x + (w / cx), y, Col);
	gDraw.DrawLine(x, y, x, y + (h / cy), Col);

	gDraw.DrawLine(x + w, y, x + w - (w / cx), y, Col);
	gDraw.DrawLine(x + w, y, x + w, y + (h / cy), Col);

	gDraw.DrawLine(x, y + h, x + (w / cx), y + h, Col);
	gDraw.DrawLine(x, y + h, x, y + h - (h / cy), Col);

	gDraw.DrawLine(x + w, y + h, x + w - (w / cx), y + h, Col);
	gDraw.DrawLine(x + w, y + h, x + w, y + h - (h / cy), Col);



}
