#include <iostream>
#include <memory>
#include <vector>

#include <fstream>
#include <filesystem>

#include "BitUtils.hpp"
#include "Mov.hpp"
#include "Test.hpp"
#include "Args.hpp"

#define DOCTEST

int main(int argc, char* argv[]) {
	
	Args args(argc, argv);
	
	if (!args.Healthy()) {
		std::cout << 
			"No file!\n" <<
			"usage: decoder <filename> or deocoder --test" <<
			std::endl;
		exit(1);
	}

	
	if (args.ShouldTestProgram()) {
		std::unique_ptr<Test::TestResult> r = Test::Run();
		exit(r->EnumerateResults());	
	}

	if (!std::filesystem::exists(args.FileName())) {
		std::cout << "File " << args.FileName() << " doesn't exist!" << std::endl;
		return 0;
	} 

	std::ifstream file(args.FileName(), std::ios::binary | std::ios::ate);

	if (!file.is_open()) {
		std::cout << "Failed to open the file." << std::endl;
		return 1;
	}

	std::streamsize size = file.tellg();
	if (size % 2 != 0) {
		std::cout << "File malformed." << std::endl;
	}

	// Return file pointer the beginning of file.
	file.seekg(0);

	std::vector<u8> buffer(size);

	std::vector<ops::Mov> ops {};

	file.read(buffer.data(), size);

	constexpr u8 stride = 2;

	int bytesRead = 0;
	while (bytesRead < size) {
		ops::Mov op(buffer[bytesRead], buffer[bytesRead + 1]);
		ops.push_back(op);
		bytesRead += stride;
	}

	std::cout << "bits 16\n\n";
	for (ops::Mov op:ops) {
		std::cout << op.ReconstructAsm() << "\n";
	}
	std::cout << std::endl;
}
