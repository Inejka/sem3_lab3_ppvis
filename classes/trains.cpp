//
// Created by inejka on 02.10.2020.
//

#include "trains.h"
#include <iostream>

template<typename T1>

bool add(std::vector<T1> &list, const T1 &to_add, const int max_capacity) {
    if (list.size() == max_capacity)return false;
    list.push_back(to_add);
    return true;
}


template<class T1>
bool Wagon<T1>::add(const T1 &to_add) {
    if (max_capacity >= list.size()) {
        list.push_back(to_add);
        return true;
    }
    return false;
}

template<class T1>
void Wagon<T1>::laod(std::vector<T1> &to_load) {
    while (!to_load.empty() && add(to_load[0]))
        to_load.erase(to_load.begin());
}

template<class T1>
std::vector<T1> Wagon<T1>::unload(const int &par) {
    std::vector<T1> to_return;
    for (int i = 0; i < list.size(); i++)
        if (unload_decision(list[i], par)) {
            to_return.push_back(list[i]);
            list.erase(list.begin() + i);
            i--;
        }
    return to_return;
}

bool Passenger_wagon::unload_decision(const Passenger &make_decision_about, const int &par) {
    return make_decision_about.check_destination_point(par);
}

int Passenger_wagon::get_its_weight() const {
    int to_return = Wagon_p::get_its_weight();
    for (auto &i:get_list_for_weight())
        to_return += i.get_its_weight();
    return to_return;
}

int Freight_wagon::get_its_weight() const {
    int to_return = Wagon_p::get_its_weight();
    for (auto &i:get_list_for_weight())
        to_return += i.get_its_weight();
    return to_return;
}

bool Freight_wagon::unload_decision(const Cargo &make_decision_about, const int &par) {
    return make_decision_about.check_type(par);
}

void Train::load_passangers(std::vector<Passenger> &passagers) {
    for (auto &i : its_wagons) {
        Passenger_wagon *p_w_p = dynamic_cast<Passenger_wagon *>(i);
        if (p_w_p)p_w_p->laod(passagers);
        if (passagers.empty())break;;
    }
}

void Train::load_Cargo(std::vector<Cargo> &cargo) {
    for (auto &i:its_wagons) {
        Freight_wagon *f_w_p = dynamic_cast<Freight_wagon *>(i);
        if (f_w_p)f_w_p->laod(cargo);
        if (cargo.empty())break;
    }
}

std::vector<Passenger> Train::unload_passangers_by_their_dest_point(const int &current_station) {
    std::vector<Passenger> tmp;
    for (auto &i:its_wagons) {
        Passenger_wagon *p_w_p = dynamic_cast<Passenger_wagon *>(i);
        if (p_w_p) {
            auto tmp1 = p_w_p->unload(current_station);
            tmp.insert(tmp.end(), tmp1.begin(), tmp1.end());
        }
    }
    return tmp;
}

std::vector<Cargo> Train::unload_Cargo_by_type(const int &type) {
    std::vector<Cargo> tmp;
    for (auto &i:its_wagons) {
        Freight_wagon *f_w_p = dynamic_cast<Freight_wagon *>(i);
        if (f_w_p) {
            auto tmp1 = f_w_p->unload(type);
            tmp.insert(tmp.end(), tmp1.begin(), tmp1.end());
        }
    }
    return tmp;
}

int Train::get_its_weight() const {
    int to_return = its_weight;
    for (auto &i:its_wagons)
        to_return += i->get_its_weight();
    return to_return;
}

bool Train::move(const int &distance) {
    if (its_locomotive.create_pulling_force()) {
        float km = (its_locomotive.get_pulling_force() - get_its_weight() / 100);
        if (km > 0)
            progress += km / distance * 100;
        //std::cout<<distance << ' ' << progress  << ' ' << km << "\n";
        if (progress > 100) {
            progress = 0 ;
            is_on_station = true;
            current_position_on_its_route = (current_position_on_its_route + 1) % its_route.size();
        }
        return true;
    }
    return false;
}

int Train::get_next_station() const {
    if (current_position_on_its_route != its_route.size())
        return its_route[current_position_on_its_route + 1];
    else return its_route[0];
}
