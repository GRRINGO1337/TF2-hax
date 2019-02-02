#pragma once
#define NOMINMAX

#include <Windows.h>
#include "singleton.h"

typedef unsigned long HFont;
class Font : public Singleton<Font>
{
public:
	HFont Overlay;
	HFont MenuText;
	HFont MenuTAB;
	HFont ESP;
	HFont Title;
	void Create();
};