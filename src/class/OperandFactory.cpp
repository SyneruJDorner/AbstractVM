#include "OperandFactory.hpp"
# include "Operand.hpp"

OperandFactory *OperandFactory::instance = new OperandFactory();

OperandFactory::OperandFactory()
{
	_tab[Int8] = &OperandFactory::createInt8;
	_tab[Int16] = &OperandFactory::createInt16;
	_tab[Int32] = &OperandFactory::createInt32;
	_tab[Float] = &OperandFactory::createFloat;
	_tab[Double] = &OperandFactory::createDouble;

	_instruction["push"] = &OperandFactory::_push;
	_instruction["pop"] = &OperandFactory::_pop;
	_instruction["dump"] = &OperandFactory::_dump;
	_instruction["assert"] = &OperandFactory::_assert;
	_instruction["add"] = &OperandFactory::_add;
	_instruction["sub"] = &OperandFactory::_sub;
	_instruction["mul"] = &OperandFactory::_mul;
	_instruction["div"] = &OperandFactory::_div;
	_instruction["mod"] = &OperandFactory::_mod;
	_instruction["print"] = &OperandFactory::_print;
	_instruction["exit"] = &OperandFactory::_exit;
}

void OperandFactory::_push(eOperandType type, std::string const &value)
{
	const IOperand *result = createOperand(type, value);
	_stack.push_front(result);
}

void OperandFactory::_pop(eOperandType type, std::string const &value)
{
	(void)value;
	(void)type;
	if (_stack.empty())
		throw VMExceptions::EmptyStackException();
	_stack.erase(_stack.begin());
}

void OperandFactory::_dump(eOperandType type, std::string const &value)
{
	(void)value;
	(void)type;
	std::list<const IOperand*>::iterator p = _stack.begin();
	while (p != _stack.end())
		std::cout << (*p++)->toString() << std::endl;
}

void OperandFactory::_assert(eOperandType type, std::string const &value)
{
	std::list<const IOperand*>::iterator p = _stack.begin();

	if (type != (*p)->getType())
		throw VMExceptions::DifferentTypesException();
	if (stod(value) != stod((*p)->toString()))
		throw VMExceptions::DifferentValuesException();
}

void OperandFactory::_add(eOperandType type, std::string const &value)
{
	(void)value;
	(void)type;
	std::list<const IOperand*>::iterator p = _stack.begin();
	IOperand const *result;

	if (_stack.size() < 2)
		throw VMExceptions::EmptyValueStackException();
	
	const IOperand *val_1 = *(++p);
	const IOperand *val_2 = *(--p);

	result = *val_1 + *val_2;
	instance->_pop(Int8, "");
	instance->_pop(Int8, "");
	_stack.push_front(result);
}

void OperandFactory::_sub(eOperandType type, std::string const &value)
{
	(void)value;
	(void)type;
	std::list<const IOperand*>::iterator p = _stack.begin();
	IOperand const *result;

	if (_stack.size() < 2)
		throw VMExceptions::EmptyValueStackException();
	
	const IOperand *val_1 = *(++p);
	const IOperand *val_2 = *(--p);

	result = *val_1 - *val_2;
	instance->_pop(Int8, "");
	instance->_pop(Int8, "");
	_stack.push_front(result);
}

void OperandFactory::_mul(eOperandType type, std::string const &value)
{
	(void)value;
	(void)type;
	std::list<const IOperand*>::iterator p = _stack.begin();
	IOperand const *result;

	if (_stack.size() < 2)
		throw VMExceptions::EmptyValueStackException();
	
	const IOperand *val_1 = *(++p);
	const IOperand *val_2 = *(--p);

	result = *val_1 * *val_2;
	instance->_pop(Int8, "");
	instance->_pop(Int8, "");
	_stack.push_front(result);
}

