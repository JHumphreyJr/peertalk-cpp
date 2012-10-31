#include "Device.hpp"

#include <sstream>
#include <boost/assign.hpp>

namespace peertalk
{

std::map<uint16_t, std::string> Device::products = 
	boost::assign::map_list_of
		(0x1290, "iPhone")
		(0x1292, "iPhone 3G")
		(0x1294, "iPhone 3GS")
		(0x1297, "iPhone 4 GSM")
		(0x129c, "iPhone 4 CDMA")
		(0x12a0, "iPhone 4S")
		(0x12a8, "iPhone 5")
		(0x1291, "iPod touch")
		(0x1293, "iPod touch 2G")
		(0x1299, "iPod touch 3G")
		(0x129e, "iPod touch 4G")
		(0x129a, "iPad")
		(0x129f, "iPad 2 Wi-Fi")
		(0x12a2, "iPad 2 GSM")
		(0x12a3, "iPad 2 CDMA")
		(0x12a9, "iPad 2 R2")
		(0x12a4, "iPad 3 Wi-Fi")
		(0x12a5, "iPad 3 CDMA")
		(0x12a6, "iPad 3 Global")
		(0x129d, "Apple TV 2G")
		(0x12a7, "Apple TV 3G");

Device::Device(const usbmuxd_device_info_t& device) : 
	_valid(true),
	_device(device),
	_uuid(_device.uuid),
	//Lookup product name in the products map, If it does not exisit
	// then format a string with product_id. "Unknown Device (0x12a6)"
	_productName(products.find(_device.product_id) == products.end() ? 
		static_cast<std::ostringstream&>(std::ostringstream().seekp(0) << "Unknown Device (0x"  << std::hex << _device.product_id << ")").str() : 
		products[_device.product_id])
{
}

const std::string & Device::uuid() const
{
	return _uuid;
}

const std::string & Device::productName() const
{
	return _productName;
}

uint16_t Device::productID() const
{
	return _device.product_id;
}
	
std::ostream & operator<<(std::ostream & os, const Device& v)
{
	os << v.productName() << " [ " << v.uuid() << " ]";
	return os;
}

}