
#include "ESP.h"
#include "CDrawManager.h"
#include "Util.h"
#include "Radar.h"
#define FastSqrt(x)	::sqrtf(x)
CESP gESP;
Box box;



void drawAimbotSnap(CBaseEntity* pEntity, CBaseEntity* pPlayer)
{
	
	Vector angles = pEntity->GetAngles();
	Vector eyepos = pEntity->GetEyePosition();

	Vector screenEyepos, screenForward;	

	int m_iScreenWidth = gScreenSize.iScreenWidth;
	int m_iScreenHeight = gScreenSize.iScreenHeight;

	int x = m_iScreenWidth / 2;
	int y = m_iScreenHeight / 2;

	if (pPlayer->GetIndex() == gCvars.iAimbotIndex)
	{
		if (gDraw.WorldToScreen(eyepos, screenEyepos))
		{
			gDraw.DrawLine(x, y, screenEyepos.x, screenEyepos.y, Color::Yellow());
		}
	}
}


void drawSnaplines(CBaseEntity* pEntity, CBaseEntity* pLocal)
{
	Color clrPlayerCol = gDraw.GetPlayerColor(pLocal, pEntity);

	if (gCvars.esp_snaplines == 0)
	{
		//Do nothing
	}
	else if (gCvars.esp_snaplines == 1)
	{
		Vector angles = pEntity->GetAngles();
		Vector eyepos = pEntity->GetAbsOrigin();

		Vector screenEyepos;



		int m_iScreenWidth = gScreenSize.iScreenWidth;
		int m_iScreenHeight = gScreenSize.iScreenHeight;

		int x = m_iScreenWidth / 2;
		int y = m_iScreenHeight / 2;

		if (gDraw.WorldToScreen(eyepos, screenEyepos))
		{
			gDraw.DrawLine(x, y, screenEyepos.x, screenEyepos.y, clrPlayerCol);
		}
	}
}

