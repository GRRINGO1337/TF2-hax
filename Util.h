#pragma once
#include "SDK.h"

class CUtil
{
public:
	void TrimStart(std::string & s);

	void VectorTransform(const Vector& vSome, const matrix3x4& vMatrix, Vector& vOut);

	float RandFloatRange(float min, float max);

	void ReplaceString(std::string & input, const std::string & what, const std::string & with_what);

	float flGetDistance(Vector vOrigin, Vector vLocalOrigin);

	bool IsVisible(void* pLocal, void* pEntity, Vector vStart, Vector vEnd);

	void NormaliseViewAngle(Vector &angle);

	bool IsKeyPressed(int i);

	bool IsKeyPressedString(const char * i);

	bool IsKeyDown(char * key);

	void SilentMovementFix(CUserCmd * pUserCmd, Vector angles);

	bool IsHeadshotWeapon(CBaseEntity* pLocal, CBaseCombatWeapon* pWep);

	bool IsReadyToHeadshot(CBaseCombatWeapon* pWep);

	bool IsBackstabWeapon(CBaseEntity* pLocal, CBaseCombatWeapon* pWep);

	bool IsReadyToBackstab(CBaseEntity* pLocal, CBaseCombatWeapon* pWep);

	void silentMovementFix(CUserCmd *pUserCmd, Vector angles);

	Vector EstimateAbsVelocity(CBaseEntity * ent);
	
	PVOID InitKeyValue();

	template<typename T, typename... Targs>
	void format_internal(std::stringstream& stream, T value, Targs... args)
	{
		stream << value;
		format_internal(stream, args...);
	}
	template<typename... Args>
	std::string format(const Args&... args)
	{
		std::stringstream stream;
		format_internal(stream, args...);
		return stream.str();
	}



};
extern CUtil* Util;