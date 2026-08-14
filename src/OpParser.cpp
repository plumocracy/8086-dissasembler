#include "OpParser.hpp"
#include <iostream>
#include <cstdlib>

namespace op {
	OpParser::OpParser(std::byte byte): 
		byte(byte) 
	{
		ParseOpCode();

		if (opCode == OpCode::COULD_NOT_PARSE) {
			std::cerr << "Could not parse opcode!" << std::endl;
			exit(1);
		}
	}

	OpParser::OpCode OpParser::GetOpCode() noexcept {
		return this->opCode;
	}

	void OpParser::ParseOpCode() {
	}
}
