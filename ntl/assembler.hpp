#ifndef NTL_ASSEMBLER_HPP
#define NTL_ASSEMBLER_HPP

#include <unordered_map>
#include <fstream>
#include <array>
#include <vector>

#include "codegen.hpp"
#include "isa.hpp"

namespace ntl
{
	enum class TokenType
	{
		EndOfLine,
		Unknown, // Unknown token (parse error)
		
		Comma, // Assembler directive comma
		
		Identifier,
		Numeric,
	};
	
	struct Token
	{
		TokenType type;
		std::size_t line;
		std::string::const_iterator itb, ite;
				
		std::string str() const;
		operator bool() const;
	};
	
	struct Register
	{
		const RegisterInfo* info;
		
		Register(const std::string& name);
		operator const RegisterInfo*() const;
	};
	
	struct Opcode
	{
		const OpcodeInfo* info;
		
		Opcode(const std::string& name);
		operator const OpcodeInfo*() const;
	};
	
	bool asm_isnotidentifier(const char c);
	bool asm_isnotdigit(const char c);
	bool asm_canendnumeric(const char c);
	
	class Assembler
	{
		std::ifstream _source;
		const std::string _source_name;
		
		std::string::const_iterator _itb, _ite;
		
		std::vector<std::string> _program;
		std::vector<Instruction> _instructions;
		std::vector<std::uint8_t> _assembled;
		
		char _last_char = ' ';
		std::size_t _last_integer = 0;
		
		bool _completed = false;
		
		const std::string& current_line() const;
		
		void note(const Token& token, const std::string text) const;
		
		bool encode_operand(const Token& token, const std::size_t n, const OperandInfo opinfo, Instruction& instruction);
		
		char read_char();
		Token read_token();
				
	public:
		Assembler(std::string source_name);
		void save(const std::string& dest_name);
	};
}

#endif
