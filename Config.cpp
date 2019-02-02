#include "Config.h"
#include <string>
#include "SDK.h"
#include <sstream>

GConfig gConfig;

void GConfig::GetVal(Json::Value &config, int* setting)
{
	if (config.isNull())
		return;

	*setting = config.asInt();
}

void GConfig::GetVal(Json::Value &config, bool* setting)
{
	if (config.isNull())
		return;

	*setting = config.asBool();
}

void GConfig::GetVal(Json::Value &config, float* setting)
{
	if (config.isNull())
		return;

	*setting = config.asFloat();
}
void GConfig::GetVal(Json::Value &config, char** setting)
{
	if (config.isNull())
		return;

	*setting = strdup(config.asCString());
}

void GConfig::GetVal(Json::Value &config, char* setting)
{
	if (config.isNull())
		return;

	strcpy(setting, config.asCString());
}

void GConfig::GetVal(Json::Value &config, ImVec4* setting, bool loadAlpha)
{
	if (config.isNull())
		return;

	GetVal(config["r"], &setting->x);
	GetVal(config["g"], &setting->y);
	GetVal(config["b"], &setting->z);
	if (loadAlpha)
		GetVal(config["a"], &setting->w);
}

template <typename Ord, Ord(*lookupFunction)(std::string)>
void GetOrdinal(Json::Value& config, Ord* setting)
{
	if (config.isNull())
		return;

	Ord value;
	if (config.isString())
		value = lookupFunction(config.asString());
	else
		value = (Ord)config.asInt();

	*setting = value;
}
inline bool GConfig::exists_test3(const std::string& name)
{
	struct stat buffer;
	return (stat(name.c_str(), &buffer) == 0);
}

