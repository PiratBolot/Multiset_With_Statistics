#pragma once

#include <stdexcept>
#include <string>

class EmptySetException : std::exception {
	public:
		explicit EmptySetException(const char* message) : msg(message) {};

		const char* what() const{
			return msg.c_str();
		}

	private:
		std::string msg;
};
