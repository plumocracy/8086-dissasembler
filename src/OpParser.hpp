#pragma once
#include "IntDef.hpp"

#include <cstddef>

namespace op {

class Parser {
	Parser(std::byte byte);
	~Parser();
	
	Parser(const Parser& other) = delete;
	Parser(const Parser&& other) noexcept = delete;
	
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
