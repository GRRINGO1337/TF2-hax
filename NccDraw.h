#include <Windows.h>
#include "Vector2.h"
#include "Font.h"

namespace Draw
{
	inline void Line(int x0, int y0, int x1, int y1, Color col)
	{
		gInts.Surface->DrawSetColor(col[0], col[1], col[2], col[3]);
		gInts.Surface->DrawLine(x0, y0, x1, y1);
	}

	inline void Line(Vector2 start_pos, Vector2 end_pos, Color col)
	{
		Line(start_pos.x, start_pos.y, end_pos.x, end_pos.y, col);
	}

	inline void Circle(Vector2 position, float points, float radius, Color color)
	{
		float step = (float)PI * 2.0f / points;

		for (float a = 0; a < (PI * 2.0f); a += step)
		{
			Vector2 start(radius * cosf(a) + position.x, radius * sinf(a) + position.y);
			Vector2 end(radius * cosf(a + step) + position.x, radius * sinf(a + step) + position.y);
			Line(start, end, color);
		}
	}

	inline void Circle(int x, int y, float points, float radius, Color color)
	{
		Circle(Vector2(x, y), points, radius, color);
	}

	inline void FilledRectangle(int x0, int y0, int x1, int y1, Color col)
	{
		gInts.Surface->DrawSetColor(col[0], col[1], col[2], col[3]);
		gInts.Surface->DrawFilledRect(x0, y0, x1, y1);
	}

	inline void FilledRectangle(Vector2 start_pos, Vector2 end_pos, Color col)
	{
		FilledRectangle(start_pos.x, start_pos.y, end_pos.x, end_pos.y, col);
	}

	inline void Rectangle(int x0, int y0, int x1, int y1, Color col)
	{
		gInts.Surface->DrawSetColor(col[0], col[1], col[2], col[3]);
		gInts.Surface->DrawOutlinedRect(x0, y0, x1, y1);
	}

	inline void Rectangle(Vector2 start_pos, Vector2 end_pos, Color col)
	{
		Rectangle(start_pos.x, start_pos.y, end_pos.x, end_pos.y, col);
	}

	inline void FilledGradientRectangle(int x0, int y0, int x1, int y1, Color top, Color bottom)
	{
		gInts.Surface->DrawSetColor(top[0], top[1], top[2], top[3]);
		gInts.Surface->DrawFilledRectFade(x0, y0, x1, y1, 255, 255, false);

		gInts.Surface->DrawSetColor(bottom[0], bottom[1], bottom[2], bottom[3]);
		gInts.Surface->DrawFilledRectFade(x0, y0, x1, y1, 0, 255, false);
	}

	inline void FilledGradientRectangle(Vector2 pos, Vector2 size, Color top, Color bottom)
	{
		FilledGradientRectangle(pos.x, pos.y, pos.x + size.x, pos.y + size.y, top, bottom);
	}

	inline void Text(int x, int y, const wchar_t* text, HFont font, Color color, bool centeredx, bool centeredy)
	{
		if (centeredx || centeredy)
		{
			int wide, tall;
			gInts.Surface->GetTextSize(font, text, wide, tall);
			if (centeredx)
				x -= wide / 2;
			if (centeredy)
				y -= tall / 2;
		}

		gInts.Surface->DrawSetTextPos(x, y);
		gInts.Surface->DrawSetTextFont(font);
		gInts.Surface->DrawSetTextColor(color[0], color[1], color[2], color[3]);
		gInts.Surface->DrawPrintText(text, wcslen(text));
	}

	inline void Text(int x, int y, const wchar_t* text, HFont font, Color color, bool centered = false)
	{
		Text(x, y, text, font, color, centered, centered);
	}

	inline Vector2 GetTextSize(const wchar_t* text, HFont font)
	{
		int x_res, y_res;
		gInts.Surface->GetTextSize(font, text, x_res, y_res);
		return Vector2(x_res, y_res);
	}
}