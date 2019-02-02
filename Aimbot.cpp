#include "Aimbot.h"
#include "Util.h"
#include "Panels.h"
#include "Backtrack.h"

CAimbot gAim;

mstudiobbox_t *CAimbot::get_studio_hitbox(int Hitbox, studiohdr_t* Header)
{
	int HitboxSetIndex = *(int *)((uintptr_t)Header + 0xB0);
	mstudiohitboxset_t *Set = (mstudiohitboxset_t *)(((uintptr_t)Header) + HitboxSetIndex);

	return (mstudiobbox_t *)Set->pHitbox(Hitbox);
}

void CAimbot::vec_transform(Vector &in1, const matrix3x4 &in2, Vector &out)
{
	out[0] = (in1[0] * in2[0][0] + in1[1] * in2[0][1] + in1[2] * in2[0][2]) + in2[0][3];
	out[1] = (in1[0] * in2[1][0] + in1[1] * in2[1][1] + in1[2] * in2[1][2]) + in2[1][3];
	out[2] = (in1[0] * in2[2][0] + in1[1] * in2[2][1] + in1[2] * in2[2][2]) + in2[2][3];
}



Vector CAimbot::get_hitbox(CBaseEntity *ent, int Hitbox)
{
	Vector TargetHitbox;

	if (ent == NULL || ent->GetIndex() == 0)
		return TargetHitbox;

	studiohdr_t* StudioHdr = gInts.ModelInfo->GetStudiomodel(ent->GetModel());

	matrix3x4 BoneToWorld[128];
	if (!ent->SetupBones(BoneToWorld, 128, 0x100, 0))
		return TargetHitbox;


	mstudiobbox_t *box = get_studio_hitbox(Hitbox, StudioHdr);

	Vector Min, Max;

	vec_transform(box->bbmin, BoneToWorld[box->bone], Min);
	vec_transform(box->bbmax, BoneToWorld[box->bone], Max);

	TargetHitbox = (Min + Max) / 2;

	return TargetHitbox;
}

Vector CAimbot::EstimateAbsVelocity(CBaseEntity* entity)
{
	typedef void(__thiscall * estimate_abs_velocity_fn)(CBaseEntity*, Vector &);
	static uintptr_t function = gSignatures.GetClientSignature("E8 ? ? ? ? F3 0F 10 4D ? 8D 85 ? ? ? ? F3 0F 10 45 ? F3 0F 59 C9 56 F3 0F 59 C0 F3 0F 58 C8 0F 2F 0D ? ? ? ? 76 07") + 0x1;
	static uintptr_t estimate = ((*(PDWORD)(function)) + function + 4);

	estimate_abs_velocity_fn vel = (estimate_abs_velocity_fn)estimate;
	Vector v; vel(entity, v); return v;
}

