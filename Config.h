#pragma once
#include <Windows.h>
#include <unordered_map>
#include <fstream>
#include <vector>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include "json.h"
#include "SDK.h"
#include "ESP.h"

class GConfig
{
public:
	void GetVal(Json::Value & config, int * setting);
	void GetVal(Json::Value & config, bool * setting);
	void GetVal(Json::Value & config, float * setting);
	void GetVal(Json::Value & config, char ** setting);
	void GetVal(Json::Value & config, char * setting);
	void GetVal(Json::Value & config, ImVec4 * setting, bool loadAlpha = false);
	bool exists_test3(const std::string & name);
	bool LoadSettings(const char * path);
	bool SaveSettings(const char * path);
};

extern GConfig gConfig;