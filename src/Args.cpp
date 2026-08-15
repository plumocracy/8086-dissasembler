#include "Args.hpp"

Args::Args(int argc, char* argv[]) {
	int count = 0;
	while (count < argc) {
		this->argv.emplace_back(argv[count]);
		count++;
	}
	
	this->argc = argc;

	ParseArguments();
}

Args::~Args() {;}

bool Args::ShouldTestProgram() {
	return test;
}

bool Args::Healthy() {
	return successfulParse;
}

std::string& Args::FileName() {
	return fileName;
}

void Args::ParseArguments() {			
	if (argc == 1) {
		successfulParse = false;
		return;
	}
	
	for (int i = 1; i < argc; i++) {
		const std::string arg = argv[i];

		if (arg == "--test" || arg == "--t") {
			test = true;
			continue;
		}
		if (fileName == "\0") {
			fileName = arg;
			continue;
		}
	}
}
