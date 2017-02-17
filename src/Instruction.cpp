/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Instruction.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlepeche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 16:58:13 by tlepeche          #+#    #+#             */
/*   Updated: 2017/02/18 00:27:08 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Instruction.hpp>
#include <regex>

Instruction::Instruction()
{
	_action["push"] = &Instruction::push;
	_action["pop"] = &Instruction::pop;
	_action["dump"] = &Instruction::dump;
	_action["add"] = &Instruction::add;
	_action["sub"] = &Instruction::sub;
	_action["mul"] = &Instruction::mul;
	_action["div"] = &Instruction::div;
	_action["mod"] = &Instruction::mod;
	_action["assert"] = &Instruction::assert;
	_action["print"] = &Instruction::print;
	_action["exit"] = &Instruction::exit;
	_factory = new Factory();
	_stack.clear();
}

Instruction::~Instruction() {}

Instruction::Instruction(Instruction & src)
{
	(void)src;
	//	*this = src;
}

Instruction &Instruction::operator=(Instruction &src)
{
	(void)src;
	return *this;
}

Factory		*Instruction::getFactory() { return _factory; }

std::list<IOperand	const*>	Instruction::getStack() { return _stack; }

std::map<std::string, void (Instruction::*)(std::vector<std::string>::iterator &it)> Instruction::getAction() { return _action; }

void		Instruction::exec(std::vector<std::string> token)
{
	std::map<std::string, void (Instruction::*)(std::vector<std::string>::iterator &it)>::iterator iter;
	for (std::vector<std::string>::iterator i = token.begin(); i != token.end() ; ++i)
	{
		iter = _action.find(*i);
		if (i->compare("push") == 0 || i->compare("assert") == 0)
			i++;
		if (iter != _action.end())
			(this->*(iter->second))(i);
	}
}

eOperandType Instruction::findType(std::string str)
{
	eOperandType type;
	if (std::regex_match(str, std::regex("(int8)\\(-?[0-9]+\\)")))
		type = Int8;
	else if (std::regex_match(str, std::regex("(int16)\\(-?[0-9]+\\)")))
		type = Int16;
	else if (std::regex_match(str, std::regex("(int32)\\(-?[0-9]+\\)")))
		type = Int32;
	else if (std::regex_match(str, std::regex("(float)\\(-?[0-9]+(\\.[0-9]+)?\\)")))
		type = Float;
	else if (std::regex_match(str, std::regex("(double)\\(-?[0-9]+(\\.[0-9]+)?\\)"))) 
		type = Double;
//	else
//		throw AbstractException("Unknow type value.", token, __LINE__, "Machine.cpp");
		return type;
}

void	Instruction::push(std::vector<std::string>::iterator &it)
{
	eOperandType type  = findType(*it);
		std::string test;
	std::string val = it->substr(it->find("(") + 1, it->find(")") - it->find("(") - 1);
	_stack.push_front(_factory->createOperand(type, val));
	std::cout << val << std::endl;
	std::cout << *it << std::endl;
}

void	Instruction::pop(std::vector<std::string>::iterator &it)
{
	std::cout << *it << std::endl;
}

void	Instruction::dump(std::vector<std::string>::iterator &it)
{
	std::cout << *it << std::endl;
}

void	Instruction::add(std::vector<std::string>::iterator &it)
{
	std::cout << *it << std::endl;
}

void	Instruction::sub(std::vector<std::string>::iterator &it)
{
	std::cout << *it << std::endl;
}

void	Instruction::mul(std::vector<std::string>::iterator &it)
{
	std::cout << *it << std::endl;
}

void	Instruction::div(std::vector<std::string>::iterator &it)
{
	std::cout << *it << std::endl;
}

void	Instruction::mod(std::vector<std::string>::iterator &it)
{
	std::cout << *it << std::endl;
}

void	Instruction::assert(std::vector<std::string>::iterator &it)
{
	std::cout << *it << std::endl;
}

void	Instruction::print(std::vector<std::string>::iterator &it)
{
	std::cout << *it << std::endl;
}

void	Instruction::exit(std::vector<std::string>::iterator &it)
{
	std::cout << *it << std::endl;
}
