//
// Created by inejka on 15.10.2020.
//

#ifndef SEM3_LAB3_PPVIS_GAME_FIELD_H
#define SEM3_LAB3_PPVIS_GAME_FIELD_H

#include "stations.h"
class Game_field {
public:
    Game_field(bool mode):its_mode(mode){}
    void simulate();
    friend class Load;
    friend class Check;
private:
    bool its_mode;
    int find_distance_between(int first,int second);
    //(     вектор из пар - следующая станция,расстояние до неё , станция   )
    std::vector<std::pair<std::vector<std::pair<int, int>>, Station *>> its_graph;
    //((вектор состоящий из маршрута поезда,(текущая станция,процент прохождения расстояния)) , поезд)
    std::vector<std::pair<std::pair<std::vector<int>, std::pair<int, float>>, Train *>> its_trains;
};

#endif //SEM3_LAB3_PPVIS_GAME_FIELD_H
