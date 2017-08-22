#ifndef NTL_CODEGEN_HPP
#define NTL_CODEGEN_HPP

#include <cstdint>
#include <bitset>

#include "isa.hpp"

namespace ntl
{
	struct Instruction
	{
		std::uint32_t instruction;
		
		Instruction(const std::uint8_t opcode);
		void operand(const OperandType type, const std::uint32_t value);
	};
}

#endif
