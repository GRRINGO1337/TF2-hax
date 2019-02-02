#include "AntiAim.h"
#include "Util.h"

CAA gAA;
float c_yaw = 0.0f;

float edgeDistance(float edgeRayYaw)
{
	trace_t trace;
	Ray_t ray;
	Vector forward;
	float sp, sy, cp, cy;
	sy = sinf(DEG2RAD(edgeRayYaw)); // yaw
	cy = cosf(DEG2RAD(edgeRayYaw));
	sp = sinf(DEG2RAD(0)); // pitch
	cp = cosf(DEG2RAD(0));
	forward.x = cp * cy;
	forward.y = cp * sy;
	forward.z = -sp;
	forward = forward * 300.0f + GetBaseEntity(me)->GetEyePosition();
	ray.Init(GetBaseEntity(me)->GetEyePosition(), forward);
	gInts.EngineTrace->TraceRay(ray, 0x4200400B, NULL, &trace);
	float edgeDistance = (sqrt(pow(trace.startpos.x - trace.endpos.x, 2) + pow(trace.startpos.y - trace.endpos.y, 2)));
	return edgeDistance;
}
float edgeYaw = 0;
float edgeToEdgeOn = 0;
bool findEdge(float edgeOrigYaw, int pitch_mode)
{
	float edgeLeftDist = edgeDistance(edgeOrigYaw - 21);
	edgeLeftDist = edgeLeftDist + edgeDistance(edgeOrigYaw - 27);
	float edgeRightDist = edgeDistance(edgeOrigYaw + 21);
	edgeRightDist = edgeRightDist + edgeDistance(edgeOrigYaw + 27);

	if (edgeLeftDist >= 260) edgeLeftDist = 999999999;
	if (edgeRightDist >= 260) edgeRightDist = 999999999;

	if (edgeLeftDist == edgeRightDist) return false;

	if (edgeRightDist < edgeLeftDist)
	{
		edgeToEdgeOn = 1;
		if (((int)pitch_mode == 1) || ((int)pitch_mode == 3)) edgeToEdgeOn = 2;
		return true;
	}
	else
	{
		edgeToEdgeOn = 2;
		if (((int)pitch_mode == 1) | ((int)pitch_mode == 3)) edgeToEdgeOn = 1;
		return true;
	}
}
float useEdge(float edgeViewAngle)
{
	bool edgeTest = true;
	if (((edgeViewAngle < -135) || (edgeViewAngle > 135)) && edgeTest == true)
	{
		if (edgeToEdgeOn == 1) edgeYaw = (float)-90;
		if (edgeToEdgeOn == 2) edgeYaw = (float)90;
		edgeTest = false;
	}
	if ((edgeViewAngle >= -135) && (edgeViewAngle < -45) && edgeTest == true)
	{
		if (edgeToEdgeOn == 1) edgeYaw = (float)0;
		if (edgeToEdgeOn == 2) edgeYaw = (float)179;
		edgeTest = false;
	}
	if ((edgeViewAngle >= -45) && (edgeViewAngle < 45) && edgeTest == true)
	{
		if (edgeToEdgeOn == 1) edgeYaw = (float)90;
		if (edgeToEdgeOn == 2) edgeYaw = (float)-90;
		edgeTest = false;
	}
	if ((edgeViewAngle <= 135) && (edgeViewAngle >= 45) && edgeTest == true)
	{
		if (edgeToEdgeOn == 1) edgeYaw = (float)179;
		if (edgeToEdgeOn == 2) edgeYaw = (float)0;
		edgeTest = false;
	}
	return edgeYaw;
}

