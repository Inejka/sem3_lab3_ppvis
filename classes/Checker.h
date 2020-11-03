//
// Created by inejka on 02.11.2020.
//

#ifndef SEM3_LAB3_PPVIS_CHECKER_H
#define SEM3_LAB3_PPVIS_CHECKER_H

#include "game_field.h"
#include <iostream>
#include "stations.h"
#include <fstream>
#include <string>

class Check {
public:
    bool check_game_field(Game_field &to_check);
private:
    void check_connections(Game_field &to_check);
};


#endif //SEM3_LAB3_PPVIS_CHECKER_H