void CAimbot::Projectile(CBaseEntity* local_player, CBaseEntity* entity, CBaseCombatWeapon* local_weapon, Vector& vec_hitbox)
{
	auto item_index = local_weapon->GetItemDefinitionIndex();
	auto get_speed = [&local_player, &local_weapon, &entity, &item_index]() -> float {
		auto weapon_speed = 0.0f;
		switch (item_index) {
		case WPN_FestiveFlaregun:
		case WPN_Flaregun:
			weapon_speed = 2000.0f; break;
		case WPN_SyringeGun:
		case WPN_NewSyringeGun:
		case WPN_Blutsauger:
		case WPN_Overdose:
			weapon_speed = 1000.0f; break;
		case WPN_RescueRanger:
		case WPN_Crossbow:
		case WPN_FestiveCrossbow:
			weapon_speed = 2400.0f; break;
		case WPN_GrenadeLauncher:
		case WPN_NewGrenadeLauncher:
		case WPN_FestiveGrenadeLauncher:
			weapon_speed = 1216.6f; break;
		case WPN_LochNLoad:
			weapon_speed = 1513.3f; break;
		case WPN_LoooseCannon:
			weapon_speed = 1453.9f; break;
		case WPN_IronBomber:
			weapon_speed = 1216.6f; break;
		default: weapon_speed = 0.0f; break;
		}
		return weapon_speed;
	};
	auto get_gravity = [&local_player, &local_weapon, &entity, &item_index]() -> float {
		auto weapon_gravity = 0.0f;
		switch (item_index) {
		case WPN_RescueRanger:
		case WPN_Crossbow:
		case WPN_FestiveCrossbow:
			weapon_gravity = 0.2f; break;
		case WPN_GrenadeLauncher:
		case WPN_NewGrenadeLauncher:
		case WPN_FestiveGrenadeLauncher:
		case WPN_LoooseCannon:
		case WPN_LochNLoad:
		case WPN_IronBomber:
			weapon_gravity = 0.4f; break;
		default: weapon_gravity = 0.0f; break;
		}
		return weapon_gravity;
	};
	auto is_projectile_weapon = [&local_player, &local_weapon, &entity, &item_index]() -> bool {
		auto local_class = local_player->GetClassNum(), weapon_slot = local_weapon->GetSlot();
		if (local_class == TF2_Demoman || local_class == TF2_Medic) {
			if (weapon_slot == 0) {
				return true;
			}
		}

		if (local_class == TF2_Engineer) {
			if (weapon_slot == 0) {
				if (item_index == WPN_RescueRanger) {
					return true;
				}
			}
		}

		return false;
	};
	auto distance_to_ground = [&entity]() -> float {
		if (entity->GetFlags() & FL_ONGROUND) return 0.0f;
		auto distance_to_ground = [&entity](Vector origin) -> float
		{
			trace_t ground_trace; Ray_t ray;
			CTraceFilter filter; filter.pSkip = entity;
			Vector endpos = origin;

			endpos.z -= 8192;
			ray.Init(origin, endpos);
			gInts.EngineTrace->TraceRay(ray, MASK_PLAYERSOLID, &filter, &ground_trace);
			return 8192.0f * ground_trace.fraction;
		};

		Vector origin = entity->GetAbsOrigin();
		float v1 = distance_to_ground(origin + Vector(10.0f, 10.0f, 0.0f));
		float v2 = distance_to_ground(origin + Vector(-10.0f, 10.0f, 0.0f));
		float v3 = distance_to_ground(origin + Vector(10.0f, -10.0f, 0.0f));
		float v4 = distance_to_ground(origin + Vector(-10.0f, -10.0f, 0.0f));
		return min(v1, min(v2, min(v3, v4)));
	};
	if (is_projectile_weapon()) {
		bool on_ground = entity->GetFlags() & FL_ONGROUND;
		if (local_player->GetClassNum() == TF2_Medic || local_player->GetClassNum() == TF2_Engineer || local_player->GetClassNum() == TF2_Pyro)
			vec_hitbox = entity->GetHitboxPosition(4);
		else if (local_player->GetClassNum() == TF2_Soldier || local_player->GetClassNum() == TF2_Demoman) {
			vec_hitbox = entity->GetAbsOrigin();
			vec_hitbox[2] += 10.0f;
		}

		auto hitbox_pred = [&local_player, &entity, &on_ground](Vector hitbox, float speed, float gravity, float distance_to_ground) -> Vector {
			Vector result = hitbox, bestpos = result;

			auto vec_velocity = gAim.EstimateAbsVelocity(entity);
			auto medianTime = (local_player->GetEyePosition().DistTo(result) / speed), range = 1.5f,
				currenttime = medianTime - range;

			if (currenttime <= 0.0f) currenttime = 0.01f;

			auto besttime = currenttime, mindelta = 65536.0f; auto maxsteps = 300;
			for (int steps = 0; steps < maxsteps; steps++, currenttime += ((float)(2 * range) / (float)maxsteps)) {
				Vector curpos = result; curpos += vec_velocity * currenttime;

				if (distance_to_ground > 0.0f) {
					curpos.z -= currenttime * currenttime * 400.0f * ((entity->GetCond() & TFCondEx2_Parachute) ? 0.448f : 1.0f);
					if (curpos.z < result.z - distance_to_ground) {
						curpos.z = result.z - distance_to_ground;
					}
				}

				auto rockettime = (local_player->GetEyePosition().DistTo(curpos) / speed);
				if (fabs(rockettime - currenttime) < mindelta) {
					besttime = currenttime; bestpos = curpos;
					mindelta = fabs(rockettime - currenttime);
				}
			}
			bestpos.z += (400 * besttime * besttime * gravity);
			return bestpos;
		};

		vec_hitbox = hitbox_pred(vec_hitbox, get_speed(), get_gravity(), distance_to_ground());
	}
}

