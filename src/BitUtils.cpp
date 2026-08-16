#include "BitUtils.hpp"

#include <cassert>

namespace bu {

u8 bitSpan(u8 byte, u8 start, u8 end) {
    if (start > end) { 
			u8 t = start; 
			start = end; 
			end = t; 
		}
    if (end > 7) end = 7;
    unsigned length = (unsigned)(end - start + 1);
    u8 mask = (u8)((1u << length) - 1u);
    return (byte >> start) & mask;
}


std::bitset<8> printAsBits(u8 byte) {
	return std::bitset<8>(byte);
}
}
