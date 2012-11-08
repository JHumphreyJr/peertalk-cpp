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
			client->addDevice(event->device);
		break;
		case UE_DEVICE_REMOVE:
			client->removeDevice(event->device);
		break;
	}
}

Peertalk::Peertalk() :
	_listening(false),
	_devices()
{
}

int Peertalk::startListeningForDevices()
{
	//Subscribe for device connections
	int status = usbmuxd_subscribe(pt_usbmuxd_cb, this);
	if(status)
	{
		return -1;
	}
	
	_listening = true;

	return 0;
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

void Peertalk::addDevice(const usbmuxd_device_info_t& device)
{
	if(_devices.find(device.handle) == _devices.end())
		_devices.insert(DeviceMap::value_type(device.handle, Device::shared_ptr(new Device(device))));
}

void Peertalk::removeDevice(const usbmuxd_device_info_t& device)
{
	DeviceMap::iterator it = _devices.find(device.handle);

	if(it != _devices.end())
	{
		_devices.erase(it);
	}
}

Peertalk::~Peertalk()
{
	if(_listening)
	{
		usbmuxd_unsubscribe();
	}
}

}