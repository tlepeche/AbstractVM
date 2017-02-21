#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <Instruction.hpp>
#include <Exception.hpp>

std::string	analyse(std::string line)
{
	size_t		start;

	start = line.find(";");
	if (start < line.size())
		line.erase(start, line.size());
	return line;
}


void	parse_command(std::string strline, Instruction *Instr)
{
	if (strline.find(";;") < strline.size())
	{
		if (!(Instr->getExit()))
			throw AVMException("Error : program must have an exit instruction");
	}
	strline = analyse(strline);
	if (strline.empty())
		return ;
	std::istringstream iss(strline);
	std::vector<std::string> tokens;
	copy(std::istream_iterator<std::string>(iss), std::istream_iterator<std::string>(),	back_inserter(tokens));
	Instr->exec(tokens);
}

void	exec_file(char *str)
{
	Instruction *Instr = new Instruction();
	int	line = 1;

	std::ifstream file(str);
	if (file.fail())
	{
		std::cout << "File opening error" << std::endl;
		return ;
	}
	std::string strline;
	while (getline(file, strline) && !(Instr->getExit()))
	{
		try
		{
			parse_command(strline, Instr);
		}
		catch (std::exception const &e)
		{
			std::cout << "Line " << line  << " : " << e.what() << " (" << strline << ")" << std::endl;
			Instr->exit();
			break;
		}
		line++;
	}

	if (file.is_open())
		file.close();
	delete Instr;
}


void	exec_input()
{
	Instruction *Instr = new Instruction();
	int	line = 1;

	std::string strline = "start";
	while (strline.find(";;") > strline.size() != 0 && !(Instr->getExit()))
	{
		getline(std::cin, strline);
		try
		{
			parse_command(strline, Instr);
		}
		catch (std::exception const &e)
		{
			std::cout << "Line " << line  << " : " << e.what() << " (" << strline << ")" << std::endl;
			Instr->exit();
			break;
		}
		line++;
	}
}

int main (int ac, char **av)
{
	try
	{
		if (ac == 2)
			exec_file(av[1]);
		else
			exec_input();
	}
	catch (std::exception const &e)
	{
		std::cout << e.what() << std::endl;
	}
	return 0;
}
