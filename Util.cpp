#include "Util.h"
#include <algorithm>
#include <ctype.h>

CUtil* Util;



void CUtil::VectorTransform(const Vector& vSome, const matrix3x4& vMatrix, Vector& vOut)
{
	for (auto i = 0; i < 3; i++)
		vOut[i] = vSome.Dot((Vector&)vMatrix[i]) + vMatrix[i][3];
}

float CUtil::RandFloatRange(float min, float max)
{
	return (min + 1) + (((float)rand()) / (float)RAND_MAX) * (max - (min + 1));
}

void CUtil::ReplaceString(std::string& input, const std::string& what, const std::string& with_what)
{
	size_t index;
	index = input.find(what);
	while (index != std::string::npos)
	{
		input.replace(index, what.size(), with_what);
		index = input.find(what, index + with_what.size());
	}
}

void CUtil::TrimStart(std::string &s)
{
	s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch)
	{
		return (ch);
	}));
}

Vector CUtil::EstimateAbsVelocity(CBaseEntity *ent)
{
	typedef void(__thiscall * EstimateAbsVelocityFn)(CBaseEntity *, Vector &);



	static DWORD dwFn = gSignatures.GetClientSignature("E8 ? ? ? ? F3 0F 10 4D ? 8D 85 ? ? ? ? F3 0F 10 45 ? F3 0F 59 C9 56 F3 0F 59 C0 F3 0F 58 C8 0F 2F 0D ? ? ? ? 76 07") + 0x1;

	static DWORD dwEstimate = ((*(PDWORD)(dwFn)) + dwFn + 4);

	EstimateAbsVelocityFn vel = (EstimateAbsVelocityFn)dwEstimate;

	Vector v;

	vel(ent, v);

	return v;
}

float CUtil::flGetDistance(Vector vOrigin, Vector vLocalOrigin)
{
	Vector vDelta = vOrigin - vLocalOrigin;

	float m_fDistance = sqrt(vDelta.Length());

	if (m_fDistance < 1.0f)
		return 1.0f;

	return m_fDistance;
}

bool CUtil::IsVisible(void* pLocal, void* pEntity, Vector vStart, Vector vEnd)
{
	trace_t Trace;
	Ray_t Ray;			 // the future of variable naming
	CTraceFilter Filter;

	Filter.pSkip = pLocal;

	Ray.Init(vStart, vEnd);

	gInts.EngineTrace->TraceRay(Ray, MASK_SHOT, &Filter, &Trace);

	return (Trace.m_pEnt == pEntity);
}
void CUtil::NormaliseViewAngle(Vector &angle)
{
	while (angle.y <= -180) angle.y += 360;
	while (angle.y > 180) angle.y -= 360;
	while (angle.x <= -180) angle.x += 360;
	while (angle.x > 180) angle.x -= 360;


	if (angle.x > 89) angle.x = 89;
	if (angle.x < -89) angle.x = -89;
	if (angle.y < -180) angle.y = -179.999;
	if (angle.y > 180) angle.y = 179.999;

	angle.z = 0;
}
void CUtil::silentMovementFix(CUserCmd *pUserCmd, Vector angles) //Fix for silent movement    creds gir + f1ssi0n
{
	Vector vecSilent(pUserCmd->forwardmove, pUserCmd->sidemove, pUserCmd->upmove);
	float flSpeed = sqrt(vecSilent.x * vecSilent.x + vecSilent.y * vecSilent.y);
	Vector angMove;
	VectorAngles(vecSilent, angMove);
	float flYaw = DEG2RAD(angles.y - pUserCmd->viewangles.y + angMove.y);
	pUserCmd->forwardmove = cos(flYaw) * flSpeed;
	pUserCmd->sidemove = sin(flYaw) * flSpeed;
}
bool CUtil::IsKeyPressed(int i)
{
	switch (i)
	{
	case 0: //None
		return true;
	case 1: //Mouse 1
		return GetAsyncKeyState(VK_LBUTTON);
	case 2:
		return GetAsyncKeyState(VK_RBUTTON);
	case 3:										  //Mouses 1-5
		return GetAsyncKeyState(VK_MBUTTON);
	case 4:
		return GetAsyncKeyState(VK_XBUTTON1);
	case 5:
		return GetAsyncKeyState(VK_XBUTTON2);
	case 6: //Shift
		return GetAsyncKeyState(VK_SHIFT);
	case 7: //Alt
		return GetAsyncKeyState(VK_MENU);
	case 8: //F
		return GetAsyncKeyState(0x46);
	default:
		return false;
	}

	return false;
}

