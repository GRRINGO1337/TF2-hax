#include "Triggerbot.h"
#include "Util.h"

CTriggerbot gTrigger;

void CTriggerbot::Run(CBaseEntity* pLocal, CUserCmd* pCommand)
{
	if (!gCvars.triggerbot_active)
		return;

	if (!Util->IsKeyPressed(gCvars.triggerbot_key))
		return;

	Vector vAim;
	gInts.Engine->GetViewAngles(vAim); //We use getviewangles so that this can work with anti-aim when it gets added

	Vector vForward;
	AngleVectors(vAim, &vForward);
				//How far we wanna look forward, lower this value if needed
	vForward = vForward * 9999 + pLocal->GetEyePosition();

	Ray_t ray;
	trace_t trace;
	CTraceFilter filt;

	filt.pSkip = pLocal;

	ray.Init(pLocal->GetEyePosition(), vForward);
	gInts.EngineTrace->TraceRay(ray, 0x46004003, &filt, &trace);

	if (!trace.m_pEnt)
		return;

	if (trace.hitgroup < 1)
		return;

	if (trace.m_pEnt->GetTeamNum() == pLocal->GetTeamNum())
		return;

	if (!gCvars.PlayerMode[trace.m_pEnt->GetIndex()])
		return;

	if (trace.m_pEnt->GetCond() & TFCond_Ubercharged ||
		trace.m_pEnt->GetCond() & TFCond_UberchargeFading ||
		trace.m_pEnt->GetCond() & TFCond_Bonked)
		return;

	if (gCvars.triggerbot_headonly && trace.hitbox != 0)
		return;

	pCommand->buttons |= IN_ATTACK;
}