bool GConfig::LoadSettings(const char* path)
{
	if (!exists_test3(path))
		return false;
	Json::Value settings;
	std::ifstream configDoc(path, std::ifstream::binary);
	configDoc >> settings;


	auto section = "Aimbot";
	GetVal(settings[section]["Enabled"], &gCvars.aimbot_active);
	GetVal(settings[section]["Silent"], &gCvars.aimbot_silent);
	GetVal(settings[section]["Autoshoot"], &gCvars.aimbot_autoshoot);
	GetVal(settings[section]["WaitForChargeAmby"], &gCvars.aimbot_waitforcharge);
	GetVal(settings[section]["Hitscan"], &gCvars.aimbot_hitscan);
	GetVal(settings[section]["Aimkey"], &gCvars.aimbot_key);
	GetVal(settings[section]["Hitbox"], &gCvars.aimbot_hitbox);
	GetVal(settings[section]["Smooth"], &gCvars.aimbot_smooth);
	GetVal(settings[section]["SmoothAMT"], &gCvars.aimbot_smooth_amt);
	GetVal(settings[section]["FovAMT"], &gCvars.aimbot_fov);
	GetVal(settings[section]["IgnoreCloak"], &gCvars.aimbot_ignore_cloak);
	GetVal(settings[section]["ZoomedOnly"], &gCvars.aimbot_zoomedonly);
	GetVal(settings[section]["Backtrack"], &gCvars.backtrack);
	GetVal(settings[section]["BTticks"], &gCvars.bt_ticks);

	section = "Triggerbot";
	GetVal(settings[section]["Enabled"], &gCvars.triggerbot_active);
	GetVal(settings[section]["TriggerKey"], &gCvars.triggerbot_key);
	GetVal(settings[section]["HeadOnly"], &gCvars.triggerbot_headonly);
	GetVal(settings[section]["AutoAirblast"], &gCvars.triggerbot_autoairblast);
	GetVal(settings[section]["AirblastKey"], &gCvars.triggerbot_autoairblast_key);
	GetVal(settings[section]["AirblastLegit"], &gCvars.triggerbot_autoairblast_legit);
	GetVal(settings[section]["AirblastSilent"], &gCvars.triggerbot_autoairblast_silent);

	section = "HVH";
	GetVal(settings[section]["Enabled"], &gCvars.aa_enabled);
	GetVal(settings[section]["Pitch"], &gCvars.aa_pitch_enabled);
	GetVal(settings[section]["PitchType"], &gCvars.aa_pitch);
	GetVal(settings[section]["Yaw"], &gCvars.aa_yaw_enabled);
	GetVal(settings[section]["YawType"], &gCvars.aa_yaw);
	GetVal(settings[section]["AAkey"], &gCvars.aa_key);
	GetVal(settings[section]["SpinSpeed"], &gCvars.aa_spinspeed);
	GetVal(settings[section]["Resolver"], &gCvars.aa_resolver);
	GetVal(settings[section]["FAKE"], &gCvars.fakeYAW);
	GetVal(settings[section]["FAKEType"], &gCvars.aa_fake_yaw);


	section = "ESP";
	GetVal(settings[section]["Enabled"], &gCvars.esp_active);
	GetVal(settings[section]["Enable Snaplines"], &gCvars.esp_snaplineson);
	GetVal(settings[section]["SnaplinesSINC"], &gCvars.esp_snaplines);
	GetVal(settings[section]["Object ESP"], &gCvars.esp_buildings);
	GetVal(settings[section]["BoxBuildings"], &gCvars.esp_box_buildings);
	GetVal(settings[section]["Weapon"], &gCvars.esp_weapons);
	GetVal(settings[section]["EnemiesOnly"], &gCvars.esp_enemyonly);
	GetVal(settings[section]["Box"], &gCvars.esp_box);	
	GetVal(settings[section]["BoxSelection"], &gCvars.esp_box_selection);
	GetVal(settings[section]["Name"], &gCvars.esp_name);
	GetVal(settings[section]["Class"], &gCvars.esp_class);
	GetVal(settings[section]["CondEnabled"], &gCvars.esp_playerCond_enabled);
	GetVal(settings[section]["CondSelection"], &gCvars.esp_playerCond);
	GetVal(settings[section]["AntiCloak"], &gCvars.esp_removeCloak);
	GetVal(settings[section]["AntiDisguise"], &gCvars.esp_removeDisguise);
	GetVal(settings[section]["AntiTaunt"], &gCvars.esp_removeTaunt);
	GetVal(settings[section]["HealthEnabled"], &gCvars.esp_health_enabled);
	GetVal(settings[section]["HealthSelection"], &gCvars.esp_health);
	GetVal(settings[section]["BonesEnabled"], &gCvars.esp_bones_enabled);
	GetVal(settings[section]["BonesSelection"], &gCvars.esp_bones);
	GetVal(settings[section]["HappyFace"], &gCvars.esp_face);
	GetVal(settings[section]["Skychanger"], &gCvars.sky_changer_value);
	GetVal(settings[section]["Crosshair"], &gCvars.esp_crosshair);
	GetVal(settings[section]["Objects"], &gCvars.esp_objects);
	GetVal(settings[section]["HealthBuildings"], &gCvars.esp_health_buildings);
	GetVal(settings[section]["Radar"], &gCvars.radarenable);
	GetVal(settings[section]["RadarPosx"], &gCvars.radar_posx);
	GetVal(settings[section]["RadarPosy"], &gCvars.radar_posy);
	GetVal(settings[section]["RadarSize"], &gCvars.radar_width);
	GetVal(settings[section]["RadarType"], &gCvars.radartype);
	GetVal(settings[section]["Viewlines"], &gCvars.esp_view_lines);

	section = "Misc";
	GetVal(settings[section]["BunnyHop"], &gCvars.misc_bunnyhop);
	GetVal(settings[section]["AutoStrafe"], &gCvars.misc_autostrafe);
	GetVal(settings[section]["Thirdperson"], &gCvars.misc_thirdPerson);
	GetVal(settings[section]["AutoBackstab"], &gCvars.misc_autobackstab);
	GetVal(settings[section]["Noisemaker Spam"], &gCvars.misc_noisemaker_spam);
	GetVal(settings[section]["No Scope"], &gCvars.misc_noscope);
	GetVal(settings[section]["No Zoom"], &gCvars.misc_nozoom);
	GetVal(settings[section]["No Push"], &gCvars.misc_no_push);
	GetVal(settings[section]["Chat Spam"], &gCvars.misc_chatspam_enabled);
	GetVal(settings[section]["Chat SpamType"], &gCvars.misc_chatspam_selection);
	GetVal(settings[section]["Delay"], &gCvars.misc_chatspam_delay);
	GetVal(settings[section]["Newlines"], &gCvars.misc_chatspam_newline);
	GetVal(settings[section]["Kill Say"], &gCvars.misc_killsay_enabled);
	GetVal(settings[section]["Kill SayType"], &gCvars.misc_killsay_selection);
	GetVal(settings[section]["Voice Menu Spam"], &gCvars.misc_voice);
	GetVal(settings[section]["Roll Speedhack"], &gCvars.misc_roll_speedhack);
	GetVal(settings[section]["Big Heads"], &gCvars.misc_bighead);
	GetVal(settings[section]["HeadSize"], &gCvars.misc_bigheadsize);
	GetVal(settings[section]["TorsoSize"], &gCvars.misc_torsosize);
	GetVal(settings[section]["HandSize"], &gCvars.misc_handsize);
	GetVal(settings[section]["Clean Screenshot"], &gCvars.misc_cleanScreenshot);
	GetVal(settings[section]["Field of View"], &gCvars.misc_fov);
	GetVal(settings[section]["Viewmodel FOV"], &gCvars.misc_viewmodel_fov);

	section = "Colors";
	GetVal(settings[section]["Box Color - Red"], &gCvars.color_box_r);
	GetVal(settings[section]["Box Color - Green"], &gCvars.color_box_g);
	GetVal(settings[section]["Box Color - Blue"], &gCvars.color_box_b);
	GetVal(settings[section]["Box-Fill Color - Red"], &gCvars.color_fill_box_r);
	GetVal(settings[section]["Box-Fill Color - Green"], &gCvars.color_fill_box_g);
	GetVal(settings[section]["Box-Fill Color - Blue"], &gCvars.color_fill_box_b);
	


	return true;
}

