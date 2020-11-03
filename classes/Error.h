//
// Created by inejka on 02.11.2020.
//

#ifndef SEM3_LAB3_PPVIS_ERROR_H
#define SEM3_LAB3_PPVIS_ERROR_H

#include <string>
#include <iostream>

class Error {
public:
    Error(std::string name_of_file, std::string name_of_function, std::string how_to_solve)
            : name_of_file(name_of_file), name_of_function(name_of_function),how_to_solve(how_to_solve) {}

    void print();

private:
    std::string name_of_file, name_of_function, how_to_solve;
};


#endif //SEM3_LAB3_PPVIS_ERROR_H
