#include "Protocol.hpp"

#include <boost/cstdint.hpp>

namespace peertalk
{

// This is what we send as the header for each frame.
typedef struct FrameHeader {
  // The version of the frame and protocol.
  uint32_t version;

  // Type of frame
  uint32_t type;

  // Unless zero, a tag is retained in frames that are responses to previous
  // frames. Applications can use this to build transactions or request-response
  // logic.
  uint32_t tag;

  // If payloadSize is larger than zero, *payloadSize* number of bytes are
  // following, constituting application-specific data.
  uint32_t payloadSize;

} FrameHeader_t;


}