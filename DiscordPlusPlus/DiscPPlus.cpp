#include "Client.h"
#include <iostream>
using DiscPPlus::Commands;
using DiscPPlus::Client;



int main() {
	std::string token = "Your Token Here";
	Client c;
	c.establishConnection(token);
	std::cout << std::string("Connection Lost Restart to continue...");
	return 0;
}

void DiscPPlus::Commands::OnMsg(std::string msg, std::string channel, DiscPPlus::bot bot) {
	if (msg == "$hi") {
		SendMsg("hello! <@!405894247745716224>! \n https://rb.gy/nnqou3", channel, bot);
	}
	else if (msg == "$help") {
		SendMsg("http://sparktonian.net/Secure/Filesharing/uploads/PrivateStorage/Capture.png", channel, bot);
	}
}