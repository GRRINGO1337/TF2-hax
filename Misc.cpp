#include "Misc.h"
#include "Util.h"
#include "CDrawManager.h"

CMisc gMisc;

void CMisc::Run(CBaseEntity* pLocal, CUserCmd* pCommand)
{
	static ConVar* viewmodel_fov = gInts.cvar->FindVar("viewmodel_fov");
	viewmodel_fov->SetValue(gCvars.misc_viewmodel_fov);
	//pLocal->setfov(gCvars.misc_fov); // im gonna keep this code here because its funny and cute - plasma
	
	if (gCvars.misc_no_push)
	{
		static ConVar* tf_avoidteammates_pushaway = gInts.cvar->FindVar("tf_avoidteammates_pushaway");
		if (tf_avoidteammates_pushaway->GetInt() == 1)
			tf_avoidteammates_pushaway->SetValue(0);
	}

	if (!(pLocal->GetFlags() & FL_ONGROUND) && pCommand->buttons & IN_JUMP)
	{
		if (gCvars.misc_autostrafe)
			if (pCommand->mousedx > 1 || pCommand->mousedx < -1)  //> 1 < -1 so we have some wiggle room
				pCommand->sidemove = pCommand->mousedx > 1 ? 450.f : -450.f;

		
		if (gCvars.misc_bunnyhop && pLocal->GetClassNum() != TF2_Scout )
			pCommand->buttons &= ~IN_JUMP;
	}

	if (gCvars.misc_autobackstab && pLocal->GetActiveWeapon() && Util->IsReadyToBackstab(pLocal, pLocal->GetActiveWeapon()))
		pCommand->buttons |= IN_ATTACK;

	if (gCvars.misc_noisemaker_spam)
	{
		PVOID kv = Util->InitKeyValue();
		if (kv != NULL)
		{
			NoisemakerSpam(kv);
			gInts.Engine->ServerCmdKeyValues(kv);
		}
	}
	
	if (gCvars.misc_roll_speedhack && !(pCommand->buttons & IN_ATTACK) && (pCommand->buttons & IN_DUCK)) // who changed my comment >:(
	{
		Vector vLocalAngles = pCommand->viewangles;
		float speed = pCommand->forwardmove;
		if (fabs(speed) > 0.0f) {
			pCommand->forwardmove = -speed;
			pCommand->sidemove = 0.0f;
			pCommand->viewangles.y = vLocalAngles.y;
			pCommand->viewangles.y -= 180.0f;
			if (pCommand->viewangles.y < -180.0f) pCommand->viewangles.y += 360.0f;
			pCommand->viewangles.z = 90.0f;
		}
	}
}

void CMisc::NoisemakerSpam(PVOID kv) //Credits gir https://www.unknowncheats.me/forum/team-fortress-2-a/141108-infinite-noisemakers.html
{
	char chCommand[30] = "use_action_slot_item_server";
	typedef int(__cdecl* HashFunc_t)(const char*, bool);
	static DWORD dwHashFunctionLocation = gSignatures.GetClientSignature("FF 15 ? ? ? ? 83 C4 08 89 06 8B C6");
	static HashFunc_t s_pfGetSymbolForString = (HashFunc_t)**(PDWORD*)(dwHashFunctionLocation + 0x2);
	*(PDWORD)((DWORD)kv + 0x4) = 0;
	*(PDWORD)((DWORD)kv + 0x8) = 0;
	*(PDWORD)((DWORD)kv + 0xC) = 0;
	*(PDWORD)((DWORD)kv + 0x10) = 0xDEADBEEF;
	*(PDWORD)((DWORD)kv + 0x14) = 0;
	*(PDWORD)((DWORD)kv + 0x18) = 0;
	*(PDWORD)((DWORD)kv + 0x1C) = 0;
	*(PDWORD)((DWORD)kv + 0) = s_pfGetSymbolForString(chCommand, 1);
}