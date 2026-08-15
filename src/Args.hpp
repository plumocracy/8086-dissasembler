#pragma once
#include <string>
#include <vector>

class Args {	
public:
	Args(int argc, char* argv[]);
	~Args();
	
	Args(const Args& other) = delete;
	Args(const Args&& other) noexcept = delete;
	
	bool ShouldTestProgram();
	bool Healthy();
	std::string& FileName();


private:
	bool successfulParse = true;
	bool test = false;

	int argc;

	std::string fileName = "\0";
	std::vector<std::string> argv;
	void ParseArguments();
};


