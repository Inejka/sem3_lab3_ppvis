//
// Created by inejka on 02.10.2020.
//

#ifndef SEM3_LAB3_PPVIS_TRAINS_H
#define SEM3_LAB3_PPVIS_TRAINS_H

#include <vector>
#include <string>

class Entity_with_weight {
public:
    virtual int get_its_weight() const = 0 ;

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

    int get_its_weight() const override { return its_weight; }

private:
    std::string its_name;
    int its_destination_point;
};

class Cargo : public Entity_with_weight {
public:
    Cargo(int type, int weight) : its_type(type) { set_its_weight(weight); }

    bool check_type(const int &to_check) const { return to_check == its_type; }

    int get_its_weight() const override { return its_weight; }

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

    int get_its_weight()const  override { return its_weight; }

private:
    int pulling_force, life_time;
};

class Wagon_p : public Entity_with_weight {
public:
    Wagon_p(const int& weight){set_its_weight(weight);}
    virtual std::string get_its_type() = 0;
    int get_its_weight() const override{
        return its_weight;
    }
};

template<class T1>
class Wagon :  public Wagon_p{
public:
    Wagon(const int &max_capacity, std::string its_type , const int & weight) : Wagon_p(weight) ,max_capacity(max_capacity), its_type(its_type) {}

    bool add(const T1 &to_add);

    void laod(std::vector<T1> &to_load);

    virtual std::vector<T1> unload(const int &par);

    std::string get_its_type() override{
        return its_type;
    }
protected:
    virtual bool unload_decision(const T1 &make_decision_about,const int & par) = 0;
    const std::vector<T1> get_list_for_weight() const {return list;}
private:
    int max_capacity;
    std::vector<T1> list;
    std::string its_type;

};


class Passenger_wagon : public Wagon<Passenger> {
public:
    Passenger_wagon():Wagon(60,"Passanger_wagon",4000){}
    int get_its_weight()const  override;
protected:
    bool unload_decision(const Passenger &make_decision_about,const int & par) override;
};

class Freight_wagon : public Wagon<Cargo> {
public:
    Freight_wagon():Wagon(500,"Cargo_wagon",2500) {  }
    int get_its_weight() const override;
protected:
    bool unload_decision(const Cargo &make_decision_about,const int & par) override;
};

class Train : Entity_with_weight {
public:
    Train(int locomotive_lifetime, int locomotive_pulling_force, int freight_wagons_count,
          int passenger_wagons_count) : its_locomotive(locomotive_pulling_force,
                                                       locomotive_lifetime) {
            for(int i = 0 ; i < freight_wagons_count ; i++)
                its_wagons.push_back(new Freight_wagon);
            for(int i = 0 ; i < passenger_wagons_count; i++)
                its_wagons.push_back(new Passenger_wagon);
    }

    void load_passangers(std::vector<Passenger> &passagers);

    void load_Cargo(std::vector<Cargo> &Cargo);

    std::vector<Passenger> unload_passangers_by_their_dest_point(const int &current_station);

    std::vector<Cargo> unload_Cargo_by_type(const int &type);

    int get_its_weight() const override;

    bool move(const int &distance, float &percent);

    bool if_on_station() const { return is_on_station; }

    void make_move() { is_on_station = false; }

private:
    Locomotive its_locomotive;
    std::vector<Wagon_p*> its_wagons;
    bool is_on_station = true;

    //    std::vector<int> its_route;
    //    int current_position_on_its_route = 0;

};

#endif //SEM3_LAB3_PPVIS_TRAINS_H
