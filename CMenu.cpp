
/// THIS IS NOT THE MENU YOU ARE LOOKING FOR!

/// NEW MENU LOCATED IN FAKEWARE/MENU.CPP

/*#include "CMenu.h"
#include "SDK.h"
#include "CDrawManager.h"
#include "Util.h"

#include <algorithm>

CCheatMenu gCheatMenu;

int ScreenH;
int ScreenW;

char* szKeyNames[] = {
	"None", "Mouse 1", "Mouse 2", "Mouse 3", "Mouse 4", "Mouse 5", "Shift", "Alt", "F"
};

char* szHealthModes[] = {
	"OFF", "Text", "Bar", "Both",
};

char* szBoneModes[] = {
	"OFF", "White", "Health", "Team",
};

char* szHitboxes[] =
{
	"Auto", "Head", "Pelvis", "Lower Torse", "Lower Mid. Torse", "Upper Mid. Torse", "Upper Torse",
	"Left Upper Arm", "Left Lower Arm", "Left Hand", "Right Upper Arm",
	"Right Lower Arm", "Right Hand", "Left Hip", "Left Knee", "Left Foot",
	"Right Hip", "Right Knee", "Right Foot",
};

char* ChatSpams[] = { "OFF", "NullCore", "LMAOBOX", "Lithium", "Cathook", "Empty Lines", "Speedhook", "Freebox", "Catbot", "Dumpster Fire" };

char* KillSays[] = { "OFF", "NiggerHOOK", "NullCore", "File" };

char* condESP[] = { "OFF", "Dumpster Fire", "NullCore" };

int CCheatMenu::AddItem(int nIndex, char szTitle[30], float* value, float flMin, float flMax, float flStep, bool isClassSwitch)
{
	strcpy(pMenu[nIndex].szTitle, szTitle);
	pMenu[nIndex].value = value;
	pMenu[nIndex].flMin = flMin;
	pMenu[nIndex].flMax = flMax;
	pMenu[nIndex].flStep = flStep;
	pMenu[nIndex].isClassSwitch = isClassSwitch;
	return (nIndex + 1);
}

void CCheatMenu::Render(void)
{
	gInts.Engine->GetScreenSize(ScreenW, ScreenH);

	int i = 0;
	
	i = AddItem(i, "Aimbot", &gCvars.aimbot_switch, 0, 1, 1, true);
	if (gCvars.aimbot_switch)
	{

		/TODO: TRANSITION EVERYTHING FROM POTASSIUM TO FAKEWARE MENU

		i = AddItem(i, " - Enabled", &gCvars.aimbot_active, 0, 1, 1, false);
		i = AddItem(i, " - Silent", &gCvars.aimbot_silent, 0, 1, 1, false);
		i = AddItem(i, " - FOV", &gCvars.aimbot_fov, 0, 180, 1, false);  NOT IN CHEAT ANYMORE
		i = AddItem(i, " - Key", &gCvars.aimbot_key, 0, 8, 1, false);
		i = AddItem(i, " - Hitscan", &gCvars.aimbot_hitscan, 0, 1, 1, false);
		i = AddItem(i, " - Hitbox", &gCvars.aimbot_hitbox, 0, 18, 1, false);
		i = AddItem(i, " - Autoshoot", &gCvars.aimbot_autoshoot, 0, 1, 1, false);
		i = AddItem(i, " - Smooth", &gCvars.aimbot_smooth, 0, 1, 1, false);
		if (gCvars.aimbot_smooth)
		{
			i = AddItem(i, "  - Amount", &gCvars.aimbot_smooth_amt, 0, 180, 1, false);
		}
		i = AddItem(i, " - Ignore Cloak", &gCvars.aimbot_ignore_cloak, 0, 1, 1, false);
		i = AddItem(i, " - Zoomed Only", &gCvars.aimbot_zoomedonly, 0, 1, 1, false);
	}

	i = AddItem(i, "Triggerbot", &gCvars.triggerbot_switch, 0, 1, 1, true);
	if (gCvars.triggerbot_switch)
	{
		i = AddItem(i, " - Enabled", &gCvars.triggerbot_active, 0, 1, 1, false);
		i = AddItem(i, " - Key", &gCvars.triggerbot_key, 0, 8, 1, false);
		i = AddItem(i, " - Head Only", &gCvars.triggerbot_headonly, 0, 1, 1, false);
	}

	i = AddItem(i, "Player List", &gCvars.playerlist_switch, 0, 1, 1, true);
	for (int p = 1; p <= gInts.Engine->GetMaxClients(); p++)
	{
		if (p == me)
			continue;

		CBaseEntity *pPlayer = GetBaseEntity(p);

		if (pPlayer == NULL)
			continue;

		player_info_t pInfo;
		gInts.Engine->GetPlayerInfo(p, &pInfo);

		char szString[256];
		sprintf(szString, " - %s", pInfo.name);

		if (gCvars.playerlist_switch)
			i = AddItem(i, szString, &gCvars.PlayerMode[pPlayer->GetIndex()], 0, 2, 1, false);
	}


	i = AddItem(i, "ESP", &gCvars.esp_switch, 0, 1, 1, true);
	if (gCvars.esp_switch)
	{
		i = AddItem(i, " - Enabled", &gCvars.esp_active, 0, 1, 1, false);
		i = AddItem(i, " - Enemies Only", &gCvars.esp_enemyonly, 0, 1, 1, false);
		i = AddItem(i, " - Box", &gCvars.esp_box, 0, 1, 1, false);
		if (gCvars.esp_box)
		{
			i = AddItem(i, " - Thickness", &gCvars.esp_box_thickness, 1, 4, 1, false);
		}
		i = AddItem(i, " - Name", &gCvars.esp_name, 0, 1, 1, false);
		i = AddItem(i, " - Class", &gCvars.esp_class, 0, 1, 1, false);
		i = AddItem(i, " - Cond", &gCvars.esp_playerCond, 0, 1, 1, false);
		i = AddItem(i, " - Remove Cloak", &gCvars.esp_removeCloak, 0, 1, 1, false);
		i = AddItem(i, " - Remove Disguise", &gCvars.esp_removeDisguise, 0, 1, 1, false);
		i = AddItem(i, " - Remove Taunt", &gCvars.esp_removeTaunt, 0, 1, 1, false);
		i = AddItem(i, " - Health", &gCvars.esp_health, 0, 3, 1, false);
		i = AddItem(i, " - Bones", &gCvars.esp_bones, 0, 3, 1, false);
		i = AddItem(i, " - Happy Face", &gCvars.esp_face, 0, 1, 1, false);
		i = AddItem(i, " - Crosshair", &gCvars.esp_crosshair, 0, 1, 1, false);
	}
	
	i = AddItem(i, "Anti Aim", &gCvars.aa_switch, 0, 1, 1, true);
	if (gCvars.aa_switch)
	{
		i = AddItem(i, " - Pitch", &gCvars.aa_pitch, 0, 1, 1, true);
		i = AddItem(i, " - Yaw", &gCvars.aa_yaw, 0, 1, 1, true);

		/ JUST WHY?!?!?!?
		i = AddItem(i, " - Pitch", &gCvars.aa_pitch, 0, 1, 1, true);
		if (gCvars.aa_pitch)
		{
			i = AddItem(i, " - Fake Up", &gCvars.aa_pitch_fakeup, 0, 1, 1, false);
			i = AddItem(i, " - Fake Down", &gCvars.aa_pitch_fakedown, 0, 1, 1, false);
		}
		i = AddItem(i, " - Yaw", &gCvars.aa_yaw, 0, 1, 1, true);
		if (gCvars.aa_yaw)
		{
			i = AddItem(i, " - Left", &gCvars.aa_yaw_left, 0, 1, 1, false);
			i = AddItem(i, " - Right", &gCvars.aa_yaw_right, 0, 1, 1, false);
			i = AddItem(i, " - Staticjitter", &gCvars.aa_yaw_staticjitter, 0, 1, 1, false);
		}
	}


	i = AddItem(i, "Settings", &gCvars.settings_switch, 0, 1, 1, true);
	if (gCvars.settings_switch)
	{
		i = AddItem(i, " - Position X", &gCvars.iMenu_Pos_X, 0, ScreenW, 8, false);
		i = AddItem(i, " - Position Y", &gCvars.iMenu_Pos_Y, 0, ScreenH, 8, false);
	}

	i = AddItem(i, "Remove Cond", &gCvars.removecond_switch, 0, 1, 1, true);
	if (gCvars.removecond_switch) {
		i = AddItem(i, " - Enabled", &gCvars.removecond_enabled, 0, 1, 1, false);
		i = AddItem(i, " - Value", &gCvars.removecond_value, 0, 1000, 100, false);
		i = AddItem(i, " - Key", &gCvars.removecond_key, 0, 8, 1, false);
		i = AddItem(i, " - Auto Instant Cap", &gCvars.removecond_autoinstantcap, 0, 1, 1, false);
		i = AddItem(i, " - Instant Weapon Switch", &gCvars.removecond_instantweaponswitch, 0, 1, 1, false);
		i = AddItem(i, " - Auto Medkit", &gCvars.removecond_automedkit, 0, 1, 1, false);
		i = AddItem(i, " - Sticky Spam", &gCvars.removecond_stickyspam, 0, 1, 1, false);
	}

	i = AddItem(i, "Misc", &gCvars.misc_switch, 0, 1, 1, true);
	if (gCvars.misc_switch)
	{
		i = AddItem(i, " - Bunnyhop", &gCvars.misc_bunnyhop, 0, 1, 1, false);
		i = AddItem(i, " - Autostrafe", &gCvars.misc_autostrafe, 0, 1, 1, false);
		i = AddItem(i, " - Thirdperson", &gCvars.misc_thirdPerson, 0, 1, 1, false);
		i = AddItem(i, " - Auto Backstab", &gCvars.misc_autobackstab, 0, 1, 1, false);
		i = AddItem(i, " - Noisemaker Spam", &gCvars.misc_noisemaker_spam, 0, 1, 1, false);
		i = AddItem(i, " - No Scope", &gCvars.misc_noscope, 0, 1, 1, false);
		i = AddItem(i, " - Chat Spam", &gCvars.misc_chatspam_selection, 0, 9, 1, false);
		i = AddItem(i, " - Chat Spam Delay", &gCvars.misc_chatspam_delay, 0, 3000, 100, false); autism
		i = AddItem(i, " - Kill Say", &gCvars.misc_killsay_selection, 0, 3, 1, false);
		i = AddItem(i, " - Roll Speedhack", &gCvars.misc_roll_speedhack, 0, 1, 1, false);
		i = AddItem(i, " - wow sweet", &gCvars.misc_wowsweet, 0, 1, 1, false);
		i = AddItem(i, " - Clean Screenshot", &gCvars.misc_cleanScreenshot, 0, 1, 1, false);
		i = AddItem(i, " - FOV", &gCvars.misc_fov, 70, 120, 1, false);
		i = AddItem(i, " - Viewmodel FOV", &gCvars.misc_viewmodel_fov, 50, 120, 1, false); this can be done via in-game commands retards
		i = AddItem(i, " - No Push", &gCvars.misc_no_push, 0, 1, 1, false);
		i = AddItem(i, " - Voice Menu Spam", &gCvars.misc_voice, 0, 6, 1, false); too lazy to make the actual labels for the options
	}

	iMenuItems = i;
}

void CCheatMenu::DrawMenu(void)
{
	int x = gCvars.iMenu_Pos_X,
		xx = x + 200,
		y = gCvars.iMenu_Pos_Y,
		w = 272,
		h = 14;

	CBaseEntity *pLocal = GetBaseEntity(me);

	Color clrColor = gDraw.GetPlayerColor(pLocal);

	gDraw.DrawRect(x, y - (h + 4), w, iMenuItems * h + 20, Color(32, 32, 32, 127));
	gDraw.DrawRect(x, y - (h + 4), w, (h + 4), clrColor);
	gDraw.DrawLineEx(x, y + 2 + (iMenuItems * h), w, 0, clrColor);

	gDraw.DrawString(x + 4, y - 16, clrColor, "Dumpster Fire");

	for (int i = 0; i < iMenuItems; i++)
	{
		if (i != iMenuIndex)
		{
			if (pMenu[i].isClassSwitch)
			{
				if (!(pMenu[i].value[0]))
				{
					gDraw.DrawString(x + 2, y + (h * i), clrColor, "[+] %s", pMenu[i].szTitle);
				}
				else if (pMenu[i].value[0])
				{
					gDraw.DrawString(x + 2, y + (h * i), clrColor, "[-] %s", pMenu[i].szTitle);
				}
			}
			else
			{
				gDraw.DrawString(x + 4, y + (h * i), Color::White(), pMenu[i].szTitle);

				if (!strcmp(pMenu[i].szTitle, " - Health"))
				{
					gDraw.DrawString(xx, y + (h * i), pMenu[i].value[0] ? Color::White() : Color(105, 105, 105, 255), "%s", szHealthModes[(int)pMenu[i].value[0]]);
				}

				else if (!strcmp(pMenu[i].szTitle, " - Bones"))
				{
					gDraw.DrawString(xx, y + (h * i), pMenu[i].value[0] ? Color::White() : Color(105, 105, 105, 255), "%s", szBoneModes[(int)pMenu[i].value[0]]);
				}

				else if (pMenu[i].flMax == 18)
				{
					gDraw.DrawString(xx, y + (h * i), Color::White(), "%s", szHitboxes[(int)pMenu[i].value[0]]);
				}

				else if (pMenu[i].flMax == 8)
				{
					gDraw.DrawString(xx, y + (h * i), Color::White(), "%s", szKeyNames[(int)pMenu[i].value[0]]);
				}

				else if (pMenu[i].flMax == 9)
				{
					gDraw.DrawString(xx, y + (h * i), pMenu[i].value[0] ? Color::White() : Color(105, 105, 105, 255), "%s", ChatSpams[(int)pMenu[i].value[0]]);
				}

				else if (pMenu[i].flMax == 3)
				{
					gDraw.DrawString(xx, y + (h * i), pMenu[i].value[0] ? Color::White() : Color(105, 105, 105, 255), "%s", KillSays[(int)pMenu[i].value[0]]);
				}

				else if (pMenu[i].flMax == 2)
				{
					if (!strcmp(pMenu[i].szTitle, " - Cond"))
						gDraw.DrawString(xx, y + (h * i), pMenu[i].value[0] ? Color::White() : Color(105, 105, 105, 255), "%s", condESP[(int)pMenu[i].value[0]]);
					else
						gDraw.DrawString(xx, y + (h * i), Color::White(), !pMenu[i].value[0] ? "Ignore" : pMenu[i].value[0] == 1 ? "Normal" : "Rage");
				}

				else if (pMenu[i].flMax == 1)
				{
					gDraw.DrawString(xx, y + (h * i), pMenu[i].value[0] ? Color::White() : Color(105, 105, 105, 255), pMenu[i].value[0] ? "ON" : "OFF");
				}

				else if (pMenu[i].value[0] >= 1 && pMenu[i].flMax > 1)
				{
					gDraw.DrawString(xx, y + (h * i), pMenu[i].value[0] >= 1 ? Color::White() : Color(105, 105, 105, 255), "%0.0f", pMenu[i].value[0]);
				}
			}
		}
		else
		{
			gDraw.DrawRect(x + 1, y + (h * i), w - 2, h, Color(255, 255, 255, 80));

			if (pMenu[i].isClassSwitch)
			{
				if (!(pMenu[i].value[0]))
				{
					gDraw.DrawString(x + 2, y + (h * i), clrColor, "[+] %s", pMenu[i].szTitle);
				}
				else if (pMenu[i].value[0])
				{
					gDraw.DrawString(x + 2, y + (h * i), clrColor, "[-] %s", pMenu[i].szTitle);
				}
			}
			else
			{
				gDraw.DrawString(x + 4, y + (h * i), clrColor, pMenu[i].szTitle);

				if (!strcmp(pMenu[i].szTitle, " - Health"))
				{
					gDraw.DrawString(xx, y + (h * i), clrColor, "%s", szHealthModes[(int)pMenu[i].value[0]]);
				}

				else if (!strcmp(pMenu[i].szTitle, " - Bones"))
				{
					gDraw.DrawString(xx, y + (h * i), clrColor, "%s", szBoneModes[(int)pMenu[i].value[0]]);
				}

				else if (pMenu[i].flMax == 18)
				{
					gDraw.DrawString(xx, y + (h * i), clrColor, "%s", szHitboxes[(int)pMenu[i].value[0]]);
				}

				else if (pMenu[i].flMax == 8)
				{
					gDraw.DrawString(xx, y + (h * i), clrColor, "%s", szKeyNames[(int)pMenu[i].value[0]]);
				}

				else if (pMenu[i].flMax == 9)
				{
					gDraw.DrawString(xx, y + (h * i), pMenu[i].value[0] ? clrColor : Color(105, 105, 105, 255), "%s", ChatSpams[(int)pMenu[i].value[0]]);
				}

				else if (pMenu[i].flMax == 3)
				{
					gDraw.DrawString(xx, y + (h * i), pMenu[i].value[0] ? clrColor : Color(105, 105, 105, 255), "%s", KillSays[(int)pMenu[i].value[0]]);
				}

				else if (pMenu[i].flMax == 2)
				{
					if (!strcmp(pMenu[i].szTitle, " - Cond"))
						gDraw.DrawString(xx, y + (h * i), pMenu[i].value[0] ? clrColor : Color(105, 105, 105, 255), "%s", condESP[(int)pMenu[i].value[0]]);
					else
						gDraw.DrawString(xx, y + (h * i), clrColor, !pMenu[i].value[0] ? "Ignore" : pMenu[i].value[0] == 1 ? "Normal" : "Rage");
				}

				else if (pMenu[i].flMax == 1)
				{
					gDraw.DrawString(xx, y + (h * i), clrColor, pMenu[i].value[0] ? "ON" : "OFF");
				}

				else
				{
					gDraw.DrawString(xx, y + (h * i), clrColor, "%0.0f", pMenu[i].value[0]);
				}
			}
		}
	}
}*/