#ifndef MACROS_H
#define MACROS_H

#include <stdio.h>
#include <iostream>

#define NOT_IMPLEMENTED TRACE("\e[34m[NOT IMPLEMENTED.]")
#define OK TRACE("\e[32m[OK]")
#define FAILED TRACE("\e[31m[FAILED]")

/**
 * This macro can be used to write usefull trace messages.
 * Example of use:<br>
 * `TRACE("Something went wrong here");`<br>
 * `TRACE(exception.toString());`<p>
 *
 * Output includes the File name, function and line number.
 *
 */
#ifdef DEBUG
#define TRACE(x) \
{ std::cerr <<"\e[33m"<<"[TRACE] "<<__FILE__<<"::" \
            <<__func__<<":"<<__LINE__<<" >>\e[34m " \
            << x <<"\e[0m"<<std::endl; }

#define TRACEm(fmt,...) \
	fprintf(stderr, "\e[33m[TRACE] %s::%s:%d >>\e[34m " fmt\
	 "\e[0m\n",__FILE__,__func__,__LINE__, __VA_ARGS__)

#define TRACE_ERROR(x) \
{ std::cerr <<"\e[33m"<<"[TRACE] "<<__FILE__<<"::" \
            <<__func__<<":"<<__LINE__<<" >>\e[31m " \
            << x <<"\e[0m"<<std::endl; }

#define TRACEm_ERROR(fmt,...) \
	fprintf(stderr, "\e[33m[TRACE] %s::%s:%d >>\e[31m " fmt\
	 "\e[0m\n",__FILE__,__func__,__LINE__, __VA_ARGS__)
#else
#define TRACE(x)
#define TRACEm(fmt,...)
#define TRACE_ERROR(x)
#define TRACEm_ERROR(fmt,...)
#endif

#ifdef PREC
#define EXPECT_ZERO(x) if(x){\
	TRACE_ERROR(#x)\
	throw CryptokiException(__func__,666);}

#define EXPECT_N_ZERO(x) if(!x){\
	TRACE_ERROR(#x)\
	throw CryptokiException(__func__,666);}
#else
#define EXPECT_ZERO(x)
#define EXPECT_N_ZERO(x)
#endif
#define PRECONDITION(x) EXPECT_N_ZERO(x)

#endif /*MACROS_H*/
