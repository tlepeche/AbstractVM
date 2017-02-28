/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Instruction.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlepeche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 16:58:13 by tlepeche          #+#    #+#             */
/*   Updated: 2017/02/28 21:38:49 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Instruction.hpp>
#include <Exception.hpp>
#include <regex>

Instruction::Instruction(): _exit(false)
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
	*this = src;
}

Instruction &Instruction::operator=(Instruction &src)
{
	_stack = src.getStack();
	_exit = src.getExit();
	_action = src.getAction();
	_factory = src.getFactory();
	return *this;
}

bool		Instruction::getExit() { return _exit; }

Factory		*Instruction::getFactory() { return _factory; }

std::list<IOperand	const*>	Instruction::getStack() { return _stack; }

std::map<std::string, void (Instruction::*)(std::vector<std::string>::iterator &it)> Instruction::getAction() { return _action; }

void		Instruction::exec(std::vector<std::string> token)
{
	std::map<std::string, void (Instruction::*)(std::vector<std::string>::iterator &it)>::iterator iter;

	if (!_exit)
	{
		for (std::vector<std::string>::iterator i = token.begin(); i != token.end() ; ++i)
		{
			if (token.size() == 1 || (token.size() == 2 && (i->compare("push") == 0 || i->compare("assert") == 0)))
			{
				iter = _action.find(*i);
				if (i->compare("push") == 0 || i->compare("assert") == 0)
					i++;
				if (iter != _action.end())
					(this->*(iter->second))(i);
				else
					throw AVMException("Error : Unknowm instruction");
			}
			else
				throw AVMException("Error : Unknowm instruction");
		}
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
	else
		throw AVMException("Error : lexical / synthax error");
	return type;
}

void	Instruction::push(std::vector<std::string>::iterator &it)
{
	eOperandType type  = findType(*it);
	std::string test;
	std::string val = it->substr(it->find("(") + 1, it->find(")") - it->find("(") - 1);
	_stack.push_front(_factory->createOperand(type, val));
}

void	Instruction::pop(std::vector<std::string>::iterator &it)
{
	if (!(_stack.empty()))
		_stack.pop_front();
	else
		throw AVMException("Error : Stack is empty");
}

void	Instruction::dump(std::vector<std::string>::iterator &it)
{
	for (std::list<IOperand const*>::iterator it = _stack.begin(); it != _stack.end(); ++it)
	{
		std::cout << (*it)->toString() << std::endl;
	}
}

void	Instruction::assert(std::vector<std::string>::iterator &it)
{
	if (_stack.empty())
		throw AVMException("Error : Stack is empty");
	std::list<const IOperand* >::iterator tmp = _stack.begin();

	long double test1, test2;

	test1 = std::stold((*tmp)->toString());
	test2 = std::stold(it->substr(it->find("(") + 1, it->find(")") - it->find("(") - 1));
	if (!(findType((*it)) == (*tmp)->getType() && test1 == test2))
		throw AVMException("Error : Assert is not true");
}

void	Instruction::add(std::vector<std::string>::iterator &it)
{
	if (_stack.size() < 2)
		throw AVMException("Error : Stack has less than 2 values");
	const IOperand *v1 = *(_stack.begin());
	_stack.pop_front();
	const IOperand *v2 = *(_stack.begin());
	_stack.pop_front();
	_stack.push_front((*v2)+(*v1));
}

void	Instruction::sub(std::vector<std::string>::iterator &it)
{
	if (_stack.size() < 2)
		throw AVMException("Error : Stack has less than 2 values");
	const IOperand *v1 = *(_stack.begin());
	_stack.pop_front();
	const IOperand *v2 = *(_stack.begin());
	_stack.pop_front();
	_stack.push_front((*v2)-(*v1));
}

void	Instruction::mul(std::vector<std::string>::iterator &it)
{
	if (_stack.size() < 2)
		throw AVMException("Error : Stack has less than 2 values");
	const IOperand *v1 = *(_stack.begin());
	_stack.pop_front();
	const IOperand *v2 = *(_stack.begin());
	_stack.pop_front();
	_stack.push_front((*v2)*(*v1));
}


void	Instruction::div(std::vector<std::string>::iterator &it)
{
	if (_stack.size() < 2)
		throw AVMException("Error : Stack has less than 2 values");
	if ((*_stack.begin())->toString() == "0")
		throw AVMException("Error : Division by 0");
	const IOperand *v1 = *(_stack.begin());
	_stack.pop_front();
	const IOperand *v2 = *(_stack.begin());
	_stack.pop_front();
	_stack.push_front((*v2)/(*v1));

}

void	Instruction::mod(std::vector<std::string>::iterator &it)
{
	if (_stack.size() < 2)
		throw AVMException("Error : Stack has less than 2 values");
	if ((*_stack.begin())->toString() == "0")
		throw AVMException("Error : Modulo by 0");
	const IOperand *v1 = *(_stack.begin());
	_stack.pop_front();
	const IOperand *v2 = *(_stack.begin());
	_stack.pop_front();
	_stack.push_front((*v2)%(*v1));
}

void	Instruction::print(std::vector<std::string>::iterator &it)
{
	if (_stack.empty())
		throw AVMException("Error : Stack is empty");
	if ((*_stack.begin())->getType() != Int8)
		throw AVMException("Error : Assert is not true");
	if ((*_stack.begin())->getType() == Int8)
	{
		char print = std::stoi((*_stack.begin())->toString());
		std::cout << print << std::endl;	
	}
}

void	Instruction::exit(std::vector<std::string>::iterator &it)
{
	_exit = true;
}

void	Instruction::exit()
{
	while (!_stack.empty())
		_stack.pop_front();
}
