/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Operand.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlepeche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 21:31:49 by tlepeche          #+#    #+#             */
/*   Updated: 2017/02/18 00:02:53 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPERAND_HPP
# define OPERAND_HPP

#include <IOperand.hpp>
#include <limits.h>
#include <sstream>
#include <cfloat>
#include <Factory.hpp>
#include <math.h>

template <typename T>
class Operand : public IOperand
{
	public:
		Operand(std::string value, eOperandType type, int precision, const Factory *factory):
			_type(type), _precision(precision), _factory(factory)
		{
			long double tmp = std::stold(value);
			//		if (hasOverflow(tmp, _type))
			//			throw exception
			T	val = static_cast<T>(tmp);
	
			std::stringstream	ss;
			if (_type == Float || _type == Double)
				ss << std::fixed << val;
			else
				ss << val;
			ss >> _str;
		}

		int				getPrecision() const { return _precision; }
		eOperandType	getType() const { return _type; }
		Factory			*getFactory() const { return _factory; }

		IOperand const * operator+( IOperand const & rhs) const
		{
			std::stringstream ss;
			eOperandType t = rhs.getType() > _type ? rhs.getType() : _type;
			long double res = std::stold(_str) + std::stold(rhs.toString());
			//		if (hasOverflow(tmp, t))
			//			throw exception
			if (t == Float || t == Double)
				ss << std::fixed << res;
			else
				ss << res;
			return (_factory->createOperand(t, ss.str()));
		}

		IOperand const * operator-( IOperand const & rhs) const
		{
			std::stringstream ss;
			eOperandType t = rhs.getType() > _type ? rhs.getType() : _type;
			long double res = std::stold(_str) - std::stold(rhs.toString());
			//		if (hasOverflow(tmp, t))
			//			throw exception
			if (t == Float || t == Double)
				ss << std::fixed << res;
			else
				ss << res;
			return (_factory->createOperand(t, ss.str()));
		}

		IOperand const * operator*( IOperand const & rhs) const
		{
			std::stringstream ss;
			eOperandType t = rhs.getType() > _type ? rhs.getType() : _type;
			long double res = std::stold(_str) * std::stold(rhs.toString());
			//		if (hasOverflow(tmp, t))
			//			throw exception
			if (t == Float || t == Double)
				ss << std::fixed << res;
			else
				ss << res;
			return (_factory->createOperand(t, ss.str()));
		}

		IOperand const * operator/( IOperand const & rhs) const
		{
			std::stringstream ss;
			eOperandType t = rhs.getType() > _type ? rhs.getType() : _type;
			//			if (std::stold(rhs.toString()) == 0)
			//				throw exception
			long double res = std::stold(_str) / std::stold(rhs.toString());
			//		if (hasOverflow(tmp, t))
			//			throw exception
			if (t == Float || t == Double)
				ss << std::fixed << res;
			else
				ss << res;
			return (_factory->createOperand(t, ss.str()));
		}

		IOperand const * operator%( IOperand const & rhs) const
		{
			std::stringstream ss;
			eOperandType t = rhs.getType() > _type ? rhs.getType() : _type;
			//			if (std::stold(rhs.toString()) == 0)
			//				throw exception
			//			if (hasOverflow(tmp, t))
			//				throw exception
			if (t == Float || t == Double)
			{
				long double res = fmod(std::stold(_str), std::stold(rhs.toString()));
				ss << std::fixed << res;
			}
			else
			{
				long long res = std::stoll(_str) % std::stoll(rhs.toString());
				ss << res;
			}
			return (_factory->createOperand(t, ss.str()));
		}

		static IOperand const * Create() { return new Operand<T>(); }

		std::string const & toString() const { return _str; }

		~Operand() {}

		bool 	hasOverflow(long double r, eOperandType type) const
		{
			switch (type)
			{
				case (Int8):
					return (r > SCHAR_MAX || r < SCHAR_MIN);
				case (Int16):
					return  (r > SHRT_MAX || r < SHRT_MIN);
				case (Int32):
					return (r > INT_MAX || r < INT_MIN);
				case (Float):
					return (r > FLT_MAX || r < -FLT_MAX);
				case (Double):
					return (r > DBL_MAX || r < -DBL_MAX);
				break;
			}
			return (true);
		}

	private:
		Operand() {}
		Operand(Operand &src) { *this = src; }
		Operand &operator=(Operand const & src)
		{
			_type = src.getType();
			_precision = src.getPrecision();
			_factory = src.getFactory();
			return *this;
		}


		eOperandType	_type;
		int				_precision;
		const Factory	*_factory;
		std::string		_str;
};

#endif