Vector CAimbot::GetHitbox(CBaseEntity* ent, int hitbox)
{
	DWORD* model = ent->GetModel();
	if (!model)
		return Vector();

	studiohdr_t* hdr = gInts.ModelInfo->GetStudiomodel(model);
	if (!hdr)
		return Vector();

	matrix3x4 matrix[128];
	if (!ent->SetupBones(matrix, 128, 0x100, gInts.globals->curtime))
		return Vector();

	mstudiohitboxset_t* set = hdr->GetHitboxSet(ent->GetHitboxSet());
	if (!set)
		return Vector();

	mstudiobbox_t* box = set->pHitbox(hitbox);
	if (!box)
		return Vector();

	Vector center = (box->bbmin + box->bbmax) * 0.5f;

	Vector hitboxpos;

	Util->VectorTransform(center, matrix[box->bone], hitboxpos);

	return hitboxpos;
}

float VectorialDistanceToGround(Vector origin)
{
	static trace_t* ground_trace = new trace_t();
	Ray_t ray;
	Vector endpos = origin;
	endpos.z -= 8192;
	ray.Init(origin, endpos);
	gInts.EngineTrace->TraceRay(ray, MASK_PLAYERSOLID, NULL, ground_trace);
	return 8192.0f * ground_trace->fraction;
}

Vector SimpleLatencyPrediction(CBaseEntity* ent, int hb)
{
	if (!ent) return Vector();
	Vector result;
	result = ent->GetHitboxPosition(hb);
	float latency = ((INetChannel*)gInts.Engine->GetNetChannelInfo())->GetLatency(FLOW_OUTGOING) +
		((INetChannel*)gInts.Engine->GetNetChannelInfo())->GetLatency(FLOW_INCOMING);
	Vector vel = Util->EstimateAbsVelocity(ent);
	result += vel * latency;
	return result;
}
float PlayerGravityMod(CBaseEntity* player)
{
	int movetype = player->GetMoveType();
	if (movetype == MOVETYPE_FLY || movetype == MOVETYPE_NOCLIP)
		return 0.0f;

	return 1.0f;
}
float CAimbot::DistanceToGround(CBaseEntity* ent)
{
	if (ent->GetFlags() & FL_ONGROUND) return 0;

	Vector& origin = ent->GetVecOrigin();
	float v1 = VectorialDistanceToGround(origin + Vector(10.0f, 10.0f, 0.0f));
	float v2 = VectorialDistanceToGround(origin + Vector(-10.0f, 10.0f, 0.0f));
	float v3 = VectorialDistanceToGround(origin + Vector(10.0f, -10.0f, 0.0f));
	float v4 = VectorialDistanceToGround(origin + Vector(-10.0f, -10.0f, 0.0f));
	return min(v1, min(v2, min(v3, v4)));
}

bool CanShoot(CBaseEntity* pLocal)
{
	return gInts.globals->curtime - pLocal->GetActiveWeapon()->m_flLastFireTime() >= 0.01;//1.0;
}

bool CAimbot::CanAmbassadorHeadshot(CBaseEntity* pLocal)
{
	return gInts.globals->curtime - pLocal->GetActiveWeapon()->m_flLastFireTime() >= 0.930;//1.0;
}