void CESP::Run(CBaseEntity* pLocal)
{
	if (!gCvars.esp_active)
		return;

	// Start at index 1 for players
	for (int i = 1; i <= gInts.Engine->GetMaxClients(); i++)
	{
		if (!gCvars.esp_local && i == me)
			continue;

		static ConVar* crosshair = gInts.cvar->FindVar("crosshair");
		if (gCvars.esp_crosshair)
		{
			gDraw.DrawCrosshair(1);
			crosshair->SetValue(0);
		}
		else
			crosshair->SetValue(1);

		CBaseEntity* pEntity = GetBaseEntity(i);
		if (!pEntity || pEntity->IsDormant() || pEntity->GetLifeState() != LIFE_ALIVE)
			continue;

		if (gCvars.esp_enemyonly && pEntity->GetTeamNum() == pLocal->GetTeamNum())
			continue;

		Player_ESP(pLocal, pEntity);
	}

	// Skip all player indexes so we can do buildings
	for (int i = gInts.Engine->GetMaxClients() + 1; i <= gInts.EntList->GetHighestEntityIndex(); i++)
	{
		int allowedIDS[6] = { 88, 86, 180 };
		int Objects;
		if (!gCvars.esp_buildings)
			break;
		//id = 117 sniper dots
		CBaseEntity *pEntity = gInts.EntList->GetClientEntity(i);
		if (!pEntity || pEntity->IsDormant() || pEntity->GetClientClass()->iClassID != 180 /*|| pEntity->GetClientClass()->iClassID != 180*/)
			continue;
		//if (gCvars.esp_enemyonly && pEntity->GetTeamNum() == pLocal->GetTeamNum())
		//	continue;

		auto id = pEntity->GetClientClass()->iClassID;
		int x, y, w, h;
		SetupBounds(pEntity, x, y, w, h);

		int iY = 0;
		int iHp = pEntity->GetHealth(), iMaxHp = pEntity->GetMaxHealth();
		if (iHp > iMaxHp)
			iHp = iMaxHp;

		Vector vOrigin, yousell;
		pEntity->GetWorldSpaceCenter(vOrigin);
		if (!gDraw.WorldToScreen(vOrigin, yousell))
			continue;

		int hpBuilding = pEntity->GetBuildingHealth();
		Color clrBuildingColor = gDraw.GetPlayerColor(pLocal,pEntity), clrTeam = Color(255, 255, 255, 255);
		//if (pEntity->GetTeamNum() == 2)
		if (pEntity->GetTeamNum() != pLocal->GetTeamNum())
			clrTeam = Color(255, 20, 20, 255); //red
		else if (pEntity->GetTeamNum() == pLocal->GetTeamNum())
			clrTeam = Color(0, 255, 20, 255);//green
		TColor filled = TColor(150, 0, 255, 10);

		switch (id)
		{
		case 180:
			if (gCvars.esp_buildings)
			{
				gDraw.text(x + w + 2, y + iY, clrBuildingColor, "[Ammo]");
				iY += gDraw.GetESPHeight();
			}break;

		}

	/*	if (gCvars.esp_box_buildings)
		{
			switch (gCvars.esp_box_selection)
			{
			case 0://Outlined
				gDraw.OutlineRect(x - 1, y - 1, w + 2, h + 2, Color::Black());
				gDraw.OutlineRect(x, y, w, h, clrBuildingColor);
				gDraw.OutlineRect(x + 1, y + 1, w - 2, h - 2, Color::Black());
				break;
			case 1://Not outlined
				gDraw.OutlineRect(x, y, w, h, clrBuildingColor);
				break;
			case 2://Filled
				gDraw.DrawRect(x, y, w, h, clrBuildingColor);
				break;
			case 3://Corner
				gDraw.DrawCornerBox(x, y, w, h - 1, 3, 5, Color::Red());
				gDraw.DrawFillbox(x, y, w, h, filled);
				break;
			}
		}*/
	}
	for (int i = gInts.Engine->GetMaxClients() + 1; i <= gInts.EntList->GetHighestEntityIndex(); i++)
	{
		int allowedIDS[6] = { 88, 86, 180 };
		int Objects;
		if (!gCvars.esp_buildings)
			break;
		//id = 117 sniper dots
		CBaseEntity *pEntity = gInts.EntList->GetClientEntity(i);
		if (!pEntity || pEntity->IsDormant() || pEntity->GetClientClass()->iClassID != 88 /*|| pEntity->GetClientClass()->iClassID != 180*/)
			continue;
		//if (gCvars.esp_enemyonly && pEntity->GetTeamNum() == pLocal->GetTeamNum())
		//	continue;

		auto id = pEntity->GetClientClass()->iClassID;
		int x, y, w, h;
		SetupBounds(pEntity, x, y, w, h);

		int iY = 0;
		int iHp = pEntity->GetHealth(), iMaxHp = pEntity->GetMaxHealth();
		if (iHp > iMaxHp)
			iHp = iMaxHp;

		Vector vOrigin, yousell;
		pEntity->GetWorldSpaceCenter(vOrigin);
		if (!gDraw.WorldToScreen(vOrigin, yousell))
			continue;

		int hpBuilding = pEntity->GetBuildingHealth();
		Color clrBuildingColor = gDraw.GetPlayerColor(pLocal,pEntity), clrTeam = Color(255, 255, 255, 255);
		//if (pEntity->GetTeamNum() == 2)
		if (pEntity->GetTeamNum() != pLocal->GetTeamNum())
			clrTeam = Color(255, 20, 20, 255); //red
		else if (pEntity->GetTeamNum() == pLocal->GetTeamNum())
			clrTeam = Color(0, 255, 20, 255);//green
		TColor filled = TColor(150, 0, 255, 10);

		switch (id)
		{
		case 88:
			if (gCvars.esp_buildings)
			{
				gDraw.text(x + w + 2, y + iY, clrBuildingColor, "[Sentry]");
				iY += gDraw.GetESPHeight();
			}break;

		}
			if (gCvars.esp_health_buildings == 0 && gCvars.esp_health_enabled || gCvars.esp_health_buildings == 2 && gCvars.esp_health_enabled)
		{
		gDraw.text(x + w + 2, y + iY, clrBuildingColor, "%d HP", hpBuilding);
		iY += gDraw.GetESPHeight();
		}

		if (gCvars.esp_box_buildings)
		{
			switch (gCvars.esp_box_selection)
			{
			case 0://Outlined
				gDraw.OutlineRect(x - 1, y - 1, w + 2, h + 2, Color::Black());
				gDraw.OutlineRect(x, y, w, h, clrBuildingColor);
				gDraw.OutlineRect(x + 1, y + 1, w - 2, h - 2, Color::Black());
				break;
			case 1://Not outlined
				gDraw.OutlineRect(x, y, w, h, clrBuildingColor);
				break;
			case 2://Filled
				gDraw.DrawRect(x, y, w, h, clrBuildingColor);
				break;
			case 3://Corner
				gDraw.DrawCornerBox(x, y, w, h - 1, 3, 5, Color::Red());
				gDraw.DrawFillbox(x, y, w, h, filled);
				break;
			}
		}
	}
	for (int i = gInts.Engine->GetMaxClients() + 1; i <= gInts.EntList->GetHighestEntityIndex(); i++)
	{
		int allowedIDS[6] = { 88, 86, 180 };
		int Objects;
		if (!gCvars.esp_buildings)
			break;
		//id = 117 sniper dots
		CBaseEntity *pEntity = gInts.EntList->GetClientEntity(i);
		if (!pEntity || pEntity->IsDormant() || pEntity->GetClientClass()->iClassID != 86 /*|| pEntity->GetClientClass()->iClassID != 180*/)
			continue;
		//if (gCvars.esp_enemyonly && pEntity->GetTeamNum() == pLocal->GetTeamNum())
		//	continue;

		auto id = pEntity->GetClientClass()->iClassID;
		int x, y, w, h;
		SetupBounds(pEntity, x, y, w, h);

		int iY = 0;
		int iHp = pEntity->GetHealth(), iMaxHp = pEntity->GetMaxHealth();
		if (iHp > iMaxHp)
			iHp = iMaxHp;

		Vector vOrigin, yousell;
		pEntity->GetWorldSpaceCenter(vOrigin);
		if (!gDraw.WorldToScreen(vOrigin, yousell))
			continue;

		int hpBuilding = pEntity->GetBuildingHealth();
		Color clrBuildingColor = gDraw.GetPlayerColor(pLocal,pEntity), clrTeam = Color(255, 255, 255, 255);
		//if (pEntity->GetTeamNum() == 2)
		if (pEntity->GetTeamNum() != pLocal->GetTeamNum())
			clrTeam = Color(255, 20, 20, 255); //red
		else if (pEntity->GetTeamNum() == pLocal->GetTeamNum())
			clrTeam = Color(0, 255, 20, 255);//green
		TColor filled = TColor(150, 0, 255, 10);

		switch (id)
		{
		case 86:
			if (gCvars.esp_buildings)
			{
				gDraw.text(x + w + 2, y + iY, clrBuildingColor, "[Dispenser]");
				iY += gDraw.GetESPHeight();
			}break;

		}
		if (gCvars.esp_health_buildings == 0 && gCvars.esp_health_enabled || gCvars.esp_health_buildings == 2 && gCvars.esp_health_enabled)
		{
			gDraw.text(x + w + 2, y + iY, clrBuildingColor, "%d HP", hpBuilding);
			iY += gDraw.GetESPHeight();	
		} /*
		if (gCvars.esp_health_buildings == 1 && gCvars.esp_health_enabled || gCvars.esp_health_buildings == 2 && gCvars.esp_health_enabled)
		{
		gDraw.OutlineRect(x - 6, y - 1, 5, h, Color::Black());
		gDraw.DrawRect(x - 5, y + (h - (h / iMaxHp * hpBuilding)) - 1, 3, h / iMaxHp * hpBuilding, Color::Green());
		}*/
		if (gCvars.esp_box_buildings)
		{
			switch (gCvars.esp_box_selection)
			{
			case 0://Outlined
				gDraw.OutlineRect(x - 1, y - 1, w + 2, h + 2, Color::Black());
				gDraw.OutlineRect(x, y, w, h, clrBuildingColor);
				gDraw.OutlineRect(x + 1, y + 1, w - 2, h - 2, Color::Black());
				break;
			case 1://Not outlined
				gDraw.OutlineRect(x, y, w, h, clrBuildingColor);
				break;
			case 2://Filled
				gDraw.DrawRect(x, y, w, h, clrBuildingColor);
				break;
			case 3://Corner
				gDraw.DrawCornerBox(x, y, w, h - 1, 3, 5, Color::Red());
				gDraw.DrawFillbox(x, y, w, h, filled);
				break;
			}
		}
	}
}

