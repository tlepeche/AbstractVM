#include <Exception.hpp>

AVMException::AVMException() {}

AVMException::AVMException(std::string const & error)
{
	_errMess = error;
}

AVMException::AVMException(AVMException const &src) { *this = src; }

AVMException::~AVMException() throw() {}

AVMException	&AVMException::operator=(AVMException const & src)
{
	_errMess = src.getMess();
	return *this;
}

std::string	AVMException::getMess() const { return _errMess; }

const char*AVMException::what() const throw() { return _errMess.c_str(); }
