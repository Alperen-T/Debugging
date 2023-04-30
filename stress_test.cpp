#include <bits/stdc++.h>

using namespace std;

const int TL_SIGNAL = 31744;

#define COLOR_RESET "\033[0m" 
#define COLOR_RED "\033[1;31m"
#define COLOR_RED2 "\033[31m"
#define COLOR_GREEN "\033[1;32m"
#define COLOR_YELLOW "\033[1;33m"
#define COLOR_BLUE "\033[1;34m"

void create_report(bool output_report, bool is_checker, string checker_ans = ""){
	ofstream report_file("ast_report.txt");

	report_file << "[===] Alperen Stress Tester Report [===]\n\n";

	report_file << "Input:\n\n";

	ifstream input_file("ast_input.txt");

	string str;

	while(getline(input_file, str)) report_file << str << "\n";

	report_file << "\n";

	if(is_checker) report_file << "Output:\n\n";
	else report_file << "Output 1:\n\n";

	ifstream code1_output("ast_code1.txt");

	while(getline(code1_output, str)) report_file << str << "\n";

	report_file << "\n";

	if(!is_checker){
		report_file << "Output 2:\n\n";

		ifstream code2_output("ast_code2.txt");

		while(getline(code2_output, str)) report_file << str << "\n";

		report_file << "\n";

		code2_output.close();
	}
	else{
		report_file << "Checker:\n\n";
		report_file << checker_ans << "\n";
	}

	report_file.close(), input_file.close(), code1_output.close();

	if(output_report){
		ifstream report_file("ast_report.txt");

		while(getline(report_file, str)) printf("%s\n", str.c_str());
	}

	if(filesystem::exists("ast_input.txt")) system("rm ast_input.txt");
	if(filesystem::exists("ast_code1.txt")) system("rm ast_code1.txt");
	if(filesystem::exists("ast_code2.txt")) system("rm ast_code2.txt");

	// if(system("find ast_input.txt 1> /dev/null") != 256) system("rm ast_input.txt");
	// if(system("find ast_code1.txt 1> /dev/null") != 256) system("rm ast_code1.txt");
	// if(system("find ast_code2.txt 1> /dev/null") != 256) system("rm ast_code2.txt");

	exit(0);
}

bool compare_files(){
	ifstream output1("ast_code1.txt"), output2("ast_code2.txt");

	vector<string> output_lines1, output_lines2;

	string str;

	while(getline(output1, str)){
		while(!str.empty() && (str.back() == ' ' || str.back() == '\n')) str.pop_back();

		output_lines1.push_back(str);
	}

	while(getline(output2, str)){
		while(!str.empty() && (str.back() == ' ' || str.back() == '\n')) str.pop_back();

		output_lines2.push_back(str);
	}

	return output_lines1 == output_lines2;
}