RECT get_text_size(const char* _Input, int font)
{
	int apple = 0;
	char Buffer[2048] = { '\0' };
	va_list Args;
	va_start(Args, _Input);
	vsprintf_s(Buffer, _Input, Args);
	va_end(Args);
	size_t Size = strlen(Buffer) + 1;
	wchar_t* WideBuffer = new wchar_t[Size];
	mbstowcs_s(0, WideBuffer, Size, Buffer, Size - 1);
	int Width = 0, Height = 0;

	gInts.Surface->GetTextSize(font, WideBuffer, Width, Height);

	RECT outcome = { 0, 0, Width, Height };
	return outcome;
}


void CESP::Player_ESP(CBaseEntity* pLocal, CBaseEntity* pEntity)
{
	player_info_t pInfo;
	if (!gInts.Engine->GetPlayerInfo(pEntity->GetIndex(), &pInfo))
		return;

	int x, y, w, h;
	SetupBounds(pEntity, x, y, w, h);
	Box box;

	int x_strings = x + 3;
	TColor filled = TColor(gCvars.color_fill_box_r, gCvars.color_fill_box_g, gCvars.color_fill_box_b, 10);
	TColor TeamMatefilled = TColor(0,100, 0, 10);
	Color clrPlayerCol = gDraw.GetPlayerColor(pLocal,pEntity);
	Color BoxMenuChoose = Color(gCvars.color_box_r, gCvars.color_box_g, gCvars.color_box_b);
	Color clrBoneCol = !gCvars.esp_bones ? Color::Color::Rainbow() : gCvars.esp_bones == 1 ? clrPlayerCol : gCvars.esp_bones == 2;
	int iY = 0;
	//iHp is only for health bar
	int iHp = pEntity->GetHealth(), iMaxHp = pEntity->GetMaxHealth();
	if (iHp > iMaxHp)
		iHp = iMaxHp;

	int curCond = pEntity->GetCond();
	if (gCvars.esp_removeDisguise && curCond & tf_cond::TFCond_Disguised)
		pEntity->SetCond(curCond & ~tf_cond::TFCond_Disguised);
	if (gCvars.esp_removeCloak && curCond & tf_cond::TFCond_Cloaked)
		pEntity->SetCond(curCond & ~tf_cond::TFCond_Cloaked);
	if (gCvars.esp_removeTaunt && curCond & tf_cond::TFCond_Taunting)
		pEntity->SetCond(curCond & ~tf_cond::TFCond_Taunting);

	if (gCvars.esp_health == 1 && gCvars.esp_health_enabled || gCvars.esp_health == 2 && gCvars.esp_health_enabled)
	{
		int iHp = pEntity->GetHealth(), iMaxHp = pEntity->GetMaxHealth();
		if (iHp > iMaxHp)
			iHp = iMaxHp;

		
			gDraw.OutlineRect(x - 1, y + h + 2, w + 2, 4, Color(21, 21, 21));

			int armor_width = iHp * w / iMaxHp;

			gDraw.DrawRect(x, y + h + 3, w, 2, Color(21, 21, 21));
			gDraw.DrawRect(x, y + h + 3, armor_width, 2, Color(0, 255, 0));
		
		/*gDraw.OutlineRect(x - 6, y - 1, 5, h, Color::Red());
		gDraw.DrawRect(x - 5, y + (h - (h / iMaxHp * iHp)) - 1, 3, h / iMaxHp * iHp, Color::Green());*/
	}
	if (gCvars.esp_name)
	{	
		RECT name_size = get_text_size(pInfo.name, g_ESPFont);
		gDraw.text(x + (w / 2) - (name_size.right / 2), y - 14, clrPlayerCol, pInfo.name);
		
	}
	float Distance = flGetDistance(pEntity->GetAbsOrigin(), pLocal->GetAbsOrigin());
	float flDistance = flGetDistance(pEntity->GetAbsOrigin(), pLocal->GetAbsOrigin());
	if (gCvars.esp_weapons)
	{
		gDraw.text(x + w + 2, y + iY, Color::Red(), "[%.0fm]", Distance);
		iY += gDraw.GetESPHeight();
	}
	if (pEntity->GetIndex() == gCvars.iAimbotIndex)
	{

		int iWidth, iHeight; //Resolution fix, so this can work in Fullscreen
		gInts.Engine->GetScreenSize(iWidth, iHeight);
		if (gScreenSize.iScreenWidth != iWidth || gScreenSize.iScreenHeight != iHeight)
			gInts.Engine->GetScreenSize(gScreenSize.iScreenWidth, gScreenSize.iScreenHeight);

	
		gDraw.text(iWidth / 2 - 30, iHeight / 2, Color::Red(), "!=TARGET=!");
		
	}
	if (gCvars.esp_class)
	{
		gDraw.text(x + w + 2, y + iY, Color::Yellow(), "%s", pEntity->szGetClass());
		iY += gDraw.GetESPHeight();
	}
	if (gCvars.esp_health == 0 && gCvars.esp_health_enabled || gCvars.esp_health == 2 && gCvars.esp_health_enabled)
	{
	
		gDraw.text(x + w + 2, y + iY, Color::Green(), "[%d HP]", pEntity->GetHealth());
		iY += gDraw.GetESPHeight();
	}
	if (gCvars.esp_snaplineson)
	{
		drawSnaplines(pEntity, pLocal);
	}

	if (gCvars.esp_active && gCvars.aimbot_fov != 0)
	{
		int m_iScreenWidth = gScreenSize.iScreenWidth;
		int m_iScreenHeight = gScreenSize.iScreenHeight;

		int x = m_iScreenWidth / 2;
		int y = m_iScreenHeight / 2;


		int sirka = gCvars.aimbot_fov * 6;
				

			gDraw.DrawCircle(x, y, sirka, 30, Color::Yellow());
	
	}	

	Vector b = pLocal->GetAbsAngles();

	if (gCvars.radarenable)
		gRadar.DrawRadarPoint(pEntity->GetAbsOrigin(), pLocal->GetAbsOrigin(), QAngle(b.x, b.y, b.z), pEntity, clrPlayerCol);


	if (gCvars.esp_view_lines)
	{
		//Lines;
		Vector angles = pEntity->GetAngles();
		Vector forward;
		AngleVectors(angles, &forward);
		Vector eyepos = pEntity->GetEyePosition();
		forward = forward * 83 + eyepos;
		Vector screenForward, screenEyepos;
		if (gDraw.WorldToScreen(eyepos, screenEyepos) && gDraw.WorldToScreen(forward, screenForward))
		{
			gDraw.DrawLine(screenForward.x, screenForward.y, screenEyepos.x, screenEyepos.y, Color::Rainbow());
		}
	}

	if (CBaseCombatWeapon* pWep = pEntity->GetActiveWeapon())
	{
		if (gCvars.esp_weapons)
		{
			std::string name = pWep->GetName();
			Util->ReplaceString(name, "#", "");
			Util->ReplaceString(name, "_", "");
			Util->ReplaceString(name, "TF", "");
			Util->ReplaceString(name, "Weapon", "");
			Util->ReplaceString(name, "tf weapon", "");
			Util->ReplaceString(name, "syringegun medic", "syringegun");
			Util->TrimStart(name);
			gDraw.text(x + w + 2, y + iY, Color::Indigo(), "%s", name.c_str());
			iY += gDraw.GetESPHeight();
		}
	}
	
	if (gCvars.esp_bones_enabled) //bones
	{
		static int iLeftArmBones[] = { 8, 7, 6, 4 };
		static int iRightArmBones[] = { 11, 10, 9, 4 };
		static int iHeadBones[] = { 0, 4, 1 };
		static int HeadOnly[] = { 0 };
		static int iLeftLegBones[] = { 14, 13, 1 };
		static int iRightLegBones[] = { 17, 16, 1 };
		

		DrawBone(pEntity, iLeftArmBones, 4, clrBoneCol);
		DrawBone(pEntity, iRightArmBones, 4, clrBoneCol);

		DrawBone(pEntity, iHeadBones, 3, clrBoneCol);

		DrawBone(pEntity, iLeftLegBones, 3, clrBoneCol);
		DrawBone(pEntity, iRightLegBones, 3, clrBoneCol);

	}
	
	if (gCvars.esp_bones_enabled) //bones
	{
		for (int i = 1; i < 17; i++) {
			Vector screen_position;
	
			Vector hitbone_pos = pEntity->GetHitboxPosition(i);


			if (gDraw.WorldToScreen(hitbone_pos, screen_position))
			{
				gDraw.rect(screen_position.x, screen_position.y, 4, 4, Color(21, 21, 21));
				gDraw.rect(screen_position.x + 1, screen_position.y + 1, 2, 2, clrPlayerCol);
			}
		}

		Vector screen_position;
		Vector headbone_pos = pEntity->GetHitboxPosition(0);
		
		if (gDraw.WorldToScreen(headbone_pos, screen_position))
		{
			gDraw.DrawCornerBox(screen_position.x, screen_position.y, 10, 10 - 1, 3, 4, Color::Red());
			gDraw.DrawFillbox(screen_position.x, screen_position.y, 10, 10, filled);
		}
	}


	if (gCvars.esp_box)
	{
		switch (gCvars.esp_box_selection)
		{
		case 0://Outlined
			boxas(pEntity, clrPlayerCol);
			break;
		case 1://Not outlined
			gDraw.OutlineRect(x, y, w, h, clrPlayerCol);
			break;
		case 2://Filled
			boxas(pEntity, clrPlayerCol);
			gDraw.DrawFillbox(x, y, w, h, filled);
			break;
		case 3://Corner
			gDraw.DrawCornerBox(x, y, w, h - 1, 3, 5, clrPlayerCol);
			gDraw.DrawFillbox(x, y, w, h, filled);			
			break;
		}
	}

	if (gCvars.backtrack && gCvars.backtrack_tick > 2) {

		for (int i = 0; i < 64; i++) {
			for (int t = 3; t < gCvars.backtrack_tick; t++) {
				Vector DrawThatShit;

				if (gDraw.WorldToScreen(headPositions[i][t].hitboxpos, DrawThatShit))
				{
					gDraw.DrawLine(DrawThatShit.x, DrawThatShit.y, DrawThatShit.x + 2, DrawThatShit.y + 2, Color::Indigo());
				}			
			}
		}
	}

	
	
		if (gCvars.esp_playerCond_enabled)
		{
			char* chCond = "**";
			if (gCvars.esp_playerCond)
				chCond = "[]";

			if (curCond & TFCond_Cloaked)
			{
				gDraw.text(x + w + 2, y + iY, Color(102, 178, 255, 255), "%cCLOAKED%c", chCond[0], chCond[1]);
				iY += gDraw.GetESPHeight();
			}
			if (curCond & TFCond_Disguised)
			{
				gDraw.text(x + w + 2, y + iY, Color(102, 178, 255, 255), "%cDisguised%c", chCond[0], chCond[1]);
				iY += gDraw.GetESPHeight();
			}
			if (curCond & TFCond_Bonked)
			{
				gDraw.text(x + w + 2, y + iY, Color(102, 178, 255, 255), "%cBonked%c", chCond[0], chCond[1]);
				iY += gDraw.GetESPHeight();
			}
			if (curCond & TFCond_Slowed)
			{
				gDraw.text(x + w + 2, y + iY, Color(102, 178, 255, 255), "%cSlowed%c", chCond[0], chCond[1]);
				iY += gDraw.GetESPHeight();
			}
			if (curCond & TFCond_OnFire)
			{
				gDraw.text(x + w + 2, y + iY, Color(102, 178, 255, 255), "%cBurning%c", chCond[0], chCond[1]);
				iY += gDraw.GetESPHeight();
			}
			if (curCond & TFCond_Zoomed)
			{
				gDraw.text(x + w + 2, y + iY, Color(102, 178, 255, 255), "%cZoomed%c", chCond[0], chCond[1]);
				iY += gDraw.GetESPHeight();
			}
			if (curCond & TFCond_Jarated)
			{
				gDraw.text(x + w + 2, y + iY, Color(102, 178, 255, 255), "%cJarated%c", chCond[0], chCond[1]);
				iY += gDraw.GetESPHeight();
			}
			if ((curCond & TFCond_Ubercharged) || (curCond & TFCond_MegaHeal))
			{
				gDraw.text(x + w + 2, y + iY, Color(102, 178, 255, 255), "%cUbered%c", chCond[0], chCond[1]);
				iY += gDraw.GetESPHeight();
			}
			else if (curCond & TFCond_UberchargeFading)
			{
				gDraw.text(x + w + 2, y + iY, Color(102, 178, 255, 255), "%cUber Fading%c", chCond[0], chCond[1]);
				iY += gDraw.GetESPHeight();
			}
			if (curCond & TFCond_Healing)
			{
				gDraw.text(x + w + 2, y + iY, Color(102, 178, 255, 255), "%cOver Healed%c", chCond[0], chCond[1]);
				iY += gDraw.GetESPHeight();
			}
		}
	
}

