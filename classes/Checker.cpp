//
// Created by inejka on 02.11.2020.
//

#include "Checker.h"
#include "Error.h"

bool Check::check_game_field(Game_field &to_check) {
    try {
        check_connections(to_check);
    }
    catch (Error error) {
        throw error;
    }
    return true;
}

void Check::check_connections(Game_field &to_check) {
    for (auto &i : to_check.trains) {
        auto i_route = i.get_route();
        for (int j = 0; j < i_route.size() - 1; j++) {
            if (to_check.connections.find({i_route[j], i_route[j + 1]}) == to_check.connections.end())
                throw Error("Checker.cpp", "check_connections", "there is no connections between some stations");
            if (to_check.connections[{i_route[j], i_route[j + 1]}] == 0)
                throw Error("Checker.cpp", "check_connections", "there is connections with 0 weight");
        }
        if (to_check.connections.find({i_route[i_route.size() - 1], i_route[0]}) == to_check.connections.end())
            throw Error("Checker.cpp", "check_connections", "there is no connections between some stations");;
        if (to_check.connections[{i_route[i_route.size() - 1], i_route[0]}] == 0)
            throw Error("Checker.cpp", "check_connections", "there is connections with 0 weight");
    }
}

