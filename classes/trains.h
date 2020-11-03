//
// Created by inejka on 02.10.2020.
//

#ifndef SEM3_LAB3_PPVIS_TRAINS_H
#define SEM3_LAB3_PPVIS_TRAINS_H

#include <vector>
#include <string>

class Entity_with_weight {
public:
    virtual int get_weight() const = 0;

    void set_weight(const int &to_set) { weight = to_set; }

protected:
    int weight = 0;
};

class Passenger : public Entity_with_weight {
public:
    Passenger(std::string name, std::string destination_point, int weight) : name(name), destination_point(
            destination_point) { set_weight(weight); }

    bool check_destination_point(const std::string &to_check) const { return destination_point == to_check; }

    std::string get_destination_point() const { return destination_point; }

    int get_weight() const override { return weight; }

private:
    std::string name,destination_point;
};

class Cargo : public Entity_with_weight {
public:
    Cargo(std::string type, int weight) : type(type) { set_weight(weight); }

    bool check_type(const std::string &to_check) const { return to_check == type; }

    int get_weight() const override { return weight; }

private:
    std::string type;
};

class Locomotive : Entity_with_weight {
public:
    Locomotive(int pulling_force, int life_time) : pulling_force(pulling_force),
                                                       life_time(life_time) { weight = 1500; }

    int get_pulling_force() const { return pulling_force; }

    bool create_pulling_force() {
        if (life_time == 0)return false;
        life_time--;
        return true;
    }

    int get_weight() const override { return weight; }

private:
    int pulling_force, life_time;
};

class Base_wagon : public Entity_with_weight {
public:
    Base_wagon(const int &weight) { set_weight(weight); }

    virtual std::string get_type() = 0;

    int get_weight() const override {
        return weight;
    }
};

template<class T1>
class Wagon : public Base_wagon {
public:
    Wagon(const int &max_capacity, std::string type, const int &weight) : Base_wagon(weight),
                                                                              max_capacity(max_capacity),
                                                                              type(type) {}

    bool add(const T1 &to_add);

    void load(std::vector<T1> &to_load);

    virtual std::vector<T1> unload(const std::string &par);

    std::string get_type() override {
        return type;
    }

protected:
    virtual bool unload_decision(const T1 &make_decision_about, const std::string &par) = 0;

    const std::vector<T1> get_list_for_weight() const { return list; }

private:
    int max_capacity;
    std::vector<T1> list;
    std::string type;

};


class Passenger_wagon : public Wagon<Passenger> {
public:
    Passenger_wagon() : Wagon(60, "Passenger_wagon", 4000) {}

    int get_weight() const override;

protected:
    bool unload_decision(const Passenger &make_decision_about, const std::string &par) override;
};

class Freight_wagon : public Wagon<Cargo> {
public:
    Freight_wagon() : Wagon(500, "Cargo_wagon", 2500) {}

    int get_weight() const override;

protected:
    bool unload_decision(const Cargo &make_decision_about, const std::string &par) override;
};

class Train : Entity_with_weight {
public:
    Train(int locomotive_lifetime, int locomotive_pulling_force, int freight_wagons_count,
          int passenger_wagons_count, std::vector<std::string> route) : route(route),
                                                                    locomotive(locomotive_pulling_force,
                                                                                   locomotive_lifetime) {
        for (int i = 0; i < freight_wagons_count; i++)
            wagons.push_back(new Freight_wagon);
        for (int i = 0; i < passenger_wagons_count; i++)
            wagons.push_back(new Passenger_wagon);
    }


    void load_passengers(std::vector<Passenger> &passengers);

    void load_cargo(std::vector<Cargo> &Cargo);

    std::vector<Passenger> unload_passengers_by_their_dest_point();

    std::vector<Cargo> unload_cargo_by_type(const std::string &type);

    int get_weight() const override;

    bool move(const int &distance);

    bool if_on_station() const { return is_on_station; }

    void make_move() { is_on_station = false; }

    std::string get_next_station() const;

    std::string get_current_station() const { return route[current_position_on_route]; }

    float progress = 0;

    const std::vector<std::string>get_route(){return route;}
private:
    Locomotive locomotive;
    std::vector<Base_wagon *> wagons;
    bool is_on_station = true;
    std::vector<std::string> route;
    int current_position_on_route = 0;

};

#endif //SEM3_LAB3_PPVIS_TRAINS_H
