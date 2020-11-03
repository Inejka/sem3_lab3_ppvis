//
// Created by inejka on 02.11.2020.
//

#include "Loader.h"
#include "Error.h"

bool is_string(const std::string &to_scan) {
    for (auto &i : to_scan)
        if (i < '0' || '9' < i)return true;
    return false;
}

int pow(const int &a, const int &b) {
    int ans = 1;
    for (int i = 0; i < b; i++)
        ans *= a;
    return ans;
}

int string_to_int(const std::string &to_transform) {
    int ans = 0;
    for (int i = 0; i < to_transform.size(); i++)
        ans += pow(10, to_transform.size() - i - 1) * (to_transform[i] - '0');
    return ans;
}

std::map<std::pair<std::string, std::string>, int> Load::load_connections(std::fstream &file, const int &quantity) {
    std::map<std::pair<std::string, std::string>, int> to_return;
    for (int i = 0; i < quantity; i++) {
        std::string tmp1 = load_string(file), tmp2 = load_string(file);
        int tmp = load_int(file);
        to_return.insert({{tmp1, tmp2}, tmp});
    }
    return to_return;
}

std::vector<Cargo> Load::load_to_spawn_cargo(std::fstream &file) {
    int quantity1 = load_int(file);
    std::vector<Cargo> to_return;
    for (int j = 0; j < quantity1; j++) {
        std::string type = load_string(file);
        int weight = load_int(file);
        to_return.push_back(Cargo(type, weight));
    }
    return to_return;
}

std::vector<Passenger> Load::load_to_spawn_passenger(std::fstream &file) {
    std::vector<Passenger> to_return;
    int quantity1 = load_int(file);
    for (int j = 0; j < quantity1; j++) {
        std::string name = load_string(file), dest_point = load_string(file);
        int weight = load_int(file);
        to_return.push_back(Passenger(name, dest_point, weight));
    }
    return to_return;
}

int Load::load_int(std::fstream &file) {
    std::string load_try;
    file >> load_try;
    if (load_try.empty())throw Error("Loader.cpp", "load_int", "missing statement,check input format");
    if (is_string(load_try))
        throw Error("Loader.cpp", "load_int", "cannot convert string to int,check input format");
    return string_to_int(load_try);
}

Station *Load::load_station(std::fstream &file) {
    int type;
    type = load_int(file);
    switch (type) {
        case 0:
            return new Passenger_station(load_string(file), load_to_spawn_passenger(file));
        case 1:
            return new Cargo_station(load_string(file), load_string(file), load_to_spawn_cargo(file));
        case 2:
            return new Passenger_and_Cargo_station(load_string(file), load_to_spawn_passenger(file),
                                                   load_string(file), load_to_spawn_cargo(file));
        default:
            throw Error("Loader.cpp", "load_station", "invalid station type,check input format");
    }
}

Train Load::load_train(std::fstream &file) {
    int lifetime = load_int(file), pulling_force = load_int(file), f_w_c = load_int(file), p_w_c = load_int(file);
    return Train(lifetime, pulling_force, f_w_c, p_w_c, load_route(file));
}

std::vector<std::string> Load::load_route(std::fstream &file) {
    std::vector<std::string> to_return;
    int quantity = load_int(file);
    for (int i = 0; i < quantity; i++)
        to_return.push_back(load_string(file));
    return to_return;
}

bool Load::load_game_field(std::string load_from, Game_field &to_load, const int &mode) {
        std::fstream file;
        file.open(load_from);
        if (!file.is_open())throw Error("Loader.cpp", "load_game_field", "cannot open file");;
        int quantity = load_int(file);
        if (mode != 0 && mode != 1)
            throw Error("Loader.cpp", "load_game_field", "invalid game format,check input format");
        else to_load.mode = (bool) mode;
        for (int i = 0; i < quantity; i++) {
            auto tmp = load_station(file);
            to_load.stations.insert({tmp->get_name(), tmp});
        }
        to_load.connections = load_connections(file, load_int(file));
        quantity = load_int(file);
        for (int i = 0; i < quantity; i++)
            to_load.trains.push_back(load_train(file));
        to_load.alive_trains.resize(to_load.trains.size());
        for (int i = 0; i < to_load.alive_trains.size(); i++) to_load.alive_trains[i] = true;
        file.close();
    return true;
}

std::string Load::load_string(std::fstream &file) {
    std::string load_try;
    file >> load_try;
    if (load_try.empty())throw Error("Loader.cpp", "load_string", "missing statement,check input format");
    return load_try;
}
