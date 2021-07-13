#include <iostream>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <array>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <cstring>


std::vector<std::string> split(const std::string& s, char delimiter)
{
	std::vector<std::string> tokens;
	std::string token;
	std::istringstream tokenStream(s);
	while (std::getline(tokenStream, token, delimiter))
	{
		tokens.push_back(token);
	}
	return tokens;
}

std::string exec(std::string const &input)
{
	const char* cmd = input.c_str();
	std::array<char, 128> buffer{};
	std::string result;
	std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
	if (!pipe)
		throw std::runtime_error("popen() failed!");
	while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr)
		result += buffer.data();
	return result;
}

int main()
{
	std::vector<int> v{};
	auto end = v.end();
#if (1)
	const char *filename = "tests.log";
	std::ifstream in;
	in.open(filename);
	std::string line;
	while (std::getline(in, line))
	{
		std::stringstream ss1, ss2;
		ss1 << "minishell -c '" << line << "'";
		ss2 << "bash -c '" << line << "'";
#if (0)
		std::cout << ss1.str() << std::endl;
		std::cout << ss2.str() << std::endl;
#endif
#if (1)
		std::string minishell_out = exec(ss1.str());
		std::string bash_out = exec(ss2.str());
		std::cout << "{ " << line << " }" << ' ';

		std::cout << std::setw(150 - strlen(line.c_str())) <<
		(minishell_out == bash_out ? "\033[1;32m [ AC ]\033[0m\n" : "\033[1;31m [ WA ]\033[0m\n");
#endif
	}
#endif
#if (0)
	std::string out = exec("minishell -c 'echo $HOME hahahahah > file.log'");
	std::cout << out << std::endl;
#endif
	return 0;
}
