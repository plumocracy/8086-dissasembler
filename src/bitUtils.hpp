#include <iostream>
#include <cstdint>
#include <cassert>
#include <stdexcept>

using u16 = uint16_t;
using u8 = char;

namespace bu {

// Returns a u8 with the bits in the given range (inclusive) as the most 
// signifigant bits.
u8 bitSpan(u8 byte, u8 start, u8 end) {
 	constexpr u8 hexBitMasks[8] = {
		0b00000000, 0b00000001, 0b00000011, 0b00000111, 
		0b00001111, 0b00011111, 0b00111111, 0b01111111
	};

	if (start > 7 || end > 7) {
		throw std::invalid_argument("argument out of range.");
	}

	u8 count = (end + 1) - start; 
	assert(count < 8);	

	u8 byteCopy = byte;
	
	// Shift the bit right by count to isolate
	// the desired bits
	byte >>= 7 - end;
	byte &= hexBitMasks[count];

	return byte;
}


// TODO: This is dumb.
std::bitset<8> printAsBits(u8 byte) {
	return std::bitset<8>(byte);
}
}
