#pragma once

#include "IntDef.hpp"
#include <bitset>


namespace bu {

// Returns a u8 with the bits in the given range (inclusive) as the most
// signifigant bits.
u8 bitSpan(u8 byte, u8 start, u8 end);

// TODO: This is dumb.
std::bitset<8> printAsBits(u8 byte);
}
