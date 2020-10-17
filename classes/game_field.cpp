//
// Created by inejka on 15.10.2020.
//

#include "game_field.h"
#include <iostream>

void Game_field::simulate() {
    for (int i = 0; i < its_trains.size(); i++)
        if (its_trains[i].second->if_on_station())
            its_graph[its_trains[i].first.second.first].second->progress(*its_trains[i].second, its_mode);
        else if (its_trains[i].second->move(
                find_distance_between(its_trains[i].first.first[its_trains[i].first.second.first],
                                      its_trains[i].first.first[(its_trains[i].first.second.first + 1) %
                                                                its_trains[i].first.first.size()]),
                its_trains[i].first.second.second)) {
            if (its_trains[i].first.second.second > 100) {
                its_trains[i].first.second.second = 0;
                its_trains[i].first.second.first =
                        (its_trains[i].first.second.first + 1) % its_trains[i].first.first.size();

                std::cout << "Train number " << i << " has arrived to "
                          << its_trains[i].first.first[its_trains[i].first.second.first] << " station\n";
            }
        } else {

        }
}

int Game_field::find_distance_between(int first, int second) {
    for (int i = 0; i < its_graph[first].first.size(); i++)
        if (its_graph[first].first[i].first == second)return its_graph[first].first[i].second;
}
