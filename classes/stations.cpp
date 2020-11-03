//
// Created by inejka on 14.10.2020.
//

#include "stations.h"
#include <iostream>

bool Passenger_station::progress(Train &to_process,  int mode()) {
    to_process.progress++;
    if (to_process.progress == 60) {
        to_process.progress = 0;
        switch (mode()) {
            case 0: {
                load_passenger(to_process);
                break;
            }
            case 1:
                unload_passenger(to_process);
                break;
            case 2:
                load_passenger(to_process);
                unload_passenger(to_process);
                break;
        }
        to_process.make_move();
        return true;
    }
    return false;
}

void Passenger_station::load_passenger(Train &to_process) {
    int buffer = to_load.size();
    to_process.load_passengers(to_load);
    if (buffer - to_load.size() != 0)
        delta.push_back(Info("loaded ", buffer - to_load.size(), " passengers\n"));
}

void Passenger_station::unload_passenger(Train &to_process) {
    int buffer = unloaded.size();
    auto tmp = to_process.unload_passengers_by_their_dest_point();
    unloaded.insert(unloaded.begin(), tmp.begin(), tmp.end());
    if (unloaded.size() - buffer != 0)
        delta.push_back(Info("unloaded ", unloaded.size() - buffer, " passengers\n"));
}

bool Cargo_station::progress(Train &to_process, int mode()) {
    to_process.progress++;
    if (to_process.progress == 120) {
        to_process.progress = 0;
        switch (mode()) {
            case 0:
                load_cargo(to_process);
                break;
            case 1:
                unload_cargo(to_process);
                break;
            case 2:
                load_cargo(to_process);
                unload_cargo(to_process);
                break;
        }
        to_process.make_move();
        return true;
    }
    return false;
}

void Cargo_station::unload_cargo(Train &to_process) {
    int buffer = to_load.size();
    to_process.load_cargo(to_load);
    if (buffer - to_load.size() != 0)
        delta.push_back(Info("loaded ", buffer - to_load.size(), " cargos\n"));

}

void Cargo_station::load_cargo(Train &to_process) {
    int buffer = unloaded.size();
    auto tmp = to_process.unload_cargo_by_type(type_is_needed);
    unloaded.insert(unloaded.end(), tmp.begin(), tmp.end());
    if (unloaded.size() - buffer != 0)
        delta.push_back(Info("unloaded ", unloaded.size() - buffer, " cargos\n"));
}

bool Passenger_and_Cargo_station::progress(Train &to_process, int mode()) {
    to_process.progress++;
    if (to_process.progress == 240) {
        to_process.progress = 0;
        switch (mode()) {
            case 0:
                load_passenger(to_process);
                load_cargo(to_process);
                break;
            case 1:
                unload_cargo(to_process);
                unload_passenger(to_process);
                break;
            case 2:
                load_passenger(to_process);
                load_cargo(to_process);
                unload_cargo(to_process);
                unload_passenger(to_process);
                break;
        }
        to_process.make_move();
        return true;
    }
    return false;
}
