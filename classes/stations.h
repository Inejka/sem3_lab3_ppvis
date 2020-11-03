//
// Created by inejka on 14.10.2020.
//

#ifndef SEM3_LAB3_PPVIS_STATIONS_H
#define SEM3_LAB3_PPVIS_STATIONS_H

#include "trains.h"

struct Info {
    Info(std::string operation_type, int quantity, std::string type_type) : operation_type(operation_type),
                                                                            quantity(quantity),
                                                                            type_type(type_type) {}

    std::string operation_type, type_type;
    int quantity;
};

class Station {
public:
    Station(const std::string &name) : name(name) {}

    virtual bool progress(Train &, int mode()) = 0;

    virtual void clear_unloaded() = 0;

    virtual std::vector<Info> get_delta() = 0;

    virtual void progress_to_spawn() {
        time++;
        if (time == 100) {
            spawn();
            time = 0;
        }
    }
    std::string get_name()const{return name;}

protected:
    virtual void spawn() = 0;

    Station() {}
    std::string name;
    int time = 0 ;
};

class Passenger_station : virtual public Station {
public:
    std::vector<Info> get_delta() override {
        auto tmp = delta;
        delta.clear();
        return tmp;
    }

    void clear_unloaded() override {
        unloaded.clear();
    }

    Passenger_station(const std::string &number,
                      std::vector<Passenger> to_spawn) : Station(number), to_spawn(to_spawn) {}

    bool progress(Train &, int mode()) override;


protected:

    void load_passenger(Train &to_process);

    void unload_passenger(Train &to_process);

    void spawn() override {
        to_load.insert(to_load.end(), to_spawn.begin(), to_spawn.end());
    }

    Passenger_station(std::vector<Passenger> to_spawn) : to_spawn(to_spawn) {}

    std::vector<Info> delta;

    std::vector<Passenger> to_load, to_spawn, unloaded;
};

class Cargo_station : virtual public Station {
public:

    std::vector<Info> get_delta() override {
        auto tmp = delta;
        delta.clear();
        return tmp;
    }

    void clear_unloaded() override {
        unloaded.clear();
    }

    Cargo_station(const std::string &number,
                  const  std::string &type_is_needed, std::vector<Cargo> to_spawn) : Station(number),
                                                                            to_spawn(to_spawn),
                                                                            type_is_needed(type_is_needed) {}

    bool progress(Train &, int mode()) override;

protected:
    Cargo_station(std::vector<Cargo> to_spawn, const std::string &type_is_needed) : to_spawn(to_spawn),
                                                                            type_is_needed(type_is_needed) {}

    void load_cargo(Train &to_process);

    void unload_cargo(Train &to_process);

    void spawn() override {
        to_load.insert(to_load.end(), to_spawn.begin(), to_spawn.end());
    }

    std::vector<Cargo> to_load, to_spawn, unloaded;
    std::vector<Info> delta;
    std::string type_is_needed;
};

class Passenger_and_Cargo_station : public Cargo_station, public Passenger_station {
public:

    std::vector<Info> get_delta() override {
        auto tmp = Passenger_station::delta;
        Passenger_station::delta.clear();
        tmp.insert(tmp.end(), Cargo_station::delta.begin(), Cargo_station::delta.end());
        Cargo_station::delta.clear();
        return tmp;
    }

    void clear_unloaded() override {
        Passenger_station::unloaded.clear();
        Cargo_station::unloaded.clear();
    }

    Passenger_and_Cargo_station(const std::string &number,
                                std::vector<Passenger> to_spawn_passenger,
                                const  std::string &type_is_needed, std::vector<Cargo> to_spawn_cargo) : Station(number),
                                                                                                Passenger_station(
                                                                                                        to_spawn_passenger),
                                                                                                Cargo_station(
                                                                                                        to_spawn_cargo,
                                                                                                        type_is_needed) {}

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