void OperandFactory::_div(eOperandType type, std::string const &value)
{
	(void)value;
	(void)type;
	std::list<const IOperand*>::iterator p = _stack.begin();
	IOperand const *result;

	if (_stack.size() < 2)
		throw VMExceptions::EmptyValueStackException();
	
	const IOperand *val_1 = *(++p);
	const IOperand *val_2 = *(--p);

	result =  *val_1 / *val_2;
	instance->_pop(Int8, "");
	instance->_pop(Int8, "");
	_stack.push_front(result);
}

void OperandFactory::_mod(eOperandType type, std::string const &value)
{
	(void)value;
	(void)type;
	std::list<const IOperand*>::iterator p = _stack.begin();
	IOperand const *result;

	const IOperand *val_1 = *(++p);
	const IOperand *val_2 = *(--p);

	result = *val_1 % *val_2;
	instance->_pop(Int8, "");
	instance->_pop(Int8, "");
	_stack.push_front(result);
}

void OperandFactory::_print(eOperandType type, std::string const &value)
{
	(void)value;
	(void)type;
	if ((*_stack.begin())->getType())
		throw VMExceptions::DifferentTypesException();
	printf("%c\n", std::stoi((*_stack.begin())->toString()));
}

void OperandFactory::_exit(eOperandType type, std::string const &value)
{
	(void)value;
	(void)type;
	std::exit(0);
}

IOperand const *OperandFactory::createOperand( eOperandType type, std::string const &value ) const
{
	IOperand const *result = NULL;
	result = (this->*_tab[type])(value);
	return (result);
}

IOperand const *OperandFactory::createInt8( std::string const &value ) const
{
	double nb = stod(value);

	if (nb > 127)
		throw VMExceptions::OverflowException();
	if (nb < -127)
		throw VMExceptions::UnderflowException();
	return (new Operand<char>((char)nb, Int8));
}

IOperand const *OperandFactory::createInt16( std::string const &value ) const
{
	double nb = stod(value);

	if (nb > 32767)
		throw VMExceptions::OverflowException();
	if (nb < -32768)
		throw VMExceptions::UnderflowException();
	return (new Operand<short int>((short int)nb, Int16));
}

IOperand const *OperandFactory::createInt32( std::string const &value ) const
{
	double nb = stod(value);

	if (nb > 2147483647)
		throw VMExceptions::OverflowException();
	if (nb < -2147483648)
		throw VMExceptions::UnderflowException();
	return (new Operand<long int>((long int)nb, Int32));
}

IOperand const *OperandFactory::createFloat( std::string const &value ) const
{
	double nb = stod(value);

	if (!isfinite(nb) && nb > 0)
		throw VMExceptions::OverflowException();
	if (!isfinite(nb) && nb < 0)
		throw VMExceptions::UnderflowException();
	return (new Operand<float>((float)nb, Float));
}

IOperand const *OperandFactory::createDouble( std::string const &value ) const
{
	double nb = stod(value);

	if (!isfinite(nb) && nb > 0)
		throw VMExceptions::OverflowException();
	if (!isfinite(nb) && nb < 0)
		throw VMExceptions::UnderflowException();
	return (new Operand<double>((double)nb, Double));
}

OperandFactory::~OperandFactory()
{

}

OperandFactory::OperandFactory(OperandFactory const &src)
{
	*this = src;
}

void OperandFactory::HandleInstruction(std::string const &instr, eOperandType type, std::string const &value)
{
	(this->*_instruction[instr])(type, value);
}

OperandFactory &OperandFactory::operator=(OperandFactory const &other)
{
	if (this != &other)
		this->_stack = other.getStack();
	return (*this);
}

std::list<const IOperand*> OperandFactory::getStack() const
{
	return (_stack);
}

eOperandType OperandFactory::getTypeWithString(std::string type)
{
	std::string names[5] =
	{
		"Int8",
		"Int16",
		"Int32",
		"Float",
		"Double"
	};
	
	if (!type.compare(names[0]))
		return (Int8);
	if (!type.compare(names[1]))
		return (Int16);
	if (!type.compare(names[2]))
		return (Int32);
	if (!type.compare(names[3]))
		return (Float);
	if (!type.compare(names[4]))
		return (Double);
	return (Int8);
}