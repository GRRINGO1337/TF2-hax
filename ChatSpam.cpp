#include "ChatSpam.h"
#include "Util.h"

CChatSpam gChatSpam;

void CChatSpam::Run(CBaseEntity* pLocal, CUserCmd* pCommand)
{
	if (!gCvars.misc_chatspam_enabled)
		return;

	int spam_source = gCvars.misc_chatspam_selection;
	static int safety_ticks = 0;
	static int last_source = 0;
	static float last_message = 0;
	if ((int)spam_source != last_source)
	{
		safety_ticks = 300;
		last_source = (int)spam_source;
	}
	if (safety_ticks > 0)
	{
		safety_ticks--;
		return;
	}
	else
	{
		safety_ticks = 0;
	}

	const std::vector<std::string>* source = nullptr;
	switch (spam_source)
	{
	case 1:
		source = &ChatSpams::builtin_hackname; break;
	case 2:
		source = &ChatSpams::builtin_lmaobox; break;
	case 3:
		source = &ChatSpams::builtin_lithium; break;
	case 4:
		source = &ChatSpams::builtin_cathook; break;
	case 5: //Empty lines
		source = &ChatSpams::builtin_empty; break;
	case 6:
		source = &ChatSpams::builtin_speedhook; break;
	case 7:
		source = &ChatSpams::builtin_freelbox; break;
	case 8:
		source = &ChatSpams::builtin_catbot; break;
	case 9:
		source = &ChatSpams::builtin_dumpsterfire; break;
	default:
		return;
	}
	if (!source || !source->size()) return;
	if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - last_spam_point).count() > gCvars.misc_chatspam_delay)
	{

		if (current_index >= source->size()) current_index = 0;
		std::string spamString = source->at(current_index);
		std::string msg;
		msg.append("say ");
		if (gCvars.misc_chatspam_newline)//\x0D
		{
			msg.append(" ");
			msg.append(repeat(gCvars.misc_chatspam_newline, "\x0D"));
		}
		msg.append(spamString);

		gInts.Engine->ClientCmd(msg.c_str());
		current_index++;

		last_spam_point = std::chrono::system_clock::now();
	}
}