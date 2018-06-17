//
// EPITECH PROJECT, 2018
// zappy
// File description:
// ai
//

#include <string>

namespace zappy {
	class Exception : public std::exception {
	public:
		Exception(const std::string &ctx = "Unknow context",
			  const std::string &msg = "Unknown error");
		~Exception() = default;
		
		virtual const char* what() const throw();
		virtual const char* where() const throw();
	private:
		std::string _context;
		std::string _message;
	};
}
