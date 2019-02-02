#pragma once
#include "SDK.h"
#include "Aimbot.h"

struct BacktrackData
{
	int tickcount;
	Vector hitboxpos;
};

class CBacktracking
{
public:
	void Run(CUserCmd* cmd);

private:

};

extern BacktrackData headPositions[24][12];
extern CBacktracking gBacktracking;
