#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "ntl/assembler.hpp"

int main(int argc, const char* argv[])
{
	if (argc == 1)
		std::cout << "Usage: ntlas [file1] [file2...]\n";
		
	for (const auto& arg : std::vector<std::string>{argv + 1, argv + argc})
		ntl::Assembler{arg}.save(std::string{begin(arg), std::find(begin(arg), end(arg), '.')} + ".ntl");
}