float CESP::flGetDistance(Vector vOrigin, Vector vLocalOrigin)
{
	Vector vDelta = vOrigin - vLocalOrigin;
	float m_fDistance = FastSqrt(vDelta.Length());
	if (m_fDistance < 1.0f)
	{
		return 1.0f;
	}
	return m_fDistance;
}

void CESP::SetupBounds(CBaseEntity* pEntity, int& x, int& y, int& w, int& h)
{
	if (!pEntity)
		return;

	const matrix3x4& vMatrix = pEntity->GetRgflCoordinateFrame();
	Vector vMin = pEntity->GetCollideableMins(), vMax = pEntity->GetCollideableMaxs();

	Vector vPointList[] = {
		Vector(vMin.x, vMin.y, vMin.z),
		Vector(vMin.x, vMax.y, vMin.z),
		Vector(vMax.x, vMax.y, vMin.z),
		Vector(vMax.x, vMin.y, vMin.z),
		Vector(vMax.x, vMax.y, vMax.z),
		Vector(vMin.x, vMax.y, vMax.z),
		Vector(vMin.x, vMin.y, vMax.z),
		Vector(vMax.x, vMin.y, vMax.z)
	};
	Vector a;
	Vector vTransformed[8];

	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 3; j++)
			vTransformed[i][j] = vPointList[i].Dot((Vector&)vMatrix[j]) + vMatrix[j][3];

	Vector flb, brt, blb, frt, frb, brb, blt, flt;

	if (!gDraw.WorldToScreen(vTransformed[3], flb) ||
		!gDraw.WorldToScreen(vTransformed[0], blb) ||
		!gDraw.WorldToScreen(vTransformed[2], frb) ||
		!gDraw.WorldToScreen(vTransformed[6], blt) ||
		!gDraw.WorldToScreen(vTransformed[5], brt) ||
		!gDraw.WorldToScreen(vTransformed[4], frt) ||
		!gDraw.WorldToScreen(vTransformed[1], brb) ||
		!gDraw.WorldToScreen(vTransformed[7], flt))
		return;

	Vector arr[] = { flb, brt, blb, frt, frb, brb, blt, flt };

	float left = flb.x;
	float top = flb.y;
	float right = flb.x;
	float bottom = flb.y;

	for (int i = 0; i < 8; i++)
	{
		if (left > arr[i].x)
			left = arr[i].x;
		if (top < arr[i].y)
			top = arr[i].y;
		if (right < arr[i].x)
			right = arr[i].x;
		if (bottom > arr[i].y)
			bottom = arr[i].y;
	}

	x = left, y = bottom, w = right - left, h = top - bottom;

	// ESP boxes too thicc ;3
	x += ((right - left) / 8);
	w -= ((right - left) / 8) * 2;
}

void CESP::boxas(CBaseEntity* pEntity, Color clrColor)
{
	int x, y, w, h;
	SetupBounds(pEntity, x, y, w, h);

	gDraw.outline(x, y, w, h, clrColor);
	
	gDraw.outline(x - 1, y - 1, w + 2, h + 2, Color(21, 21, 21));
	gDraw.outline(x + 1, y + 1, w - 2, h - 2, Color(21, 21, 21));
}

//My code, but creds to f1ssion for giving me the idea
void CESP::DrawBone(CBaseEntity* pEntity, int* iBones, int count, Color clrCol)
{
	for (int i = 0; i < count; i++)
	{
		if (i == count - 1)
			continue;

		Vector vBone1 = pEntity->GetHitboxPosition(iBones[i]);
		Vector vBone2 = pEntity->GetHitboxPosition(iBones[i + 1]);

		Vector vScr1, vScr2;

		if (!gDraw.WorldToScreen(vBone1, vScr1) || !gDraw.WorldToScreen(vBone2, vScr2))
			continue;

		gDraw.DrawLine(vScr1.x, vScr1.y, vScr2.x, vScr2.y, clrCol);
	}
}

