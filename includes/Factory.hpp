#ifndef FACTORY_HPP
# define FACTORY_HPP

#include <IOperand.hpp>
#include <map>
#include <limits.h>

class Factory
{
	public :
		Factory();
		~Factory();
		Factory(Factory & src);
		Factory &operator=(Factory & src);
		
		IOperand const * createOperand( eOperandType type, std::string const & value ) const;
		std::map<eOperandType, IOperand const * (Factory::*)( std::string const & value ) const> map;

	private:
		IOperand const * createInt8( std::string const & value ) const;
		IOperand const * createInt16( std::string const & value ) const;
		IOperand const * createInt32( std::string const & value ) const;
		IOperand const * createFloat( std::string const & value ) const;
		IOperand const * createDouble( std::string const & value ) const;
};

#endif
