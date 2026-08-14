#pragma once
#include "IntDef.hpp"

#include <cstddef>

namespace op {

class OpParser {
	OpParser(std::byte byte);
	~OpParser();
	
	OpParser(const OpParser& other) = delete;
	OpParser(const OpParser&& other) noexcept = delete;
	
	enum class OpCode: int {
		COULD_NOT_PARSE = -1,
		MOV = 0,
		OTHER = 1,
	};
	
	OpCode GetOpCode() noexcept;
private: 
	
	void ParseOpCode();

	std::byte byte;
	OpCode opCode;
};

}
