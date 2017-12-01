#include "isa.hpp"

namespace ntl
{
	const std::unordered_map<std::string, OpcodeInfo> opcode_match =
	{
		{"nop",    {0x00, { }}},
		{"load",   {0x01, { {REG, "rdst"},   {REG, "raddr"} }}},
		{"store",  {0x02, { {REG, "rsrc"},   {REG, "raddr"} }}},
		{"mov",    {0x03, { {REG, "rsrc"},   {REG, "rdst"} }}},
		{"add",    {0x04, { {REG, "ra"},     {REG, "rb"} }}},
		{"sub",    {0x05, { {REG, "ra"},     {REG, "rb"} }}},
		{"mul",    {0x06, { {REG, "ra"},     {REG, "rb"} }}},
		{"div",    {0x07, { {REG, "ra"},     {REG, "rb"} }}},
		{"and",    {0x08, { {REG, "ra"},     {REG, "rb"} }}},
		{"or",     {0x09, { {REG, "ra"},     {REG, "rb"} }}},
		{"xor",    {0x0A, { {REG, "ra"},     {REG, "rb"} }}},
		{"not",    {0x0B, { {REG, "ra"} }}},
		{"shl",    {0x0C, { {REG, "ra"},     {REG, "roff"} }}},
		{"shr",    {0x0D, { {REG, "ra"},     {REG, "roff"} }}},
		{"gbit",   {0x0E, { {REG, "ra"},     {REG, "roff"} }}},
		{"fbit",   {0x0F, { {REG, "ra"},     {REG, "rdst"} }}},
		{"pop",    {0x10, { {REG, "rdst"} }}},
		{"push",   {0x11, { {REG, "rsrc"} }}},
		{"jmpi",   {0x12, { {IMM, "iaddr"} }}},
		{"jmp",    {0x13, { {REG, "raddr"} }}},
		{"cjmpi",  {0x14, { {IMM, "iaddr"} }}},
		{"cjmp",   {0x15, { {REG, "raddr"} }}},
		{"ret",    {0x16, { }}},
		{"calli",  {0x17, { {IMM, "iaddr"} }}},
		{"call",   {0x18, { {REG, "raddr"} }}},
		{"tz",     {0x19, { {REG, "ra"} }}},
		{"tht",    {0x1A, { {REG, "ra"},     {REG, "rb"} }}},
		{"thq",    {0x1B, { {REG, "ra"},     {REG, "rb"} }}},
		{"teq",    {0x1C, { {REG, "ra"},     {REG, "rb"} }}},
		{"ldi",    {0x1D, { {REG, "rdst"},   {IMM, "ia"} }}},
		{"hlt",    {0x1E, { }}},
		{"int",    {0x1F, { {IMM, "iid"} }}},
	};
	
	const std::unordered_map<std::string, RegisterInfo> register_match =
	{
		{"rfl",  {0x0}},
		{"ridt", {0x1}},
		{"racc", {0x2}},
		{"rsp",  {0x3}},
		{"r4",   {0x4}},
		{"r5",   {0x5}},
		{"r6",   {0x6}},
		{"r7",   {0x7}}
	};
}
