//
// Created by inejka on 14.10.2020.
//

#ifndef SEM3_LAB3_PPVIS_STATIONS_H
#define SEM3_LAB3_PPVIS_STATIONS_H

#include "trains.h"

struct Info {
    Info(std::string operation_type, int kolvo, std::string type_type) : operation_type(operation_type), kolvo(kolvo),
                                                                         type_type(type_type) {}

    std::string operation_type, type_type;
    int kolvo;
};

class Station {
public:
    Station(const int &number, std::vector<std::pair<int, int>> its_connections) : its_number(number),
                                                                                   its_connections(its_connections) {}

    virtual bool progress(Train &, int mode()) = 0;

    int get_distance(const int &to_station) const;

    virtual void clear_unloaded() = 0;

    virtual std::vector<Info> get_delta() = 0;

    virtual void progress_to_spawn() {
        time++;
        if (time == 100) {
            spawn();
            time = 0;
        }
    }

protected:
    virtual void spawn() = 0;

    Station() {}

    // stations\weight
    std::vector<std::pair<int, int>> its_connections;
    int time = 0, its_number;
};

class Passenger_station : virtual public Station {
public:
    std::vector<Info> get_delta() override {
        auto tmp = its_delta;
        its_delta.clear();
        return tmp;
    }

    void clear_unloaded() override {
        unloaded.clear();
    }

    Passenger_station(const int &number, std::vector<std::pair<int, int>> its_connections,
                      std::vector<Passenger> to_spawn) : Station(number, its_connections), to_spawn(to_spawn) {}

    bool progress(Train &, int mode()) override;


protected:

    void load_passanger(Train &to_process);

    void unload_passanger(Train &to_process);

    void spawn() override {
        to_load.insert(to_load.end(), to_spawn.begin(), to_spawn.end());
    }

    Passenger_station(std::vector<Passenger> to_spawn) : to_spawn(to_spawn) {}

    std::vector<Info> its_delta;

    std::vector<Passenger> to_load, to_spawn, unloaded;
};

class Cargo_station : virtual public Station {
public:

    std::vector<Info> get_delta() override {
        auto tmp = its_delta;
        its_delta.clear();
        return tmp;
    }

    void clear_unloaded() override {
        unloaded.clear();
    }

    Cargo_station(const int &number, std::vector<std::pair<int, int>> its_connections,
                  const int &type_is_needed, std::vector<Cargo> to_spawn) : Station(number, its_connections),
                                                                            to_spawn(to_spawn),
                                                                            type_is_needed(type_is_needed) {}

    bool progress(Train &, int mode()) override;

protected:
    Cargo_station(std::vector<Cargo> to_spawn, const int &type_is_needed) : to_spawn(to_spawn),
                                                                            type_is_needed(type_is_needed) {}

    void load_cargo(Train &to_process);

    void unload_cargo(Train &to_process);

    void spawn() override {
        to_load.insert(to_load.end(), to_spawn.begin(), to_spawn.end());
    }

    std::vector<Cargo> to_load, to_spawn, unloaded;
    std::vector<Info> its_delta;
    int type_is_needed;
};

class Passenger_and_Cargo_station : public Cargo_station, public Passenger_station {
public:

    std::vector<Info> get_delta() override {
        auto tmp = Cargo_station::its_delta;
        Cargo_station::its_delta.clear();
        tmp.insert(tmp.end(), Cargo_station::its_delta.begin(), Cargo_station::its_delta.end());
        Cargo_station::its_delta.clear();
        return tmp;
    }

    void clear_unloaded() override {
        Passenger_station::unloaded.clear();
        Cargo_station::unloaded.clear();
    }

    Passenger_and_Cargo_station(const int &number, std::vector<std::pair<int, int>> its_connections,
                                std::vector<Passenger> to_spawn_passanger,
                                const int &type_is_neeeded, std::vector<Cargo> to_spawn_cargo) : Station(number,
                                                                                                         its_connections),
                                                                                                 Passenger_station(
                                                                                                         to_spawn_passanger),
                                                                                                 Cargo_station(
                                                                                                         to_spawn_cargo,
                                                                                                         type_is_neeeded) {}

    bool progress(Train &, int mode()) override;

protected:
    void spawn() override {
        Passenger_station::to_load.insert(Passenger_station::to_load.end(), Passenger_station::to_spawn.begin(),
                                          Passenger_station::to_spawn.end());
        Cargo_station::to_load.insert(Cargo_station::to_load.end(), Cargo_station::to_spawn.begin(),
                                      Cargo_station::to_spawn.end());
    }
};


#endif //SEM3_LAB3_PPVIS_Stations_H

