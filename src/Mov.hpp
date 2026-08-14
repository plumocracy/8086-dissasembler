#pragma once

#include <string>
#include <string_view>

#include "BitUtils.hpp"

namespace ops {

class Mov {
public:
	Mov(u8 low, u8 high) : low(low), high(high) {
		DecodeLow();
		DecodeHigh();
	}

	~Mov() {}

	enum class MemMode : u8 {
		MEMORY_NO_DISP = 0,
		MEMORY_8_BIT_DISP = 1,
		MEMORY_16_BIT_DISP = 2,
		REGISTER = 3
	};

	enum class Direction : u8 {
		TO_REG = 0,
		FROM_REG = 1
	};

	std::string_view memModeToString();
	std::string_view directionToString();
	std::string ReconstructAsm();

	u8 low{0};
	u8 high{0};

	MemMode mode{0};
	bool wide {false};

	Direction direction {0};

	u8 RegA{0};
	u8 RegB{0};

private:
	void DecodeLow();
	void DecodeHigh();
};
}
