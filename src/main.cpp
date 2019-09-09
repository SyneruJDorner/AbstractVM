#include <string>
#include <stdio.h>
#include <iostream>
#include <list>
#include <vector>
#include <regex>
#include <fstream>
#include <locale>
#include <exception>
#include "class/VMExceptions.hpp"
#include "class/OperandFactory.hpp"

std::string trim(std::string &str)
{
	size_t p = str.find_first_not_of(" \t");
   	str.erase(0, p);

	p = str.find_last_not_of(" \t");
   	if (std::string::npos != p)
      str.erase(p + 1);

  	return (str);
}

void parseConsole(std::string &s, int nb, int &error)
{
	int i = 0;
	std::string regexExpressionSearch = "([ \t]+)?((add|pop|dump|sub|mul|div|mod|print|exit)|((push|assert)[ \t]((int(8|16|32)[(]-?[0-9]+[)])|(float|double)[(]-?[0-9]+(.[0-9]+)?[)])))([ \t]+)?";
	std::regex reg(regexExpressionSearch);

	if ((i = s.find(";")) != -1)
		s.assign(s, 0, i);

	if (!s.empty())
	{
		if (!regex_match(s, reg))
		{
			std::cerr << "Syntax error on line " << nb + 1 << std::endl;
			error = 1;
		}
	}
}

void readline(std::list<std::string> &s)
{
	std::string line;
	std::regex reg("([ \t]+)?exit([ \t]+)?");
	int flag = 0;
	std::cout << "Please type your source assebly (end with ';;'):" << std::endl;

	while (std::getline(std::cin, line) && line.compare(";;"))
	{
		s.push_back(trim(line));
		if (regex_match(line, reg))
			flag++;
	}

	if (line.compare(";;"))
		throw VMExceptions::SemicolonException();

	if (!flag)
		throw VMExceptions::ExitException();
}

void readfile(const char *file, std::list<std::string> &s)
{	
	std::ifstream stream(file);
	std::string line;
	std::regex reg("([ \t]+)?exit([ \t]+)?");

	if (stream)
	{
		while (std::getline(stream, line) && !regex_match(line, reg))
			s.push_back(trim(line));

		if (!regex_match(line, reg))
			throw VMExceptions::ExitException();
	}
	else
		throw VMExceptions::FileException();
}

void display(std::list<std::string> s)
{
	std::list<std::string>::iterator p = s.begin();

	while (p != s.end())
	{
		std::cout << *p << std::endl;
		p++;
	}
}

void lexerStandard(std::list<std::string> s)
{
	std::list<std::string>::iterator p = s.begin();
	std::locale loc;
	std::cmatch val;
	std::cmatch typ;
	std::cmatch ins;
	std::regex in("^[[:alpha:]]+");
	std::regex ty("[ \t][[:alnum:]]+");
    std::regex va("[(](-?[0-9]+(.[0-9]+)?)][)]");

	while (p != s.end())
	{	
		regex_search((*p).c_str(), val, va);
	    regex_search((*p).c_str(), typ, ty);
	    regex_search((*p).c_str(), ins, in);
	    std::string instruction(ins[0]);
	    std::string type(typ[0]);
	    type.erase(type.begin());
		type[0] = std::toupper(type[0], loc);
	    std::string value(val[1]);
	    
	    OperandFactory::instance->HandleInstruction(trim(instruction), OperandFactory::instance->getTypeWithString(trim(type)), trim(value));
		p++;
	}
}

int main(int argc, const char **argv)
{
	std::list<std::string> s;
	int error = 0;
	int offset = 0;

	try
	{
		if (argc == 1)
			readline(s);
		else if (argc == 2)
			readfile(argv[1], s);
		else
		{
			std::cout << "usage ./avm or ./avm file" << std::endl;
			return (0);
		}

		std::list<std::string>::iterator p = s.begin();

		while (p != s.end())
		{
			parseConsole(*p, std::distance(s.begin(), p) + offset, error);
			if ((*p).empty())
			{
				s.erase(p);
				offset++;
			}
			p++;
		}

		if (error)
			throw VMExceptions::SyntaxException();

		lexerStandard(s);
	}
	catch(std::exception &e)
	{
		std::cout << e.what() << '\n';
	}
	catch(std::runtime_error &e)
	{
		std::cout << e.what() << '\n';
	}
	return (0);
}