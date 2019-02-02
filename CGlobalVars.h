#include "SDK.h"

class CGlobalVariables
{
public:
	int iAimbotIndex = -1;
	
	float settings_switch;
	float iMenu_Pos_X = 16;
	float iMenu_Pos_Y = 32;
	float szsubstest;

	bool esptab;
	int aa_key;
	float aimbot_switch;
	bool aimbot_active;
	bool aimbot_waitforcharge;
	int aimbot_key;
	bool aimbot_hitscan;
	int aimbot_hitbox;
	bool aimbot_autoshoot;
	int aimbot_fov = 180;
	bool aimbot_silent;
	bool aimbot_zoomedonly;
	bool aimbot_ignore_cloak;
	int aimbot_smooth;
	int aimbot_smooth_amt;
	bool projectilaimbot;

	float triggerbot_switch;
	bool triggerbot_active;
	int triggerbot_key;
	bool triggerbot_headonly;
	bool triggerbot_autoairblast;
	int triggerbot_autoairblast_key;
	bool triggerbot_autoairblast_legit;
	bool triggerbot_autoairblast_silent;

	bool radarenable;
	int radar_posx, radar_posy, radar_width, bt_ticks;

	float esp_switch;
	bool esp_active;
	bool esp_objects;
	int esp_health_buildings;
	bool esp_weapons;
	bool esp_view_lines;
	bool esp_box_buildings;
	bool esp_buildings;
	bool esp_enemyonly;
	bool esp_box;
	int esp_box_thickness = 1;
	bool esp_name;
	bool esp_class;
	bool esp_removeDisguise;
	bool esp_removeCloak;
	bool esp_removeTaunt;
	bool esp_playerCond_enabled;
	int esp_playerCond;
	bool esp_health_enabled;
	int esp_health;
	bool esp_bones_enabled;
	int esp_bones;
	bool esp_face;
	bool esp_crosshair;
	bool esp_local;
	bool esp_snaplineson;
	int esp_snaplines;


	bool sky_changer;
	int sky_changer_value;

	float aa_switch;
	int aa_pitch;
	float aa_pitch_fakeup;
	float aa_pitch_fakedown;
	int aa_yaw;
	int aa_fake_yaw;
	int aa_spinspeed;
	float aa_yaw_staticjitter;
	float aa_yaw_right;
	float aa_yaw_left;
	bool aa_enabled;
	bool aa_pitch_enabled;
	bool aa_yaw_enabled;
	bool aa_resolver;
	bool fakeYAW;

	float removecond_switch;
	bool removecond_enabled;
	int removecond_value;
	int removecond_key;
	bool removecond_autoinstantcap;
	bool removecond_instantweaponswitch;
	bool removecond_automedkit;
	bool removecond_stickyspam;

	float misc_switch;
	bool misc_thirdPerson;
	bool misc_bunnyhop;
	bool misc_autostrafe;
	bool misc_autobackstab;
	bool misc_noisemaker_spam;
	bool misc_noscope;
	bool misc_chatspam_enabled;
	int misc_chatspam_selection;
	int misc_chatspam_newline;
	bool misc_cleanScreenshot;
	int misc_chatspam_delay;
	bool misc_killsay_enabled;
	int misc_killsay_selection;
	int esp_box_selection;
	bool misc_roll_speedhack;
	bool misc_wowsweet;
	bool misc_voice;
	int misc_fov = 90;// = 90; // why the fuck would u start at 70 - plasma // someone on steamcommunity said default was 70 - wolfie
	int misc_viewmodel_fov = 70;// = 70;
	bool misc_no_push;
	bool misc_nozoom;
	int backtrack_tick = 12;
	bool backtrack;
	bool viewfov;
	bool backtrackshow;
	bool misc_lagger;
	bool fakelag;
	int fakelag_value;
	int misc_laggeramt = 1;
	int misc_lagkey;
	bool misc_bighead;
	int misc_torsosize = 1;
	int misc_handsize = 1;
	int misc_bigheadsize;

	int storedFOV;

	int radartype;


	/*Color changer*/
	int color_box_r = 255;
	int color_box_g = 255;
	int color_box_b = 255;

	int color_fill_box_r = 255;
	int color_fill_box_g = 255;
	int color_fill_box_b = 255;

	
	int color_menu_outline_r = 0;
	int color_menu_outline_g = 100;
	int color_menu_outline_b = 0;
	int color_menu_outline_alfa = 135;

	int color_menu_back_r = 40;
	int color_menu_back_g = 40;
	int color_menu_back_b = 40;
	int color_menu_back_alfa = 255;

	int color_skeleton;	


	float playerlist_switch;
	float PlayerMode[64] = {
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	};
};

class COffsets
{
public:
	int iKeyEventOffset = 20, iCreateMoveOffset = 21, iPaintTraverseOffset = 41, iFrameStageNotifyOffset = 35;

	DWORD LoadFromBuffer;
	DWORD KeyValues;

	void SafetyCheck(void* Pointer)
	{
		if (Pointer)
			return;

		exit(EXIT_FAILURE);
	}
	inline void SafetyCheck(DWORD Pointer)
	{
		return SafetyCheck((void*)Pointer);
	}
};