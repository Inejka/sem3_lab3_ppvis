//
// Created by inejka on 02.11.2020.
//

#ifndef SEM3_LAB3_PPVIS_LOADER_H
#define SEM3_LAB3_PPVIS_LOADER_H

#include "game_field.h"
#include <iostream>
#include "stations.h"
#include <fstream>
#include <string>
#include "Error.h"

class Load {
public:
    bool load_game_field(std::string load_from, Game_field &to_load,const int &mode)noexcept(false);

private:

    Train load_train(std::fstream &file);

    std::vector<std::string> load_route(std::fstream &file);

    Station *load_station(std::fstream &file);

    std::vector<Passenger> load_to_spawn_passenger(std::fstream &file);

    std::vector<Cargo> load_to_spawn_cargo(std::fstream &file);

    std::map<std::pair<std::string,std::string>,int> load_connections(std::fstream &file,const int & quantity);

    int load_int(std::fstream &file);

    std::string load_string(std::fstream &file);
};


#endif //SEM3_LAB3_PPVIS_LOADER_H
