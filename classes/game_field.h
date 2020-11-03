//
// Created by inejka on 15.10.2020.
//

#ifndef SEM3_LAB3_PPVIS_GAME_FIELD_H
#define SEM3_LAB3_PPVIS_GAME_FIELD_H

#include "stations.h"
#include <iostream>
#include <map>

class Game_field {
public:
    Game_field() {}

    void simulate();

    bool empty() const {
        for (int i = 0; i < alive_trains.size(); i++)if (alive_trains[i])return false;
        return true;
    }

    friend class Load;

    friend class Check;

    void print_log(){
        for(auto &i:log)
            std::cout << i.operation_type << i.quantity << i.type_type;
        log.clear();
    }


private:
    std::vector<Info> log;
    std::map<std::pair<std::string, std::string>, int> connections;
    bool mode;
    std::map<std::string, Station *> stations;
    std::vector<Train> trains;
    std::vector<bool> alive_trains;
};

#endif //SEM3_LAB3_PPVIS_GAME_FIELD_H