bool CUtil::IsKeyPressedString(const char* i)
{
	if (i == "Always")
		return true;
	if (i == "Mouse 1")
		return GetAsyncKeyState(VK_LBUTTON);
	if (i == "Mouse 2")
		return GetAsyncKeyState(VK_RBUTTON);
	if (i == "Mouse 3")
		return GetAsyncKeyState(VK_MBUTTON);
	if (i == "Mouse 4")
		return GetAsyncKeyState(VK_XBUTTON1);
	if (i == "Mouse 5")
		return GetAsyncKeyState(VK_XBUTTON2);
	if (i == "Shift")
		return GetAsyncKeyState(VK_SHIFT);
	if (i == "Alt")
		return GetAsyncKeyState(VK_MENU);
	if (i == "F")
		return GetAsyncKeyState(0x46);

		return false;
}

bool CUtil::IsKeyDown(char* key)
{
	if (strlen(key) < 1) return true;

	return gInts.InputSys->IsButtonDown(gInts.InputSys->StringToButtonCode(key));
}

void CUtil::SilentMovementFix(CUserCmd *pUserCmd, Vector angles)
{
	Vector vecSilent(pUserCmd->forwardmove, pUserCmd->sidemove, pUserCmd->upmove);
	float flSpeed = sqrt(vecSilent.x * vecSilent.x + vecSilent.y * vecSilent.y);
	Vector angMove;
	VectorAngles(vecSilent, angMove);
	float flYaw = DEG2RAD(angles.y - pUserCmd->viewangles.y + angMove.y);
	pUserCmd->forwardmove = cos(flYaw) * flSpeed;
	pUserCmd->sidemove = sin(flYaw) * flSpeed;
	pUserCmd->viewangles = angles;
}

bool CUtil::IsHeadshotWeapon(CBaseEntity* pLocal, CBaseCombatWeapon* pWep)
{
	if (pWep->GetSlot() == 0 && pLocal->GetClassNum() == TF2_Sniper)
		if (pWep->GetItemDefinitionIndex() != WPN_Huntsman && pWep->GetItemDefinitionIndex() != WPN_CompoundBow)
			return true;

	if (pWep->GetItemDefinitionIndex() == WPN_Ambassador || pWep->GetItemDefinitionIndex() == WPN_FestiveAmbassador)
		return true;

	return false;
}

bool CUtil::IsReadyToHeadshot(CBaseCombatWeapon* pWep)
{
	if (pWep->ChargedDamage() >= 15.f)
		return true;

	return false;
}

bool CUtil::IsBackstabWeapon(CBaseEntity* pLocal, CBaseCombatWeapon* pWep)
{
	if (pWep->GetSlot() == 2 && pLocal->GetClassNum() == TF2_Spy)
		return true;

	return false;
}

bool CUtil::IsReadyToBackstab(CBaseEntity* pLocal, CBaseCombatWeapon* pWep)
{
	return Util->IsBackstabWeapon(pLocal, pLocal->GetActiveWeapon()) && pWep->ReadyToBackstab();
}

PVOID CUtil::InitKeyValue() //Credits f1ssion
{
	typedef PDWORD(__cdecl* Init_t)(int);
	static DWORD dwInitLocation = gSignatures.GetClientSignature("E8 ? ? ? ? 83 C4 14 85 C0 74 10 68") + 0x1;
	static DWORD dwInit = ((*(PDWORD)(dwInitLocation)) + dwInitLocation + 4);
	static Init_t InitKeyValues = (Init_t)dwInit;
	return InitKeyValues(32);
}