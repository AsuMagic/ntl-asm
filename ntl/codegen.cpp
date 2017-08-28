#include "codegen.hpp"

namespace ntl
{
	Instruction::Instruction(const std::uint8_t opcode) :
		instruction{static_cast<std::uint32_t>(opcode)}
	{}
	
	void Instruction::operand(const OperandType type, const std::uint32_t value, const std::size_t offset)
	{
		switch (type)
		{
		case REG: instruction |= value << (8 + (offset * 4)); break;
		case IMM: instruction |= value << 16; break;
		};
	}
}
