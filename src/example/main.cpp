#include <iostream>

#include <Peertalk.hpp>

int main()
{
	std::cout << "Peer-Talk C++ Example\nAuthor: Joseph Humphrey\nBased on the work of: Rasmus Andersson\n\n";
	std::cout << "Looking for devices" << std::endl;

	peertalk::Peertalk client;
	
	client.startListeningForDevices();
	while(client.isListening())
	{
		//waiting for device
		usleep(100);
	}

	return 0;
}