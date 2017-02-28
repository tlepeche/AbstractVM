/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Operand.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlepeche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 21:31:49 by tlepeche          #+#    #+#             */
/*   Updated: 2017/02/28 21:34:16 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPERAND_HPP
# define OPERAND_HPP

#include <IOperand.hpp>
#include <Exception.hpp>
#include <limits.h>
#include <sstream>
#include <cfloat>
#include <Factory.hpp>
#include <iomanip>
#include <math.h>

template <typename T>
class Operand : public IOperand
{
	public:
		Operand(std::string value, eOperandType type, int precision, const Factory *factory):
			_str(value), _type(type), _precision(precision), _factory(factory)
	{
		long double tmp = std::stold(value);
		if (hasOverflow(tmp, _type))
			throw AVMException("Error : Overflow / Underflow during Operand creation");
	}

		int				getPrecision() const { return _precision; }
		eOperandType	getType() const { return _type; }
		Factory			*getFactory() const { return _factory; }

		IOperand const * operator+( IOperand const & rhs) const
		{
			std::stringstream ss;
			eOperandType t = rhs.getPrecision() > _precision ? rhs.getType() : _type;
			long double res = std::stold(_str) + std::stold(rhs.toString());
			if (hasOverflow(res, t))
				throw AVMException("Error : Overflow / Underflow during Operand creation");
			int prec = _str.size() > rhs.toString().size() ? _str.size() : rhs.toString().size(); 			
			if (t == Float || t == Double)
				ss << std::setprecision(prec) << res;
			else
				ss << res;
			return (_factory->createOperand(t, ss.str()));
		}

		IOperand const * operator-( IOperand const & rhs) const
		{
			std::stringstream ss;
			eOperandType t = rhs.getPrecision() > _precision ? rhs.getType() : _type;
			long double res = std::stold(_str) - std::stold(rhs.toString());
			if (hasOverflow(res, t))
				throw AVMException("Error : Overflow / Underflow during Operand creation");
			int prec = _str.size() > rhs.toString().size() ? _str.size() : rhs.toString().size(); 			
			if (t == Float || t == Double)
				ss << std::setprecision(prec) << res;
			else
				ss << res;
			return (_factory->createOperand(t, ss.str()));
		}

		IOperand const * operator*( IOperand const & rhs) const
		{
			std::stringstream ss;
			eOperandType t = rhs.getPrecision() > _precision ? rhs.getType() : _type;
			long double res = std::stold(_str) * std::stold(rhs.toString());
			if (hasOverflow(res, t))
				throw AVMException("Error : Overflow / Underflow during Operand creation");
			int prec = _str.size() + rhs.toString().size(); 			
			if (t == Float || t == Double)
				ss << std::setprecision(prec) << res;
			else
				ss << res;
			return (_factory->createOperand(t, ss.str()));
		}

		IOperand const * operator/( IOperand const & rhs) const
		{
			std::stringstream ss;
			eOperandType t = rhs.getPrecision() > _precision ? rhs.getType() : _type;
			long double res = std::stold(_str) / std::stold(rhs.toString());
			if (hasOverflow(res, t))
				throw AVMException("Error : Overflow / Underflow during Operand creation");
			int prec = _str.size() > rhs.toString().size() ? _str.size() : rhs.toString().size(); 			
			if (t == Float || t == Double)
				ss << std::setprecision(prec) << res;
			else
				ss << res;
			return (_factory->createOperand(t, ss.str()));
		}

		IOperand const * operator%( IOperand const & rhs) const
		{
			std::stringstream ss;
			eOperandType t = rhs.getPrecision() > _precision ? rhs.getType() : _type;
			if (t == Float || t == Double)
			{
				long double res = fmod(std::stold(_str), std::stold(rhs.toString()));
				int prec = _str.size() > rhs.toString().size() ? _str.size() : rhs.toString().size(); 			
				ss << std::setprecision(prec) << res;
				if (hasOverflow(res, t))
					throw AVMException("Error : Overflow / Underflow during Operand creation");
			}
			else
			{
				long long res = std::stoll(_str) % std::stoll(rhs.toString());
				ss << res;
				if (hasOverflow(res, t))
					throw AVMException("Error : Overflow / Underflow during Operand creation");
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

