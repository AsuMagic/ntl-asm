#include "isa.hpp"

namespace ntl
{
	const std::unordered_map<std::string, OpcodeInfo> opcode_match =
	{
		{"nop",    {0x00, { }}},
		{"load",   {0x01, { {REG, "rdst"},   {REG, "raddr"} }}},
		{"store",  {0x02, { {REG, "rsrc"},   {REG, "raddr"} }}},
		{"pload",  {0x03, { {REG, "rdst"},   {REG, "raddr"} }}},
		{"pstore", {0x04, { {REG, "rsrc"},   {REG, "raddr"} }}},
		{"mov",    {0x05, { {REG, "rsrc"},   {REG, "rdst"} }}},
		{"add",    {0x06, { {REG, "ra"},     {REG, "rb"},   {REG, "rdst"} }}},
		{"sub",    {0x07, { {REG, "ra"},     {REG, "rb"},   {REG, "rdst"} }}},
		{"mul",    {0x08, { {REG, "ra"},     {REG, "rb"},   {REG, "rdst"} }}},
		{"div",    {0x09, { {REG, "ra"},     {REG, "rb"},   {REG, "rdst"} }}},
		{"and",    {0x0A, { {REG, "ra"},     {REG, "rb"},   {REG, "rdst"} }}},
		{"or",     {0x0B, { {REG, "ra"},     {REG, "rb"},   {REG, "rdst"} }}},
		{"xor",    {0x0C, { {REG, "ra"},     {REG, "rb"},   {REG, "rdst"} }}},
		{"not",    {0x0D, { {REG, "ra"},     {REG, "rdst"} }}},
		{"shl",    {0x0E, { {REG, "ra"},     {REG, "roff"}, {REG, "rdst"} }}},
		{"shr",    {0x0F, { {REG, "ra"},     {REG, "roff"}, {REG, "rdst"} }}},
		{"ashr",   {0x10, { {REG, "ra"},     {REG, "roff"}, {REG, "rdst"} }}},
		{"gbit",   {0x11, { {REG, "ra"},     {REG, "roff"}, {REG, "rdst"} }}},
		{"fbit",   {0x12, { {REG, "ra"},     {REG, "rdst"} }}},
		{"pop",    {0x13, { {REG, "rdst"} }}},
		{"push",   {0x14, { {REG, "rsrc"} }}},
		{"jmpi",   {0x15, { {IMM, "iaddr"} }}},
		{"jmp",    {0x16, { {REG, "raddr"} }}},
		{"cjmpi",  {0x17, { {IMM, "iaddr"} }}},
		{"cjmp",   {0x18, { {REG, "raddr"} }}},
		{"ret",    {0x19, { }}},
		{"calli",  {0x1A, { {IMM, "iaddr"} }}},
		{"call",   {0x1B, { {REG, "raddr"} }}},
		{"tz",     {0x1C, { {REG, "ra"} }}},
		{"tht",    {0x1D, { {REG, "ra"},     {REG, "rb"} }}},
		{"thq",    {0x1E, { {REG, "ra"},     {REG, "rb"} }}},
		{"teq",    {0x1F, { {REG, "ra"},     {REG, "rb"} }}},
		{"ldi",    {0x20, { {REG, "rdst"},   {IMM, "ia"} }}},
		{"hlt",    {0x21, { }}},
		{"read",   {0x22, { {REG, "rdst"},   {REG, "rport"} }}},
		{"write",  {0x23, { {REG, "rsrc"},   {REG, "rport"} }}},
		{"wait",   {0x24, { {REG, "rport"} }}},
		{"int",    {0x24, { {IMM, "iid"} }}},
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
}
