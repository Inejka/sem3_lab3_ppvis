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

bool Passenger_wagon::add_passenger(const Passenger &to_add) {
    return add(list, to_add, Passenger_wagon::max_capacity);
}

std::vector<Passenger> Passenger_wagon::remove_passengers_for_their_dest_point(const int &current_station) {
    std::vector<Passenger> to_return;
    for (int i = 0; i < list.size(); i++)
        if (list[i].check_destination_point(current_station)) {
            to_return.push_back(list[i]);
            list.erase(list.begin() + i);
            i--;
        }
    return to_return;
}

int Passenger_wagon::get_its_weight() {
    int to_return = its_weight;
    for (auto &i:list)
        to_return += i.get_its_weight();
    return to_return;
}

bool Freight_wagon::add_Cargo(const Cargo &to_add) {
    return add(list, to_add, Freight_wagon::max_capacity);
}

std::vector<Cargo> Freight_wagon::remove_Cargo_by_its_type(const int &type) {
    std::vector<Cargo> to_return;
    for (int i = 0; i < list.size(); i++)
        if (list[i].check_type(type)) {
            to_return.push_back(list[i]);
            list.erase(list.begin() + i);
            i--;
        }
    return to_return;
}

int Freight_wagon::get_its_weight() {
    int to_return = its_weight;
    for (auto &i:list)
        to_return += i.get_its_weight();
    return to_return;
}

void Train::load_passangers(std::vector<Passenger> &passagers) {
    int in_which_wagon_load = 0;
    int first_kolvo = passagers.size();
    while (!passagers.empty() && in_which_wagon_load != its_passenger_wagons.size())
        if (its_passenger_wagons[in_which_wagon_load].add_passenger(passagers[passagers.size() - 1]))
            passagers.erase(passagers.end() - 1);
        else in_which_wagon_load++;
    std::cout << "Loaded " << first_kolvo - passagers.size() << " passagers\n";
}

void Train::load_Cargo(std::vector<Cargo> &cargo) {
    int in_which_wagon_load = 0;
    int first_kolvo = cargo.size();
    while (!cargo.empty() && in_which_wagon_load != its_freight_wagons.size())
        if (its_freight_wagons[in_which_wagon_load].add_Cargo(cargo[cargo.size() - 1]))
            cargo.erase(cargo.end() - 1);
        else in_which_wagon_load++;
    std::cout << "Loaded " << first_kolvo-cargo.size() << " cargos\n";
}

std::vector<Passenger> Train::unload_passangers_by_their_dest_point(const int &current_station) {
    std::vector<Passenger> tmp;
    for (auto &i:its_passenger_wagons) {
        auto tmp1 = i.remove_passengers_for_their_dest_point(current_station);
        tmp.insert(tmp.end(), tmp1.begin(), tmp1.end());
    }
    std::cout << "Removed " << tmp.size() << " passangers\n";
    return tmp;
}

std::vector<Cargo> Train::unload_Cargo_by_type(const int &type) {
    std::vector<Cargo> tmp;
    for (auto &i:its_freight_wagons) {
        auto tmp1 = i.remove_Cargo_by_its_type(type);
        tmp.insert(tmp.end(), tmp1.begin(), tmp1.end());
    }
    std::cout << "Remove " << tmp.size() << " cargos\n";
    return tmp;
}

int Train::get_its_weight() {
    int to_return = its_weight;
    for (auto &i:its_freight_wagons)
        to_return += i.get_its_weight();
    for (auto &i:its_passenger_wagons)
        to_return += i.get_its_weight();
    return to_return;
}

bool Train::move(const int &distance, float &percent) {
    if (its_locomotive.create_pulling_force()) {
        float km = (its_locomotive.get_pulling_force() - get_its_weight() / 100);
        if (km > 0)
            percent += km / distance * 100;
//        std::cout<<distance << ' ' << percent  << ' ' << km << "\n";
        if (percent > 100)is_on_station = true;
        return true;
    }
    return false;
}
