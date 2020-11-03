//
// Created by inejka on 15.10.2020.
//

#include "game_field.h"
#include <iostream>

int passive_mode() {
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
    if (mode)choice = passive_mode; else choice = active_mode;
    for (int i = 0; i < trains.size(); i++) {
        if (trains[i].if_on_station()) {
            if (stations[trains[i].get_current_station()]->progress(trains[i],
                                                                    choice)) {
                auto j = stations[trains[i].get_current_station()]->get_delta();
                log.insert(log.end(),j.begin(),j.end());
            }
        } else if (!trains[i].move(connections[{trains[i].get_current_station(), trains[i].get_next_station()}])) {
            alive_trains[i]= false;
        } else if (trains[i].if_on_station()) {
            log.push_back(Info("Train number ",i," has arrived to " + trains[i].get_current_station() +" station\n"));
        }
    }
    for (auto &i : stations)
        i.second->progress_to_spawn();
}