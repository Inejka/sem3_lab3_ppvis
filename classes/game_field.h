//
// Created by inejka on 15.10.2020.
//

#ifndef SEM3_LAB3_PPVIS_GAME_FIELD_H
#define SEM3_LAB3_PPVIS_GAME_FIELD_H

#include "stations.h"
#include <iostream>

class Game_field {
public:
    Game_field() {}

    void simulate();

    bool empty() const { return its_trains.empty(); }

    friend class Load;

    friend class Check;


private:

    int *game_mode_select();
    bool its_mode;
    std::vector<Station *> its_stations;
    std::vector<Train> its_trains;
};

#endif //SEM3_LAB3_PPVIS_GAME_FIELD_H
