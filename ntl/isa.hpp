#ifndef NTL_ISA_HPP
#define NTL_ISA_HPP

#include <unordered_map>
#include <vector>
#include <string>

namespace ntl
{
	enum OperandType
	{
		R1 = 0,
		R2,
		R3,
		IMM1,
		
		OOB_OPERAND
	};
	
	struct RegisterInfo
	{
		const std::uint8_t id;
	};
	
	struct OperandInfo
	{
		OperandType type;
		const char *const name = "";
		
		bool is_register() const;
	};
	
	struct OpcodeInfo
	{
		const std::uint8_t opcode;
		std::vector<OperandInfo> operands;
		
		OperandInfo operator[](const std::size_t i) const;
	};

	extern const std::unordered_map<std::string, OpcodeInfo> opcode_match;
	extern const std::unordered_map<std::string, RegisterInfo> register_match;
}

#endif
