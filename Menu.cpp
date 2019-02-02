#include "Menu.h"
#include "Panels.h"
/*
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

char* condESP[] = { "OFF", "Dumpster Fire", "NullCore" };*/ // Unneeded, but keep them here for reference.

void Menu::Init()
{
	if (m_isVisible = false)
	{
		int m_iScreenWidth = gScreenSize.iScreenWidth;
		int m_iScreenHeight = gScreenSize.iScreenHeight;

		int x = (m_iScreenWidth / 2) + 2000;
		int y = m_iScreenHeight / 2;
		gInts.Surface->GetCursorPosition(x, y);
	}

	m_isVisible = false;
	m_ESPtabVisible = false;
	m_AIMtabVisible = false;
	m_MISCtabVisible = false;
	m_COLtabVisible = false;//šířka, délka
	CWindow AimbotTabz(100, 100, 175, 335);
	CWindow HVHTabz(100, 100, 170, 200);
	CWindow	ESPTabz(100, 100, 245, 505);
	CWindow	MISCTabz(100, 100, 245, 380);
	CWindow COLORTabz(100, 100, 310, 300);
	CWindow MainTablist(100, 100, 125, 110);
	// checkbox: 12 pixels
	
#pragma region fistgui
	auto Tabz = new CChild(0, 0, 100, L"╔Tabs╗");
	Tabz->AddControl(new CCheckBox2(L"✜ AIM", &m_AIMtabVisible));
	Tabz->AddControl(new CCheckBox2(L"❂ ESP", &m_ESPtabVisible));
	Tabz->AddControl(new CCheckBox2(L"Ξ MISC", &m_MISCtabVisible));
	Tabz->AddControl(new CCheckBox2(L"☠ HVH", &m_HVHtabVisible));
	Tabz->AddControl(new CCheckBox2(L"◮ COLOR", &m_COLtabVisible));
	MainTablist.AddControl(Tabz);
#pragma endregion
#pragma region Aimbot
	auto AimbotTab = new CChild(0, 0, 150, L"╔Aimbot╗");

	AimbotTab->AddControl(new CCheckBox(L"Enabled", &gCvars.aimbot_active));
	AimbotTab->AddControl(new CCheckBox(L"Silent", &gCvars.aimbot_silent));
	AimbotTab->AddControl(new CSlider<int>(L"FOV", 0, 180, &gCvars.aimbot_fov));
	AimbotTab->AddControl(new CCheckBox(L"Autoshoot", &gCvars.aimbot_autoshoot));
	AimbotTab->AddControl(new CCheckBox(L"Hitscan", &gCvars.aimbot_hitscan));
	AimbotTab->AddControl(new CCombo(&gCvars.aimbot_key, { L"Always", L"Mouse 1", L"Mouse 2", L"Mouse 3", L"Mouse 4", L"Mouse 5", L"Shift", L"Alt", L"F" }));
	AimbotTab->AddControl(new CSlider<int>(L"Smooth", 0.f, 4.f, &gCvars.aimbot_smooth));
	AimbotTab->AddControl(new CCheckBox(L"Ignore Cloak", &gCvars.aimbot_ignore_cloak));
	AimbotTab->AddControl(new CCheckBox(L"Zoomed Only", &gCvars.aimbot_zoomedonly));
	AimbotTab->AddControl(new CCheckBox(L"Amby", &gCvars.aimbot_waitforcharge));

	AimbotTab->AddControl(new CCheckBox(L"Backtrack", &gCvars.backtrack));
	AimbotTab->AddControl(new CSlider<int>(L"Ticks", 0, 12, &gCvars.bt_ticks));
	AimbotTabz.AddControl(AimbotTab);
#pragma endregion
#pragma region Triggerbot
	auto TriggerbotTab = new CChild(0, 195, 150, L"╔Triggerbot╗");

	TriggerbotTab->AddControl(new CCheckBox(L"Enabled", &gCvars.triggerbot_active));
	TriggerbotTab->AddControl(new CCombo(&gCvars.triggerbot_key, { L"Always", L"Mouse 1", L"Mouse 2", L"Mouse 3", L"Mouse 4", L"Mouse 5", L"Shift", L"Alt", L"F" })); // NEEDS LIST
	TriggerbotTab->AddControl(new CCheckBox(L"Head Only", &gCvars.triggerbot_headonly));
	TriggerbotTab->AddControl(new CCheckBox(L"Auto Airblast", &gCvars.triggerbot_autoairblast));
	TriggerbotTab->AddControl(new CCombo(&gCvars.triggerbot_autoairblast_key, { L"Always", L"Mouse 1", L"Mouse 2", L"Mouse 3", L"Mouse 4", L"Mouse 5", L"Shift", L"Alt", L"F" })); // NEEDS LIST
	TriggerbotTab->AddControl(new CCheckBox(L"Legit", &gCvars.triggerbot_autoairblast_legit));
	TriggerbotTab->AddControl(new CCheckBox(L"Silent", &gCvars.triggerbot_autoairblast_silent));


	AimbotTabz.AddControl(TriggerbotTab);
#pragma endregion
#pragma region Anti Aim
	auto AntiAimTab = new CChild(0, 0, 150, L"╔HVH╗");

	AntiAimTab->AddControl(new CCheckBox(L"Enabled", &gCvars.aa_enabled));
	AntiAimTab->AddControl(new CCheckBox(L"Pitch", &gCvars.aa_pitch_enabled));
	AntiAimTab->AddControl(new CCombo(&gCvars.aa_pitch, { L"none",L"Fake Up", L"Up", L"Fake Down", L"Down" })); // NEEDS LIST
	AntiAimTab->AddControl(new CCheckBox(L"Yaw", &gCvars.aa_yaw_enabled));
	AntiAimTab->AddControl(new CCombo(&gCvars.aa_yaw, { L"none",L"BackJitter", L"Flip", L"Back", L"Random", L"Spin", L"Edge", L"Fake Sideways" })); // NEEDS LIST // Finally, a string that actually uses a unicode character! // Well not anymore...
	AntiAimTab->AddControl(new CCombo(&gCvars.aa_key, { L"Always", L"Mouse 1", L"Mouse 2", L"Mouse 3", L"Mouse 4", L"Mouse 5", L"Shift", L"Alt", L"F" })); // NEEDS LIST
	AntiAimTab->AddControl(new CSlider<int>(L"Spin Speed", 0, 360, &gCvars.aa_spinspeed));
	AntiAimTab->AddControl(new CCheckBox(L"Resolver", &gCvars.aa_resolver));
	AntiAimTab->AddControl(new CCheckBox(L"FAKE", &gCvars.fakeYAW));
	AntiAimTab->AddControl(new CCombo(&gCvars.aa_fake_yaw, { L"none",L"Switch",L"Spin"}));
	HVHTabz.AddControl(AntiAimTab);
#pragma endregion
#pragma region ESP
	auto ESPTab = new CChild(0, 0, 220, L"╔ESP╗");

	ESPTab->AddControl(new CCheckBox(L"Enable ESP", &gCvars.esp_active));
	ESPTab->AddControl(new CCheckBox(L"Enable Snaplines", &gCvars.esp_snaplineson));
	ESPTab->AddControl(new CCombo(&gCvars.esp_snaplines, { L"none", L"All players" })); 
	ESPTab->AddControl(new CCheckBox(L"Object ESP", &gCvars.esp_buildings));
	ESPTab->AddControl(new CCheckBox(L"Object ESP Box", &gCvars.esp_box_buildings));
	ESPTab->AddControl(new CCombo(&gCvars.esp_health_buildings, { L"Text", L"Bar", L"Both" }));
	ESPTab->AddControl(new CCheckBox(L"Box", &gCvars.esp_box));
	ESPTab->AddControl(new CCheckBox(L"Enemies Only", &gCvars.esp_enemyonly)); 
	ESPTab->AddControl(new CCheckBox(L"Local", &gCvars.esp_local));
	ESPTab->AddControl(new CCheckBox(L"View lines", &gCvars.esp_view_lines));
	ESPTab->AddControl(new CCombo(&gCvars.esp_box_selection, { L"Outlined", L"Box", L"Filled", L"Corner" })); 
	ESPTab->AddControl(new CCheckBox(L"Name", &gCvars.esp_name));
	ESPTab->AddControl(new CCheckBox(L"Class", &gCvars.esp_class));
	ESPTab->AddControl(new CCheckBox(L"Weapon", &gCvars.esp_weapons));
	ESPTab->AddControl(new CCheckBox(L"Cond", &gCvars.esp_playerCond_enabled));
	ESPTab->AddControl(new CCombo(&gCvars.esp_playerCond, { L"Dumpster Fire", L"NullCore" })); // NEEDS LIST
	ESPTab->AddControl(new CCheckBox(L"Remove Cloak", &gCvars.esp_removeCloak));
	ESPTab->AddControl(new CCheckBox(L"Remove Disguise", &gCvars.esp_removeDisguise));
	ESPTab->AddControl(new CCheckBox(L"Remove Taunt", &gCvars.esp_removeTaunt));
	ESPTab->AddControl(new CCheckBox(L"Health", &gCvars.esp_health_enabled));
	ESPTab->AddControl(new CCombo(&gCvars.esp_health, { L"Text", L"Bar", L"Both" })); // NEEDS LIST
	ESPTab->AddControl(new CCheckBox(L"Bones", &gCvars.esp_bones_enabled));
	ESPTab->AddControl(new CCombo(&gCvars.esp_bones, { L"White", L"Health", L"Team" })); // NEEDS LIST
	ESPTab->AddControl(new CCheckBox(L"Happy Face", &gCvars.esp_face));
	ESPTab->AddControl(new CCombo(&gCvars.sky_changer_value, { L"None", L"Night", L"Nightfall", L"Harvest Night", L"Halloween" }));
	ESPTab->AddControl(new CCheckBox(L"Crosshair", &gCvars.esp_crosshair));

	


	ESPTabz.AddControl(ESPTab);
#pragma endregion
#pragma region RADAR
	auto RADARTab = new CChild(0, 390, 220, L"╔ESP - Radar╗");
	
	RADARTab->AddControl(new CCheckBox(L"Enable", &gCvars.radarenable));
	RADARTab->AddControl(new CSlider<int>(L"Pos-X", 0, 3000, &gCvars.radar_posx));
	RADARTab->AddControl(new CSlider<int>(L"Pos-Y", 0, 3000, &gCvars.radar_posy));
	RADARTab->AddControl(new CSlider<int>(L"Size", 0, 300, &gCvars.radar_width));
	RADARTab->AddControl(new CCombo(&gCvars.radartype, { L"none", L"Square", L"Circle" }));
	ESPTabz.AddControl(RADARTab);
#pragma endregion

#pragma region Misc
	auto MiscTab = new CChild(0, 0, 220, L"╔Misc╗");

	MiscTab->AddControl(new CCheckBox(L"Bunny Hop", &gCvars.misc_bunnyhop));
	MiscTab->AddControl(new CCheckBox(L"Auto Strafe", &gCvars.misc_autostrafe));
	MiscTab->AddControl(new CCheckBox(L"Third Person", &gCvars.misc_thirdPerson));
	MiscTab->AddControl(new CCheckBox(L"Auto Backstab", &gCvars.misc_autobackstab));
	MiscTab->AddControl(new CCheckBox(L"Noisemaker Spam", &gCvars.misc_noisemaker_spam));
	MiscTab->AddControl(new CCheckBox(L"No Scope", &gCvars.misc_noscope));
	MiscTab->AddControl(new CCheckBox(L"No Zoom", &gCvars.misc_nozoom));
	MiscTab->AddControl(new CCheckBox(L"No Push", &gCvars.misc_no_push));
	MiscTab->AddControl(new CCheckBox(L"Chat Spam", &gCvars.misc_chatspam_enabled));
	MiscTab->AddControl(new CCombo(&gCvars.misc_chatspam_selection, { L"hackname", L"LMAOBOX", L"Lithium", L"Cathook", L"Empty Lines", L"Speedhook", L"Freebox", L"Catbot", L"Dumpster Fire" })); // NEEDS LIST
	MiscTab->AddControl(new CSlider<int>(L"Delay", 1000, 3000, &gCvars.misc_chatspam_delay));
	MiscTab->AddControl(new CSlider<int>(L"Newlines", 0, 32, &gCvars.misc_chatspam_newline));
	MiscTab->AddControl(new CCheckBox(L"Kill Say", &gCvars.misc_killsay_enabled));
	MiscTab->AddControl(new CCombo(&gCvars.misc_killsay_selection, { L"NiggerHOOK", L"NullCore", L"File" })); // NEEDS LIST
	MiscTab->AddControl(new CCheckBox(L"Voice Menu Spam", &gCvars.misc_voice)); // NEEDS LIST (?) // Apple, when you add the options to this feature please add to menu. Thanks. - Wolfie
	MiscTab->AddControl(new CCheckBox(L"Roll Speedhack", &gCvars.misc_roll_speedhack));
	MiscTab->AddControl(new CCheckBox(L"Big Heads", &gCvars.misc_bighead));
	MiscTab->AddControl(new CSlider<int>(L"HeadSize", 0, 20, &gCvars.misc_bigheadsize));
	MiscTab->AddControl(new CSlider<int>(L"TorsoSize", 0, 20, &gCvars.misc_torsosize));
	MiscTab->AddControl(new CSlider<int>(L"HandSize", 0, 20, &gCvars.misc_handsize));
	MiscTab->AddControl(new CCheckBox(L"Clean Screenshot", &gCvars.misc_cleanScreenshot));
	MiscTab->AddControl(new CSlider<int>(L"Field of View", 0, 120, &gCvars.misc_fov));
	MiscTab->AddControl(new CSlider<int>(L"Viewmodel FOV", 0, 120, &gCvars.misc_viewmodel_fov));

	MISCTabz.AddControl(MiscTab);
#pragma endregion
#pragma region BoxColor
	auto BoxColorTab = new CChild(0, 0, 240, L"╔Box (Enemy) Color╗");

	BoxColorTab->AddControl(new CSlider<int>(L"Box Color - Red", 0, 255, &gCvars.color_box_r));
	BoxColorTab->AddControl(new CSlider<int>(L"Box Color - Green", 0, 255, &gCvars.color_box_g));
	BoxColorTab->AddControl(new CSlider<int>(L"Box Color - Blue", 0, 255, &gCvars.color_box_b));

	COLORTabz.AddControl(BoxColorTab);
#pragma endregion
#pragma region BoxFillColor
	auto BoxFillColorTab = new CChild(0, 55, 240, L"╔Box-Fill (Enemy) Color╗");

	BoxFillColorTab->AddControl(new CSlider<int>(L"Box-Fill Color - Red", 0, 255, &gCvars.color_fill_box_r));
	BoxFillColorTab->AddControl(new CSlider<int>(L"Box-Fill Color - Green", 0, 255, &gCvars.color_fill_box_g));
	BoxFillColorTab->AddControl(new CSlider<int>(L"Box-Fill Color - Blue", 0, 255, &gCvars.color_fill_box_b));

	COLORTabz.AddControl(BoxFillColorTab);
#pragma endregion
#pragma region MenuOutlineColor
	auto MenuOutlineColorTab = new CChild(0, 110, 240, L"╔Menu-Outline Color╗");

	MenuOutlineColorTab->AddControl(new CSlider<int>(L"Menu-Outline Color - Red", 0, 255, &gCvars.color_menu_outline_r));
	MenuOutlineColorTab->AddControl(new CSlider<int>(L"Menu-Outline Color - Green", 0, 255, &gCvars.color_menu_outline_g));
	MenuOutlineColorTab->AddControl(new CSlider<int>(L"Menu-Outline Color - Blue", 0, 255, &gCvars.color_menu_outline_b));

	COLORTabz.AddControl(MenuOutlineColorTab);
#pragma endregion

#pragma region MenuBackColor
	auto MenuBackColorTab = new CChild(0, 165, 240, L"╔Menu-Background Color╗");

	MenuBackColorTab->AddControl(new CSlider<int>(L"Menu-Background Color - Red", 0, 255, &gCvars.color_menu_back_r));
	MenuBackColorTab->AddControl(new CSlider<int>(L"Menu-Background Color - Green", 0, 255, &gCvars.color_menu_back_g));
	MenuBackColorTab->AddControl(new CSlider<int>(L"Menu-Background Color - Blue", 0, 255, &gCvars.color_menu_back_b));

	COLORTabz.AddControl(MenuBackColorTab);
#pragma endregion
		AIMTabz.AddWindow(AimbotTabz);
		ESPERTabz.AddWindow(ESPTabz);
		MISERCTabz.AddWindow(MISCTabz);
		HVHERTabz.AddWindow(HVHTabz);
		COLTabz.AddWindow(COLORTabz);
#pragma endregion
		MenuTabz.AddWindow(MainTablist);
}

