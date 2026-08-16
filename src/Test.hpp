#pragma once

// TODO: Release Guard


#include <bitset>
#include <memory>
#include <vector>
#include <iostream>

#include "BitUtils.hpp"

// TODO:(plum) Turn this into a harness/result model.
// You can create a new result in any file and it will
// register itself with the harness (debug only).
// the harness will the execute all of the result runs and
// find the result of the tests that way.

#ifndef TEST	
	#define TEST(harness_ptr, cond, msg) (harness_ptr)->test(cond, #cond, msg, __FILE__, __LINE__)
#endif

namespace Test {
	class TestResult {
		public:
			enum class Status : char {
				SKIPPED = 'S',
				PASS = 'P',
				FAIL = 'F'
			};
			
			long long count = 0;
			std::vector<Status>        status{};
			std::vector<std::string> 	 messages{};	
			std::vector<std::string> 	 conditions{};	
			std::vector<std::string>   fileNames{};
			std::vector<int>           lineNumbers{};


			void test(
					bool condition, const char* name, std::string msg, const char* fileName, int lineNumber) 
			{
				this->messages.emplace_back(msg);
				this->conditions.emplace_back(name);
				this->fileNames.emplace_back(fileName);
				this->lineNumbers.emplace_back(lineNumber);
				if (condition) {
					this->status.emplace_back(Status::PASS);
				} else {
					this->status.emplace_back(Status::FAIL);
				}
				this->count++;
			}
			

			int EnumerateResults() {
				std::cout << "Running " << count << " tests." << std::endl;
				std::cout << "------------------" << std::endl;

				bool fail = false;

				for (int i = 0; i < count; i++) {
					// These escape codes set colors, green for pass, red for fail,
					// white for everything else.
					constexpr const char* RED = "\033[31m";
					constexpr const char* GREEN = "\033[32m";
					constexpr const char* WHITE = "\033[37m";

					constexpr const char* ITALIC = "\033[37m";


					switch(status[i]) {
						case Status::PASS: { std::cout << GREEN; break; }
	 					case Status::FAIL: { fail = true; std::cout << RED; break; }
						default: std::cout << "\033[37m";
					}

					std::string end = status[i] == 
						Status::FAIL ? 
							std::string("\n\t\033[37m" + std::string(messages[i])) 
						: "";

					std::cout 
						<< "[" << i << "] " 
						<< static_cast<char>(status[i]) << " at " << fileNames[i] << ":" << lineNumbers[i] << ": " 
						<< conditions[i] << end;
					
					if (i + 1 != count) std::cout << "\n";
				}

				if (fail) {
					return 1;
				} else {
					return 0;
				}
			}
	};

	std::unique_ptr<TestResult> Run() {
		std::unique_ptr<TestResult> harness = std::make_unique<TestResult>();
		
		char x = 0b10000000;
		char y = 0b00101000;
		char z = 0b00000101;

		TEST(harness, bu::bitSpan(x, 7, 6) == 0b00000010, "");
		TEST(harness, bu::bitSpan(y, 5, 3) == 0b00000101, "");
		TEST(harness, bu::bitSpan(z, 2, 0) == 0b00000101, "");


		return harness;
	};	
}
