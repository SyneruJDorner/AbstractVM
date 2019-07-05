#ifndef CALCULATOR_HPP
# define CALCULATOR_HPP

#include "IOperand.hpp"
#include "OperandFactory.hpp"

template <typename T>
class Operand : public IOperand
{
	public: 
		int getPrecision() const
		{
			return _precision;
		}

		eOperandType getType() const
		{
			return _type;
		}

		IOperand const *operator+(IOperand const &other) const
		{
			int prec = (other.getPrecision() >= _precision) ? other.getPrecision() : _precision;
			return (OperandFactory::instance->createOperand((eOperandType)prec, (std::to_string(stod(other.toString()) + stod(_str)))));
		}

		IOperand const *operator-(IOperand const &other) const
		{
			int prec = (other.getPrecision() >= _precision) ? other.getPrecision() : _precision;
			return (OperandFactory::instance->createOperand((eOperandType)prec, (std::to_string(stod(_str) - stod(other.toString())))));

		}

		IOperand const *operator*(IOperand const &other) const
		{
			int prec = (other.getPrecision() >= _precision) ? other.getPrecision() :_precision;
			return (OperandFactory::instance->createOperand((eOperandType)prec, (std::to_string(stod(other.toString()) *stod(_str)))));

		}

		IOperand const *operator/(IOperand const &other) const
		{
			double result = stod(_str);

			if (!stod(other.toString()))
				throw VMExceptions::DivisionZeroException();
			
			int prec = (other.getPrecision() >= _precision) ? other.getPrecision() : _precision;

			if (result != 0)
				result = stod(_str) / stod(other.toString());
			return (OperandFactory::instance->createOperand((eOperandType)prec, (std::to_string(result))));
		}

		IOperand const *operator%(IOperand const &other) const
		{
			if (!stod(other.toString()))
				throw VMExceptions::DivisionZeroException();

			int prec = (other.getPrecision() >= _precision) ? other.getPrecision() : _precision;
			if (other.getType() == 3 || other.getType() == 4 || _type == 3 || _type == 4)
				return OperandFactory::instance->createOperand((eOperandType)prec, std::to_string(fmod(std::stod(other.toString()), std::stod(_str))));
			else
				return (OperandFactory::instance->createOperand((eOperandType)prec, (std::to_string(std::stoi(other.toString()) % std::stoi(_str)))));
		}

		std::string const &toString() const
		{
			return (_str);
		}

		~Operand ()
		{

		}

		Operand (T value, eOperandType type): _value(value), _type(type)
		{
			_str = std::to_string(value);
			_precision = type;
		}

	private:
		T 				_value;
		eOperandType 	_type;
		int 			_precision;
		std::string		_str;
	};
#endif