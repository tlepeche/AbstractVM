/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Instruction.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlepeche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 16:54:32 by tlepeche          #+#    #+#             */
/*   Updated: 2017/02/21 21:09:11 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <IOperand.hpp>
#include <map>
#include <list>
#include <vector>
#include <Factory.hpp>

class Instruction
{
	public:
		Instruction();
		~Instruction();

		std::list<IOperand	const*>	getStack();
		bool						getExit();
		std::map<std::string, void (Instruction::*)(std::vector<std::string>::iterator &it)> getAction();
		Factory					*getFactory();
		
		eOperandType			findType(std::string str);
		void	exec(std::vector<std::string> token);
		void	exit();

	private:
		void	push(std::vector<std::string>::iterator &it);
		void	pop(std::vector<std::string>::iterator &it);
		void	dump(std::vector<std::string>::iterator &it);
		void	add(std::vector<std::string>::iterator &it);
		void	sub(std::vector<std::string>::iterator &it);
		void	mul(std::vector<std::string>::iterator &it);
		void	div(std::vector<std::string>::iterator &it);
		void	mod(std::vector<std::string>::iterator &it);
		void	assert(std::vector<std::string>::iterator &it);
		void	print(std::vector<std::string>::iterator &it);
		void	exit(std::vector<std::string>::iterator &it);

		Instruction(Instruction &src);
		Instruction	&operator=(Instruction &src);

		std::list<IOperand const*>	_stack;
		std::map<std::string, void (Instruction::*)(std::vector<std::string>::iterator &it)> _action;
		Factory					*_factory;
		bool					_exit;
};