void Menu::Kill()
{}

void Menu::PaintTraverse()
{
	if (m_isVisible)
	{
		MenuTabz.Paint();

		if (m_AIMtabVisible)
			AIMTabz.Paint();

		if (m_ESPtabVisible)
			ESPERTabz.Paint();
	
		if (m_MISCtabVisible)
			MISERCTabz.Paint();

		if (m_HVHtabVisible)
			HVHERTabz.Paint();

		if (m_COLtabVisible)
			COLTabz.Paint();
	}	
}

void Menu::Click()
{
	if (m_AIMtabVisible)
		AIMTabz.Click();

	if (m_ESPtabVisible)
		ESPERTabz.Click();

	if (m_isVisible)
		MenuTabz.Click();

	if (m_MISCtabVisible)
		MISERCTabz.Click();

	if (m_HVHtabVisible)
		HVHERTabz.Click();

	if (m_COLtabVisible)
		COLTabz.Click();
}

void Menu::HandleInput(WPARAM vk)
{
	if (m_AIMtabVisible)
		AIMTabz.HandleInput(vk);

	if (m_ESPtabVisible)
		ESPERTabz.HandleInput(vk);

	if (m_isVisible)
		MenuTabz.HandleInput(vk);

	if (m_MISCtabVisible)
		MISERCTabz.HandleInput(vk);

	if (m_HVHtabVisible)
		HVHERTabz.HandleInput(vk);

	if (m_COLtabVisible)
		COLTabz.HandleInput(vk);
}

void Menu::Toggle()
{
	m_isVisible = !m_isVisible;
}