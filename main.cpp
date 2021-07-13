#include <iostream>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <array>
#include <string>

std::string exec(const char* cmd)
{
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
	std::string out = exec("minishell -c 'echo $USER > file.log'");
	std::cout << out << std::endl;
	// func();
	return 0;
}
