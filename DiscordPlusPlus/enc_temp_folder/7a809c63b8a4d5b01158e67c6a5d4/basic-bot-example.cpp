#include "client.h"
#include <iostream>
#include <chrono>
#include "json.hpp"
using DiscPPlus::Commands; // basic commands listed in libs
using DiscPPlus::Client; // main functions

auto start = std::chrono::steady_clock::now();;

int main() {
	std::string token = "ODQyNDk2ODY0MjA4Mjg5ODMy.YJ2KWQ.0qEZQPcSDSXq8xywhY3hwg8rWBY"; // our token
	start = std::chrono::steady_clock::now();
	Client c;
	try {
		c.establishConnection(token); // establish connection using token
	}
	catch (nlohmann::detail::type_error) {
		// do nothing
	}

	std::cout << std::string("Connection Lost Restart to continue...");
	return 0; // exits the program
}

std::string ftime(int sec) {
	int min = 00;
	int hour = 00;

	if (sec > 60) {
		min = sec / 60;
		sec -= min * 60;
	}
	if (hour > 60) {
		hour = min / 60;
		min -= hour * 60;
	}
	std::string secs = (std::stringstream() << std::setw(2) << std::setfill('0') << sec).str();
	std::string mins = (std::stringstream() << std::setw(2) << std::setfill('0') << min).str();
	std::string hours = (std::stringstream() << std::setw(2) << std::setfill('0') << hour).str();


	return hours + ":" + mins + ":" + secs;


}

void DiscPPlus::Commands::OnMsg(DiscPPlus::Message msg, DiscPPlus::Bot bot) { // on message event teliing us that a message has been sent
	// all this stuff here should be pretty obvious
	if (msg.content == "$hi") {
		msg.channel.Send("hello! "+ msg.author.mention + "! \n https://rb.gy/nnqou3", bot); 
	}
	else if (msg.content == "$help") { 
		msg.channel.Send("http://sparktonian.net/Secure/Filesharing/uploads/PrivateStorage/Capture.png", bot);
	}
	else if (msg.content == "$runtime") {
		auto end = std::chrono::steady_clock::now();
		
		msg.channel.Send("Elapsed Time in HH:MM:SS is: " + ftime(std::chrono::duration_cast<std::chrono::seconds>(end - start).count()), bot);
	}
}