#include <iostream>
#include <memory>
#include <vector>

#include <fstream>
#include <filesystem>

#include "BitUtils.hpp"
#include "Mov.hpp"
#include "Test.hpp"

#define DOCTEST

int main(int argc, char** argv) {
	
	if (argc == 1) {
		std::unique_ptr<Test::TestResult> r = Test::Run();
		exit(r->EnumerateResults());	
	}

	std::string fileName;
	if (!std::filesystem::exists(argv[1])) {
		std::cout << "File " << argv[1] << " doesn't exist!" << std::endl;
		return 0;
	} else {
		fileName = std::string(argv[1]);
	}

	std::ifstream file(fileName, std::ios::binary | std::ios::ate);

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
