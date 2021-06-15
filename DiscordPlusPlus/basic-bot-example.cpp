
#include "client.h"
#include <iostream>
#include <chrono>
#include <windows.h>
#include <psapi.h>

using DiscPPlus::Commands; // basic commands listed in libs
using DiscPPlus::Client; // main functions

std::chrono::steady_clock::time_point const start = std::chrono::steady_clock::now();;
DiscPPlus::Channel chan;

int main() {
	chan.id = "";
	std::string const token = ""; // our token
	Client c;
	c.establishConnection(token); // establish connection using token

	std::cout << std::string("Connection Lost Restart to continue...");
	return 0; // exits the program
}

std::string ftime(short int sec) {
	short int min = 00;
	int hour = 00;

	if (sec > 60) {
		min = sec / 60;
		sec -= min * 60;
	}
	if (min > 60) {
		hour = min / 60;
		min -= hour * 60;
	}
	const std::string secs = (std::stringstream() << std::setw(2) << std::setfill('0') << sec).str();
	const std::string mins = (std::stringstream() << std::setw(2) << std::setfill('0') << min).str();
	const std::string hours = (std::stringstream() << std::setw(2) << std::setfill('0') << hour).str();


	return hours + ":" + mins + ":" + secs;


}

std::vector<std::string> Args(std::string cmd) {
	std::stringstream ss(cmd);
	std::istream_iterator<std::string> begin(ss);
	std::istream_iterator<std::string> end;
	std::vector<std::string> vstrings(begin, end);
	std::copy(vstrings.begin(), vstrings.end(), std::ostream_iterator<std::string>(std::cout, "\n"));
	return vstrings;
}	

void DiscPPlus::Commands::OnMsg(DiscPPlus::Message msg, DiscPPlus::Bot bot) { // on message event teliing us that a message has been sent
	if (msg.content.rfind("$", 0) == 0) {
		std::vector<std::string> fullcmd = Args(msg.content.substr(1));
		std::string cmd = fullcmd[0];
		fullcmd.erase(fullcmd.begin());
		// all this stuff here should be pretty obvious
		if (cmd == "hi") {
			msg.channel.Send("hello! " + msg.author.mention + "! \n https://rb.gy/nnqou3", bot);
		}
		else if (cmd == "help") {
			msg.channel.Send("http://sparktonian.net/Secure/Filesharing/uploads/PrivateStorage/Capture.png", bot);
		}
		else if (cmd == "runtime") {
			std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

			msg.channel.Send("Elapsed Time in HH:MM:SS is: " + ftime(std::chrono::duration_cast<std::chrono::seconds>(end - start).count()), bot);
		}
		else if (cmd == "embed") {
			DiscPPlus::Embed embedmsg;
			embedmsg.SetAuthor("SparksCool", "", "https://cdn.discordapp.com/attachments/740770560149291089/845730338239938590/detective.png");
			embedmsg.SetTitle("Whats This?");
			embedmsg.SetColor(0xFDFD96);
			embedmsg.SetDesc("A Test Description???");
			embedmsg.AddField("A Field?", "and a value too!");
			embedmsg.AddField("A Second Field?", "and a second value too!");
			embedmsg.AddField("A Third Field?", "and a third value too!");
			embedmsg.SetFooter("Guess what we have a footer aswell!");
			msg.channel.SendEmbed(embedmsg, bot);
		}
		else if (cmd == "ram") {
			PROCESS_MEMORY_COUNTERS_EX pmc;
			GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc));
			const float virtualMemUsedByMe = pmc.PrivateUsage;
			msg.channel.Send("Current Memory Used is : " + std::to_string((virtualMemUsedByMe / (1024 * 1000))) + "MB", bot);

		}
		else if (cmd == "dm") {
			msg.author.CreateDM(bot);
			msg.author.channel.Send("DM Test!", bot);
		}
		else if (cmd == "smdm") {
			chan.Send("this was sent from a dm! Sender is: " + msg.author.name, bot);
		}
		else if (cmd == "cmd") {
			msg.channel.Send("command is: " + cmd, bot);
			int c = 0;
			if (c < fullcmd.size()) {


				while (c < fullcmd.size()) {
					msg.channel.Send("Arg[" + std::to_string(c) + "] is " + fullcmd[c], bot);
					c++;
				}
			}
		}
		else if (cmd == "guild") {
			DiscPPlus::Guild gld = msg.GetGuild(bot);
			msg.channel.Send("guild name is:" + gld.name + " with approx " + std::to_string(gld.memCount) + " members" , bot);
		}
		else if (cmd == "kick") {
			DiscPPlus::Guild gld = msg.GetGuild(bot);
			try {
				Kick(fullcmd[0], bot, gld.id);
				msg.channel.Send("<@!" + fullcmd[0] + "> has been kicked from" + gld.id + "!", bot);
			}
			catch (...) {
				msg.channel.Send("an error has occured please try again!", bot);
			}
		}
	}
}