void CorrectMovement(Vector vOldAngles, CUserCmd* pCmd, float fOldForward, float fOldSidemove) //you guys know that the aa movement fix is the same as silent movement fix, right? :thinking:
{
	float deltaView;
	float f1;
	float f2;

	if (vOldAngles.y < 0.f)
		f1 = 360.0f + vOldAngles.y;
	else
		f1 = vOldAngles.y;

	if (pCmd->viewangles.y < 0.0f)
		f2 = 360.0f + pCmd->viewangles.y;
	else
		f2 = pCmd->viewangles.y;

	if (f2 < f1)
		deltaView = abs(f2 - f1);
	else
		deltaView = 360.0f - abs(f1 - f2);

	deltaView = 360.0f - deltaView;

	pCmd->forwardmove = cos(DEG2RAD(deltaView)) * fOldForward + cos(DEG2RAD(deltaView + 90.f)) * fOldSidemove;
	pCmd->sidemove = sin(DEG2RAD(deltaView)) * fOldForward + sin(DEG2RAD(deltaView + 90.f)) * fOldSidemove;
}
bool CanShooter(CBaseEntity* pLocal)
{
	return gInts.globals->curtime - pLocal->GetActiveWeapon()->m_flLastFireTime() >= 0.01;//1.0;
}
void CAA::Run(CBaseEntity * pLocal, CUserCmd * pCommand, bool bSendPacket)
{
	Vector angles = pCommand->viewangles;

	if (!gCvars.aa_enabled)
		return;

	if (pLocal->GetHealth() < 1)
		return;

	/*if ((pCommand->buttons & IN_ATTACK))*/
	if (!CanShooter(pLocal))
		return;

	if (gCvars.aa_pitch_enabled) {
		switch ((int)gCvars.aa_pitch)
		{
		case 1://Fake up
			angles.x = -271.0;
			break;
		case 2://Up
			angles.x = -89.0f;
			break;
		case 3://Fake down
			angles.x = 271.0;
			break;
		case 4://Down
			angles.x = 89.0f;
			break;
		default:
			break;
		}
	}

	if (gCvars.fakeYAW)
	{
		switch ((int)gCvars.aa_fake_yaw)
		{
			if (bSendPacket) {
		case 1: {


			int ffps = rand() % 100;
			bool jitter = false;
			jitter = !jitter;

			switch (ffps)
			{
			case 1: angles.y -= rand() % 360; break;
			case 2: {
				if (jitter)
					angles.y -= 90;
				else
					angles.y += 90;
			}break;
			}
		}break;
		case 2: {
			c_yaw += gCvars.aa_spinspeed;
			if (c_yaw > 180) c_yaw = -180;
			if (c_yaw < -180) c_yaw = 180;
			angles.y = c_yaw;
		}break;

			}
		}
	}
	bool flick = false;
		
	if (!Util->IsKeyPressed(gCvars.aa_key))
		flick = true;
	else
		flick = false;

	
	if (gCvars.aa_yaw_enabled) {
		switch ((int)gCvars.aa_yaw)
		{
		case 1://Right
		{	

			angles.y += 180 + ((rand() % 35) - (35 * 0.5f));
		
						
		}break;
		case 2://Left
		{
			if (flick)
			{
				angles.y += 70 + ((rand() % 35) - (35 * 0.5f));
			}
			else
			{
				angles.y -= 70 + ((rand() % 35) - (35 * 0.5f));
			}
		}break;
		case 3://Back
			angles.y -= 180;
			break;
		case 4://Random
			angles.y = Util->RandFloatRange(-180.0f, 180.0f);
			break;
		case 5://Spin
			c_yaw += gCvars.aa_spinspeed;
			if (c_yaw > 180) c_yaw = -180;
			if (c_yaw < -180) c_yaw = 180;
			angles.y = c_yaw;
			break;
		case 6://Edge
			if (findEdge(angles.y, gCvars.aa_pitch_enabled)) angles.y = useEdge(angles.y);
			break;
		case 7://FSideways
			angles.y = pCommand->tick_count * 180 % 360;
			break;
		default:
			break;
		}
	}
	Util->SilentMovementFix(pCommand, angles);
	pCommand->viewangles = angles;
}

