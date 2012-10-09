#ifndef PEERTALK_HPP
#define PEERTALK_HPP

#include <usbmuxd.h>

namespace peertalk
{

/**
The Peertalk client that listens for devices
and initiates connections.
*/
class Peertalk
{
public:
	Peertalk();
	/**
	Start listening for device connections
	*
	@discussion Devices already connected will trigger a callback
	*/
	void startListeningForDevices();

	/**
	Stop listening for device connections
	*/
	void stopListeningForDevices();

	/**
	Checks to see if the Peertalk client is listening
	for devices
	*
	@return true if listening
	*/
	bool isListening();
	~Peertalk();

private:
	bool _listening;

	Peertalk(const Peertalk& other);
	Peertalk& operator= (const Peertalk& other);

	void printDevice(const usbmuxd_device_info_t& device);
	friend void pt_usbmuxd_cb(const usbmuxd_event_t *event, void *user_data);
};

}

#endif //PEERTALK_HPP