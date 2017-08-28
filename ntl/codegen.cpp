#include "codegen.hpp"

namespace ntl
{
	Instruction::Instruction(const std::uint8_t opcode) :
		instruction{static_cast<std::uint32_t>(opcode)}
	{}
	
	void Instruction::operand(const OperandType type, const std::uint32_t value)
	{
		switch (type)
		{
		case R1:   instruction |= value <<  8; break;
		case R2:   instruction |= value << 12; break;
		case R3:   instruction |= value << 16; break;
		case IMM1: instruction |= value << 16; break;
		};
	}
}
