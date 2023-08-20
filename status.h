#pragma once

#include "defines.h"
#include <sstream>

namespace Gspeak
{
	enum Command
	{
		Failure = -2,
		Success = -1,
		Clear,
		Rename,
		ForceMove,
		ForceKick
	};

	struct RadioEffect {
		short downsampler;
		short distortion;
		float volume;
		float noise;
	};

	struct WaterEffect {

	};

	struct WallEffect {

	};

	struct Status {
		int clientID;
		bool inChannel;
		char name[NAME_BUF];
		short tslibV;
		short gspeakV;
		float upward[3];
		float forward[3];
		RadioEffect radioEffect;
		//char password[PASS_BUF];
		bool status;
		bool talking;
		Command command;
		char commandArgs[CMD_ARGS_BUF];

		//char channelName[NAME_BUF];
		//int channelId;
	};

	std::ostream& operator<<(std::ostream& os, Status const& arg);;
	std::string to_string(Status const& arg);
}