//
// Created by inejka on 16.10.2020.
//

#ifndef SEM3_LAB3_PPVIS_LOADER_AND_CHECKER_H
#define SEM3_LAB3_PPVIS_LOADER_AND_CHECKER_H

#include "game_field.h"
#include <iostream>
#include "stations.h"
#include <fstream>
#include <string>

enum Error {
    load_file_error,
    end_of_file_error,
    string_instead_of_int_error,
    station_type_error,
    game_mode_error,
    connections_error
};

class Load {
public:
    bool load_game_field(std::string load_from, Game_field &to_load);

private:

    Train load_train(std::fstream &file);

    std::vector<int> load_route(std::fstream &file);

    Station *load_station(std::fstream &file, const int &its_number);

    std::vector<Passenger> load_to_spawn_passanger(std::fstream &file);

    std::vector<Cargo> load_to_spawn_cargo(std::fstream &file);

    std::vector<std::pair<int, int>> load_connections(std::fstream &file);

    int load_int(std::fstream &file);
};


class Check {
public:
    bool check_game_field(Game_field &to_check);
private:
    void check_connections(Game_field &to_check);
};

#endif //SEM3_LAB3_PPVIS_LOADER_AND_CHECKER_H
