#include <iostream>
#include <signal.h>
#include <Peertalk.hpp>

bool m_running = true;

void sig_interrupt(int sig)
{
	m_running = false;
}

int main()
{
	std::cout << "Peer-Talk C++ Example\nAuthor: Joseph Humphrey\n\n";
	std::cout << "Looking for devices" << std::endl;

	peertalk::Peertalk client;
	
	client.startListeningForDevices();
	signal(SIGINT, sig_interrupt);

	while(m_running && client.isListening())
	{
		//waiting for device
		usleep(100);
	}

	std::cout << "Done!" << std::endl;

	return 0;
}