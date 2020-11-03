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
    if (max_capacity > list.size()) {
        list.push_back(to_add);
        return true;
    }
    return false;
}

template<class T1>
void Wagon<T1>::load(std::vector<T1> &to_load) {
    while (!to_load.empty() && add(to_load[0]))
        to_load.erase(to_load.begin());
}

template<class T1>
std::vector<T1> Wagon<T1>::unload(const std::string &par) {
    std::vector<T1> to_return;
    for (int i = 0; i < list.size(); i++)
        if (unload_decision(list[i], par)) {
            to_return.push_back(list[i]);
            list.erase(list.begin() + i);
            i--;
        }
    return to_return;
}

bool Passenger_wagon::unload_decision(const Passenger &make_decision_about, const std::string &par) {
    return make_decision_about.check_destination_point(par);
}

int Passenger_wagon::get_weight() const {
    int to_return = Base_wagon::get_weight();
    for (auto &i:get_list_for_weight())
        to_return += i.get_weight();
    return to_return;
}

int Freight_wagon::get_weight() const {
    int to_return = Base_wagon::get_weight();
    for (auto &i:get_list_for_weight())
        to_return += i.get_weight();
    return to_return;
}

bool Freight_wagon::unload_decision(const Cargo &make_decision_about, const std::string &par) {
    return make_decision_about.check_type(par);
}

void Train::load_passengers(std::vector<Passenger> &passengers) {
    for (auto &i : wagons) {
        Passenger_wagon *p_w_p = dynamic_cast<Passenger_wagon *>(i);
        if (p_w_p)p_w_p->load(passengers);
        if (passengers.empty())break;;
    }
}

void Train::load_cargo(std::vector<Cargo> &cargo) {
    for (auto &i:wagons) {
        Freight_wagon *f_w_p = dynamic_cast<Freight_wagon *>(i);
        if (f_w_p)f_w_p->load(cargo);
        if (cargo.empty())break;
    }
}

std::vector<Passenger> Train::unload_passengers_by_their_dest_point() {
    std::vector<Passenger> tmp;
    for (auto &i:wagons) {
        Passenger_wagon *p_w_p = dynamic_cast<Passenger_wagon *>(i);
        if (p_w_p) {
            auto tmp1 = p_w_p->unload(route[current_position_on_route]);
            tmp.insert(tmp.end(), tmp1.begin(), tmp1.end());
        }
    }
    return tmp;
}

std::vector<Cargo> Train::unload_cargo_by_type(const std::string &type) {
    std::vector<Cargo> tmp;
    for (auto &i:wagons) {
        Freight_wagon *f_w_p = dynamic_cast<Freight_wagon *>(i);
        if (f_w_p) {
            auto tmp1 = f_w_p->unload(type);
            tmp.insert(tmp.end(), tmp1.begin(), tmp1.end());
        }
    }
    return tmp;
}

int Train::get_weight() const {
    int to_return = weight;
    for (auto &i:wagons)
        to_return += i->get_weight();
    return to_return;
}

bool Train::move(const int &distance) {
    if (locomotive.create_pulling_force()) {
        float km = (locomotive.get_pulling_force() - get_weight() / 100);
        if (km > 0)
            progress += km / distance * 100;
        //std::cout<<distance << ' ' << progress  << ' ' << km << "\n";
        if (progress > 100) {
            progress = 0 ;
            is_on_station = true;
            current_position_on_route = (current_position_on_route + 1) % route.size();
        }
        return true;
    }
    return false;
}

std::string Train::get_next_station() const {
    if (current_position_on_route != route.size()-1)
        return route[current_position_on_route + 1];
    else return route[0];
}
