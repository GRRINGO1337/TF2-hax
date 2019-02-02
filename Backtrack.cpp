#include "Backtrack.h"

BacktrackData headPositions[24][12];

CBacktracking gBacktracking;

//=======================================================================
inline float distance_point_to_line(Vector Point, Vector LineOrigin, Vector Dir)
{
	auto PointDir = Point - LineOrigin;

	auto TempOffset = PointDir.Dot(Dir) / (Dir.x*Dir.x + Dir.y*Dir.y + Dir.z*Dir.z);
	if (TempOffset < 0.000001f)
		return FLT_MAX;

	auto PerpendicularPoint = LineOrigin + (Dir * TempOffset);

	return (Point - PerpendicularPoint).Length();
}

inline Vector angle_vector(Vector meme)
{
	auto sy = sin(meme.y / 180.f * static_cast<float>(PI));
	auto cy = cos(meme.y / 180.f * static_cast<float>(PI));

	auto sp = sin(meme.x / 180.f * static_cast<float>(PI));
	auto cp = cos(meme.x / 180.f* static_cast<float>(PI));

	return Vector(cp*cy, cp*sy, -sp);
}
//=======================================================================

void CBacktracking::Run(CUserCmd* cmd)
{
	int iBestTarget = -1;
	float bestFov = 99999;
	gCvars.backtrack_tick = 0;
	CBaseEntity* pLocal = gInts.EntList->GetClientEntity(me);

	if (!pLocal)
		return;
	if (!gCvars.backtrack)
		return;

	for (int i = 1; i <= gInts.Engine->GetMaxClients(); i++)
	{
		CBaseEntity* pEntity = GetBaseEntity(i);

		if (!pEntity)
			continue;
		if (pEntity->IsDormant())
			continue;
		if (pEntity->GetLifeState() != LIFE_ALIVE)
			continue;
		if (pEntity->GetTeamNum() == pLocal->GetTeamNum())
			continue;
		for (int b = 0; b <= 17; b++) {
			Vector hitboxpos = pEntity->GetHitboxPosition(b);
			headPositions[i][cmd->command_number % 13] = BacktrackData{ cmd->tick_count, hitboxpos };

			Vector ViewDir = angle_vector(cmd->viewangles);
			float FOVDistance = distance_point_to_line(hitboxpos, pLocal->GetEyePosition(), ViewDir);

			if (bestFov > FOVDistance)
			{
				bestFov = FOVDistance;
				iBestTarget = i;
			}

			if (iBestTarget != -1)
			{
				int bestTick = 0;
				float tempFOV = 9999;
				float bestFOV = 30;
				Vector lowestDistTicks(180, 180, 0);
				for (int t = 0; t < 12; ++t)
				{
					Vector ViewDir = angle_vector(cmd->viewangles);
					float tempFOV = distance_point_to_line(headPositions[iBestTarget][t].hitboxpos, pLocal->GetEyePosition(), ViewDir);
					if (bestFOV > tempFOV)
					{
						bestTick = t, bestFOV = tempFOV;
						gCvars.backtrack_tick = t;
					}
				}

				if (cmd->buttons & IN_ATTACK)
					cmd->tick_count = headPositions[i][bestTick].tickcount;
			}
		}
	}

}
