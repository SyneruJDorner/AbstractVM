#include "VMExceptions.hpp"

VMExceptions *VMExceptions::instance = new VMExceptions();

VMExceptions::VMExceptions()
{
	
}

VMExceptions::VMExceptions(VMExceptions const &src)
{
	*this = src;
}

VMExceptions::~VMExceptions()
{
    
}

void VMExceptions::operator=(VMExceptions const &other) 
{
	(void)other;
}

void VMExceptions::runtimeErrorMessage(const std::string &msg)
{
    throw std::runtime_error(msg);
}

//EXEPTION HANDLES
const char* VMExceptions::FileException::what() const throw()
{
	return ("Unable to read file.");
}

const char* VMExceptions::SemicolonException::what() const throw()
{
	return ("Error ';;' missing.");
}

const char* VMExceptions::ExitException::what() const throw()
{
	return ("Missing 'exit' instruction error.");
}

const char* VMExceptions::SyntaxException::what() const throw()
{
	return ("Syntax Error.");
}

const char* VMExceptions::OverflowException::what() const throw()
{
	return ("Value Overflow.");
}

const char* VMExceptions::UnderflowException::what() const throw()
{
	return ("Value Underflow.");
}

const char* VMExceptions::DifferentTypesException::what() const throw()
{
	return ("Asset error on different types.");
}

const char* VMExceptions::DifferentValuesException::what() const throw()
{
	return ("Asset error on different values.");
}

const char* VMExceptions::EmptyStackException::what() const throw()
{
	return ("Pop error on an empty stack.");
}

const char* VMExceptions::EmptyValueStackException::what() const throw()
{
	return ("Operation error on a stack that does not contain at least 2 elements.");
}

const char* VMExceptions::DivisionZeroException::what() const throw()
{
	return ("Division by zero error.");
}