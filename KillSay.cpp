#include "KillSay.h"

CKillSay gKillSay;


void CKillSay::InitKillSay()
{
	gInts.EventManager->AddListener(this, "player_death", false);
	wasEventInitialized = true;
}

void CKillSay::FireGameEvent(IGameEvent *event)
{
	if (strcmp(event->GetName(), "player_death") || !gCvars.misc_killsay_selection || !gCvars.misc_killsay_enabled)
		return;

	int vid = event->GetInt("userid");
	int kid = event->GetInt("attacker");
	if (kid == vid) return;

	const std::vector<std::string>* source = nullptr;
	std::string msg;
	msg.append("say ");

	if (gCvars.misc_killsay_selection == 1)
		source = &KillSay::niggerhook;
	else if (gCvars.misc_killsay_selection == 2)
		source = &KillSay::ncc;
	else
		source = &killsayFile.lines;

	msg.append(source->at(rand() % source->size()));

	player_info_t pInfo;
	if (!gInts.Engine->GetPlayerInfo(kid, &pInfo))
		return;
	
	const int iBuffer = 256;
	char szCommand[iBuffer];
	if (gCvars.misc_killsay_enabled)
		sprintf_s(szCommand, iBuffer, msg.c_str(), pInfo.name);

	gInts.Engine->ClientCmd(szCommand);
}