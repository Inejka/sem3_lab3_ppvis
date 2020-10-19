//
// Created by inejka on 15.10.2020.
//

#include "game_field.h"
#include <iostream>

int passive_mode(){
    return 2;
}

int active_mode() {
    std::cout << "Choose option : 0-load,1-unload,2-load\\unload,other-do nothing ";
    int ch;
    std::cin >> ch;
    return ch;
}

void Game_field::simulate() {
    int (*choice)();
    if(its_mode)choice=passive_mode;else choice=active_mode;
    for (int i = 0; i < its_trains.size(); i++) {
        if (its_trains[i].if_on_station()) {
            if (its_stations[its_trains[i].get_current_station()]->progress(its_trains[i],
                                                                            choice)) {
                auto j = its_stations[its_trains[i].get_current_station()]->get_delta();
                for (auto &i : j)
                    std::cout << i.operation_type << i.kolvo << i.type_type;
            }
        } else if (!its_trains[i].move(
                its_stations[its_trains[i].get_current_station()]->get_distance(
                        its_trains[i].get_next_station()))) {
            its_trains.erase(its_trains.begin() + i);
        } else if (its_trains[i].if_on_station()) {
            std::cout << "Train number " << i << " has arrived to " << its_trains[i].get_current_station()
                      << " station\n";
        }
    }
    for (auto &i : its_stations)
        i->progress_to_spawn();
}