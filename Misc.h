#pragma once
#include "SDK.h"

class CMisc
{
public:

	void Run(CBaseEntity* pLocal, CUserCmd* pCommand);

private:
	float fLastTime, fLastSpam;
	//Other funcs

	void NoisemakerSpam(PVOID kv);
};

extern CMisc gMisc;