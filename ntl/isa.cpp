#include "isa.hpp"

namespace ntl
{
	const std::unordered_map<std::string, OpcodeInfo> opcode_match =
	{
		{"nop",    {0x00, { }}},
		{"load",   {0x01, { {R1, "rdst"},   {R2, "raddr"} }}},
		{"store",  {0x02, { {R1, "rsrc"},   {R2, "raddr"} }}},
		{"pload",  {0x03, { {R1, "rdst"},   {R2, "raddr"} }}},
		{"pstore", {0x04, { {R1, "rsrc"},   {R2, "raddr"} }}},
		{"mov",    {0x05, { {R1, "rsrc"},   {R2, "rdst"} }}},
		{"add",    {0x06, { {R1, "ra"},     {R2, "rb"},   {R3, "rdst"} }}},
		{"sub",    {0x07, { {R1, "ra"},     {R2, "rb"},   {R3, "rdst"} }}},
		{"mul",    {0x08, { {R1, "ra"},     {R2, "rb"},   {R3, "rdst"} }}},
		{"div",    {0x09, { {R1, "ra"},     {R2, "rb"},   {R3, "rdst"} }}},
		{"and",    {0x0A, { {R1, "ra"},     {R2, "rb"},   {R3, "rdst"} }}},
		{"or",     {0x0B, { {R1, "ra"},     {R2, "rb"},   {R3, "rdst"} }}},
		{"xor",    {0x0C, { {R1, "ra"},     {R2, "rb"},   {R3, "rdst"} }}},
		{"not",    {0x0D, { {R1, "ra"},     {R2, "rdst"} }}},
		{"shl",    {0x0E, { {R1, "ra"},     {R2, "roff"}, {R3, "rdst"} }}},
		{"shr",    {0x0F, { {R1, "ra"},     {R2, "roff"}, {R3, "rdst"} }}},
		{"ashr",   {0x10, { {R1, "ra"},     {R2, "roff"}, {R3, "rdst"} }}},
		{"gbit",   {0x11, { {R1, "ra"},     {R2, "roff"}, {R3, "rdst"} }}},
		{"fbit",   {0x12, { {R1, "ra"},     {R2, "rdst"} }}},
		{"pop",    {0x13, { {R1, "rdst"} }}},
		{"push",   {0x14, { {R1, "rsrc"} }}},
		{"jmpi",   {0x15, { {IMM1, "iaddr"} }}},
		{"jmp",    {0x16, { {R1, "raddr"} }}},
		{"cjmpi",  {0x17, { {IMM1, "iaddr"} }}},
		{"cjmp",   {0x18, { {R1, "raddr"} }}},
		{"ret",    {0x19, { }}},
		{"calli",  {0x1A, { {IMM1, "iaddr"} }}},
		{"call",   {0x1B, { {R1, "raddr"} }}},
		{"tz",     {0x1C, { {R1, "ra"} }}},
		{"tht",    {0x1D, { {R1, "ra"},     {R2, "rb"} }}},
		{"thq",    {0x1E, { {R1, "ra"},     {R2, "rb"} }}},
		{"teq",    {0x1F, { {R1, "ra"},     {R2, "rb"} }}},
		{"ldi",    {0x20, { {R1, "rdst"},   {IMM1, "ia"} }}},
		{"hlt",    {0x21, { }}},
		{"read",   {0x22, { {R1, "rdst"},   {R2, "rport"} }}},
		{"write",  {0x23, { {R1, "rsrc"},   {R2, "rport"} }}},
		{"wait",   {0x24, { {R1, "rport"} }}},
		{"int",    {0x24, { {IMM1, "iid"} }}},
	};
	
	const std::unordered_map<std::string, RegisterInfo> register_match =
	{
		{"rfl", {0x0}},
		{"ridt", {0x1}},
		{"racc", {0x2}},
		{"rsp", {0x3}},
		{"r4", {0x4}},
		{"r5", {0x5}},
		{"r6", {0x6}},
		{"r7", {0x7}}
	};
	
	bool OperandInfo::is_register() const
	{
		return type != IMM1;
	}
	
	OperandInfo OpcodeInfo::operator[](const std::size_t i) const
	{
		if (i >= operands.size())
			return OperandInfo{OOB_OPERAND, ""};
		
		return operands[i];
	}
}
