#include "Peertalk.hpp"
#include <iostream>

namespace peertalk
{
/**
usbmuxd callback
*/
void pt_usbmuxd_cb(const usbmuxd_event_t *event, void *user_data)
{
	Peertalk *client = static_cast<Peertalk*>(user_data);

	switch(event->event)
	{
		case UE_DEVICE_ADD:
			//TODO: device added
		break;
		case UE_DEVICE_REMOVE:
			//TODO: device removed
		break;
	}

	std::cout << (event->event == UE_DEVICE_ADD ? "Added: \n" : "Removed: \n");
	client->printDevice(event->device);
}

Peertalk::Peertalk() :
	_listening(false)
{

}

void Peertalk::startListeningForDevices()
{
	//Subscribe for device connections
	int status = usbmuxd_subscribe(pt_usbmuxd_cb, this);
	if(status)
	{
		throw;
	}
	_listening = true;
}

void Peertalk::stopListeningForDevices()
{
	if(_listening)
	{
		//Always returns 0
		usbmuxd_unsubscribe();
		_listening = false;
	}
}

bool Peertalk::isListening()
{
	return _listening;
}

void Peertalk::printDevice(const usbmuxd_device_info_t& device)
{
	std::cout << device.uuid << " - " << device.product_id << std::endl;
}

Peertalk::~Peertalk()
{
	if(_listening)
	{
		usbmuxd_unsubscribe();
	}
}

}