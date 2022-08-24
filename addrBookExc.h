/*
CS 202 Assignment 10

Name: Keith Beauvais, 5005338658, CS 202 Assignment 10
*/
#ifndef H_ADDRBOOK_EXC
#define H_ADDRBOOK_EXC

#include <stdexcept>

/*
Runtime error is inherited to make an error class. The string value is passed into error 
will call the constructor of and pass the parameter value to it.
*/
class Error: public std::runtime_error{
    public:
    Error(std::string parameter=""):runtime_error(parameter){};
};


#endif
