#ifndef MACROS_H
#define MACROS_H

#include <stdio.h>
#include <iostream>

#define NOT_IMPLEMENTED "\e[34m[NOT IMPLEMENTED.]\e[0m"

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
            <<__func__<<"("<<__LINE__<<") - ("     \
            << x <<")\e[0m"<<std::endl; }

#define TRACEm(fmt,...) \
	fprintf(stderr, "\e[33m[TRACE] %s::%s:%d\t\t>" fmt\
	 "\e[0m\n",__FILE__,__func__,__LINE__, __VA_ARGS__)
#else
#define TRACE(M,...)
#endif

#endif /*MACROS_H*/
