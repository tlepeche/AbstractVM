#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
//#include <start.h>
#include <Instruction.hpp>

std::string	analyse(std::string line)
{
	size_t		start;

	start = line.find(";");
	if (start < line.size())
		line.erase(start, line.size());
	return line;
}

int main (int ac, char **av)
{
	Instruction *Instr = new Instruction();
	if (ac == 2)
	{
		std::ifstream file(av[1]);
		if (file.fail())
		{
			std::cout << "File opening error" << std::endl;
			return 0;
		}
		std::string ALL;
		std::string strline;
		while (getline(file, strline))
		{
			if (strline.find(";;") < strline.size())
				break;
			strline = analyse(strline);
			if (strline.empty())
				continue ;

			std::istringstream		iss(strline);
			std::vector<std::string> tokens;
			//token = tableau contenant l'instruction de la ligne + value
			copy(std::istream_iterator<std::string>(iss), std::istream_iterator<std::string>(),	back_inserter(tokens));
			Instr->exec(tokens);
			
/*			for (std::vector<std::string>::iterator i = tokens.begin(); i != tokens.end(); i++)
				std::cout << *i << std::endl;*/
//			std::cout << std::endl;




		}
		if (file.is_open())
			file.close();
		delete Instr;
	}
	return 0;
}
