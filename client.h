#pragma once

#include <sstream>

namespace Gspeak
{
	enum class VoiceEffect {
		None,
		Radio,
		Water,
		Wall,
		Phone, //unused
		Helium, //unused
	};

	struct Client {
		int clientID;
		float pos[3];
		float volume_gm;
		float volume_ts;
		VoiceEffect effect;
		bool talking;
	};

	std::ostream& operator<<(std::ostream& os, Client const& arg);
	std::string to_string(Client const& arg);
}