#include "CDrawManager.h"
bool isEntity = false;
void CAimbot::Run(CBaseEntity* pLocal, CUserCmd* pCommand)
{
	gCvars.iAimbotIndex = -1;

	if (!gCvars.aimbot_active) return;

	if (!pLocal->GetActiveWeapon()) return;

	auto id = pLocal->GetActiveWeapon()->GetItemDefinitionIndex();
	if (
#pragma region scout
		id == (int)scoutweapons::WPN_Sandman
		|| id == (int)scoutweapons::WPN_CritCola
		|| id == (int)scoutweapons::WPN_CritCola
		|| id == (int)scoutweapons::WPN_FlyingGuillotine1
		|| id == (int)scoutweapons::WPN_FlyingGuillotine2
		|| id == (int)scoutweapons::WPN_Milk
		|| id == (int)scoutweapons::WPN_MutatedMilk
		|| id == (int)scoutweapons::WPN_WrapAssassin
#pragma endregion
#pragma region soldier
		|| id == (int)soldierweapons::WPN_LibertyLauncher
#pragma endregion
#pragma region heavy
		|| id == (int)heavyweapons::WPN_FestiveSandvich
		|| id == (int)heavyweapons::WPN_RobotSandvich
		|| id == (int)heavyweapons::WPN_Sandvich
		|| id == (int)heavyweapons::WPN_Steak
		|| id == (int)heavyweapons::WPN_CandyBar
		|| id == (int)heavyweapons::WPN_Fishcake
#pragma endregion
#pragma region engineer
		|| id == (int)engineerweapons::WPN_Builder
		|| id == (int)engineerweapons::WPN_Builder2
		|| id == (int)engineerweapons::WPN_Destructor
		|| id == (int)engineerweapons::WPN_FestiveWrangler
		|| id == (int)engineerweapons::WPN_Pomson
		|| id == (int)engineerweapons::WPN_RescueRanger
		|| id == (int)engineerweapons::WPN_ShortCircut
		|| id == (int)engineerweapons::WPN_Toolbox
		|| id == (int)engineerweapons::WPN_Wrangler
#pragma endregion
#pragma region medic
		|| id == (int)medicweapons::WPN_Blutsauger
		|| id == (int)medicweapons::WPN_FestiveCrossbow
		|| id == (int)medicweapons::WPN_FestiveMedigun
		|| id == (int)medicweapons::WPN_Kritzkrieg
		|| id == (int)medicweapons::WPN_Medigun
		|| id == (int)medicweapons::WPN_Overdose
		|| id == (int)medicweapons::WPN_QuickFix
		|| id == (int)medicweapons::WPN_SyringeGun
		|| id == (int)medicweapons::WPN_Vaccinator

#pragma endregion
#pragma region sniper
		|| id == (int)sniperweapons::WPN_CompoundBow
		|| id == (int)sniperweapons::WPN_FestiveJarate
		|| id == (int)sniperweapons::WPN_FestiveHuntsman
		|| id == (int)sniperweapons::WPN_Huntsman
		|| id == (int)sniperweapons::WPN_Jarate
#pragma endregion
#pragma region spy
		|| id == (int)spyweapons::WPN_ApSap
		|| id == (int)spyweapons::WPN_DisguiseKit
		|| id == (int)spyweapons::WPN_RedTape1
		|| id == (int)spyweapons::WPN_RedTape2
		|| id == (int)spyweapons::WPN_Sapper
		|| id == (int)spyweapons::WPN_Sapper2
		|| id == (int)spyweapons::WPN_FestiveSapper
#pragma endregion
		)
		return;

	if (!Util->IsKeyPressed(gCvars.aimbot_key))
		return;


	CBaseEntity* pEntity = GetBaseEntity(GetBestTarget(pLocal, pCommand));

	if (!pEntity)
		return;

	if (pLocal->GetCond() & TFCond_Cloaked) return;

	if (!CanShoot(pLocal)) return;

	auto pWep = pLocal->GetActiveWeapon();
	if (gCvars.aimbot_waitforcharge)
		if (pWep->GetItemDefinitionIndex() == spyweapons::WPN_Ambassador || pWep->GetItemDefinitionIndex() == spyweapons::WPN_FestiveAmbassador)
			if (!CanAmbassadorHeadshot(pLocal)) return;

	int iBestHitbox = GetBestHitbox(pLocal, pEntity);

	if (iBestHitbox == -1)
		return;
	Vector vEntity = pEntity->GetHitboxPosition(iBestHitbox);

	Vector vLocal = pLocal->GetEyePosition();
	
	CBaseCombatWeapon* pWeapon = pLocal->GetActiveWeapon();

	Projectile(pLocal, pEntity, pWeapon, vEntity);
	auto pWeap = pLocal->GetActiveWeapon(); if (!pWeap) return;
	auto pSoldier = (pLocal->GetClassNum() == TF2_Soldier && pWeap->GetSlot() == 0);
	if (pSoldier)
	{
		
		bool ponGround = pEntity->GetFlags() & FL_ONGROUND;

		vEntity = pEntity->GetAbsOrigin(); vEntity[2] += 10.0f;

		auto projectile_speed = pWeap->GetItemDefinitionIndex() == WPN_DirectHit ? 1980.0f : 1100.0f;
		auto predicted_time = ((pLocal->GetEyePosition().DistTo(vEntity) / projectile_speed) + gInts.globals->interval_per_tick);

		Vector AbsVel = Util->EstimateAbsVelocity(pEntity);
		AbsVel[2] += -gInts.cvar->FindVar("sv_gravity")->GetFloat() * gInts.globals->interval_per_tick * gInts.globals->interval_per_tick;

		vEntity[0] += (AbsVel[0] * predicted_time) + gInts.globals->interval_per_tick;
		vEntity[1] += (AbsVel[1] * predicted_time) + gInts.globals->interval_per_tick;
		vEntity[2] += (ponGround ? (AbsVel[2] * predicted_time) + gInts.globals->interval_per_tick :
			(0.5 * pow(predicted_time, 2) + AbsVel[2] * predicted_time)) + gInts.globals->interval_per_tick;
	}



	//if (gCvars.backtrack) //Aims at backtrack ticks 8 and below, not really useful, will just improve accuracy slightly so not worth including in patch notes.
	//	for (int i = 0; i < gCvars.bt_ticks; i++)
	//		vEntity = headPositions[pEntity->GetIndex()][i].hitboxpos;
	//else
	//	vEntity = pEntity->GetHitboxPosition(iBestHitbox);


	Vector vAngs;
	VectorAngles((vEntity - vLocal), vAngs);

	ClampAngle(vAngs);

	gCvars.iAimbotIndex = pEntity->GetIndex();

	if (gCvars.aimbot_smooth > 0.0 && !gCvars.aimbot_silent)
	{
		Vector vDelta(pCommand->viewangles - vAngs);
		AngleNormalize(vDelta);
		vAngs = pCommand->viewangles - vDelta / gCvars.aimbot_smooth;
	}


	if (gCvars.aimbot_silent)
	{
		if (pCommand->buttons & IN_ATTACK)
		{
			w(true, vAngs, pCommand);
		}
		else if (gCvars.aimbot_autoshoot)
		{
			w(true, vAngs, pCommand);
			pCommand->buttons |= IN_ATTACK;
		}
		else
		{
			if (pCommand->buttons & IN_ATTACK)
				w(true, vAngs, pCommand);
		}
	}
	else
	{
		w(gCvars.aimbot_silent, vAngs, pCommand);
		if (gCvars.aimbot_autoshoot)
			pCommand->buttons |= IN_ATTACK;
	}

}

