//
// Created by inejka on 16.10.2020.
//

#include "loader_and_checker.h"

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

std::vector<std::pair<int, int>> Load::load_connections(std::fstream &file) {
    std::vector<std::pair<int, int>> to_return;
    int kolvo1 = load_int(file);
    for (int j = 0; j < kolvo1; j++) {
        int first = load_int(file), second = load_int(file);
        to_return.push_back({first, second});
    }
    return to_return;
}

std::vector<Cargo> Load::load_to_spawn_cargo(std::fstream &file) {
    int kolvo1=load_int(file);
    std::vector<Cargo> to_return;
    for (int j = 0; j < kolvo1; j++) {
        int type = load_int(file), weight = load_int(file);
        to_return.push_back(Cargo(type, weight));
    }
    return to_return;
}

std::vector<Passenger> Load::load_to_spawn_passanger(std::fstream &file) {
    std::vector<Passenger> to_return;
    int kolvo1 = load_int(file);
    for (int j = 0; j < kolvo1; j++) {
        std::string name;
        if (file.eof())throw end_of_file_error;
        file >> name;
        int dest_point = load_int(file), weight = load_int(file);
        to_return.push_back(Passenger(name, dest_point, weight));
    }
    return to_return;
}

int Load::load_int(std::fstream &file) {
    std::string load_try;
    file >> load_try;
    if (load_try.empty())throw end_of_file_error;
    if (!is_string(load_try))
        return string_to_int(load_try);
    else throw string_instead_of_int_error;
}

Station *Load::load_station(std::fstream &file, const int &its_number) {
    int type;
    std::vector<std::pair<int, int>> connections = load_connections(file);
    type = load_int(file);
    switch (type) {
        case 0:
            return new Passenger_station(its_number, connections, load_to_spawn_passanger(file));
        case 1:
            return new Cargo_station(its_number, connections, load_int(file), load_to_spawn_cargo(file));
        case 2:
            return new Passenger_and_Cargo_station(its_number, connections, load_to_spawn_passanger(file),
                                                   load_int(file), load_to_spawn_cargo(file));
        default:
            throw station_type_error;
    }
}

Train Load::load_train(std::fstream &file,const int &its_number) {
    int lifetime = load_int(file), pulling_force = load_int(file), f_w_c = load_int(file), p_w_c = load_int(file);
    return Train(lifetime, pulling_force, f_w_c, p_w_c, load_route(file),its_number);
}

std::vector<int> Load::load_route(std::fstream &file) {
    std::vector<int> to_return;
    int kolvo = load_int(file);
    for (int i = 0; i < kolvo; i++)
        to_return.push_back(load_int(file));
    return to_return;
}

bool Load::load_game_field(std::string load_from, Game_field &to_load,const int &its_mode) {
    try {
        std::fstream file;
        file.open(load_from);
        if (!file.is_open())throw load_file_error;
        int kolvo = load_int(file);
        if (its_mode != 0 && its_mode != 1)throw game_mode_error;
        else to_load.its_mode = (bool) its_mode;
        for (int i = 0; i < kolvo; i++)
            to_load.its_stations.push_back(load_station(file, i));
        kolvo = load_int(file);
        for (int i = 0; i < kolvo; i++)
            to_load.its_trains.push_back(load_train(file,i));
        file.close();
    }
    catch (Error error) {
        switch (error) {
            case load_file_error:
                std::cout << "Can not open file";
                return false;
                break;
            case end_of_file_error:
                std::cout << "Invalid input file";
                return false;
                break;
            case string_instead_of_int_error:
                std::cout << "Invalid input file";
                return false;
                break;
            case station_type_error:
                std::cout << "Invalid station type";
                break;
            case game_mode_error:
                std::cout << "Invalid game mode";
                break;
        }

    }
    return true;
}

bool Check::check_game_field(Game_field &to_check) {
    try {
        check_connections(to_check);
    }
    catch (Error error) {
        switch (error) {
            case connections_error:
                std::cout << "Invalid route or zero km";
                return false;
                break;
        }
    }
    return true;
}

void Check::check_connections(Game_field &to_check) {
    for(auto &i : to_check.its_trains){
        auto i_route = i.get_its_route() ;
        for(int j = 0 ; j < i_route.size() - 1 ; j++) {
            if(i_route[j]>=to_check.its_stations.size())throw connections_error;
            int tmp = to_check.its_stations[i_route[j]]->get_distance(i_route[j+1]);
            if (tmp ==-1 || tmp == 0 )throw connections_error;
        }
        int tmp = to_check.its_stations[i_route[i_route.size()-1]]->get_distance(i_route[0]);
        if (tmp ==-1 || tmp == 0 )throw connections_error;

    }
}
