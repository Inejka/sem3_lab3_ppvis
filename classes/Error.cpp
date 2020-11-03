//
// Created by inejka on 02.11.2020.
//
#include "Error.h"
#define endl std::endl
void Error::print() {
    std::cout << "Exception was thrown from " << name_of_file << endl << "From function " << name_of_function << endl << "Advice how to solve: " << how_to_solve ;
}
