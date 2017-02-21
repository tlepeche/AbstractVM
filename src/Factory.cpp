#include <Factory.hpp>
#include <Operand.hpp>

Factory::Factory()
{
	map[Int8] = &Factory::createInt8;
	map[Int16] = &Factory::createInt16;
	map[Int32] = &Factory::createInt32;
	map[Float] = &Factory::createFloat;
	map[Double] = &Factory::createDouble;
}

Factory::~Factory() {}

Factory::Factory(Factory & src)
{
	*this = src;
}

Factory &Factory::operator=(Factory & src)
{
	map = src.map;
	return *this;
}

IOperand const * Factory::createOperand(eOperandType type, std::string const & value) const
{
	IOperand const * (Factory::*f)(std::string const &value) const;
	f = map.at(type);
	return ((*this.*f)(value));
}

IOperand const * Factory::createInt8(std::string const & value) const
{ return new Operand<int8_t>(value, Int8, 0, this); }

IOperand const * Factory::createInt16(std::string const & value) const
{ return new Operand<int16_t>(value, Int16, 1, this); }

IOperand const * Factory::createInt32(std::string const & value) const
{ return new Operand<int32_t>(value, Int32, 2, this); }

IOperand const * Factory::createFloat(std::string const & value) const
{ return new Operand<float>(value, Float, 3, this); }

IOperand const * Factory::createDouble(std::string const & value) const
{ return new Operand<double>(value, Double, 4, this); }
