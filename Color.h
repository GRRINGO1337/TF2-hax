//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================//


#define COLOR_H

#ifdef _WIN32
#pragma once
#endif

//-----------------------------------------------------------------------------
// Purpose: Basic handler for an rgb set of colors
//			This class is fully inline
//-----------------------------------------------------------------------------
class Color
{
public:
	// constructors
	Color()
	{
		*((int *)this) = 0;
	}
	Color(int _r, int _g, int _b, int _a = 255)
	{
		SetColor(_r, _g, _b, _a);
	}
	Color(int value, int _a = 255)
	{
		SetColor(value, value, value, _a);
	}

	// set the color
	// r - red component (0-255)
	// g - green component (0-255)
	// b - blue component (0-255)
	// a - alpha component, controls transparency (0 - transparent, 255 - opaque);
	void SetColor(int _r, int _g, int _b, int _a)
	{
		_color[0] = (unsigned char)_r;
		_color[1] = (unsigned char)_g;
		_color[2] = (unsigned char)_b;
		_color[3] = (unsigned char)_a;
	}

	void GetColor(int &_r, int &_g, int &_b, int &_a) const
	{
		_r = _color[0];
		_g = _color[1];
		_b = _color[2];
		_a = _color[3];
	}

	void SetRawColor(int color32)
	{
		*((int *)this) = color32;
	}

	int GetRawColor() const
	{
		return *((int *)this);
	}

	static Color White() { return Color(255, 255, 255, 255); }
	static Color Black() { return Color(0, 0, 0, 255); }
	static Color Red() { return Color(255, 0, 0, 255); }
	static Color Orange() { return Color(255, 165, 0, 255); }
	static Color Yellow() { return Color(255, 255, 0, 255); }
	static Color Green() { return Color(0, 255, 0, 255); }
	static Color Blue() { return Color(0, 0, 255, 255); }
	static Color Indigo() { return Color(75, 0, 130, 255); }
	static Color Violet() { return Color(128, 66, 244, 255); }
	static Color Rainbow()
	{
		static uint32_t cnt = 0;
		float freq = .01f;//00.

		Color color = Color(
			std::sin(freq*cnt + 0) * 127 + 128,
			std::sin(freq*cnt + 2) * 127 + 128,
			std::sin(freq*cnt + 4) * 127 + 128,
			255);

		// Probably redundant
		if (cnt++ >= (uint32_t)-1) cnt = 0;

		return color;
	}

	static Color RainbowMenu()
	{
		static uint32_t cnt = 0;
		float freq = .001f;//00.

		Color color = Color(
			std::sin(freq*cnt + 0) * 127 + 128,
			std::sin(freq*cnt + 2) * 127 + 128,
			std::sin(freq*cnt + 4) * 127 + 128,
			255);

		// Probably redundant
		if (cnt++ >= (uint32_t)-1) cnt = 0;

		return color;
	}

	inline int r() const { return _color[0]; }
	inline int g() const { return _color[1]; }
	inline int b() const { return _color[2]; }
	inline int a() const { return _color[3]; }

	unsigned char &operator[](int index)
	{
		return _color[index];
	}

	const unsigned char &operator[](int index) const
	{
		return _color[index];
	}

	bool operator == (const Color &rhs) const
	{
		return (*((int *)this) == *((int *)&rhs));
	}

	bool operator != (const Color &rhs) const
	{
		return !(operator==(rhs));
	}

	Color &operator=(const Color &rhs)
	{
		SetRawColor(rhs.GetRawColor());
		return *this;
	}

private:
	unsigned char _color[4];
};


class TColor
{
public:
	// constructors
	TColor()
	{
		*((int *)this) = 0;
	}
	TColor(int _r, int _g, int _b, int _a = 30)
	{
		SetTColor(_r, _g, _b, _a);
	}
	TColor(int value, int _a = 30)
	{
		SetTColor(value, value, value, _a);
	}

	// set the color
	// r - red component (0-255)
	// g - green component (0-255)
	// b - blue component (0-255)
	// a - alpha component, controls transparency (0 - transparent, 255 - opaque);
	void SetTColor(int _r, int _g, int _b, int _a = 30)
	{
		_color[0] = (unsigned char)_r;
		_color[1] = (unsigned char)_g;
		_color[2] = (unsigned char)_b;
		_color[3] = (unsigned char)_a;
	}

	void GetTColor(int &_r, int &_g, int &_b, int &_a) const
	{
		_r = _color[0];
		_g = _color[1];
		_b = _color[2];
		_a = _color[3];
	}

	void SetRawTColor(int color32)
	{
		*((int *)this) = color32;
	}

	int GetRawTColor() const
	{
		return *((int *)this);
	}

	static TColor White() { return TColor(255, 255, 255, 255); }
	static TColor Black() { return TColor(0, 0, 0, 255); }
	static TColor Red() { return TColor(255, 0, 0, 255); }
	static TColor Orange() { return TColor(255, 165, 0, 255); }
	static TColor Yellow() { return TColor(255, 255, 0, 255); }
	static TColor Green() { return TColor(0, 255, 0, 255); }
	static TColor Blue() { return TColor(0, 0, 255, 255); }
	static TColor Indigo() { return TColor(75, 0, 130, 255); }
	static TColor Violet() { return TColor(128, 66, 244, 255); }

	inline int r() const { return _color[0]; }
	inline int g() const { return _color[1]; }
	inline int b() const { return _color[2]; }
	inline int a() const { return _color[3]; }

	unsigned char &operator[](int index)
	{
		return _color[index];
	}

	const unsigned char &operator[](int index) const
	{
		return _color[index];
	}

	bool operator == (const TColor &rhs) const
	{
		return (*((int *)this) == *((int *)&rhs));
	}

	bool operator != (const TColor &rhs) const
	{
		return !(operator==(rhs));
	}

	TColor &operator=(const TColor &rhs)
	{
		SetRawTColor(rhs.GetRawTColor());
		return *this;
	}

private:
	unsigned char _color[4];
};


class SColor
{
public:
	byte rgba[4];

	inline byte& operator[](int i)
	{
		return rgba[i];
	}
	inline bool operator==(SColor& other)
	{
		return *(size_t*)&rgba == *(size_t*)&other.rgba;
	}
	inline bool operator!=(SColor& other)
	{
		return *(size_t*)&rgba != *(size_t*)&other.rgba;
	}

	SColor(byte red, byte green, byte blue, byte alpha = 255)
	{
		rgba[0] = red, rgba[1] = green, rgba[2] = blue, rgba[3] = alpha;
	}
	SColor(byte bright, byte alpha = 255)
	{
		rgba[0] = bright, rgba[1] = bright, rgba[2] = bright, rgba[3] = alpha;
	}
	SColor() {}
};

SColor hsv2rgb(float hue, float saturation, float brightness, int alpha = 255);