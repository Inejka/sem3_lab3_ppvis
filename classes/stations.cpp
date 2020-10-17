//
// Created by inejka on 14.10.2020.
//

#include "stations.h"
#include <iostream>

int operattion_type(bool &mode){
    if(mode)return 2;
    else {
        std::cout << "0-load,1-unload,2-load\\unload,other-wait\n";
        int tmp;
        std::cin >> tmp;
        return tmp;
    }
}

bool Passenger_station::progress(Train &to_process,bool &mode) {
    time++;
    if(time==60){
        time = 0;
        switch (operattion_type(mode)) {
            case 0:
                to_process.load_passangers(to_load);
                break;
            case 1:
                to_process.unload_passangers_by_their_dest_point(its_number);
                break;
            case 2:
                to_process.load_passangers(to_load);
                to_process.unload_passangers_by_their_dest_point(its_number);
                break;
            case 4:
                //to_transit=to_process.unload_passangers_by_their_dest_point(); reserve for transt
                break;
        }
        to_process.make_move();
        return true;
    }
    return false;
}

bool Cargo_station::progress(Train &to_process,bool &mode) {
    time++;
    if(time==30){
        switch (operattion_type(mode)) {
            case 0:
                to_process.load_Cargo(to_load);
                break;
            case 1:
                to_process.unload_Cargo_by_type(0);
                break;
            case 2:
                to_process.load_Cargo(to_load);
                to_process.unload_Cargo_by_type(0);
                break;
        }
        to_process.make_move();
        return true;
    }
    return false;
}

bool Passenger_and_Cargo_station::progress(Train &to_process,bool &mode) {
    time++;
    if(time==120){
        time=0;
        switch (operattion_type(mode)) {
            case 0:
                to_process.load_passangers(Passenger_station::to_load);
                to_process.load_Cargo(Cargo_station::to_load);
                break;
            case 1:
                to_process.unload_passangers_by_their_dest_point(its_number);
                to_process.unload_Cargo_by_type(type_is_needed);
                break;
            case 2:
                to_process.load_passangers(Passenger_station::to_load);
                to_process.load_Cargo(Cargo_station::to_load);
                to_process.unload_passangers_by_their_dest_point(its_number);
                to_process.unload_Cargo_by_type(type_is_needed);
                break;
            case 4:
               // to_transit=to_process.unload_passangers_by_their_dest_point()
                break;
        }
        to_process.make_move();
        return true;
    }
    return false;
}
