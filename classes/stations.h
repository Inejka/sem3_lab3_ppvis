//
// Created by inejka on 14.10.2020.
//

#ifndef SEM3_LAB3_PPVIS_STATIONS_H
#define SEM3_LAB3_PPVIS_STATIONS_H

#include "trains.h"

class Station {
public:
    Station(const int &number) : its_number(number) {}

    virtual bool progress(Train &,bool &mode) = 0;

    virtual void add() = 0 ;
protected:
    Station(){}
    int time = 0, its_number;
};

class Passenger_station : virtual public Station {
public:
    Passenger_station(const int &number) : Station(number) {}

    bool progress(Train &,bool &mode) override;

    void add() override{
        to_load.push_back(Passenger("ZAMOIDICK",0,75));
    }

protected:
    Passenger_station(){}
    std::vector<Passenger> to_load, to_transit;
};

class Cargo_station : virtual public Station {
public:
    Cargo_station(const int &number) : Station(number) {}

    bool progress(Train &,bool &mode) override;
    void add() override{
     //   to_load.push_back(Passenger("ZAMOIDICK",0,75));
    }
protected:
    Cargo_station(){}
    std::vector<Cargo> to_load;
    int type_is_needed;
};

class Passenger_and_Cargo_station : public Cargo_station, public Passenger_station {
public:
    Passenger_and_Cargo_station(const int &number) : Station(number) {}
    void add() override{
    //  to_load.push_back(Passenger("ZAMOIDIC",0,75));
    }
    bool progress(Train &,bool &mode) override;
};


#endif //SEM3_LAB3_PPVIS_Stations_H

