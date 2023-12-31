#include "status.h"

namespace Gspeak
{
	std::ostream& operator<<(std::ostream& os, Status const& arg)
	{
		os << "clientID = " << arg.clientID << '\n'
			<< "inChannel = " << arg.inChannel << '\n'
			<< "name = " << arg.name << '\n'
			<< "tslibV = " << arg.tslibV << '\n'
			<< "gspeakV = " << arg.gspeakV << '\n'
			<< "radio_downsampler = " << arg.radioEffect.downsampler << '\n'
			<< "radio_distortion = " << arg.radioEffect.distortion << '\n'
			<< "radio_volume = " << arg.radioEffect.volume << '\n'
			<< "radio_volume_noise = " << arg.radioEffect.noise << '\n'
			<< "water_scale = " << arg.waterEffect.scale << '\n'
			<< "water_smooth = " << arg.waterEffect.smooth << '\n'
			<< "water_boost = " << arg.waterEffect.boost << '\n'
			<< "wall_scale = " << arg.wallEffect.scale << '\n'
			<< "wall_smooth = " << arg.wallEffect.smooth << '\n'
			<< "wall_boost = " << arg.wallEffect.boost << '\n'
			<< "upward = " << arg.upward[0] << ' ' << arg.upward[1] << ' ' << arg.upward[2] << '\n'
			<< "forward = " << arg.forward[0] << ' ' << arg.forward[1] << ' ' << arg.forward[2] << '\n'
			<< "status = " << arg.status << '\n'
			<< "talking = " << arg.talking << '\n'
			<< "command = " << (int)arg.command << '\n'
			<< "commandArgs = " << arg.commandArgs << '\n';
		return os;
	}

	std::string to_string(Status const& arg)
	{
		std::ostringstream ss;
		ss << arg;
		return std::move(ss).str();  // enable efficiencies in c++17
	}
}