#ifndef OPERANDFACTORY_HPP
# define OPERANDFACTORY_HPP
# include <list>
# include <map>
# include <math.h>
# include <cmath>
# include <iostream>
# include "IOperand.hpp"
# include "VMExceptions.hpp"

class OperandFactory
{
	public:
		OperandFactory();
		OperandFactory(OperandFactory const &src);
		virtual ~OperandFactory();
		OperandFactory &operator=(OperandFactory const &other);
		static OperandFactory *instance;
		std::list<const IOperand*> getStack() const;

		void _push(eOperandType type, std::string const &value);
		void _pop(eOperandType type, std::string const &value);
		void _dump(eOperandType type, std::string const &value);
		void _assert(eOperandType type, std::string const &value);
		void _add(eOperandType type, std::string const &value);
		void _sub(eOperandType type, std::string const &value);
		void _mul(eOperandType type, std::string const &value);
		void _div(eOperandType type, std::string const &value);
		void _mod(eOperandType type, std::string const &value);
		void _print(eOperandType type, std::string const &value);
		void _exit(eOperandType type, std::string const &value);

		IOperand const *createOperand(eOperandType type, std::string const &value) const;
		IOperand const *createInt8(std::string const &value) const;
		IOperand const *createInt16(std::string const &value) const;
		IOperand const *createInt32(std::string const &value) const;
		IOperand const *createFloat(std::string const &value) const;
		IOperand const *createDouble(std::string const &value) const;

		void HandleInstruction(std::string const &instr, eOperandType type, std::string const &value);
		eOperandType getTypeWithString(std::string type);		
	private:
		std::list<const IOperand*>	_stack;
		IOperand const *(OperandFactory::*_tab[5])(std::string const &value) const;
		std::map<std::string, void (OperandFactory::*)(eOperandType type, std::string const &value) > _instruction;
};

#endif