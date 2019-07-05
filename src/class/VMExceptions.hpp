#ifndef VMEXCEPTIONS_HPP
# define VMEXCEPTIONS_HPP
# include <stdexcept>
# include <string>

class VMExceptions
{
	public:
		VMExceptions();
		VMExceptions(VMExceptions const &src);
		virtual ~VMExceptions();
		void operator=(VMExceptions const &other);
		static VMExceptions *instance;
		void runtimeErrorMessage(const std::string &msg);
		struct FileException : public std::exception
		{
			virtual const char* what() const throw();
		};

		struct SemicolonException : public std::exception
		{
			virtual const char* what() const throw();
		};

		struct ExitException : public std::exception
		{
			virtual const char* what() const throw();
		};

		struct SyntaxException : public std::exception
		{
			virtual const char* what() const throw();
		};

		struct OverflowException : public std::exception
		{
			virtual const char* what() const throw();
		};

		struct UnderflowException : public std::exception
		{
			virtual const char* what() const throw();
		};

		struct DifferentTypesException : public std::exception
		{
			virtual const char* what() const throw();
		};

		struct DifferentValuesException : public std::exception
		{
			virtual const char* what() const throw();
		};

		struct  EmptyStackException : public std::exception
		{
			virtual const char* what() const throw();
		};

		struct EmptyValueStackException : public std::exception
		{
			virtual const char* what() const throw();
		};

		struct DivisionZeroException : public std::exception
		{
			virtual const char* what() const throw();
		};
};
#endif
