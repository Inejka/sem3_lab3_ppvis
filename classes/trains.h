//
// Created by inejka on 02.10.2020.
//

#ifndef SEM3_LAB3_PPVIS_TRAINS_H
#define SEM3_LAB3_PPVIS_TRAINS_H

#include <vector>
#include <string>

class Entity_with_weight {
public:
    virtual int get_its_weight() = 0;

    void set_its_weight(const int &to_set) { its_weight = to_set; }

protected:
    int its_weight = 0;
};

class Passenger : public Entity_with_weight {
public:
    Passenger(std::string name, int destination_point, int weight) : its_name(name), its_destination_point(
            destination_point) { set_its_weight(weight); }

    bool check_destination_point(const int &to_check) const { return its_destination_point == to_check; }

    int get_its_destination_point() const { return its_destination_point; }

    int get_its_weight() override { return its_weight; }

private:
    std::string its_name;
    int its_destination_point;
};

class Cargo : public Entity_with_weight {
public:
    Cargo(int type, int weight) : its_type(type) { set_its_weight(weight); }

    bool check_type(const int &to_check) const { return to_check == its_type; }

    int get_its_weight() override { return its_weight; }

private:
    int its_type;
};

class Locomotive : Entity_with_weight {
public:
    Locomotive(int r_pulling_force, int r_life_time) : pulling_force(r_pulling_force),
                                                       life_time(r_life_time) { its_weight = 1500; }

    int get_pulling_force() const { return pulling_force; }

    bool create_pulling_force() {
        if (life_time == 0)return false;
        life_time--;
        return true;
    }

    int get_its_weight() override { return its_weight; }

private:
    int pulling_force, life_time;
};

class Passenger_wagon : public Entity_with_weight {
public:
    Passenger_wagon() { set_its_weight(4000); }

    bool add_passenger(const Passenger &to_add);

    std::vector<Passenger> remove_passengers_for_their_dest_point(const int &current_station);

    int get_its_weight() override;

private:
    std::vector<Passenger> list;
    static const int max_capacity = 60;
};

class Freight_wagon : public Entity_with_weight {
public:
    Freight_wagon() { set_its_weight(2500); }

    bool add_Cargo(const Cargo &to_add);

    std::vector<Cargo> remove_Cargo_by_its_type(const int &type);

    int get_its_weight() override;

private:
    std::vector<Cargo> list;
    static const int max_capacity = 500;
};

class Train : Entity_with_weight {
public:
    Train(int locomotive_lifetime, int locomotive_pulling_force, int freight_wagons_count,
          int passenger_wagons_count) : its_locomotive(locomotive_pulling_force,
                                                       locomotive_lifetime) {
        its_freight_wagons.resize(freight_wagons_count);
        its_passenger_wagons.resize(passenger_wagons_count);
    }

    void load_passangers(std::vector<Passenger> &passagers);

    void load_Cargo(std::vector<Cargo> &Cargo);

    std::vector<Passenger> unload_passangers_by_their_dest_point(const int &current_station);

    std::vector<Cargo> unload_Cargo_by_type(const int &type);

    int get_its_weight() override;

    bool move(const int &distance, float &percent);

    bool if_on_station() const { return is_on_station; }

    void make_move() { is_on_station = false; }

private:
    Locomotive its_locomotive;
    std::vector<Freight_wagon> its_freight_wagons;
    std::vector<Passenger_wagon> its_passenger_wagons;
    bool is_on_station = true;

    //    std::vector<int> its_route;
    //    int current_position_on_its_route = 0;

};

#endif //SEM3_LAB3_PPVIS_TRAINS_H
