#include "assembler.hpp"

#include <algorithm>
#include <iostream>
#include <iomanip>
#include <cstring>

namespace ntl
{
	std::string Token::str() const
	{
		return std::string{itb, ite};
	}
	
	Token::operator bool() const
	{
		return type != TokenType::EndOfLine;
	}
	
	bool Assembler::asm_isnotidentifier(const char c)
	{
		return !(::isalnum(c) || (c == '-') || (c == '_'));
	}
	
	bool Assembler::asm_isnotdigit(const char c)
	{
		return !(::isdigit(c) || (::tolower(c) >= 'a' && ::tolower(c) <= 'z'));
	}
	
	bool Assembler::asm_canendnumeric(const char c)
	{
		return (asm_isnotdigit(c) || ::isspace(c) || (c == '#') || (c == EOF));
	}
	
	const std::string& Assembler::current_line() const
	{
		return _program.back();
	}
	
	void Assembler::note(const Token& tok, const std::string text) const
	{
		const std::size_t begin_off = std::distance(begin(_program[tok.line]), tok.itb),
						  token_len = std::distance(tok.itb, tok.ite);
		
		std::cerr << _source_name << ':' << begin_off << ':' << tok.line << ": " << text << '\n'      // file:line:col: text
				  << _program[tok.line] << '\n'                                                       // line content with a token highlighted below
				  << std::string(begin_off, ' ') << '^' << std::string(token_len - 1, '~') << "\n\n"; //      ^~~~~~~
	}
	
	char Assembler::read_char()
	{
		if ((_itb = _ite) == end(current_line()))
			return (_last_char = EOF);
				
		++_ite;
		return (_last_char = *_itb);
	}
	
	Token Assembler::read_token()
	{
		while (::isspace(_last_char))
			read_char();
				
		if (_last_char == '\n' || _last_char == '#') // end of line or comment
			return Token{TokenType::EndOfLine, _program.size() - 1, _itb, _ite};
		
		if (_last_char == EOF)
			return Token{TokenType::EndOfLine, _program.size() - 1, _itb, _ite};
		
		if (_last_char == '.')
			return Token{TokenType::Comma, _program.size() - 1, _itb, _ite};
		
		if (::isalpha(_last_char))
			return Token{TokenType::Identifier, _program.size() - 1, _itb, (_ite = std::find_if(_itb, end(current_line()), asm_isnotidentifier))};
				
		if (::isdigit(_last_char)) // TODO handle 50A for example as an error, etc // also TODO make this not as bad...
		{
			std::string::const_iterator numbegin = _itb;
			const char second_digit = read_char();
			std::size_t base = 10;
			
			if (second_digit == 'x')
				base = 16;
			else if (second_digit == 'b')
				base = 2;
			else if (!::isdigit(second_digit) && !asm_canendnumeric(second_digit))
				return Token{TokenType::Unknown, _program.size() - 1, (_itb = numbegin), _ite};
			
			std::string::const_iterator realnumbegin = (base == 10 ? numbegin : numbegin + 2);
			_last_integer = std::stoull(std::string{realnumbegin, (_ite = std::find_if(realnumbegin, end(current_line()), asm_canendnumeric))}, nullptr, base);
				
			return Token{TokenType::Numeric, _program.size() - 1, (_itb = numbegin), _ite};
		}
		
		return Token{TokenType::Unknown, _program.size() - 1, _itb, _ite};
	}
	
	Assembler::Assembler(std::string fname) :
		_source{fname},
		_source_name{std::move(fname)}
	{
		if (!_source)
		{
			std::cerr << "Failed to load source from file '" << _source_name << "'\n\n";
			return;
		}
		
		while (_program.emplace_back(), std::getline(_source, _program.back()))
		{
			std::string& line = _program.back();
						
			if (line.empty())
				continue;
			
			_ite = begin(line);
			
			read_char();
			Token token;
			while ((token = read_token()))
			{
				switch (token.type)
				{
				case TokenType::EndOfLine: {
				} break;
				case TokenType::Unknown: {
					note(token, "Error: Unknown token");
				} return;
				case TokenType::Comma: {
					note(token, "Error: Assembler directives are not supported yet");
				} return;
				case TokenType::Identifier: {
					auto opit = opcode_match.find(token.str());
					if (opit == end(opcode_match))
					{
						note(token, "Error: Expected an instruction");
						return;
					}
					
					Instruction ins{opit->second.opcode};
										
					Token operand;
					
					std::size_t n = 0;
					while (read_char(), (operand = read_token()))
					{
						if (n >= opit->second.operands.size())
						{
							note(operand, "Error: Too much operands to instruction '" + token.str() + "'");
							return;
						}
						
						OperandInfo opinfo = opit->second.operands[n];
						
						if (operand.type == TokenType::Identifier)
						{
							auto regit = register_match.find(operand.str());
							if (regit == end(register_match))
							{
								if (opinfo.is_register())
								{
									note(operand, "Error: Cannot use unrecognized identifier '" + operand.str() + "' as a register name");
									return;
								}
								
								note(operand, "Error: Macros are not implemented yet");
								return;
							}
							else
							{
								if (!opinfo.is_register())
								{
									note(operand, "Error: Cannot use register name '" + operand.str() + "' as an immediate value");
									return;
								}
								
								ins.operand(opinfo.type, regit->second.id);
							}
						}
						else if (operand.type == TokenType::Numeric)
						{
							if (opinfo.is_register())
							{
								note(operand, "Error: Cannot use numeric value '" + operand.str() + "' as a register name");
								return;
							}
							
							ins.operand(opinfo.type, _last_integer);
						}
						else
						{
							note(operand, "Error: Unexpected token '" + operand.str() + "' as an operand");
							return;
						}
						
						++n;
					}
					
					if (n != opit->second.operands.size())
					{
						note(token, "Error: Missing operands to instruction '" + token.str() + "'");
						return;
					}
					
					_instructions.push_back(ins);
					
					continue; // Don't read an extra char
				} break;
				case TokenType::Numeric:
				default:
					note(token, "Error: Unexpected token '" + token.str() + "'.");
					return;
				}
				
				read_char();
			}
		}
		
		// TODO temp output
		_assembled.resize(_instructions.size() * sizeof(std::uint32_t));
		for (std::size_t i = 0; i < _instructions.size(); ++i)
			std::memcpy(_assembled.data() + (i * sizeof(std::uint32_t)), &_instructions[i], sizeof(std::uint32_t));
		
		_completed = true;
	}
	
	void Assembler::save(const std::string& dest_name)
	{
		if (!_completed)
		{
			std::cerr << "Error: Cannot save to file '" << dest_name << "' because of assembly errors.\n";
			return;
		}
		
		std::ofstream dest{dest_name};
		
		if (!dest)
		{
			std::cerr << "Error: Could not open file '" << dest_name << "' for writing.\n";
			return;
		}
		
		dest.write(reinterpret_cast<char*>(_assembled.data()), _assembled.size());
	}
}