void CAimbot::w(bool silent, Vector vAngs, CUserCmd* pCommand)
{
	if (silent)
	{
		ClampAngle(vAngs);
		Util->SilentMovementFix(pCommand, vAngs);
		pCommand->viewangles = vAngs;

	}
	else
	{
		pCommand->viewangles = vAngs;
		gInts.Engine->SetViewAngles(pCommand->viewangles);
	}
}

float DistanceToGround(CBaseEntity* ent)
{
	if (ent->GetFlags() & FL_ONGROUND) return 0;

	Vector& origin = ent->GetVecOrigin();
	float v1 = VectorialDistanceToGround(origin + Vector(10.0f, 10.0f, 0.0f));
	float v2 = VectorialDistanceToGround(origin + Vector(-10.0f, 10.0f, 0.0f));
	float v3 = VectorialDistanceToGround(origin + Vector(10.0f, -10.0f, 0.0f));
	float v4 = VectorialDistanceToGround(origin + Vector(-10.0f, -10.0f, 0.0f));
	return min(v1, min(v2, min(v3, v4)));
}

int CAimbot::GetBestTarget(CBaseEntity* pLocal, CUserCmd* pCommand)
{
	int bestTarget = -1;
	float flDistToBest = 99999.0;
	float minimalDistance = 99999.0;

	Vector vLocal = pLocal->GetEyePosition();

	for (int i = 1; i <= gInts.Engine->GetMaxClients(); i++)
	{
		if (i == me)
			continue;

		CBaseEntity* pEntity = GetBaseEntity(i);

		if (!pEntity)
			continue;

		if (pEntity->IsDormant())
			continue;

		if (pEntity->GetLifeState() != LIFE_ALIVE ||
			pEntity->GetTeamNum() == pLocal->GetTeamNum())
			continue;

		int iBestHitbox = GetBestHitbox(pLocal, pEntity);

		if (iBestHitbox == -1)
			continue;

		Vector vEntity = pEntity->GetHitboxPosition(iBestHitbox);


		if (!gCvars.PlayerMode[i])
			continue;

		if (pEntity->GetCond() & TFCond_Ubercharged ||
			pEntity->GetCond() & TFCond_Bonked)
			continue;

		if (gCvars.aimbot_ignore_cloak
			&& (pEntity->GetCond() & TFCond_Cloaked))
			continue;

		auto pWep = pLocal->GetActiveWeapon();
		auto pClass = pWep->GetItemDefinitionIndex();
		auto demo = pClass == demomanweapons::WPN_Sword || pClass == demomanweapons::WPN_FestiveEyelander || pClass == demomanweapons::WPN_Golfclub || pClass == demomanweapons::WPN_ScottsSkullctter || pClass == demomanweapons::WPN_Headless;
		if (pWep->GetSlot() == 2 && !demo)
			minimalDistance = (float)8.4;

		if (pClass == demomanweapons::WPN_Sword || pClass == demomanweapons::WPN_FestiveEyelander || pClass == demomanweapons::WPN_Golfclub || pClass == demomanweapons::WPN_ScottsSkullctter || pClass == demomanweapons::WPN_Headless)
			minimalDistance = 12.0;

		if (pLocal->szGetClass() == "Pyro" && (pClass == pyroweapons::WPN_Backburner || pClass == pyroweapons::WPN_Degreaser || pClass == pyroweapons::WPN_FestiveBackburner || pClass == pyroweapons::WPN_FestiveFlamethrower || pClass == pyroweapons::WPN_Flamethrower || pClass == pyroweapons::WPN_Phlogistinator || pClass == pyroweapons::WPN_Rainblower || pClass == pyroweapons::WPN_NostromoNapalmer))
			minimalDistance = 17.0;

		float flFOV = GetFOV(pCommand->viewangles, vLocal, vEntity);
		float distance = Util->flGetDistance(vEntity, pLocal->GetEyePosition());

		if (distance < minimalDistance)
		{
			if (flFOV < flDistToBest && flFOV < gCvars.aimbot_fov)
			{
				if (gCvars.PlayerMode[i] == 2)
					return i;
				flDistToBest = flFOV;
				gCvars.iAimbotIndex = i;
				bestTarget = i;
			}
		}

	}

	return bestTarget;
}
Vector CAimbot::calc_angle(Vector src, Vector dst)
{
	Vector AimAngles, delta;
	float hyp;
	delta = src - dst;
	hyp = sqrtf((delta.x * delta.x) + (delta.y * delta.y));
	AimAngles.x = atanf(delta.z / hyp) * RADPI;
	AimAngles.y = atanf(delta.y / delta.x) * RADPI;
	AimAngles.z = 0.0f;
	if (delta.x >= 0.0)
		AimAngles.y += 180.0f;
	return AimAngles;
}
void CAimbot::MakeVector(Vector angle, Vector& vector)
{
	float pitch, yaw, tmp;
	pitch = float(angle[0] * PI / 180);
	yaw = float(angle[1] * PI / 180);
	tmp = float(cos(pitch));
	vector[0] = float(-tmp * -cos(yaw));
	vector[1] = float(sin(yaw)*tmp);
	vector[2] = float(-sin(pitch));
}

