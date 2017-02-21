#ifndef EXCEPTION_HPP
#define EXCEPTION_HPP

#include <iostream>
#include <stdexcept>

class AVMException : public std::exception
{
	public:
		virtual const char *what() const throw();
		AVMException(std::string const &error);
		std::string getMess() const;
		AVMException(AVMException const & src);
		~AVMException() throw();

	private:
		AVMException &	operator=(AVMException const & src);
		AVMException();
		std::string _errMess;
};

#endif
