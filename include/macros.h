#ifndef MACROS_H
#define MACROS_H

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
#define TRACE(x) do                                \
{ std::cerr <<"\e[33m"<<"[TRACE] "<<__FILE__<<"::" \
            <<__func__<<"("<<__LINE__<<") - ("     \
            << x <<")\e[0m"<<std::endl; }          \
    while (0)

#endif /*MACROS_H*/
