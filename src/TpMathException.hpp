/*
 * TpMathException.hpp
 *
 *  Created on: 14 nov. 2013
 *      Author: legeek
 */

#ifndef TPMATHEXCEPTION_HPP_
#define TPMATHEXCEPTION_HPP_

#include "TpMathException.h"

inline TpMathException::TpMathException(std::string message) throw() : msg(message) {}
inline TpMathException::~TpMathException() throw() {}

inline const char* TpMathException::what() const throw() { return msg.c_str(); }


#endif /* TPMATHEXCEPTION_HPP_ */
