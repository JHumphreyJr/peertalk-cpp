#include <map>
#include <string>
#include <iostream>
#include <usbmuxd.h>

namespace peertalk
{
	/**
	Represents an iOS device detected by usbmuxd. This class
	can be used to retrieve info and initiate a TCP session 
	with the iOS device.
	*/
	class Device
	{
	public:
		/**
		Default constructor for the class.
		*
		@param device The underlying usbmuxd device.
		*/
		explicit Device(const usbmuxd_device_info_t& device);

		/**
		Returns the 40 character UUID associated with the device.
		*
		@return The devices UUID.
		*/
		const std::string & uuid() const;

		/**
		Returns the name of the product.
		*
		@return The print friendly version of the product name.
		*/
		const std::string & productName() const;

		/**
		Returns the product ID. This is used to determine the product name.
		*
		@return The 16 bit product ID.
		*/
		uint16_t productID() const;

	private:
		bool _valid;
		const usbmuxd_device_info_t _device;
		const std::string _uuid;
		const std::string _productName;

		static std::map<uint16_t, std::string> products;

		friend std::ostream & operator<<(std::ostream & os, const Device& v);
	};
}