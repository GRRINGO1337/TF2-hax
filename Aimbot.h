#pragma once
#include "SDK.h"

class CAimbot
{
public:

	mstudiobbox_t * get_studio_hitbox(int Hitbox, studiohdr_t * Header);

	void vec_transform(Vector & in1, const matrix3x4 & in2, Vector & out);

	Vector get_hitbox(CBaseEntity * ent, int Hitbox);

	Vector GetHitbox(CBaseEntity * ent, int hitbox);

	float DistanceToGround(CBaseEntity * ent);

	bool CanAmbassadorHeadshot(CBaseEntity * pLocal);

	Vector EstimateAbsVelocity(CBaseEntity* entity);

	void Projectile(CBaseEntity* local_player, CBaseEntity* entity, CBaseCombatWeapon* local_weapon, Vector& vec_hitbox);

	void Run(CBaseEntity* pLocal, CUserCmd* pCommand);

	void w(bool silent, Vector vAngs, CUserCmd * pCommand);

	float GetFOV(Vector angle, Vector src, Vector dst);
	int GetBestHitbox(CBaseEntity* pLocal, CBaseEntity* pEntity);


private:
	int GetBestTarget(CBaseEntity * pLocal, CUserCmd * pCommand);

	Vector calc_angle(Vector src, Vector dst);

	void MakeVector(Vector angle, Vector & vector);



};

extern CAimbot gAim;