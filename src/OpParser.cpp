#include "OpParser.hpp"
#include <iostream>
#include <cstdlib>

namespace op {
	Parser::Parser(std::byte byte): 
		byte(byte) 
	{
		ParseOpCode();

		if (opCode == OpCode::COULD_NOT_PARSE) {
			std::cerr << "Could not parse opcode!" << std::endl;
			exit(1);
		}
	}

	Parser::OpCode Parser::GetOpCode() noexcept {
		return this->opCode;
	}

	void Parser::ParseOpCode() {
	}
}
