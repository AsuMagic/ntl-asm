#ifndef NTL_ISA_HPP
#define NTL_ISA_HPP

#include <unordered_map>
#include <vector>
#include <string>

namespace ntl
{
	enum OperandType
	{
		REG, IMM
	};
	
	struct RegisterInfo
	{
		const std::uint8_t id;
	};
	
	struct OperandInfo
	{
		OperandType type;
		const char *const name = "";
	};
	
	struct OpcodeInfo
	{
		const std::uint8_t opcode;
		std::vector<OperandInfo> operands;
	};

	extern const std::unordered_map<std::string, OpcodeInfo> opcode_match;
	extern const std::unordered_map<std::string, RegisterInfo> register_match;
}

#endif
