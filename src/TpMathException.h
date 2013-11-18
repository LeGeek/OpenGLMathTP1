/*
 * TpMathException.h
 *
 *  Created on: 14 nov. 2013
 *      Author: legeek
 */

#ifndef TPMATHEXCEPTION_H_
#define TPMATHEXCEPTION_H_

#include <exception>
#include <string>

class TpMathException : std::exception
{
	public:
		TpMathException(std::string message) throw();
		virtual ~TpMathException() throw();

		const char* what() const throw();

	private:
		std::string msg;
};

#include "TpMathException.hpp"

#endif /* TPMATHEXCEPTION_H_ */