int main(int argc, char* argv[]){
	vector<string> args(argv, argv + argc);

	if(argc == 2 && (args[1] == "-h" || args[1] == "-help" || args[1] == "--help")){
		printf(
			"[===] Alperen Stress Tester [===]\n\n"

			"Usage: ./ast <generator> <code1> <-c code2> <-ch checker> <-garg args> <-t test_count> <-tl time_limit> <-tl2 time_limit_2> <-out>\n\n"

			"Examples: ./ast gencode -garg 5 testcode1 -c testcode2 -t 100 -tl 2 -out\n"
			"          ./ast gencode -garg 25 testcode1 -ch check -t 100 -tl 2 -out\n\n"

			"generator    : Code that generates input for code1 and code2\n"
			"code1        : The code to test.\n"
			"code2        : Second code to compare with code1.\n"
			"checker      : Code that takes the output of code1, returns 0 if the output is correct and 1 otherwise.\n"
			"args         : Command line arguments for the generator\n"
			"test_count   : How many stress tests should the tester do. Should be an integer. (Default: Infinite)\n"
			"time_limit   : Time limit for code1 and code2. Should be a real value. (Default: 5 seconds)\n"
			"time_limit2  : Time limit for generator and checker. Should be a real value. (Default: 10 seconds)\n"
			"-out         : If this flag is present, it will also output the stress test report to the command line.\n\n"

			"Notes:\n\n"

			COLOR_BLUE "[*] " COLOR_RESET "Arguments other than first 2 are optional.\n"
			COLOR_BLUE "[*] " COLOR_RESET "Every code should use stdin/stdout.\n"
			COLOR_BLUE "[*] " COLOR_RESET "You should compile the codes before running the stress tester.\n"
			COLOR_BLUE "[*] " COLOR_RESET "Use the file name which is used for running the code. (example instead of example.cpp)\n"
			COLOR_BLUE "[*] " COLOR_RESET "If a testcase isn't [AC] then a report file called \"ast_report.txt\" will be created.\n"
			);
	}
	else{
		if(argc < 3){
			printf(COLOR_RED2 "[!] " COLOR_RESET "Not enough arguments. You should provide at least the first 2 arguments. Type -h for more help.\n");
			return 0;
		}

		string code1, code2, generator, genargs, checker;
		long test_count = -1;
		double time_limit = 5, time_limit_2 = 10;
		bool output_report = false;

		generator = args[1], code1 = args[2];

		if(!filesystem::exists(generator)){
			printf(COLOR_RED2 "[!] " COLOR_RESET "The generator called %s does not exist. Type -h for more help.\n", generator.c_str());
			return 0;
		}

		if(!filesystem::exists(code1)){
			printf(COLOR_RED2 "[!] " COLOR_RESET "The code1 called %s does not exist. Type -h for more help.\n", code1.c_str());
			return 0;
		}

		for(int i = 3; i < args.size(); i++){
			if(args[i] == "-c"){
				if(i + 1 < args.size()) code2 = args[i + 1], i += 1;
				else{
					printf(COLOR_RED2 "[!] " COLOR_RESET "After the -c, you should provide the code2. Type -h for more help.\n");
					return 0;
				}

				if(!filesystem::exists(code2)){
					printf(COLOR_RED2 "[!] " COLOR_RESET "The code2 called %s does not exist. Type -h for more help.\n", code2.c_str());
					return 0;
				}
			}
			else if(args[i] == "-ch"){
				if(i + 1 < args.size()) checker = args[i + 1], i += 1;
				else{
					printf(COLOR_RED2 "[!] " COLOR_RESET "After the -ch, you should provide the checker name. Type -h for more help.\n");
					return 0;
				}

				if(!filesystem::exists(checker)){
					printf(COLOR_RED2 "[!] " COLOR_RESET "The checker called %s does not exist. Type -h for more help.\n", checker.c_str());
					return 0;
				}
			}
			else if(args[i] == "-garg"){
				if(i + 1 < args.size()) genargs = args[i + 1], i += 1;
				else{
					printf(COLOR_RED2 "[!] " COLOR_RESET "After the -garg, you should provide the arguments for generator. Type -h for more help.\n");
					return 0;
				}
			}
			else if(args[i] == "-t"){
				if(i + 1 < args.size()){
					char *it;

					test_count = strtol(args[i + 1].c_str(), &it, 10);

					if(*it){
						printf(COLOR_RED2 "[!] " COLOR_RESET "The value you provide after the -t should be an integer. Type -h for more help.\n");
						return 0;
					}

					i += 1;
				}
				else{
					printf(COLOR_RED2 "[!] " COLOR_RESET "After the -t, you should provide the test_count. Type -h for more help.\n");
					return 0;
				}
			}
			else if(args[i] == "-tl"){
				if(i + 1 < args.size()){
					char *it;

					time_limit = strtod(args[i + 1].c_str(), &it);

					if(*it){
						printf(COLOR_RED2 "[!] " COLOR_RESET "The value you provide after the -tl should be a real value. Type -h for more help.\n");
						return 0;
					}

					i += 1;
				}
				else{
					printf(COLOR_RED2 "[!] " COLOR_RESET "After the -tl, you should provide the time_limit. Type -h for more help.\n");
					return 0;
				}
			}
			else if(args[i] == "-tl2"){
				if(i + 1 < args.size()){
					char *it;

					time_limit_2 = strtod(args[i + 1].c_str(), &it);

					if(*it){
						printf(COLOR_RED2 "[!] " COLOR_RESET "The value you provide after the -tl2 should be a real value. Type -h for more help.\n");
						return 0;
					}

					i += 1;
				}
				else{
					printf(COLOR_RED2 "[!] " COLOR_RESET "After the -tl2, you should provide the time_limit_2. Type -h for more help.\n");
					return 0;
				}
			}
			else if(args[i] == "-out"){
				output_report = true;
			}
			else{
				printf(COLOR_RED2 "[!] " COLOR_RESET "Wrong argument in index %d. Type -h for more help.\n", i);
			}
		}

		if(code2.empty() && checker.empty()){
			printf(COLOR_RED2 "[!] " COLOR_RESET "You should provide code2 or checker\n");
			return 0;
		}
		if(!code2.empty() && !checker.empty()){
			printf(COLOR_RED2 "[!] " COLOR_RESET "You shouldn't provide both code2 and checker\n");
			return 0;
		}
 
		printf(
			COLOR_BLUE "[*] " COLOR_RESET "Starting stress test with parameters:\n\n"

			"generator     : %s\n"
			"code1         : %s\n"
			"code2         : %s\n"
			"checker       : %s\n"
			"genargs       : %s\n"
			"test_count    : %s\n"
			"time_limit    : %.3lf\n"
			"time_limit_2  : %.3lf\n"
			"output_report : %s\n\n"

			"Stress test mode: %s\n\n"
			, generator.c_str(), code1.c_str(), code2.empty() ? "N/A" : code2.c_str(), checker.empty() ? "N/A" : checker.c_str(), genargs.c_str(), test_count == -1 ? "INF" : to_string(test_count).c_str(), time_limit, time_limit_2, output_report ? "true" : "false", checker.empty() ? "Compare" : "Checker"
			);

		for(int tcase = 1; test_count == -1 ? true : tcase <= test_count; tcase++){
			printf(COLOR_BLUE "[*] " COLOR_RESET "Test Case " COLOR_BLUE "%d:" COLOR_RESET " ", tcase);
			fflush(stdout);

			ofstream input_file("ast_input.txt"), code1_output("ast_code1.txt");

			if(!code2.empty()){
				ofstream code2_output("ast_code2.txt");
				code2_output.close();
			}

			input_file.close(), code1_output.close();

			string command = "timeout " + to_string(time_limit_2) + " ./" + generator + " " + genargs + " > ast_input.txt";

			int sig = system(command.c_str());

			if(sig == TL_SIGNAL){
				printf(COLOR_YELLOW "[TLE] " COLOR_RESET "while running the generator.\n\n");

				ofstream input_file("ast_input.txt");
				input_file << "[TLE]\n";
				input_file.close();

				create_report(output_report, !checker.empty());
			}
			else if(sig != 0){
				printf(COLOR_RED2 "[ERROR] " COLOR_RESET "while running the generator.\n\n");

				ofstream input_file("ast_input.txt");
				input_file << "[ERROR]\n";
				input_file.close();

				create_report(output_report, !checker.empty());
			}

			command = "timeout " + to_string(time_limit) + " ./" + code1 + " < ast_input.txt > ast_code1.txt";

			sig = system(command.c_str());

			if(sig == TL_SIGNAL){
				printf(COLOR_YELLOW "[TLE] " COLOR_RESET "while running the code1.\n\n");

				ofstream code1_output("ast_code1.txt");
				code1_output << "[TLE]\n";
				code1_output.close();

				create_report(output_report, !checker.empty());
			}
			else if(sig != 0){
				printf(COLOR_RED2 "[ERROR] " COLOR_RESET "while running the code1.\n\n");

				ofstream code1_output("ast_code1.txt");
				code1_output << "[ERROR]\n";
				code1_output.close();

				create_report(output_report, !checker.empty());
			}

			if(!code2.empty()){
				command = "timeout " + to_string(time_limit) + " ./" + code2 + " < ast_input.txt > ast_code2.txt";

				sig = system(command.c_str());

				if(sig == TL_SIGNAL){
					printf(COLOR_YELLOW "[TLE] " COLOR_RESET "while running the code2.\n\n");

					ofstream code2_output("ast_code2.txt");
					code2_output << "[TLE]\n";
					code2_output.close();

					create_report(output_report, !checker.empty());
				}
				else if(sig != 0){
					printf(COLOR_RED2 "[ERROR] " COLOR_RESET "while running the code2.\n\n");

					ofstream code2_output("ast_code2.txt");
					code2_output << "[ERROR]\n";
					code2_output.close();

					create_report(output_report, !checker.empty());
				}

				if(compare_files()){
					printf(COLOR_GREEN "[AC]" COLOR_RESET "\n");
				}
				else{
					printf(COLOR_RED "[WA] " COLOR_RESET "Outputs of code1 and code2 are different.\n\n");
					create_report(output_report, !checker.empty());
				}
			}
			else{
				command = "timeout " + to_string(time_limit_2) + " ./" + checker + " < ast_code1.txt";

				sig = system(command.c_str());

				if(sig == TL_SIGNAL){
					printf(COLOR_YELLOW "[TLE] " COLOR_RESET "while running the checker.\n\n");

					create_report(output_report, !checker.empty(), "[TLE]");
				}
				else if(sig != 0 && sig != 256){
					printf(COLOR_RED2 "[ERROR] " COLOR_RESET "while running the checker.\n\n");

					create_report(output_report, !checker.empty(), "[ERROR]");
				}
				else if(sig == 256){
					printf(COLOR_RED "[WA] " COLOR_RESET "Checker returned 1. \n\n");

					create_report(output_report, !checker.empty(), "[WA]");
				}
				else{
					printf(COLOR_GREEN "[AC]" COLOR_RESET "\n");
				}
			}
		}
	}
}