bool GConfig::SaveSettings(const char* path)
{
	try
	{
		Json::Value settings;
		Json::StyledWriter styledWriter;
		
		auto section = "Aimbot";
		settings[section]["WaitForChargeAmby"] = gCvars.aimbot_waitforcharge;
		settings[section]["Enabled"] = gCvars.aimbot_active;
		settings[section]["Silent"] = gCvars.aimbot_silent;
		settings[section]["Autoshoot"] = gCvars.aimbot_autoshoot;
		settings[section]["Hitscan"] = gCvars.aimbot_hitscan;
		settings[section]["Aimkey"] = gCvars.aimbot_key;
		settings[section]["Hitbox"] = gCvars.aimbot_hitbox;
		settings[section]["Smooth"] = gCvars.aimbot_smooth;
		settings[section]["SmoothAMT"] = gCvars.aimbot_smooth_amt;
		settings[section]["FovAMT"] = gCvars.aimbot_fov;
		settings[section]["IgnoreCloak"] = gCvars.aimbot_ignore_cloak;
		settings[section]["ZoomedOnly"] = gCvars.aimbot_zoomedonly;
		settings[section]["Backtrack"], &gCvars.backtrack;
		settings[section]["BTticks"] = gCvars.bt_ticks;

		section = "Triggerbot";
		settings[section]["Enabled"] = gCvars.triggerbot_active;
		settings[section]["TriggerKey"] = gCvars.triggerbot_key;
		settings[section]["HeadOnly"] = gCvars.triggerbot_headonly;
		settings[section]["AutoAirblast"] = gCvars.triggerbot_autoairblast;
		settings[section]["AirblastKey"] = gCvars.triggerbot_autoairblast_key;
		settings[section]["AirblastLegit"] = gCvars.triggerbot_autoairblast_legit;
		settings[section]["AirblastSilent"] = gCvars.triggerbot_autoairblast_silent;


		section = "ESP";
		settings[section]["Enabled"] = gCvars.esp_active;
		settings[section]["Enable Snaplines"], gCvars.esp_snaplineson;
		settings[section]["SnaplinesSINC"], gCvars.esp_snaplines;
		settings[section]["Local"] = gCvars.esp_local;
		settings[section]["Object ESP"] = gCvars.esp_buildings;
		settings[section]["Weapon"] = gCvars.esp_weapons;
		settings[section]["EnemiesOnly"] = gCvars.esp_enemyonly;
		settings[section]["Box"] = gCvars.esp_box;
		settings[section]["BoxBuildings"] = gCvars.esp_box_buildings;
		settings[section]["BoxSelection"] = gCvars.esp_box_selection;
		settings[section]["Name"] = gCvars.esp_name;
		settings[section]["Class"] = gCvars.esp_class;
		settings[section]["CondEnabled"] = gCvars.esp_playerCond_enabled;
		settings[section]["CondSelection"] = gCvars.esp_playerCond;
		settings[section]["AntiCloak"] = gCvars.esp_removeCloak;
		settings[section]["AntiDisguise"] = gCvars.esp_removeDisguise;
		settings[section]["AntiTaunt"] = gCvars.esp_removeTaunt;
		settings[section]["HealthEnabled"] = gCvars.esp_health_enabled;
		settings[section]["HealthSelection"] = gCvars.esp_health;
		settings[section]["BonesEnabled"] = gCvars.esp_bones_enabled;
		settings[section]["BonesSelection"] = gCvars.esp_bones;
		settings[section]["HappyFace"] = gCvars.esp_face;
		settings[section]["Skychanger"] = gCvars.sky_changer_value;
		settings[section]["Crosshair"] = gCvars.esp_crosshair;
		settings[section]["Objects"] = gCvars.esp_objects;
		settings[section]["HealthBuildings"] = gCvars.esp_health_buildings;
		settings[section]["Radar"] = gCvars.radarenable;
		settings[section]["RadarPosx"] = gCvars.radar_posx;
		settings[section]["RadarPosy"] = gCvars.radar_posy;
		settings[section]["RadarSize"] = gCvars.radar_width;
		settings[section]["RadarType"] = gCvars.radartype;
		settings[section]["Viewlines"] = gCvars.esp_view_lines;
		
		section = "Misc";
		settings[section]["BunnyHop"], gCvars.misc_bunnyhop;
		settings[section]["AutoStrafe"], gCvars.misc_autostrafe;
		settings[section]["Thirdperson"], gCvars.misc_thirdPerson;
		settings[section]["AutoBackstab"], gCvars.misc_autobackstab;
		settings[section]["Noisemaker Spam"], gCvars.misc_noisemaker_spam;
		settings[section]["No Scope"], gCvars.misc_noscope;
		settings[section]["No Zoom"], gCvars.misc_nozoom;
		settings[section]["No Push"], gCvars.misc_no_push;
		settings[section]["Chat Spam"], gCvars.misc_chatspam_enabled;
		settings[section]["Chat SpamType"], gCvars.misc_chatspam_selection;
		settings[section]["Delay"], gCvars.misc_chatspam_delay;
		settings[section]["Newlines"], gCvars.misc_chatspam_newline;
		settings[section]["Kill Say"], gCvars.misc_killsay_enabled;
		settings[section]["Kill SayType"], gCvars.misc_killsay_selection;
		settings[section]["Voice Menu Spam"], gCvars.misc_voice;
		settings[section]["Roll Speedhack"], gCvars.misc_roll_speedhack;
		settings[section]["Big Heads"], gCvars.misc_bighead;
		settings[section]["HeadSize"], gCvars.misc_bigheadsize;
		settings[section]["TorsoSize"], gCvars.misc_torsosize;
		settings[section]["HandSize"], gCvars.misc_handsize;
		settings[section]["Clean Screenshot"], gCvars.misc_cleanScreenshot;
		settings[section]["Field of View"], gCvars.misc_fov;
		settings[section]["Viewmodel FOV"], gCvars.misc_viewmodel_fov;
		
		section = "HVH";
		settings[section]["Enabled"], gCvars.aa_enabled;
		settings[section]["Pitch"], gCvars.aa_pitch_enabled;
		settings[section]["PitchType"], gCvars.aa_pitch;
		settings[section]["Yaw"], gCvars.aa_yaw_enabled;
		settings[section]["YawType"], gCvars.aa_yaw;
		settings[section]["AAkey"], gCvars.aa_key;
		settings[section]["SpinSpeed"], gCvars.aa_spinspeed;
		settings[section]["Resolver"], gCvars.aa_resolver;
		settings[section]["FAKE"], gCvars.fakeYAW;
		settings[section]["FAKEType"], gCvars.aa_fake_yaw;

		section = "Colors";
		settings[section]["Box Color - Red"] = gCvars.color_box_r;
		settings[section]["Box Color - Green"] = gCvars.color_box_g;
		settings[section]["Box Color - Blue"] = gCvars.color_box_b;
		settings[section]["Box-Fill Color - Red"] = gCvars.color_fill_box_r;
		settings[section]["Box-Fill Color - Green"] = gCvars.color_fill_box_g;
		settings[section]["Box-Fill Color - Blue"] = gCvars.color_fill_box_b;

		std::ofstream(path) << styledWriter.write(settings);
		return true;
	}
	catch (...)
	{
		return false;
	}
}