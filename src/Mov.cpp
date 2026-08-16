#include "Mov.hpp"

#include <cassert>

#include "TableData.hpp"

namespace ops {

std::string_view Mov::memModeToString() {
	switch(this->mode) {
		case MemMode::MEMORY_NO_DISP:     return "No Displacement (0)";
		case MemMode::MEMORY_8_BIT_DISP:  return "Mem Displacement, 8 bit (1)";
		case MemMode::MEMORY_16_BIT_DISP: return "Mem Displacement, 16 bit (2)";
		case MemMode::REGISTER:           return "Register Displacement (3)";
	}
}

std::string_view Mov::directionToString() {
	switch(this->direction) {
		case Direction::TO_REG:   return "TO_REG";
		case Direction::FROM_REG: return "FROM_REG";
	}
}

std::string Mov::ReconstructAsm() {
	std::string sv = "mov ";

	if (wide) {
		sv += std::string_view(regTableW[RegA]);
		sv += std::string_view(", ");
		sv += std::string_view(regTableW[RegB]);
	} else {
		sv += std::string_view(regTable[RegA]);
		sv += std::string_view(", ");
		sv += std::string_view(regTable[RegB]);
	}

	return sv;
}

void Mov::DecodeLow() {
	// This is the move opcode, if it doesnt equal this we're not able to handle it.
	assert(bu::bitSpan(low, 7, 2) == 0b00100010);

	wide = static_cast<bool>(bu::bitSpan(low, 0, 0));
	direction = static_cast<Direction>(bu::bitSpan(low, 1, 0));
}

void Mov::DecodeHigh() {
	// Mod - First 2 bits
	mode = static_cast<MemMode>(bu::bitSpan(high, 7, 6));

	// Reg - Middle 3 bits
	u8 reg = bu::bitSpan(high, 5, 3);

	// R/M - Last 3 bits
	u8 r_or_m = bu::bitSpan(high, 2, 0);

	// NOTE:(plum) This is a special case for 8086. 110 in r/m always sets mem
	// mode to 16 bit displacement.
	if (r_or_m == 0b00000110) {
		mode = MemMode::MEMORY_16_BIT_DISP;
	}

	this->RegB = reg;
	this->RegA = r_or_m;

	// std::cout << "Registers: " << std::endl;
	// std::cout << regTableW[reg] << ", " << regTableW[r_or_m]  << std::endl;
	// std::cout << "MemMode: " << this->memModeToString() << std::endl;
}
}
