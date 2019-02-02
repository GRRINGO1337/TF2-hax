#pragma once
#include "SDK.h"
#include "SDK.h"
#include "Aimbot.h"
#include "Backtrack.h"
#define BONE_USED_BY_HITBOX			0x00000100
struct Box
{
	int x = -1, y = -1, w = -1, h = -1;
};

class CESP
{
public:
	void Run(CBaseEntity* pLocal);

private:
	void Player_ESP(CBaseEntity* pLocal, CBaseEntity* pEntity);
	void DrawFace(CBaseEntity * pEntity, Color clr);
	float flGetDistance(Vector vOrigin, Vector vLocalOrigin);
	void SetupBounds(CBaseEntity* pEntity, int& x, int& y, int& w, int& h);
	void Skeleton(CBaseEntity* pLocal, CBaseEntity* pEntity);
	//Other funcs
	void boxas(CBaseEntity* pEntity, Color clrColor);
	void DrawBone(CBaseEntity* pEntity, int* iBones, int count, Color clrCol);
	void DrawHead(CBaseEntity* pEntity, int* iBones, int count, Color clrCol);
}; 

extern CESP gESP; 