float CAimbot::GetFOV(Vector angle, Vector src, Vector dst)
{
	Vector ang, aim;
	float mag, u_dot_v;
	ang = calc_angle(src, dst);


	MakeVector(angle, aim);
	MakeVector(ang, ang);

	mag = sqrtf(pow(aim.x, 2) + pow(aim.y, 2) + pow(aim.z, 2));
	u_dot_v = aim.Dot(ang);

	return RAD2DEG(acos(u_dot_v / (pow(mag, 2))));
}

bool IsVisiblePoint(CBaseEntity* pLocal, Vector Point)
{
	trace_t tr; Ray_t ray; CTraceFilter filter;
	ray.Init(pLocal->GetEyePosition(), Point);
	gInts.EngineTrace->TraceRay(ray, MASK_SOLID, &filter, &tr);
	if (tr.fraction > 0.9f) return true;
	return false;
}

int CAimbot::GetBestHitbox(CBaseEntity* pLocal, CBaseEntity* pEntity)
{
	int iBestHitbox = -1;

	if (!pLocal->GetActiveWeapon()) return iBestHitbox;

	if (Util->IsHeadshotWeapon(pLocal, pLocal->GetActiveWeapon()))
		iBestHitbox = 0;
	else
		iBestHitbox = (int)tf_hitbox::pelvis;

	if (gCvars.aimbot_hitscan)
	{
		for (int i = 0; i < 17; i++)
		{
			if (Util->IsVisible(pLocal, pEntity, pLocal->GetEyePosition(), pEntity->GetHitboxPosition(i)))
				return i;
		}
	}

	if (pEntity->GetHitboxPosition(iBestHitbox).IsZero())
		return -1;

	if (!Util->IsVisible(pLocal, pEntity, pLocal->GetEyePosition(), pEntity->GetHitboxPosition(iBestHitbox)))
		return -1;

	return iBestHitbox;
}
