#include "Client.h"
#include <iostream>


int main() {
	DiscPPlus::Client c;
	std::cout << std::string{ c.establishConnection() ? "true" : "false" };
	return 0;
}