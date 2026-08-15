#pragma once
#include <memory>
#include <vector>
#include <iostream>

// TODO:(plum) Turn this into a harness/result model.
// You can create a new result in any file and it will
// register itself with the harness (debug only).
// the harness will the execute all of the result runs and
// find the result of the tests that way.

#ifndef TEST	
	#define TEST(harness_ptr, cond, msg) (harness_ptr)->test(cond, #cond, msg)
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
			std::vector<std::string> 	 message{};	
			std::vector<std::string> 	 names{};	

			void test(bool condition, const char* name, const char* msg) {
				this->message.emplace_back(msg);
				this->names.emplace_back(name);
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
						Status::FAIL ? std::string("\n\t\033[3m" + message[i]) : "";

					std::cout 
						<< "[" << i << "] " 
						<< static_cast<char>(status[i]) << ": " 
						<< names[i] << end;
					
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
		TEST(harness, 1 != 2, "One does not equal two!");
		return harness;
	};	
}
