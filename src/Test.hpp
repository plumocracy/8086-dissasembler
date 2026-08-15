#pragma once
#include <memory>
#include <vector>
#include <iostream>

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

			void TEST(bool condition, const char* name, const char* msg) {
				this->message.emplace_back(msg);
				this->names.emplace_back(name);
				if (condition) {
					this->status.emplace_back(Status::PASS);
				} else {
					this->status.emplace_back(Status::FAIL);
				}
				this->count++;
			}

			int EnumerateResults(bool with_success = true) {
				std::cout << "Running " << count << " tests." << std::endl;
				std::cout << "------------------" << std::endl;

				bool fail = false;

				for (int i = 0; i < count; i++) {
					if (!with_success && status[i] == Status::PASS) {
						continue;
					}

					if (status[i] == Status::PASS) {
						std::cout << "\033[32m";
					} else if (status[i] == Status::FAIL) {
						fail = true;
						std::cout << "\033[31m";
					} else {
						std::cout << "\033[37m";
					}

					std::cout << "[" << i << "] " << static_cast<char>(status[i]) 
						<< ": " << names[i] << "\n\t";

					if (status[i] == Status::FAIL) {
						std::cout << "\033[3m"<<message[i];
					}

					std::cout << "\033[0m\n";
				}

				std::cout << std::endl;	

				if (fail) {
					return 1;
				} else {
					return 0;
				}
			}
	};

	std::unique_ptr<TestResult> Run() {
		std::unique_ptr<TestResult> harness = std::make_unique<TestResult>();		
		harness->TEST(1 != 2, "One doesnt equal two", "One equals two!");
		//harness->TEST(1 == 2, "One equals two", "One does not equal two!");
		return harness;
	};	
}
