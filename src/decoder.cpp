#include <iostream>
#include <vector>

#include <fstream>
#include <filesystem>

#include "bitUtils.hpp"

constexpr const char* regTable[8] = { "al", "cl", "dl", "bl", "ah", "ch", "dh", "bh" }; 
constexpr const char* regTableW[8] = { "ax", "cx", "dx", "bx", "sp", "bp", "si", "di" }; 

// TODO(plum): This isn't the best OOP pattern
// re the decoding in the mov op itself.
struct Mov {
	Mov(u8 low, u8 high) : low(low), high(high) {
		DecodeLow();	
		DecodeHigh();
	}

	~Mov() {

	}

	enum class MemMode : u8 {
		MEMORY_NO_DISP = 0,
		MEMORY_8_BIT_DISP = 1,
		MEMORY_16_BIT_DISP = 2,
		REGISTER = 3
	};

	std::string_view memModeToString() {
		switch(this->mode) {
			case MemMode::MEMORY_NO_DISP:     return "No Displacement (0)";
			case MemMode::MEMORY_8_BIT_DISP:  return "Mem Displacement, 8 bit (1)";
			case MemMode::MEMORY_16_BIT_DISP: return "Mem Displacement, 16 bit (2)";
			case MemMode::REGISTER:           return "Register Displacement (3)";
		}	
	}

	enum class Direction : u8 {
		TO_REG = 0,
		FROM_REG = 1
	};

	std::string_view directionToString() {
		switch(this->direction) {
			case Direction::TO_REG:   return "TO_REG";
			case Direction::FROM_REG: return "FROM_REG";
		}
	}


	u8 low{0};
	u8 high{0};

	MemMode mode{0};
	bool wide {false};

	Direction direction {0};

	u8 RegA{0};
	u8 RegB{0};

	std::string ReconstructAsm() {
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

private:
	void DecodeLow() {
		// This is the move opcode, if it doesnt equal this we're not able to handle it.
		assert(bu::bitSpan(low, 0, 4) == 0b00010001);			

		wide = static_cast<bool>(bu::bitSpan(low, 7, 7));
		direction = static_cast<Direction>(bu::bitSpan(low, 6, 7));	
	}

	void DecodeHigh() {
		// Mod - First 2 bits
		mode = static_cast<MemMode>(bu::bitSpan(high, 0, 1));

		// Reg - Middle 3 bits
		u8 reg = bu::bitSpan(high, 2, 4);

		// R/M - Last 3 bits
		u8 r_or_m = bu::bitSpan(high, 5, 7);	
	
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
};

int main(int argc, char** argv) {	
	if (argc == 1) { 
		std::cout << "Please pass file!" << std::endl;
		return 0; 
	}
	
	std::string fileName;
	if (!std::filesystem::exists(argv[1])) {
		std::cout << "File " << argv[1] << " doesn't exist!" << std::endl;
		return 0;
	} else {
		fileName = std::string(argv[1]);
	}

	std::ifstream file(fileName, std::ios::binary | std::ios::ate);

	if (!file.is_open()) {
		std::cout << "Failed to open the file." << std::endl;
		return 1;
	}

	std::streamsize size = file.tellg();
	if (size % 2 != 0) {
		std::cout << "File malformed." << std::endl;
	}
	
	// Return file pointer the beginning of file.
	file.seekg(0);

	std::vector<u8> buffer(size);

	std::vector<Mov> ops {};

	file.read(buffer.data(), size);

	constexpr u8 stride = 2;
	
	int bytesRead = 0;
	while (bytesRead < size) {
		Mov op(buffer[bytesRead], buffer[bytesRead + 1]);
		ops.push_back(op);
		bytesRead += stride;
	}

	std::cout << "bits 16\n\n";
	for (Mov op:ops) {
		std::cout << op.ReconstructAsm() << "\n";
	}
	std::cout << std::endl;
}
